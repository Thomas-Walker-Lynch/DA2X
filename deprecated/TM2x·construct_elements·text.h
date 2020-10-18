

TM2x·alloc_array_elements:{
  TM2x·Tape *tape               = TM2x·alloc_array_elements·args.tape;      
  address_t n_Element      = TM2x·alloc_array_elements·args.n_Element;    
  address_t element_n_Byte = TM2x·alloc_array_elements·args.element_n_Byte;    
  continuation nominal     = TM2x·alloc_array_elements·args.nominal;
  continuation alloc_fail  = TM2x·alloc_array_elements·args.alloc_fail;
  continuation index_gt_n  = TM2x·alloc_array_elements·args.index_gt_n;

  address_t byte_n;
  inclusive·mul_ext·args.an = n_Element;
  inclusive·mul_ext·args.bn = element_n_Byte;
  inclusive·mul_ext·args.cn = &byte_n;
  inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
  inclusive·mul_ext·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ext;

  mul_ext·nominal:{
    TM2x·alloc_array_bytes·args.tape       = tape;
    TM2x·alloc_array_bytes·args.byte_n     = byte_n;
    TM2x·alloc_array_bytes·args.nominal    = nominal;
    TM2x·alloc_array_bytes·args.alloc_fail = alloc_fail;
    continue_from TM2x·alloc_array_bytes;
    cend;
  }

  cend;
}
