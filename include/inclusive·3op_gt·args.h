/*
  All 3 operand address computations may use this.

*/
struct{
  address_t an;
  address_t bn;
  address_t *cn;
  continuation nominal;
  continuation gt_uint64;
} inclusive·3op_gt;

