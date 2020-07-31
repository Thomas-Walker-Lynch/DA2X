
struct{
  TM2x *src;
  address_t src_element_i;
  TM2x *dst;
  address_t dst_element_i;
  address_t element_n;  // index of nth element of the copy region
  address_t element_byte_n;
  continuation nominal;
  continuation alloc_fail;
  continuation bad_src_index;
  continuation bad_dst_index;
} TM2x·copy_elements;
