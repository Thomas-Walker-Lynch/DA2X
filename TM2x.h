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

  There are three options for the inlining style for the interface: 'static', none, 'extern
  inline', and 'static inilne'.  No inlining is the simplest, but there is no performance
  advantage.  The compiler can ignore requests to inline, and it looks like gcc is doing
  so when the debugging flag is turned on and optimization is turned off. 'static inline'
  generates file scope code if it is needed.  This is simplest inlining approach for
  development because there is only one declaration of each function to edit.  'extern
  line' will only use the one extern version of a given function when it is not
  inlined. For 'extern inline', the non-inline versions of the functions have to be
  compiled separately and made available for linking.  To make the C file for the extern
  definitions simply define the prefix with a null value then include this header.

*/  

  #ifndef TM2x·F_PREFIX 
    //#define TM2x·F_PREFIX static
    //#define TM2x·F_PREFIX extern inline
    #define TM2x·F_PREFIX static inline
  #endif

  #define CAT2(x ,y) x ## y
  #define CAT(x ,y) CAT2(x ,y)
  #define VAR(x) CAT(x, __LINE__)

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
  // need to add an overflow continuation!
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

  // similar to stdlib realloc
  #ifdef TM2x·TEST
    extern address_t TM2x·test_after_allocation_n;
  #endif
  TM2x·F_PREFIX continuation TM2x·resize
  ( TM2x *tape 
   ,address_t after_byte_n
   ,continuation nominal
   ,continuation allocation_fail
   ){

    address_t before_allocation_n = binary_interval_inclusive_upper_bound(tape->byte_n);
    address_t after_allocation_n = binary_interval_inclusive_upper_bound(after_byte_n);

    if( after_allocation_n == before_allocation_n ){
      tape->byte_n = after_byte_n;
      continue_via_trampoline nominal;
    }

    char *after_base_pt;
    continue_into mallocn((void **)&after_base_pt ,after_allocation_n ,&&malloc_nominal ,&&malloc_fail);
      malloc_nominal:
        {}
        #ifdef TM2x·TEST
          TM2x·test_after_allocation_n = after_allocation_n;
        #endif
        address_t copy_n = after_byte_n <  tape->byte_n ? after_byte_n : tape->byte_n;
        memcpyn( after_base_pt ,tape->base_pt ,copy_n);
        free(tape->base_pt);
        tape->base_pt = after_base_pt;
        tape->byte_n = after_byte_n;
        continue_via_trampoline nominal;
      malloc_fail:
       continue_via_trampoline allocation_fail;
  }
  #define TM2x·Resize(tape ,expansion_element_n ,type ,cont_nominal ,cont_fail) \
    ({                                                                      \
      address_t VAR(TM2x·Resize·byte_n) = TM2x·mulns(expansion_element_n , byte_n_of(type) ); \
      TM2x·resize(tape ,VAR(TM2x·Resize·byte_n) ,cont_nominal ,cont_fail); \
        })

  TM2x·F_PREFIX address_t TM2x·initialized(TM2x *tape){
    return TM2x·initialized_cnt;
  }

//--------------------------------------------------------------------------------
// formatting / formatting and initializing
//

  // Need to add limit check against our upper address bound
  // element_n is the maximum index for the initial data array
  // returns true when formatting succeeds
  TM2x·F_PREFIX continuation TM2x·format_bytes
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
  TM2x·F_PREFIX continuation TM2x·format_elements
  ( TM2x *tape
    ,address_t element_n
    ,address_t element_byte_n 
    ,continuation nominal
    ,continuation alloc_fail
    ){
    address_t byte_n = TM2x·mulns(element_byte_n ,element_n);
    continue_into TM2x·format_bytes(tape ,byte_n ,&&format_nominal ,&&format_alloc_fail);
      format_nominal: continue_via_trampoline nominal;
      format_alloc_fail: continue_via_trampoline alloc_fail;
  }
  // makes a pointer to an unitialized tape
  #define TM2x·AllocStaticFormat(tape ,element_n ,type ,cont_nominal ,cont_fail) \
    TM2x·AllocStatic(tape);\
    continue_into TM2x·format_elements(tape ,element_n ,byte_n_of(type), cont_nominal ,cont_fail);

  TM2x·F_PREFIX continuation TM2x·alloc_heap_format
  ( TM2x **tape 
    ,address_t element_n 
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation fail
    ){
    continue_into mallocn((void **)tape ,byte_n_of(TM2x) ,&&mallocn_nominal ,&&mallocn_fail);
      mallocn_nominal:
        continue_into TM2x·format_elements(*tape ,element_n ,element_byte_n ,&&format_nominal ,&&format_fail);
          format_fail: continue_via_trampoline fail;
          format_nominal: continue_via_trampoline nominal;
      mallocn_fail: continue_via_trampoline fail;
    }

  TM2x·F_PREFIX continuation TM2x·format_write_bytes
  ( TM2x *tape 
    ,void *source_pt 
    ,address_t source_byte_n 
    ,continuation nominal
    ,continuation fail
    ){
    continue_into TM2x·format_bytes(tape ,source_byte_n ,&&format_nominal ,&&format_fail);
      format_nominal:
        memcpyn(tape->base_pt, source_pt, source_byte_n);
        continue_via_trampoline nominal;
      format_fail: continue_via_trampoline fail;
  }

  // use this to block copy an array of bytes to a newly allocated TM2x
  TM2x·F_PREFIX continuation TM2x·format_write
  ( TM2x *tape 
    ,void *element_base_pt
    ,address_t element_byte_n 
    ,continuation nominal
    ,continuation fail
    ){
    return TM2x·format_write_bytes(tape ,element_base_pt ,element_byte_n ,nominal  ,fail);
  }

  // use this to block copy an array to a newly allocated TM2x
  TM2x·F_PREFIX continuation TM2x·format_write_elements
  ( TM2x *tape 
    ,void *base_pt
    ,address_t element_n 
    ,address_t element_byte_n 
    ,continuation nominal
    ,continuation fail
    ){
    address_t byte_n = TM2x·mulns(element_n ,element_byte_n);
    return TM2x·format_write(tape ,base_pt ,byte_n ,nominal  ,fail);
  }

  // use this to block copy another TM2x to a newly allocated TM2x
  TM2x·F_PREFIX continuation TM2x·format_write_TM2x
  ( TM2x *tape 
    ,TM2x *tape_source
    ,continuation nominal
    ,continuation fail
    ){
    return TM2x·format_write(tape ,tape_source->base_pt ,tape_source->byte_n ,nominal  ,fail);
  }

  #define TM2x·AllocStaticFormat_Write(tape ,item ,cont_nominal ,cont_fail)\
    TM2x·AllocStatic(tape);\
    continue_into TM2x·format_write(tape ,&item ,byte_n_of(typeof(item)) ,cont_nominal ,cont_fail);


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

  TM2x·F_PREFIX continuation TM2x·copy_bytes
  ( TM2x *src
    ,address_t src_byte_i
    ,TM2x *dst
    ,address_t dst_byte_i
    ,address_t byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_src_index
    ,continuation bad_dst_index
    ){
    if( src_byte_i + byte_n > TM2x·byte_n(src) ) continue_via_trampoline bad_src_index;
    if( dst_byte_i + byte_n > TM2x·byte_n(dst) ) continue_via_trampoline bad_dst_index;
    memcpyn(TM2x·byte_0_pt(dst) + dst_byte_i ,TM2x·byte_0_pt(dst) + src_byte_i ,byte_n);
  }

  // A bad index is either one that overlflows the address space for either source or
  // destination, or one that is off the end of the source array.
  TM2x·F_PREFIX continuation TM2x·copy_elements
  ( TM2x *src
    ,address_t src_element_i
    ,TM2x *dst
    ,address_t dst_element_i
    ,address_t element_n  // index of nth element of the copy region
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_src_index
    ,continuation bad_dst_index
    ){
    address_t dst_byte_i = TM2x·mulns(dst_element_i ,element_byte_n);
    address_t src_byte_i = TM2x·mulns(src_element_i ,element_byte_n);
    address_t byte_n = TM2x·mulns(element_n ,element_byte_n);
    return TM2x·copy_bytes
      ( src
        ,src_byte_i
        ,dst
        ,dst_byte_i
        ,byte_n
        ,nominal
        ,alloc_fail
        ,bad_src_index
        ,bad_dst_index
        );
  }




//--------------------------------------------------------------------------------
// stack behavior
//
  TM2x·F_PREFIX continuation TM2x·push_bytes
  ( TM2x *tape 
    ,void *source_pt 
    ,address_t source_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ){
    address_t push_pt = TM2x·byte_n(tape) + 1;
    address_t after_byte_n = push_pt + source_byte_n;
    continue_into TM2x·resize(tape ,after_byte_n ,&&resize_nominal ,&&resize_fail);
      resize_nominal:
        memcpyn(TM2x·byte_0_pt(tape) + push_pt ,source_pt ,source_byte_n);
        continue_via_trampoline nominal;
      resize_fail:
        continue_via_trampoline alloc_fail;
  }

  // use this to block push an entire array of bytes 
  TM2x·F_PREFIX continuation TM2x·push
  ( TM2x *tape 
    ,void *element_base_pt
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ){
    return TM2x·push_bytes(tape ,element_base_pt ,element_byte_n ,nominal  ,alloc_fail);
  }

  // use this to block push an entire array of elements
  TM2x·F_PREFIX continuation TM2x·push_elements
  ( TM2x *tape 
    ,void *base_pt
    ,address_t element_n 
    ,address_t element_byte_n 
    ,continuation nominal
    ,continuation alloc_fail
    ){
    address_t byte_n = TM2x·mulns(element_n ,element_byte_n);
    return TM2x·push(tape ,base_pt ,byte_n ,nominal  ,alloc_fail);
  }

  // use this to block push the contents of another TM2x
  TM2x·F_PREFIX continuation TM2x·push_TM2x
  ( TM2x *tape 
    ,TM2x *tape_source
    ,continuation nominal
    ,continuation alloc_fail
    ){
    return TM2x·push(tape ,tape_source->base_pt ,tape_source->byte_n ,nominal  ,alloc_fail);
  }

  #define TM2x·Push(tape ,src_element ,nominal ,alloc_fail)\
    TM2x·push(tape ,&src_element ,byte_n_of(typeof(src_element)) ,nominal ,alloc_fail)


  TM2x·F_PREFIX continuation TM2x·pop
  ( TM2x *tape
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation pop_last
    ,continuation alloc_fail
    ){

    address_t before_byte_n = TM2x·byte_n(tape);
    if( before_byte_n <= element_byte_n ) continue_via_trampoline pop_last;
    address_t after_byte_n = before_byte_n - element_byte_n - 1;
    TM2x·resize(tape ,after_byte_n ,&&resize_nominal ,&&alloc_fail);
      resize_nominal:;
        continue_via_trampoline nominal;    
      alloc_fail:;
        continue_via_trampoline alloc_fail;

  }
  #define TM2x·Pop(tape ,type ,cont_nominal ,cont_pop_last)\
    TM2x·pop(tape ,byte_n_of(type) ,cont_nominal ,cont_pop_last )

  TM2x·F_PREFIX continuation TM2x·read_pop
  ( TM2x *tape 
    ,void *dst_element_pt 
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation pop_last
    ,continuation alloc_fail
    ){
    memcpyn(dst_element_pt, TM2x·element_n_pt(tape ,element_byte_n) ,element_byte_n);
    continue_into TM2x·pop(tape ,element_byte_n ,&&pop_nominal ,&&pop_pop_last ,&&pop_alloc_fail);
      pop_nominal: continue_via_trampoline nominal;
      pop_pop_last: continue_via_trampoline pop_last;
      pop_alloc_fail: continue_via_trampoline alloc_fail;
  }
  #define TM2x·Read_Pop(tape ,dst_element ,nominal ,pop_last ,alloc_fail)           \
    TM2x·read_pop(tape ,&dst_element ,byte_n_of(typeof(dst_element)) ,nominal ,pop_last ,alloc_fail)

#endif

