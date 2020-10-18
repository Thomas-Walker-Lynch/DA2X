
  typedef struct{
  } TM2x·AllocTapeHeap·Args;
  typedef struct{
    TM2x·Tape **tm2x;
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
    TM2x·Tape *tm2x;
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
    TM2x·Tape *tm2x;
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
    TM2x·Tape *tm2x;
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
    TM2x·Tape *tm2x;
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
  } TM2x·CopyTape·Args;
  typedef struct{
  } TM2x·CopyTape·Ress;
  typedef struct{
    SQ·Lnk nominal;
  } TM2x·CopyTape·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·CopyTape·Args *args;
    TM2x·CopyTape·Ress *ress;
    TM2x·CopyTape·Lnks *lnks;
  } TM2x·CopyTape·Lnk;

  typedef struct{
         TM2x·Tape *src;
    address_t *src_0;
         TM2x·Tape *dst;
    address_t *dst_0;
    address_t *n;
  } TM2x·CopyContiguous·Args;
  typedef struct{
  } TM2x·CopyContiguous·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk src_index_gt_n;
    SQ·Lnk dst_index_gt_n;
  } TM2x·CopyContiguous·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·CopyContiguous·Args *args;
    TM2x·CopyContiguous·Ress *ress;
    TM2x·CopyContiguous·Lnks *lnks;
  } TM2x·CopyContiguous·Lnk;


  typedef struct{
         TM2x·Tape *src;
    address_t *src_element_0;
         TM2x·Tape *dst;
    address_t *dst_element_0;
    address_t *n_Element;
    address_t *element_n_Byte;
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



#if 0

struct TM2x·index·read_0{
  TM2x·Tape *tape;
  address_t index;
  address_t n_Element;
  address_t element_n_Byte;
  void *dst_element_pt;
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
};

struct TM2x·index·to_pt_0{
  TM2x·Tape *tape ;
  address_t index;
  address_t element_n_Byte;
  void **pt;
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
};

struct TM2x·pop_0{
  TM2x·Tape *tape;
  address_t element_n_Byte;
  SQ·Lnk nominal;
  SQ·Lnk pop_last;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_0{
  TM2x·Tape *tape;
  void *element_base_pt;
  address_t element_n_Byte;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_bytes_0{
  TM2x·Tape *tape;
  void *source_pt;
  address_t source_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_elements_0{
  TM2x·Tape *tape ;
  void *base_pt;
  address_t n_Element ;
  address_t element_n_Byte ;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk index_gt_n;
};

struct TM2x·push_TM2x_0{
  TM2x·Tape *tape ;
  TM2x·Tape *tape_source;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·read_pop_0{
  TM2x·Tape *tape ;
  void *dst_element_pt ;
  address_t element_n_Byte;
  SQ·Lnk nominal;
  SQ·Lnk pop_last;
  SQ·Lnk alloc_fail;
};

struct TM2x·resize_bytes_0{
  TM2x·Tape *tape;
  address_t after_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·resize_elements_0{
  TM2x·Tape *tape;
  address_t after_n_Element;
  address_t element_n_Byte;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk index_gt_n;
};

struct TM2x·write_bytes_0{
  void *src_pt;
  TM2x·Tape *dst;
  address_t dst_i;
  address_t n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk src_index_gt_n;
  SQ·Lnk dst_index_gt_n;
};


#endif
