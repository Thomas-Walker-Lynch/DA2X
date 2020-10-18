
struct{
  TM2x·Tape *tape;
  void *source_pt;
  address_t source_byte_n;
  continuation nominal;
  continuation alloc_fail;
} TM2x·push_bytes;
