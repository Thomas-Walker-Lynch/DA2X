/*
  Dynamic allocation of the TM2x·Tape header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

struct{
  TM2x·Tape *tape;
  address_t after_n_Element;
  address_t element_n_Byte;
  continuation nominal;
  continuation alloc_fail;
  continuation index_gt_n;
} TM2x·resize_elements;


