
/*
  mul_ib = mul inclusive bounds.

  gives the product of two extent values.

  When an is the max element index for a region, and bn is the max byte
  index within an element, then cn is the max byte index for the region.

    (an + 1) (bn + 1) -1
    = an bn + an + bn

   eg.  an = 0,  bn = 3   --> 3
        an = 1,  bn = 3   --> 7

*/
inclusive·mul_ib:{
  address_t an = inclusive·mul_ib·args.an;
  address_t bn = inclusive·mul_ib·args.bn;
  address_t *cn = inclusive·mul_ib·args.cn;
  continuation nominal = inclusive·mul_ib·args.nominal;
  continuation gt_address_n = inclusive·mul_ib·args.gt_address_n;

  uint128_t d_an = an, d_bn = bn, d_cn;
  d_cn = d_an * d_bn + d_an + d_bn;
  if( d_cn > address_t_n ) continue_from *gt_address_n;
  *cn = d_cn;
  continue_from *nominal;
}


/*
  mul_ei_bi  convert element index to a byte index

  Given an element index and the extent of the element, computes the byte index.

    an (bn + 1)
    = an bn + an 

   eg.  an = 0,  bn = 3   --> 0
        an = 1,  bn = 3   --> 4
        an = 2,  bn = 3   --> 8

*/
inclusive·mul_ei_bi:{
  address_t an = inclusive·3op·args.an;
  address_t bn = inclusive·3op·args.bn;
  address_t *cn = inclusive·3op·args.cn;
  continuation nominal = inclusive·mul_ei_bi·args.nominal;
  continuation gt_address_n = inclusive·mul_ei_bi·args.gt_address_n;

  uint128_t d_an = an, d_bn = bn, d_cn;
  d_cn = d_an * d_bn + d_an;
  if( d_cn > address_t_n ) continue_from *gt_address_n;
  *cn = d_cn;
  continue_from *nominal;
}
