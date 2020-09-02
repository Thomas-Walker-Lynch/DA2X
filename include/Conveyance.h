#ifndef CONVEYANCE_H
#define CONVEYANCE_H
#include <stdlib.h>
#include "misc.h"

typedef void **CV·Ptr; 
#define CV·Conveyance __label__
#define CV·convey(c) goto c;
#define CV·def(c) goto CV·##c;c:{
#define CV·end(c) abort();} CV·##c:;

// connections
typedef struct {
} CV·Cnxs;

// arguments
typedef struct {
} CV·Args;

typedef struct{
  CV·Ptr conveyance;
  CV·Args *args;
  CV·Cnxs *cnxs;
} CV·GeneralConveyance·Ptr;

#define CV·init_cnx(ns ,conveyance_name)           \
  {                                             \
    .conveyance = &&ns##·##convyeance_name      \
      ,.args = &CA.##conveyance_name            \
      ,.cnxs = &CC.##conveyance_name            \
      }

#define CV·general_convey(gcptr)                \
  ({                                            \
    CV·args = (CV·Args *)gcptr.args;            \
    CV·cnxs = (CV·Cnxs *)gcptr.cnxs;            \
    CV·convey(gcptr->conveyance);               \
  })

#endif
