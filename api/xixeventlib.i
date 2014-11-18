
%module xixeventlib

%{
#define SWIG_FILE_WITH_INIT
#include "xixeventlib.h"
%}

/* xixEventSet (SNMPv2-NOTIFICATION) */
%feature("autodoc", "0");
int xix_event_set_notification_2(char *manager,
                                 char *community,
                                 char *xix_event_id,
                                 char *xix_event_text);


/* xixEventSet (SNMPv2-INFORM) */
%feature("autodoc", "0");
int xix_event_set_inform_2(char *manager,
                           char *community,
                           char *xix_event_id,
                           char *xix_event_text);


/* xixEventClear (SNMPv2-NOTIFICATION) */
%feature("autodoc", "0");
int xix_event_clear_notification_2(char *manager,
                                   char *community,
                                   char *xix_event_id);


/* xixEventClear (SNMPv2-INFORM) */
%feature("autodoc", "0");
int xix_event_clear_inform_2(char *manager,
                             char *community,
                             char *xix_event_id);
