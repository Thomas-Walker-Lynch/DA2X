/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#define S0(x) TM2x·resize_bytes· ## x

struct{
  TM2x *tape;
  address_t after_byte_n;
  continuation nominal;
  continuation alloc_fail;
}S0(args);

#undef S0



