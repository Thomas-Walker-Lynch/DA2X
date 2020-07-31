
TM2x·index·to_pt{
  TM2x *tape               = TM2x·index·to_pt·args.tape;
  address_t index          = TM2x·index·to_pt·args.index;
  address_t element_byte_n = TM2x·index·to_pt·args.element_byte_n;
  void **pt                = TM2x·index·to_pt·args.pt;
  continuation nominal     = TM2x·index·to_pt·args.nominal;
  continuation index_gt_n = TM2x·index·to_pt·args.index_gt_n;

  address_t byte_i;
  inclusive·mul_ib·args.an = index;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_i;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    if( byte_i > TM2x·byte_n(tape) ) continue_from index_gt_n;
    *pt = (void *)(TM2x·byte_0_pt(tape) + byte_i);
    cend;
  }

  cend;
}





