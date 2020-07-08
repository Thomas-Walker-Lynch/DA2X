
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "TM2x_malloc_counter.h"
#include "TM2x.h"
#include "TM2xHd.h"
#include "TM2x_Result.h"

typedef struct {
  uint ref; // reference value
  uint result; // results of applying the function to the list
} TM2xHdTestContext1;

// checks for equivalence between item and reference value, then increments the referece value.
void TM2xHd_f0(void *context ,void *item_pt ,address_t element_byte_n){
  uint item = *(uint *)item_pt;
  TM2xHdTestContext1 *cpt = context; 
  cpt->result = cpt->result && (item == cpt->ref++);
}

TM2x_Result test_0(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t initialized_cnt = TM2x_initialized_cnt;
  bool f[256];
  uint32_t i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);
  TM2x *a0;
  continue_into TM2x_alloc_heap_format(&a0 ,0 ,byte_n_of(uint32_t) ,&&nominal_0 ,&&fail_0);
    nominal_0:;
      f[i] = true;
      continue_from_local end_0;
    fail_0:;
      f[i] = false;
      continue_from_local end_0;
    end_0:;
      i++;

  // make an array of data
  f[i] = true; // allocation failure flag
  uint32_t j=10;
  TM2x_Write(a0 ,0 ,j);
  while( j < 99 ){
    j++;
    continue_into TM2x_Push_Write(a0 ,j ,&&nominal_1 ,&&fail_1);    
    fail_1:;
      f[i] = false;
    nominal_1:;
      ;
  }
  i++;
  
  TM2xHdTestContext1 c_instance, *c; c = &c_instance;
  c->ref = 10;
  c->result = true;
  TM2xHd_AllocStaticRewind(a0 ,hd);
  TM2xHd_apply_to_each(a0 ,hd ,byte_n_of(uint32_t) ,c ,TM2xHd_f0);
  f[i++] = c->result;
  f[i++] = c->ref == 100;

  TM2x_dealloc_heap(a0);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = initialized_cnt == TM2x_initialized_cnt;
  TM2x_Result_tally("test_0" ,rp ,f ,i);
  return r;
}

continuation TM2xHd_p0
( void *context 
  ,void *item_pt 
  ,address_t element_byte_n 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item >= 100 && item < 356 )
    continue_from pred_true;
  else 
    continue_from pred_false;
}
continuation TM2xHd_p1
( void *context 
  ,void *item_pt 
  ,address_t element_byte_n 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item >= 100 && item < 355 )
    continue_from pred_true;
  else 
    continue_from pred_false;
}
continuation TM2xHd_p2
( void *context 
  ,void *item_pt 
  ,address_t element_byte_n 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item == 248 )
    continue_from pred_true;
  else 
    continue_from pred_false;
}
continuation TM2xHd_p3
( void *context 
  ,void *item_pt 
  ,address_t element_byte_n 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item == 355 )
    continue_from pred_true;
  else 
    continue_from pred_false;
}
continuation TM2xHd_p4
( void *context 
  ,void *item_pt 
  ,address_t element_byte_n 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item == 356 )
    continue_from pred_true;
  else 
    continue_from pred_false;
}

TM2x_Result test_1(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t initialized_cnt = TM2x_initialized_cnt;
  bool f[256];
  uint32_t i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);
  TM2x *a0;
  continue_into TM2x_alloc_heap_format(&a0 ,0 ,byte_n_of(uint32_t) ,&&nominal_0 ,&&fail_0);
    nominal_0:;
      f[i] = true;
      continue_from_local end_0;
    fail_0:;
      f[i] = false;
      continue_from_local end_0;
    end_0:;
      i++;

  // make an array of data
  f[i] = true; // allocation failure flag
  uint32_t j=100;
  TM2x_Write(a0 ,0 ,j);
  while( j < 355){
    j++;
    continue_into TM2x_Push_Write(a0 ,j ,&&nominal_1 ,&&fail_1);    
    fail_1:;
      f[i] = false;
    nominal_1:;
  }

  TM2xHd_AllocStaticRewind(a0 ,hd);
  continue_into TM2xHd_all(a0 ,hd ,byte_n_of(uint32_t) ,NULL ,TM2xHd_p0 ,&&true_for_all_1 ,&&an_exception_1);
    true_for_all_1:;
      f[i] = true;
      continue_from_local end_1;
    an_exception_1:;
      f[i] = false;
      continue_from_local end_1;
    end_1:;
      i++;

  TM2xHd_rewind(a0 ,hd);
  continue_into TM2xHd_all(a0 ,hd ,byte_n_of(uint32_t) ,NULL ,TM2xHd_p1 ,&&true_for_all_2 ,&&an_exception_2);
    true_for_all_2:;
      f[i] = false;
      continue_from_local end_2;
    an_exception_2:;
// test hd to have the correct value
      f[i] = true;
      continue_from_local end_2;
    end_2:;
      i++;

  TM2xHd_rewind(a0 ,hd);
  continue_into TM2xHd_exists(a0 ,hd ,byte_n_of(uint32_t) ,NULL ,TM2xHd_p3 ,&&found_3 ,&&not_found_3);
    found_3:;
// need to test that the right thing was found
      f[i] = true;
      continue_from_local end_3;
    not_found_3:;
      f[i] = false;
      continue_from_local end_3;
    end_3:;
      i++;

  TM2xHd_rewind(a0 ,hd);
  continue_into TM2xHd_exists(a0 ,hd ,byte_n_of(uint32_t) ,NULL ,TM2xHd_p4 ,&&found_4 ,&&not_found_4);
    found_4:;
      f[i] = false;
      continue_from_local end_4;
    not_found_4:;
      f[i] = true;
      continue_from_local end_4;
    end_4:;
      i++;

  TM2xHd_AllocStaticRewind(a0 ,hd1);
  continue_into TM2xHd_exists(a0 ,hd1 ,byte_n_of(uint32_t) ,NULL ,TM2xHd_p2 ,&&found_5 ,&&not_found_5);
    found_5:;
      uint t0 = TM2xHd_Read_Expr(hd1 ,uint32_t);
      continue_into TM2xHd_is_on_tape(a0 ,hd1 ,&&on_tape_51 ,&&not_on_tape_51);
        on_tape_51:;
          f[i] = t0 == 248;    
          continue_from_local end_5;
        not_on_tape_51:;
          f[i] = false;    
          continue_from_local end_5;
    not_found_5:;
      f[i] = false;
      continue_from_local end_5;
    end_5:;
      i++;
  
  TM2x_dealloc_heap(a0);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = initialized_cnt == TM2x_initialized_cnt;
  TM2x_Result_tally("test_1" ,rp ,f ,i);
  return r;
}
#if 0

TM2x_Result test_2(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t initialized_cnt = TM2x_initialized_cnt;
  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);
  bool f[7];
  uint32_t i = 0;

  TM2x *a0;
  f[i++] = TM2x_alloc_heap_format(&a0 ,0 ,byte_n_of(uint32_t));

  uint j=100;
  TM2x_Write(a0 ,0 ,j);
  while(j < 110){
    ++j;
    TM2x_Push_Write(a0 ,j);    
  }

  // prints: 
  TM2xHd_AllocStaticRewind(a0 ,hd);
  TM2xHd_apply_to_each(a0 ,hd ,byte_n_of(uint32_t) ," " ,TM2xHd_f_print_int);
  fputc('\n' ,stderr);

  TM2x_dealloc_heap(a0);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = initialized_cnt == TM2x_initialized_cnt;
  TM2x_Result_tally("test_2" ,rp ,f ,i);
  return r;
}

TM2x_Result test_3(){
  address_t malloc_cnt = TM2x_malloc_cnt;
  address_t initialized_cnt = TM2x_initialized_cnt;
  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);
  bool f[7];
  uint32_t i = 0;

  uint j=0;
  TM2x_AllocStaticFormat_Write(a0 ,j);
  while(j < 30){
    j+=3;
    TM2x_Push_Write(a0 ,j);    
  }

  fprintf(stderr, "a0:");
  TM2xHd_AllocStaticRewind(a0 ,hd);
  TM2xHd_apply_to_each(a0 ,hd ,byte_n_of(uint) ," " ,TM2xHd_f_print_int);
  fputc('\n' ,stderr);

  j=50;
  TM2x_AllocStaticFormat_Write(a1 ,j);
  while(j > 10){
    j-=5;
    TM2x_Push_Write(a1 ,j);    
  }

  fprintf(stderr, "a1:");
  TM2xHd_rewind(a1 ,hd);
  TM2xHd_apply_to_each(a1 ,hd ,byte_n_of(uint) ," " ,TM2xHd_f_print_int);
  fputc('\n' ,stderr);

  j=30;
  TM2x_AllocStaticFormat_Write(a2 ,j);
  j=57;
  TM2x_Push_Write(a2 ,j);
  j=15;
  TM2x_Push_Write(a2 ,j);    
  j=59;
  TM2x_Push_Write(a2 ,j);    
  j=15;
  TM2x_Push_Write(a2 ,j);    

  fprintf(stderr, "a2:");
  TM2xHd_rewind(a2 ,hd);
  TM2xHd_apply_to_each(a2 ,hd ,byte_n_of(uint) ," " ,TM2xHd_f_print_int);
  fputc('\n' ,stderr);

  TM2x_AllocStatic(a3);
  TM2xHd_init_intersection(a3 ,a0 ,a1 ,byte_n_of(uint) ,TM2xHd_pred_bytes_eq);
  fprintf(stderr, "a3 = intersection a1 a0: ");
  TM2xHd_rewind(a3 ,hd);
  TM2xHd_apply_to_each(a3 ,hd ,byte_n_of(uint) ," " ,TM2xHd_f_print_int);
  fputc('\n' ,stderr);

  TM2xHd_accumulate_union(a3 ,a2 ,byte_n_of(uint) ,TM2xHd_pred_bytes_eq);

  fprintf(stderr, "a3 union a2: ");
  TM2xHd_rewind(a3 ,hd);
  TM2xHd_apply_to_each(a3 ,hd ,byte_n_of(uint) ," " ,TM2xHd_f_print_int);
  fputc('\n' ,stderr);

  TM2x_dealloc_static(a0);
  TM2x_dealloc_static(a1);
  TM2x_dealloc_static(a2);
  TM2x_dealloc_static(a3);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = initialized_cnt == TM2x_initialized_cnt;
  TM2x_Result_tally("test_3" ,rp ,f ,i);
  return r;
}
#endif

int main(){
  TM2x_Result r ,acc ,*accp; accp=&acc;
  TM2x_Result_init(accp);

  r = test_0(); TM2x_Result_accumulate(accp ,&r);
  r = test_1(); TM2x_Result_accumulate(accp ,&r);
  /*
  r = test_2(); TM2x_Result_accumulate(accp ,&r);
  r = test_3(); TM2x_Result_accumulate(accp ,&r);
  */
  TM2x_Result_print("TM2xHd_test results" ,accp);
  return acc.failed;
}
