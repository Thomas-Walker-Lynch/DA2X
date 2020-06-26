

CC= gcc
CFLAGS= -Wall -g
TARGETS= libDA2x.a DA2x_test DA2xHd_test

.PHONY: all
all: $(TARGETS)

DA2x.o: DA2x.c
	$(CC) -c DA2x.c

libDA2x.a: DA2x.o
	ar rcs libDA2x.a DA2x.o

DA2x_test: DA2x_test.c DA2x.o DA2x.h DA2x_malloc_counter.h
	$(CC) $(CFLAGS) -o DA2x_test DA2x.o DA2x_test.c 

DA2xHd_test: DA2xHd_test.c DA2xHd.h DA2x_malloc_counter.h
	$(CC) $(CFLAGS) -o DA2xHd_test DA2x.o DA2xHd_test.c

.PHONY: test
test: DA2x_test DA2xHd_test
	./DA2x_test && ./DA2xHd_test

.PHONY: clean
clean:
	rm -f $(TARGETS)






