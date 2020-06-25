

CC= gcc
CFLAGS= -Wall -g
TARGETS= DA2x.o DA2x_test DA2xIt_test

.PHONY: all
all: $(TARGETS)

DA2x.o: DA2x.c
	$(CC) -c DA2x.c

DA2x_test: DA2x_test.c DA2x.o DA2x.h DA2x_malloc_counter.h
	$(CC) $(CFLAGS) -o DA2x_test DA2x.o DA2x_test.c 

DA2xIt_test: DA2xIt_test.c DA2xIt.h DA2x_malloc_counter.h
	$(CC) $(CFLAGS) -o DA2xIt_test DA2x.o DA2xIt_test.c

.PHONY: test
test: DA2x_test DA2xIt_test
	./DA2x_test && ./DA2xIt_test

.PHONY: clean
clean:
	rm -f $(TARGETS)






