#ifndef TM2x·CString_H
#define TM2x·CString_H
#include "TM2xHd.h"

//--------------------------------------------------------------------------------
// iniitialize the character array from a cstring
//
  TM2x·F_PREFIX continuation TM2x·format_write_cstring
  ( TM2x *tape 
    ,char *pt
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

  // elements are char *
  TM2xHd·F_PREFIX void TM2xHd·f_print_cstring(void *context ,void *element_pt ,address_t element_byte_n){
    fprintf(stderr ,"%s%s" ,(char *)context ,(char *)element_pt);
  }

// need a utf8 apply_to_each

//--------------------------------------------------------------------------------
// print
//
  // the array itself is a list of chars
  TM2xHd·F_PREFIX void TM2xHd·f_print_char_array(void *context ,void *element_pt ,address_t element_byte_n){
    // probably push a terminator, write, and pop it, though currently there is no hysterisis.  Wonder if
    // there is an easy way to add that.
  }

  // the array is a list of char * points to cstrings
  TM2xHd·F_PREFIX void TM2xHd·f_print_cstring(void *context ,void *element_pt ,address_t element_byte_n){
    fprintf(stderr ,"%s%s" ,(char *)context ,(char *)element_pt);
  }


#endif

