#ifndef nonstdint_H
#define nonstdint_H

#include <stdint.h>
#include <limits.h>

  #define address_t uint64_t
  #define address_bit_length 64

  // address_t_n is the largest address that may be used to access a byte from memory.
  // If this array is implemented over virtual memory, that migth be the largest virtual memory
  //  address, i.e. UINT64_MAX.  That is what I have put here.
  #define address_t_n UINT64_MAX

#endif
