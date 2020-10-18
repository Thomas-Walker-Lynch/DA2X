
struct{
  TM2x·Tape *tape;
  address_t n_Element;  // number of elements
  address_t element_n_Byte; // index of last byte in element
  continuation nominal;
  continuation alloc_fail;
  continuation index_gt_n;
} TM2x·alloc_array_bytes;
