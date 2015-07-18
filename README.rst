xix-event-mib
=============

The XIX-EVENT-MIB defines notifications (traps) that enable an SNMP
agent to send generic events to an SNMP manager. 

SNMP agents can alert the manager that an event has become active
(``xixEventSet``) or that an event has cleared (`xixEventClear``).

An ``xixEventSet`` notification contains a short textual identifier 
(``xixEventId``) and a message (``xixEventText``). The message may contain 
any kind of text that describes the event.  The purpose of the 
identifier is to distinguish between different types of events. Its 
content is generally not meant to be displayed by an SNMP manager.

An ``xixEventClear`` notification contains only the identifier. Its 
purpose is to signal to the SNMP manager that a any previously
sent ``xxixEventSet`` notification with the same identifier has
cleared.


Example
--------

The example below first alerts the SNMP manager that the ``/tmp``
filesystem is almost full. It then clears the previous event
(presumably because there is enough free space in ``/tmp`` again)::

    snmptrap -v 2c -c public nms.example.org '' \
        xixEventSet \
        xixEventId s "diskspace.tmp" \
        xixEventText s "/tmp is 95% full"

    snmptrap -v 2c -c public nms.example.org '' \
        xixEventClear \
        xixEventId s "diskspace.tmp"


API
---

The ``python/`` directory contains a Python package for sending XIX-EVENT-MIB
SNMPv2c/SNMPv3 notifications and informs as well as SNMPv1 traps. It
requires PySNMP to be installed.

The ``api/`` directory contains libraries for sending XIX-EVENT-MIB 
SNMPv2c notifications and informs from the following languages.

* C
* Python (if PySNMP is not available)
* Perl
* PHP (planned)
* others (maybe)

These API are stand-alone but do not support SNMPv1 and SNMPv3.


