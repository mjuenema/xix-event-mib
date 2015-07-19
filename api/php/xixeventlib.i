
%include "../xixeventlib.i";

/* Provide aliases for convenience */
%pragma(php) code="

function xix_event_set_notification($manager,$community,$xix_event_id,$xix_event_text) {
        return xix_event_set_notification_2($manager,$community,$xix_event_id,$xix_event_text);
}

function xix_event_set($manager,$community,$xix_event_id,$xix_event_text) {
        return xix_event_set_notification_2($manager,$community,$xix_event_id,$xix_event_text);
}

function xix_event_set_inform($manager,$community,$xix_event_id,$xix_event_text) {
        return xix_event_set_inform_2($manager,$community,$xix_event_id,$xix_event_text);
}

function xix_event_clear_notification($manager,$community,$xix_event_id) {
        return xix_event_clear_notification_2($manager,$community,$xix_event_id);
}

function xix_event_clear($manager,$community,$xix_event_id) {
        return xix_event_clear_notification_2($manager,$community,$xix_event_id);
}

function xix_event_clear_inform($manager,$community,$xix_event_id) {
        return xix_event_clear_inform_2($manager,$community,$xix_event_id);
}
"
