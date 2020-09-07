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
  #pragma push_macro("ARGS")
  #pragma push_macro("ARGS_1")
  #pragma push_macro("LNKS")

  #define ARGS ((Inclusive·3opLL·Args *)(CV·lnk->args))
  #define ARGS_1 ((Inclusive·3opLL·Args_1 *)(CV·lnk->args))
  #define LNKS ((Inclusive·3opLL·Lnks *)(CV·lnk->lnks))

    CV·def(Inclusive·mul_ib){
      ARGS_1->r = ARGS->a_0 * ARGS->a_1 + ARGS->a_0 + ARGS->a_1;
      if( ARGS_1->r > address_t_n ){
        CV·convey_indirect(LNKS->gt_address_t_n);
      }
      *(ARGS->rpt) = ARGS_1->r;

      CV·convey_indirect(LNKS->nominal)

      //      CV·lnk = &((Inclusive·3opLL·Lnks *)(CV·lnk->lnks))->nominal;
      //      goto *CV·lnk->conveyance;
    } CV·end(Inclusive·mul_ib);

  #pragma pop_macro("ARGS")
  #pragma pop_macro("ARGS_1")
  #pragma pop_macro("LNKS")


/*
  mul_ei_bi  convert element index to a byte index

  Given a0 element index a0d the extent of elements in bytes, computes the byte index.

    a0 (a1 + 1)
    = a0 a1 + a0 

   eg.  a0 = 0,  a1 = 3   --> 0
        a0 = 1,  a1 = 3   --> 4
        a0 = 2,  a1 = 3   --> 8

   smaller than mul_ib so no ov possible, also
   (2^n - 1) * (2^n) = 2^2n - 2^n ; 2^n >= 1, so no ov possible

*/
  #pragma push_macro("ARGS")
  #pragma push_macro("ARGS_1")
  #pragma push_macro("LNKS")

  #define ARGS ((Inclusive·3opLL·Args *)(CV·lnk->args))
  #define ARGS_1 ((Inclusive·3opLL·Args_1 *)(CV·lnk->args))
  #define LNKS ((Inclusive·3opLL·Lnks *)(CV·lnk->lnks))

    CV·def(Inclusive·mul_ei_bi){
      ARGS_1->r = ARGS->a_0 * ARGS->a_1 + ARGS->a_0;
      if( ARGS_1->r > address_t_n ){
        CV·convey_indirect(LNKS->gt_address_t_n);
      }
      *(ARGS->rpt) = ARGS_1->r;

      CV·convey_indirect(LNKS->nominal)

      //      CV·lnk = &((Inclusive·3opLL·Lnks *)(CV·lnk->lnks))->nominal;
      //      goto *CV·lnk->conveyance;
    } CV·end(Inclusive·mul_ei_bi);

  #pragma pop_macro("ARGS")
  #pragma pop_macro("ARGS_1")
  #pragma pop_macro("LNKS")

