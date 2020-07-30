/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

struct{
  TM2x *tape;
  address_t after_element_n;
  address_t element_byte_n;
  continuation nominal;
  continuation alloc_fail;
  continuation index_gt_n;
} TM2x·resize_elements·args;


