
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

  DA2xIt_F_PREFIX void DA2xIt_init(DA2xIt *dipt ,DA2x *dap){
    dipt->element_pt = dap->byte_0_pt;
  }
  #define DA2xIt_Make(it ,dap) DA2xIt DA2xIt_ ## it ,*it; it = &DA2xIt_  ## it; DA2xIt_init(it ,dap);

  DA2x_F_PREFIX void DA2xIt_data_dealloc(DA2x *dap){
  }
  DA2xIt_F_PREFIX void DA2xIt_inc(DA2xIt *dipt ,DA2x *dap){
    dipt->element_pt += dap->element_size;
  }
  DA2xIt_F_PREFIX bool DA2xIt_inbound(DA2xIt *dipt ,DA2x *dap){
    return dipt->element_pt < dap->byte_np1_pt;
  }
  DA2xIt_F_PREFIX void *DA2xIt_deref(DA2xIt *dipt){
    return dipt->element_pt;
  }
  #define DA2xIt_Deref(dipt ,type) *((type *)dipt->element_pt)

  // for dynamic allocation of iterators
  DA2xIt_F_PREFIX DA2xIt *DA2xIt_alloc(DA2x *dap){
    void *dipt = malloc(sizeof(DA2xIt));
    assert(dipt);
    DA2xIt_init(dipt ,dap);
    return dipt;
  }
  DA2xIt_F_PREFIX void DA2xIt_dealloc(DA2xIt *dipt){
    free(dipt);
  }

//--------------------------------------------------------------------------------
// quantifiers
//
  DA2xIt_F_PREFIX void DA2xIt_foreach(DA2x *dap, void f(void *, void *), void *context){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_init(dipt, dap);
    while( DA2xIt_inbound(dipt ,dap) ){
      f(DA2xIt_deref(dipt) ,context);
      DA2xIt_inc(dipt ,dap);
    }
  }

  DA2xIt_F_PREFIX bool DA2xIt_all(DA2x *dap, bool pred(void *, void *), void *context){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_init(dipt, dap);
    while( DA2xIt_inbound(dipt ,dap) && pred(DA2xIt_deref(dipt) ,context) ) DA2xIt_inc(dipt ,dap);
    return !DA2xIt_inbound(dipt ,dap);
  }

  DA2xIt_F_PREFIX bool DA2xIt_exists(DA2x *dap, bool pred(void *, void *), void *context){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_init(dipt, dap);
    while( DA2xIt_inbound(dipt ,dap) && !pred(DA2xIt_deref(dipt) ,context) ) DA2xIt_inc(dipt ,dap);
    return DA2xIt_inbound(dipt ,dap);
  }

  // version of exists that works with an iterator so that it may be called multiple times
  DA2xIt_F_PREFIX void DA2xIt_find(DA2xIt *dipt ,DA2x *dap, bool pred(void *, void *), void *context){
    while( DA2xIt_inbound(dipt ,dap) && !pred(DA2xIt_deref(dipt) ,context) ) DA2xIt_inc(dipt ,dap);
  }


//--------------------------------------------------------------------------------
// useful functions for quantifiers
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
