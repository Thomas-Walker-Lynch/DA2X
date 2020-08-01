#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>

  // continuations by trampoline
  #define continuations __label__
  #define continue_into goto *
  #define continue_via_trampoline return
  #define continue_from goto
  typedef void **conveyance;
  #define cend abort();

#endif
