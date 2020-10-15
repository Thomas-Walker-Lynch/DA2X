
TM2x·read_pop:{
  TM2x·Tape*tape                 = TM2x·read_pop·args.TM2x·Tape*tape;            
  void *dst_element_pt       = TM2x·read_pop·args.void *dst_element_pt;  
  address_t element_byte_n   = TM2x·read_pop·args.address_t element_byte_n;
  continuation nominal       = TM2x·read_pop·args.continuation nominal;   
  continuation pop_last      = TM2x·read_pop·args.continuation pop_last;  
  continuation alloc_fail    = TM2x·read_pop·args.continuation alloc_fail;
  cend;
}



