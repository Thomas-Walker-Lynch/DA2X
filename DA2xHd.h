#ifndef DA2XHD_LIB_H
#define DA2XHD_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "DA2x.h"

//#define DA2xHd_F_PREFIX
//#define DA2xHd_F_PREFIX extern inline
#define DA2xHd_F_PREFIX static inline


//--------------------------------------------------------------------------------
// dyanamic array iterator
//
  typedef struct {
    char *element_pt;
  } DA2xHd;

  DA2xHd_F_PREFIX void DA2xHd_rewind(DA2xHd *hdpt ,DA2x *dap){
    hdpt->element_pt = dap->byte_0_pt;
  }
  #define DA2xHd_Mount(hd ,dap) DA2xHd DA2xHd_ ## hd ,*hd; hd = &DA2xHd_  ## hd; DA2xHd_rewind(hd ,dap);

  DA2xHd_F_PREFIX void DA2xHd_step(DA2xHd *hdpt ,DA2x *dap ,byte_length_t distance){
    hdpt->element_pt += distance * dap->element_byte_length;
  }
  DA2xHd_F_PREFIX bool DA2xHd_is_on_tape(DA2xHd *hdpt ,DA2x *dap){
    return hdpt->element_pt < dap->byte_np1_pt && hdpt->element_pt >= dap->byte_0_pt;
  }
  DA2xHd_F_PREFIX void *DA2xHd_read(DA2xHd *hdpt){
    return hdpt->element_pt;
  }
  #define DA2xHd_Read(hd ,type) *((type *)hd->element_pt)

  DA2xHd_F_PREFIX void DA2xHd_write(DA2xHd *hdpt ,DA2x *dap ,void *src_element_pt){
    char *dst_element_pt = (char *)(hdpt->element_pt);
    memcpy(dst_element_pt, src_element_pt, DA2x_element_byte_length(dap));
  }
  #define DA2xHd_Write(hd ,item) *((typeof(item) *)hd->element_pt) = item;


  // for dynamic allocation of hderators
  DA2xHd_F_PREFIX DA2xHd *DA2xHd_dynamic_mount(DA2x *dap){
    void *hdpt = malloc(byte_length_of(DA2xHd));
    assert(hdpt);
    DA2xHd_rewind(hdpt ,dap);
    return hdpt;
  }
  DA2xHd_F_PREFIX void DA2xHd_dynamic_unmount(DA2xHd *hdpt){
    free(hdpt);
  }

//--------------------------------------------------------------------------------
// quantifiers
//
  DA2xHd_F_PREFIX void DA2xHd_foreach(DA2x *dap, void f(void *, void *), void *context){
    DA2xHd hd ,*hdpt; hdpt = &hd;
    DA2xHd_rewind(hdpt, dap);
    while( DA2xHd_is_on_tape(hdpt ,dap) ){
      f(DA2xHd_read(hdpt) ,context);
      DA2xHd_step(hdpt ,dap ,1);
    }
  }

  DA2xHd_F_PREFIX bool DA2xHd_all(DA2x *dap, bool pred(void *, void *), void *context){
    DA2xHd hd ,*hdpt; hdpt = &hd;
    DA2xHd_rewind(hdpt, dap);
    while( DA2xHd_is_on_tape(hdpt ,dap) && pred(DA2xHd_read(hdpt) ,context) ) DA2xHd_step(hdpt ,dap ,1);
    return !DA2xHd_is_on_tape(hdpt ,dap);
  }

  DA2xHd_F_PREFIX bool DA2xHd_exists(DA2x *dap, bool pred(void *, void *), void *context){
    DA2xHd hd ,*hdpt; hdpt = &hd;
    DA2xHd_rewind(hdpt, dap);
    while( DA2xHd_is_on_tape(hdpt ,dap) && !pred(DA2xHd_read(hdpt) ,context) ) DA2xHd_step(hdpt ,dap ,1);
    return DA2xHd_is_on_tape(hdpt ,dap);
  }

  // version of exists that works whdh an hderator so that 1) hd may be used to find the element that
  // makes pred true. 2) hd may be called multiple times to find all the elements where pred is true
  DA2xHd_F_PREFIX void DA2xHd_find(DA2xHd *hdpt ,DA2x *dap, bool pred(void *, void *), void *context){
    while( DA2xHd_is_on_tape(hdpt ,dap) && !pred(DA2xHd_read(hdpt) ,context) ) DA2xHd_step(hdpt ,dap ,1);
  }

  // all src elements that pred says are true are pushed on to the dst array
  DA2xHd_F_PREFIX void DA2xHd_find_all
  (
   DA2x *src_dap
   ,DA2x *dst_dap 
   ,bool pred(void *, void *)
   ){
    DA2xHd_Mount(hd ,src_dap);
    while( DA2xHd_is_on_tape(hd ,src_dap) ){
      if( pred(DA2xHd_read(hd) ,NULL) ) DA2x_push_write(dst_dap , DA2xHd_read(hd));
      DA2xHd_step(hd ,src_dap ,1);
    }
  }

//--------------------------------------------------------------------------------
// useful functions for mapping over arrays
//

  // each element is a pointer to dynamic memory, and that memory is to be freed:
  DA2xHd_F_PREFIX void DA2xHd_f_free(void *item_pt ,void *context){
    free(item_pt);
  }

  // elements are integers
  DA2xHd_F_PREFIX void DA2xHd_f_print_int(void *element_pt, char *sep){
    fprintf(stderr ,"%s%d" ,sep ,*(int *)element_pt);
  }

  // elements are char *
  DA2xHd_F_PREFIX void DA2xHd_f_print_string(void *element_pt, char *sep){
    fprintf(stderr ,"%s%s" ,sep ,(char *)element_pt);
  }

#endif
