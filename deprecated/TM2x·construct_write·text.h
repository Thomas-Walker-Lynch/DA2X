
/*
  Writes one element.
*/

TM2x·construct_write·args:{
          TM2x·Tape *tape            = TM2x·construct_write·args.tape;
          void *element_base_pt = TM2x·construct_write·args.element_base_pt;
     address_t  element_byte_n  = TM2x·construct_write·args.element_byte_n;
  continuation  nominal         = TM2x·construct_write·args.nominal;
  continuation  fail            = TM2x·construct_write·args.fail;

  TM2x·construct_write_bytes·args.tape      = tape;
  TM2x·construct_write_bytes·args.source_pt = element_base_pt;
  TM2x·construct_write_bytes·args.byte_n    = element_byte_n;
  TM2x·construct_write_bytes·args.nominal   = nominal;
  TM2x·construct_write_bytes·args.fail      = fail;
  continue_from TM2x·construct_write_bytes;
  cend;
}
