

OBJS=xix_eventd.o xix_event.o
TARGETS=xix-eventd

CFLAGS=-I. `net-snmp-config --cflags`
BUILDLIBS=`net-snmp-config --libs`
BUILDAGENTLIBS=`net-snmp-config --agent-libs`
DLFLAGS=-fPIC -shared

all: $(TARGETS)

xix-eventd: $(OBJS)
	$(CC) -o xix-eventd $(OBJS) $(BUILDAGENTLIBS)

xix_event.o: xix_event.c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o xix_event.o xix_event.c

clean:
	rm -fv xix-eventd *.o

#mib2c:
#	MIBDIRS=+../mibs MIBS=+XIX-MIB:XIX-EVENT-MIB mib2c -f xix-event -c mib2c.notify.conf xixEventMib
