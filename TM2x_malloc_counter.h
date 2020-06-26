#ifndef TM2x_Malloc_Counter_H
#define TM2x_Malloc_Counter_H

static size_t TM2x_malloc_cnt = 0;
#define malloc(size) (TM2x_malloc_cnt++ ,malloc(size))
#define free(pt) (TM2x_malloc_cnt-- ,free(pt))

#endif
