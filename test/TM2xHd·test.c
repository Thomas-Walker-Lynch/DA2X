
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "MallocCounter.h"
#include "TM2x.h"
#include "Result.h"

typedef struct {
  uint ref; // reference value
  uint result; // results of applying the function to the list
} TM2xHdTestContext1;

// checks for equivalence between item and reference value, then increments the referece value.
void TM2xHd·f0(void *context ,void *item_pt ,address_t element_n_Byte){
  uint item = *(uint *)item_pt;
  TM2xHdTestContext1 *cpt = context; 
  cpt->result = cpt->result && (item == cpt->ref++);
}

Result·Tallies test_0(){
  address_t malloc_cnt = MallocCounter·count;
  address_t constructed_cnt = T02x·alloc_array_count;
  bool f[256];
  uint32_t i = 0;

  Result·Tallies r ,*rp; rp = &r;
  Result·Tallies·init(rp);
  T02x·Root *a0;
  continue_into T02x·alloc_Tape_heap_construct(&a0 ,0 ,n_of(uint32_t) ,&&nominal_0 ,&&fail_0 ,&&fail_0);
  nominal_0:{
    f[i] = true;
    continue_from end_0;
  }
  fail_0:{
    f[i] = false;
    continue_from end_0;
  }
  end_0:{
    i++;
  }

  // make an array of data
  f[i] = true; // allocation failure flag
  uint32_t j=10;
  T02x·Write(a0 ,0 ,j);
  while( j < 99 ){
    j++;
    continue_into T02x·Push(a0 ,j ,&&nominal_1 ,&&fail_1);    
    fail_1:{
      f[i] = false;
    }
    nominal_1:{
      ;
    }
  }
  i++;
  
  TM2xHdTestContext1 c_instance, *c; c = &c_instance;
  c->ref = 10;
  c->result = true;
  TM2xHd·AllocStaticRewind(a0 ,hd);
  TM2xHd·apply_to_each(a0 ,hd ,n_of(uint32_t) ,c ,TM2xHd·f0);
  f[i++] = c->result;
  f[i++] = c->ref == 100;

  T02x·dealloc_Tape_heap(a0);
  f[i++] = malloc_cnt == MallocCounter·count;
  f[i++] = constructed_cnt == T02x·alloc_array_count;
  Result·Tallies·tally("test_0" ,rp ,f ,i);
  return r;
}

continuation TM2xHd·p0
( void *context 
  ,void *item_pt 
  ,address_t element_n_Byte 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item >= 100 && item < 356 )
    continue_via_trampoline pred_true;
  else 
    continue_via_trampoline pred_false;
}
continuation TM2xHd·p1
( void *context 
  ,void *item_pt 
  ,address_t element_n_Byte 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item >= 100 && item <= 354 )
    continue_via_trampoline pred_true;
  else 
    continue_via_trampoline pred_false;
}
continuation TM2xHd·p2
( void *context 
  ,void *item_pt 
  ,address_t element_n_Byte 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item == 248 )
    continue_via_trampoline pred_true;
  else 
    continue_via_trampoline pred_false;
}
continuation TM2xHd·p3
( void *context 
  ,void *item_pt 
  ,address_t element_n_Byte 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item == 355 )
    continue_via_trampoline pred_true;
  else 
    continue_via_trampoline pred_false;
}
continuation TM2xHd·p4
( void *context 
  ,void *item_pt 
  ,address_t element_n_Byte 
  ,continuation pred_true 
  ,continuation pred_false
  ){
  uint item = *(uint *)item_pt;
  if( item == 356 )
    continue_via_trampoline pred_true;
  else 
    continue_via_trampoline pred_false;
}

Result·Tallies test_1(){
  address_t malloc_cnt = MallocCounter·count;
  address_t constructed_cnt = T02x·alloc_array_count;
  bool f[256];
  uint32_t i = 0;

  Result·Tallies r ,*rp; rp = &r;
  Result·Tallies·init(rp);
  T02x·Root *a0;
  continue_into T02x·alloc_Tape_heap_construct(&a0 ,0 ,n_of(uint32_t) ,&&nominal_0 ,&&fail_0 ,&&fail_0);
  nominal_0:{
    f[i] = true;
    continue_from end_0;
  }
  fail_0:{
    f[i] = false;
    continue_from end_0;
  }
  end_0:{
    i++;
  }

  // make an array of data
  f[i] = true; // allocation failure flag
  uint32_t j=100;
  T02x·Write(a0 ,0 ,j);
  while( j < 355){
    j++;
    continue_into T02x·Push(a0 ,j ,&&nominal_1 ,&&fail_1);    
    fail_1:{
      f[i] = false;
    }
    nominal_1:{
      ;
    }
  }

  TM2xHd·AllocStaticRewind(a0 ,hd);
  continue_into TM2xHd·all(a0 ,hd ,n_of(uint32_t) ,NULL ,TM2xHd·p0 ,&&true_for_all_1 ,&&an_exception_1);
  true_for_all_1:{
    f[i] = true;
    continue_from end_1;
  }
  an_exception_1:{
    f[i] = false;
    continue_from end_1;
  }
  end_1:{
    i++;
  }

  TM2xHd·rewind(a0 ,hd);
  continue_into TM2xHd·all(a0 ,hd ,n_of(uint32_t) ,NULL ,TM2xHd·p1 ,&&true_for_all_2 ,&&an_exception_2);
  true_for_all_2:{
    f[i] = false;
    continue_from end_2;
  }
  an_exception_2:{
    f[i] = TM2xHd·Read_Expr(hd ,uint32_t) == 355;
    continue_from end_2;
  }
  end_2:{
    i++;
  }

  TM2xHd·rewind(a0 ,hd);
  continue_into TM2xHd·exists(a0 ,hd ,n_of(uint32_t) ,NULL ,TM2xHd·p3 ,&&found_3 ,&&not_found_3);
  found_3:{
    f[i] = TM2xHd·Read_Expr(hd ,uint32_t) == 355;
    continue_from end_3;
  }
  not_found_3:{
    f[i] = false;
    continue_from end_3;
  }
  end_3:{
    i++;
  }

  TM2xHd·rewind(a0 ,hd);
  continue_into TM2xHd·exists(a0 ,hd ,n_of(uint32_t) ,NULL ,TM2xHd·p4 ,&&found_4 ,&&not_found_4);
  found_4:{
    f[i] = false;
    continue_from end_4;
  }
  not_found_4:{
    f[i] = true;
    continue_from end_4;
  }
  end_4:{
    i++;
  }

  TM2xHd·AllocStaticRewind(a0 ,hd1);
  continue_into TM2xHd·exists(a0 ,hd1 ,n_of(uint32_t) ,NULL ,TM2xHd·p2 ,&&found_5 ,&&not_found_5);
  found_5:{
      uint t0 = TM2xHd·Read_Expr(hd1 ,uint32_t);
      {
        continue_into TM2xHd·is_on_tape(a0 ,hd1 ,&&on_tape_51 ,&&not_on_tape_51);
        on_tape_51:{
          f[i] = t0 == 248;    
          continue_from end_5;
        }
        not_on_tape_51:{
          f[i] = false;    
          continue_from end_5;
        }
      }
  }
  not_found_5:{
    f[i] = false;
    continue_from end_5;
  }
  end_5:{
    i++;
  }
  
  T02x·dealloc_Tape_heap(a0);
  f[i++] = malloc_cnt == MallocCounter·count;
  f[i++] = constructed_cnt == T02x·alloc_array_count;
  Result·Tallies·tally("test_1" ,rp ,f ,i);
  return r;
}

Result·Tallies test_2(){
  address_t malloc_cnt = MallocCounter·count;
  address_t constructed_cnt = T02x·alloc_array_count;
  Result·Tallies r ,*rp; rp = &r;
  Result·Tallies·init(rp);
  bool f[256];
  uint32_t i = 0;

  T02x·Root *a0;
  continue_into T02x·alloc_Tape_heap_construct(&a0 ,0 ,n_of(uint32_t) ,&&nominal_0 ,&&fail_0 ,&&fail_0);
  nominal_0:{
    f[i] = true;
    continue_from end_0;
  }
  fail_0:{
    f[i] = false;
    continue_from end_0;
  }
  end_0:{
    i++;
  }

  // make an array of data
  f[i] = true; // allocation failure flag
  uint32_t j=100;
  T02x·Write(a0 ,0 ,j);
  while( j < 110){
    ++j;
    continue_into T02x·Push(a0 ,j ,&&nominal_1 ,&&fail_1);    
    fail_1:{
      f[i] = false;
    }
    nominal_1:{
      ;
    }
  }

  // prints: 
  TM2xHd·AllocStaticRewind(a0 ,hd);
  TM2xHd·apply_to_each(a0 ,hd ,n_of(uint32_t) ," " ,TM2xHd·f_print_int);
  fputc('\n' ,stderr);

  T02x·dealloc_Tape_heap(a0);
  f[i++] = malloc_cnt == MallocCounter·count;
  f[i++] = constructed_cnt == T02x·alloc_array_count;
  Result·Tallies·tally("test_2" ,rp ,f ,i);
  return r;
}

Result·Tallies test_3(){
  address_t malloc_cnt = MallocCounter·count;
  address_t constructed_cnt = T02x·alloc_array_count;
  Result·Tallies r ,*rp; rp = &r;
  Result·Tallies·init(rp);
  bool f[256];
  uint32_t i = 0;
  uint32_t j;

  j=0;
  T02x·AllocStatic(a0);
  {
    continuations nominal ,fail ,end;
    T02x·construct_write(a0 ,&j ,n_of(j) ,&&nominal ,&&fail);
    nominal:{
      f[i] = true;
      continue_from end;
    }
    fail:{
      f[i] = false;
      continue_from end;
    }
    end:{
      i++;
    }
  }
  {
    continuations nominal ,fail;
    f[i] = true; 
    while( j < 30 ){
      j+=3;
      continue_into T02x·Push(a0 ,j ,&&nominal ,&&fail);    
      fail:{
        f[i] = false;
      }
      nominal:{
        ;
      }
    }
    i++;
  }

  fprintf(stderr, "a0:");
  TM2xHd·AllocStaticRewind(a0 ,hd);
  TM2xHd·apply_to_each(a0 ,hd ,n_of(uint) ," " ,TM2xHd·f_print_int);
  fputc('\n' ,stderr);

  j=50;
  T02x·AllocStaticConstruct_Write(a1 ,j ,&&nominal_2 ,&&fail_2);
  nominal_2:{
    f[i] = true;
    continue_from end_2;
  }
  fail_2:{
    f[i] = false;
    continue_from end_2;
  }
  end_2:{
    i++;
  }
  while( j > 10 ){
    j-=5;
    continue_into T02x·Push(a1 ,j ,&&nominal_3 ,&&fail_3);    
    nominal_3:{
      f[i] = true;
      continue_from end_3;
    }
    fail_3:{
      f[i] = false;
      continue_from end_3;
    }
    end_3:{
      i++;
    }
  }

  fprintf(stderr, "a1:");
  TM2xHd·rewind(a1 ,hd);
  TM2xHd·apply_to_each(a1 ,hd ,n_of(uint) ," " ,TM2xHd·f_print_int);
  fputc('\n' ,stderr);

  j=30;
  T02x·AllocStaticConstruct_Write(a2 ,j ,&&nominal_4 ,&&fail_4);
  nominal_4:{
    f[i] = true;
    continue_from end_4;
  }
  fail_4:{
    f[i] = false;
    continue_from end_4;
  }
  end_4:{
    i++;
  }

  j=57;
  continue_into T02x·Push(a2 ,j ,&&nominal_5 ,&&fail_5);    
  nominal_5:{
    f[i] = true;
    continue_from end_5;
  }
  fail_5:{
    f[i] = false;
    continue_from end_5;
  }
  end_5:{
    i++;
  }

  j=15;
  continue_into T02x·Push(a2 ,j ,&&nominal_6 ,&&fail_6);    
  nominal_6:{
    f[i] = true;
    continue_from end_6;
  }
  fail_6:{
    f[i] = false;
    continue_from end_6;
  }
  end_6:{
    i++;
  }

  j=59;
  continue_into T02x·Push(a2 ,j ,&&nominal_7 ,&&fail_7);    
  nominal_7:{
    f[i] = true;
    continue_from end_7;
  }
  fail_7:{
    f[i] = false;
    continue_from end_7;
  }
  end_7:{
    i++;
  }

  j=15;
  continue_into T02x·Push(a2 ,j ,&&nominal_8 ,&&fail_8);    
  nominal_8:{
    f[i] = true;
    continue_from end_8;
  }
  fail_8:{
    f[i] = false;
    continue_from end_8;
  }
  end_8:{
    i++;
  }

  fprintf(stderr, "a2:");
  TM2xHd·rewind(a2 ,hd);
  TM2xHd·apply_to_each(a2 ,hd ,n_of(uint) ," " ,TM2xHd·f_print_int);
  fputc('\n' ,stderr);
  // add test distinct == false
  T02x·AllocStatic(a3);
  {
    continuations nominal ,fail ,end;
    continue_into TM2xHd·init_intersection
      ( a3 
        ,a0 
        ,a1
        ,n_of(uint) 
        ,TM2xHd·pred_bytes_eq
        ,&&nominal 
        ,&&empty
        ,&&fail
        );

    nominal:{ // a3 is only constructed if we travel down this path
      f[i++] = true;
      fprintf(stderr, "a3 = intersection a1 a0: ");
      TM2xHd·rewind(a3 ,hd);
      TM2xHd·apply_to_each(a3 ,hd ,n_of(uint) ," " ,TM2xHd·f_print_int);
      fputc('\n' ,stderr);
      bool subset;
      TM2xHd·AllocStaticRewind(a2 ,a2_hd);
      {
        continuations nominal ,fail ,end;
        continue_into TM2xHd·accumulate_union
          ( a3 
            ,a2 
            ,a2_hd
            ,n_of(uint) 
            ,TM2xHd·pred_bytes_eq 
            ,&subset
            ,&&nominal 
            ,&&fail
            );
        nominal:{
          f[i] = true;
          continue_from end;
        }
        fail:{
          f[i] = false;
          continue_from end;
        }
        end:{
          i++;
        }
      }
      fprintf(stderr, "a3 union a2: ");
      TM2xHd·rewind(a3 ,hd);
      TM2xHd·apply_to_each(a3 ,hd ,n_of(uint) ," " ,TM2xHd·f_print_int);
      fputc('\n' ,stderr);
      T02x·dealloc_array(a3);
      continue_from end;
    }

    empty:{
      f[i++] = false;
      continue_from end;
    }

    fail:{
      f[i++] = false;
      continue_from end;
    }

    end:{
      ;
    }
  }

  T02x·dealloc_array(a0);
  T02x·dealloc_array(a1);
  T02x·dealloc_array(a2);
  f[i++] = malloc_cnt == MallocCounter·count;
  f[i++] = constructed_cnt == T02x·alloc_array_count;
  Result·Tallies·tally("test_3" ,rp ,f ,i);
  return r;
}

int main(){
  Result·Tallies r ,acc ,*accp; accp=&acc;
  Result·Tallies·init(accp);

  r = test_0(); Result·Tallies·accumulate(accp ,&r);
  r = test_1(); Result·Tallies·accumulate(accp ,&r);
  r = test_2(); Result·Tallies·accumulate(accp ,&r);
  r = test_3(); Result·Tallies·accumulate(accp ,&r);

  Result·Tallies·print("TM2xHd·test results" ,accp);
  return acc.failed;
}
