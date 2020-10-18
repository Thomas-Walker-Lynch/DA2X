

TM2x·alloc_array_elements:{
  TM2x·Tape *tape               = TM2x·alloc_array_elements·args.tape;      
  address_t element_n      = TM2x·alloc_array_elements·args.element_n;    
  address_t element_byte_n = TM2x·alloc_array_elements·args.element_byte_n;    
  continuation nominal     = TM2x·alloc_array_elements·args.nominal;
  continuation alloc_fail  = TM2x·alloc_array_elements·args.alloc_fail;
  continuation index_gt_n  = TM2x·alloc_array_elements·args.index_gt_n;

  address_t byte_n;
  inclusive·mul_ext·args.an = element_n;
  inclusive·mul_ext·args.bn = element_byte_n;
  inclusive·mul_ext·args.cn = &byte_n;
  inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
  inclusive·mul_ext·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ext;

  mul_ext·nominal:{
    TM2x·alloc_array·args.tape       = tape;
    TM2x·alloc_array·args.byte_n     = byte_n;
    TM2x·alloc_array·args.nominal    = nominal;
    TM2x·alloc_array·args.alloc_fail = alloc_fail;
    continue_from TM2x·alloc_array;
    cend;
  }

  cend;
}
