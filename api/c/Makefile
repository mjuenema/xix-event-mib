

NAME := xixeventlib


all: $(NAME).so


$(NAME).so: $(NAME).o
	$(CC) `net-snmp-config --libs` -shared -o $@ $<


$(NAME).o: $(NAME).c
	$(CC) `net-snmp-config --cflags` -c -Wall -Werror -fPIC -o $@ $<


clean:
	rm -fv *.so 
	rm -fv *.o 
