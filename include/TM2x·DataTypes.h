
  typedef struct{
  } TM2x·AllocHeap·Args;

  typedef struct{
    TM2x **tm2x;
  } TM2x·AllocHeap·Ress;

  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk fail;
  } TM2x·AllocHeap·Lnks;

  typedef struct{
    SQ·Ptr sequence;
    TM2x·AllocHeap·Args *args;
    TM2x·AllocHeap·Ress *ress;
    TM2x·AllocHeap·Lnks *lnks;
  } TM2x·AllocHeap·Lnk;


  typedef struct{
    TM2x *tm2x;
    address_t byte_n;   // extent of the array, in bytes
  } TM2x·ConstructBytes·Args;

  typedef struct{
  } TM2x·ConstructBytes·Ress;

  typedef struct{
    SQ·Lnk nominal;
    SQ·Lnk alloc_fail;
  } TM2x·ConstructBytes·Lnks;

  typedef struct{
    SQ·Ptr sequence;
    TM2x·ConstructBytes·Args *args;
    TM2x·ConstructBytes·Ress *ress;
    TM2x·ConstructBytes·Lnks *lnks;
  } TM2x·ConstructBytes·Lnk;


  typedef struct{
    TM2x *tape;
  } TM2x·Destruct·Args;

  typedef struct{
  } TM2x·Destruct·Ress;

  typedef struct{
    SQ·Lnk nominal;
  } TM2x·Destruct·Lnks;

  typedef struct{
    SQ·Ptr sequence;
    TM2x·Destruct·Args *args;
    TM2x·Destruct·Ress *ress;
    TM2x·Destruct·Lnks *lnks;
  } TM2x·Destruct·Lnk;

  typedef struct{
    TM2x *tape;
  } TM2x·DeallocHeap·Args;

  typedef struct{
    SQ·Lnk nominal;
  } TM2x·DeallocHeap·Lnks;

  typedef struct{
    SQ·Ptr sequence;
    TM2x·DeallocHeap·Args *args;
    TM2x·DeallocHeap·Ress *ress;
    TM2x·DeallocHeap·Lnks *lnks;
  } TM2x·DeallocHeap·Lnk;

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

struct TM2x·alloc_heap_0{
  TM2x **tape;
  SQ·Lnk nominal;
  SQ·Lnk fail;
};

struct TM2x·construct_bytes_0{
  TM2x *tape;
  address_t byte_n;   // extent of the array, in bytes
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;
};
struct TM2x·construct_bytes_1{
  TM2x *tape;
  address_t byte_n;   // extent of the array, in bytes
  SQ·Lnk nominal;
  SQ·Lnk alloc_fail;

  address_t alloc_byte_n;
};

struct TM2x·Args·construct_elements{
  TM2x *tape;
  address_t element_n;  // extent of the array, in elements
  address_t element_byte_n; // extent of the element, in bytes
};

struct TM2x·Cons·construct_elements{
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
  SQ·Lnk alloc_fail;
};

struct TM2x·Context·construct_elements{
  struct TM2x·Args·construct_elements args;
  struct TM2x·Cons·construct_elements cons;
}


struct TM2x·construct_elements_1{
  TM2x *tape;
  address_t element_n;  // extent of the array, in elements
  address_t element_byte_n; // extent of the element, in bytes
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
  SQ·Lnk alloc_fail;

  address_t byte_n;
};

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

struct TM2x·dealloc_heap_0{
  TM2x *tape;
  SQ·Lnk nominal;
};

struct TM2x·destruct_0{
  TM2x *tape;
  SQ·Lnk nominal;
};

struct TM2x·destruct_dealloc_heap_0{
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
