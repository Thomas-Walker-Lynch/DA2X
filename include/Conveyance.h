#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>

  #define continue_from goto

  // unlike for the rest of C, the Conveyance type can not be used to declare
  // Conveyances, instead there is a separate DECL form.
  #define ConveyanceDECL __label__
  typedef void **Conveyance; // The Conveyance type

  // It is good form for a conveyance definition to end with this.
  // Later it might be related with destructors.
  #define cend abort();

  // These are no longer used in the library, but a program might use them.
  // continuations by trampoline
  #define continue_into goto *
  #define continue_via_trampoline return

#endif
