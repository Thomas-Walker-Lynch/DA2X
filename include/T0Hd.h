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
  T0Hd·Root *hd;
} T0·Remaining·Args;
typedef struct{
  address_t *r;
} T0·Remaining·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·Remaining·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Remaining·Args *args;
  T0·Remaining·Ress *ress;
  T0·Remaining·Lnks *lnks;
} T0·Remaining·Lnk;


typedef struct{
  T0Hd·Root *hd;
} T0·Leftmost·Args;
typedef struct{
} T0·Leftmost·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·Leftmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Leftmost·Args *args;
  T0·Leftmost·Ress *ress;
  T0·Leftmost·Lnks *lnks;
} T0·Leftmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
  T0Hd·Root *element_n;
} T0·Rightmost·Args;
typedef struct{
} T0·Rightmost·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk left_of_leftmost;
} T0·Rightmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Rightmost·Args *args;
  T0·Rightmost·Ress *ress;
  T0·Rightmost·Lnks *lnks;
} T0·Rightmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
  address_t *i;
} T0·Cue·Args;
typedef struct{
} T0·Cue·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk right_of_rightmost;
} T0·Cue·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Cue·Args *args;
  T0·Cue·Ress *ress;
  T0·Cue·Lnks *lnks;
} T0·Cue·Lnk;

typedef struct{
  T0Hd·Root *hd;
  address_t *d;
} T0·StepLeft·Args;
typedef struct{
} T0·StepLeft·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk right_of_rightmost;
} T0·StepLeft·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·StepLeft·Args *args;
  T0·StepLeft·Ress *ress;
  T0·StepLeft·Lnks *lnks;
} T0·StepLeft·Lnk;

typedef struct{
  T0Hd·Root *hd;
  address_t *d;
} T0·StepRight·Args;
typedef struct{
} T0·StepRight·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk right_of_rightmost;
} T0·StepRight·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·StepRight·Args *args;
  T0·StepRight·Ress *ress;
  T0·StepRight·Lnks *lnks;
} T0·StepRight·Lnk;


typedef struct{
  T0Hd·Root *hd;
  char *pt;
  address_t *n;
} T0·ReadToPt·Args;
typedef struct{
} T0·ReadToPt·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk underflow;
} T0·ReadToPt·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·ReadToPt·Args *args;
  T0·ReadToPt·Ress *ress;
  T0·ReadToPt·Lnks *lnks;
} T0·ReadToPt·Lnk;


typedef struct{
  T0Hd·Root *hd;
  char *pt;
  address_t *n;
} T0·WriteFromPt·Args;
typedef struct{
} T0·WriteFromPt·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk overflow;
} T0·WriteFromPt·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·WriteFromPt·Args *args;
  T0·WriteFromPt·Ress *ress;
  T0·WriteFromPt·Lnks *lnks;
} T0·WriteFromPt·Lnk;


typedef struct{
  T0Hd·Root *src;
  T0Hd·Root *dst;
  address_t *n;
} T0·Copy·Args;
typedef struct{
} T0·Copy·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·Copy·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Copy·Args *args;
  T0·Copy·Ress *ress;
  T0·Copy·Lnks *lnks;
} T0·Copy·Lnk;

