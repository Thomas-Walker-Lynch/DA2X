#ifndef INCLUSIVE_H
#define INCLUSIVE_H

/*
  mul_ib = mul inclusive bounds.

  gives the product of two extent values.

  When an is the extent of a region measured in elements, and bn is the
  extent of an element in bytes, then mul_ib is will the extent of the
  region in bytes.

    (an + 1) (bn + 1) -1
    = an bn + an + bn

   eg.  an = 0,  bn = 3   --> 3
        an = 1,  bn = 3   --> 7
        an = 2,  bn = 3   --> 11

---
say n is the number of bits in an address_t.  Can our 2n bit intermediate values
overflow?

   if we are to have an overflow it will happen with max value operands, so say:
     an = (2^n - 1) and bn = (2^n - 1)

    initial multiply:
      (2^n - 1) * (2^n - 1) = 2^2n - 2^n - 2^n + 1 = 2^2n - 2^(n+1) + 1
           no ov if:  2^2n - 2^(n+1) + 1 <= 2^2n - 1  
                           - 2^(n+1) + 1 <= -1
                                       2 <= 2^(n+1) ; true, so no ov

    including sum terms, no ov if:
            2^2n - 2^(n+1) + 1 + 2 (2^n - 1) <= 2^2n - 1  
                  -2^(n+1) + 2^(n+1) - 1 <= -1  
                                      -1 <= -1  ; true

    yikes, but we just make it ( 2^n * 2^n - 1 leads to the result more directly)

*/
#pragma push_macro("S0")
#pragma push_macro("S1")
#undef S0
#undef S1
#define S1 Locals.Inclusive·mul_ib
#define S1 Args.Inclusive·mul_ib
Inclusive·mul_ib:{
  S0.an = S1.an;
  S0.bn = S1.bn;
  S0.cn = S0.an * S0.bn + S0.an + S0.bn;
  if( S0.cn > address_t_n ) continue_from *S1.gt_address_n;
  *S1.cn = S0.cn;
  continue_from *nominal;
}
#pragma pop_macro("S0")
#pragma pop_macro("S1")

/*
  mul_ei_bi  convert element index to a byte index

  Given an element index and the extent of elements in bytes, computes the byte index.

    an (bn + 1)
    = an bn + an 

   eg.  an = 0,  bn = 3   --> 0
        an = 1,  bn = 3   --> 4
        an = 2,  bn = 3   --> 8

   smaller than mul_ib so no ov possible, also
   (2^n - 1) * (2^n) = 2^2n - 2^n ; 2^n >= 1, so no ov possible

*/
#pragma push_macro("S0")
#pragma push_macro("S1")
#undef S0
#undef S1
#define S1 Locals.Inclusive·mul_ei_bi
#define S1 Args.Inclusive·mul_ei_bi
inclusive·mul_ei_bi:{
  S0.an = S1.an;
  S0.bn = S1.bn;
  S0.cn = S0.an * S0.bn + S0.an;
  if( S0.cn > address_t_n ) continue_from *S1.gt_address_n;
  *S1.cn = S0.cn;
  continue_from *nominal;
}
#pragma pop_macro("S0")
#pragma pop_macro("S1")

#endif
