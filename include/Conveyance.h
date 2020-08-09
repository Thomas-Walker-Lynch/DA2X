#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

#define continue_from goto
typedef void **ConveyancePtr; 
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

// Declare local pad pointers
#define AR(x ,i) register struct x##i *ar = (struct x##i *)&Conveyance·Args_pt->x;
#define LC(x ,i) register struct x##i *lc = (struct x##i *)&Conveyance·Locals_pt->x;
#define CX(x ,i) register struct x##i *cx = (struct x##i *)&Conveyance·Context.x;

#endif
