#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

#define continue_from goto
typedef void **Conveyance; // The Conveyance type

// unlike for the rest of C, the Conveyance type can not be used to declare
// Conveyances, instead we start with 'Conveyances' 
#define Conveyances __label__

// It is good form for a conveyance definition to end with this.
// Later it might be related with destructors.
#define cend abort();

// These are no longer used in the library, but a program might use them.
// Conveyances by trampoline.
//
  // this is placed just before the function name in the call, the function
  #define continue_into goto *
  // this is used inside of the function in place of continue_from
  #define continue_via_trampoline return


#endif
