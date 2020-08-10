/*
  This is not a traditional header, and can not be used as such.

  #include this file inside of a Data union with other conveyance's locals .h files. 

  union{
   ...
   #include "TM2x·AR.h"
  }AR;

  A conveyance may make use of multiple interpretations of the Args pad.  The first
  interpretation is the initial one sent with the arguments on it.  This is interpretation
  . As the conveyance no longer needs access to an argument, it may case the arguments
  pointer to a different interpretation.
  
  In places the field order and packing can matter, because sometimes the code just
  changes the type of a pointer so as to 'inherit' some of the existing fields.

*/

union{
  struct AR·TM2x·alloc_heap{
    TM2x **tape;
    ConveyancePtr nominal;
    ConveyancePtr fail;
  } alloc_heap;

  struct AR·TM2x·construct_bytes{
    TM2x *tape;
    address_t byte_n;   // extent of the array, in bytes
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  } construct_bytes;

  struct AR·TM2x·construct_elements{
    TM2x *tape;
    address_t element_n;  // extent of the array, in elements
    address_t element_byte_n; // extent of the element, in bytes
    ConveyancePtr nominal;
    ConveyancePtr index_gt_n;
    ConveyancePtr alloc_fail;
  } construct_elements;

  struct AR·TM2x·construct_write{
    TM2x *tape;
    TM2x *tape_source;
    ConveyancePtr nominal;
    ConveyancePtr fail;
  } construct_write;

  struct AR·TM2x·construct_write_bytes{
    TM2x *tape;
    void *source_pt;
    address_t byte_n;
    ConveyancePtr nominal;
    ConveyancePtr fail;
  } construct_write_bytes;


  struct AR·TM2x·construct_write_elements{
    TM2x *tape;
    void *source_pt;
    address_t element_n;
    address_t element_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr index_gt_n;
    ConveyancePtr fail;

    address_t byte_n;
  } construct_write_elements;

  struct AR·TM2x·construct_write_TM2x{
    TM2x *tape;
    TM2x *tape_source;
    ConveyancePtr nominal;
    ConveyancePtr fail;
  } construct_write_TM2x;

  struct AR·TM2x·copy_bytes{
    TM2x *src;
    address_t src_byte_i;
    TM2x *dst;
    address_t dst_byte_i;
    address_t byte_n;
    ConveyancePtr nominal;
    ConveyancePtr src_index_gt_n;
    ConveyancePtr dst_index_gt_n;
  } copy_bytes;
  struct AR·TM2x·copy_bytes1{
    uint128 end_n;
  } copy_bytes1;

  struct AR·TM2x·copy_elements{
    TM2x *src;
    address_t src_element_i;
    TM2x *dst;
    address_t dst_element_i;
    address_t element_n;  // index of nth element of the copy region
    address_t element_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr src_index_gt_n;
    ConveyancePtr dst_index_gt_n;
  } copy_elements;

  struct AR·TM2x·dealloc_heap{
    TM2x *tape;
    ConveyancePtr nominal;
  } dealloc_heap;

  struct AR·TM2x·destruct1{
    TM2x *tape;
    ConveyancePtr nominal;
    ConveyancePtr message_dealloc_heap_nominal;
  } destruct1;struct AR·TM2x·destruct{
    TM2x *tape;
    ConveyancePtr nominal;
  } destruct;

  struct AR·TM2x·destruct_dealloc_heap{
    TM2x *tape;
    ConveyancePtr nominal;
  } destruct_dealloc_heap;


  struct AR·TM2x·index·read{
    TM2x *tape;
    address_t index;
    address_t element_n;
    address_t element_byte_n;
    void *dst_element_pt;
    ConveyancePtr nominal;
    ConveyancePtr index_gt_n;
  } index·read;

  struct AR·TM2x·index·to_pt{
    TM2x *tape ;
    address_t index;
    address_t element_byte_n;
    void **pt;
    ConveyancePtr nominal;
    ConveyancePtr index_gt_n;
  } index·to_pt;

  struct AR·TM2x·pop{
    TM2x *tape;
    address_t element_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr pop_last;
    ConveyancePtr alloc_fail;
  } pop;

  struct AR·TM2x·push{
    TM2x *tape;
    void *element_base_pt;
    address_t element_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  } push;

  struct AR·TM2x·push_bytes{
    TM2x *tape;
    void *source_pt;
    address_t source_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  } push_bytes;

  struct AR·TM2x·push_elements{
    TM2x *tape ;
    void *base_pt;
    address_t element_n ;
    address_t element_byte_n ;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
    ConveyancePtr index_gt_n;
  } push_elements;

  struct AR·TM2x·push_TM2x{
    TM2x *tape ;
    TM2x *tape_source;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  } push_TM2x;

  struct AR·TM2x·read_pop{
    TM2x *tape ;
    void *dst_element_pt ;
    address_t element_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr pop_last;
    ConveyancePtr alloc_fail;
  } read_pop;

  struct AR·TM2x·resize_bytes{
    TM2x *tape;
    address_t after_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  } resize_bytes;

  struct AR·TM2x·resize_elements{
    TM2x *tape;
    address_t after_element_n;
    address_t element_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
    ConveyancePtr index_gt_n;
  } resize_elements;

  struct AR·TM2x·write_bytes{
    void *src_pt;
    TM2x *dst;
    address_t dst_byte_i;
    address_t byte_n;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
    ConveyancePtr src_index_gt_n;
    ConveyancePtr dst_index_gt_n;
  } write_bytes;
} TM2x;

