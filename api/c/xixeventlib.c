/*
 
  xixeventlib.c

  Functions for sending xixEventSet and xixEventClear TRAPS,
  NOTIFICATIONS and INFORMS in SNMPv1, SNMPV2c and SNMPv3.

  Currently only SNMPv2c has been implemented!

  Markus Juenemann - <markus@juenemann.net>

*/

#include <net-snmp/net-snmp-config.h>

#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#include <sys/types.h>
#if HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
#if TIME_WITH_SYS_TIME
# ifdef WIN32
#  include <sys/timeb.h>
# else
#  include <sys/time.h>
# endif
# include <time.h>
#else
# if HAVE_SYS_TIME_H
#  include <sys/time.h>
# else
#  include <time.h>
# endif
#endif
#if HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif
#include <stdio.h>
#if HAVE_WINSOCK_H
#include <winsock.h>
#endif
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if HAVE_NETDB_H
#include <netdb.h>
#endif
#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#include <net-snmp/net-snmp-includes.h>

#include "xixeventlib.h"


/* Hard-coded OIDs to avoid having to parse the MIB files. */
oid objid_enterprise[] = { 1, 3, 6, 1, 4, 1, 3, 1, 1 };
oid objid_sysdescr[] = { 1, 3, 6, 1, 2, 1, 1, 1, 0 };
oid objid_sysuptime[] = { 1, 3, 6, 1, 2, 1, 1, 3, 0 };
oid objid_snmptrap[] = { 1, 3, 6, 1, 6, 3, 1, 1, 4, 1, 0 };

/*	smidump -p XIX-MIB.mib -f identifiers XIX-EVENT-MIB.mib
	
	XIX-EVENT-MIB xixEventMib node 1.3.6.1.4.1.32979.1
	XIX-EVENT-MIB xixEventMibObjects node 1.3.6.1.4.1.32979.1.1
	XIX-EVENT-MIB xixEventNotifications node 1.3.6.1.4.1.32979.1.1.0
	XIX-EVENT-MIB xixEventSet notification 1.3.6.1.4.1.32979.1.1.0.1
	XIX-EVENT-MIB xixEventClear notification 1.3.6.1.4.1.32979.1.1.0.2
	XIX-EVENT-MIB xixEventObjects node 1.3.6.1.4.1.32979.1.1.1
	XIX-EVENT-MIB xixEventId scalar 1.3.6.1.4.1.32979.1.1.1.1
	XIX-EVENT-MIB xixEventText scalar 1.3.6.1.4.1.32979.1.1.1.2
	XIX-EVENT-MIB xixEventGroups node 1.3.6.1.4.1.32979.1.1.2
	XIX-EVENT-MIB xixEventObjectsGroup group 1.3.6.1.4.1.32979.1.1.2.1
	XIX-EVENT-MIB xixEventNotificationsGroup group 1.3.6.1.4.1.32979.1.1.2.2
	XIX-EVENT-MIB xixEventCompliances node 1.3.6.1.4.1.32979.1.1.3
	XIX-EVENT-MIB xixEventCompliances compliance 1.3.6.1.4.1.32979.1.1.3.1
*/
oid objid_xix_event_set[] = {1, 3, 6, 1, 4, 1, 32979, 1, 1, 0, 1};
oid objid_xix_event_clear[] = {1, 3, 6, 1, 4, 1, 32979, 1, 1, 0, 2};
char *oid_xix_event_set = ".1.3.6.1.4.1.32979.1.1.0.1";
char *oid_xix_event_clear = ".1.3.6.1.4.1.32979.1.1.0.2";

oid objid_xix_event_id[] = {1, 3, 6, 1, 4, 1, 32979, 1, 1, 1, 1};
oid objid_xix_event_text[] = {1, 3, 6, 1, 4, 1, 32979, 1, 1, 1, 2};

int inform = 0;


/* xixEventSet (SNMPv2-NOTIFICATION) */
int xix_event_set_notification_2(char *manager, 
                                 char *community, 
                                 char *xix_event_id,
                                 char *xix_event_text) {

    return xix_event(manager, 2, community, 0, xix_event_id, xix_event_text);
}


/* xixEventSet (SNMPv2-INFORM) */
int xix_event_set_inform_2(char *manager,
                           char *community,
                           char *xix_event_id,
                           char *xix_event_text) {

    return xix_event(manager, 2, community, 1, xix_event_id, xix_event_text);
}


/* xixEventClear (SNMPv2-NOTIFICATION) */
int xix_event_clear_notification_2(char *manager,
                                   char *community,
                                   char *xix_event_id) {

    return xix_event(manager, 2, community, 0, xix_event_id, NULL);
}


/* xixEventClear (SNMPv2-INFORM) */
int xix_event_clear_inform_2(char *manager,
                             char *community,
                             char *xix_event_id) {

    return xix_event(manager, 2, community, 1, xix_event_id, NULL);
}


/* 
	Send an XIX-EVENT-MIB TRAP, NOTIFICATION or INFORM.

	@param manager: Hostname or IP address of SNMP manager.
	@param version: The SNMP version (2=2c, others=1).
	@param community: The SNMP Community string or NULL. NULL
	    is interpreted as 'public'.
	@param inform: Whether to send an INFORM instead of a
	    TRAP/NOTIFICATION. Any non-zero value will cause an
		INFORM to be sent and force version 2c.
	@param xix_event_id: The xixEventId varbind.
	@param xix_event_text: The xixEventText varbind or NULL. If
	    NULL an xixEventClear trap will be sent, otherwise an
		xixEventSet trap will be sent.

*/
int xix_event(char *manager, int version, 
              char *community, int inform,
              char *xix_event_id, char *xix_event_text) {

    netsnmp_session session;			/* Session parameters. */
    netsnmp_session *ss;			/* The actual session. */
	
    netsnmp_pdu *pdu;				/* SNMP PDU for the request. */
    netsnmp_pdu *response;			/* SNMP PDU for the response to an INFORM */

    netsnmp_log_handler	*log_handler;		/* Log handler. */
	
    long luptime;				/* System uptime as long... */
    char cuptime[20];				/* ... and text. */

    int status;                                 /* Status information. */
	
	
    /* Initialise the SNMP library. */
    init_snmp("xixeventlib");


    /* Configure logging. */
    snmp_disable_log();
    log_handler = netsnmp_register_loghandler(NETSNMP_LOGHANDLER_NONE, LOG_DEBUG);
    if (log_handler) {
        log_handler->pri_max = LOG_EMERG;
    }
	
	
    /* Populate the session. */
    snmp_sess_init( &session ); 


    /* manager */
    session.peername = manager;
	

    /* version */
    if(version == 2 || inform ) {
        session.version = SNMP_VERSION_2c;
    } else {
	session.version = SNMP_VERSION_1;
    }
	

    /* community */
    if (community != NULL) {
        session.community = (u_char *)community;
    } else {
        session.community = (u_char *)strdup("public");
    }
    session.community_len = strlen((const char *)session.community);


    /* No callbacks! */
    session.callback = NULL;
    session.callback_magic = NULL;


    /* Set the port. */
    netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, NETSNMP_DS_LIB_DEFAULT_PORT, SNMP_TRAP_PORT);


    /* Open the session. */
    SOCK_STARTUP;
    ss = snmp_open(&session);
    if (!ss) {
        snmp_sess_perror("snmp_open()", &session);
        SOCK_CLEANUP;
        return -1;
    }
    
	
	
    if (session.version == SNMP_VERSION_1) {

        /* SNMPv1 TRAP. */
        // TODO: implement SNMPv1 TRAP
        return -1;

    } else { /* if(session.version == SNMP_VERSION_1) */

        /* SNMPv2c TRAP/INFORM. */

        pdu = snmp_pdu_create(inform ? SNMP_MSG_INFORM : SNMP_MSG_TRAP2);
        
        /* Add uptime. */
        luptime = get_uptime();
        sprintf(cuptime, "%ld", luptime);
       
        if (snmp_add_var(pdu, objid_sysuptime, sizeof(objid_sysuptime) / sizeof(oid), 't', cuptime) != 0 ) {
            snmp_sess_perror("snmp_add_var(objid_sysuptime)", ss);
            SOCK_CLEANUP;
            return(1);
        };


        /* Add TRAP OID and varbinds. */
        if (xix_event_text == NULL) {

            /* xixEventClear. */
            if (snmp_add_var (pdu, objid_snmptrap, sizeof(objid_snmptrap) / sizeof(oid), 'o', oid_xix_event_set) != 0) {
                snmp_sess_perror("snmp_add_var(objid_snmptrap)", ss);
                SOCK_CLEANUP;
                return(1);
            }

            /* xixEventId. */
            if (snmp_add_var (pdu, objid_xix_event_id, sizeof(objid_xix_event_id) / sizeof(oid), 's', xix_event_id) != 0) {
                snmp_sess_perror("snmp_add_var(objid_snmptrap)", ss);
                SOCK_CLEANUP;
                return(1);
            }

        } else { /* if(xix_event_text == NULL) */

            /* xixEventSet. */
            if (snmp_add_var (pdu, objid_snmptrap, sizeof(objid_snmptrap) / sizeof(oid), 'o', oid_xix_event_set) != 0) {
                snmp_sess_perror("snmp_add_var(objid_snmptrap)", ss);
                SOCK_CLEANUP;
                return(1);
            }

            /* xixEventId. */
            if (snmp_add_var (pdu, objid_xix_event_id, sizeof(objid_xix_event_id) / sizeof(oid), 's', xix_event_id) != 0) {
                snmp_sess_perror("snmp_add_var(objid_snmptrap)", ss);
                SOCK_CLEANUP;
                return(1);
            }

            /* xixEventText. */
            if (snmp_add_var (pdu, objid_xix_event_text, sizeof(objid_xix_event_text) / sizeof(oid), 's', xix_event_text) != 0) {
                snmp_sess_perror("snmp_add_var(objid_snmptrap)", ss);
                SOCK_CLEANUP;
                return(1);
            }

        }

    } /* if(session.version == SNMP_VERSION_1) */ 


    /* Send the stuff. */
    if (inform) {
        status = snmp_synch_response(ss, pdu, &response);
    } else {
        status = snmp_send(ss, pdu) == 0;
    }

    if (status) {
        snmp_sess_perror(inform ? "snmpinform" : "snmptrap", ss);
    }


    if (status) {
        snmp_sess_perror(inform ? "snmpinform" : "snmptrap", ss);
        if (!inform)
            snmp_free_pdu(pdu);
    } else if (inform)
        snmp_free_pdu(response);

    snmp_close(ss);
    SOCK_CLEANUP;

   
    /* Return the status. */
    return status;
}


