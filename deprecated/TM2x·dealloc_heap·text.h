/*
  Dynamic allocation of the TM2x·Tape header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

TM2x·dealloc_Tape_heap:{
  TM2x·dealloc_array(TM2x·dealloc_Tape_heap·args.tape);
  free(TM2x·dealloc_Tape_heap·args.tape);
  continue_from *TM2x·dealloc_Tape_heap·args.nominal;
  cend;
}
