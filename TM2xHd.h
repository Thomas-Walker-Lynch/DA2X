#ifndef DA2XHD_LIB_H
#define DA2XHD_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "TM2x.h"

// 
// .. if we add dap and hdpt to context, pred can ask about its neighbors (windowing)



// in general, arg order:  context ,dap ,hd ,..

//#define TM2xHd_F_PREFIX
//#define TM2xHd_F_PREFIX extern inline
#define TM2xHd_F_PREFIX static inline


//--------------------------------------------------------------------------------
// dyanamic array iterator
//
  typedef struct {
    TM2x *dap;
    char *element_pt;
  } TM2xHd;

  TM2xHd_F_PREFIX void TM2xHd_rewind(TM2xHd *hd){
    hd->element_pt = hd->dap->byte_0_pt;
  }
  #define TM2xHd_Mount(_dap ,_hd)                 \
    TM2xHd _hd ## _instance ,*_hd;                \
    _hd = &_hd ## _instance;                      \
    _hd->dap=_dap;                                \
    TM2xHd_rewind(_hd);

  TM2xHd_F_PREFIX void TM2xHd_step(TM2xHd *hd ,byte_length_t distance){
    hd->element_pt += distance * hd->dap->element_byte_length;
  }

  TM2xHd_F_PREFIX bool TM2xHd_is_on_tape(TM2xHd *hdpt){
    return hdpt->element_pt < hdpt->dap->byte_np1_pt && hdpt->element_pt >= hdpt->dap->byte_0_pt;
  }
  
  TM2xHd_F_PREFIX void *TM2xHd_readpt(TM2xHd *hdpt){
    return hdpt->element_pt;
  }
  TM2xHd_F_PREFIX void TM2xHd_read(TM2xHd *hdpt ,void *dst_pt){
    memcpy(dst_pt, hdpt->element_pt, TM2x_element_byte_length(hdpt->dap));
  }
  #define TM2xHd_Read(hd ,type) *((type *)hd->element_pt)

  TM2xHd_F_PREFIX void TM2xHd_write(TM2xHd *hdpt ,void *src_element_pt){
    char *dst_element_pt = (char *)(hdpt->element_pt);
    memcpy(dst_element_pt, src_element_pt, TM2x_element_byte_length(hdpt->dap));
  }
  #define TM2xHd_Write(hd ,item) *((typeof(item) *)hd->element_pt) = item;


  // for dynamic allocation of heads
  TM2xHd_F_PREFIX TM2xHd *TM2xHd_dynamic_mount(TM2x *dap){
    TM2xHd *hd = malloc(byte_length_of(TM2xHd));
    assert(hd);
    hd->dap = dap;
    TM2xHd_rewind(hd);
    return hd;
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
   void *context
   ,TM2x *dap 
   ,void f(void *context ,void *el)
   ){
    TM2xHd_Mount(dap ,hdpt);
    while( TM2xHd_is_on_tape(hdpt) ){
      f(context ,TM2xHd_readpt(hdpt));
      TM2xHd_step(hdpt ,1);
    }
  }

  TM2xHd_F_PREFIX bool TM2xHd_all
  (
   void *context
   ,TM2x *dap
   ,bool pred(void *context ,void *el)
   ){
    TM2xHd_Mount(dap ,hdpt);
    while( TM2xHd_is_on_tape(hdpt) && pred(context ,TM2xHd_readpt(hdpt)) ) TM2xHd_step(hdpt ,1);
    return !TM2xHd_is_on_tape(hdpt);
  }

  TM2xHd_F_PREFIX bool TM2xHd_exists
  (
   void *context
   ,TM2x *dap
   ,bool pred(void *context ,void *el)
   ){
    TM2xHd_Mount(dap ,hdpt);
    while( TM2xHd_is_on_tape(hdpt) && !pred(context ,TM2xHd_readpt(hdpt)) ) TM2xHd_step(hdpt ,1);
    return TM2xHd_is_on_tape(hdpt);
  }

  // version of exists that works with a head so that 1) hd may be used to find the element that
  // makes pred true. 2) hd may be called multiple times to find all the elements where pred is true
  TM2xHd_F_PREFIX void TM2xHd_find
  (
   void *context
   ,TM2xHd *hdpt
   ,bool pred(void *context ,void *el)
  ){
    while( TM2xHd_is_on_tape(hdpt) && !pred(context ,TM2xHd_readpt(hdpt)) ) TM2xHd_step(hdpt ,1);
  }

/*
  TM2xHd_F_PREFIX bool TM2xHd_push_write_unique
  (
   void *context
   ,TM2xHd *hdpt
   ,bool pred(void *el, void *context)
 
  void *src_element_pt 
   ){
*/


  // all src elements that pred says are true are pushed on to the dst array
  TM2xHd_F_PREFIX void TM2xHd_find_all
  (
   TM2x *src_dap
   ,TM2x *dst_dap 
   ,bool pred(void *context ,void *el)
   ){
    TM2xHd_Mount(src_dap ,hd);
    while( TM2xHd_is_on_tape(hd) ){
      // better to push alloc, then call TM2xHd_read to do the copy
      if( pred(TM2xHd_readpt(hd) ,NULL) ) TM2x_push_write(dst_dap , TM2xHd_readpt(hd));
      TM2xHd_step(hd  ,1);
    }
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
    if( !TM2xHd_exists(dap ,qd.pred ,&elb) ) TM2x_push_write(qd.dap ,src_element_pt);
  }

  TM2xHd_F_PREFIX bool TM2xHd_push_accumulate_unique
  (TM2x *acc_dap 
   ,TM2x *src_dap 
   ,bool pred(void *context ,void *el)
   ){
    TM2x_qualified_da qd = {acc_dep ,pred};
    TM2xHd_foreach(src_dap ,TM2xHd_push_write_unique ,
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
  TM2xHd_F_PREFIX void TM2xHd_f_free(void *context ,void *item_pt){
    free(item_pt);
  }

  TM2xHd_F_PREFIX void TM2xHd_f_string_eq(void *element_pt, void *sep){
    fprintf(stderr ,"%s%s" ,(char *)sep ,(char *)element_pt);
  }


#endif
