/*
Lambda passing context.

*/

union {
  struct CX·TM2x0·construct_bytes{
    TM2x *tape;
    address_t byte_n;   // extent of the array, in bytes
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
    address_t alloc_byte_n;
  };

  struct CX·TM2x0·construct_elements{
    TM2x *tape;
    address_t element_n;  // extent of the array, in elements
    address_t element_byte_n; // extent of the element, in bytes
    ConveyancePtr nominal;
    ConveyancePtr index_gt_n;
    ConveyancePtr alloc_fail;
    address_t byte_n;
  };

  struct CX·TM2x0·copy_bytes{
    uint28 end_n;
  };

  struct CX·TM2x0·destruct{
    TM2x *tape;
    ConveyancePtr nominal;
    ConveyancePtr message_dealloc_heap_nominal;
  };

  struct CX·TM2x0·construct_elements{
    TM2x *tape;
    address_t byte_n;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  } construct_elements;

  struct CX·TM2x0·write_bytes{
    TM2x *tape;
    void *source_pt;
    address_t byte_n;
    ConveyancePtr nominal;
  } construct_elements;

  struct CX·TM2x0·write_elements{
    TM2x *tape;
    void *source_pt;
    address_t byte_n;
    ConveyancePtr nominal;
    ConveyancePtr fail;
  } construct_elements;

  struct CX·TM2x0·copy_elements{
    TM2x *src;
    address_t src_element_i;
    TM2x *dst;
    address_t dst_element_i;
    address_t element_n;
    address_t element_byte_n;
    ConveyancePtr nominal;
    ConveyancePtr src_index_gt_n;
    ConveyancePtr dst_index_gt_n;

    address_t byte_n;
    address_t src_byte_i;
    address_t dst_byte_i;

  } copy_elements;

} CX·TM2x0;
