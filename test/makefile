

CC= gcc
CFLAGS= -std=gnu2x -Wall -O0 -ggdb -DDEBUG -DDEBUGDB -I../include -L../lib 
LIB= $(wildcard ../lib/*)
INCLUDES= $(wildcard ../include/*.h)
TARGETS= TM2x·test TM2xHd·test

.PHONY: all
all: $(TARGETS)

TM2x·test: TM2x·test.c $(LIB) $(INCLUDES)
	$(CC) $(CFLAGS) -o TM2x·test TM2x·test.c -lTM2x

TM2xHd·test: TM2xHd·test.c $(LIB) $(INCLUDES)
	$(CC) $(CFLAGS) -o TM2xHd·test TM2xHd·test.c -lTM2x

.PHONY: test
test: TM2x·test TM2xHd·test
	./TM2x·test && ./TM2xHd·test

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o 



