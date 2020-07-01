#ifndef DA2XHD_LIB_H
#define DA2XHD_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "TM2x.h"

/*
  element_pt is always element aligned and pointing to the base of an element.
 
*/


//#define TM2xHd_F_PREFIX
//#define TM2xHd_F_PREFIX extern inline
#define TM2xHd_F_PREFIX static inline


//--------------------------------------------------------------------------------
// dyanamic array iterator
//
  typedef struct {
    char *element_pt;
  } TM2xHd;

  #define TM2xHd_Mount(tape ,hd) TM2xHd TM2xHd_ ## hd ,*hd; hd = &TM2xHd_ ## hd; TM2xHd_rewind(tape ,hd);

  TM2xHd_F_PREFIX bool TM2xHd_is_on_tape(TM2x *tape ,TM2xHd *hd){
    return hd->element_pt <= TM2x_byte_n_pt(tape) && hd->element_pt >= TM2x_byte_0_pt(tape);
  }

  TM2xHd_F_PREFIX void TM2xHd_rewind(TM2x *tape ,TM2xHd *hd){
    hd->element_pt = TM2x_byte_0_pt(tape);
  }

  TM2xHd_F_PREFIX bool TM2xHd_step(TM2x *tape ,TM2xHd *hd ,address_t element_byte_n){
    if( hd->element_pt >= (char *)TM2x_element_n_pt(tape ,element_byte_n) ) return false;
    hd->element_pt += element_byte_n + 1;
    return true;
  }
  
  TM2xHd_F_PREFIX void *TM2xHd_pt(TM2xHd *hd){
    return hd->element_pt;
  }

  TM2xHd_F_PREFIX void TM2xHd_read(TM2xHd *hd ,void *dst_pt ,address_t element_byte_n){
    memcpyn(dst_pt, hd->element_pt, element_byte_n);
  }
  #define TM2xHd_Read(hd ,item) TM2xHd_read(hd ,&item ,byte_no_of(type_of(item)))
  #define TM2xHd_Read_Expr(hd ,type) *((type *)hd->element_pt)

  TM2xHd_F_PREFIX void TM2xHd_write(TM2xHd *hd ,void *src_element_pt ,address_t element_byte_n){
    memcpyn(hd->element_pt, src_element_pt, element_byte_n);
  }
  #define TM2xHd_Write(hd ,item) *((typeof(item) *)hd->element_pt) = item
  #define TM2xHd_Write_Lval(hd ,item) *((typeof(item) *)hd->element_pt)


//--------------------------------------------------------------------------------
// quantifiers
//
  // applies f to each element, in order starting at the current hd position, until reaching the end of the tape
  TM2xHd_F_PREFIX void TM2xHd_to_each
  (
   TM2x *tape
   ,TM2xHd *hd
   ,void *context
   ,void f(void *context ,void *el)
   ,address_t element_byte_n
   ){
    do{
      f(context ,TM2xHd_pt(hd));
    }while( TM2xHd_step(tape ,hd ,element_byte_n) );
  }

  // applies pred to each element until either pred is not true, or reaching the end of the tape
  TM2xHd_F_PREFIX bool TM2xHd_all
  (
   TM2x *tape
   ,TM2xHd *hd
   ,void *context
   ,bool pred(void *context ,void *el)
   ,address_t element_byte_n
   ){
    do{
      if( !pred(context ,TM2xHd_pt(hd)) ) return false;
    }while( TM2xHd_step(tape ,hd ,element_byte_n) );
    return true;
  }

  TM2xHd_F_PREFIX bool TM2xHd_exists
  (
   TM2x *tape
   ,TM2xHd *hd
   ,void *context
   ,bool pred(void *context ,void *el)
   ,address_t element_byte_n
   ){
    do{
      if( pred(context ,TM2xHd_pt(hd)) ) return true;
    }while( TM2xHd_step(tape ,hd ,element_byte_n) );
    return false;
  }

#if 0


//--------------------------------------------------------------------------------
// set
//
  // Adds a constraint on to a dynamic array. Typically this is to say that
  // the elements in the array will satistfy the constraint.
  typdef struct{
    char *tape;
    ,bool pred(void *el, void *context)
  }TM2x_contstrained_da;




  // push_write src_elmeent on array if pred not exists over tape
  // when pred is a comparison can be used to force order
  // when pred is equality can be used to get set behavior
  TM2xHd_F_PREFIX bool TM2xHd_push_write_unique
  (
   void *src_element_pt 
   TM2x_constrained_da qd
   ){
    TM2x_sized_el elb;
    elb.elpt = src_element_pt;
    elb.byte_length = TM2x_element_byte_length(qd.tape);
    if( !TM2xHd_exists(tape ,qd.pred ,&elb) ) TM2x_push_write(qd.tape ,src_element_pt);
  }

  TM2xHd_F_PREFIX bool TM2xHd_push_accumulate_unique
  (TM2x *acc_tape 
   ,TM2x *src_tape 
   ,bool pred(void *context ,void *el)
   ){
    TM2x_qualified_da qd = {acc_dep ,pred};
    TM2xHd_foreach(src_tape ,TM2xHd_push_write_unique ,
  }

//--------------------------------------------------------------------------------
// some useful predicates
//
  typedef struct{
    char *elpt;
    size_t byte_length;
  }TM2x_sized_el;

  TM2xHd_F_PREFIX bool TM2xHd_pred_bytes_eq(void *context ,void *e0){
    char *opa_pt = e0;
    TM2x_sized_el *opb_pt = context;
    return memcmp(opa_pt ,opb_pt->elpt ,opb_pt->byte_length) == 0;
  }
  TM2xHd_F_PREFIX bool TM2xHd_pred_cstring_eq(void *context ,void *cs0){
    char *opa_pt = cs0;
    TM2x_sized_el *opb_pt = context;
    return strncmp(opa_pt ,opb_pt->elpt ,opb_pt->byte_length) == 0;
  }



//--------------------------------------------------------------------------------
// utilities
//
  // elements are integers
  TM2xHd_F_PREFIX void TM2xHd_f_print_int(void *element_pt, void *sep){
    fprintf(stderr ,"%s%d" ,(char *)sep ,*(int *)element_pt);
  }

  // elements are char *
  TM2xHd_F_PREFIX void TM2xHd_f_print_string(void *element_pt, void *sep){
    fprintf(stderr ,"%s%s" ,(char *)sep ,(char *)element_pt);
  }

  // each element is a pointer to dynamic memory, and that memory is to be freed:
  TM2xHd_F_PREFIX void TM2xHd_f_free(void *context ,void *item_pt){
    free(item_pt);
  }

  TM2xHd_F_PREFIX void TM2xHd_f_string_eq(void *element_pt, void *sep){
    fprintf(stderr ,"%s%s" ,(char *)sep ,(char *)element_pt);
  }


#endif
#endif
