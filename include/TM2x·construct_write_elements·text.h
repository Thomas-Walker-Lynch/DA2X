TM2x·construct_write_elements:{
         TM2x *tape            = TM2x·construct_write_elements·args.tape;           
         void *source_pt       = TM2x·construct_write_elements·args.source_pt;        
     address_t element_n       = TM2x·construct_write_elements·args.element_n;      
     address_t element_byte_n  = TM2x·construct_write_elements·args.element_byte_n; 
  continuation nominal         = TM2x·construct_write_elements·args.nominal;        
  continuation fail            = TM2x·construct_write_elements·args.fail;           
  continuation index_gt_n       = TM2x·construct_write_elements·args.index_gt_n;      

  address_t byte_n;
  #include "inclusive·mul_ib·args.h"
  inclusive·mul_ib·args.an = element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.overflow = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    #include "TM2x·construct_write_bytes·args.h"
    TM2x·construct_write_bytes·args.tape      = tape;
    TM2x·construct_write_bytes·args.source_pt = source_pt;
    TM2x·construct_write_bytes·args.byte_n    = byte_n;
    TM2x·construct_write_bytes·args.nominal   = nominal;
    TM2x·construct_write_bytes·args.fail      = fail;
    #include "TM2x·construct_write_bytes.h"
    continue_from TM2x·construct_write_bytes;
    cend;
  }

  cend;
}







