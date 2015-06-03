
%include "../xixeventlib.i";

/* Provide aliases for convenience */
%perlcode %{

*xix_event_set_notification = *xixeventlibc::xix_event_set_notification_2;
*xix_event_set = *xixeventlibc::xix_event_set_notification_2;

*xix_event_clear_notification = *xixeventlibc::xix_event_clear_notification_2;
*xix_event_clear = *xixeventlibc::xix_event_clear_notification_2;

*xix_event_set_inform = *xixeventlibc::xix_event_set_inform_2;
*xix_event_clear_inform = *xixeventlibc::xix_event_clear_inform_2;

%}
