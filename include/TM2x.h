#ifndef TM2x_H
#define TM2x_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include "misc.h"
#include "Inclusive.h"
#include "Sequence.h"

//--------------------------------------------------------------------------------
// The TM2x·Tapedynamic array header struct
//   .. does the mutex lock variable belongs here, or at L2? Perhaps here,
//   because look at all the trouble we have already gone through to make
//   this thread safe.
  typedef struct {
    char *base_pt;
    address_t byte_n;
  } TM2x·Tape;

INLINE_PREFIX TM2x·TapeCopy(


//--------------------------------------------------------------------------------
// adjectives
//
// Use these adjectives rather than accessing the header struct directly.
//

  // base pointers
  INLINE_PREFIX char *TM2x·byte_0_pt(TM2x·Tape *tm2x){
    return tm2x->base_pt;
  }
  INLINE_PREFIX void *TM2x·element_0_pt(TM2x·Tape *tm2x){
    return tm2x->base_pt;
  }

  // max offsets
  INLINE_PREFIX address_t TM2x·byte_n(TM2x·Tape *tm2x){
    return tm2x->byte_n;
  }
  // The index of the last element in the array.  Note that the
  // (element_byte_n + 1) in the denominator must be representable:
  INLINE_PREFIX address_t TM2x·element_n(TM2x·Tape *tm2x ,address_t element_byte_n){
    return tm2x->byte_n/(element_byte_n + 1);
  }

  // nth pointers
  INLINE_PREFIX char *TM2x·byte_n_pt(TM2x·Tape *tm2x){
    return tm2x->base_pt + tm2x->byte_n;
  }
  INLINE_PREFIX void *TM2x·element_n_pt(TM2x·Tape *tm2x ,address_t element_byte_n){
    return TM2x·byte_n_pt(tm2x) - element_byte_n;
  }

  #define TM2x·Element_N_Pt(tm2x ,type) TM2x·element_n_pt(tm2x ,byte_n_of(type))


//--------------------------------------------------------------------------------
// allocation
//
  #define MINIMUM_ALLOC_N power_2_extent(15)

  INLINE_PREFIX address_t alloc_n(address_t byte_n){
    if( byte_n <= MINIMUM_ALLOC_N) return MINIMUM_ALLOC_N;
    return power_2_extent(byte_n);
  }

  // tm2x becomes a pointer to a static allocation of a TM2x·Tape struct
  #define TM2x·alloc_Tape_static(tm2x) TM2x·Tape TM2x· ## tm2x ,*tm2x; tm2x = &TM2x· ## tm2x;


#endif

