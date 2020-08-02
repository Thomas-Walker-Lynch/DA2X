#include <stdlib.h>
#include "Inclusive.h"
#include "Conveyance.h"

/* Tested, works, but I will add an interface to L2
struct Text·CLib{
  Conveyance mallocn;
} Text·CLib
={
  &&CLib·mallocn
};
*/

goto CLib·end;

/* 
  Implementations use non-inclusive bounding artihmetic to accomodate the C library, 
  but this is not carried through to the interface.
*/
#pragma push_macro("S1")
#undef S1
#define S1 Args.CLib·mallocn
CLib·mallocn:{
  if( S1.n == address_t_n ) continue_from *S1.fail; 
  *S1.pt = malloc(S1.n + 1);
  if(!*S1.pt) continue_from *S1.fail;
  continue_from *S1.nominal;
  cend;
}
#pragma pop_macro("S1")

CLib·end:;

