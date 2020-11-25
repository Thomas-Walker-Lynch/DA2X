#ifndef T02xHD_H
#define T02xHD_H
#include "misc.h"
#include "Inclusive.h"
#include "Sequence.h"
#include "T02x.h"

typedef struct{
  T02x·Root *tape;
  address_t i;  // byte index
  address_t element_n; // extent of an element
} T02xHdI·Root;



#endif

