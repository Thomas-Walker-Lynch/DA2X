#include <stdlib.h>
#include "Inclusive.h"
#include "Conveyance.h"

#if TEST
  address_t Test·CLib·allocation_n = 0;
#endif

/* 
  Implementations use non-inclusive bounding artihmetic to accomodate the C library, 
  but this is not carried past the interface.
*/
  CV·def(CLib·mallocn){
    CLib·Mallocn·Lnk *lnk = (CLib·Mallocn·Lnk *)CV·lnk;
    #if TEST
      Test·CLib·allocation_n = lnk->args->n;
    #endif
    if( lnk->args->n == address_t_n ) CV·convey_indirect(lnk->lnks->fail); 
    *lnk->args->pt = malloc(lnk->args->n + 1);
    if(!*lnk->args->pt) CV·convey_indirect(lnk->lnks->fail); 
    CV·convey_indirect(lnk->lnks->nominal);
  } CV·end(CLib·mallocn);
