/*
A generic interface for a T0 level tape implementation iterator.

Both read and write check for fit first, before moving any data.

*/

#ifndef T0Hd_H
#define T0Hd_H
#include "Sequence.h"
#include "Inclusive.h"
#include "T0.h"

typedef struct {
  SQ·Ptr remaining;
  SQ·Ptr leftmost;
  SQ·Ptr rightmost;
  SQ·Ptr cue;
  SQ·Ptr step_left;
  SQ·Ptr step_right;
  SQ·Ptr read_to_pt;
  SQ·Ptr write_from_pt;
  SQ·Ptr copy;
} T0Hd·Iface;

typedef struct{
  T0·Root *tape;
} T0Hd·InitHd·Args;
typedef struct{
  T0Hd·Root *hd;
} T0Hd·InitHd·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·InitHd·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·InitHd·Args *args;
  T0Hd·InitHd·Ress *ress;
  T0Hd·InitHd·Lnks *lnks;
} T0Hd·InitHd·Lnk;


typedef struct{
  T0Hd·Root *hd;
} T0Hd·Remaining·Args;
typedef struct{
  address_t *r;
} T0Hd·Remaining·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·Remaining·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Remaining·Args *args;
  T0Hd·Remaining·Ress *ress;
  T0Hd·Remaining·Lnks *lnks;
} T0Hd·Remaining·Lnk;


typedef struct{
  T0Hd·Root *hd;
} T0Hd·Leftmost·Args;
typedef struct{
} T0Hd·Leftmost·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·Leftmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Leftmost·Args *args;
  T0Hd·Leftmost·Ress *ress;
  T0Hd·Leftmost·Lnks *lnks;
} T0Hd·Leftmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
  T0Hd·Root *element_n;
} T0Hd·Rightmost·Args;
typedef struct{
} T0Hd·Rightmost·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk left_of_leftmost;
} T0Hd·Rightmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Rightmost·Args *args;
  T0Hd·Rightmost·Ress *ress;
  T0Hd·Rightmost·Lnks *lnks;
} T0Hd·Rightmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
  address_t *i;
} T0Hd·Cue·Args;
typedef struct{
} T0Hd·Cue·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk right_of_rightmost;
} T0Hd·Cue·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Cue·Args *args;
  T0Hd·Cue·Ress *ress;
  T0Hd·Cue·Lnks *lnks;
} T0Hd·Cue·Lnk;

typedef struct{
  T0Hd·Root *hd;
  address_t *d;
} T0Hd·StepLeft·Args;
typedef struct{
} T0Hd·StepLeft·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk right_of_rightmost;
} T0Hd·StepLeft·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·StepLeft·Args *args;
  T0Hd·StepLeft·Ress *ress;
  T0Hd·StepLeft·Lnks *lnks;
} T0Hd·StepLeft·Lnk;

typedef struct{
  T0Hd·Root *hd;
  address_t *d;
} T0Hd·StepRight·Args;
typedef struct{
} T0Hd·StepRight·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk right_of_rightmost;
} T0Hd·StepRight·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·StepRight·Args *args;
  T0Hd·StepRight·Ress *ress;
  T0Hd·StepRight·Lnks *lnks;
} T0Hd·StepRight·Lnk;


typedef struct{
  T0Hd·Root *hd;
  char *pt;
  address_t *n;
} T0Hd·ReadToPt·Args;
typedef struct{
} T0Hd·ReadToPt·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk underflow;
} T0Hd·ReadToPt·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·ReadToPt·Args *args;
  T0Hd·ReadToPt·Ress *ress;
  T0Hd·ReadToPt·Lnks *lnks;
} T0Hd·ReadToPt·Lnk;


typedef struct{
  T0Hd·Root *hd;
  char *pt;
  address_t *n;
} T0Hd·WriteFromPt·Args;
typedef struct{
} T0Hd·WriteFromPt·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk overflow;
} T0Hd·WriteFromPt·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·WriteFromPt·Args *args;
  T0Hd·WriteFromPt·Ress *ress;
  T0Hd·WriteFromPt·Lnks *lnks;
} T0Hd·WriteFromPt·Lnk;

typedef struct{
  T0Hd·Root *src;
  T0Hd·Root *dst;
  address_t *n;
} T0Hd·Copy·Args;
typedef struct{
} T0Hd·Copy·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk misfit;
} T0Hd·Copy·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Copy·Args *args;
  T0Hd·Copy·Ress *ress;
  T0Hd·Copy·Lnks *lnks;
} T0Hd·Copy·Lnk;

typedef struct{
  bool *underflow;
  bool *overflow;
} T0Hd·Misfit·Args;
typedef struct{
} T0Hd·Misfit·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·Misfit·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Misfit·Args *args;
  T0Hd·Misfit·Ress *ress;
  T0Hd·Misfit·Lnks *lnks;
} T0Hd·pMisfit·Lnk;

