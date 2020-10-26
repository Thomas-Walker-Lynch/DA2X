#ifndef CLIB_H
#define CLIB_H

#include "misc.h"
#include "Inclusive.h"

// struct CLib·mallocn *ar = &Sequence·Args_pt->CLib·mallocn;
typedef struct {
  address_t *n;
} CLib·Mallocn·Args;

typedef struct {
  void **allocation;
} CLib·Mallocn·Ress;

typedef struct {
  SQ·Lnk nominal;
  SQ·Lnk fail;
} CLib·Mallocn·Lnks;

typedef struct{
  SQ·Ptr sequence;
  CLib·Mallocn·Args *args;
  CLib·Mallocn·Ress *ress;
  CLib·Mallocn·Lnks *lnks;
} CLib·Mallocn·Lnk;

#endif
