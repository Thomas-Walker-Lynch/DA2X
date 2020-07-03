#ifndef TM2x_LIB_H
#define TM2x_LIB_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include <stdint.h> // int64_t
#include <limits.h>


/*--------------------------------------------------------------------------------
   global stuff

  To make inclusive bounds really work we would need some new C library functions.
  In this sections I provide some mockups.  The implementations of these mockups
  might not respect inclusive bound math.

  There are three options for the inlining style for the interface: no-inlining, 'extern
  inline', and 'static inilne'.  No inlining is the simplest, but there is no performance
  advantage.  The compiler can ignore requests to inline, and it looks like gcc is doing
  so when the debugging flag is turned on and optimization is turned off. 'static inline'
  generates file scope code if it is needed.  This is simplest inlining approach for
  development because there is only one declaration of each function to edit.  'extern
  line' will only generate one version of functions that are not inlined, and share it
  everywhere it is needed. The non-inline versions of the functions have to be compiled
  separately and made available for linking.

  memory_byte_n is the largest address that may be used to access a byte from memory.
  If this array is implemented over virtual memory, that migth be the largest virtual memory
  address, i.e. UINT64_MAX.  That is what I have put here.

*/

  //
  //#define TM2x_F_PREFIX static
  //#define TM2x_F_PREFIX extern inline
  #define TM2x_F_PREFIX static inline

  // this particular machine has 64 bit addresses (bit indexed 0 to 63)
  #define address_t uint64_t
  #define address_bit_length 64
  #define memory_byte_n UINT64_MAX

  // if an instance of the given type is put in memory what is byte_n (offset of the last byte)?
  #define byte_n_of(type) sizeof(type)-1

  TM2x_F_PREFIX address_t binary_interval_inclusive_upper_bound(address_t byte_n){
    if( byte_n == 0 ) return 1;
    return (1 << (address_bit_length - __builtin_clz(byte_n))) - 1;
  }

  TM2x_F_PREFIX void *mallocn(address_t n){
    void *pt = malloc(n+1); // n+1 might overflow
    assert(pt); // in our model we can not use null pointers because address 0 can hold an element ..
    return pt;
  }
  // without the assert
  // #define mallocn(n) malloc(n+1)

  // the n+1 could overflow:
  #define memcpyn(dst ,src ,n) memcpy(dst ,src ,n+1) 
  #define memcmpn(e0 ,e1 ,n) memcmp(e0 ,e1 ,n+1) 
  #define strncmpn(e0 ,e1 ,n) strncmp(e0 ,e1 ,n+1)

  // This is a debug feature. To keep the heap clean all initialized arrays must be
  // TM2x_data_dalloc'ed.  This counter is incremented upon initialization of an array,
  // and it is decremented upon TM2x_data_dalloc.
  extern address_t TM2x_initialized_cnt;


//--------------------------------------------------------------------------------
// dynamic array instance 
//    
  typedef struct {
    char *base_pt;
    address_t byte_n;
  } TM2x;

//--------------------------------------------------------------------------------
// alloc/init/dealloc
//
  // change unit of measure
  TM2x_F_PREFIX address_t TM2x_mulns(address_t a_n , address_t b_n){
    return a_n * b_n + a_n + b_n;
  }

  // Need to add limit checks because an init sized array might fail to fit in memory.
  // element_n is the maximum index for the initial data array
  // returns true when initialization succeeds
  TM2x_F_PREFIX bool __TM2x_init(TM2x *tape ,address_t byte_n ){
    TM2x_initialized_cnt++; // to assist with debugging
    tape->byte_n = byte_n;
    address_t allocation_byte_n = binary_interval_inclusive_upper_bound(byte_n);
    tape->base_pt = mallocn(allocation_byte_n);
    return true;
  }
  TM2x_F_PREFIX bool TM2x_init(TM2x *tape ,address_t element_n, address_t element_byte_n ){
    address_t byte_n = TM2x_mulns(element_byte_n ,element_n);
    return __TM2x_init(tape ,byte_n );
  }
  #define TM2x_Make(da ,element_n ,type) TM2x TM2x_ ## da ,*da; da = &TM2x_ ## da; assert(TM2x_init(da ,element_n ,byte_n_of(type)));

  TM2x_F_PREFIX bool TM2x_init_write(TM2x *tape ,void *element_pt, address_t element_byte_n ){
    TM2x_init(tape ,0 ,element_byte_n );
    memcpyn(tape->base_pt, element_pt, element_byte_n);
    return true;
  }

  // tape_new is a raw TM2x struct
  // shallow copy tape_src elements to tape_new
  // need a version of this where the second argument is an hd, takes the tail from another list == drop
  TM2x_F_PREFIX bool TM2x_init_copy
  (
   TM2x *tape
   ,TM2x *tape_src
   ,address_t element_byte_n
   ){
    address_t byte_n = tape_src->byte_n;
    bool alloc_success = __TM2x_init(tape ,byte_n);
    if( alloc_success ) memcpyn(tape->base_pt ,tape_src->base_pt ,byte_n);
    return alloc_success;
  }

  // after data_deallocation, the TM2x may be re-initialized and used again
  TM2x_F_PREFIX void TM2x_data_dealloc(TM2x *tape){
    free(tape->base_pt);
    TM2x_initialized_cnt--;
  }

  TM2x_F_PREFIX address_t TM2x_initialized(TM2x *tape){
    return TM2x_initialized_cnt;
  }

  // for dynammic allocation of TM2xs:
  TM2x_F_PREFIX TM2x *TM2x_alloc(address_t element_n ,address_t element_byte_n){
    TM2x *tape = mallocn(byte_n_of(TM2x));
    assert(TM2x_init(tape ,element_n, element_byte_n));
    return tape;
  }
  TM2x_F_PREFIX void TM2x_dealloc(TM2x *tape){
    TM2x_data_dealloc(tape);
    free(tape);
  }

  // size limit issues, not other comments in this file on this topic
  #ifdef TM2x_TEST
    extern address_t TM2x_test_after_allocation_n;
  #endif
  TM2x_F_PREFIX bool TM2x_resize(TM2x *tape ,address_t after_allocation_n){
    char *after_base_pt = mallocn( after_allocation_n );
    #ifdef TM2x_TEST
      TM2x_test_after_allocation_n = after_allocation_n;
    #endif
    char *before_base_pt = tape->base_pt;
    memcpyn( after_base_pt ,before_base_pt ,tape->byte_n);
    free(before_base_pt);
    tape->base_pt = after_base_pt;
    return true;
  }


//--------------------------------------------------------------------------------
// instance interface use this interface for the rest of the code. Do not refer to the
// instance directly.  This frees us to change the instance implementation later.
//

  // base pointers
  TM2x_F_PREFIX char *TM2x_byte_0_pt(TM2x *tape){
    return tape->base_pt;
  }
  TM2x_F_PREFIX void *TM2x_element_0_pt(TM2x *tape){
    return tape->base_pt;
  }

  // max offsets
  TM2x_F_PREFIX address_t TM2x_byte_n(TM2x *tape){
    return tape->byte_n;
  }
  // The index of the last element in the array.  Note that the
  // (element_byte_n + 1) in the denominator must be representable:
  TM2x_F_PREFIX address_t TM2x_element_n(TM2x *tape ,address_t element_byte_n){
    return tape->byte_n/(element_byte_n + 1);
  }

  // nth pointers
  TM2x_F_PREFIX char *TM2x_byte_n_pt(TM2x *tape){
    return tape->base_pt + tape->byte_n;
  }
  TM2x_F_PREFIX void *TM2x_element_n_pt(TM2x *tape ,address_t element_byte_n){
    return TM2x_byte_n_pt(tape) - element_byte_n;
  }
  #define TM2x_Element_N_Pt(tape ,type) TM2x_element_n_pt(tape ,byte_n_of(type))


//--------------------------------------------------------------------------------
// change allocation size
//
  // Need to add limit checks because an expanded array might fail to fit in memory.
  // Attempts to expands the data portion of the array to accomodate np1 more elements.
  // If the current allocation is not large enough we make a new larger allocation.  If that
  // is not possible, then we return false.  Otherwise we return true.
  // If you need the before expansion top of the array, save that before calling this.
  TM2x_F_PREFIX bool TM2x_push_alloc(TM2x *tape ,address_t requested_expansion_element_n ,address_t element_byte_n){
    address_t requested_expansion_byte_n = TM2x_mulns(requested_expansion_element_n ,element_byte_n);
    address_t before_byte_n = TM2x_byte_n(tape);
    address_t before_allocation_n = binary_interval_inclusive_upper_bound(before_byte_n);
    address_t after_byte_n = before_byte_n + requested_expansion_byte_n + 1;
    tape->byte_n = after_byte_n;
    address_t after_allocation_n = binary_interval_inclusive_upper_bound(after_byte_n);
    if( after_allocation_n > before_allocation_n ) TM2x_resize(tape ,after_allocation_n);
    return true;
  }
  #define TM2x_Push_Alloc(tape ,expansion_element_n ,type) TM2x_push_alloc(tape, expansion_element_n ,byte_n_of(type))

  TM2x_F_PREFIX bool TM2x_push_write(TM2x *tape ,void *src_element_pt ,address_t element_byte_n){
    if( !TM2x_push_alloc(tape ,0 ,element_byte_n) )return false;
    memcpyn(TM2x_element_n_pt(tape ,element_byte_n) ,src_element_pt ,element_byte_n);
    return true;
  }
  #define TM2x_Push_Write(tape ,src_element) TM2x_push_write(tape ,&src_element ,byte_n_of(typeof(src_element)))

  // should make a version to pop off n elements .. in general I need to add array to array ops
  // the read always succeeds, but the pop might not
  TM2x_F_PREFIX bool TM2x_pop_read(TM2x *tape ,void *dst_element_pt ,address_t element_byte_n){
    if(dst_element_pt) memcpyn(dst_element_pt, TM2x_element_n_pt(tape ,element_byte_n) ,element_byte_n);

    // we should never have partial elements, could make this a zero test..
    address_t before_byte_n = TM2x_byte_n(tape);
    if( before_byte_n <= element_byte_n ) return false;

    address_t before_allocation_n = binary_interval_inclusive_upper_bound(before_byte_n);
    address_t after_byte_n = before_byte_n - element_byte_n - 1;
    tape->byte_n = after_byte_n;
    address_t after_allocation_n = binary_interval_inclusive_upper_bound(after_byte_n);
    if( after_allocation_n < before_allocation_n ) TM2x_resize(tape ,after_allocation_n);
    return true;
  }
  #define TM2x_Pop_Read(tape ,dst_element) TM2x_pop_read(tape ,&dst_element ,byte_n_of(typeof(dst_element)))

  // need to add pop and throw away for n elements ...
  TM2x_F_PREFIX bool TM2x_pop(TM2x *tape ,address_t element_byte_n){
    return TM2x_pop_read(tape, NULL ,element_byte_n);
  }
  #define TM2x_Pop(tape ,type) TM2x_pop(tape ,byte_n_of(type))

//--------------------------------------------------------------------------------
// indexing
//   consider using the iterator TM2xHd.h instead of indexes
//
  // returns pointer to element at given index
  TM2x_F_PREFIX void *TM2x_element_i_pt(TM2x *tape ,address_t index ,address_t element_byte_n){
    return TM2x_byte_0_pt(tape) + element_byte_n * index + index;
  }

  TM2x_F_PREFIX bool TM2x_read(TM2x *tape ,address_t index ,void *dst_element_pt ,address_t element_byte_n){
    void *src_element_pt = TM2x_element_i_pt(tape ,index ,element_byte_n);
    if( src_element_pt > TM2x_element_n_pt(tape ,element_byte_n) ) return false;
    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
    return true;
  }
  #define TM2x_Read(tape ,index ,x) TM2x_read(tape ,index ,&x ,byte_n_of(typeof(x)))

  TM2x_F_PREFIX bool TM2x_write(TM2x *tape ,address_t index ,void *src_element_pt ,address_t element_byte_n){
    void *dst_element_pt = TM2x_element_i_pt(tape ,index ,element_byte_n);
    if( dst_element_pt > TM2x_element_n_pt(tape ,element_byte_n) ) return false;
    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
    return true;
  }
  #define TM2x_Write(tape ,index ,x) TM2x_write(tape ,index ,&(x) ,byte_n_of(typeof(x)))


#endif

