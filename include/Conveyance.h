#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

typedef void **CV·Ptr; 
#define CV·Conveyance __label__
#define CV·convey(c) goto c;
#define CV·def(c) goto CV·##c;c:{
#define CV·end(c) abort();} CV·##c:;

// arguments
typedef struct {
} CV·Args;

// connections
typedef struct {
} CV·Lnks;

typedef struct{
  CV·Ptr conveyance;
  CV·Args *args;
  CV·Lnks *lnks;
} CV·Lnk;

#define CV·init_lnk(ns ,conveyance_name)           \
  {                                             \
    .conveyance = &&ns##·##convyeance_name      \
      ,.args = &CA.##conveyance_name            \
      ,.lnks = &CC.##conveyance_name            \
      }

#define CV·convey_indirect(lnk) \
  CV·lnk  = &(lnk);                             \
  CV·convey(*CV·lnk->conveyance);


#endif
