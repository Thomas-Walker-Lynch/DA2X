/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

TM2x·alloc_heap:{
  continuations CLib·mallocn;
  #include "CLib·mallocn.args.h"
  CLib·mallocn·args.pt      = TM2x·alloc_heap·args.tape;
  CLib·mallocn·args.n       = byte_n_of(TM2x);
  CLib·mallocn·args.nominal = TM2x·alloc_heap·args.malloc_nominal;
  CLib·mallocn·args.fail    = TM2x·alloc_heap·args.malloc_fail;
  #include "CLib·mallocn.h"
  continue_from CLib·mallocn;
  cend;
}
