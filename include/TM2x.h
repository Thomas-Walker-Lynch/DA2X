#ifndef TM2x·LIB_H
#define TM2x·LIB_H
#include <stdlib.h> // size_t
#include <string.h> // memcpy
#include <stdbool.h>
#include <assert.h>
#include "Inclusive.h"
#include "Conveyance.h"
#include "misc.h"

//--------------------------------------------------------------------------------
// misc
//    
  #ifndef TM2x·F_PREFIX 
    //#define TM2x·F_PREFIX static
    //#define TM2x·F_PREFIX extern inline
    #define TM2x·F_PREFIX static inline
  #endif

  extern address_t TM2x·constructed_count;

//--------------------------------------------------------------------------------
// The TM2x dynamic array header struct
//    
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
  TM2x·F_PREFIX char *TM2x·byte_0_pt(TM2x *tape){
    return tape->base_pt;
  }
  TM2x·F_PREFIX void *TM2x·element_0_pt(TM2x *tape){
    return tape->base_pt;
  }

  // max offsets
  TM2x·F_PREFIX address_t TM2x·byte_n(TM2x *tape){
    return tape->byte_n;
  }
  // The index of the last element in the array.  Note that the
  // (element_byte_n + 1) in the denominator must be representable:
  TM2x·F_PREFIX address_t TM2x·element_n(TM2x *tape ,address_t element_byte_n){
    return tape->byte_n/(element_byte_n + 1);
  }

  // nth pointers
  TM2x·F_PREFIX char *TM2x·byte_n_pt(TM2x *tape){
    return tape->base_pt + tape->byte_n;
  }
  TM2x·F_PREFIX void *TM2x·element_n_pt(TM2x *tape ,address_t element_byte_n){
    return TM2x·byte_n_pt(tape) - element_byte_n;
  }
  #define TM2x·Element_N_Pt(tape ,type) TM2x·element_n_pt(tape ,byte_n_of(type))


//--------------------------------------------------------------------------------
// allocation
//
  // tape becomes a pointer to a static allocation of a TM2x struct
  #define TM2x·AllocStatic(tape) TM2x TM2x· ## tape ,*tape; tape = &TM2x· ## tape;

  TM2x·F_PREFIX address_t TM2x·constructed(TM2x *tape){
    return TM2x·constructed_count;
  }


#endif

