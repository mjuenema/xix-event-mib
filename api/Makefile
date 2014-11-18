

NAME := xixeventlib


all: c

.PHONY: c
c:
	make -C c/ all


$(NAME).so: $(NAME).o
	$(CC) `net-snmp-config --libs` -shared -o $@ $<


$(NAME).o: $(NAME).c
	$(CC) `net-snmp-config --cflags` -c -Wall -Werror -fPIC -o $@ $<


_$(NAME).so: $(NAME).o $(NAME).i 
	swig -python $(NAME).i
	$(CC) -O2 -fPIC -c -o $(NAME)_wrap.o $(NAME)_wrap.c `python-config --cflags`
	$(CC) -shared $(NAME).o $(NAME)_wrap.o -o _$(NAME).so

clean:
	rm -fv *.so 
	rm -fv *.o 
	rm -fv *.py  
	rm -fv *_wrap.c

