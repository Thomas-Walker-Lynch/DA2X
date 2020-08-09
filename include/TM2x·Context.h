/*
Lambda passing context.

*/

union {
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


} CX·TM2x0;
