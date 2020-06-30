
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "TM2x_malloc_counter.h"
#include "TM2x.h"
#include "TM2x_Result.h"

TM2x_Result test_0(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t outstanding_cnt = TM2x_outstanding_cnt;
  bool f[6];
  uint i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);

  TM2x_Make(a0p ,0 ,int32_t);
  int32_t j = -5;
  int32_t k;

  f[i++] = TM2x_byte_n(a0p) == 3;
  f[i++] = TM2x_Write(a0p ,0 ,j);
  f[i++] = TM2x_Read(a0p ,0 ,k);
  f[i++] = k == -5;

  TM2x_data_dealloc(a0p);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = outstanding_cnt == TM2x_outstanding_cnt;
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_0 ");
  return r;
}
#if 0
TM2x_Result test_1(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t outstanding_cnt = TM2x_outstanding_cnt;
  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);

  bool f[11];
  uint i = 0;

  TM2x_Make(a0p ,0 ,int32_t);

  // push 1 ,2 ,3 ,4
  //
    int *pt = (int *)TM2x_push_alloc(a0p ,1);
    *pt = 1;

    pt = (int *)TM2x_push_alloc(a0p ,1);
    *pt = 2;

    int x = 3;
    TM2x_push_write(a0p ,&x);

    x = 4;
    TM2x_push_write(a0p ,&x);

  // pop 4 ,3 ,2 ,1
  //
    int y;
    f[i++] = TM2x_pop_read(a0p ,&y) && y == 4;
    f[i++] = TM2x_pop_read(a0p ,&y) && y == 3; 
    f[i++] = TM2x_pop_read(a0p ,&y) && y == 2; // after this pop the data n will be 1, so the array contracts
    f[i++] = TM2x_allocation_byte_n(a0p) == byte_n_of(int) * 4;  // array will not contract below minimum byte_n
    f[i++] = TM2x_pop_read(a0p ,&y) && y == 1; // after this pop, the data n will halve again
    f[i++] = TM2x_allocation_byte_n(a0p) == byte_n_of(int) * 4;

  // the array is now empty
  //
    f[i++] = TM2x_element_byte_n(a0p) == byte_n_of(int);
    f[i++] = TM2x_byte_n(a0p) == 0;
    f[i++] = TM2x_empty(a0p);

  TM2x_data_dealloc(a0p);
  f[i++] =  malloc_cnt == TM2x_malloc_cnt;
  f[i++] = outstanding_cnt == TM2x_outstanding_cnt;
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_1 ");
  return r;
}

TM2x_Result test_2(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t outstanding_cnt = TM2x_outstanding_cnt;
  bool f[18];
  uint i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);

  TM2x_Make(a0 ,int);

  f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N;
  f[i++] = TM2x_empty(a0);

  // fill the initial allocation
  //
    int x = 7;
    TM2x_push_write(a0 ,&x);
    TM2x_push_write(a0 ,&x);
    TM2x_push_write(a0 ,&x);
    TM2x_push_write(a0 ,&x);
    f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N;
    f[i++] = !TM2x_empty(a0);

  // one more, the array should double
  //
    TM2x_push_write(a0 ,&x);
    f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N * 2;
    f[i++] = !TM2x_empty(a0);

  // fill the doubled array
  //
    TM2x_push_write(a0 ,&x);
    TM2x_push_write(a0 ,&x);
    TM2x_push_write(a0 ,&x);
    f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N * 2;
    f[i++] = !TM2x_empty(a0);

  // one more
  //    9 integers on the array,  allocation for 16 integers
  //
    TM2x_push_write(a0 ,&x);
    f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N * 4;
    f[i++] = !TM2x_empty(a0);


  // bring it back to 4 integers of data, and the array byte_n should drop to 8
  //      
    TM2x_pop(a0);
    TM2x_pop(a0);
    TM2x_pop(a0);
    TM2x_pop(a0);
    f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N * 4;
    TM2x_pop(a0);
    f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N * 2;

  // empty the array is now empty
  //
    TM2x_pop(a0);
    TM2x_pop(a0);
    TM2x_pop(a0);
    TM2x_pop(a0);
    f[i++] = TM2x_allocation_byte_n(a0) == byte_n_of(int) * TM2x_INITIAL_ALLOCATION_ELEMENT_N;

  // the array is now empty
  //
    f[i++] = TM2x_element_byte_n(a0) == byte_n_of(int);
    f[i++] = TM2x_byte_n(a0) == 0;
    f[i++] = TM2x_empty(a0);

  TM2x_data_dealloc(a0);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = outstanding_cnt == TM2x_outstanding_cnt;
  // printf("test_2 'i': %u" ,i);
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_2 ");
  return r;
}
#endif 

int main(){
  TM2x_Result r ,acc ,*accp; accp=&acc;
  TM2x_Result_init(accp);

  r = test_0(); TM2x_Result_accumulate(accp ,&r);
  //  r = test_1(); TM2x_Result_accumulate(accp ,&r);
  //  r = test_2(); TM2x_Result_accumulate(accp ,&r);

  TM2x_Result_print(accp ,"TM2x_test results: ");
  return acc.failed;
}
