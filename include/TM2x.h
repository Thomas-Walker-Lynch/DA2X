#ifndef TM2x·LIB_H
#define TM2x·LIB_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include "misc.h"
#include "Inclusive.h"
#include "Conveyance.h"

//--------------------------------------------------------------------------------
// misc
//    
  extern address_t TM2x·constructed_count;

  #define MINIMUM_ALLOC_EXTENT 15

  INLINE_PREFIX address_t power_2_extent_w_lower_bound(address_t byte_n){
    if( byte_n < MINIMUM_ALLOC_EXTENT) return MINIMUM_ALLOC_EXTENT;
    return power_2_extent(byte_n);
  }




//--------------------------------------------------------------------------------
// The TM2x dynamic array header struct
//   .. does the mutex lock variable belongs here, or at L2? Perhaps here,
//   because look at all the trouble we have already gone through to make
//   this thread safe.
  typedef struct {
    char *base_pt;
    address_t byte_n;
  } TM2x;

//--------------------------------------------------------------------------------
// adjectives
//
// Use these adjectives rather than accessing the header struct directly.
//

  // base pointers
  INLINE_PREFIX char *TM2x·byte_0_pt(TM2x *tape){
    return tape->base_pt;
  }
  INLINE_PREFIX void *TM2x·element_0_pt(TM2x *tape){
    return tape->base_pt;
  }

  // max offsets
  INLINE_PREFIX address_t TM2x·byte_n(TM2x *tape){
    return tape->byte_n;
  }
  // The index of the last element in the array.  Note that the
  // (element_byte_n + 1) in the denominator must be representable:
  INLINE_PREFIX address_t TM2x·element_n(TM2x *tape ,address_t element_byte_n){
    return tape->byte_n/(element_byte_n + 1);
  }

  // nth pointers
  INLINE_PREFIX char *TM2x·byte_n_pt(TM2x *tape){
    return tape->base_pt + tape->byte_n;
  }
  INLINE_PREFIX void *TM2x·element_n_pt(TM2x *tape ,address_t element_byte_n){
    return TM2x·byte_n_pt(tape) - element_byte_n;
  }
  #define TM2x·Element_N_Pt(tape ,type) TM2x·element_n_pt(tape ,byte_n_of(type))


//--------------------------------------------------------------------------------
// allocation
//
  // tape becomes a pointer to a static allocation of a TM2x struct
  #define TM2x·AllocStatic(tape) TM2x TM2x· ## tape ,*tape; tape = &TM2x· ## tape;

  INLINE_PREFIX address_t TM2x·constructed(TM2x *tape){
    return TM2x·constructed_count;
  }


#endif

