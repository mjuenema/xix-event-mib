

NAME := xixeventlib
LANG := perl


all: $(NAME).so


$(NAME).so: $(NAME).o ../$(NAME).i $(NAME).i
	swig -$(LANG) -outcurrentdir $(NAME).i
	$(CC) -I../c/ -O2 -fPIC -c -o $(NAME)_wrap.o $(NAME)_wrap.c `perl -MExtUtils::Embed -e ccopts`
	$(CC) `net-snmp-config --libs` `perl -MExtUtils::Embed -e ldopts` -shared $(NAME).o $(NAME)_wrap.o -o $@


$(NAME).o: ../c/$(NAME).c ../c/$(NAME).h
	$(CC) -I../c/ `perl -MExtUtils::Embed -e ccopts` `net-snmp-config --cflags` -c -Wall -Werror -fPIC -o $@ ../c/$(NAME).c


clean:
	rm -fv $(NAME).so 
	rm -fv $(NAME).o 
	rm -fv $(NAME).pm
	rm -fv $(NAME)_wrap.c
	rm -fv $(NAME)_wrap.o

