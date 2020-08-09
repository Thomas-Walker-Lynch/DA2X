/*
Lambda passing context.

*/

union {
  struct{
    TM2x *tape;
    address_t byte_n;
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
  } construct_elements;
}
