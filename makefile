

CC= gcc
CFLAGS= -std=gnu2x -Wall -g
TARGETS= libTM2x.a TM2x·test TM2xHd·test
INSTALL= libTM2x.a TM2x.h TM2xHd.h

#Examples are not built here, but are cleaned.
EXAMPLES= example·trampoline example·nested_functions example·utf8 \
example·nested_labeling_1 example·nested_labeling_2 example·nested_labeling_3

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
	cp *.h ../env/include 



