#ifndef T1_H
#define T1_H

#include <stdbool.h>
#include "misc.h"
#include "T02x·Tape

//--------------------------------------------------------------------------------
// The T02x·Tape dynamic array header struct
//   .. does the mutex lock variable belongs here, or at L2? Perhaps here,
//   because look at all the trouble we have already gone through to make
//   this thread safe.
  typedef struct {
    bool empty;
    T02x·Tape t0;
  } T1·Tape ;


#endif

