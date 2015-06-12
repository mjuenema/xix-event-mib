#!/usr/bin/env python

"""

Edit the SNMP client configuration to speed up testing
SNMPv2 INFORMs.

  # vi /etc/snmp/snmp.conf
  timeout 1
  retries 1

"""

# TODO: Rewrite this as nosetests
# TODO: version=1, and inform=True + version=1 should raise NotImplementedError

from xixeventlib import *


assert set_event('127.0.0.1', 'test', 'test') == 0
assert set_event('127.0.0.1', 'test', 'test', version=2) == 0
assert set_event('127.0.0.1', 'test', 'test', community='public') == 0
assert set_event('127.0.0.1', 'test', 'test', inform=True) == 2
assert set_event('127.0.0.1', 'test', 'test', inform=False) == 0
assert set_event('127.0.0.1', 'test', 'test', inform=None) == 0
assert set_event('127.0.0.1', 'test', 'test', inform=1) == 2
assert set_event('127.0.0.1', 'test', 'test', inform=0) == 0

assert clear_event('127.0.0.1', 'test') == 0
assert clear_event('127.0.0.1', 'test', version=2) == 0
assert clear_event('127.0.0.1', 'test', community='public') == 0
assert clear_event('127.0.0.1', 'test', inform=True) == 2
assert clear_event('127.0.0.1', 'test', inform=False) == 0
assert clear_event('127.0.0.1', 'test', inform=None) == 0
assert clear_event('127.0.0.1', 'test', inform=1) == 2
assert clear_event('127.0.0.1', 'test', inform=0) == 0

## SNMPv1 is not yet implemented
##
#assert set_event('127.0.0.1', 'test', 'test', version=1) == -1
#assert clear_event('127.0.0.1', 'test', version=1) == -1

## inform=True will always be SNMPv2
#assert set_event('127.0.0.1', 'test', 'test', version=1, inform=True) == 2
#assert clear_event('127.0.0.1', 'test', version=1, inform=True) == 2
