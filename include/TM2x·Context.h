/*
Lambda passing context.

*/

union {

  struct CX·TM2x0·destruct_dealloc_heap{
    TM2x *tape;
    ConveyancePtr nominal;
  };

  struct CX·TM2x0·construct_elements{
    TM2x *tape;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  };

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
