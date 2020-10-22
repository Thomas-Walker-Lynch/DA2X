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
// The T02x·Tape dynamic array header struct
//   .. does the mutex lock variable belongs here, or at L2? Perhaps here,
//   because look at all the trouble we have already gone through to make
//   this thread safe.
  typedef struct {
    char *base_pt;
    address_t n;
  } T02x·Tape ;

//--------------------------------------------------------------------------------
// adjectives
//
// Use these adjectives rather than accessing the header struct directly.
//

  // base pointers
  INLINE_PREFIX char *T02x·0_pt(T02x·Tape *tm2x){
    return tm2x->base_pt;
  }

  // max offsets
  INLINE_PREFIX address_t T02x·n(T02x·Tape *tm2x){
    return tm2x->n;
  }
  // The index of the last element in the array.  Note that the
  // (element_n_Byte + 1) in the denominator must be representable:
  INLINE_PREFIX address_t T02x·n_Element(T02x·Tape *tm2x ,address_t element_n_Byte){
    return tm2x->n/(element_n_Byte + 1);
  }

  // nth pointers
  INLINE_PREFIX char *T02x·n_pt(T02x·Tape *tm2x){
    return tm2x->base_pt + tm2x->n;
  }
  INLINE_PREFIX void *T02x·n_Element_pt(T02x·Tape *tm2x ,address_t element_n_Byte){
    return T02x·n_pt(tm2x) - element_n_Byte;
  }

  #define T02x·Element_N_Pt(tm2x ,type) T02x·n_Element_pt(tm2x ,n_of(type))


//--------------------------------------------------------------------------------
// allocation
//
  #define T02x·MINIMUM_ALLOC_N power_2_extent(15)

  // returns the allocation extent for an array of extent n
  INLINE_PREFIX address_t T02x·alloc_n(address_t n){
    if( n <= T02x·MINIMUM_ALLOC_N) return T02x·MINIMUM_ALLOC_N;
    return power_2_extent(n);
  }

#endif

