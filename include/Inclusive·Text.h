
/*
struct Text·Inclusive{
  ConveyancePtr mul_ib;
  ConveyancePtr mul_ei_bi;
} Text·Inclusive
={
  &&Inclusive·mul_ib
  ,&&Inclusive·mul_ei_bi
};
*/

goto Inclusive·end;

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

Inclusive·mul_ib:{
  Conveyance·swap();
  LC(lc0 ,Inclusive·3opLL ,0);
  LC(lc1 ,Inclusive·3opLL ,1);
  AR(ar ,Inclusive·3opLL  ,2);

  lc1->r = lc0->a0 * lc0->a1 + lc0->a0 + lc0->a1;
  if( lc1->r > address_t_n ) convey *lc0->gt_address_t_n;
  ar->rpt = lc1->r;
  convey *lc0->nominal;
}


/*
  mul_ei_bi  convert element index to a byte index

  Given a0 element index a0d the extent of elements in bytes, computes the byte index.

    a0 (a1 + 1)
    = a0 a1 + a0 

   eg.  a0 = 0,  a1 = 3   --> 0
        a0 = 1,  a1 = 3   --> 4
        a0 = 2,  a1 = 3   --> 8

   smaller tha0 mul_ib so no ov possible, also
   (2^n - 1) * (2^n) = 2^2n - 2^n ; 2^n >= 1, so no ov possible

*/
Inclusive·mul_ei_bi:{
  Conveyance·swap();
  LC(lc0 ,Inclusive·3opLL0 ,0);
  LC(lc1 ,Inclusive·3opLL1 ,0);
  AR(ar ,Inclusive·3opLL  ,2);

  lc1->r = lc0->a0 * lc0->a1 + lc0->a0;
  if( lc1->r > address_t_n ) convey *lc0->gt_address_t_n;
  ar->rpt = lc1->r;
  convey *lc0->nominal;
}


Inclusive·end:;
