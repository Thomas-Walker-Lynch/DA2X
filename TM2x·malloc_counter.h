#ifndef TM2x·Malloc_Counter_H
#define TM2x·Malloc_Counter_H

static size_t TM2x·malloc_cnt = 0;
#define malloc(size) (TM2x·malloc_cnt++ ,malloc(size))
#define free(pt) (TM2x·malloc_cnt-- ,free(pt))

#endif
