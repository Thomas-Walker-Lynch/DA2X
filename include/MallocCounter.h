#ifndef MallocCounter_H
#define MallocCounter_H

static size_t MallocCounter·count = 0;
#define malloc(size) (MallocCounter·count++ ,malloc(size))
#define free(pt) (MallocCounter·count-- ,free(pt))

#endif
