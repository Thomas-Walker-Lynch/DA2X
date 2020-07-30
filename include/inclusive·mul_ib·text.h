
inclusive·mul_ib:{
  address_t an = inclusive·mul_ib·args.an;
  address_t bn = inclusive·mul_ib·args.bn;
  address_t *cn = inclusive·mul_ib·args.cn;
  continuation nominal = inclusive·mul_ib·args.nominal;
  continuation overflow = inclusive·mul_ib·args.overflow;

  uint128_t d_an = an, d_bn = bn, d_cn;
  d_cn = d_an * d_bn + d_an + d_bn;
  if( d_cn > address_t_n ) continue_from *overflow;
  *cn = d_cn;
  continue_from *nominal;
}
