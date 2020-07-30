
struct{
         TM2x *src             = TM2x·copy_elements·args.src;
     address_t src_element_i   = TM2x·copy_elements·args.src_element_i;
         TM2x *dst             = TM2x·copy_elements·args.dst;
     address_t dst_element_i   = TM2x·copy_elements·args.dst_element_i;
     address_t element_n       = TM2x·copy_elements·args.element_n;
     address_t element_byte_n  = TM2x·copy_elements·args.element_byte_n;
  continuation nominal         = TM2x·copy_elements·args.nominal;
  continuation alloc_fail      = TM2x·copy_elements·args.alloc_fail;
  continuation bad_src_index   = TM2x·copy_elements·args.bad_src_index;
  continuation bad_dst_index   = TM2x·copy_elements·args.bad_dst_index;
} TM2x·copy_elements·args;
