

CC= gcc
CFLAGS= -Wall -g

.PHONY: all
all: DA2x_test DA2xIt_test

DA2x_test: DA2x_test.c DA2x.h
	$(CC) $(CFLAGS) -o DA2x_test DA2x_test.c

DA2xIt_test: DA2xIt_test.c DA2xIt.h
	$(CC) $(CFLAGS) -o DA2xIt_test DA2xIt_test.c

.PHONY: clean
clean:
	rm -f DA2x_test DA2xIt_test






