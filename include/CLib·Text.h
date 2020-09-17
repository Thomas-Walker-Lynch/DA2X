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
    register address_t n = *lnk->args->n;
    register void * = allocation;
    #if TEST
      Test·CLib·allocation_n = n;
    #endif
    if( n == address_t_n ){
      SQ·continue_indirect(lnk->lnks->fail);
    }
    allocation = malloc(n + 1);
    if(allocation){
      SQ·continue_indirect(lnk->lnks->fail);
    }
    *lnk_ress->allocation = allocation;
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(CLib·mallocn);
