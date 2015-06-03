#!/usr/bin/env perl

# This just tests whether it works without crashing.
#
# I am not a Perl programmer!!!
#
# MJ, 03-Jun-2015


use xixeventlib;

xixeventlib::xix_event_set_notification_2("127.0.0.1", "public", "id", "text");

xixeventlib::xix_event_set_inform_2("127.0.0.1", "public", "id", "text");

xixeventlib::xix_event_clear_notification_2("127.0.0.1", "public", "id");

xixeventlib::xix_event_clear_inform_2("127.0.0.1", "public", "id");

xixeventlib::xix_event_set("127.0.0.1", "public", "id", "text");

xixeventlib::xix_event_clear("127.0.0.1", "public", "id");

xixeventlib::xix_event_set_inform("127.0.0.1", "public", "id", "text");

xixeventlib::xix_event_clear_inform("127.0.0.1", "public", "id");
