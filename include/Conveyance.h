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

// May call more than once to get multiple variables with different interpretations of the same args.
// Declare local pad pointers
// v - variable name for the namespace
// s - context name 
// x - conveyance name
// i - interpreteation, mainly used with local pads
#define AR(v ,x ,i) register struct x##i *v = (struct x##i *)&Conveyance·Args_pt->x;
#define LC(v ,x ,i) register struct x##i *v = (struct x##i *)&Conveyance·Locals_pt->x;
#define CX(v ,s ,x) register struct CX·##s##·##x *v = &CX·##s.x;


#endif
