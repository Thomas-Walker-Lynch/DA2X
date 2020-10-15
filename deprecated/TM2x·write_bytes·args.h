
struct{
  void *src_pt;
  TM2x·Tape*dst;
  address_t dst_byte_i;
  address_t byte_n;
  continuation nominal;
  continuation alloc_fail;
  continuation bad_src_index;
  continuation bad_dst_index;
}TM2x·write_bytes;
