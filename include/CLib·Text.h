#include <stdlib.h>
#include "Inclusive.h"
#include "Sequence.h"

#if TEST
  address_t Test·CLib·allocation_n = 0;
#endif

/* 
  Implementations use non-inclusive bounding artihmetic to accomodate the C library, 
  but this is not carried past the interface.
*/
  SQ·def(CLib·mallocn){
    CLib·Mallocn·Lnk *lnk = (CLib·Mallocn·Lnk *)SQ·lnk;
    #if TEST
      Test·CLib·allocation_n = lnk->args->n;
    #endif
    if( lnk->args->n == address_t_n ){
      SQ·continue_indirect(lnk->lnks->fail);
    }
    *lnk->ress->allocated_data = malloc(lnk->args->n + 1);
    if(!*lnk->ress->allocated_data){
      SQ·continue_indirect(lnk->lnks->fail);
    }
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(CLib·mallocn);
