
construct_write_bytes:{
         TM2x·Tape*tape      = TM2x·construct_write_bytes·args.tape;
         void *source_pt = TM2x·construct_write_bytes·args.source_pt;
     address_t byte_n    = TM2x·construct_write_bytes·args.byte_n;
  continuation nominal   = TM2x·construct_write_bytes·args.nominal;
  continuation fail      = TM2x·construct_write_bytes·args.fail;

  TM2x·alloc_array_bytes·args.tape = tape;      
  TM2x·alloc_array_bytes·args.tape_source = tape_source->base_pt;  
  TM2x·alloc_array_bytes·args.byte_n = tape_source->byte_n;
  TM2x·alloc_array_bytes·args.continuation nominal = &&construct_nominal;
  TM2x·alloc_array_bytes·args.continuation fail = fail;
  continue_from TM2x·alloc_array_bytes;

  construct_nominal:{
    memcpyn(tape->base_pt, source_pt, byte_n);
    continue_from *nominal;
    cend;
  }
  
  cend;
}

