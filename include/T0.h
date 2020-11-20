/*
A generic interface for a T0 level tape implementation.

*/


#ifndef T0_H
#define T0_H
#include "Sequence.h"
#include "Inclusive.h"

typedef struct {
  SQ·Ptr construct;
  SQ·Ptr destruct;
  SQ·Ptr move_array;
  SQ·Ptr lengthen;
  SQ·Ptr shorten;
} T0·Iface;

typedef struct{
} T0·Root;


typedef struct{
  T0·Root *tape;
  address_t *n;
} T0·Construct·Args;
typedef struct{
} T0·Construct·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T0·Construct·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Construct·Args *args;
  T0·Construct·Ress *ress;
  T0·Construct·Lnks *lnks;
} T0·Construct·Lnk;


typedef struct{
  T0·Root *tape;
} T0·Destruct·Args;
typedef struct{
} T0·Destruct·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·Destruct·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Destruct·Args *args;
  T0·Destruct·Ress *ress;
  T0·Destruct·Lnks *lnks;
} T0·Destruct·Lnk;


typedef struct{
  T0·Root *src;
  T0·Root *dst;
} T0·MoveArray·Args;
typedef struct{
} T0·MoveArray·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·MoveArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·MoveArray·Args *args;
  T0·MoveArray·Ress *ress;
  T0·MoveArray·Lnks *lnks;
} T0·MoveArray·Lnk;

typedef struct{
  T0·Root *tape;
  address_t *n;
} T0·Lengthen·Args;
typedef struct{
  char **new_area_pt;
} T0·Lengthen·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T0·Lengthen·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Lengthen·Args *args;
  T0·Lengthen·Ress *ress;
  T0·Lengthen·Lnks *lnks;
} T0·Lengthen·Lnk;


typedef struct{
  T0·Root *tape;
  address_t *n;
} T0·Shorten·Args;
typedef struct{
} T0·Shorten·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_empty;
  SQ·Lnk fail_underflow;
  SQ·Lnk fail_alloc;
} T0·Shorten·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Shorten·Args *args;
  T0·Shorten·Ress *ress;
  T0·Shorten·Lnks *lnks;
} T0·Shorten·Lnk;


#endif
