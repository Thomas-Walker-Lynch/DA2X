#ifndef INCLUSIVE_H
#define INCLUSIVE_H
/*
  Inclusive bound region addressing support.  Hacks for now.

*/
#include <stdint.h>
#include <limits.h>
#include "Conveyance.h"

  #define address_t uint64_t
  #define address_bit_length 64

  // address_t_n is the largest address that may be used to access a byte from memory.  If
  // this array is implemented over virtual memory, that might be the largest virtual
  // memory address, i.e. UINT64_MAX.  That is what I have put here.
  #define address_t_n UINT64_MAX

  #define byte_n_of(type) sizeof(type)-1

  // the n+1 could overflow:
  #define memcpyn(dst ,src ,n) memcpy(dst ,src ,n+1) 
  #define memcmpn(e0 ,e1 ,n) memcmp(e0 ,e1 ,n+1) 
  #define strncmpn(e0 ,e1 ,n) strncmp(e0 ,e1 ,n+1)
  #define str_octet_n(cstring) (strlen(cstring) - 1)

  typedef unsigned __int128 uint128_t;


#endif
