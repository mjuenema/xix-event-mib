
%include "../xixeventlib.i";

/* Wrapper with keyword arguments */
%pythoncode %{

def _xix_event(manager, version, community, inform,
               xix_event_id, xix_event_text):
    """
    Python wrapper around the C ```xix_event()``` function.
    
    The purpose of this wrapper is to normalise arguments
    for the C function call. 

    """

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
              version=2, community='public', inform=False):

    return _xix_event(manager, version, community, inform, 
                     xix_event_id, xix_event_text)


def clear_event(manager, xix_event_id,
              version=2, community='public', inform=False):

    return _xix_event(manager, version, community, inform, 
                     xix_event_id, None)

%}
