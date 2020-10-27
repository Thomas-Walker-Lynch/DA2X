/*
A generic interface for a T0 level tape implementation iterator.

both read and write check for fit first, before moving any data.

*/

#ifndef T0Hd_H
#define T0Hd_H
#include "Sequence.h"
#include "Inclusive.h"
#include "T0.h"

typedef struct {
  SQ·Ptr leftmost;
  SQ·Ptr rightmost;
  SQ·Ptr step_left;
  SQ·Ptr step_right;
  SQ·Ptr read_to_pt;
  SQ·Ptr write_from_pt;
  SQ·Ptr copy;
} T0Hd·Iface;


typedef struct{
  T0Hd·Root *hd;
} T0·CueLeftmost·Args;
typedef struct{
} T0·CueLeftmost·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·CueLeftmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·CueLeftmost·Args *args;
  T0·CueLeftmost·Ress *ress;
  T0·CueLeftmost·Lnks *lnks;
} T0·CueLeftmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
} T0·CueRightmost·Args;
typedef struct{
} T0·CueRightmost·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·CueRightmost·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·CueRightmost·Args *args;
  T0·CueRightmost·Ress *ress;
  T0·CueRightmost·Lnks *lnks;
} T0·CueRightmost·Lnk;


typedef struct{
  T0Hd·Root *hd;
  char *pt;
  address_t n;
} T0·ReadToPt·Args;
typedef struct{
} T0·ReadToPt·Ress;
typedef struct{
  SQ·Lnk nominal;
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
  address_t n;
} T0·WriteFromPt·Args;
typedef struct{
} T0·WriteFromPt·Ress;
typedef struct{
  SQ·Lnk nominal;
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
  address_t n;
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
