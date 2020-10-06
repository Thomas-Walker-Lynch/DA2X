

CC= gcc
//CFLAGS= -std=gnu2x -Wall -O3 -DTEST -Wno-unused-label -I../include -L../lib
CFLAGS= -save-temps -std=gnu2x -Wall -O0 -ggdb -DDEBUG -DDEBUGDB -DTEST -Wno-unused-label -I../include -L../lib
LIB= $(wildcard ../lib/*)
INCLUDES= $(wildcard ../include/*.h)
TARGETS= specific_use_sequences

.PHONY: all
all: $(TARGETS)

specific_use_sequences: specific_use_sequences.c $(INCLUDES)
	$(CC) $(CFLAGS) -o $@ $<


.PHONY: clean
clean:
	rm -f $(TARGETS) *.o *.i *.s



