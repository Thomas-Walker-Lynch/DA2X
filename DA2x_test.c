
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "DA2x_malloc_counter.h"
#include "DA2x.h"
#include "DA2x_Result.h"

DA2x_Result test_0(){
  size_t malloc_cnt = DA2x_malloc_cnt;
  size_t outstanding_cnt = DA2x_outstanding_cnt;
  bool f[6];
  uint i = 0;

  DA2x_Result r ,*rp; rp = &r;
  DA2x_Result_init(rp);

  DA2x a0 ,*a0p; a0p=&a0;
  DA2x_init(a0p ,sizeof(int));

  f[i++] = DA2x_element_size(a0p) == sizeof(int);
  f[i++] = DA2x_size(a0p) == 0;
  f[i++] = DA2x_empty(a0p);
  f[i++] = DA2x_allocation_size(a0p) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH;

  DA2x_data_dealloc(a0p);
  f[i++] = malloc_cnt == DA2x_malloc_cnt;
  f[i++] = outstanding_cnt == DA2x_outstanding_cnt;
  DA2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) DA2x_Result_print(&r ,"test_0 ");
  return r;
}

DA2x_Result test_1(){
  size_t malloc_cnt = DA2x_malloc_cnt;
  size_t outstanding_cnt = DA2x_outstanding_cnt;
  DA2x_Result r ,*rp; rp = &r;
  DA2x_Result_init(rp);

  bool f[11];
  uint i = 0;

  DA2x a0 ,*a0p; a0p=&a0;
  DA2x_init(a0p ,sizeof(int));

  // push 1 ,2 ,3 ,4
  //
    int *pt = (int *)DA2x_push_alloc(a0p ,1);
    *pt = 1;

    pt = (int *)DA2x_push_alloc(a0p ,1);
    *pt = 2;

    int x = 3;
    DA2x_push_write(a0p ,&x);

    x = 4;
    DA2x_push_write(a0p ,&x);

  // pop 4 ,3 ,2 ,1
  //
    int y;
    f[i++] = DA2x_pop_read(a0p ,&y) && y == 4;
    f[i++] = DA2x_pop_read(a0p ,&y) && y == 3; 
    f[i++] = DA2x_pop_read(a0p ,&y) && y == 2; // after this pop the data length will be 1, so the array contracts
    f[i++] = DA2x_allocation_size(a0p) == sizeof(int) * 4;  // array will not contract below minimum size
    f[i++] = DA2x_pop_read(a0p ,&y) && y == 1; // after this pop, the data length will halve again
    f[i++] = DA2x_allocation_size(a0p) == sizeof(int) * 4;

  // the array is now empty
  //
    f[i++] = DA2x_element_size(a0p) == sizeof(int);
    f[i++] = DA2x_size(a0p) == 0;
    f[i++] = DA2x_empty(a0p);

  DA2x_data_dealloc(a0p);
  f[i++] =  malloc_cnt == DA2x_malloc_cnt;
  f[i++] = outstanding_cnt == DA2x_outstanding_cnt;
  DA2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) DA2x_Result_print(&r ,"test_1 ");
  return r;
}

DA2x_Result test_2(){
  size_t malloc_cnt = DA2x_malloc_cnt;
  size_t outstanding_cnt = DA2x_outstanding_cnt;
  bool f[18];
  uint i = 0;

  DA2x_Result r ,*rp; rp = &r;
  DA2x_Result_init(rp);

  DA2x_Make(a0 ,int);

  f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH;
  f[i++] = DA2x_empty(a0);

  // fill the initial allocation
  //
    int x = 7;
    DA2x_push_write(a0 ,&x);
    DA2x_push_write(a0 ,&x);
    DA2x_push_write(a0 ,&x);
    DA2x_push_write(a0 ,&x);
    f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH;
    f[i++] = !DA2x_empty(a0);

  // one more, the array should double
  //
    DA2x_push_write(a0 ,&x);
    f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH * 2;
    f[i++] = !DA2x_empty(a0);

  // fill the doubled array
  //
    DA2x_push_write(a0 ,&x);
    DA2x_push_write(a0 ,&x);
    DA2x_push_write(a0 ,&x);
    f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH * 2;
    f[i++] = !DA2x_empty(a0);

  // one more
  //    9 integers on the array,  allocation for 16 integers
  //
    DA2x_push_write(a0 ,&x);
    f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH * 4;
    f[i++] = !DA2x_empty(a0);


  // bring it back to 4 integers of data, and the array size should drop to 8
  //      
    DA2x_pop(a0);
    DA2x_pop(a0);
    DA2x_pop(a0);
    DA2x_pop(a0);
    f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH * 4;
    DA2x_pop(a0);
    f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH * 2;

  // empty the array is now empty
  //
    DA2x_pop(a0);
    DA2x_pop(a0);
    DA2x_pop(a0);
    DA2x_pop(a0);
    f[i++] = DA2x_allocation_size(a0) == sizeof(int) * DA2x_INITIAL_ALLOCATION_LENGTH;

  // the array is now empty
  //
    f[i++] = DA2x_element_size(a0) == sizeof(int);
    f[i++] = DA2x_size(a0) == 0;
    f[i++] = DA2x_empty(a0);

  DA2x_data_dealloc(a0);
  f[i++] = malloc_cnt == DA2x_malloc_cnt;
  f[i++] = outstanding_cnt == DA2x_outstanding_cnt;
  // printf("test_2 'i': %u" ,i);
  DA2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) DA2x_Result_print(&r ,"test_2 ");
  return r;
}

int main(){
  DA2x_Result r ,acc ,*accp; accp=&acc;
  DA2x_Result_init(accp);

  r = test_0(); DA2x_Result_accumulate(accp ,&r);
  r = test_1(); DA2x_Result_accumulate(accp ,&r);
  r = test_2(); DA2x_Result_accumulate(accp ,&r);

  DA2x_Result_print(accp ,"DA2x_test results: ");
  return acc.failed;
}
