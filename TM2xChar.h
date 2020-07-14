#ifndef TM2x·Char_H
#define TM2x·Char_H
#include "TM2xHd.h"

/*--------------------------------------------------------------------------------
  The array elements are UTF-8 chars.

*/  

continuation C_string·format_write
( TM2x *tape 
  ,char *pt
  ,address_t element_byte_n 
  ,continuation nominal
  ,continuation null_pt
  ,continuation alloc_fail
  ){
  
  if(!pt) continue_from null_pt;
  continuation do_write = &&init; 

  is_char_q:;
    if(*pt) continue_from_local do_write;
    continue_from nominal;

  init:;
    continue_into TM2x·format_write(tape ,pt ,byte_n_of(char) ,&&init·nominal ,&&alloc_fail_local);
      init·nominal:;
        do_write = &&extend;
        continue_from_local next;
    
  extend:;
    continue_into TM2x·push_write(tape ,pt ,byte_n_of(char) ,&&next ,&&alloc_fail_local);

  next:;
    pt++;
    continue_from_local is_char_q;

  alloc_fail_local:;
    continue_from alloc_fail;

}



#endif

