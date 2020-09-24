

CC= gcc
//CFLAGS= -std=gnu2x -Wall -O3 -DTEST -Wno-unused-label -I../include -L../lib
CFLAGS= -save-temps -std=gnu2x -Wall -O0 -ggdb -DDEBUG -DDEBUGDB -DTEST -Wno-unused-label -I../include -L../lib
LIB= $(wildcard ../lib/*)
INCLUDES= $(wildcard ../include/*.h)
TARGETS= Inclusive·test TM2x·test

.PHONY: all
all: $(TARGETS)

Inclusive·test: Inclusive·test.c  $(INCLUDES)
	$(CC) $(CFLAGS) -o Inclusive·test Inclusive·test.c 

TM2x·test: TM2x·test.c TM2x·test_0.h TM2x·test_1.h $(LIB) $(INCLUDES)
	$(CC) $(CFLAGS) -o TM2x·test TM2x·test.c -lTM2x

#TM2xHd·test: TM2xHd·test.c $(LIB) $(INCLUDES)
#	$(CC) $(CFLAGS) -o TM2xHd·test TM2xHd·test.c -lTM2x

.PHONY: test
test: TM2x·test TM2xHd·test
	./TM2x·test && ./TM2xHd·test

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o *.i *.s



