#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

typedef void **ConveyancePtr; 
#define Conveyance __label__
#define convey goto
#define cdef(c) abort();c:
#define cend abort();

#define encapsulation(name) ConveyancePtr name
#define eend abort();
#define leave_to return

// May call more than once to get multiple variables with different interpretations of the same args.
// Declare local pad pointers
// v - variable naoome for the namespace
// s - context name 
// x - conveyance name
// i - interpreteation, mainly used with local pads
#define AR(v ,x ,i) struct x##i *v = (struct x##i *)&Conveyance·Args_pt->x;
#define LC(v ,x ,i) struct x##i *v = (struct x##i *)&Conveyance·Locals_pt->x;
#define CX(v ,s ,x) struct CX·##s##·##x *v = &CX·##s.x;


#endif
