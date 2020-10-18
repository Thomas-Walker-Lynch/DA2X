/*
  This is not a traditional header, and can not be used as such.

  #include this file inside of an Args union with other sequence's locals .h files. 

  union{
   ...
   #include "TM2x·Args"
  }Args;

*/

    struct TM2x·Args·AllocHeap{
      TM2x·Tape**tape;
      Sequence nominal;
      Sequence fail;
    } TM2x·alloc_Tape_heap;

    struct TM2x·Args·ConstructBytes{
      TM2x·Tape*tape;
      address_t byte_n;   // extent of the array, in bytes
      Sequence nominal;
      Sequence alloc_fail;
    } TM2x·alloc_array_bytes;

    struct TM2x·Args·AllocArrayElements{
      TM2x·Tape*tape;
      address_t element_n;  // extent of the array, in elements
      address_t element_byte_n; // extent of the element, in bytes
      Sequence nominal;
      Sequence index_gt_n;
      Sequence alloc_fail;
    } TM2x·alloc_array_elements;

    struct TM2x·Args·ConstructWrite{
      TM2x·Tape*tape;
      TM2x·Tape*tape_source;
      Sequence nominal;
      Sequence fail;
    } TM2x·construct_write;

    struct TM2x·Args·ConstructWriteBytes{
      TM2x·Tape*tape;
      void *source_pt;
      address_t byte_n;
      Sequence nominal;
      Sequence fail;
    } TM2x·construct_write_bytes;

    struct TM2x·Args·ConstructWriteElements{
      TM2x·Tape*tape;
      void *source_pt;
      address_t element_n;
      address_t element_byte_n;
      Sequence nominal;
      Sequence index_gt_n;
      Sequence fail;
    } TM2x·construct_write_elements;

    struct TM2x·Args·ConstructWriteTM2x{
      TM2x·Tape*tape;
      TM2x·Tape*tape_source;
      Sequence nominal;
      Sequence fail;
    } TM2x·construct_write_TM2x;

    struct TM2x·Args·CopyContiguousBytes{
      TM2x·Tape*src;
      address_t src_byte_i;
      TM2x·Tape*dst;
      address_t dst_byte_i;
      address_t byte_n;
      Sequence nominal;
      Sequence src_index_gt_n;
      Sequence dst_index_gt_n;
    } TM2x·copy_contiguous_bytes;

    struct TM2x·Args·CopyContiguousElements{
      TM2x·Tape*src;
      address_t src_element_i;
      TM2x·Tape*dst;
      address_t dst_element_i;
      address_t element_n;  // index of nth element of the copy region
      address_t element_byte_n;
      Sequence nominal;
      Sequence alloc_fail;
      Sequence src_index_gt_n;
      Sequence dst_index_gt_n;
    } TM2x·copy_contiguous_elements;

    struct TM2x·Args·DeallocHeap{
      TM2x·Tape**tape;
      Sequence nominal;
    } TM2x·dealloc_Tape_heap;

    struct TM2x·Args·Destruct{
      TM2x·Tape*tape;
      Sequence nominal;
    } TM2x·dealloc_array;

    struct TM2x·Args·Index·Read{
      TM2x·Tape*tape;
      address_t index;
      address_t element_n;
      address_t element_byte_n;
      void *dst_element_pt;
      Sequence nominal;
      Sequence index_gt_n;
    } TM2x·index·read;

    struct TM2x·Args·Index·ToPt{
       TM2x·Tape*tape ;
       address_t index;
       address_t element_byte_n;
       void **pt;
       Sequence nominal;
       Sequence index_gt_n;
    } TM2x·index·to_pt;

    struct TM2x·Args·Pop{
       TM2x·Tape*tape;
       address_t element_byte_n;
       Sequence nominal;
       Sequence pop_last;
       Sequence alloc_fail;
    } TM2x·pop;

    struct TM2x·Args·Push{
      TM2x·Tape*tape;
      void *element_base_pt;
      address_t element_byte_n;
      Sequence nominal;
      Sequence alloc_fail;
    } TM2x·push;

    struct TM2x·Args·PushBytes{
      TM2x·Tape*tape;
      void *source_pt;
      address_t source_byte_n;
      Sequence nominal;
      Sequence alloc_fail;
    } TM2x·push_bytes;

    struct TM2x·Args·PushElements{
      TM2x·Tape*tape ;
      void *base_pt;
      address_t element_n ;
      address_t element_byte_n ;
      Sequence nominal;
      Sequence alloc_fail;
      Sequence index_gt_n;
     } TM2x·push_elements;

    struct TM2x·Args·PushTM2x{
      TM2x·Tape*tape ;
      TM2x·Tape*tape_source;
      Sequence nominal;
      Sequence alloc_fail;
    } TM2x·push_TM2x;

    struct TM2x·Args·ReadPop{
       TM2x·Tape*tape ;
       void *dst_element_pt ;
       address_t element_byte_n;
       Sequence nominal;
       Sequence pop_last;
       Sequence alloc_fail;
    } TM2x·read_pop;

    struct TM2x·Args·ResizeBytes{
      TM2x·Tape*tape;
      address_t after_byte_n;
      Sequence nominal;
      Sequence alloc_fail;
    } TM2x·resize_bytes;

    struct TM2x·Args·ResizeElements{
      TM2x·Tape*tape;
      address_t after_element_n;
      address_t element_byte_n;
      Sequence nominal;
      Sequence alloc_fail;
      Sequence index_gt_n;
    } TM2x·resize_elements;

    struct TM2x·Args·WriteBytes{
      void *src_pt;
      TM2x·Tape*dst;
      address_t dst_byte_i;
      address_t byte_n;
      Sequence nominal;
      Sequence alloc_fail;
      Sequence src_index_gt_n;
      Sequence dst_index_gt_n;
    } TM2x·write_bytes;

