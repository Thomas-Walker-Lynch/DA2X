#ifndef TM2x·LIB_H
#define TM2x·LIB_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include "nonstdint.h"
#include "inclusive.h"
#include "continuation.h"

/*--------------------------------------------------------------------------------
   global stuff

  There are three options for the inlining style for the interface: no-inlining, 'extern
  inline', and 'static inilne'.  No inlining is the simplest, but there is no performance
  advantage.  The compiler can ignore requests to inline, and it looks like gcc is doing
  so when the debugging flag is turned on and optimization is turned off. 'static inline'
  generates file scope code if it is needed.  This is simplest inlining approach for
  development because there is only one declaration of each function to edit.  'extern
  line' will only generate one version of functions that are not inlined, and share it
  everywhere it is needed. The non-inline versions of the functions have to be compiled
  separately and made available for linking.

*/  

  //
  //#define TM2x·F_PREFIX static
  //#define TM2x·F_PREFIX extern inline
  #define TM2x·F_PREFIX static inline

  TM2x·F_PREFIX address_t binary_interval_inclusive_upper_bound(address_t byte_n){
    if( byte_n == 0 ) return 1;
    return (1 << (address_bit_length - __builtin_clz(byte_n))) - 1;
  }

  TM2x·F_PREFIX continuation mallocn(void **pt ,address_t n ,continuation nominal ,continuation fail){
    if( n == address_t_n ) continue_via_trampoline fail;
    *pt = malloc(n+1);
    if(!*pt) continue_via_trampoline fail;
    continue_via_trampoline nominal;
  }

  // This is a debug feature. To keep the heap clean all initialized arrays must be
  // TM2x·data_dalloc'ed.  This counter is incremented upon initialization of an array,
  // and it is decremented upon TM2x·data_dalloc.
  extern address_t TM2x·initialized_cnt;

  // change unit of measure
  TM2x·F_PREFIX address_t TM2x·mulns(address_t a_n , address_t b_n){
    return a_n * b_n + a_n + b_n;
  }

//--------------------------------------------------------------------------------
// dynamic array instance type
//    
  typedef struct {
    char *base_pt;
    address_t byte_n;
  } TM2x;

//--------------------------------------------------------------------------------
// allocation
//
  // tape becomes a pointer to a static allocation of a TM2x struct
  #define TM2x·AllocStatic(tape) TM2x TM2x· ## tape ,*tape; tape = &TM2x· ## tape;

  // after data_deallocation, the TM2x may be re-initialized and used again
  TM2x·F_PREFIX void TM2x·dealloc_static(TM2x *tape){
    free(tape->base_pt);
    TM2x·initialized_cnt--;
  }

  // for dynammic allocation of TM2xs:
  TM2x·F_PREFIX continuation TM2x·alloc_heap
  ( TM2x **tape 
   ,address_t element_n 
   ,address_t element_byte_n
   ,continuation nominal
   ,continuation fail
   ){
    continue_via_trampoline mallocn((void **)tape ,byte_n_of(TM2x) ,nominal ,fail);
  }
  TM2x·F_PREFIX void TM2x·dealloc_heap(TM2x *tape){
    TM2x·dealloc_static(tape);
    free(tape);
  }

  // need to check memory limit
  #ifdef TM2x·TEST
    extern address_t TM2x·test_after_allocation_n;
  #endif
  TM2x·F_PREFIX continuation TM2x·resize
  ( TM2x *tape 
   ,address_t after_allocation_n
   ,continuation resize_nominal
   ,continuation allocation_fail
   ){
    char *after_base_pt;
    continue_into mallocn((void **)&after_base_pt ,after_allocation_n ,&&malloc_nominal ,&&malloc_fail);
      malloc_nominal:
        {}
        #ifdef TM2x·TEST
          TM2x·test_after_allocation_n = after_allocation_n;
        #endif
        char *before_base_pt = tape->base_pt;
        memcpyn( after_base_pt ,before_base_pt ,tape->byte_n);
        free(before_base_pt);
        tape->base_pt = after_base_pt;
        continue_via_trampoline resize_nominal;
      malloc_fail: continue_via_trampoline allocation_fail;
  }

  TM2x·F_PREFIX address_t TM2x·initialized(TM2x *tape){
    return TM2x·initialized_cnt;
  }

//--------------------------------------------------------------------------------
// formatting / formatting and initializing
//

  // Need to add limit check against our upper address bound
  // element_n is the maximum index for the initial data array
  // returns true when formatting succeeds
  TM2x·F_PREFIX continuation __TM2x·format
  ( TM2x *tape 
   ,address_t byte_n 
   ,continuation format_nominal
   ,continuation format_alloc_fail
   ){
    TM2x·initialized_cnt++; // to assist with debugging
    tape->byte_n = byte_n;
    address_t allocation_byte_n = binary_interval_inclusive_upper_bound(byte_n);
    continue_into mallocn( (void **)&(tape->base_pt) ,allocation_byte_n ,&&mallocn_nominal ,&&mallocn_fail);
      mallocn_nominal: continue_via_trampoline format_nominal;
      mallocn_fail: continue_via_trampoline format_alloc_fail;
  }
  TM2x·F_PREFIX continuation TM2x·format
  ( TM2x *tape
    ,address_t element_n
    ,address_t element_byte_n 
    ,continuation nominal
    ,continuation alloc_fail
    ){
    address_t byte_n = TM2x·mulns(element_byte_n ,element_n);
    continue_into __TM2x·format(tape ,byte_n ,&&format_nominal ,&&format_alloc_fail);
      format_nominal: continue_via_trampoline nominal;
      format_alloc_fail: continue_via_trampoline alloc_fail;
  }
  // makes a pointer to an unitialized tape
  #define TM2x·AllocStaticFormat(tape ,element_n ,type ,cont_nominal ,cont_fail) \
    TM2x·AllocStatic(tape);\
    continue_into TM2x·format(tape ,element_n ,byte_n_of(type), cont_nominal ,cont_fail);

  TM2x·F_PREFIX continuation TM2x·alloc_heap_format
  ( TM2x **tape 
    ,address_t element_n 
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation fail
    ){
    continue_into mallocn((void **)tape ,byte_n_of(TM2x) ,&&mallocn_nominal ,&&mallocn_fail);
      mallocn_nominal:
        continue_into TM2x·format(*tape ,element_n ,element_byte_n ,&&format_nominal ,&&format_fail);
          format_fail: continue_via_trampoline fail;
          format_nominal: continue_via_trampoline nominal;
      mallocn_fail: continue_via_trampoline fail;
    }

  TM2x·F_PREFIX continuation TM2x·format_write
  ( TM2x *tape 
    ,void *element_pt 
    ,address_t element_byte_n 
    ,continuation nominal
    ,continuation fail
    ){
    continue_into TM2x·format(tape ,0 ,element_byte_n ,&&format_nominal ,&&format_fail);
      format_nominal:
        memcpyn(tape->base_pt, element_pt, element_byte_n);
        continue_via_trampoline nominal;
      format_fail: continue_via_trampoline fail;
  }

  TM2x·F_PREFIX continuation TM2x·format_write_cstring
  ( TM2x *tape 
    ,char *pt
    ,continuation nominal
    ,continuation null_pt
    ,continuation alloc_fail
    ){

    if(!pt) continue_via_trampoline null_pt;
    continuation do_write = &&init; 

    is_char_q:;
      if(*pt) continue_from do_write;
      continue_via_trampoline nominal;

    init:;
      continue_into TM2x·format_write(tape ,pt ,byte_n_of(char) ,&&init·nominal ,&&alloc_fail_local);
        init·nominal:;
          do_write = &&extend;
          continue_from next;

    extend:;
      continue_into TM2x·push_write(tape ,pt ,byte_n_of(char) ,&&next ,&&alloc_fail_local);

    next:;
      pt++;
      continue_from is_char_q;

    alloc_fail_local:;
      continue_via_trampoline alloc_fail;

  }

  #define TM2x·AllocStaticFormat_Write(tape ,item ,cont_nominal ,cont_fail)\
    TM2x·AllocStatic(tape);\
    continue_into TM2x·format_write(tape ,&item ,byte_n_of(typeof(item)) ,cont_nominal ,cont_fail);



  // tape_new has been allocated. This routine formats and intitializes it.
  // shallow copy tape_src elements to tape_new
  // need a version of this where the second argument is an hd, takes the tail from another list == drop
  TM2x·F_PREFIX continuation TM2x·format_copy
  ( TM2x *tape
    ,TM2x *tape_src
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation fail
    ){
    address_t byte_n = tape_src->byte_n;
    continue_into __TM2x·format(tape ,byte_n ,&&format_nominal ,&&format_fail);
      format_nominal: 
        memcpyn(tape->base_pt ,tape_src->base_pt ,byte_n);
        continue_via_trampoline nominal;
      format_fail: continue_via_trampoline fail;
  }

//--------------------------------------------------------------------------------
// adjectives
//
// Use these adjectives rather than accessing the TM2x struct directly.
//

  // base pointers
  TM2x·F_PREFIX char *TM2x·byte_0_pt(TM2x *tape){
    return tape->base_pt;
  }
  TM2x·F_PREFIX void *TM2x·element_0_pt(TM2x *tape){
    return tape->base_pt;
  }

  // max offsets
  TM2x·F_PREFIX address_t TM2x·byte_n(TM2x *tape){
    return tape->byte_n;
  }
  // The index of the last element in the array.  Note that the
  // (element_byte_n + 1) in the denominator must be representable:
  TM2x·F_PREFIX address_t TM2x·element_n(TM2x *tape ,address_t element_byte_n){
    return tape->byte_n/(element_byte_n + 1);
  }

  // nth pointers
  TM2x·F_PREFIX char *TM2x·byte_n_pt(TM2x *tape){
    return tape->base_pt + tape->byte_n;
  }
  TM2x·F_PREFIX void *TM2x·element_n_pt(TM2x *tape ,address_t element_byte_n){
    return TM2x·byte_n_pt(tape) - element_byte_n;
  }
  #define TM2x·Element_N_Pt(tape ,type) TM2x·element_n_pt(tape ,byte_n_of(type))

//--------------------------------------------------------------------------------
// indexing
//   consider using the iterator TM2xHd.h instead of indexes
//
  // returns pointer to element at given index
  TM2x·F_PREFIX void *TM2x·element_i_pt(TM2x *tape ,address_t index ,address_t element_byte_n){
    return TM2x·byte_0_pt(tape) + element_byte_n * index + index;
  }

  TM2x·F_PREFIX void TM2x·read(TM2x *tape ,address_t index ,void *dst_element_pt ,address_t element_byte_n){
    void *src_element_pt = TM2x·element_i_pt(tape ,index ,element_byte_n);
    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
  }
  #define TM2x·Read(tape ,index ,x) TM2x·read(tape ,index ,&x ,byte_n_of(typeof(x)))

  TM2x·F_PREFIX void TM2x·write(TM2x *tape ,address_t index ,void *src_element_pt ,address_t element_byte_n){
    void *dst_element_pt = TM2x·element_i_pt(tape ,index ,element_byte_n);
    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
  }
  #define TM2x·Write(tape ,index ,x) TM2x·write(tape ,index ,&(x) ,byte_n_of(typeof(x)))

//--------------------------------------------------------------------------------
// stack
//
  // Need to add limit checks because an expanded array might fail to fit in memory.
  // Attempts to expands the data portion of the array to accomodate np1 more elements.
  // If the current allocation is not large enough we make a new larger allocation.  If that
  // is not possible, then we return false.  Otherwise we return true.
  // If you need the before expansion top of the array, save that before calling this.
  TM2x·F_PREFIX continuation TM2x·push_alloc
  ( TM2x *tape 
    ,address_t requested_expansion_element_n
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation fail
    ){
    address_t requested_expansion_byte_n = TM2x·mulns(requested_expansion_element_n ,element_byte_n);
    address_t before_byte_n = TM2x·byte_n(tape);
    address_t before_allocation_n = binary_interval_inclusive_upper_bound(before_byte_n);
    address_t after_byte_n = before_byte_n + requested_expansion_byte_n + 1;
    tape->byte_n = after_byte_n;
    address_t after_allocation_n = binary_interval_inclusive_upper_bound(after_byte_n);
    if( after_allocation_n <= before_allocation_n ) continue_via_trampoline nominal;
    continue_into TM2x·resize(tape ,after_allocation_n ,&&resize_nominal ,&&resize_fail);
      resize_nominal: continue_via_trampoline nominal;
      resize_fail: continue_via_trampoline fail;
  }
  #define TM2x·Push_Alloc(tape ,expansion_element_n ,type ,cont_nominal ,cont_fail) \
    TM2x·push_alloc(tape, expansion_element_n ,byte_n_of(type) ,cont_nominal ,cont_fail)

  TM2x·F_PREFIX continuation TM2x·push_write
  ( TM2x *tape 
    ,void *src_element_pt 
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation allocation_failed
    ){
    continue_into TM2x·push_alloc(tape ,0 ,element_byte_n ,&&push_alloc_nominal ,&&push_alloc_fail);
      push_alloc_nominal:
        memcpyn(TM2x·element_n_pt(tape ,element_byte_n) ,src_element_pt ,element_byte_n);
        continue_via_trampoline nominal;
      push_alloc_fail:
        continue_via_trampoline allocation_failed;
  }
  #define TM2x·Push_Write(tape ,src_element ,cont_nominal ,cont_allocation_failed)\
    TM2x·push_write(tape ,&src_element ,byte_n_of(typeof(src_element)) ,cont_nominal ,cont_allocation_failed)

  // need to add pop for n elements ...
  TM2x·F_PREFIX continuation TM2x·pop
  ( TM2x *tape
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation pop_last
    ){

    address_t before_byte_n = TM2x·byte_n(tape);
    if( before_byte_n <= element_byte_n ) continue_via_trampoline pop_last;
    address_t after_byte_n = before_byte_n - element_byte_n - 1;
    tape->byte_n = after_byte_n; 

    // attempt to reduce the allocation
    // If we attempt but fail to reduce the allocation size, the extra space on this tape will never be used,
    // but otherwise the stack will continue to function.
    address_t before_allocation_n = binary_interval_inclusive_upper_bound(before_byte_n);
    address_t after_allocation_n = binary_interval_inclusive_upper_bound(after_byte_n);
    if( after_allocation_n < before_allocation_n ) TM2x·resize(tape ,after_allocation_n ,NULL ,NULL);

    continue_via_trampoline nominal;
  }
  #define TM2x·Pop(tape ,type ,cont_nominal ,cont_pop_last)\
    TM2x·pop(tape ,byte_n_of(type) ,cont_nominal ,cont_pop_last )

  // should make a version to pop off n elements 
  TM2x·F_PREFIX continuation TM2x·read_pop
  ( TM2x *tape 
    ,void *dst_element_pt 
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation pop_last
    ){
    memcpyn(dst_element_pt, TM2x·element_n_pt(tape ,element_byte_n) ,element_byte_n);
    continue_into TM2x·pop(tape ,element_byte_n ,&&pop_nominal ,&&pop_pop_last);
      pop_nominal: continue_via_trampoline nominal;
      pop_pop_last: continue_via_trampoline pop_last;
  }
  #define TM2x·Read_Pop(tape ,dst_element ,cont_nominal ,cont_pop_last)\
    TM2x·read_pop(tape ,&dst_element ,byte_n_of(typeof(dst_element)) ,cont_nominal ,cont_pop_last)



#endif

