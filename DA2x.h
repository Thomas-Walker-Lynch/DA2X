#ifndef DA2x_LIB_H
#define DA2x_LIB_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>


//--------------------------------------------------------------------------------
// global stuff
//

  // referenced in DA2x_init and DA2x_data_dealloc, used to count the number of
  // dynamic arrays that have allocations on the heap. Useful for debug, easily removed.
  extern size_t DA2x_outstanding_cnt;

  // inlining the interface
  //#define DA2x_F_PREFIX
  //#define DA2x_F_PREFIX extern inline
  #define DA2x_F_PREFIX static inline

  // We guarantee that the array size is always an non-negative integer multiple of the
  // element_size.  
  //
    #define DA2x_INITIAL_ALLOCATION_LENGTH 4 


//--------------------------------------------------------------------------------
// doubling array instance
//
  typedef struct {
    char *byte_0_pt; // byte 0 of both the array and the allocation
    char *byte_np1_pt; // one byte beyond the end of the array
    char *allocation_byte_np1_pt; // one byte beyond the end of the allocation
    size_t element_size;
  } DA2x;

//--------------------------------------------------------------------------------
// alloc/init/dealloc
//
  DA2x_F_PREFIX DA2x *DA2x_init(DA2x *dap ,size_t element_size){
    DA2x_outstanding_cnt++;
    dap->element_size = element_size;
    size_t allocation_size = DA2x_INITIAL_ALLOCATION_LENGTH * element_size;
    dap->byte_0_pt = malloc(allocation_size);
    assert(dap->byte_0_pt);
    dap->allocation_byte_np1_pt = dap->byte_0_pt + allocation_size;
    dap->byte_np1_pt = dap->byte_0_pt; 
    return dap;
  }

  // after data_dallocation, the DA2x may be re-initialized and used again
  DA2x_F_PREFIX void DA2x_data_dealloc(DA2x *dap){
    free(dap->byte_0_pt);
    DA2x_outstanding_cnt--;
  }

  DA2x_F_PREFIX size_t DA2x_outstanding(DA2x *dap){
    return DA2x_outstanding_cnt;
  }

  // for dynammic allocation of DA2xs:
  DA2x_F_PREFIX DA2x *DA2x_alloc(size_t element_size){
    DA2x *dap = malloc(sizeof(DA2x));
    DA2x_init(dap ,element_size);
    return dap;
  }
  DA2x_F_PREFIX void DA2x_dealloc(DA2x *dap){
    DA2x_data_dealloc(dap);
    free(dap);
  }

//--------------------------------------------------------------------------------
// adjectives
//
  DA2x_F_PREFIX size_t DA2x_element_size(DA2x *dap){
    return dap->element_size;
  }
  DA2x_F_PREFIX size_t DA2x_size(DA2x *dap){
    return dap->byte_np1_pt - dap->byte_0_pt;
  }
  DA2x_F_PREFIX bool DA2x_empty(DA2x *dap){
    return dap->byte_np1_pt == dap->byte_0_pt;
  }
  DA2x_F_PREFIX size_t DA2x_allocation_size(DA2x *dap){
    return dap->allocation_byte_np1_pt - dap->byte_0_pt;
  }

//--------------------------------------------------------------------------------
// change size
//
  // private
  DA2x_F_PREFIX void __DA2x_adjust(DA2x *dap ,size_t new_allocation_size){
    size_t data_size = DA2x_size(dap);
    char *new_data_allocation_pt = malloc( new_allocation_size );
    assert( new_data_allocation_pt );
    memcpy( new_data_allocation_pt ,dap->byte_0_pt ,data_size );
    free(dap->byte_0_pt);
    dap->byte_0_pt = new_data_allocation_pt;
    dap->byte_np1_pt = new_data_allocation_pt + data_size;
    dap->allocation_byte_np1_pt = new_data_allocation_pt + new_allocation_size;
  }
  DA2x_F_PREFIX void DA2x_expand(DA2x *dap){
    size_t new_allocation_size = DA2x_allocation_size(dap) << 1;
    __DA2x_adjust(dap ,new_allocation_size);
  }
  DA2x_F_PREFIX void DA2x_contract(DA2x *dap){
    size_t initial_allocation_size = DA2x_INITIAL_ALLOCATION_LENGTH * DA2x_element_size(dap);
    size_t new_allocation_size = DA2x_allocation_size(dap) >> 1;
    if( new_allocation_size < initial_allocation_size || dap->byte_0_pt + new_allocation_size < dap->byte_np1_pt )
      return;
    __DA2x_adjust(dap ,new_allocation_size);
  }

  DA2x_F_PREFIX char *DA2x_push_alloc(DA2x *dap){
    if( dap->byte_np1_pt + DA2x_element_size(dap) > dap->allocation_byte_np1_pt ) DA2x_expand(dap);
    char *element_pt = dap->byte_np1_pt;
    dap->byte_np1_pt += DA2x_element_size(dap);
    return element_pt;
  }
  DA2x_F_PREFIX char *DA2x_push_write(DA2x *dap, void *src_element_pt){
    char *dst_element_pt = DA2x_push_alloc(dap);
    memcpy(dst_element_pt, src_element_pt, DA2x_element_size(dap));
    return dst_element_pt;
  }

  DA2x_F_PREFIX bool DA2x_pop_read(DA2x *dap, void *dst_element_pt){
    if( DA2x_empty(dap) ) return false;
    char *src_element_pt = dap->byte_np1_pt - DA2x_element_size(dap);
    if( dst_element_pt ) memcpy(dst_element_pt, src_element_pt, DA2x_element_size(dap));
    dap->byte_np1_pt = src_element_pt;

    // if the array fits in 1/4 of the allocation, then contract the alloction by 1/2
    size_t allocation_size_contract_threshold = DA2x_allocation_size(dap) >> 2;
    if( DA2x_size(dap) <= allocation_size_contract_threshold ) DA2x_contract(dap);

    return true;
  }
  DA2x_F_PREFIX bool DA2x_pop(DA2x *dap){
    return DA2x_pop_read(dap, NULL);
  }

//--------------------------------------------------------------------------------
// indexing
//
  DA2x_F_PREFIX size_t DA2x_least_index(DA2x *dap){
    return 0;
  }
  DA2x_F_PREFIX size_t DA2x_greatest_index(DA2x *dap){
    return DA2x_size(dap) / DA2x_element_size(dap);
  }
  DA2x_F_PREFIX void *DA2x_at_least_index_pt(DA2x *dap){
    return dap->byte_0_pt;
  }
  DA2x_F_PREFIX void *DA2x_at_greatest_index_pt(DA2x *dap){
    return dap->allocation_byte_np1_pt - DA2x_element_size(dap);
  }
  DA2x_F_PREFIX void *DA2x_at_supremum_index_pt(DA2x *dap){
    return dap->allocation_byte_np1_pt;
  }

  // returns pointer to element at given index
  DA2x_F_PREFIX void *DA2x_at_index_pt(DA2x *dap ,size_t index){
    return dap->byte_0_pt + DA2x_element_size(dap) * index;
  }

  DA2x_F_PREFIX bool DA2x_read(DA2x *dap ,size_t index ,void *dst_element_pt){
    char *src_element_pt = DA2x_at_index_pt(dap ,index);
    if( src_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, DA2x_element_size(dap));
    return true;
  }
  DA2x_F_PREFIX bool DA2x_write(DA2x *dap ,size_t index ,void *src_element_pt){
    char *dst_element_pt = DA2x_at_index_pt(dap ,index);
    if( dst_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, DA2x_element_size(dap));
    return true;
  }


#endif

