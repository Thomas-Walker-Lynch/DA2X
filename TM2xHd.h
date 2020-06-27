#ifndef DA2XHD_LIB_H
#define DA2XHD_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "TM2x.h"

//#define TM2xHd_F_PREFIX
//#define TM2xHd_F_PREFIX extern inline
#define TM2xHd_F_PREFIX static inline


//--------------------------------------------------------------------------------
// dyanamic array iterator
//
  typedef struct {
    char *element_pt;
  } TM2xHd;

  TM2xHd_F_PREFIX void TM2xHd_rewind(TM2xHd *hdpt ,TM2x *dap){
    hdpt->element_pt = dap->byte_0_pt;
  }
  #define TM2xHd_Mount(hd ,dap) TM2xHd TM2xHd_ ## hd ,*hd; hd = &TM2xHd_  ## hd; TM2xHd_rewind(hd ,dap);

  TM2xHd_F_PREFIX void TM2xHd_step(TM2xHd *hdpt ,TM2x *dap ,byte_length_t distance){
    hdpt->element_pt += distance * dap->element_byte_length;
  }
  TM2xHd_F_PREFIX bool TM2xHd_is_on_tape(TM2xHd *hdpt ,TM2x *dap){
    return hdpt->element_pt < dap->byte_np1_pt && hdpt->element_pt >= dap->byte_0_pt;
  }
  TM2xHd_F_PREFIX void *TM2xHd_read(TM2xHd *hdpt){
    return hdpt->element_pt;
  }
  #define TM2xHd_Read(hd ,type) *((type *)hd->element_pt)

  TM2xHd_F_PREFIX void TM2xHd_write(TM2xHd *hdpt ,TM2x *dap ,void *src_element_pt){
    char *dst_element_pt = (char *)(hdpt->element_pt);
    memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(dap));
  }
  #define TM2xHd_Write(hd ,item) *((typeof(item) *)hd->element_pt) = item;


  // for dynamic allocation of hderators
  TM2xHd_F_PREFIX TM2xHd *TM2xHd_dynamic_mount(TM2x *dap){
    void *hdpt = malloc(byte_length_of(TM2xHd));
    assert(hdpt);
    TM2xHd_rewind(hdpt ,dap);
    return hdpt;
  }
  TM2xHd_F_PREFIX void TM2xHd_dynamic_unmount(TM2xHd *hdpt){
    free(hdpt);
  }

//--------------------------------------------------------------------------------
// quantifiers
//
  // calls f one time for each element of dap, in order
  TM2xHd_F_PREFIX void TM2xHd_foreach
  (
   TM2x *dap 
   ,void f(void *el ,void *context)
   ,void *context
   ){
    TM2xHd hd ,*hdpt; hdpt = &hd;
    TM2xHd_rewind(hdpt, dap);
    while( TM2xHd_is_on_tape(hdpt ,dap) ){
      f(TM2xHd_read(hdpt) ,context);
      TM2xHd_step(hdpt ,dap ,1);
    }
  }

  TM2xHd_F_PREFIX bool TM2xHd_all
  (TM2x *dap
   ,bool pred(void *el, void *context)
   ,void *context
   ){
    TM2xHd hd ,*hdpt; hdpt = &hd;
    TM2xHd_rewind(hdpt, dap);
    while( TM2xHd_is_on_tape(hdpt ,dap) && pred(TM2xHd_read(hdpt) ,context) ) TM2xHd_step(hdpt ,dap ,1);
    return !TM2xHd_is_on_tape(hdpt ,dap);
  }

  TM2xHd_F_PREFIX bool TM2xHd_exists
  (
   TM2x *dap
   ,bool pred(void *el, void *context)
   ,void *context
   ){
    TM2xHd hd ,*hdpt; hdpt = &hd;
    TM2xHd_rewind(hdpt, dap);
    while( TM2xHd_is_on_tape(hdpt ,dap) && !pred(TM2xHd_read(hdpt) ,context) ) TM2xHd_step(hdpt ,dap ,1);
    return TM2xHd_is_on_tape(hdpt ,dap);
  }

  // version of exists that works whdh an hderator so that 1) hd may be used to find the element that
  // makes pred true. 2) hd may be called multiple times to find all the elements where pred is true
  TM2xHd_F_PREFIX void TM2xHd_find
  (
   TM2xHd *hdpt
   ,TM2x *dap
   ,bool pred(void *el, void *context)
   ,void *context
   ){
    while( TM2xHd_is_on_tape(hdpt ,dap) && !pred(TM2xHd_read(hdpt) ,context) ) TM2xHd_step(hdpt ,dap ,1);
  }

  // all src elements that pred says are true are pushed on to the dst array
  TM2xHd_F_PREFIX void TM2xHd_find_all
  (
   TM2x *src_dap
   ,TM2x *dst_dap 
   ,bool pred(void *el, void *context)
   ){
    TM2xHd_Mount(hd ,src_dap);
    while( TM2xHd_is_on_tape(hd ,src_dap) ){
      if( pred(TM2xHd_read(hd) ,NULL) ) TM2x_push_write(dst_dap , TM2xHd_read(hd));
      TM2xHd_step(hd ,src_dap ,1);
    }
  }

//--------------------------------------------------------------------------------
// some useful predicates
//
  typedef struct{
    char *elpt;
    size_t byte_length;
  }TM2x_sized_el;
  TM2xHd_F_PREFIX bool TM2xHd_pred_bytes_eq( void *e0 ,void *context ){
    char *opa_pt = e0;
    TM2x_sized_el *opb_pt = context;
    return memcmp(opa_pt ,opb_pt->elpt ,opb_pt->byte_length) == 0;
  }
  TM2xHd_F_PREFIX bool TM2xHd_pred_cstring_eq( void *cs0 ,void *context ){
    char *opa_pt = cs0;
    TM2x_sized_el *opb_pt = context;
    return strncmp(opa_pt ,opb_pt->elpt ,opb_pt->byte_length) == 0;
  }

//--------------------------------------------------------------------------------
// set
//
#if 0
  // Adds a constraint on to a dynamic array. Typically this is to say that
  // the elements in the array will satistfy the constraint.
  typdef struct{
    char *dap;
    ,bool pred(void *el, void *context)
  }TM2x_contstrained_da;



  // push_write src_elmeent on array if pred not exists over dap
  // when pred is a comparison can be used to force order
  // when pred is equality can be used to get set behavior
  TM2xHd_F_PREFIX bool TM2xHd_push_write_unique
  (
   void *src_element_pt 
   TM2x_constrained_da qd
   ){
    TM2x_sized_el elb;
    elb.elpt = src_element_pt;
    elb.byte_length = TM2x_element_byte_length(qd.dap);
    if( !TM2xHD_exists(dap ,qd.pred ,&elb) ) TM2x_push_write(qd.dap ,src_element_pt);
  }

  TM2xHd_F_PREFIX bool TM2xHd_push_accumulate_unique
  (TM2x *acc_dap 
   ,TM2x *src_dap 
   ,bool pred(void *el, void *context)
   ){
    TM2x_qualified_da qd = {acc_dep ,pred};
    TM2xHd_foreach(src_dap ,TM2xHD_push_write_unique ,
  }
#endif


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
  TM2xHd_F_PREFIX void TM2xHd_f_free(void *item_pt ,void *context){
    free(item_pt);
  }

  TM2xHd_F_PREFIX void TM2xHd_f_string_eq(void *element_pt, void *sep){
    fprintf(stderr ,"%s%s" ,(char *)sep ,(char *)element_pt);
  }


#endif
