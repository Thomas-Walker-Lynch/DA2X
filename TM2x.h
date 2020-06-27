#ifndef TM2x_LIB_H
#define TM2x_LIB_H
#include <stdlib.h> // byte_length_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>

#define byte_length_t size_t
#define byte_length_of sizeof

//--------------------------------------------------------------------------------
// global stuff
//

  // referenced in TM2x_init and TM2x_data_dealloc, used to count the number of
  // dynamic arrays that have allocations on the heap. Useful for debug, easily removed.
  extern byte_length_t TM2x_outstanding_cnt;

  // inlining the interface
  //#define TM2x_F_PREFIX
  //#define TM2x_F_PREFIX extern inline
  #define TM2x_F_PREFIX static inline

  // We guarantee that the array byte_length is always a non-negative integer multiple of the
  // element_byte_length.  
  //
    #define TM2x_INITIAL_ALLOCATION_ELEMENT_LENGTH 4 


//--------------------------------------------------------------------------------
// doubling array instance
//
  typedef struct {
    char *byte_0_pt; // byte 0 of both the array and the allocation
    char *byte_np1_pt; // one byte beyond the end of the array
    char *allocation_byte_np1_pt; // one byte beyond the end of the allocation
    byte_length_t element_byte_length;
  } TM2x;

//--------------------------------------------------------------------------------
// alloc/init/dealloc
//
  TM2x_F_PREFIX TM2x *TM2x_init(TM2x *dap ,byte_length_t element_byte_length){
    TM2x_outstanding_cnt++;
    dap->element_byte_length = element_byte_length;
    byte_length_t allocation_byte_length = TM2x_INITIAL_ALLOCATION_ELEMENT_LENGTH * element_byte_length;
    dap->byte_0_pt = malloc(allocation_byte_length);
    assert(dap->byte_0_pt);
    dap->allocation_byte_np1_pt = dap->byte_0_pt + allocation_byte_length;
    dap->byte_np1_pt = dap->byte_0_pt; 
    return dap;
  }
  #define TM2x_Make(da ,type) TM2x TM2x_ ## da ,*da; da = &TM2x_ ## da; TM2x_init(da ,byte_length_of(type));

  // after data_dallocation, the TM2x may be re-initialized and used again
  TM2x_F_PREFIX void TM2x_data_dealloc(TM2x *dap){
    free(dap->byte_0_pt);
    TM2x_outstanding_cnt--;
  }

  TM2x_F_PREFIX byte_length_t TM2x_outstanding(TM2x *dap){
    return TM2x_outstanding_cnt;
  }

  // for dynammic allocation of TM2xs:
  TM2x_F_PREFIX TM2x *TM2x_alloc(byte_length_t element_byte_length){
    TM2x *dap = malloc(byte_length_of(TM2x));
    TM2x_init(dap ,element_byte_length);
    return dap;
  }
  TM2x_F_PREFIX void TM2x_dealloc(TM2x *dap){
    TM2x_data_dealloc(dap);
    free(dap);
  }

//--------------------------------------------------------------------------------
// adjectives
//
  TM2x_F_PREFIX byte_length_t TM2x_element_byte_length(TM2x *dap){
    return dap->element_byte_length;
  }
  TM2x_F_PREFIX byte_length_t TM2x_byte_length(TM2x *dap){
    return dap->byte_np1_pt - dap->byte_0_pt;
  }
  TM2x_F_PREFIX bool TM2x_empty(TM2x *dap){
    return dap->byte_np1_pt == dap->byte_0_pt;
  }
  TM2x_F_PREFIX byte_length_t TM2x_allocation_byte_length(TM2x *dap){
    return dap->allocation_byte_np1_pt - dap->byte_0_pt;
  }

//--------------------------------------------------------------------------------
// change byte_length
//
  // private
  TM2x_F_PREFIX void __TM2x_adjust(TM2x *dap ,byte_length_t new_allocation_byte_length){
    byte_length_t data_byte_length = TM2x_byte_length(dap);
    char *new_data_allocation_pt = malloc( new_allocation_byte_length );
    assert( new_data_allocation_pt );
    memcpy( new_data_allocation_pt ,dap->byte_0_pt ,data_byte_length );
    free(dap->byte_0_pt);
    dap->byte_0_pt = new_data_allocation_pt;
    dap->byte_np1_pt = new_data_allocation_pt + data_byte_length;
    dap->allocation_byte_np1_pt = new_data_allocation_pt + new_allocation_byte_length;
  }
  TM2x_F_PREFIX void TM2x_expand(TM2x *dap){
    byte_length_t new_allocation_byte_length = TM2x_allocation_byte_length(dap) << 1;
    __TM2x_adjust(dap ,new_allocation_byte_length);
  }
  TM2x_F_PREFIX void TM2x_collapse(TM2x *dap){
    byte_length_t initial_allocation_byte_length = TM2x_INITIAL_ALLOCATION_ELEMENT_LENGTH * TM2x_element_byte_length(dap);
    byte_length_t new_allocation_byte_length = TM2x_allocation_byte_length(dap) >> 1;
    if( new_allocation_byte_length < initial_allocation_byte_length || dap->byte_0_pt + new_allocation_byte_length < dap->byte_np1_pt )
      return;
    __TM2x_adjust(dap ,new_allocation_byte_length);
  }

  TM2x_F_PREFIX char *TM2x_push_alloc(TM2x *dap ,byte_length_t count){
    byte_length_t push_byte_length = count * TM2x_element_byte_length(dap);
    while( dap->byte_np1_pt + push_byte_length > dap->allocation_byte_np1_pt ) TM2x_expand(dap);
    char *element_pt = dap->byte_np1_pt;
    dap->byte_np1_pt += push_byte_length;
    return element_pt;
  }
  TM2x_F_PREFIX char *TM2x_push_write(TM2x *dap ,void *src_element_pt){
    char *dst_element_pt = TM2x_push_alloc(dap ,1);
    memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(dap));
    return dst_element_pt;
  }

  TM2x_F_PREFIX bool TM2x_pop_read(TM2x *dap ,void *dst_element_pt){
    if( TM2x_empty(dap) ) return false;
    char *src_element_pt = dap->byte_np1_pt - TM2x_element_byte_length(dap);
    if( dst_element_pt ) memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(dap));
    dap->byte_np1_pt = src_element_pt;

    // if the array fits in 1/4 of the allocation, then collapse the alloction by 1/2
    byte_length_t allocation_byte_length_collapse_threshold = TM2x_allocation_byte_length(dap) >> 2;
    if( TM2x_byte_length(dap) <= allocation_byte_length_collapse_threshold ) TM2x_collapse(dap);

    return true;
  }
  TM2x_F_PREFIX bool TM2x_pop(TM2x *dap){
    return TM2x_pop_read(dap, NULL);
  }

//--------------------------------------------------------------------------------
// indexing
//
  TM2x_F_PREFIX byte_length_t TM2x_least_index(TM2x *dap){
    return 0;
  }
  TM2x_F_PREFIX byte_length_t TM2x_greatest_index(TM2x *dap){
    return TM2x_byte_length(dap) / TM2x_element_byte_length(dap);
  }
  TM2x_F_PREFIX void *TM2x_at_least_index_pt(TM2x *dap){
    return dap->byte_0_pt;
  }
  TM2x_F_PREFIX void *TM2x_at_greatest_index_pt(TM2x *dap){
    return dap->allocation_byte_np1_pt - TM2x_element_byte_length(dap);
  }
  TM2x_F_PREFIX void *TM2x_at_supremum_index_pt(TM2x *dap){
    return dap->allocation_byte_np1_pt;
  }

  // returns pointer to element at given index
  TM2x_F_PREFIX void *TM2x_at_index_pt(TM2x *dap ,byte_length_t index){
    return dap->byte_0_pt + TM2x_element_byte_length(dap) * index;
  }

  TM2x_F_PREFIX bool TM2x_read(TM2x *dap ,byte_length_t index ,void *dst_element_pt){
    char *src_element_pt = TM2x_at_index_pt(dap ,index);
    if( src_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(dap));
    return true;
  }
  #define TM2x_Read(dap ,index ,x) assert(TM2x_read ,index ,&x))

  TM2x_F_PREFIX bool TM2x_write(TM2x *dap ,byte_length_t index ,void *src_element_pt){
    char *dst_element_pt = TM2x_at_index_pt(dap ,index);
    if( dst_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(dap));
    return true;
  }
  #define TM2x_Write(dap ,index ,x) assert(TM2x_write ,index ,&x))


#endif

