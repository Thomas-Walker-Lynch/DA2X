/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#define S0(x) TM2x·destruct· ## x

  extern address_t TM2x·constructed_count;

  #ifdef DEFAULT_ARGS
  #define tape      S0(args.tape)
  #define nominal   S0(args.nominal) 
  #define fail      S0(args.fail) 
  #endif
  #undef DEFAULT_ARGS

  TM2x·alloc_heap:{
    { continuations CLib·mallocn
      //  #include "CLib·mallocn·args.h"
      #define pt      tape
      #define n       byte_n_of(TM2x)
      #define nominal malloc_nominal
      #define fail    malloc_fail
      #include "CLib·mallocn.h"
      continue_from CLib·mallocn;
    }
    cend
  }

  #undef tape
  #undef nominal

#undef S0
