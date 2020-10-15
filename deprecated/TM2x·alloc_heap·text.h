/*
  Dynamic allocation of the TM2x·Tapeheader.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

TM2x·alloc_header_heap:{
  CLib·mallocn·args.pt      = TM2x·alloc_header_heap·args.tape;
  CLib·mallocn·args.n       = byte_n_of(TM2x·Tape);
  CLib·mallocn·args.nominal = TM2x·alloc_header_heap·args.malloc_nominal;
  CLib·mallocn·args.fail    = TM2x·alloc_header_heap·args.malloc_fail;
  continue_from CLib·mallocn;
  cend;
}
