/*
A generic interface for a T0 level tape implementation.

*/


#ifndef T0_H
#define T0_H
#include "Sequence.h"
#include "Inclusive.h"

typedef struct {
  SQ·Ptr alloc_Tape_heap; // a convenience function
  SQ·Ptr alloc_array;
  SQ·Ptr alloc_array_elements;
  SQ·Ptr dealloc_array;
  SQ·Ptr dealloc_Tape_heap;
  SQ·Ptr move_array;
  SQ·Ptr lengthen;
  SQ·Ptr shorten;
  SQ·Ptr make_hd;
} T0·Iface;

typedef struct{
} T0·Root;

typedef struct{
} T0Hd·Root;


typedef struct{
} T0·AllocTapeHeap·Args;
typedef struct{
  T0·Root **tape;
} T0·AllocTapeHeap·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail;
} T0·AllocTapeHeap·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·AllocTapeHeap·Args *args;
  T0·AllocTapeHeap·Ress *ress;
  T0·AllocTapeHeap·Lnks *lnks;
} T0·AllocTapeHeap·Lnk;

typedef struct{
  T0·Root *tape;
  address_t *n;   // extent of the array, in bytes
} T0·AllocArray·Args;
typedef struct{
} T0·AllocArray·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T0·AllocArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·AllocArray·Args *args;
  T0·AllocArray·Ress *ress;
  T0·AllocArray·Lnks *lnks;
} T0·AllocArray·Lnk;

typedef struct{
  T0·Root *tape;
  address_t *n_Element;  // extent of the array, in elements
  address_t *element_n_Byte; // extent of the element, in bytes
} T0·AllocArrayElements·Args;
typedef struct{
} T0·AllocArrayElements·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
  SQ·Lnk fail_alloc;
} T0·AllocArrayElements·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·AllocArrayElements·Args *args;
  T0·AllocArrayElements·Ress *ress;
  T0·AllocArrayElements·Lnks *lnks;
} T0·AllocArrayElements·Lnk;

typedef struct{
  T0·Root *tape;
} T0·DeallocArray·Args;
typedef struct{
} T0·DeallocArray·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·DeallocArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·DeallocArray·Args *args;
  T0·DeallocArray·Ress *ress;
  T0·DeallocArray·Lnks *lnks;
} T0·DeallocArray·Lnk;

typedef struct{
  T0·Root *tape;
} T0·DeallocTapeHeap·Args;
typedef struct{
} T0·DeallocTapeHeap·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·DeallocTapeHeap·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·DeallocTapeHeap·Args *args;
  T0·DeallocTapeHeap·Ress *ress;
  T0·DeallocTapeHeap·Lnks *lnks;
} T0·DeallocTapeHeap·Lnk;

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
  SQ·Lnk empty;
  SQ·Lnk fail_left_leftmost;
  SQ·Lnk fail_alloc;
} T0·Shorten·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·Shorten·Args *args;
  T0·Shorten·Ress *ress;
  T0·Shorten·Lnks *lnks;
} T0·Shorten·Lnk;


typedef struct{
  T0·Root *tape;
} T0·MakeHd·Args;
typedef struct{
  T0Hd·Root *hd;
} T0·MakeHd·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·MakeHd·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·MakeHd·Args *args;
  T0·MakeHd·Ress *ress;
  T0·MakeHd·Lnks *lnks;
} T0·MakeHd·Lnk;
 
#endif
