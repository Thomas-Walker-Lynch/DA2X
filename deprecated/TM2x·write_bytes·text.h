/*

Copies a region stemming from src_pt to src_pt + byte_n on to the 
dst tape starting from byte offset dst_byte_i.

The only tape explicitly identified is the dst tape, so we say that
we are writing the dst tape.

*/
TM2x·write_bytes:{
          TM2x·Tape*dst             = TM2x·write_bytes·args.dst          
     address_t  dst_byte_i      = TM2x·write_bytes·args.dst_byte_i   
          void *src_pt          = TM2x·write_bytes·args.src_pt       
     address_t  byte_n          = TM2x·write_bytes·args.byte_n       
  continuation  nominal         = TM2x·write_bytes·args.nominal      
  continuation  alloc_fail      = TM2x·write_bytes·args.alloc_fail   
  continuation  bad_src_index   = TM2x·write_bytes·args.bad_src_index
  continuation  bad_dst_index   = TM2x·write_bytes·args.bad_dst_index
}
