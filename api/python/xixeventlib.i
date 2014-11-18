
%include "../xixeventlib.i";

/* Provide aliases for convenience */
%pythoncode %{

xix_event_set_notification = xix_event_set_notification_2
xix_event_set = xix_event_set_notification

xix_event_clear_notification = xix_event_clear_notification_2
xix_event_clear = xix_event_clear_notification

xix_event_set_inform = xix_event_set_inform_2
xix_event_clear_inform = xix_event_clear_inform_2

%}
