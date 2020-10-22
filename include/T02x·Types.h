

typedef struct{
} T02x·AllocTapeHeap·Args;
typedef struct{
  T02x·Tape **tape;
} T02x·AllocTapeHeap·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail;
} T02x·AllocTapeHeap·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·AllocTapeHeap·Args *args;
  T02x·AllocTapeHeap·Ress *ress;
  T02x·AllocTapeHeap·Lnks *lnks;
} T02x·AllocTapeHeap·Lnk;

typedef struct{
  T02x·Tape *tape;
  address_t *n;   // extent of the array, in bytes
} T02x·AllocArray·Args;
typedef struct{
} T02x·AllocArray·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T02x·AllocArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·AllocArray·Args *args;
  T02x·AllocArray·Ress *ress;
  T02x·AllocArray·Lnks *lnks;
} T02x·AllocArray·Lnk;

typedef struct{
  T02x·Tape *tape;
  address_t *n_Element;  // extent of the array, in elements
  address_t *element_n_Byte; // extent of the element, in bytes
} T02x·AllocArrayElements·Args;
typedef struct{
} T02x·AllocArrayElements·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
  SQ·Lnk fail_alloc;
} T02x·AllocArrayElements·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·AllocArrayElements·Args *args;
  T02x·AllocArrayElements·Ress *ress;
  T02x·AllocArrayElements·Lnks *lnks;
} T02x·AllocArrayElements·Lnk;

typedef struct{
  T02x·Tape *tape;
} T02x·DeallocArray·Args;
typedef struct{
} T02x·DeallocArray·Ress;
typedef struct{
  SQ·Lnk nominal;
} T02x·DeallocArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·DeallocArray·Args *args;
  T02x·DeallocArray·Ress *ress;
  T02x·DeallocArray·Lnks *lnks;
} T02x·DeallocArray·Lnk;

typedef struct{
  T02x·Tape *tape;
} T02x·DeallocTapeHeap·Args;
typedef struct{
} T02x·DeallocTapeHeap·Ress;
typedef struct{
  SQ·Lnk nominal;
} T02x·DeallocTapeHeap·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·DeallocTapeHeap·Args *args;
  T02x·DeallocTapeHeap·Ress *ress;
  T02x·DeallocTapeHeap·Lnks *lnks;
} T02x·DeallocTapeHeap·Lnk;

typedef struct{
  T02x·Tape *src;
  T02x·Tape *dst;
} T02x·MoveArray·Args;
typedef struct{
} T02x·MoveArray·Ress;
typedef struct{
  SQ·Lnk nominal;
} T02x·MoveArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·MoveArray·Args *args;
  T02x·MoveArray·Ress *ress;
  T02x·MoveArray·Lnks *lnks;
} T02x·MoveArray·Lnk;

typedef struct{
  T02x·Tape *tape;
  address_t *n;
} T02x·Lengthen·Args;
typedef struct{
  char **new_area_pt;
} T02x·Lengthen·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T02x·Lengthen·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·Lengthen·Args *args;
  T02x·Lengthen·Ress *ress;
  T02x·Lengthen·Lnks *lnks;
} T02x·Lengthen·Lnk;

typedef struct{
  T02x·Tape *tape;
  address_t *n;
} T02x·Shorten·Args;
typedef struct{
} T02x·Shorten·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk empty;
  SQ·Lnk fail_left_leftmost;
  SQ·Lnk fail_alloc;
} T02x·Shorten·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T02x·Shorten·Args *args;
  T02x·Shorten·Ress *ress;
  T02x·Shorten·Lnks *lnks;
} T02x·Shorten·Lnk;
 
