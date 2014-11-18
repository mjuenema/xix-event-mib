
from xixeventlib import *


print xix_event_set_notification_2("10.193.56.94", "public", "id", "text")

print xix_event_set_inform_2("10.193.56.94", "public", "id", "text")

print xix_event_clear_notification_2("10.193.56.94", "public", "id")

print xix_event_clear_inform_2("10.193.56.94", "public", "id")

print xix_event_set("10.193.56.94", "public", "id", "text")

print xix_event_clear("10.193.56.94", "public", "id")

print xix_event_set_inform("10.193.56.94", "public", "id", "text")

print xix_event_clear_inform("10.193.56.94", "public", "id")
