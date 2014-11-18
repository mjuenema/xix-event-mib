

NAME := xixeventlib
LANG := python


all: _$(NAME).so


_$(NAME).so: $(NAME).o ../$(NAME).i $(NAME).i
	swig -$(LANG) -outcurrentdir $(NAME).i
	$(CC) -I../c/ -O2 -fPIC -c -o $(NAME)_wrap.o $(NAME)_wrap.c `$(LANG)-config --cflags`
	$(CC) `net-snmp-config --libs` -shared $(NAME).o $(NAME)_wrap.o -o _$(NAME).so


$(NAME).o: ../c/$(NAME).c ../c/$(NAME).h
	$(CC) -I../c/ `net-snmp-config --cflags` -c -Wall -Werror -fPIC -o $(NAME).o ../c/$(NAME).c


clean:
	rm -fv _$(NAME).so 
	rm -fv $(NAME).o 
	rm -fv $(NAME).py
	rm -fv $(NAME).pyc
	rm -fv $(NAME)_wrap.c
	rm -fv $(NAME)_wrap.o

