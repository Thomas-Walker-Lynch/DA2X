/*
  This is not a traditional header, and can not be used as such.

  #include this file inside of an Args union with other conveyance's locals .h files. 

  union{
   ...
   #include "TM2x·Args"
  }Args;

*/

    struct TM2x·Args·AllocHeap{
      TM2x **tape;
      Conveyance nominal;
      Conveyance fail;
    } TM2x·alloc_heap;

    struct TM2x·Args·ConstructBytes{
      TM2x *tape;
      address_t byte_n;   // extent of the array, in bytes
      Conveyance nominal;
      Conveyance alloc_fail;
    } TM2x·construct_bytes;

    struct TM2x·Args·ConstructElements{
      TM2x *tape;
      address_t element_n;  // extent of the array, in elements
      address_t element_byte_n; // extent of the element, in bytes
      Conveyance nominal;
      Conveyance index_gt_n;
      Conveyance alloc_fail;
    } TM2x·construct_elements;

    struct TM2x·Args·ConstructWrite{
      TM2x *tape;
      TM2x *tape_source;
      Conveyance nominal;
      Conveyance fail;
    } TM2x·construct_write;

    struct TM2x·Args·ConstructWriteBytes{
      TM2x *tape;
      void *source_pt;
      address_t byte_n;
      Conveyance nominal;
      Conveyance fail;
    } TM2x·construct_write_bytes;

    struct TM2x·Args·ConstructWriteElements{
      TM2x *tape;
      void *source_pt;
      address_t element_n;
      address_t element_byte_n;
      Conveyance nominal;
      Conveyance index_gt_n;
      Conveyance fail;
    } TM2x·construct_write_elements;

    struct TM2x·Args·ConstructWriteTM2x{
      TM2x *tape;
      TM2x *tape_source;
      Conveyance nominal;
      Conveyance fail;
    } TM2x·construct_write_TM2x;

    struct TM2x·Args·CopyBytes{
      TM2x *src;
      address_t src_byte_i;
      TM2x *dst;
      address_t dst_byte_i;
      address_t byte_n;
      Conveyance nominal;
      Conveyance src_index_gt_n;
      Conveyance dst_index_gt_n;
    } TM2x·copy_bytes;

    struct TM2x·Args·CopyElements{
      TM2x *src;
      address_t src_element_i;
      TM2x *dst;
      address_t dst_element_i;
      address_t element_n;  // index of nth element of the copy region
      address_t element_byte_n;
      Conveyance nominal;
      Conveyance alloc_fail;
      Conveyance src_index_gt_n;
      Conveyance dst_index_gt_n;
    } TM2x·copy_elements;

    struct TM2x·Args·DeallocHeap{
      TM2x **tape;
      Conveyance nominal;
    } TM2x·dealloc_heap;

    struct TM2x·Args·Destruct{
      TM2x *tape;
      Conveyance nominal;
    } TM2x·destruct;

    struct TM2x·Args·Index·Read{
      TM2x *tape;
      address_t index;
      address_t element_n;
      address_t element_byte_n;
      void *dst_element_pt;
      Conveyance nominal;
      Conveyance index_gt_n;
    } TM2x·index·read;

    struct TM2x·Args·Index·ToPt{
       TM2x *tape ;
       address_t index;
       address_t element_byte_n;
       void **pt;
       Conveyance nominal;
       Conveyance index_gt_n;
    } TM2x·index·to_pt;

    struct TM2x·Args·Pop{
       TM2x *tape;
       address_t element_byte_n;
       Conveyance nominal;
       Conveyance pop_last;
       Conveyance alloc_fail;
    } TM2x·pop;

    struct TM2x·Args·Push{
      TM2x *tape;
      void *element_base_pt;
      address_t element_byte_n;
      Conveyance nominal;
      Conveyance alloc_fail;
    } TM2x·push;

    struct TM2x·Args·PushBytes{
      TM2x *tape;
      void *source_pt;
      address_t source_byte_n;
      Conveyance nominal;
      Conveyance alloc_fail;
    } TM2x·push_bytes;

    struct TM2x·Args·PushElements{
      TM2x *tape ;
      void *base_pt;
      address_t element_n ;
      address_t element_byte_n ;
      Conveyance nominal;
      Conveyance alloc_fail;
      Conveyance index_gt_n;
     } TM2x·push_elements;

    struct TM2x·Args·PushTM2x{
      TM2x *tape ;
      TM2x *tape_source;
      Conveyance nominal;
      Conveyance alloc_fail;
    } TM2x·push_TM2x;

    struct TM2x·Args·ReadPop{
       TM2x *tape ;
       void *dst_element_pt ;
       address_t element_byte_n;
       Conveyance nominal;
       Conveyance pop_last;
       Conveyance alloc_fail;
    } TM2x·read_pop;

    struct TM2x·Args·ResizeBytes{
      TM2x *tape;
      address_t after_byte_n;
      Conveyance nominal;
      Conveyance alloc_fail;
    } TM2x·resize_bytes;

    struct TM2x·Args·ResizeElements{
      TM2x *tape;
      address_t after_element_n;
      address_t element_byte_n;
      Conveyance nominal;
      Conveyance alloc_fail;
      Conveyance index_gt_n;
    } TM2x·resize_elements;

    struct TM2x·Args·WriteBytes{
      void *src_pt;
      TM2x *dst;
      address_t dst_byte_i;
      address_t byte_n;
      Conveyance nominal;
      Conveyance alloc_fail;
      Conveyance src_index_gt_n;
      Conveyance dst_index_gt_n;
    } TM2x·write_bytes;

