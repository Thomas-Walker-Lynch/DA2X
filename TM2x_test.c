
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define TM2x_TEST
#include "TM2x_malloc_counter.h"
#include "TM2x.h"
#include "TM2x_Result.h"

address_t TM2x_test_after_allocation_n = 0;

TM2x_Result test_0(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t initialized_cnt = TM2x_initialized_cnt;
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
  f[i++] = initialized_cnt == TM2x_initialized_cnt;
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_0 ");
  return r;
}

TM2x_Result test_1(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t initialized_cnt = TM2x_initialized_cnt;
  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);

  bool f[15];
  uint i = 0;

  TM2x a0,*a0p; a0p = &a0;
  f[i++] = TM2x_init(a0p ,1 ,byte_n_of(int32_t));
  f[i++] = a0p->byte_n == 7;
  f[i++] = TM2x_Push_Alloc(a0p ,1 ,int32_t);
  f[i++] = a0p->byte_n == 15;

  // push 1 ,2 ,3 ,4
  //
    int32_t x;
    x = 1;
    f[i++] = TM2x_Write(a0p ,0 ,x);
    x = 2;
    f[i++] = TM2x_Write(a0p ,1 ,x);
    x = 3;
    f[i++] = TM2x_Write(a0p ,2 ,x);
    x = 4;
    f[i++] = TM2x_Write(a0p ,3 ,x);

  // pop 4 ,3 ,2 ,1
  //
    int32_t y;
    f[i++] = a0p->byte_n == 15;
    f[i++] = TM2x_Pop_Read(a0p ,y) && y == 4;
    f[i++] = TM2x_Pop_Read(a0p ,y) && y == 3;
    f[i++] = TM2x_Pop_Read(a0p ,y) && y == 2;
    f[i++] = !TM2x_Pop_Read(a0p ,y) && y == 1;
    f[i++] = a0p->byte_n == 3;

  TM2x_data_dealloc(a0p);
  f[i++] =  malloc_cnt == TM2x_malloc_cnt;
  f[i++] = initialized_cnt == TM2x_initialized_cnt;
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_1 ");
  return r;
}

TM2x_Result test_2(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t initialized_cnt = TM2x_initialized_cnt;
  bool f[256];
  uint i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);

  TM2x_Make(a0 ,0 ,int32_t);
  f[i++] = a0->byte_n == 3;

  int32_t x=1; f[i++] = TM2x_Write(a0 ,0 ,x); 

  ++x; f[i++] = TM2x_Push_Write(a0 ,x);
  f[i++] = TM2x_test_after_allocation_n == 7;

  ++x; f[i++] = TM2x_Push_Write(a0 ,x);
  f[i++] = TM2x_test_after_allocation_n == 15;

  ++x; f[i++] = TM2x_Push_Write(a0 ,x);
  f[i++] = TM2x_test_after_allocation_n == 15;

  ++x; f[i++] = TM2x_Push_Write(a0 ,x);
  f[i++] = TM2x_test_after_allocation_n == 31;

  int32_t y=111222;
  f[i++] = TM2x_Pop_Read(a0 ,y);
  f[i++] = y == 5;
  f[i++] = TM2x_test_after_allocation_n == 15;
  
  f[i++] = TM2x_Pop_Read(a0 ,y);
  f[i++] = y == 4;
  f[i++] = TM2x_test_after_allocation_n == 15;
  
  f[i++] = TM2x_Pop_Read(a0 ,y);
  f[i++] = y == 3;
  f[i++] = TM2x_test_after_allocation_n == 7;
  
  f[i++] = TM2x_Pop_Read(a0 ,y);
  f[i++] = y == 2;
  f[i++] = TM2x_test_after_allocation_n == 3;
  
  f[i++] = !TM2x_Pop_Read(a0 ,y);
  f[i++] = y == 1;  
  f[i++] = TM2x_test_after_allocation_n == 3;

  TM2x_data_dealloc(a0);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = initialized_cnt == TM2x_initialized_cnt;
  // printf("test_2 'i': %u" ,i);
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_2 ");

  return r;
}

int main(){
  TM2x_Result r ,acc ,*accp; accp=&acc;
  TM2x_Result_init(accp);

  r = test_0(); TM2x_Result_accumulate(accp ,&r);
  r = test_1(); TM2x_Result_accumulate(accp ,&r);
  r = test_2(); TM2x_Result_accumulate(accp ,&r);

  TM2x_Result_print(accp ,"TM2x_test results: ");
  return acc.failed;
}
