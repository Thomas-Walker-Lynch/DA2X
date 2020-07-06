
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
  bool f[5];
  uint i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);

  TM2x_AllocStaticFormat(a0p ,0 ,int32_t ,&&nominal ,&&fail);
    nominal:
      f[i] = true;  
      goto end;
    fail:
      f[i] = false;
    end:
      i++;

  int32_t j = -5;
  int32_t k;

  f[i++] = TM2x_byte_n(a0p) == 3;
  TM2x_Write(a0p ,0 ,j);
  TM2x_Read(a0p ,0 ,k);
  f[i++] = k == -5;

  TM2x_dealloc_static(a0p);
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

  bool f[19];
  uint i = 0;

  TM2x a0,*a0p; a0p = &a0;
  goto *TM2x_format(a0p ,1 ,byte_n_of(int32_t) ,&&format_nominal ,&&format_alloc_fail);
    format_alloc_fail:
      f[i] = false;
      goto format_end;
    format_nominal:
      f[i] = true;
    format_end:
      i++;

  f[i++] = a0p->byte_n == 7;
  TM2x_Push_Alloc(a0p ,1 ,int32_t ,&&push_alloc_nominal ,&&push_alloc_fail);
    push_alloc_fail:
      f[i] = false;
      goto push_alloc_end;
    push_alloc_nominal:
      f[i] = true;
    push_alloc_end:
      i++;

  f[i++] = a0p->byte_n == 15;

  // push 1 ,2 ,3 ,4
  //
    int32_t x;
    x = 1; TM2x_Write(a0p ,0 ,x);
    x = 2; TM2x_Write(a0p ,1 ,x);
    x = 3; TM2x_Write(a0p ,2 ,x);
    x = 4; TM2x_Write(a0p ,3 ,x);

  // pop 4 ,3 ,2 ,1
  //
    int32_t y;
    f[i++] = a0p->byte_n == 15;

    TM2x_Read_Pop(a0p ,y ,&&read_pop_nominal_0 ,&&read_pop_pop_last_0);
      read_pop_pop_last_0:
        f[i] = false;
        goto read_pop_end_0;
      read_pop_nominal_0:
        f[i] = true;
      read_pop_end_0:
        i++;
    f[i++] = y == 4;

    TM2x_Read_Pop(a0p ,y ,&&read_pop_nominal_1 ,&&read_pop_pop_last_1);
      read_pop_pop_last_1:
        f[i] = false;
        goto read_pop_end_1;
      read_pop_nominal_1:
        f[i] = true;
      read_pop_end_1:
        i++;
    f[i++] = y == 3;

    TM2x_Read_Pop(a0p ,y ,&&read_pop_nominal_2 ,&&read_pop_pop_last_2);
      read_pop_pop_last_2:
        f[i] = false;
        goto read_pop_end_2;
      read_pop_nominal_2:
        f[i] = true;
      read_pop_end_2:
        i++;
    f[i++] = y == 2;

    TM2x_Read_Pop(a0p ,y ,&&read_pop_nominal_3 ,&&read_pop_pop_last_3);
      read_pop_pop_last_3:
        f[i] = true;
        goto read_pop_end_3;
      read_pop_nominal_3:
        f[i] = false;
      read_pop_end_3:
        i++;
    f[i++] = y == 1;

    f[i++] = a0p->byte_n == 3;

  TM2x_dealloc_static(a0p);
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

  TM2x_AllocStaticFormat(a0 ,0 ,int32_t ,&&nominal ,&&fail);
    nominal:
      f[i] = true;  
      goto end;
    fail:
      f[i] = false;
    end:
      i++;
  f[i++] = a0->byte_n == 3;

  int32_t x=1; 
  TM2x_Write(a0 ,0 ,x); 

  ++x;
  TM2x_Push_Write(a0 ,x ,&&push_write_nominal_0 ,&&push_write_allocation_failed_0);
    push_write_allocation_failed_0:
      f[i] = false;
      goto push_write_end_0;
    push_write_nominal_0:
      f[i] = true;
    push_write_end_0:
      i++;
  f[i++] = TM2x_test_after_allocation_n == 7;

  ++x; 
  TM2x_Push_Write(a0 ,x ,&&push_write_nominal_1 ,&&push_write_allocation_failed_1);
    push_write_allocation_failed_1:
      f[i] = false;
      goto push_write_end_1;
    push_write_nominal_1:
      f[i] = true;
    push_write_end_1:
      i++;
  f[i++] = TM2x_test_after_allocation_n == 15;

  ++x; 
  TM2x_Push_Write(a0 ,x ,&&push_write_nominal_2 ,&&push_write_allocation_failed_2);
    push_write_allocation_failed_2:
      f[i] = false;
      goto push_write_end_2;
    push_write_nominal_2:
      f[i] = true;
    push_write_end_2:
      i++;
  f[i++] = TM2x_test_after_allocation_n == 15;

  ++x; 
  TM2x_Push_Write(a0 ,x ,&&push_write_nominal_3 ,&&push_write_allocation_failed_3);
    push_write_allocation_failed_3:
      f[i] = false;
      goto push_write_end_3;
    push_write_nominal_3:
      f[i] = true;
    push_write_end_3:
      i++;
  f[i++] = TM2x_test_after_allocation_n == 31;

  int32_t y=111222;
    TM2x_Read_Pop(a0 ,y ,&&read_pop_nominal_0 ,&&read_pop_pop_last_0);
      read_pop_pop_last_0:
        f[i] = false;
        goto read_pop_end_0;
      read_pop_nominal_0:
        f[i] = true;
      read_pop_end_0:
        i++;
  f[i++] = y == 5;
  f[i++] = TM2x_test_after_allocation_n == 15;
  
    TM2x_Read_Pop(a0 ,y ,&&read_pop_nominal_1 ,&&read_pop_pop_last_1);
      read_pop_pop_last_1:
        f[i] = false;
        goto read_pop_end_1;
      read_pop_nominal_1:
        f[i] = true;
      read_pop_end_1:
        i++;
  f[i++] = y == 4;
  f[i++] = TM2x_test_after_allocation_n == 15;
  
    TM2x_Read_Pop(a0 ,y ,&&read_pop_nominal_2 ,&&read_pop_pop_last_2);
      read_pop_pop_last_2:
        f[i] = false;
        goto read_pop_end_2;
      read_pop_nominal_2:
        f[i] = true;
      read_pop_end_2:
        i++;
  f[i++] = y == 3;
  f[i++] = TM2x_test_after_allocation_n == 7;
  
    TM2x_Read_Pop(a0 ,y ,&&read_pop_nominal_3 ,&&read_pop_pop_last_3);
      read_pop_pop_last_3:
        f[i] = false;
        goto read_pop_end_3;
      read_pop_nominal_3:
        f[i] = true;
      read_pop_end_3:
        i++;
  f[i++] = y == 2;
  f[i++] = TM2x_test_after_allocation_n == 3;
  
    TM2x_Read_Pop(a0 ,y ,&&read_pop_nominal_4 ,&&read_pop_pop_last_4);
      read_pop_pop_last_4:
        f[i] = true;
        goto read_pop_end_4;
      read_pop_nominal_4:
        f[i] = false;
      read_pop_end_4:
        i++;
  f[i++] = y == 1;  
  f[i++] = TM2x_test_after_allocation_n == 3;

  TM2x_dealloc_static(a0);
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
