#ifndef DA2XHD_LIB_H
#define DA2XHD_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "TM2x.h"

/*
  element_pt is always element aligned and pointing to the base of an element.

  operand order:
    context just before pred or function
    element_byte_n  just after hd, and if not hd, just after tape
 
*/


//#define TM2xHd·F_PREFIX
//#define TM2xHd·F_PREFIX extern inline
#define TM2xHd·F_PREFIX static inline


//--------------------------------------------------------------------------------
// allocation
//
  typedef struct {
    char *element_pt;
  } TM2xHd;
  #define TM2xHd·AllocStaticRewind(tape ,hd)\
    TM2xHd TM2xHd· ## hd ,*hd; hd = &TM2xHd· ## hd; TM2xHd·rewind(tape ,hd);

//--------------------------------------------------------------------------------
// adjectives
//
  TM2xHd·F_PREFIX continuation TM2xHd·is_on_tape
  ( TM2x *tape 
    ,TM2xHd *hd 
    ,continuation is_true  
    ,continuation is_false
    ){
    if( hd->element_pt <= TM2x·byte_n_pt(tape) && hd->element_pt >= TM2x·byte_0_pt(tape) ) continue_via_trampoline is_true;
    continue_via_trampoline is_false;
  }
  TM2xHd·F_PREFIX continuation TM2xHd·at_element_n
  ( TM2x *tape 
    ,TM2xHd *hd 
    ,address_t element_byte_n
    ,continuation is_true  
    ,continuation is_false
    ){
    if( hd->element_pt == TM2x·element_n_pt(tape ,element_byte_n) ) continue_via_trampoline is_true;
    continue_via_trampoline is_false;
  }

//--------------------------------------------------------------------------------
// motion
//
  // this also initializes an hd
  TM2xHd·F_PREFIX void TM2xHd·rewind(TM2x *tape ,TM2xHd *hd){
    hd->element_pt = TM2x·byte_0_pt(tape);
  }

  TM2xHd·F_PREFIX void TM2xHd·unguarded_step(TM2xHd *hd ,address_t element_byte_n){
    hd->element_pt += element_byte_n + 1;
  }

  TM2xHd·F_PREFIX continuation TM2xHd·step
  ( TM2x *tape 
    ,TM2xHd *hd 
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation end_of_tape
    ){
    continue_into TM2xHd·at_element_n(tape ,hd ,element_byte_n ,&&at_n ,&&not_at_n);
    at_n:;
      continue_via_trampoline end_of_tape;
    not_at_n:;
      TM2xHd·unguarded_step(hd ,element_byte_n);
      continue_via_trampoline nominal;
  }
  
  TM2xHd·F_PREFIX void *TM2xHd·pt(TM2xHd *hd){
    return hd->element_pt;
  }

  TM2xHd·F_PREFIX void TM2xHd·read(TM2xHd *hd ,address_t element_byte_n ,void *dst_pt){
    memcpyn(dst_pt, hd->element_pt, element_byte_n);
  }
  #define TM2xHd·Read(hd ,item) TM2xHd·read(hd ,byte_no_of(type_of(item)) ,&item)
  #define TM2xHd·Read_Expr(hd ,type) *((type *)hd->element_pt)

  TM2xHd·F_PREFIX void TM2xHd·write(TM2xHd *hd ,address_t element_byte_n ,void *src_element_pt){
    memcpyn(hd->element_pt ,src_element_pt ,element_byte_n);
  }
  #define TM2xHd·Write(hd ,item) *((typeof(item) *)hd->element_pt) = item
  #define TM2xHd·Write_Lval(hd ,item) *((typeof(item) *)hd->element_pt)


//--------------------------------------------------------------------------------
// quantifiers
//

  // nah .. better to implement this with memcpyn, see TM2x·format_write
  // shallow copy tape_src elements to the end of tape_acc
  TM2xHd·F_PREFIX continuation TM2x·cat
  ( TM2x *tape_acc
    ,TM2x *tape_src
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation allocation_failed
    ){
    TM2xHd·AllocStaticRewind(tape_src, hd_src);
    loop:
      continue_into TM2x·push(tape_acc ,TM2xHd·pt(hd_src) ,element_byte_n ,&&pw_nominal ,&&pw_allocation_failed);
      pw_nominal:
        continue_into TM2xHd·step(tape_src ,hd_src ,element_byte_n ,&&loop ,&&at_n);
          at_n: 
            continue_via_trampoline nominal;
      pw_allocation_failed: 
        continue_via_trampoline allocation_failed;
  }

  // applies f to each element, in order starting at the current hd position, until reaching the end of the tape
  // should f accept/return continuations?  Should it take an hd instead of an element?
  TM2xHd·F_PREFIX void TM2xHd·apply_to_each
  ( TM2x *tape
    ,TM2xHd *hd
    ,address_t element_byte_n
    ,void *context
    ,void f(void *context ,void *el ,address_t element_byte_n)
    ){
    TM2xHd·apply_to_each:
      f(context ,TM2xHd·pt(hd) ,element_byte_n);
      continue_into TM2xHd·at_element_n(tape ,hd ,element_byte_n ,&&hd_at_n ,&&hd_not_at_n);
        hd_at_n:
          return;
        hd_not_at_n:
          TM2xHd·unguarded_step(hd ,element_byte_n);
          continue_from TM2xHd·apply_to_each;
  }

  // applies pred to each element until either pred is not true, or reaching the end of the tape
  TM2xHd·F_PREFIX continuation TM2xHd·all
  ( TM2x *tape
    ,TM2xHd *hd
    ,address_t element_byte_n
    ,void *context
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation true_for_all
    ,continuation an_exception
    ){
    TM2xHd·all:
      continue_into pred(context ,TM2xHd·pt(hd) ,element_byte_n ,&&pred_true ,&&pred_false);
        pred_true:
          continue_into TM2xHd·at_element_n(tape ,hd ,element_byte_n ,&&at_n , &&not_at_n);
            at_n: 
              continue_via_trampoline true_for_all;
            not_at_n: 
              TM2xHd·unguarded_step(hd ,element_byte_n);
              continue_from TM2xHd·all;
        pred_false:
          continue_via_trampoline an_exception;
  }

  TM2xHd·F_PREFIX continuation TM2xHd·exists
  ( TM2x *tape
    ,TM2xHd *hd
    ,address_t element_byte_n
    ,void *context
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation found_one
    ,continuation not_on_tape
    ){
    TM2xHd·exists:
      continue_into pred(context ,TM2xHd·pt(hd) ,element_byte_n ,&&pred_true ,&&pred_false );
        pred_true:
          continue_via_trampoline found_one;
        pred_false:
          continue_into TM2xHd·at_element_n(tape ,hd ,element_byte_n ,&&hd_at_n , &&hd_not_at_n);
            hd_at_n:
              continue_via_trampoline not_on_tape;
            hd_not_at_n: 
              TM2xHd·unguarded_step(hd ,element_byte_n);
              continue_from TM2xHd·exists;
  }

//--------------------------------------------------------------------------------
// set
//

  // no push if pred exists on tape
  // no push if cannot allocate space
  // otherwise does a push
  // when pred is a comparison can be used to force order
  // when pred is equality treats tape like a set
  TM2xHd·F_PREFIX continuation TM2xHd·push_not_exists
  ( TM2x *tape_dst
    ,void *src_element_pt 
    ,address_t element_byte_n
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation wrote_it
    ,continuation already_on_tape_dst
    ,continuation allocate_failed
    ){
    TM2xHd·AllocStaticRewind(tape_dst ,hd);
    continue_into TM2xHd·exists
      ( tape_dst 
        ,hd 
        ,element_byte_n 
        ,src_element_pt
        ,pred
        ,&&found_one
        ,&&not_found
        );
      found_one:
        continue_via_trampoline already_on_tape_dst;
      not_found:
        continue_into TM2x·push(tape_dst ,src_element_pt ,element_byte_n ,&&pw_wrote_it ,&&pw_alloc_failed);
          pw_wrote_it:
            continue_via_trampoline wrote_it;
          pw_alloc_failed:
            continue_via_trampoline allocate_failed;
  }
  #define TM2xHd·Push_Not_Exists(tape_dst ,item ,pred ,wrote_it ,already_on_tape ,allocate_failed) \
    continue_into TM2xHd·push_not_exists(tape_dst ,&item ,byte_n_of(type_of(item)) ,pred ,wrote_it ,already_on_tape ,allocate_failed)

  // -accumulates elements from set_src which are not already in set_acc into set_acc.
  // -returns whether set_src was a subset of set_acc even before the union (make this a separate continuation?)
  // -context given to the pred is a pointer to the src element
  TM2xHd·F_PREFIX continuation TM2xHd·accumulate_union
  ( TM2x *set_acc
    ,TM2x *set_src
    ,TM2xHd *hd_src
    ,address_t element_byte_n
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,bool *subset
    ,continuation nominal
    ,continuation allocation_failed
    ){
    if(subset) *subset = true;
    TM2xHd·accumulate_union:
      continue_into TM2xHd·push_not_exists
        ( set_acc 
          ,TM2xHd·pt(hd_src) 
          ,element_byte_n 
          ,pred
          ,&& pw_wrote_it
          ,&& pw_already_on_tape
          ,&& pw_allocate_failed
          );
        pw_wrote_it:
          if(subset) *subset = false;
        pw_already_on_tape:
          continue_into TM2xHd·at_element_n(set_src ,hd_src ,element_byte_n ,&&at_n , &&not_at_n);
            at_n:
              continue_via_trampoline nominal;
            not_at_n: 
              TM2xHd·unguarded_step(hd_src ,element_byte_n);
              continue_from TM2xHd·accumulate_union;
        pw_allocate_failed:
          continue_via_trampoline allocation_failed;
    }

  // -> set_intersection = set_a intersection set_b
  // -> returns whether the sets set_a and set_b were found to be distinct,
  //    i.e. if initialization ever occurred on set_intersection
  // -> context given to the pred is a_element, the pred src element is the b_element
  // -> on allocation failure the intersection set might be partially created
  TM2xHd·F_PREFIX continuation TM2xHd·init_intersection
  ( TM2x *set_intersection
    ,TM2x *set_a
    ,TM2x *set_b
    ,address_t element_byte_n
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation init_intersection·nominal
    ,continuation init_intersection·empty
    ,continuation init_intersection·allocation_failed
    ){
    TM2xHd·AllocStaticRewind(set_a ,hd_a);
    TM2xHd·AllocStaticRewind(set_b ,hd_b);

      // when_found is either &&init or &&extend
    continuation do_write = &&init;

    exists:;
      continue_into TM2xHd·exists
        ( set_b 
          ,hd_b 
          ,element_byte_n 
          ,TM2xHd·pt(hd_a) 
          ,pred 
          ,do_write
          ,&&next
          );

    init:;  
      continue_into TM2x·format_write
        ( set_intersection 
          ,TM2xHd·pt(hd_a) 
          ,element_byte_n 
          ,&&init·nominal
          ,&&init·alloc_fail
          );
        init·nominal:;
          do_write = &&extend;
          continue_from next;
        init·alloc_fail:;
          continue_via_trampoline init_intersection·allocation_failed;
        
    extend:;
      continue_into TM2x·push
        ( set_intersection 
          ,TM2xHd·pt(hd_a) 
          ,element_byte_n 
          ,&&extend·nominal 
          ,&&extend·alloc_fail
          );        
        extend·nominal:;
          continue_from next;
        extend·alloc_fail:;
          continue_via_trampoline init_intersection·allocation_failed;

    next:;
      TM2xHd·rewind(set_b ,hd_b);
      continue_into TM2xHd·step
        ( set_a
          ,hd_a
          ,element_byte_n
          ,&&loop
          ,&&next·end_of_tape
          );
        loop:; // this little detour assists with debugging
          continue_from exists;
        next·end_of_tape:;
          if( do_write == &&init )
            continue_via_trampoline init_intersection·empty;
          else
            continue_via_trampoline init_intersection·nominal;
  }


//--------------------------------------------------------------------------------
// some useful predicates
//

  TM2xHd·F_PREFIX continuation TM2xHd·true
  ( void *context 
    ,TM2x *tape 
    ,TM2xHd *hd
    ,address_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    continue_via_trampoline pred_true;
  }

  TM2xHd·F_PREFIX continuation TM2xHd·false
  ( void *context 
    ,void *a_e0 
    ,address_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    continue_via_trampoline pred_false;
  }

  TM2xHd·F_PREFIX continuation TM2xHd·pred_bytes_eq
  ( void *context 
    ,void *a_e0 
    ,address_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    char *e0 = a_e0;
    char *e1 = context;
    if( memcmpn(e0 ,e1 ,element_byte_n) == 0 )
      continue_via_trampoline pred_true;
    else
      continue_via_trampoline pred_false;
  }

  TM2xHd·F_PREFIX continuation TM2xHd·pred_cstring_eq
  ( void *context 
    ,void *a_e0 
    ,address_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    char *e0 = a_e0;
    char *e1 = context;
    if( strncmpn(e0 ,e1 ,element_byte_n) == 0 )
      continue_via_trampoline pred_true;
    else
      continue_via_trampoline pred_false;
  }

//--------------------------------------------------------------------------------
// some utility functions typically be used with apply_to_each
//
  // each element is a pointer to dynamic memory, and that memory is to be freed:
  TM2xHd·F_PREFIX void TM2xHd·f_free(void *context ,void *element_pt ,address_t element_byte_n){
    free(element_pt);
  }

  // elements are integers to be printed
  // could improve this by getting the integer size from element_byte_n
  TM2xHd·F_PREFIX void TM2xHd·f_print_int(void *context ,void *element_pt ,address_t element_byte_n){
    fprintf(stderr ,"%s%d" ,(char *)context ,*(int *)element_pt);
  }


#endif
