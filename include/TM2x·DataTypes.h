
  typedef struct{
  } TM2x·AllocTapeHeap·Args;
  typedef struct{
    TM2x·Tape **tape;
  } TM2x·AllocTapeHeap·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk fail;
  } TM2x·AllocTapeHeap·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·AllocTapeHeap·Args *args;
    TM2x·AllocTapeHeap·Ress *ress;
    TM2x·AllocTapeHeap·Lnks *lnks;
  } TM2x·AllocTapeHeap·Lnk;


  typedef struct{
    TM2x·Tape *tape;
    address_t *n;   // extent of the array, in bytes
  } TM2x·AllocArray·Args;
  typedef struct{
  } TM2x·AllocArray·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk alloc_fail;
  } TM2x·AllocArray·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·AllocArray·Args *args;
    TM2x·AllocArray·Ress *ress;
    TM2x·AllocArray·Lnks *lnks;
  } TM2x·AllocArray·Lnk;


  typedef struct{
    TM2x·Tape *tape;
    address_t *n_Element;  // extent of the array, in elements
    address_t *element_n_Byte; // extent of the element, in bytes
  } TM2x·AllocArrayElements·Args;
  typedef struct{
  } TM2x·AllocArrayElements·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk index_gt_n;
    SQ·Lnk alloc_fail;
  } TM2x·AllocArrayElements·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·AllocArrayElements·Args *args;
    TM2x·AllocArrayElements·Ress *ress;
    TM2x·AllocArrayElements·Lnks *lnks;
  } TM2x·AllocArrayElements·Lnk;


  typedef struct{
    TM2x·Tape *tape;
  } TM2x·DeallocArray·Args;
  typedef struct{
  } TM2x·DeallocArray·Ress;
  typedef struct{
    SQ·Lnk nominal;
  } TM2x·DeallocArray·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·DeallocArray·Args *args;
    TM2x·DeallocArray·Ress *ress;
    TM2x·DeallocArray·Lnks *lnks;
  } TM2x·DeallocArray·Lnk;


  typedef struct{
    TM2x·Tape *tape;
  } TM2x·DeallocTapeHeap·Args;
  typedef struct{
  } TM2x·DeallocTapeHeap·Ress;
  typedef struct{
    SQ·Lnk nominal;
  } TM2x·DeallocTapeHeap·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·DeallocTapeHeap·Args *args;
    TM2x·DeallocTapeHeap·Ress *ress;
    TM2x·DeallocTapeHeap·Lnks *lnks;
  } TM2x·DeallocTapeHeap·Lnk;


  typedef struct{
         TM2x·Tape *src;
         TM2x·Tape *dst;
  } TM2x·MoveArray·Args;
  typedef struct{
  } TM2x·MoveArray·Ress;
  typedef struct{
    SQ·Lnk nominal;
  } TM2x·MoveArray·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·MoveArray·Args *args;
    TM2x·MoveArray·Ress *ress;
    TM2x·MoveArray·Lnks *lnks;
  } TM2x·MoveArray·Lnk;

  typedef struct{
    TM2x·Tape *tape;
    address_t *n;
  } TM2x·Resize·Args;
  typedef struct{
  } TM2x·Resize·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk alloc_fail;
  } TM2x·Resize·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·Resize·Args *args;
    TM2x·Resize·Ress *ress;
    TM2x·Resize·Lnks *lnks;
  } TM2x·Resize·Lnk;

  typedef struct{
    TM2x·Tape *tape;
    address_t *n;
  } TM2x·Lengthen·Args;
  typedef struct{
    char **new_area_pt;
  } TM2x·Lengthen·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk alloc_fail;
  } TM2x·Lengthen·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·Lengthen·Args *args;
    TM2x·Lengthen·Ress *ress;
    TM2x·Lengthen·Lnks *lnks;
  } TM2x·Lengthen·Lnk;


  typedef struct{
    TM2x·Tape *tape;
    address_t *n;
  } TM2x·Shorten·Args;
  typedef struct{
  } TM2x·Shorten·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk empty;
    SQ·Lnk fail_left_leftmost;
    SQ·Lnk alloc_fail;
  } TM2x·Shorten·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·Shorten·Args *args;
    TM2x·Shorten·Ress *ress;
    TM2x·Shorten·Lnks *lnks;
  } TM2x·Shorten·Lnk;

