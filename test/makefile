
CC= gcc
//CFLAGS= -std=gnu2x -Wall -O3 -DTEST -Wno-unused-label -I../include -L../lib
CFLAGS= -save-temps -std=gnu2x -Wall -O0 -ggdb -DDEBUG -DDEBUGDB -DTEST -Wno-unused-label -I../include -L../lib
LIB= $(wildcard ../lib/*)
INCLUDES= $(wildcard ../include/*.h)
TARGETS= Inclusive·test T02x·test

.PHONY: all
all: $(TARGETS)

Inclusive·test: Inclusive·test.c  $(INCLUDES)
	$(CC) $(CFLAGS) -o Inclusive·test Inclusive·test.c 

T02x·test: T02x·test.c $(wildcard T02x·test_*.h) $(INCLUDES) $(LIB)
	$(CC) $(CFLAGS) -o T02x·test T02x·test.c -lTM2x

#TM2xHd·test: build TM2xHd·test.c
#	$(CC) $(CFLAGS) -o TM2xHd·test TM2xHd·test.c -lT02x

.PHONY: test
test: $(wildcard *·test)
	for i in $^; do ./$$i; done

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o *.i *.s



