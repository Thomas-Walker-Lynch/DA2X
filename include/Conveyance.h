#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

typedef void **CV·Ptr; 
#define CV·Conveyance __label__
#define CV·convey goto
#define CV·def(c) abort();c:
#define CV·end abort();


// deprecated stuff, some of it from Conveyance·Text
#if 0

#define encapsulation(name) CV·Ptr name
#define eend abort();
#define leave_to return


// May call more than once to get multiple variables with different interpretations of the same args.
// Declare local pad pointers
// v - variable name
// s - context name (space)
// x - conveyance name
// i - interpreteation, mainly used with local pads
#define P0(v ,x ,i) struct x##i *v = (struct x##i *)&Conveyance·Args_pt->x;
#define P1(v ,x ,i) struct x##i *v = (struct x##i *)&Conveyance·Locals_pt->x;
#define CX(v ,s ,x) struct CX·##s##·##x *v = &CX·##s.x;

union Conveyance·Data *Conveyance·Args_pt = &Conveyance·Data0;
union Conveyance·Data *Conveyance·Locals_pt = &Conveyance·Data1;

// rather flawed implemenation, uses a function call or creates an auto class variable
// should make this a continuation, add the not so temp variable to the two unions above.
static inline void Conveyance·swap(){
  union Conveyance·Data *t1_locals = Conveyance·Args_pt;
  Conveyance·Args_pt = Conveyance·Locals_pt;
  Conveyance·Locals_pt = t1_locals;
}

#endif


#endif
