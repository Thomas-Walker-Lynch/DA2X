
TM2x·copy_contiguous:{
         TM2x·Tape *src             = TM2x·copy_contiguous·args.src;          
     address_t src_byte_i      = TM2x·copy_contiguous·args.src_byte_i;   
         TM2x·Tape *dst             = TM2x·copy_contiguous·args.dst;          
     address_t dst_byte_i      = TM2x·copy_contiguous·args.dst_byte_i;   
     address_t byte_n          = TM2x·copy_contiguous·args.byte_n;       
  continuation nominal         = TM2x·copy_contiguous·args.nominal;      
  continuation alloc_fail      = TM2x·copy_contiguous·args.alloc_fail;   
  continuation bad_src_index   = TM2x·copy_contiguous·args.bad_src_index;
  continuation bad_dst_index   = TM2x·copy_contiguous·args.bad_dst_index;
} 










