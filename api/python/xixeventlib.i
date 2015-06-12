
%include "../xixeventlib.i";

/* Wrapper with keyword arguments */
%pythoncode %{

def set_event(manager, xix_event_id, xix_event_text,
              version=2, community='public', inform=False):

    if inform:
        inform = 1
    else:
        inform = 0

    return xix_event(manager, version, community, inform, 
                     xix_event_id, xix_event_text)


def clear_event(manager, xix_event_id,
              version=2, community='public', inform=False):

    if inform:
        inform = 1
    else:
        inform = 0

    return xix_event(manager, version, community, inform, 
                     xix_event_id, None)

%}
