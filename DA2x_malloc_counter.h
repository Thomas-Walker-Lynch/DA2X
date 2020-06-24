#ifndef DA2x_Malloc_Counter_H
#define DA2x_Malloc_Counter_H

static size_t DA2x_malloc_cnt = 0;
#define malloc(size) (DA2x_malloc_cnt++ ,malloc(size))
#define free(pt) (DA2x_malloc_cnt-- ,free(pt))

#endif
