/*
  This is not a traditional header, and can not be used as such.

  #include this file inside of a Data union with other conveyance's locals .h files. 

  union0{
   ...
   #include "TM2x·Data"
  }Data;

  A conveyance may make use of multiple interpretations of the Args pad.  The first
  interpretation is the initial one sent with the arguments on it.  This is interpretation
  0. As the conveyance no longer needs access to an argument, it may case the arguments
  pointer to a different interpretation.
  
  In places the field order and packing can matter, because sometimes the code just
  changes the type of a pointer so as to 'inherit' some of the existing fields.

*/


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

struct TM2x·construct_elements_0{
  TM2x *tape;
  address_t element_n;  // extent of the array, in elements
  address_t element_byte_n; // extent of the element, in bytes
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
  ConveyancePtr alloc_fail;
};
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


