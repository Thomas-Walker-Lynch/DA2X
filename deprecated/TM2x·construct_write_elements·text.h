TM2x·construct_write_elements:{
         TM2x·Tape *tape            = TM2x·construct_write_elements·args.tape;           
         void *source_pt       = TM2x·construct_write_elements·args.source_pt;        
     address_t n_Element       = TM2x·construct_write_elements·args.n_Element;      
     address_t element_n_Byte  = TM2x·construct_write_elements·args.element_n_Byte; 
  continuation nominal         = TM2x·construct_write_elements·args.nominal;        
  continuation fail            = TM2x·construct_write_elements·args.fail;           
  continuation index_gt_n       = TM2x·construct_write_elements·args.index_gt_n;      

  address_t byte_n;
  inclusive·mul_ext·args.an = n_Element;
  inclusive·mul_ext·args.bn = element_n_Byte;
  inclusive·mul_ext·args.cn = &byte_n;
  inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
  inclusive·mul_ext·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ext;

  mul_ext·nominal:{
    TM2x·construct_write_bytes·args.tape      = tape;
    TM2x·construct_write_bytes·args.source_pt = source_pt;
    TM2x·construct_write_bytes·args.byte_n    = byte_n;
    TM2x·construct_write_bytes·args.nominal   = nominal;
    TM2x·construct_write_bytes·args.fail      = fail;
    continue_from TM2x·construct_write_bytes;
    cend;
  }

  cend;
}







