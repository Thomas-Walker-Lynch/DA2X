
  typedef struct{
  } TM2x·AllocHeaderHeap·Args;
  typedef struct{
    TM2x **tm2x;
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
    TM2x *tm2x;
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
    TM2x *tm2x;
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
    TM2x *tm2x;
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
    TM2x *tm2x;
  } TM2x·DeallocHeap·Args;
  typedef struct{
  } TM2x·DeallocHeap·Ress;
  typedef struct{
    SQ·Lnk nominal;
  } TM2x·DeallocHeap·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·DeallocHeap·Args *args;
    TM2x·DeallocHeap·Ress *ress;
    TM2x·DeallocHeap·Lnks *lnks;
  } TM2x·DeallocHeap·Lnk;


  typedef struct{
         TM2x *src;
    address_t *src_byte_0;
         TM2x *dst;
    address_t *dst_byte_0;
    address_t *byte_n;
  } TM2x·CopyBytes·Args;
  typedef struct{
  } TM2x·CopyBytes·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk src_index_gt_n;
    SQ·Lnk dst_index_gt_n;
  } TM2x·CopyBytes·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·CopyBytes·Args *args;
    TM2x·CopyBytes·Ress *ress;
    TM2x·CopyBytes·Lnks *lnks;
  } TM2x·CopyBytes·Lnk;


  typedef struct{
         TM2x *src;
    address_t *src_element_0;
         TM2x *dst;
    address_t *dst_element_0;
    address_t *element_n;
    address_t *element_byte_n;
  } TM2x·CopyElements·Args;
  typedef struct{
  } TM2x·CopyElements·Ress;
  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk src_index_gt_n;
    SQ·Lnk dst_index_gt_n;
  } TM2x·CopyElements·Lnks;
  typedef struct{
    SQ·Ptr sequence;
    TM2x·CopyElements·Args *args;
    TM2x·CopyElements·Ress *ress;
    TM2x·CopyElements·Lnks *lnks;
  } TM2x·CopyElements·Lnk;



#if 0

//--------------------------------------------------------------------------------
// copy elements
//
  typedef struct {
    TM2x *src;
    address_t src_element_i;
    TM2x *dst;
    address_t dst_element_i;
    address_t element_n;  // index of nth element of the copy region
    address_t element_byte_n;
  } TM2x·CopyElements·Args;

  typedef struct {
    SQ·Lnk nominal;
    SQ·Lnk src_index_gt_n;
    SQ·Lnk dst_index_gt_n;
  } TM2x·CopyElements·Lnks;









//--------------------------------------------------------------------------------
// deprecated

struct TM2x·construct_write_0{
  TM2x *tape;
  TM2x *tape_source;
  SQ·Lnk nominal;
  SQ·Lnk fail;
};

struct TM2x·construct_write_bytes_0{
  TM2x *tape;
  void *source_pt;
  address_t byte_n;
  SQ·Lnk nominal;
  SQ·Lnk fail;
};


struct TM2x·construct_write_elements_0{
  TM2x *tape;
  void *source_pt;
  address_t element_n;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
  SQ·Lnk fail;

  address_t byte_n;
};

struct TM2x·construct_write_TM2x_0{
  TM2x *tape;
  TM2x *tape_source;
  SQ·Lnk nominal;
  SQ·Lnk fail;
};

struct TM2x·copy_bytes_0{
  TM2x *src;
  address_t src_byte_i;
  TM2x *dst;
  address_t dst_byte_i;
  address_t byte_n;
  SQ·Lnk nominal;
  SQ·Lnk src_index_gt_n;
  SQ·Lnk dst_index_gt_n;
};
struct TM2x·copy_bytes_1{
  uint_128 end_n;
};

struct TM2x·copy_elements_0{
  TM2x *src;
  address_t src_element_i;
  TM2x *dst;
  address_t dst_element_i;
  address_t element_n;  // index of nth element of the copy region
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk src_index_gt_n;
  SQ·Lnk dst_index_gt_n;
};

struct TM2x·dealloc_header_heap_0{
  TM2x *tape;
  SQ·Lnk nominal;
};

struct TM2x·dealloc_array_0{
  TM2x *tape;
  SQ·Lnk nominal;
};

struct TM2x·dealloc_array_dealloc_header_heap_0{
  TM2x *tape;
  SQ·Lnk nominal;
};


struct TM2x·index·read_0{
  TM2x *tape;
  address_t index;
  address_t element_n;
  address_t element_byte_n;
  void *dst_element_pt;
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
};

struct TM2x·index·to_pt_0{
  TM2x *tape ;
  address_t index;
  address_t element_byte_n;
  void **pt;
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
};

struct TM2x·pop_0{
  TM2x *tape;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk pop_last;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_0{
  TM2x *tape;
  void *element_base_pt;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_bytes_0{
  TM2x *tape;
  void *source_pt;
  address_t source_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·push_elements_0{
  TM2x *tape ;
  void *base_pt;
  address_t element_n ;
  address_t element_byte_n ;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk index_gt_n;
};

struct TM2x·push_TM2x_0{
  TM2x *tape ;
  TM2x *tape_source;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·read_pop_0{
  TM2x *tape ;
  void *dst_element_pt ;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk pop_last;
  SQ·Lnk alloc_fail;
};

struct TM2x·resize_bytes_0{
  TM2x *tape;
  address_t after_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};

struct TM2x·resize_elements_0{
  TM2x *tape;
  address_t after_element_n;
  address_t element_byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk index_gt_n;
};

struct TM2x·write_bytes_0{
  void *src_pt;
  TM2x *dst;
  address_t dst_byte_i;
  address_t byte_n;
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
  SQ·Lnk src_index_gt_n;
  SQ·Lnk dst_index_gt_n;
};


#endif
