
  TM2x·push:{
    TM2x·Tape *tape                 = TM2x·push·args.tape;
    void *element_base_pt      = TM2x·push·args.element_base_pt;
    address_t element_n_Byte   = TM2x·push·args.element_n_Byte;
    continuation nominal       = TM2x·push·args.nominal;
    continuation alloc_fail    = TM2x·push·args.alloc_fail;
    cend;
  }
