#include <stdlib.h>
#include "Inclusive.h"
#include "Sequence.h"

#if TEST
  address_t Test·CLib·allocation_n = 0;
#endif

/* 
  This implementation uses non-inclusive bounding artihmetic to accomodate the C library, 
  but this is not reflected to the interface..
*/
  SQ·def(CLib·mallocn){
    CLib·Mallocn·Lnk *lnk = (CLib·Mallocn·Lnk *)SQ·lnk;
    address_t n = *lnk->args->n;
    #if TEST
      Test·CLib·allocation_n = n;
    #endif
    if( n == address_t_n ){
      SQ·continue_indirect(lnk->lnks->fail);
    }
    void *alloc = malloc(n + 1);
    if(!alloc){
      SQ·continue_indirect(lnk->lnks->fail);
    }
    *lnk->ress->allocation = alloc;
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(CLib·mallocn);
