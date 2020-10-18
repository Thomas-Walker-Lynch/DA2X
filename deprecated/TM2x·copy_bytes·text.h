
TM2x·copy_contiguous_bytes:{
         TM2x·Tape *src             = TM2x·copy_contiguous_bytes·args.src;          
     address_t src_byte_i      = TM2x·copy_contiguous_bytes·args.src_byte_i;   
         TM2x·Tape *dst             = TM2x·copy_contiguous_bytes·args.dst;          
     address_t dst_byte_i      = TM2x·copy_contiguous_bytes·args.dst_byte_i;   
     address_t byte_n          = TM2x·copy_contiguous_bytes·args.byte_n;       
  continuation nominal         = TM2x·copy_contiguous_bytes·args.nominal;      
  continuation alloc_fail      = TM2x·copy_contiguous_bytes·args.alloc_fail;   
  continuation bad_src_index   = TM2x·copy_contiguous_bytes·args.bad_src_index;
  continuation bad_dst_index   = TM2x·copy_contiguous_bytes·args.bad_dst_index;
} 










