
  
struct{
  TM2x·Tape *tape;
  address_t index;
  address_t n_Element;
  address_t element_n_Byte;
  void *dst_element_pt;
  continuation nominal;
  continuation index_gt_n;
} TM2x·index·read;
