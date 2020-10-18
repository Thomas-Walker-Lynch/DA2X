#ifndef TM2x·LIB_H
#define TM2x·LIB_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include "inclusive.h"
#include "Continuation.h"
#include "misc.h"
#include "TM2x·misc.h"

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

  TM2x·F_PREFIX SequencePtr mallocn(void **pt ,address_t n ,SequencePtr nominal ,SequencePtr fail){
    if( n == address_t_n ) continue_via_trampoline fail;
    *pt = malloc(n+1);
    if(!*pt) continue_via_trampoline fail;
    continue_via_trampoline nominal;
  }

  // This is a debug feature. To keep the heap clean all constructed arrays must be
  // TM2x·data_dalloc'ed.  This counter is incremented upon construction of an array,
  // and it is decremented upon destruction.
  extern address_t TM2x·alloc_array_count;

//--------------------------------------------------------------------------------
// dynamic array instance type
//    
  typedef struct {
    char *base_pt;
    address_t byte_n;
  } TM2x;

//--------------------------------------------------------------------------------
// adjectives
//
// Use these adjectives rather than accessing the TM2x·Tape struct directly.
//

  // base pointers
  TM2x·F_PREFIX char *TM2x·byte_0_pt(TM2x·Tape *tape){
    return tape->base_pt;
  }
  TM2x·F_PREFIX void *TM2x·element_0_pt(TM2x·Tape *tape){
    return tape->base_pt;
  }

  // max offsets
  TM2x·F_PREFIX address_t TM2x·byte_n(TM2x·Tape *tape){
    return tape->byte_n;
  }
  // The index of the last element in the array.  Note that the
  // (element_byte_n + 1) in the denominator must be representable:
  TM2x·F_PREFIX address_t TM2x·element_n(TM2x·Tape *tape ,address_t element_byte_n){
    return tape->byte_n/(element_byte_n + 1);
  }

  // nth pointers
  TM2x·F_PREFIX char *TM2x·byte_n_pt(TM2x·Tape *tape){
    return tape->base_pt + tape->byte_n;
  }
  TM2x·F_PREFIX void *TM2x·element_n_pt(TM2x·Tape *tape ,address_t element_byte_n){
    return TM2x·byte_n_pt(tape) - element_byte_n;
  }
  #define TM2x·Element_N_Pt(tape ,type) TM2x·element_n_pt(tape ,byte_n_of(type))


//--------------------------------------------------------------------------------
// allocation
//
  // tape becomes a pointer to a static allocation of a TM2x·Tape struct
  #define TM2x·AllocStatic(tape) TM2x·Tape TM2x· ## tape ,*tape; tape = &TM2x· ## tape;

  TM2x·F_PREFIX address_t TM2x·constructed(TM2x·Tape *tape){
    return TM2x·alloc_array_count;
  }

//--------------------------------------------------------------------------------
// constructing / constructing and initializing
//

//--------------------------------------------------------------------------------
// indexing
//   consider using the iterator TM2xHd.h instead of indexes
//

TM2x·write_bytes·args

  TM2x·F_PREFIX SequencePtr TM2x·write_bytes
    ,TM2x·Tape *dst
    ,address_t dst_byte_i
    ,void *src_pt
    ,address_t byte_n
    ,SequencePtr nominal
    ,SequencePtr alloc_fail
    ,SequencePtr src_index_gt_n
    ,SequencePtr dst_index_gt_n
    ){
    if( (address_t)(src_pt + byte_n) < (address_t)src_pt  ) continue_via_trampoline bad_src_index;
    if( dst_byte_i + byte_n > TM2x·byte_n(dst) ) continue_via_trampoline bad_dst_index;
    memcpyn(TM2x·byte_0_pt(dst) + dst_byte_i ,src_pt ,byte_n);
  }

  TM2x·F_PREFIX void TM2x·write(TM2x·Tape *tape ,address_t index ,void *src_element_pt ,address_t element_byte_n){
    void *dst_element_pt = TM2x·index·to_pt(tape ,index ,element_byte_n);
    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
  }
  #define TM2x·Write(tape ,index ,x) TM2x·write(tape ,index ,&(x) ,byte_n_of(typeof(x)))


TM2x·copy_contiguous_bytes·args
  TM2x·F_PREFIX SequencePtr TM2x·copy_contiguous_bytes
  ( TM2x·Tape *src
    ,address_t src_byte_i
    ,TM2x·Tape *dst
    ,address_t dst_byte_i
    ,address_t byte_n
    ,SequencePtr nominal
    ,SequencePtr alloc_fail
    ,SequencePtr bad_src_index
    ,SequencePtr bad_dst_index
    ){
    if( src_byte_i + byte_n > TM2x·byte_n(src) ) continue_via_trampoline bad_src_index;
    if( dst_byte_i + byte_n > TM2x·byte_n(dst) ) continue_via_trampoline bad_dst_index;
    memcpyn(TM2x·byte_0_pt(dst) + dst_byte_i ,TM2x·byte_0_pt(dst) + src_byte_i ,byte_n);
  }

  // A bad index is either one that overlflows the address space for either source or
  // destination, or one that is off the end of the source array.
TM2x·copy_contiguous_elements·args
  TM2x·F_PREFIX SequencePtr TM2x·copy_contiguous_elements
   ( TM2x·Tape *src
    ,address_t src_element_i
    ,TM2x·Tape *dst
    ,address_t dst_element_i
    ,address_t element_n  // index of nth element of the copy region
    ,address_t element_byte_n
    ,SequencePtr nominal
    ,SequencePtr alloc_fail
    ,SequencePtr bad_src_index
    ,SequencePtr bad_dst_index
    ){

    Sequence nominal ,gt_address_n;
    address_t src_byte_i;
    continue_into mul_ext(src_element_i ,element_byte_n ,&src_byte_i ,&&nominal ,&&gt_address_n);

    nominal:{ 
      Sequence nominal;
      address_t dst_byte_i;
      continue_into mul_ext(dst_element_i ,element_byte_n ,&dst_byte_i ,&&nominal ,&&gt_address_n);
      nominal:{
        Sequence nominal;
        address_t byte_n;
        continue_into mul_ext(element_n ,element_byte_n ,&byte_n ,&&nominal ,&&gt_address_n);
        nominal:{
          continue_via_trampoline TM2x·copy_contiguous_bytes
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
      }
    }

    gt_address_n:{
      continue_via_trampoline bad_src_index;
    }

  }

//--------------------------------------------------------------------------------
// stack behavior
//
TM2x·push_bytes.args
  TM2x·F_PREFIX SequencePtr TM2x·push_bytes
   ( TM2x·Tape *tape 
    ,void *source_pt 
    ,address_t source_byte_n
    ,SequencePtr nominal
    ,SequencePtr alloc_fail
    ){
    address_t push_pt = TM2x·byte_n(tape) + 1;
    address_t after_byte_n = push_pt + source_byte_n;
    continue_into TM2x·resize_bytes(tape ,after_byte_n ,&&resize_nominal ,&&resize_fail);

    resize_nominal:{
      memcpyn(TM2x·byte_0_pt(tape) + push_pt ,source_pt ,source_byte_n);
      continue_via_trampoline nominal;
    }

    resize_fail:{
      continue_via_trampoline alloc_fail;
    }
  }

  // use this to block push an entire array of bytes 
SequencePtr TM2x·push·args
  TM2x·F_PREFIX SequencePtr TM2x·push
   ( TM2x·Tape *tape 
    ,void *element_base_pt
    ,address_t element_byte_n
    ,SequencePtr nominal
    ,SequencePtr alloc_fail
    ){
    continue_via_trampoline TM2x·push_bytes(tape ,element_base_pt ,element_byte_n ,nominal  ,alloc_fail);
  }

  // use this to block push an entire array of elements
TM2x·push_elements·args
  TM2x·F_PREFIX SequencePtr TM2x·push_elements
   ( TM2x·Tape *tape 
    ,void *base_pt
    ,address_t element_n 
    ,address_t element_byte_n 
    ,SequencePtr nominal
    ,SequencePtr alloc_fail
    ,SequencePtr bad_index
    ){
    address_t byte_n;
    continue_into mul_ext(element_n ,element_byte_n ,&byte_n ,&&mul_ext·nominal ,&&mul_ext·gt_address_n);
    mul_ext·nominal:{
      continue_via_trampoline TM2x·push(tape ,base_pt ,byte_n ,nominal  ,alloc_fail);
    }
    mul_ext·gt_address_n:{
      continue_via_trampoline bad_index;
    }
  }

  // use this to block push the contents of another TM2x
TM2x·push_TM2x·args
  TM2x·F_PREFIX SequencePtr TM2x·push_TM2x
   ( TM2x·Tape *tape 
    ,TM2x·Tape *tape_source
    ,SequencePtr nominal
    ,SequencePtr alloc_fail
    ){
    continue_via_trampoline TM2x·push(tape ,tape_source->base_pt ,tape_source->byte_n ,nominal  ,alloc_fail);
  }

  #define TM2x·Push(tape ,src_element ,nominal ,alloc_fail)\
    TM2x·push(tape ,&src_element ,byte_n_of(typeof(src_element)) ,nominal ,alloc_fail)


  TM2x·F_PREFIX SequencePtr TM2x·pop·args
  ( TM2x·Tape *tape
    ,address_t element_byte_n
    ,SequencePtr nominal
    ,SequencePtr pop_last
    ,SequencePtr alloc_fail
    ){

    address_t before_byte_n = TM2x·byte_n(tape);
    if( before_byte_n <= element_byte_n ) continue_via_trampoline pop_last;
    address_t after_byte_n = before_byte_n - element_byte_n - 1;
    TM2x·resize_bytes(tape ,after_byte_n ,&&resize_nominal ,&&alloc_fail);
    resize_nominal:{
      continue_via_trampoline nominal;
    }
    alloc_fail:{
      continue_via_trampoline alloc_fail;
    }
  }
  #define TM2x·Pop(tape ,type ,cont_nominal ,cont_pop_last)\
    TM2x·pop(tape ,byte_n_of(type) ,cont_nominal ,cont_pop_last )

  TM2x·F_PREFIX SequencePtr 
TM2x·read_pop·args
  ( TM2x·Tape *tape 
    ,void *dst_element_pt 
    ,address_t element_byte_n
    ,SequencePtr nominal
    ,SequencePtr pop_last
    ,SequencePtr alloc_fail
    ){
    memcpyn(dst_element_pt, TM2x·element_n_pt(tape ,element_byte_n) ,element_byte_n);
    continue_into TM2x·pop(tape ,element_byte_n ,&&pop_nominal ,&&pop_pop_last ,&&pop_alloc_fail);
    pop_nominal:{ continue_via_trampoline nominal;}
    pop_pop_last:{ continue_via_trampoline pop_last;}
    pop_alloc_fail:{ continue_via_trampoline alloc_fail;}
  }
  #define TM2x·Read_Pop(tape ,dst_element ,nominal ,pop_last ,alloc_fail)           \
    TM2x·read_pop(tape ,&dst_element ,byte_n_of(typeof(dst_element)) ,nominal ,pop_last ,alloc_fail)

#endif

