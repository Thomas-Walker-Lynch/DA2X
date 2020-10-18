
/*
Copy elements at index of the given tape, to the location specified by dst_element_pt.

Set n_Element to 0 to read the one element from location specified by the given index.

Our attention is focused on the tape, so we call this a 'read' operation.

*/
  
TM2x·index·read:{
  TM2x·Tape *tape                = TM2x·index·read·args.tape;              
  address_t index           = TM2x·index·read·args.index;         
  address_t n_Element       = TM2x·index·read·args.element_n_Byte;
  address_t element_n_Byte  = TM2x·index·read·args.element_n_Byte;
  void *dst_element_pt      = TM2x·index·read·args.dst_element_pt;    
  continuation nominal      = TM2x·index·read·args.nominal;
  continuation index_gt_n   = TM2x·index·read·args.index_gt_n;

  // byte_n relative to element_0_pt.
  address_t region_byte_n;
  inclusive·mul_ext·args.an = n_Element;
  inclusive·mul_ext·args.bn = element_n_Byte;
  inclusive·mul_ext·args.cn = &region_byte_n;
  inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
  inclusive·mul_ext·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ext;

  mul_ext·nominal:{
    address_t byte_i;
    inclusive·mul_ext·args.an = index;
    inclusive·mul_ext·args.bn = element_n_Byte;
    inclusive·mul_ext·args.cn = &byte_i
    inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
    inclusive·mul_ext·args.gt_address_n = index_gt_n;
    continue_from inclusive·mul_ext;
    

    void *src_element_pt;
    TM2x·index·to_pt·args.tape           = tape;
    TM2x·index·to_pt·args.index          = index;     
    TM2x·index·to_pt·args.element_n_Byte = element_n_Byte;
    TM2x·index·to_pt·args.pt             = &src_element_pt;              
    TM2x·index·to_pt·args.nominal        = &&index_nominal;        
    TM2x·index·to_pt·args.index_gt_n     = index_gt_n;
    continue_from TM2x·index·to_pt;
  }

  index_nominal:{


    mul_ext·nominal:{
      if( 

    }
    

    memcpyn(dst_element_pt, src_element_pt, element_n_Byte);
    cend;
  }

  cend;
}
