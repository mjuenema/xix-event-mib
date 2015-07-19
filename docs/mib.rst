XIX-EVENT-MIB
=============

The XIX-EVENT-MIB defines notifications (traps) that enable an SNMP
agent to send generic events to an SNMP manager.

SNMP agents can alert the manager that an event has become active
(``xixEventSet``) or that an event has cleared (``xixEventClear``).

An ``xixEventSet`` notification contains a short textual identifier
(``xixEventId``) and a message (``xixEventText``). The message may contain
any kind of text that describes the event.  The purpose of the
identifier is to distinguish between different types of events. Its
content is generally not meant to be displayed by an SNMP manager.

An ``xixEventClear`` notification contains only the identifier. Its
purpose is to signal to the SNMP manager that a any previously
sent ``xxixEventSet`` notification with the same identifier has
cleared.


OID Tree
--------

.. code-block:: console

   $ smidump -p XIX-MIB.mib -f tree -tree-full-root -tree-compact XIX-EVENT-MIB.mib 
   
   iso(1)
     +-org(3)
       +-dod(6)
         +-internet(1)
           +-private(4)
             +-enterprises(1)
               +-xix(32979)
                 +-xixEventMib(1)
                   +-xixEventMibObjects(1)
                     +-xixEventNotifications(0)
                     |  +-xixEventSet(1) [xixEventId,xixEventText]
                     |  +-xixEventClear(2) [xixEventId]
                     +-xixEventObjects(1)
                     |  +- r-n DisplayString xixEventId(1)
                     |  +- r-n DisplayString xixEventText(2)
                     +-xixEventGroups(2)
                     |  +-xixEventObjectsGroup(1)
                     |  +-xixEventNotificationsGroup(2)
                     +-xixEventCompliances(3)
                       +-xixEventCompliances(1)

Identifiers
-----------

.. code-block:: console

   $ smidump -p XIX-MIB.mib -f identifiers XIX-EVENT-MIB.mib 

   XIX-EVENT-MIB xixEventMib                node         1.3.6.1.4.1.32979.1
   XIX-EVENT-MIB xixEventMibObjects         node         1.3.6.1.4.1.32979.1.1
   XIX-EVENT-MIB xixEventNotifications      node         1.3.6.1.4.1.32979.1.1.0
   XIX-EVENT-MIB xixEventSet                notification 1.3.6.1.4.1.32979.1.1.0.1
   XIX-EVENT-MIB xixEventClear              notification 1.3.6.1.4.1.32979.1.1.0.2
   XIX-EVENT-MIB xixEventObjects            node         1.3.6.1.4.1.32979.1.1.1
   XIX-EVENT-MIB xixEventId                 scalar       1.3.6.1.4.1.32979.1.1.1.1
   XIX-EVENT-MIB xixEventText               scalar       1.3.6.1.4.1.32979.1.1.1.2
   XIX-EVENT-MIB xixEventGroups             node         1.3.6.1.4.1.32979.1.1.2
   XIX-EVENT-MIB xixEventObjectsGroup       group        1.3.6.1.4.1.32979.1.1.2.1
   XIX-EVENT-MIB xixEventNotificationsGroup group        1.3.6.1.4.1.32979.1.1.2.2
   XIX-EVENT-MIB xixEventCompliances        node         1.3.6.1.4.1.32979.1.1.3
   XIX-EVENT-MIB xixEventCompliances        compliance   1.3.6.1.4.1.32979.1.1.3.1
