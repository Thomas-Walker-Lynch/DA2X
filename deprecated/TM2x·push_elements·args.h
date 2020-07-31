
struct{
  TM2x *tape ;
  void *base_pt;
  address_t element_n ;
  address_t element_byte_n ;
  continuation nominal;
  continuation alloc_fail;
  continuation index_gt_n;
 } TM2x·push_elements;
