/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

struct{
  TM2x *tape;
  address_t after_byte_n;
  continuation nominal;
  continuation alloc_fail;
} TM2x·resize_bytes·args;



