#ifndef TM2x·Char_H
#define TM2x·Char_H
#include "TM2xHd.h"

/*--------------------------------------------------------------------------------
  The array elements are chars.

*/  

continuation Chars·format_write
( TM2x *tape 
  ,char *pt
  ,address_t element_byte_n 
  ,continuation nominal
  ,continuation null_pt
  ,continuation alloc_fail
  ){
  
  if(!pt) continue_via_trampoline null_pt;
  continuation do_write = &&init; 

  is_char_q:;
    if(*pt) continue_from do_write;
    continue_via_trampoline nominal;

  init:;
    continue_into TM2x·format_write(tape ,pt ,byte_n_of(char) ,&&init·nominal ,&&alloc_fail_local);
      init·nominal:;
        do_write = &&extend;
        continue_from next;
    
  extend:;
    continue_into TM2x·push_write(tape ,pt ,byte_n_of(char) ,&&next ,&&alloc_fail_local);

  next:;
    pt++;
    continue_from is_char_q;

  alloc_fail_local:;
    continue_via_trampoline alloc_fail;

}



#endif

