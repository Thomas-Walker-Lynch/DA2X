#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

#define continue_from goto
typedef void **ConveyancePtr; // The ConveyancePtr type

// unlike for the rest of C, the ConveyancePtr type can not be used to declare
// Conveyance, instead we start with 'Conveyance' 
#define Conveyance __label__

// It is good form for a conveyance definition to end with this.
// Later it might be related with destructors.
#define cend abort();

// These are no longer used in the library, but a program might use them.
// Conveyance by trampoline.
//
  // this is placed just before the function name in the call, the function
  #define continue_into goto *
  // this is used inside of the function in place of continue_from
  #define continue_via_trampoline return


#endif
