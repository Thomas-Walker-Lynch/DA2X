/*
Lambda passing context.

regex replace that adds the *ar = comment to a struct:
^struct \([2a-zA-Z\_·]*\){\([^}]*\)} [2a-zA-Z\_·]*; → //struct \1 *ar = &Conveyance·Args_pt->\1;
struct \1{\2} \1;

*/

//struct TM2x·construct_elements *ar = &Conveyance·Args_pt->TM2x·construct_elements;
struct TM2x·construct_elements{
  TM2x *tape;
  address_t element_n;  // extent of the array, in elements
  address_t element_byte_n; // extent of the element, in bytes
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
  ConveyancePtr alloc_fail;

  address_t byte_n;
} TM2x·construct_elements;

//struct TM2x·construct_write *ar = &Conveyance·Args_pt->TM2x·construct_write;
struct TM2x·construct_write{
  TM2x *tape;
  TM2x *tape_source;
  ConveyancePtr nominal;
  ConveyancePtr fail;
} TM2x·construct_write;

//struct TM2x·construct_write_bytes *ar = &Conveyance·Args_pt->TM2x·construct_write_bytes;
struct TM2x·construct_write_bytes{
  TM2x *tape;
  void *source_pt;
  address_t byte_n;
  ConveyancePtr nominal;
  ConveyancePtr fail;
} TM2x·construct_write_bytes;


//struct TM2x·construct_write_elements *ar = &Conveyance·Args_pt->TM2x·construct_write_elements;
struct TM2x·construct_write_elements{
  TM2x *tape;
  void *source_pt;
  address_t element_n;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
  ConveyancePtr fail;

  address_t byte_n;
} TM2x·construct_write_elements;


//struct TM2x·construct_write_TM2x *ar = &Conveyance·Args_pt->TM2x·construct_write_TM2x;
struct TM2x·construct_write_TM2x{
  TM2x *tape;
  TM2x *tape_source;
  ConveyancePtr nominal;
  ConveyancePtr fail;
} TM2x·construct_write_TM2x;

/* copy_bytes does not make use of other Conveyance, and does not have local vars.
   struct TM2x·copy_bytes{
   TM2x *src;
   address_t src_byte_i;
   TM2x *dst;
   address_t dst_byte_i;
   address_t byte_n;
   ConveyancePtr nominal;
   ConveyancePtr src_index_gt_n;
   ConveyancePtr dst_index_gt_n;
   } TM2x·copy_bytes;
*/

//struct TM2x·copy_elements *ar = &Conveyance·Args_pt->TM2x·copy_elements;
struct TM2x·copy_elements{
  TM2x *src;
  address_t src_element_i;
  TM2x *dst;
  address_t dst_element_i;
  address_t element_n;  // index of nth element of the copy region
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
  ConveyancePtr src_index_gt_n;
  ConveyancePtr dst_index_gt_n;
} TM2x·copy_elements;

//struct TM2x·dealloc_heap *ar = &Conveyance·Args_pt->TM2x·dealloc_heap;
struct TM2x·dealloc_heap{
  TM2x **tape;
  ConveyancePtr nominal;
} TM2x·dealloc_heap;

//struct TM2x·destruct *ar = &Conveyance·Args_pt->TM2x·destruct;
struct TM2x·destruct{
  TM2x *tape;
  ConveyancePtr nominal;
} TM2x·destruct;

//struct TM2x·index·read *ar = &Conveyance·Args_pt->TM2x·index·read;
struct TM2x·index·read{
  TM2x *tape;
  address_t index;
  address_t element_n;
  address_t element_byte_n;
  void *dst_element_pt;
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
} TM2x·index·read;

//struct TM2x·index·to_pt *ar = &Conveyance·Args_pt->TM2x·index·to_pt;
struct TM2x·index·to_pt{
  TM2x *tape ;
  address_t index;
  address_t element_byte_n;
  void **pt;
  ConveyancePtr nominal;
  ConveyancePtr index_gt_n;
} TM2x·index·to_pt;

//struct TM2x·pop *ar = &Conveyance·Args_pt->TM2x·pop;
struct TM2x·pop{
  TM2x *tape;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr pop_last;
  ConveyancePtr alloc_fail;
} TM2x·pop;

//struct TM2x·push *ar = &Conveyance·Args_pt->TM2x·push;
struct TM2x·push{
  TM2x *tape;
  void *element_base_pt;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
} TM2x·push;

//struct TM2x·push_bytes *ar = &Conveyance·Args_pt->TM2x·push_bytes;
struct TM2x·push_bytes{
  TM2x *tape;
  void *source_pt;
  address_t source_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
} TM2x·push_bytes;

//struct TM2x·push_elements *ar = &Conveyance·Args_pt->TM2x·push_elements;
struct TM2x·push_elements{
  TM2x *tape ;
  void *base_pt;
  address_t element_n ;
  address_t element_byte_n ;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
  ConveyancePtr index_gt_n;
} TM2x·push_elements;

//struct TM2x·push_TM2x *ar = &Conveyance·Args_pt->TM2x·push_TM2x;
struct TM2x·push_TM2x{
  TM2x *tape ;
  TM2x *tape_source;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
} TM2x·push_TM2x;

//struct TM2x·read_pop *ar = &Conveyance·Args_pt->TM2x·read_pop;
struct TM2x·read_pop{
  TM2x *tape ;
  void *dst_element_pt ;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr pop_last;
  ConveyancePtr alloc_fail;
} TM2x·read_pop;

//struct TM2x·resize_bytes *ar = &Conveyance·Args_pt->TM2x·resize_bytes;
struct TM2x·resize_bytes{
  TM2x *tape;
  address_t after_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
} TM2x·resize_bytes;

//struct TM2x·resize_elements *ar = &Conveyance·Args_pt->TM2x·resize_elements;
struct TM2x·resize_elements{
  TM2x *tape;
  address_t after_element_n;
  address_t element_byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
  ConveyancePtr index_gt_n;
} TM2x·resize_elements;

//struct TM2x·write_bytes *ar = &Conveyance·Args_pt->TM2x·write_bytes;
struct TM2x·write_bytes{
  void *src_pt;
  TM2x *dst;
  address_t dst_byte_i;
  address_t byte_n;
  ConveyancePtr nominal;
  ConveyancePtr alloc_fail;
  ConveyancePtr src_index_gt_n;
  ConveyancePtr dst_index_gt_n;
} TM2x·write_bytes;



