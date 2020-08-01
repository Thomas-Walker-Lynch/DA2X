#ifndef CLIB_TEXT_H
#define CLIB_TEXT_H
#include <stdlib.h>
#include "Inclusive.h"
#include "Conveyance.h"

/* 
  Implementations use non-inclusive bounding artihmetic to accomodate the C library, 
  but this is not carried through to the interface.
*/
#pragma push_macro("S1")
#undef S1
#define S1 Args.CLib·mallocn
CLib·mallocn:{
  if( S1.n == address_t_n ) continue_from fail; 
  *S1.pt = malloc(S1.n + 1);
  if(!*S1.pt) continue_from *S1.fail;
  continue_from *S1.nominal;
  cend;
}
#pragma pop("S1")


#endif
