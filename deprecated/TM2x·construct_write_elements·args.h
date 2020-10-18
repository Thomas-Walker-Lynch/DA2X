
struct{
  TM2x·Tape *tape;
  void *source_pt;
  address_t n_Element;
  address_t element_n_Byte;
  continuation nominal;
  continuation fail;
  continuation index_gt_n;
} TM2x·construct_write_elements;
