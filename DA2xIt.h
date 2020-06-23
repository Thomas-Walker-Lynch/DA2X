
#ifndef DA2XIT_LIB_H
#define DA2XIT_LIB_H
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//--------------------------------------------------------------------------------
// dyanamic array iterator
//
  typedef struct {
    char *element_pt;
  } DA2xIt;

  static inline void DA2xIt_init(DA2xIt *dipt ,void *dap){
    di->element_pt = dap->byte_0_pt;
  }
  static inline void DA2xIt_inc(DA2xIt *dipt ,void *dap){
    di->element_pt += dap->element_size;
  }
  static inline bool DA2xIt_inbound(DA2xIt *dipt ,void *dap){
    return dipt->element_pt < dap->byte_np1_pt;
  }
  static inline void *DA2xIt_deref(DA2xIt *dipt){
    return dipt->element_pt;
  }

  // convenience for dynamic allocation of iterators
  static inline DA2xIt *DA2xIt_alloc(void *dap){
    void *dipt = malloc(sizeof(DA2xIt));
    assert(dipt);
    DA2xIt_init(dipt ,dap);
    return dipt;
  }
  static inline void DA2xIt_dealloc(DA2xIt *dipt){
    free(dipt);
  }

//--------------------------------------------------------------------------------
// quantifiers
//
  static inline void Da_foreach(Da *dap, void f(void *, void *), void *closure){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_init(dipt, dap);
    while( DA2xIt_inbound(dipt ,dap) ){
      f(DA2xIt_deref(dipt) ,closure);
    DA2xIt_inc(dipt);
    }
  }

  static inline void Da_∀(Da *dap, void pred(void *, void *), void *closure){
    DA2xIt di ,*dipt; dipt = &di;
    DA2xIt_init(dipt, dap);
    while( DA2xIt_inbound(dipt ,dap) && pred(DA2xIt_deref(dipt) ,closure) ) DA2xIt_inc(dipt);
    return !DA2xIt_inbound(dipt ,dap);
  }

  // returns pointer to first item found
  // should pass in iterator so that the search can be called again after finding the first one
  static inline void Da_∃(Da *dap, void pred(void *, void *), void *closure){
    char *element_pt = Da_at_least_index_pt(dap);
    bool iterate;
    while( DA2xIt_inbound(dipt ,dap) && !pred(DA2xIt_deref(dipt) ,closure) ) DA2xIt_inc(dipt);
    return DA2xIt_inbound(dipt ,dap) && DA2xIt_deref(dipt);
  }

//--------------------------------------------------------------------------------
// useful functions for quantifiers
//

  // each element is a pointer to dynamic memory, and that memory is to be freed:
  static inline void Da_f_free(void *item_pt ,void *closure){
    free(item_pt);
  }

  // elements are integers
  static inline void Da_f_print_int(void *element_pt, char *sep){
    fprintf(stderr ,"%s%d" ,sep ,*(int *)element_pt);
  }

  // elements are char *
  static inline void Da_f_print_string(void *element_pt, char *sep){
    fprintf(stderr ,"%s%d" ,sep ,(char *)element_pt);
  }



#endif
