/*
  This is not a traditional header, and can not be used as such.

  #include this file inside of a Data union with other conveyance's locals .h files. 

  union{
   ...
   #include "TM2x·AR.h"
  }AR;

  A conveyance may make use of multiple interpretations of the Args pad.  The first
  interpretation is the initial one sent with the arguments on it.  This is interpretation
  0. As the conveyance no longer needs access to an argument, it may case the arguments
  pointer to a different interpretation.
  
  In places the field order and packing can matter, because sometimes the code just
  changes the type of a pointer so as to 'inherit' some of the existing fields.

*/

union{

  struct LC·TM2x·construct_bytes{
    TM2x *tape;
    address_t byte_n;   // extent of the array, in bytes
    ConveyancePtr nominal;
    ConveyancePtr alloc_fail;
    address_t alloc_byte_n;
  };

  struct LC·TM2x·construct_elements{
    TM2x *tape;
    address_t element_n;  // extent of the array, in elements
    address_t element_byte_n; // extent of the element, in bytes
    ConveyancePtr nominal;
    ConveyancePtr index_gt_n;
    ConveyancePtr alloc_fail;
    address_t byte_n;
  };

  struct LC·TM2x·copy_bytes{
    uint28 end_n;
  };

  struct LC·TM2x·destruct{
    TM2x *tape;
    ConveyancePtr nominal;
    ConveyancePtr message_dealloc_heap_nominal;
  };

} TM2x;

