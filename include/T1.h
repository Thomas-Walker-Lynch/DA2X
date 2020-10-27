/*
Provides a concrete T1 interface for a given T0 interface.

*/
#ifndef T1_H
#define T1_H

#include <stdbool.h>
#include "misc.h"
#include "T0.h"

typedef struct {
  SQ·Ptr construct;
  SQ·Ptr destruct;
  SQ·Ptr move;
  SQ·Ptr lengthen;
  SQ·Ptr shorten;
} T1·Iface;

typedef struct {
  bool empty;
  T0 *t0;
  T0·Root *tape0;
} T1·Tape;


typedef struct{
  T1·Tape *tape;
  T0 *t0; // tape 0 interface to use
} T1·Construct·Args;
typedef struct{
} T1·Construct·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T1·Construct·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T1·Construct·Args *args;
  T1·Construct·Ress *ress;
  T1·Construct·Lnks *lnks;
} T1·Construct·Lnk;


typedef struct{
  T1·Tape *tape;
} T1·Destruct·Args;
typedef struct{
} T1·Destruct·Ress;
typedef struct{
  SQ·Lnk nominal;
} T1·Destruct·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T1·Destruct·Args *args;
  T1·Destruct·Ress *ress;
  T1·Destruct·Lnks *lnks;
} T1·Destruct·Lnk;


typedef struct{
  T1·Tape *src;
  T1·Tape *dst;
} T1·Move·Args;
typedef struct{
} T1·Move·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T1·Move·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T1·Move·Args *args;
  T1·Move·Ress *ress;
  T1·Move·Lnks *lnks;
} T1·Move·Lnk;


typedef struct{
  T1·Tape *tape;
} T1·Lengthen·Args;
typedef struct{
  char **new_area;
} T1·Lengthen·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T1·Lengthen·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T1·Lengthen·Args *args;
  T1·Lengthen·Ress *ress;
  T1·Lengthen·Lnks *lnks;
} T1·Lengthen·Lnk;


#endif

