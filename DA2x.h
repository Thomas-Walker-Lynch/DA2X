#ifndef DA2x_LIB_H
#define DA2x_LIB_H
#include <stdlib.h> // byte_length_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>

#define byte_length_t size_t
#define byte_length_of sizeof

//--------------------------------------------------------------------------------
// global stuff
//

  // referenced in DA2x_init and DA2x_data_dealloc, used to count the number of
  // dynamic arrays that have allocations on the heap. Useful for debug, easily removed.
  extern byte_length_t DA2x_outstanding_cnt;

  // inlining the interface
  //#define DA2x_F_PREFIX
  //#define DA2x_F_PREFIX extern inline
  #define DA2x_F_PREFIX static inline

  // We guarantee that the array byte_length is always an non-negative integer multiple of the
  // element_byte_length.  
  //
    #define DA2x_INITIAL_ALLOCATION_ELEMENT_LENGTH 4 


//--------------------------------------------------------------------------------
// doubling array instance
//
  typedef struct {
    char *byte_0_pt; // byte 0 of both the array and the allocation
    char *byte_np1_pt; // one byte beyond the end of the array
    char *allocation_byte_np1_pt; // one byte beyond the end of the allocation
    byte_length_t element_byte_length;
  } DA2x;

//--------------------------------------------------------------------------------
// alloc/init/dealloc
//
  DA2x_F_PREFIX DA2x *DA2x_init(DA2x *dap ,byte_length_t element_byte_length){
    DA2x_outstanding_cnt++;
    dap->element_byte_length = element_byte_length;
    byte_length_t allocation_byte_length = DA2x_INITIAL_ALLOCATION_ELEMENT_LENGTH * element_byte_length;
    dap->byte_0_pt = malloc(allocation_byte_length);
    assert(dap->byte_0_pt);
    dap->allocation_byte_np1_pt = dap->byte_0_pt + allocation_byte_length;
    dap->byte_np1_pt = dap->byte_0_pt; 
    return dap;
  }
  #define DA2x_Make(da ,type) DA2x DA2x_ ## da ,*da; da = &DA2x_ ## da; DA2x_init(da ,byte_length_of(type));

  // after data_dallocation, the DA2x may be re-initialized and used again
  DA2x_F_PREFIX void DA2x_data_dealloc(DA2x *dap){
    free(dap->byte_0_pt);
    DA2x_outstanding_cnt--;
  }

  DA2x_F_PREFIX byte_length_t DA2x_outstanding(DA2x *dap){
    return DA2x_outstanding_cnt;
  }

  // for dynammic allocation of DA2xs:
  DA2x_F_PREFIX DA2x *DA2x_alloc(byte_length_t element_byte_length){
    DA2x *dap = malloc(byte_length_of(DA2x));
    DA2x_init(dap ,element_byte_length);
    return dap;
  }
  DA2x_F_PREFIX void DA2x_dealloc(DA2x *dap){
    DA2x_data_dealloc(dap);
    free(dap);
  }

//--------------------------------------------------------------------------------
// adjectives
//
  DA2x_F_PREFIX byte_length_t DA2x_element_byte_length(DA2x *dap){
    return dap->element_byte_length;
  }
  DA2x_F_PREFIX byte_length_t DA2x_byte_length(DA2x *dap){
    return dap->byte_np1_pt - dap->byte_0_pt;
  }
  DA2x_F_PREFIX bool DA2x_empty(DA2x *dap){
    return dap->byte_np1_pt == dap->byte_0_pt;
  }
  DA2x_F_PREFIX byte_length_t DA2x_allocation_byte_length(DA2x *dap){
    return dap->allocation_byte_np1_pt - dap->byte_0_pt;
  }

//--------------------------------------------------------------------------------
// change byte_length
//
  // private
  DA2x_F_PREFIX void __DA2x_adjust(DA2x *dap ,byte_length_t new_allocation_byte_length){
    byte_length_t data_byte_length = DA2x_byte_length(dap);
    char *new_data_allocation_pt = malloc( new_allocation_byte_length );
    assert( new_data_allocation_pt );
    memcpy( new_data_allocation_pt ,dap->byte_0_pt ,data_byte_length );
    free(dap->byte_0_pt);
    dap->byte_0_pt = new_data_allocation_pt;
    dap->byte_np1_pt = new_data_allocation_pt + data_byte_length;
    dap->allocation_byte_np1_pt = new_data_allocation_pt + new_allocation_byte_length;
  }
  DA2x_F_PREFIX void DA2x_expand(DA2x *dap){
    byte_length_t new_allocation_byte_length = DA2x_allocation_byte_length(dap) << 1;
    __DA2x_adjust(dap ,new_allocation_byte_length);
  }
  DA2x_F_PREFIX void DA2x_collapse(DA2x *dap){
    byte_length_t initial_allocation_byte_length = DA2x_INITIAL_ALLOCATION_ELEMENT_LENGTH * DA2x_element_byte_length(dap);
    byte_length_t new_allocation_byte_length = DA2x_allocation_byte_length(dap) >> 1;
    if( new_allocation_byte_length < initial_allocation_byte_length || dap->byte_0_pt + new_allocation_byte_length < dap->byte_np1_pt )
      return;
    __DA2x_adjust(dap ,new_allocation_byte_length);
  }

  DA2x_F_PREFIX char *DA2x_push_alloc(DA2x *dap ,byte_length_t count){
    byte_length_t push_byte_length = count * DA2x_element_byte_length(dap);
    while( dap->byte_np1_pt + push_byte_length > dap->allocation_byte_np1_pt ) DA2x_expand(dap);
    char *element_pt = dap->byte_np1_pt;
    dap->byte_np1_pt += push_byte_length;
    return element_pt;
  }
  DA2x_F_PREFIX char *DA2x_push_write(DA2x *dap, void *src_element_pt){
    char *dst_element_pt = DA2x_push_alloc(dap ,1);
    memcpy(dst_element_pt, src_element_pt, DA2x_element_byte_length(dap));
    return dst_element_pt;
  }

  DA2x_F_PREFIX bool DA2x_pop_read(DA2x *dap, void *dst_element_pt){
    if( DA2x_empty(dap) ) return false;
    char *src_element_pt = dap->byte_np1_pt - DA2x_element_byte_length(dap);
    if( dst_element_pt ) memcpy(dst_element_pt, src_element_pt, DA2x_element_byte_length(dap));
    dap->byte_np1_pt = src_element_pt;

    // if the array fits in 1/4 of the allocation, then collapse the alloction by 1/2
    byte_length_t allocation_byte_length_collapse_threshold = DA2x_allocation_byte_length(dap) >> 2;
    if( DA2x_byte_length(dap) <= allocation_byte_length_collapse_threshold ) DA2x_collapse(dap);

    return true;
  }
  DA2x_F_PREFIX bool DA2x_pop(DA2x *dap){
    return DA2x_pop_read(dap, NULL);
  }

//--------------------------------------------------------------------------------
// indexing
//
  DA2x_F_PREFIX byte_length_t DA2x_least_index(DA2x *dap){
    return 0;
  }
  DA2x_F_PREFIX byte_length_t DA2x_greatest_index(DA2x *dap){
    return DA2x_byte_length(dap) / DA2x_element_byte_length(dap);
  }
  DA2x_F_PREFIX void *DA2x_at_least_index_pt(DA2x *dap){
    return dap->byte_0_pt;
  }
  DA2x_F_PREFIX void *DA2x_at_greatest_index_pt(DA2x *dap){
    return dap->allocation_byte_np1_pt - DA2x_element_byte_length(dap);
  }
  DA2x_F_PREFIX void *DA2x_at_supremum_index_pt(DA2x *dap){
    return dap->allocation_byte_np1_pt;
  }

  // returns pointer to element at given index
  DA2x_F_PREFIX void *DA2x_at_index_pt(DA2x *dap ,byte_length_t index){
    return dap->byte_0_pt + DA2x_element_byte_length(dap) * index;
  }

  DA2x_F_PREFIX bool DA2x_read(DA2x *dap ,byte_length_t index ,void *dst_element_pt){
    char *src_element_pt = DA2x_at_index_pt(dap ,index);
    if( src_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, DA2x_element_byte_length(dap));
    return true;
  }
  #define DA2x_Read(dap ,index ,x) assert(DA2x_read ,index ,&x))

  DA2x_F_PREFIX bool DA2x_write(DA2x *dap ,byte_length_t index ,void *src_element_pt){
    char *dst_element_pt = DA2x_at_index_pt(dap ,index);
    if( dst_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, DA2x_element_byte_length(dap));
    return true;
  }
  #define DA2x_Write(dap ,index ,x) assert(DA2x_write ,index ,&x))


#endif

