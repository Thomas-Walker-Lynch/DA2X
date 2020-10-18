/*
  Dynamic allocation of the TM2x·Tape header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#ifdef TM2x·TEST
  extern address_t TM2x·test_after_allocation_n;
#endif

extern address_t TM2x·alloc_array_count;

TM2x·resize:{
  // shorten the arg names, give the optimizer something more to do
  TM2x·Tape *tape = TM2x·resize·args.tape;
  address_t after_byte_n = TM2x·resize·args.after_byte_n;
  continuation nominal = TM2x·resize·args.nominal;
  continuation alloc_fail = TM2x·resize·args.alloc_fail;

  address_t before_alloc_n = binary_interval_inclusive_upper_bound(tape->byte_n);
  address_t after_alloc_n = binary_interval_inclusive_upper_bound(after_byte_n);

  if( after_alloc_n == before_alloc_n ){
    tape->byte_n = after_byte_n;
    continue_via_trampoline nominal;
  }

  char *after_base_pt;

  #include "CLib·mallocn·args.h"
  CLib·mallocn·args.pt      = (void **)&after_base_pt;
  CLib·mallocn·args.n       = after_alloc_n;
  CLib·mallocn·args.nominal = &&malloc_nominal;
  CLib·mallocn·args.fail    = &&malloc_fail; 
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
    continue_from *nominal;
    cend
  }

  malloc_fail:{
   continue_from *alloc_fail;
   cend
  }

  cend
}
