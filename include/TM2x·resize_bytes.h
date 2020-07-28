/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#ifdef TM2x·TEST
  extern address_t TM2x·test_after_allocation_n;
#endif

#define S0(x) TM2x·resize_bytes· ## x

  extern address_t TM2x·constructed_count;

  #ifdef DEFAULT_ARGS
  #define tape         S0(args.tape)
  #define after_byte_n S0(args.after_byte_n) 
  #define nominal      S0(args.nominal) 
  #define alloc_fail   S0(args.alloc_fail) 
  #endif
  #undef DEFAULT_ARGS

  TM2x·resize_bytes:{
    address_t before_alloc_n = binary_interval_inclusive_upper_bound(tape->byte_n);
    address_t after_alloc_n = binary_interval_inclusive_upper_bound(after_byte_n);

    if( after_alloc_n == before_alloc_n ){
      tape->byte_n = after_byte_n;
      continue_via_trampoline nominal;
    }

    char *after_base_pt;
    //  #include "CLib·mallocn·args.h"
    #define pt      (void **)&after_base_pt
    #define n       after_alloc_n
    #define nominal malloc_nominal
    #define fail    malloc_fail
    #include "CLib·mallocn.h"
    continue_from CLib·mallocn;

    malloc_nominal:{
      #ifdef TM2x·TEST
        TM2x·test_after_allocation_n = after_alloc_n;
      #endif
      address_t copy_n = after_byte_n < tape->byte_n ? after_byte_n : tape->byte_n;
      memcpyn( after_base_pt ,tape->base_pt ,copy_n);
      free(tape->base_pt);
      tape->base_pt = after_base_pt;
      tape->byte_n = after_byte_n;
      continue_via_trampoline nominal;
      cend
    }
    malloc_fail:{
     continue_via_trampoline alloc_fail;
     cend
    }
    cend
  }

  #undef tape
  #undef after_byte_n
  #undef nominal
  #undef alloc_fail

#undef S0
