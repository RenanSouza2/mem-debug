FLAGS = -c -Wall -Werror -Wfatal-errors

LIB_ROOT = ..
DIR = $(shell basename $(CURDIR))

build: lib.o

lib.o: code.c
	echo "Building $(DIR) object"
	gcc -o $@ $^ $(FLAGS)

debug.o: code.c
	echo "Building $(DIR) debug"
	gcc -o $@ $^ $(FLAGS) -D DEBUG

clean:
	rm -f *.o
	$(MAKE) clean --directory=test

.PHONY: test
test:
	$(MAKE) --directory=test

export
