
  
struct{
  TM2x *tape;
  address_t index;
  address_t element_n;
  address_t element_byte_n;
  void *dst_element_pt;
  continuation nominal;
  continuation index_gt_n;
} TM2x·index·read·args;
