

CC= gcc
CFLAGS= -Wall -g
TARGETS= libTM2x.a TM2x_test TM2xHd_test
INSTALL= libTM2x.a TM2x.h TM2xHd.h

.PHONY: all
all: $(TARGETS)

TM2x.o: TM2x.c
	$(CC) -c TM2x.c

libTM2x.a: TM2x.o
	ar rcs libTM2x.a TM2x.o

TM2x_test: TM2x_test.c TM2x.o TM2x.h TM2x_malloc_counter.h TM2x_Result.h
	$(CC) $(CFLAGS) -o TM2x_test TM2x.o TM2x_test.c 

TM2xHd_test: TM2x.o TM2xHd_test.c TM2xHd.h TM2x.h TM2x_malloc_counter.h  TM2x_Result.h
	$(CC) $(CFLAGS) -o TM2xHd_test TM2x.o TM2xHd_test.c

.PHONY: test
test: TM2x_test TM2xHd_test
	./TM2x_test && ./TM2xHd_test

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o

.PHONY: share
share: $(INSTALL)
	cp libTM2x.a ../env/lib
	cp TM2x.h ../env/include 
	cp TM2xHd.h ../env/include 




