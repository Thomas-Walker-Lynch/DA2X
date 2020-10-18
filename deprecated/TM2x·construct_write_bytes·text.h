
construct_write:{
         TM2x·Tape *tape      = TM2x·construct_write·args.tape;
         void *source_pt = TM2x·construct_write·args.source_pt;
     address_t byte_n    = TM2x·construct_write·args.byte_n;
  continuation nominal   = TM2x·construct_write·args.nominal;
  continuation fail      = TM2x·construct_write·args.fail;

  TM2x·alloc_array·args.tape = tape;      
  TM2x·alloc_array·args.tape_source = tape_source->base_pt;  
  TM2x·alloc_array·args.byte_n = tape_source->byte_n;
  TM2x·alloc_array·args.continuation nominal = &&construct_nominal;
  TM2x·alloc_array·args.continuation fail = fail;
  continue_from TM2x·alloc_array;

  construct_nominal:{
    memcpyn(tape->base_pt, source_pt, byte_n);
    continue_from *nominal;
    cend;
  }
  
  cend;
}

