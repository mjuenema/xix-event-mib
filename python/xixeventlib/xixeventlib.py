# -*- coding: utf-8 -*-

"""


"""


import sys
import types

from pysnmp.entity.rfc3413.oneliner import ntforg
from pysnmp.proto import rfc1902
NTFORG = ntforg.NotificationOriginator()


DEFAULT_TARGET = "localhost"
DEFAULT_COMMUNITY = "public"
DEFAULT_PORT = 162
DEFAULT_TIMEOUT = 1
DEFAULT_RETRIES = 3


OID_XIX_EVENT_SET="1.3.6.1.4.1.32979.1.1.0.1"
OID_XIX_EVENT_CLEAR="1.3.6.1.4.1.32979.1.1.0.2"
OID_XIX_EVENT_ID="1.3.6.1.4.1.32979.1.1.1.1"
OID_XIX_EVENT_TEXT="1.3.6.1.4.1.32979.1.1.1.2"


# Setup logging and suppress a possible
# "No handlers could be found for …” warning.
#
import logging
_LOG = logging.getLogger(__name__)


def event(event_id, event_text='',
          target=DEFAULT_TARGET, port=DEFAULT_PORT, community=DEFAULT_COMMUNITY,
          inform=False, version=2, timeout=DEFAULT_TIMEOUT, retries=DEFAULT_RETRIES,
          callback)

    """
    Send an ``xixEventSet`` or ``xixEventClear`` SNMP trap/notification.

    Depending on the command line arguments, any of the following may be
    sent.

    xixEventSet (SNMPv1 trap)
        Sent if `event_text` is not empty and `version` is 1.

    xixEventClear (SNMPv1 trap)
        Sent if `event_text` is empty and `version` is 1.

    xixEventSet(SNMPv2c notification)
        Sent if `event_text` is not empty.

    xixEventClear(SNMPv2c notification)
        Sent if `event_text` is empty.

    xixEventSet(SNMPv2c inform)
        Sent if `event_text` is not empty and `inform` evaluates to true.
        Set `timeout` and `retries` to tune this.

    xixEventClear(SNMPv2c inform)
        Sent if `event_text` is empty and `inform` evaluates to true.
        Set `timeout` and `retries` to tune this.

    xixEventSet(SNMPv3 notification)
        Sent if `event_text` is not empty and SNMPv3 arguments are set.

    xixEventClear(SNMPv3 notification)
        Sent if `event_text` is empty and SNMPv3 arguments are set.

    xixEventSet(SNMPv3 notification)
        Sent if `event_text` is not empty, `inform` evaluates to true
         and SNMPv3 arguments are set.

    xixEventClear(SNMPv3 notification)
        Sent if `event_text` is empty, `inform` evaluates to true
        and SNMPv3 arguments are set.

    :param event_id: ``xixEventId``.
    :type event_id: String.

    :param event_text: ``xixEventText`` for ``xixEventSet`` events or left
        empty (or anything else that evaluates to ``False``) for 
        ``xixEventClear`` events. 
    :type event_id: String (``xixEventSet``) or anything that evaluates
        to ``False`` (``xixEventClear``).

    :param target: The host to send the trap/notification to. The default is
        ``localhost`` which is useful for forwarding traps through
        snmptrapd_. 
    :type target: String.

    :param port: The UDP port the target(s) listen to. Naturally `port`
        defaults to 162.
    :type port: Integer.

    :param community: Community for SNMPv1 and SNMPv2c operations. Ignored
        if any of the SNMPv3 related arguments are given. `community`
        defaults to ``public``.
    :type community: String.

    :param inform: Send SNMPv2c/V3 inform instead of notification. Setting
        `inform` to true will force SNMPv2c/3 even if `version` is 1 as
        SNMPv1 does not implement SNMP inform.
    :type inform: Truth value.

    :param timeout: Timeout parameter of SNMP inform operation.
    :type timeout: Integer.

    :param retries: Retries parameter of SNMP inform operation.
    :type retries: Integer.

    :param callback: Setting `callback` to a function makes all operations
        asynchronous. The callback function must have the same signature
        as the callback functions in PySNMP_.

    :param lifetime: Setting `lifetime` to a positive number will suppress
        any future calls to `xixeventlib.event()` for as many seconds
        if the `event_id`, `event_text`, `target` and, `port` have been
        identical. This may be useful to reduce the number of effectively
        identical traps/notifications being sent to the same `target`.

    .. _snmptrapd:: http://www.net-snmp.org/wiki/index.php/Snmptrapd
    .. _PySNMP:: http://pysnmp.sourceforge.net/


    """


          



