

# using gnu extensions:
#  varaible value is a &&label
#  nested functions
#  statement expressions

CC= gcc
CFLAGS= -std=gnu2x -Wall -g
TARGETS= libTM2x.a TM2x·test TM2xHd·test
INSTALL= libTM2x.a TM2x.h TM2xHd.h

#Each example.c file has a comment at the top with the command for building it.  Hence
#examples are not built here.  However, the clean: target will delete the all example
#executables that exist.
EXAMPLES= example·trampoline example·nested_functions example·nested_labeling example·utf8

.PHONY: all
all: $(TARGETS)

TM2x.o: TM2x.c
	$(CC) -c TM2x.c

libTM2x.a: TM2x.o
	ar rcs libTM2x.a TM2x.o

TM2x·test: TM2x·test.c TM2x.o TM2x.h TM2x·malloc_counter.h TM2x·Result.h
	$(CC) $(CFLAGS) -o TM2x·test TM2x.o TM2x·test.c 

TM2xHd·test: TM2x.o TM2xHd·test.c TM2xHd.h TM2x.h TM2x·malloc_counter.h  TM2x·Result.h
	$(CC) $(CFLAGS) -o TM2xHd·test TM2x.o TM2xHd·test.c

.PHONY: test
test: TM2x·test TM2xHd·test
	./TM2x·test && ./TM2xHd·test

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o  $(EXAMPLES)

.PHONY: share
share: $(INSTALL)
	cp libTM2x.a ../env/lib
	cp TM2x.h ../env/include 
	cp TM2xHd.h ../env/include 




