

TM2x·construct_elements:{
  TM2x *tape               = TM2x·construct_bytes·args.tape;      
  address_t element_n      = TM2x·construct_bytes·args.element_n;    
  address_t element_byte_n = TM2x·construct_bytes·args.element_byte_n;    
  continuation nominal     = TM2x·construct_bytes·args.nominal;
  continuation alloc_fail  = TM2x·construct_bytes·args.alloc_fail;
  continuation bad_index   = TM2x·construct_bytes·args.bad_index;

  address_t byte_n;
  #include "inclusive·mul_ib·args.h"
  inclusive·mul_ib·args.an = element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.overflow = bad_index;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    #include "TM2x·construct_bytes·args.h"
    TM2x·construct_bytes·args.tape       = tape;
    TM2x·construct_bytes·args.byte_n     = byte_n;
    TM2x·construct_bytes·args.nominal    = nominal;
    TM2x·construct_bytes·args.alloc_fail = alloc_fail;
    #include "TM2x·construct_bytes.h"
    continue_from TM2x·construct_bytes;
    cend;
  }
  cend
}
