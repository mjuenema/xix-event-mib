

all: api

.PHONY: api clean

api:
	make -C api all

clean:
	make -C api clean




