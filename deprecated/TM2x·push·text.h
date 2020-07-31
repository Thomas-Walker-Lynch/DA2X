
  TM2x·push:{
    TM2x *tape                 = TM2x·push·args.tape;
    void *element_base_pt      = TM2x·push·args.element_base_pt;
    address_t element_byte_n   = TM2x·push·args.element_byte_n;
    continuation nominal       = TM2x·push·args.nominal;
    continuation alloc_fail    = TM2x·push·args.alloc_fail;
    cend;
  }
