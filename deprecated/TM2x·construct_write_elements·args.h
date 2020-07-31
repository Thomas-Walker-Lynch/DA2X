
struct{
  TM2x *tape;
  void *source_pt;
  address_t element_n;
  address_t element_byte_n;
  continuation nominal;
  continuation fail;
  continuation index_gt_n;
} TM2x·construct_write_elements;
