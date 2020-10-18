
struct{
         TM2x·Tape *src             = TM2x·copy_contiguous_elements·args.src;
     address_t src_element_i   = TM2x·copy_contiguous_elements·args.src_element_i;
         TM2x·Tape *dst             = TM2x·copy_contiguous_elements·args.dst;
     address_t dst_element_i   = TM2x·copy_contiguous_elements·args.dst_element_i;
     address_t n_Element       = TM2x·copy_contiguous_elements·args.n_Element;
     address_t element_n_Byte  = TM2x·copy_contiguous_elements·args.element_n_Byte;
  continuation nominal         = TM2x·copy_contiguous_elements·args.nominal;
  continuation alloc_fail      = TM2x·copy_contiguous_elements·args.alloc_fail;
  continuation bad_src_index   = TM2x·copy_contiguous_elements·args.bad_src_index;
  continuation bad_dst_index   = TM2x·copy_contiguous_elements·args.bad_dst_index;
} TM2x·copy_contiguous_elements·args;
