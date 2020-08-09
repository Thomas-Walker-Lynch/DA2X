#include <stdlib.h>
#include "Inclusive.h"
#include "Conveyance.h"

/* Tested, works, but I will add an interface to L2
struct Text·CLib{
  ConveyancePtr mallocn;
} Text·CLib
={
  &&CLib·mallocn
};
*/

#if TEST
  address_t Test·CLib·allocation_n = 0;
#endif


goto CLib·end;

/* 
  Implementations use non-inclusive bounding artihmetic to accomodate the C library, 
  but this is not carried through to the interface.
*/
CLib·mallocn:{
  Conveyance·swap();
  LC(CLib·mallocn ,0);

#if TEST
  Test·CLib·allocation_n = lc->n;
#endif

  if( lc->n == address_t_n ) continue_from *lc->fail; 
  *lc->pt = malloc(lc->n + 1);
  if(!*lc->pt) continue_from *lc->fail;
  continue_from *lc->nominal;
  cend;
}

CLib·end:;

