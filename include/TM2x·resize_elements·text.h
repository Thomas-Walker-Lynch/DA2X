/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#ifdef TM2x·TEST
  extern address_t TM2x·test_after_allocation_n;
#endif

extern address_t TM2x·constructed_count;

TM2x·F_PREFIX continuation TM2x·resize_elements:{
  TM2x *tape                = TM2x·resize_elements·args.tape;
  address_t after_element_n = TM2x·resize_elements·args.after_element_n;
  address_t element_byte_n  = TM2x·resize_elements·args.element_byte_n;
  continuation nominal      = TM2x·resize_elements·args.nominal;
  continuation alloc_fail   = TM2x·resize_elements·args.alloc_fail;
  continuation index_gt_n    = TM2x·resize_elements·args.index_gt_n;

  address_t after_byte_n;
  #include "inclusive·mul_ib·args.h"
  inclusive·mul_ib·args.an = after_element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &after_byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.overflow = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
   resize_bytes·args.tape = tape;
   resize_bytes·args.after_byte_n = after_byte_n;
   resize_bytes·args.nominal = nominal;
   resize_bytes·args.alloc_fail = alloc_fail;
   contine_from TM2x·resize_bytes;
   cend;
  }

  cend;
}
