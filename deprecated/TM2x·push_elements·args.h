
struct{
  TM2x·Tape *tape ;
  void *base_pt;
  address_t n_Element ;
  address_t element_n_Byte ;
  continuation nominal;
  continuation alloc_fail;
  continuation index_gt_n;
 } TM2x·push_elements;
