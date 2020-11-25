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
  SQ·Ptr bind;
  SQ·Ptr rhs_n;
  SQ·Ptr lhs_n;
  SQ·Ptr cue_leftmost;
  SQ·Ptr cue_rightmost;
  SQ·Ptr cue_i;
  SQ·Ptr cue_pt;
  SQ·Ptr step_left;
  SQ·Ptr step_right;
  SQ·Ptr read_to_pt;
  SQ·Ptr write_from_pt;
  SQ·Ptr copy;
} T0Hd·Iface;

typedef struct{
} T0Hd·Root;

typedef struct{
  T0·Root *tape;
  T0Hd·Root *hd;
} T0Hd·Bind·Args;
typedef struct{
} T0Hd·Bind·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·Bind·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Bind·Args *args;
  T0Hd·Bind·Ress *ress;
  T0Hd·Bind·Lnks *lnks;
} T0Hd·Bind·Lnk;


typedef struct{
  T0Hd·Root *hd;
} T0Hd·Rhs_N·Args;
typedef struct{
  address_t *n;
} T0Hd·Rhs_N·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·Rhs_N·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Rhs_N·Args *args;
  T0Hd·Rhs_N·Ress *ress;
  T0Hd·Rhs_N·Lnks *lnks;
} T0Hd·Rhs_N·Lnk;


typedef struct{
  T0Hd·Root *hd;
} T0Hd·Lhs_N·Args;
typedef struct{
  address_t *n;
} T0Hd·Lhs_N·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·Lhs_N·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·Lhs_N·Args *args;
  T0Hd·Lhs_N·Ress *ress;
  T0Hd·Lhs_N·Lnks *lnks;
} T0Hd·Lhs_N·Lnk;


typedef struct{
  T0Hd·Root *hd;
} T0Hd·CueLeftmost·Args;
typedef struct{
} T0Hd·CueLeftmost·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0Hd·CueLeftmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·CueLeftmost·Args *args;
  T0Hd·CueLeftmost·Ress *ress;
  T0Hd·CueLeftmost·Lnks *lnks;
} T0Hd·CueLeftmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
  T0Hd·Root *element_n; // extent of an element
} T0Hd·CueRightmost·Args;
typedef struct{
} T0Hd·CueRightmost·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk left_of_leftmost;
} T0Hd·CueRightmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·CueRightmost·Args *args;
  T0Hd·CueRightmost·Ress *ress;
  T0Hd·CueRightmost·Lnks *lnks;
} T0Hd·CueRightmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
  address_t *i;
} T0Hd·CueI·Args;
typedef struct{
} T0Hd·CueI·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk right_of_rightmost;
} T0Hd·CueI·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·CueI·Args *args;
  T0Hd·CueI·Ress *ress;
  T0Hd·CueI·Lnks *lnks;
} T0Hd·CueI·Lnk;


typedef struct{
  T0Hd·Root *hd;
  char **pt;
} T0Hd·CuePt·Args;
typedef struct{
} T0Hd·CuePt·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk left_of_leftmost;
  SQ·Lnk right_of_rightmost;
} T0Hd·CuePt·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0Hd·CuePt·Args *args;
  T0Hd·CuePt·Ress *ress;
  T0Hd·CuePt·Lnks *lnks;
} T0Hd·CuePt·Lnk;


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

