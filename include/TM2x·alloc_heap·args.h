/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#define S0(x) TM2x·alloc_heap· ## x

struct{
  TM2x **tape;
  continuation nominal;
  continuation fail;
}S0(args);

#undef S0



