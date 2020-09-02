/*
  Include this in an encapsulating function before the text includes.

*/

//--------------------------------------------------------------------------------
// allocation
//
  typedef struct{
    TM2x *tape;
  } TM2x·Destruct·Args;

  typedef struct{
    CV·GeneralConvey·Ptr nominal;
  } TM2x·Destruct·Cnxs;

  typedef struct{
    TM2x *tape;
  } TM2x·DeallocHeap·Args;

  typedef struct{
    ConveyancePtr nominal;
  } TM2x·DeallocHeap·Cnxs;


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
    CV·GeneralConvey·Ptr nominal;
    CV·GeneralConvey·Ptr src_index_gt_n;
    CV·GeneralConvey·Ptr dst_index_gt_n;
  } TM2x·CopyElements·Cnxs;


#if 0






//--------------------------------------------------------------------------------
// deprecated

struct TM2x·alloc_heap_0{
  TM2x **tape;
  ConveyancePtr nominal;
  ConveyancePtr fail;
};

struct TM2x·construct_bytes_0{
  TM2x *tape;
  address_t byte_n;   // extent of the array, in bytes
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
};
struct TM2x·construct_bytes_1{
  TM2x *tape;
  address_t byte_n;   // extent of the array, in bytes
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;

  address_t alloc_byte_n;
};

struct TM2x·Args·construct_elements{
  TM2x *tape;
  address_t element_n;  // extent of the array, in elements
  address_t element_byte_n; // extent of the element, in bytes
};

struct TM2x·Cons·construct_elements{
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
  ConveyancePtr alloc_fail;
};

struct TM2x·Context·construct_elements{
  struct TM2x·Args·construct_elements args;
  struct TM2x·Cons·construct_elements cons;
}


struct TM2x·construct_elements_1{
  TM2x *tape;
  address_t element_n;  // extent of the array, in elements
  address_t element_byte_n; // extent of the element, in bytes
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
  ConveyancePtr alloc_fail;

  address_t byte_n;
};

struct TM2x·construct_write_0{
  TM2x *tape;
  TM2x *tape_source;
  ConveyancePtr nominal;
  ConveyancePtr fail;
};

struct TM2x·construct_write_bytes_0{
  TM2x *tape;
  void *source_pt;
  address_t byte_n;
  ConveyancePtr nominal;
  ConveyancePtr fail;
};


struct TM2x·construct_write_elements_0{
  TM2x *tape;
  void *source_pt;
  address_t element_n;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
  ConveyancePtr fail;

  address_t byte_n;
};

struct TM2x·construct_write_TM2x_0{
  TM2x *tape;
  TM2x *tape_source;
  ConveyancePtr nominal;
  ConveyancePtr fail;
};

struct TM2x·copy_bytes_0{
  TM2x *src;
  address_t src_byte_i;
  TM2x *dst;
  address_t dst_byte_i;
  address_t byte_n;
  ConveyancePtr nominal;
  ConveyancePtr src_index_gt_n;
  ConveyancePtr dst_index_gt_n;
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
  ConveyancePtr nominal;
  ConveyancePtr src_index_gt_n;
  ConveyancePtr dst_index_gt_n;
};

struct TM2x·dealloc_heap_0{
  TM2x *tape;
  ConveyancePtr nominal;
};

struct TM2x·destruct_0{
  TM2x *tape;
  ConveyancePtr nominal;
};

struct TM2x·destruct_dealloc_heap_0{
  TM2x *tape;
  ConveyancePtr nominal;
};


struct TM2x·index·read_0{
  TM2x *tape;
  address_t index;
  address_t element_n;
  address_t element_byte_n;
  void *dst_element_pt;
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
};

struct TM2x·index·to_pt_0{
  TM2x *tape ;
  address_t index;
  address_t element_byte_n;
  void **pt;
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
};

struct TM2x·pop_0{
  TM2x *tape;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr pop_last;
  ConveyancePtr alloc_fail;
};

struct TM2x·push_0{
  TM2x *tape;
  void *element_base_pt;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
};

struct TM2x·push_bytes_0{
  TM2x *tape;
  void *source_pt;
  address_t source_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
};

struct TM2x·push_elements_0{
  TM2x *tape ;
  void *base_pt;
  address_t element_n ;
  address_t element_byte_n ;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
  ConveyancePtr index_gt_n;
};

struct TM2x·push_TM2x_0{
  TM2x *tape ;
  TM2x *tape_source;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
};

struct TM2x·read_pop_0{
  TM2x *tape ;
  void *dst_element_pt ;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr pop_last;
  ConveyancePtr alloc_fail;
};

struct TM2x·resize_bytes_0{
  TM2x *tape;
  address_t after_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
};

struct TM2x·resize_elements_0{
  TM2x *tape;
  address_t after_element_n;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
  ConveyancePtr index_gt_n;
};

struct TM2x·write_bytes_0{
  void *src_pt;
  TM2x *dst;
  address_t dst_byte_i;
  address_t byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
  ConveyancePtr src_index_gt_n;
  ConveyancePtr dst_index_gt_n;
};


#endif
