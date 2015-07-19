

NAME := xixeventlib
LANG := php


all: $(NAME).so


$(NAME).so: $(NAME).o ../$(NAME).i $(NAME).i
	swig -$(LANG) -outcurrentdir $(NAME).i
	$(CC) -I../c/ -O2 -fPIC -c -o $(NAME)_wrap.o $(NAME)_wrap.c `$(LANG)-config --includes`
	$(CC) `net-snmp-config --libs` -shared $(NAME).o $(NAME)_wrap.o -o $(NAME).so


$(NAME).o: ../c/$(NAME).c ../c/$(NAME).h
	$(CC) -I../c/ `net-snmp-config --cflags` -c -Wall -Werror -fPIC -o $(NAME).o ../c/$(NAME).c


clean:
	rm -fv $(NAME).so 
	rm -fv $(NAME).o 
	rm -fv $(NAME).php
	rm -fv $(NAME)_wrap.c
	rm -fv $(NAME)_wrap.o

