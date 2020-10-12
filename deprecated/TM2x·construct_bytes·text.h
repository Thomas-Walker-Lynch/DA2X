


// byte_n is the maximum byte index for the initial data array
TM2x·alloc_array_bytes:{
  TM2x *tape              = TM2x·alloc_array_bytes·args.tape;
  address_t byte_n        = TM2x·alloc_array_bytes·args.byte_n;
  continuation nominal    = TM2x·alloc_array_bytes·args.nominal;
  continuation alloc_fail = TM2x·alloc_array_bytes·args.alloc_fail;

  TM2x·alloc_array_count++; // to assist with debugging
  tape->byte_n = byte_n;
  address_t alloc_byte_n = binary_interval_inclusive_upper_bound(byte_n);

  CLib·mallocn·args.pt      = (void **)&(tape->base_pt);
  CLib·mallocn·args.n       = alloc_byte_n;
  CLib·mallocn·args.nominal = nominal;
  CLib·mallocn·args.fail    = alloc_fail;
  continue_from CLib·mallocn;
  cend;
}
