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
  #pragma push_macro("ARGS")
  #pragma push_macro("CNXS")
  #define ARGS ((CLib·mallocn·Args *)CV·args)
  #define CNXS ((CLib·mallocn·Cnxs *)CV·cnxs)

    CV·def(CLib·mallocn){
      #if TEST
        Test·CLib·allocation_n = lc->n;
      #endif
      if( ARGS->n == address_t_n ) general_convey(CNXS->fail); 
      *ARGS->pt = malloc(ARGS->n + 1);
      if(!*ARGS->pt) general_convey(CNXS->fail); 
      general_convey(CNXS->nominal);
    } CV·end(Clib·mallocn);

  #pragma pop_macro("ARGS")
  #pragma pop_macro("CNXS")
