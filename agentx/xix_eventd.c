/*
 *
 *
 * Shamelessly adapted from 
 * http://openhpi.sourceforge.net/subagent-manual/c167.html
 *
 * See also: http://www.net-snmp.org/docs/man/snmp_agent_api.html
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <xix_event.h>

#define NAME "xix-eventd"
#define FIFO "/var/run/xix-event.fifo"

        
static int keep_running;

RETSIGTYPE stop_server(int a) {
    keep_running = 0;
}


int main (int argc, char **argv) {

  FILE *fp;
  char buffer[512];
  char *xixEventId, *xixEventText;
  struct stat st;

  /* Change below if you want to be a SNMP master agent */
  int agentx_subagent=1; /* change this if you want to be a SNMP master agent */


  /* Print log errors to stderr */
  snmp_enable_stderrlog();


  /* Enable below for debugging */
  //snmp_set_do_debugging(1);
 

  /* Are we an AgentX subagent? */
  if (agentx_subagent) {

    /* Make us an AgentX client. */
    netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID, 
                NETSNMP_DS_AGENT_ROLE, 1);
  }


  /* Initialize the agent library */
  init_agent(NAME);


  /* NOTE: No MIB code needs to be initialised. */


  /* Read config file: NAME.conf */
  init_snmp(NAME);


  /* Initialised port 161/UDP if we're going to be 
   * an SNMP master agent */
  if (!agentx_subagent)
    init_master_agent();  


  /* Daemonise */
  if (netsnmp_daemonize(1, 0)) {
      snmp_log(LOG_ERR, "failed to become daemon\n");
      exit(1);
  }


  /* In case we receive a request to stop (kill -TERM or kill -INT) */
  keep_running = 1;
  signal(SIGTERM, stop_server);
  signal(SIGINT, stop_server);


  /* Create the FIFO if it does not exist */
  if (stat(FIFO, &st)) {
    if(mknod (FIFO, S_IRUSR|S_IWUSR|S_IFIFO, 0)) {
      snmp_log(LOG_ERR, "error creating create missing FIFO %s: %s\n", FIFO, strerror(errno));
      return errno;
    }
  }

  
  /* Open FIFO for reading */
  if ((fp = fopen(FIFO, "r")) == NULL) {
    snmp_log(LOG_ERR, "error opening FIFO %s: %s\n", FIFO, strerror(errno));
    return errno;
  }


  /* Main loop */
  while(keep_running) {

    /* Since XIX-EVENT-MIB does not contain scalars or tables
     * we don't have to call `agent_check_and_process()`
     * or similar. We simply keep reading from the FIFO and
     * send off notifications. */

    if((fgets(buffer, sizeof(buffer)-1, fp)) == NULL) {
        //snmp_log(LOG_ERR, "error reading from FIFO %s: %s\n", FIFO, strerror(errno));
        continue;
        //return errno;
    }

    /* Extract xixEventId which is the first word in the line */
    if ((xixEventId = strtok(buffer, " \n\r")) == NULL) {
        snmp_log(LOG_INFO, "unable to parse event id from '%s'\n", buffer);
        continue;
    }

    /* Try to find xixEventText */
    if ((xixEventText = strtok(NULL, "\n\r")) == NULL) {

        /* Send xixEventClear notification */
        if (send_xixEventClear_trap(xixEventId) != SNMP_ERR_NOERROR) {
          snmp_log_perror("error sending xixEventClear notification");
          continue;
        }
    } else {
        /* Send xixEventSet notification */
        if (send_xixEventSet_trap(xixEventId, xixEventText) != SNMP_ERR_NOERROR) {
          snmp_log_perror("Error sending xixEventSet notification");
          continue;
        }
    } 
  } 

  /* Shutdown */
  snmp_shutdown(NAME);
  return 1;
}
