#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

typedef void **CV·Ptr; 
#define CV·Conveyance __label__
#define CV·convey(c) goto c;
#define CV·def(c) goto CV·##c;c:{
#define CV·end(c) abort();} CV·##c:;

// actual argument data
typedef struct {
} CV·Args;

// pointers to places to put result data
typedef struct {
} CV·Ress;

// connections
typedef struct {
} CV·Lnks;

// a link to a conveyance for indirect calls
typedef struct{
  CV·Ptr conveyance;
  CV·Args *args;
  CV·Ress *ress;
  CV·Lnks *lnks;
} CV·Lnk;

#define CV·init_lnk(ns ,conveyance_name)           \
  {                                             \
    .conveyance = &&ns##·##convyeance_name      \
      ,.args = &CA.##conveyance_name            \
      ,.lnks = &CC.##conveyance_name            \
      }

#define CV·convey_indirect(lnk) \
  CV·lnk  = (CV·Lnk *)&(lnk);                \
  CV·convey(*CV·lnk->conveyance);


#endif
