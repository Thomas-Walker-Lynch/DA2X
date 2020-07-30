
struct{
  TM2x *tape;
  void *base_pt;
  address_t element_n;
  address_t element_byte_n;
  continuation nominal;
  continuation fail;
  continuation bad_index;
} TM2x·construct_write_elements·args;
