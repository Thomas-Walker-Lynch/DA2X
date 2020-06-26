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
  TM2xHd_F_PREFIX void TM2xHd_foreach(TM2x *dap, void f(void *, void *), void *context){
    TM2xHd hd ,*hdpt; hdpt = &hd;
    TM2xHd_rewind(hdpt, dap);
    while( TM2xHd_is_on_tape(hdpt ,dap) ){
      f(TM2xHd_read(hdpt) ,context);
      TM2xHd_step(hdpt ,dap ,1);
    }
  }

  TM2xHd_F_PREFIX bool TM2xHd_all(TM2x *dap, bool pred(void *, void *), void *context){
    TM2xHd hd ,*hdpt; hdpt = &hd;
    TM2xHd_rewind(hdpt, dap);
    while( TM2xHd_is_on_tape(hdpt ,dap) && pred(TM2xHd_read(hdpt) ,context) ) TM2xHd_step(hdpt ,dap ,1);
    return !TM2xHd_is_on_tape(hdpt ,dap);
  }

  TM2xHd_F_PREFIX bool TM2xHd_exists(TM2x *dap, bool pred(void *, void *), void *context){
    TM2xHd hd ,*hdpt; hdpt = &hd;
    TM2xHd_rewind(hdpt, dap);
    while( TM2xHd_is_on_tape(hdpt ,dap) && !pred(TM2xHd_read(hdpt) ,context) ) TM2xHd_step(hdpt ,dap ,1);
    return TM2xHd_is_on_tape(hdpt ,dap);
  }

  // version of exists that works whdh an hderator so that 1) hd may be used to find the element that
  // makes pred true. 2) hd may be called multiple times to find all the elements where pred is true
  TM2xHd_F_PREFIX void TM2xHd_find(TM2xHd *hdpt ,TM2x *dap, bool pred(void *, void *), void *context){
    while( TM2xHd_is_on_tape(hdpt ,dap) && !pred(TM2xHd_read(hdpt) ,context) ) TM2xHd_step(hdpt ,dap ,1);
  }

  // all src elements that pred says are true are pushed on to the dst array
  TM2xHd_F_PREFIX void TM2xHd_find_all
  (
   TM2x *src_dap
   ,TM2x *dst_dap 
   ,bool pred(void *, void *)
   ){
    TM2xHd_Mount(hd ,src_dap);
    while( TM2xHd_is_on_tape(hd ,src_dap) ){
      if( pred(TM2xHd_read(hd) ,NULL) ) TM2x_push_write(dst_dap , TM2xHd_read(hd));
      TM2xHd_step(hd ,src_dap ,1);
    }
  }

//--------------------------------------------------------------------------------
// useful functions for mapping over arrays
//

  // each element is a pointer to dynamic memory, and that memory is to be freed:
  TM2xHd_F_PREFIX void TM2xHd_f_free(void *item_pt ,void *context){
    free(item_pt);
  }

  // elements are integers
  TM2xHd_F_PREFIX void TM2xHd_f_print_int(void *element_pt, char *sep){
    fprintf(stderr ,"%s%d" ,sep ,*(int *)element_pt);
  }

  // elements are char *
  TM2xHd_F_PREFIX void TM2xHd_f_print_string(void *element_pt, char *sep){
    fprintf(stderr ,"%s%s" ,sep ,(char *)element_pt);
  }

#endif
