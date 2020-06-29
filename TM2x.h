#ifndef TM2x_LIB_H
#define TM2x_LIB_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include <limits.h>


//--------------------------------------------------------------------------------
// global stuff
//

  // inlining style for the interface. 'extern inline' will result in the smallest
  // executable.  'static inline' is the simplest for development as there is only
  // one point that needs to be edited.  Giving no value leads to the simplest debugging but
  // will be slower.  The compiler can ignore requests to inline, and it looks like gcc
  // is doing so when the debugging flag is turned on and optimization is turned off.
  //#define TM2x_F_PREFIX
  //#define TM2x_F_PREFIX extern inline
  #define TM2x_F_PREFIX static inline

  // To make inclusive bounds really work we would need some new C library functions.
  // Here are some mockups of those new functions. These provide the correct interface
  // but still call the C library.
  //
    TM2x_F_PREFIX void *mallocn(n){
      void *pt = malloc(n+1); // n+1 might overflow
      assert(pt); // we can not use null pointers as flags if memory 0 is to be addressable
      return pt;
    }
    // without the assert
    // #define mallocn(n) malloc(n+1)

    // the n+1 could overflow:
    #define memcpyn(dst ,src ,n) memcpy(dst ,src ,n+1) 

    // sizeof will overflow if asking for the size of a type that takes up the entire buffer,
    // so instead we just ask for the last byte offset into the buffer.
    #define byte_n_of(type) sizeof(type)-1

  // 'size'is an ambiguous term. size_t is the native address type on a machine, so we
  // will just call it that.
  #define address_t size_t

  // This is a debug feature. To keep the heap clean, all initialized arrays must be
  // TM2x_data_dalloc'ed.  This counter is incremented upon initialization of an array,
  // and it is decremented upon TM2x_data_dalloc.
  extern address_t TM2x_outstanding_cnt;

  // The max index for an element in the initial allocation. The array allocation might
  // later expand and contract, but will never be smaller than this.  A value of n = 3
  // is to say that initially we will have an allocation of 4 elements indexed 0 to 3.
  // The smallest that this value may be set to is 0, for a one element initial allocation.
  #define TM2x_INITIAL_ALLOCATION_ELEMENT_N 3

  // what is a maximum virtual pointer value?  'ULONG_MAX' might be wishful thinking,
  // as OS's do not alway provide a full sized virtual memory space. Note, all pointers
  // to memory originate from the OS, and the OS might not give us predictive control.
  #define TM2x_MEMORY_BYTE_N_PT ULONG_MAX 

//--------------------------------------------------------------------------------
// dynamic array instance 
//    
  typedef struct {
    char *base_pt;
    char *byte_n_pt;
    address_t element_byte_n; // length of an element - 1
  } TM2x;

//------------------------o--------------------------------------------------------
// alloc/init/dealloc
//
  // changing units in array size computation, (a_n + 1) (b_n + 1) - 1
  TM2x_F_PREFIX address_t TM2x_mulns(address_t a_n , address_t b_n){
    return a_n * b_n + a_n + b_n;
  }

  TM2x_F_PREFIX address_t TM2x_INITIAL_ALLOCATION_BYTE_N(address_t element_byte_n){
    return mulns(TM2x_INITIAL_ALLOCATION_ELEMENT_N ,element_byte_n);
  }

  // After initialiazation there is one data element, and an allocation 
  // for TM2x_INITIAL_ALLOCATION_ELEMENT_N more elements.
  // need to add limit checks, because init could fail to fit, and return a bool
  TM2x_F_PREFIX bool TM2x_init(TM2x *dap ,address_t element_byte_n){
    TM2x_outstanding_cnt++;
    dap->element_byte_n = element_byte_n;
    address_t allocation_byte_n = TM2x_INITIAL_ALLOCATION_BYTE_N(element_byte_n);
    dap->base_pt = mallocn(allocation_byte_n);
    assert(dap->base_pt);
    dap->allocation_byte_n_pt = dap->byte_0_pt + allocation_byte_n;
    dap->byte_n_pt = dap->base_pt;  
    return true;
  }
  #define TM2x_Make(da ,type) TM2x TM2x_ ## da ,*da; da = &TM2x_ ## da; TM2x_init(da ,byte_length_of(type)-1);

  // after data_deallocation, the TM2x may be re-initialized and used again
  TM2x_F_PREFIX void TM2x_data_dealloc(TM2x *dap){
    free(dap->byte_0_pt);
    TM2x_outstanding_cnt--;
  }

  TM2x_F_PREFIX address_t TM2x_outstanding(TM2x *dap){
    return TM2x_outstanding_cnt;
  }

  // for dynammic allocation of TM2xs:
  TM2x_F_PREFIX TM2x *TM2x_alloc(address_t element_byte_n){
    TM2x *dap = mallocn(byte_n_of(TM2x));
    TM2x_init(dap ,element_byte_n);
    return dap;
  }
  TM2x_F_PREFIX void TM2x_dealloc(TM2x *dap){
    TM2x_data_dealloc(dap);
    free(dap);
  }

//--------------------------------------------------------------------------------
// instance interface use this interface for the rest of the code. Do not refer to the
// instance directly.  This frees us to change the instance implementation later.
//

  // base pointers
  TM2x_F_PREFIX address_t TM2x_byte_0_pt(TM2x *dap){
    return dap->base_pt;
  }
  TM2x_F_PREFIX address_t TM2x_element_0_pt(TM2x *dap){
    return dap->base_pt;
  }
  TM2x_F_PREFIX address_t TM2x_allocation_byte_0_pt(TM2x *dap){
    return dap->base_pt;
  }

  // max offsets
  TM2x_F_PREFIX address_t TM2x_element_byte_n(TM2x *dap){
    return dap->element_byte_n;
  }
  TM2x_F_PREFIX address_t TM2x_byte_n(TM2x *dap){
    return dap->byte_n_pt - dap->byte_0_pt;
  }
  TM2x_F_PREFIX address_t TM2x_allocation_byte_n(TM2x *dap){
    return dap->allocation_byte_n_pt - dap->byte_0_pt;
  }
  // element_byte_n + 1 must be representable:
  TM2x_F_PREFIX address_t TM2x_element_n(TM2x *dap){
    return dap->byte_n/(dap->element_byte_n + 1);
  }

  // nth pointers
  TM2x_F_PREFIX address_t TM2x_byte_n_pt(TM2x *dap){
    return dap->byte_n_pt;
  }
  TM2x_F_PREFIX address_t TM2x_element_n_pt(TM2x *dap){
    return dap->byte_n_pt - dap->element_byte_n;
  }
  TM2x_F_PREFIX address_t TM2x_allocation_byte_n_pt(TM2x *dap){
    return dap->allocation_byte_n_pt;
  }

  // A private method.  Makes a new allocation, moves the data over, sets the array pointers
  // to the new allocation. The caller is under contract to assure the data fits in the
  // new allocation.
  TM2x_F_PREFIX void __TM2x_adjust(TM2x *dap ,address_t new_allocation_n){
    char *new_data_allocation_pt = mallocn( new_allocation_n );
    address_t byte_n = TM2x_byte_n(dap);
    memcpyn( new_data_allocation_pt ,TM2x_byte_0_pt(dap) ,byte_n);
    free(TM2x_allocation_byte_0_pt(dap));
    dap->base_pt = new_data_allocation_pt;
    dap->byte_n_pt = new_data_allocation_pt + byte_n;
    dap->allocation_byte_n_pt = new_data_allocation_pt + new_allocation_n;
  }



//--------------------------------------------------------------------------------
// change allocation size
//
  TM2x_F_PREFIX address_t TM2x_expand(TM2x *dap){
    address_t max_expansion = TM2x_MEMORY_BYTE_N_PT - TM2x_allocation_byte_n_pt(dap);
    if( max_expansion == 0 ) return 0;
    // we now know that TM2x_alloction_byte_n is less than memory_byte_n
    address_t desired_expansion = TM2x_allocation_byte_n(dap) + 1; // we want to double the allocation, m1 == -1
    if( desired_expansion > max_expansion ) desired_expansion = max_expansion;
    __TM2x_adjust(dap ,TM2x_allocation_byte_n(dap) + desired_expansion);
    return desired_expansion;
  }
  TM2x_F_PREFIX bool TM2x_collapse(TM2x *dap){
    if( TM2x_byte_n(dap) <= TM2x_allocation_byte_n(dap) << 2 ){ // then collapse
      address_t initial_allocation_byte_n = TM2x_INITIAL_ALLOCATION_BYTE_N(TM2x_element_byte_n(dap));
      if( TM2x_allocation_byte_n(dap) == iniital_allocation_byte_n ) return false;
      address_t collapse_to = TM2x_allocation_byte_n(dap) << 1;
      if( collapse_to < initial_allocation_byte_n) collapse_to = initial_allocation_byte_n;
      __TM2x_adjust(dap ,collapse_to);
      return true;
    }
    return false;
  }

  // the original array top should be saved before calling this.
  // if doubling expansion does not work, 
  TM2x_F_PREFIX bool TM2x_push_alloc(TM2x *dap ,address_t requested_expansion_element_n){
    address_t data_expansion_byte_n = TM2x_mulns(element_n ,TM2x_element_byte_n(dap));
    


    address_t expansion, total_expansion=0;
    do{
      expansion = TM2x_expand(dap);
      total_expansion += expansion;
    }while( expansion != 0 && total_expansion <= requested_expansion_byte_n );
    return expansion != 0;
  }
  TM2x_F_PREFIX bool TM2x_push_write(TM2x *dap ,void *src_element_pt){
    if
      ( 
       TM2x_MEMORY_BYTE_N_PT - TM2x_allocation_byte_n_pt(dap) <= TM2x_element_byte_n(dap)
       ||
       (TM2x_byte_n_pt(dap) + TM2x_element_byte_n(dap) + 1) >= TM2x_allocation_byte_n_pt(dap)
       &&
       !TM2x_push_alloc(dap ,0)
        )
      return false;

    memcpyn(TM2x_element_n_pt(dap), src_element_pt, TM2x_element_byte_n(dap));
    return true;
  }

  // the read will always succeed, but the pop might not
  TM2x_F_PREFIX bool TM2x_pop_read(TM2x *dap ,void *dst_element_pt){
    memcpyn(dst_element_pt, TM2x_element_n_pt(dap) ,TM2x_element_byte_n(dap));
    if( TM2x_byte_0_pt(dap) == TM2x_byte_n_pt(dap) ) return false;
    
    if( TM2x_empty(dap) ) return false;
    char *src_element_pt = dap->byte_n_pt - TM2x_element_byte_n(dap);
    if( dst_element_pt ) 
    dap->byte_np1_pt = src_element_pt;

    // if the array fits in 1/4 of the allocation, then collapse the alloction by 1/2
    address_t allocation_byte_length_collapse_threshold = TM2x_allocation_byte_length(dap) >> 2;
    if( TM2x_byte_length(dap) <= allocation_byte_length_collapse_threshold ) TM2x_collapse(dap);

    return true;
  }
  TM2x_F_PREFIX bool TM2x_pop(TM2x *dap){
    return TM2x_pop_read(dap, NULL);
  }

//--------------------------------------------------------------------------------
// indexing
//
  TM2x_F_PREFIX address_t TM2x_least_index(TM2x *dap){
    return 0;
  }
  TM2x_F_PREFIX address_t TM2x_greatest_index(TM2x *dap){
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
  TM2x_F_PREFIX void *TM2x_at_index_pt(TM2x *dap ,address_t index){
    return dap->byte_0_pt + TM2x_element_byte_length(dap) * index;
  }

  TM2x_F_PREFIX bool TM2x_read(TM2x *dap ,address_t index ,void *dst_element_pt){
    char *src_element_pt = TM2x_at_index_pt(dap ,index);
    if( src_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(dap));
    return true;
  }
  #define TM2x_Read(dap ,index ,x) assert(TM2x_read ,index ,&x))

  TM2x_F_PREFIX bool TM2x_write(TM2x *dap ,address_t index ,void *src_element_pt){
    char *dst_element_pt = TM2x_at_index_pt(dap ,index);
    if( dst_element_pt >= dap->byte_np1_pt ) return false;
    memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(dap));
    return true;
  }
  #define TM2x_Write(dap ,index ,x) assert(TM2x_write ,index ,&x))


#endif

