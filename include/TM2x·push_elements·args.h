
struct{
  TM2x *tape ;
  void *base_pt;
  address_t element_n ;
  address_t element_byte_n ;
  continuation nominal;
  continuation alloc_fail;
  continuation bad_index;
 } TM2x·push_elements·args;
