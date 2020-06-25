
#ifndef DA2XIT_LIB_H
#define DA2XIT_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//#define DA2xIt_F_PREFIX
//#define DA2xIt_F_PREFIX extern inline
#define DA2xIt_F_PREFIX static inline


//--------------------------------------------------------------------------------
// dyanamic array iterator
//
  typedef struct {
    char *element_pt;
  } DA2xIt;

  DA2xIt_F_PREFIX void DA2xIt_rewind(DA2xIt *dipt ,DA2x *dap){
    dipt->element_pt = dap->byte_0_pt;
  }
  #define DA2xIt_Mount(it ,dap) DA2xIt DA2xIt_ ## it ,*it; it = &DA2xIt_  ## it; DA2xIt_rewind(it ,dap);

  DA2xIt_F_PREFIX void DA2xIt_step(DA2xIt *dipt ,DA2x *dap ,size_t distance){
    dipt->element_pt += distance * dap->element_size;
  }
  DA2xIt_F_PREFIX bool DA2xIt_is_on_tape(DA2xIt *dipt ,DA2x *dap){
    return dipt->element_pt < dap->byte_np1_pt && dipt->element_pt >= dap->byte_0_pt;
  }
  DA2xIt_F_PREFIX void *DA2xIt_read(DA2xIt *dipt){
    return dipt->element_pt;
  }
  #define DA2xIt_Read(it ,type) *((type *)it->element_pt)

  DA2xIt_F_PREFIX void DA2xIt_write(DA2xIt *dipt ,DA2x *dap ,void *src_element_pt){
    char *dst_element_pt = (char *)(dipt->element_pt);
    memcpy(dst_element_pt, src_element_pt, DA2x_element_size(dap));
  }
  #define DA2xIt_Write(it ,item) *((typeof(item) *)it->element_pt) = item;


  // for dynamic allocation of iterators
  DA2xIt_F_PREFIX DA2xIt *DA2xIt_dynamic_mount(DA2x *dap){
    void *dipt = malloc(sizeof(DA2xIt));
    assert(dipt);
    DA2xIt_rewind(dipt ,dap);
    return dipt;
  }
  DA2xIt_F_PREFIX void DA2xIt_dynamic_unmount(DA2xIt *dipt){
    free(dipt);
  }

//--------------------------------------------------------------------------------
// quantifiers
//
  DA2xIt_F_PREFIX void DA2xIt_foreach(DA2x *dap, void f(void *, void *), void *context){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_rewind(dipt, dap);
    while( DA2xIt_is_on_tape(dipt ,dap) ){
      f(DA2xIt_read(dipt) ,context);
      DA2xIt_step(dipt ,dap ,1);
    }
  }

  DA2xIt_F_PREFIX bool DA2xIt_all(DA2x *dap, bool pred(void *, void *), void *context){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_rewind(dipt, dap);
    while( DA2xIt_is_on_tape(dipt ,dap) && pred(DA2xIt_read(dipt) ,context) ) DA2xIt_step(dipt ,dap ,1);
    return !DA2xIt_is_on_tape(dipt ,dap);
  }

  DA2xIt_F_PREFIX bool DA2xIt_exists(DA2x *dap, bool pred(void *, void *), void *context){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_rewind(dipt, dap);
    while( DA2xIt_is_on_tape(dipt ,dap) && !pred(DA2xIt_read(dipt) ,context) ) DA2xIt_step(dipt ,dap ,1);
    return DA2xIt_is_on_tape(dipt ,dap);
  }

  // version of exists that works with an iterator so that 1) it may be used to find the element that
  // makes pred true. 2) it may be called multiple times to find all the elements where pred is true
  DA2xIt_F_PREFIX void DA2xIt_find(DA2xIt *dipt ,DA2x *dap, bool pred(void *, void *), void *context){
    while( DA2xIt_is_on_tape(dipt ,dap) && !pred(DA2xIt_read(dipt) ,context) ) DA2xIt_step(dipt ,dap ,1);
  }

  // all src elements that pred says are true are pushed on to the dst array
  DA2xIt_F_PREFIX void DA2xIt_find_all
  (
   DA2x *src_dap
   ,DA2x *dst_dap 
   ,bool pred(void *, void *)
   ){
    DA2xIt_Mount(it ,src_dap);
    while( DA2xIt_is_on_tape(it ,src_dap) ){
      if( pred(DA2xIt_read(it) ,NULL) ) DA2x_push_write(dst_dap , DA2xIt_read(it));
      DA2xIt_step(it ,src_dap ,1);
    }
  }

//--------------------------------------------------------------------------------
// useful functions for mapping over arrays
//

  // each element is a pointer to dynamic memory, and that memory is to be freed:
  DA2xIt_F_PREFIX void DA2xIt_f_free(void *item_pt ,void *context){
    free(item_pt);
  }

  // elements are integers
  DA2xIt_F_PREFIX void DA2xIt_f_print_int(void *element_pt, char *sep){
    fprintf(stderr ,"%s%d" ,sep ,*(int *)element_pt);
  }

  // elements are char *
  DA2xIt_F_PREFIX void DA2xIt_f_print_string(void *element_pt, char *sep){
    fprintf(stderr ,"%s%s" ,sep ,(char *)element_pt);
  }



#endif
