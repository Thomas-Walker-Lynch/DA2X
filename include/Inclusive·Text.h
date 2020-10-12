/*
  mul_ext = mul inclusive bounds.

  gives the product of two extent values.

  When an is the extent of a region measured in elements, and bn is the
  extent of an element in bytes, then mul_ext is will the extent of the
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
  SQ·def(Inclusive·mul_ext){

    Inclusive·3opLL·Lnk *lnk = (Inclusive·3opLL·Lnk *)SQ·lnk;
    register uint128_t t = *lnk->args->a_0 * *lnk->args->a_1 + *lnk->args->a_0 + *lnk->args->a_1;
    if( t > address_t_n ){
      SQ·continue_indirect(lnk->lnks->gt_address_t_n);
    }
    *lnk->ress->r = t;
    SQ·continue_indirect(lnk->lnks->nominal);

  } SQ·end(Inclusive·mul_ext);


/*
  mul_idx  convert element index to a byte index

  Given a0 element index a0d the extent of elements in bytes, computes the byte index.

    a0 (a1 + 1)
    = a0 a1 + a0 

   eg.  a0 = 0,  a1 = 3   --> 0
        a0 = 1,  a1 = 3   --> 4
        a0 = 2,  a1 = 3   --> 8

   smaller than mul_ext so no ov possible, also
   (2^n - 1) * (2^n) = 2^2n - 2^n ; 2^n >= 1, so no ov possible

*/
  SQ·def(Inclusive·mul_idx){

    Inclusive·3opLL·Lnk *lnk = (Inclusive·3opLL·Lnk *)SQ·lnk;
    uint128_t t = *lnk->args->a_0 * *lnk->args->a_1 + *lnk->args->a_0;
    if( t > address_t_n ){
      SQ·continue_indirect(lnk->lnks->gt_address_t_n);
    }
    *lnk->ress->r = t;
    SQ·continue_indirect(lnk->lnks->nominal);

  } SQ·end(Inclusive·mul_idx);
