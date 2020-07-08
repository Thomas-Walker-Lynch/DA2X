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


//#define TM2xHd_F_PREFIX
//#define TM2xHd_F_PREFIX extern inline
#define TM2xHd_F_PREFIX static inline


//--------------------------------------------------------------------------------
// allocation
//
  typedef struct {
    char *element_pt;
  } TM2xHd;
  #define TM2xHd_AllocStaticRewind(tape ,hd)\
    TM2xHd TM2xHd_ ## hd ,*hd; hd = &TM2xHd_ ## hd; TM2xHd_rewind(tape ,hd);

//--------------------------------------------------------------------------------
// adjectives
//
  TM2xHd_F_PREFIX continuation TM2xHd_is_on_tape
  ( TM2x *tape 
    ,TM2xHd *hd 
    ,continuation is_true  
    ,continuation is_false
    ){
    if( hd->element_pt <= TM2x_byte_n_pt(tape) && hd->element_pt >= TM2x_byte_0_pt(tape) ) continue_from is_true;
    continue_from is_false;
  }
  TM2xHd_F_PREFIX continuation TM2xHd_at_element_n
  ( TM2x *tape 
    ,TM2xHd *hd 
    ,address_t element_byte_n
    ,continuation is_true  
    ,continuation is_false
    ){
    if( hd->element_pt == TM2x_element_n_pt(tape ,element_byte_n) ) continue_from is_true;
    continue_from is_false;
  }

//--------------------------------------------------------------------------------
// motion
//
  // this also initializes an hd
  TM2xHd_F_PREFIX void TM2xHd_rewind(TM2x *tape ,TM2xHd *hd){
    hd->element_pt = TM2x_byte_0_pt(tape);
  }

  TM2xHd_F_PREFIX void TM2xHd_step(TM2xHd *hd ,address_t element_byte_n){
      hd->element_pt += element_byte_n + 1;
  }
  
  TM2xHd_F_PREFIX void *TM2xHd_pt(TM2xHd *hd){
    return hd->element_pt;
  }

  TM2xHd_F_PREFIX void TM2xHd_read(TM2xHd *hd ,address_t element_byte_n ,void *dst_pt){
    memcpyn(dst_pt, hd->element_pt, element_byte_n);
  }
  #define TM2xHd_Read(hd ,item) TM2xHd_read(hd ,byte_no_of(type_of(item)) ,&item)
  #define TM2xHd_Read_Expr(hd ,type) *((type *)hd->element_pt)

  TM2xHd_F_PREFIX void TM2xHd_write(TM2xHd *hd ,address_t element_byte_n ,void *src_element_pt){
    memcpyn(hd->element_pt ,src_element_pt ,element_byte_n);
  }
  #define TM2xHd_Write(hd ,item) *((typeof(item) *)hd->element_pt) = item
  #define TM2xHd_Write_Lval(hd ,item) *((typeof(item) *)hd->element_pt)


//--------------------------------------------------------------------------------
// quantifiers
//

  // nah .. better to implement this with memcpyn, see TM2x_format_copy
  // shallow copy tape_src elements to the end of tape_acc
  TM2xHd_F_PREFIX continuation TM2x_cat
  ( TM2x *tape_acc
    ,TM2x *tape_src
    ,address_t element_byte_n
    ,continuation nominal
    ,continuation allocation_failed
    ){
    TM2xHd_AllocStaticRewind(tape_src, hd_src);
    loop:
      continue_into TM2x_push_write(tape_acc ,TM2xHd_pt(hd_src) ,element_byte_n ,&&pw_nominal ,&&pw_allocation_failed);
      pw_nominal:
        continue_into TM2xHd_at_element_n(tape_src ,hd_src ,element_byte_n ,&&at_n , &&not_at_n);
          at_n: 
            continue_from nominal;
          not_at_n: 
            TM2xHd_step(hd_src ,element_byte_n);
            continue_from_local loop;
      pw_allocation_failed: 
        continue_from allocation_failed;
  }

  // applies f to each element, in order starting at the current hd position, until reaching the end of the tape
  // should f accept/return continuations?  Should it take an hd instead of an element?
  TM2xHd_F_PREFIX void TM2xHd_apply_to_each
  ( TM2x *tape
    ,TM2xHd *hd
    ,address_t element_byte_n
    ,void *context
    ,void f(void *context ,void *el ,address_t element_byte_n)
    ){
    TM2xHd_apply_to_each:
      f(context ,TM2xHd_pt(hd) ,element_byte_n);
      continue_into TM2xHd_at_element_n(tape ,hd ,element_byte_n ,&&hd_at_n ,&&hd_not_at_n);
        hd_at_n:
          return;
        hd_not_at_n:
          TM2xHd_step(hd ,element_byte_n);
          continue_from_local TM2xHd_apply_to_each;
  }

  // applies pred to each element until either pred is not true, or reaching the end of the tape
  TM2xHd_F_PREFIX continuation TM2xHd_all
  ( TM2x *tape
    ,TM2xHd *hd
    ,address_t element_byte_n
    ,void *context
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation true_for_all
    ,continuation an_exception
    ){
    TM2xHd_all:
      continue_into pred(context ,TM2xHd_pt(hd) ,element_byte_n ,&&pred_true ,&&pred_false);
        pred_true:
          continue_into TM2xHd_at_element_n(tape ,hd ,element_byte_n ,&&at_n , &&not_at_n);
            at_n: 
              continue_from true_for_all;
            not_at_n: 
              TM2xHd_step(hd ,element_byte_n);
              continue_from_local TM2xHd_all;
        pred_false:
          continue_from an_exception;
  }

  TM2xHd_F_PREFIX continuation TM2xHd_exists
  ( TM2x *tape
    ,TM2xHd *hd
    ,address_t element_byte_n
    ,void *context
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation found_one
    ,continuation not_on_tape
    ){
    TM2xHd_exists:
      continue_into pred(context ,TM2xHd_pt(hd) ,element_byte_n ,&&pred_true ,&&pred_false );
        pred_true:
          continue_from found_one;
        pred_false:
          continue_into TM2xHd_at_element_n(tape ,hd ,element_byte_n ,&&hd_at_n , &&hd_not_at_n);
            hd_at_n:
              continue_from not_on_tape;
            hd_not_at_n: 
              TM2xHd_step(hd ,element_byte_n);
              continue_from_local TM2xHd_exists;
  }

//--------------------------------------------------------------------------------
// set
//

  // no push_write if pred exists on tape
  // no push_write if cannot allocate space
  // otherwise does a push_write
  // when pred is a comparison can be used to force order
  // when pred is equality treats tape like a set
  TM2xHd_F_PREFIX continuation TM2xHd_push_write_not_exists
  ( TM2x *tape_dst
    ,void *src_element_pt 
    ,address_t element_byte_n
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation wrote_it
    ,continuation already_on_tape_dst
    ,continuation allocate_failed
    ){
    TM2xHd_AllocStaticRewind(tape_dst ,hd);
    continue_into TM2xHd_exists
      ( tape_dst 
        ,hd 
        ,element_byte_n 
        ,src_element_pt
        ,pred
        ,&&found_one
        ,&&not_found
        );
      found_one:
        continue_from already_on_tape_dst;
      not_found:
        continue_into TM2x_push_write(tape_dst ,src_element_pt ,element_byte_n ,&&pw_wrote_it ,&&pw_alloc_failed);
          pw_wrote_it:
            continue_from wrote_it;
          pw_alloc_failed:
            continue_from allocate_failed;
  }
  #define TM2xHd_Push_Write_Not_Exists(tape_dst ,item ,pred ,wrote_it ,already_on_tape ,allocate_failed) \
    continue_into TM2xHd_push_write_not_exists(tape_dst ,&item ,byte_n_of(type_of(item)) ,pred ,wrote_it ,already_on_tape ,allocate_failed)

  // -accumulates copies of elements from set_src into set_acc
  // -returns whether set_src was a subset of set_acc even before the union
  // -context given to the pred is a pointer to the src element
  TM2xHd_F_PREFIX continuation TM2xHd_accumulate_union
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
    TM2xHd_accumulate_union:
      continue_into TM2xHd_push_write_not_exists
        ( set_acc 
          ,TM2xHd_pt(hd_src) 
          ,element_byte_n 
          ,pred
          ,&& pw_wrote_it
          ,&& pw_already_on_tape
          ,&& pw_allocate_failed
          );
        pw_wrote_it:
          if(subset) *subset = false;
        pw_already_on_tape:
          continue_into TM2xHd_at_element_n(set_src ,hd_src ,element_byte_n ,&&at_n , &&not_at_n);
            at_n:
              continue_from nominal;
            not_at_n: 
              TM2xHd_step(hd_src ,element_byte_n);
              continue_from_local TM2xHd_accumulate_union;
        pw_allocate_failed:
          continue_from allocation_failed;
    }

  // -> set_intersection -> set_a intersection set_b
  // -> returns whether the sets set_a and set_b were found to be distinct,
  //    i.e. if initialization ever occurred on set_intersection
  // -> context given to the pred is a_element, the pred src element is the b_element
  // -> on allocation failure the intersection set might be partially created
  TM2xHd_F_PREFIX continuation TM2xHd_init_intersection
  ( TM2x *set_intersection
    ,TM2x *set_a
    ,TM2x *set_b
    ,address_t element_byte_n
    ,continuation pred(void *context ,void *el ,address_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,bool *distinct
    ,continuation nominal
    ,continuation allocation_failed
    ){
    TM2xHd_AllocStaticRewind(set_a ,hd_a);
    TM2xHd_AllocStaticRewind(set_b ,hd_b);

  if(distinct) *distinct = true;

  // we look for a first common element between sets a and b.  If we fine one, we will initialize set_intersection
  search_first:
    continue_into TM2xHd_exists
      ( set_b 
        ,hd_b 
        ,element_byte_n 
        ,TM2xHd_pt(hd_a) ,pred 
        ,&&first_hda_found_in_set_b
        ,&&still_searching_for_first
        );
      first_hda_found_in_set_b:
        continue_into TM2x_format_write(set_intersection ,TM2xHd_pt(hd_a) ,element_byte_n ,&&nominal_0 ,&&fail_0);
          nominal_0:
            if(distinct) *distinct = false;
            continue_from_local extend;
          fail_0:
            continue_from allocation_failed;
      still_searching_for_first:
        continue_into TM2xHd_at_element_n(set_a ,hd_a ,element_byte_n ,&&at_n_0 , &&not_at_n_0);
          at_n_0:
            continue_from nominal;
          not_at_n_0: 
            TM2xHd_step(hd_a ,element_byte_n);
            TM2xHd_rewind(set_b ,hd_b);
            continue_from_local search_first;
            
  // if there are more common elements between sets a and b, we use them to extend set_intersection
  extend:  
    continue_into TM2xHd_at_element_n(set_a ,hd_a ,element_byte_n ,&&at_n_1 , &&not_at_n_1);
      at_n_1:
        continue_from nominal;
      not_at_n_1: 
        TM2xHd_step(hd_a ,element_byte_n);
        TM2xHd_rewind(set_b ,hd_b);
        continue_into TM2xHd_exists(set_b ,hd_b ,element_byte_n ,TM2xHd_pt(hd_a) ,pred ,&&another ,&&end_of_tape);
          another:
            continue_into TM2x_push_write(set_intersection ,TM2xHd_pt(hd_a) ,element_byte_n ,&&nominal_1 ,&&fail_1);
              nominal_1:
                continue_from_local extend;
              fail_1:              
                continue_from allocation_failed;
          end_of_tape:
            continue_from nominal;
  }

//--------------------------------------------------------------------------------
// some useful predicates
//
  TM2xHd_F_PREFIX continuation TM2xHd_pred_bytes_eq
  ( void *context 
    ,void *a_e0 
    ,address_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    char *e0 = a_e0;
    char *e1 = context;
    if( memcmpn(e0 ,e1 ,element_byte_n) == 0 )
      continue_from pred_true;
    else
      continue_from pred_false;
  }
  TM2xHd_F_PREFIX continuation TM2xHd_pred_cstring_eq
  ( void *context 
    ,void *a_e0 
    ,address_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    char *e0 = a_e0;
    char *e1 = context;
    if( strncmpn(e0 ,e1 ,element_byte_n) == 0 )
      continue_from pred_true;
    else
      continue_from pred_false;
  }

//--------------------------------------------------------------------------------
// some utility functions typically be used with apply_to_each
//
  // each element is a pointer to dynamic memory, and that memory is to be freed:
  TM2xHd_F_PREFIX void TM2xHd_f_free(void *context ,void *element_pt ,address_t element_byte_n){
    free(element_pt);
  }

  // elements are integers to be printed
  // could improve this by getting the integer size from element_byte_n
  TM2xHd_F_PREFIX void TM2xHd_f_print_int(void *context ,void *element_pt ,address_t element_byte_n){
    fprintf(stderr ,"%s%d" ,(char *)context ,*(int *)element_pt);
  }

  // elements are char *
  TM2xHd_F_PREFIX void TM2xHd_f_print_cstring(void *context ,void *element_pt ,address_t element_byte_n){
    fprintf(stderr ,"%s%s" ,(char *)context ,(char *)element_pt);
  }


#endif
