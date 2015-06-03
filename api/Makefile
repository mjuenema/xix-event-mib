

NAME := xixeventlib


all: c python perl

.PHONY: c python perl

c:
	make -C c/ all

python: c
	make -C python/ all

perl: c
	make -C perl/ all


$(NAME).so: $(NAME).o
	$(CC) `net-snmp-config --libs` -shared -o $@ $<


$(NAME).o: $(NAME).c
	$(CC) `net-snmp-config --cflags` -c -Wall -Werror -fPIC -o $@ $<


_$(NAME).so: $(NAME).o $(NAME).i 
	swig -python $(NAME).i
	$(CC) -O2 -fPIC -c -o $(NAME)_wrap.o $(NAME)_wrap.c `python-config --cflags`
	$(CC) -shared $(NAME).o $(NAME)_wrap.o -o _$(NAME).so

clean:
	make -C c/ clean
	make -C python/ clean
	make -C perl/ clean
	rm -fv *.so 
	rm -fv *.o 
	rm -fv *.py  
	rm -fv *_wrap.c

