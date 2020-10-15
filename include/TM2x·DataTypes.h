
  typedef struct{
  } TM2x·AllocHeaderHeap·Args;
  typedef struct{
    TM2x·Tape**tm2x;
  } TM2x·AllocHeaderHeap·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk fail;
  } TM2x·AllocHeaderHeap·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·AllocHeaderHeap·Args *args;
    TM2x·AllocHeaderHeap·Ress *ress;
    TM2x·AllocHeaderHeap·Lnks *lnks;
  } TM2x·AllocHeaderHeap·Lnk;


  typedef struct{
    TM2x·Tape*tm2x;
    address_t *byte_n;   // extent of the array, in bytes
  } TM2x·AllocArrayBytes·Args;
  typedef struct{
  } TM2x·AllocArrayBytes·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk alloc_fail;
  } TM2x·AllocArrayBytes·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·AllocArrayBytes·Args *args;
    TM2x·AllocArrayBytes·Ress *ress;
    TM2x·AllocArrayBytes·Lnks *lnks;
  } TM2x·AllocArrayBytes·Lnk;


  typedef struct{
    TM2x·Tape*tm2x;
    address_t *element_n;  // extent of the array, in elements
    address_t *element_byte_n; // extent of the element, in bytes
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
    TM2x·Tape*tm2x;
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
    TM2x·Tape*tm2x;
  } TM2x·DeallocHeaderHeap·Args;
  typedef struct{
  } TM2x·DeallocHeaderHeap·Ress;
  typedef struct{
    SQ·Lnk nominal;
  } TM2x·DeallocHeaderHeap·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·DeallocHeaderHeap·Args *args;
    TM2x·DeallocHeaderHeap·Ress *ress;
    TM2x·DeallocHeaderHeap·Lnks *lnks;
  } TM2x·DeallocHeaderHeap·Lnk;


  typedef struct{
         TM2x·Tape*src;
         TM2x·Tape*dst;
  } TM2x·CopyHeader·Args;
  typedef struct{
  } TM2x·CopyHeader·Ress;
  typedef struct{
    SQ·Lnk nominal;
  } TM2x·CopyHeader·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·CopyHeader·Args *args;
    TM2x·CopyHeader·Ress *ress;
    TM2x·CopyHeader·Lnks *lnks;
  } TM2x·CopyHeader·Lnk;



  typedef struct{
         TM2x·Tape*src;
    address_t *src_byte_0;
         TM2x·Tape*dst;
    address_t *dst_byte_0;
    address_t *byte_n;
  } TM2x·CopyContiguousBytes·Args;
  typedef struct{
  } TM2x·CopyContiguousBytes·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk src_index_gt_n;
    SQ·Lnk dst_index_gt_n;
  } TM2x·CopyContiguousBytes·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·CopyContiguousBytes·Args *args;
    TM2x·CopyContiguousBytes·Ress *ress;
    TM2x·CopyContiguousBytes·Lnks *lnks;
  } TM2x·CopyContiguousBytes·Lnk;


  typedef struct{
         TM2x·Tape*src;
    address_t *src_element_0;
         TM2x·Tape*dst;
    address_t *dst_element_0;
    address_t *element_n;
    address_t *element_byte_n;
  } TM2x·CopyContiguousElements·Args;
  typedef struct{
  } TM2x·CopyContiguousElements·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk src_index_gt_n;
    SQ·Lnk dst_index_gt_n;
  } TM2x·CopyContiguousElements·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·CopyContiguousElements·Args *args;
    TM2x·CopyContiguousElements·Ress *ress;
    TM2x·CopyContiguousElements·Lnks *lnks;
  } TM2x·CopyContiguousElements·Lnk;

#if 0

struct TM2x·index·read_0{
  TM2x·Tape*tape;
  address_t index;
  address_t element_n;
  address_t element_byte_n;
  void *dst_element_pt;
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
};

struct TM2x·index·to_pt_0{
  TM2x·Tape*tape ;
  address_t index;
  address_t element_byte_n;
  void **pt;
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
};

struct TM2x·pop_0{
  TM2x·Tape*tape;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk pop_last;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_0{
  TM2x·Tape*tape;
  void *element_base_pt;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_bytes_0{
  TM2x·Tape*tape;
  void *source_pt;
  address_t source_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_elements_0{
  TM2x·Tape*tape ;
  void *base_pt;
  address_t element_n ;
  address_t element_byte_n ;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk index_gt_n;
};

struct TM2x·push_TM2x_0{
  TM2x·Tape*tape ;
  TM2x·Tape*tape_source;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·read_pop_0{
  TM2x·Tape*tape ;
  void *dst_element_pt ;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk pop_last;
  SQ·Lnk alloc_fail;
};

struct TM2x·resize_bytes_0{
  TM2x·Tape*tape;
  address_t after_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·resize_elements_0{
  TM2x·Tape*tape;
  address_t after_element_n;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk index_gt_n;
};

struct TM2x·write_bytes_0{
  void *src_pt;
  TM2x·Tape*dst;
  address_t dst_byte_i;
  address_t byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk src_index_gt_n;
  SQ·Lnk dst_index_gt_n;
};


#endif
