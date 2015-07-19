API
===

C
--

::

  int xix_event(char *manager, int version,
                char *community, int inform,
               char *xix_event_id, char *xix_event_text);

* ``manager`` is the name or IP address of the host to send the trap to.
* ``version`` is not actually used as only SNMPv2c has been implemented.
* ``community`` is the SNMPv2c community string.
* If ``inform`` is non-zero an SNMPv2c INFORM will be sent instead of 
  a SNMPv2c NOTIFICATION.
* ``xix_event_id`` is the event id.
* ``xix_event_text`` sets the event text for an ``xixEventSet`` notification
  unless it is ``NULL`` which will send an ``xixEventClear`` notification.
  

Python
------

The Python API has 




Perl
----




PHP
---
