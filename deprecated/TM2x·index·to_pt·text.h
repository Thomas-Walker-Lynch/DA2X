
TM2x·index·to_pt{
  TM2x *tape               = TM2x·index·to_pt·args.tape;
  address_t index          = TM2x·index·to_pt·args.index;
  address_t element_byte_n = TM2x·index·to_pt·args.element_byte_n;
  void **pt                = TM2x·index·to_pt·args.pt;
  continuation nominal     = TM2x·index·to_pt·args.nominal;
  continuation index_gt_n = TM2x·index·to_pt·args.index_gt_n;

  address_t byte_i;
  inclusive·mul_ext·args.an = index;
  inclusive·mul_ext·args.bn = element_byte_n;
  inclusive·mul_ext·args.cn = &byte_i;
  inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
  inclusive·mul_ext·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ext;

  mul_ext·nominal:{
    if( byte_i > TM2x·byte_n(tape) ) continue_from index_gt_n;
    *pt = (void *)(TM2x·byte_0_pt(tape) + byte_i);
    cend;
  }

  cend;
}





