/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#define S0(x) TM2x·alloc_heap· ## x

  extern address_t TM2x·constructed_count;

  #ifdef DEFAULT_ARGS
  #define TM2x·alloc_heap·tape      S0(args.tape)
  #define TM2x·alloc_heap·nominal   S0(args.nominal) 
  #define TM2x·alloc_heap·fail      S0(args.fail) 
  #endif
  #undef DEFAULT_ARGS

  TM2x·alloc_heap:{
    continuations CLib·mallocn
    //  #include "CLib·mallocn·args.h"
    #define TM2x·alloc_heap·pt      tape
    #define TM2x·alloc_heap·n       byte_n_of(TM2x)
    #define TM2x·alloc_heap·nominal malloc_nominal
    #define TM2x·alloc_heap·fail    malloc_fail
    #include "CLib·mallocn.h"
    continue_from CLib·mallocn;
    cend
  }

  #undef TM2x·alloc_heap·tape
  #undef TM2x·alloc_heap·nominal
  #undef TM2x·alloc_heap·fail

#undef S0
