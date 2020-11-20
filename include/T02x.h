#ifndef T02x_H
#define T02x_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include "misc.h"
#include "Inclusive.h"
#include "Sequence.h"

//--------------------------------------------------------------------------------
// The T02x·RootHeader dynamic array header struct
//   .. does the mutex lock variable belongs here, or at L2? Perhaps here,
//   because look at all the trouble we have already gone through to make
//   this thread safe.
//
  typedef struct {
    char *base_pt;
    address_t n;
  } T02x·Root ;


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

