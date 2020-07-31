

TM2x·construct_elements:{
  TM2x *tape               = TM2x·construct_elements·args.tape;      
  address_t element_n      = TM2x·construct_elements·args.element_n;    
  address_t element_byte_n = TM2x·construct_elements·args.element_byte_n;    
  continuation nominal     = TM2x·construct_elements·args.nominal;
  continuation alloc_fail  = TM2x·construct_elements·args.alloc_fail;
  continuation index_gt_n  = TM2x·construct_elements·args.index_gt_n;

  address_t byte_n;
  inclusive·mul_ib·args.an = element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    TM2x·construct_bytes·args.tape       = tape;
    TM2x·construct_bytes·args.byte_n     = byte_n;
    TM2x·construct_bytes·args.nominal    = nominal;
    TM2x·construct_bytes·args.alloc_fail = alloc_fail;
    continue_from TM2x·construct_bytes;
    cend;
  }

  cend;
}
