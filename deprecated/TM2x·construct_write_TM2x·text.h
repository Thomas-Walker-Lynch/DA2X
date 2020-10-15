
TM2x·construct_write_TM2x{
  TM2x·Tape*tape            = TM2x·construct_write_TM2x·args.tape;           
  TM2x·Tape*tape_source     = TM2x·construct_write_TM2x·args.tape_source;    
  continuation nominal  = TM2x·construct_write_TM2x·args.continuation nominal; 
  continuation fail     = TM2x·construct_write_TM2x·args.continuation fail;    

  TM2x·construct_write_bytes·args.tape = tape;      
  TM2x·construct_write_bytes·args.tape_source = tape_source->base_pt;  
  TM2x·construct_write_bytes·args.source_byte_n = tape_source->byte_n;
  TM2x·construct_write_bytes·args.continuation nominal = nominal;
  TM2x·construct_write_bytes·args.continuation fail = fail;
  continue_from TM2x·construct_write_bytes;
  cend;
};
