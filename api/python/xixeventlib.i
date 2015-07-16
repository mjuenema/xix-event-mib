
%include "../xixeventlib.i";

/* Wrapper with keyword arguments */
%pythoncode %{

import time

STATEDB = {}

def _suppress_event(manager, version, community, inform,
                    xix_event_id, xix_event_text, expiry=0):
    """

    :returns: ``True`` if event is to be suppressed, ``False``
              otherwise.

    """

    global STATEDB

    now = time.time()


    key = "%s%s%s%s%s" % (manager, version, community, inform, xix_event_id)
    try:
        (old_expiry, old_xix_event_text) = STATEDB[key]

        if old_xix_event_text <> xix_event_text:
            # Send trap as the event state changed.
            STATEDB[key] = (time.time() + expiry, xix_event_text)
            return False
        else:
            if now > old_expiry:
                # Resend trap as the previous one has expired.
                STATEDB[key] = (time.time() + expiry, xix_event_text)
                return False
            else:
                # Suppress this event as the previous one has not expired yet.
                return True
            
    except KeyError:
        # This is the first time this event occured.
        STATEDB[key] = (time.time() + expiry, xix_event_text)

        # Garbage collectd STATEDB
        for (key, value) in STATEDB.items():
            (old_expiry, old_xix_event_text) = value

            if now > old_expiry:
                del(STATEDB[key])

        return False



def _xix_event(manager, version, community, inform,
               xix_event_id, xix_event_text, expiry=0):
    """
    Python wrapper around the C `xix_event()` function.
    
    The purpose of this wrapper is to normalise arguments
    for the C function call. 

    If ``expiry`` is a positive number, any subsequent calls
    to this function with identical(!) arguments will be suppressed
    for ``expiry`` seconds. The idea is to reduce the amount
    of identical SNMP notifications. The expiry of related
    "set" and "clear" events are dealt with correctly.

    State is stored in the dictionary like object stored
    in ``STATEDB``.

    """

    if expiry > 0 and _suppress_event(manager, version, community, inform, 
                                      xix_event_id, xix_event_text, expiry) is True:
        return None


    # Normalise values for the C function call.
    #
    manager = str(manager)

    version = int(version)

    if version not in [1, 2, 3]:
        raise ValueError('SNMP version must be 1, 2, or 3')

    if version in [1, 3]:
        raise NotImplementedError('Currently only SNMPv2c is supported')

    community = str(community)

    if inform:
        inform = 1
    else:
        inform = 0

    xix_event_id = str(xix_event_id)

    if xix_event_text:
        xix_event_text = str(xix_event_text)
    else:
        xix_event_text = None


    return xix_event(manager, version, community, inform, 
                     xix_event_id, xix_event_text)


def set_event(manager, xix_event_id, xix_event_text,
              version=2, community='public', inform=False, expiry=0):

    return _xix_event(manager, version, community, inform, 
                     xix_event_id, xix_event_text, expiry=expiry)


def clear_event(manager, xix_event_id,
              version=2, community='public', inform=False, expiry=0):

    return _xix_event(manager, version, community, inform, 
                     xix_event_id, None, expiry=expiry)

%}
