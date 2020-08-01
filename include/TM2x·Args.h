#ifndef TM2X_ARGS_H
#define TM2X_ARGS_H

/*
  This is not a traditional header, and can not be used as such.

  #include this file inside of an Args union with other conveyance's locals .h files. 

  union{
   ...
   #include "TM2x·Args"
  }Args;

*/

    struct TM2x·Args·AllocHeap{
      TM2x *tape;
      continuation nominal;
      continuation fail;
    } alloc_heap;

    struct TM2x·Args·ConstructBytes{
      TM2x *tape;
      address_t byte_n;   // extent of the array, in bytes
      continuation nominal;
      continuation alloc_fail;

      address_t alloc_byte_n;
    } construct_bytes;

    struct TM2x·Args·ConstructElements{
      TM2x *tape;
      address_t element_n;  // extent of the array, in elements
      address_t element_byte_n; // extent of the element, in bytes
      continuation nominal;
      continuation index_gt_n;
      continuation alloc_fail;
    } construct_elements;

    struct TM2x·Args·ConstructWrite{
      TM2x *tape;
      TM2x *tape_source;
      continuation nominal;
      continuation fail;
    } construct_write;

    struct TM2x·Args·ConstructWriteBytes{
      TM2x *tape;
      void *source_pt;
      address_t byte_n;
      continuation nominal;
      continuation fail;
    } construct_write_bytes;

    struct TM2x·Args·ConstructWriteElements{
      TM2x *tape;
      void *source_pt;
      address_t element_n;
      address_t element_byte_n;
      continuation nominal;
      continuation index_gt_n;
      continuation fail;
    } construct_write_elements;

    struct TM2x·Args·ConstructWriteTM2x{
      TM2x *tape;
      TM2x *tape_source;
      continuation nominal;
      continuation fail;
    } construct_write_TM2x;

    struct TM2x·Args·CopyBytes{
      TM2x *src;
      address_t src_byte_i;
      TM2x *dst;
      address_t dst_byte_i;
      address_t byte_n;
      continuation nominal;
      continuation src_index_gt_n;
      continuation dst_index_gt_n;
    } copy_bytes;

    struct TM2x·Args·CopyElements{
      TM2x *src;
      address_t src_element_i;
      TM2x *dst;
      address_t dst_element_i;
      address_t element_n;  // index of nth element of the copy region
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation src_index_gt_n;
      continuation dst_index_gt_n;
    } copy_elements;

    struct TM2x·Args·DeallocHeap{
      TM2x **tape;
      continuation nominal;
    } dealloc_heap;

    struct TM2x·Args·Destruct{
      TM2x *tape;
      continuation nominal;
    } destruct;

    struct TM2x·Args·Index·Read{
      TM2x *tape;
      address_t index;
      address_t element_n;
      address_t element_byte_n;
      void *dst_element_pt;
      continuation nominal;
      continuation index_gt_n;
    } index·read;

    struct TM2x·Args·Index·ToPt{
       TM2x *tape ;
       address_t index;
       address_t element_byte_n;
       void **pt;
       continuation nominal;
       continuation index_gt_n;
    } index·to_pt;

    struct TM2x·Args·Pop{
       TM2x *tape;
       address_t element_byte_n;
       continuation nominal;
       continuation pop_last;
       continuation alloc_fail;
    } pop;

    struct TM2x·Args·Push{
      TM2x *tape;
      void *element_base_pt;
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } push;

    struct TM2x·Args·PushBytes{
      TM2x *tape;
      void *source_pt;
      address_t source_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } push_bytes;

    struct TM2x·Args·PushElements{
      TM2x *tape ;
      void *base_pt;
      address_t element_n ;
      address_t element_byte_n ;
      continuation nominal;
      continuation alloc_fail;
      continuation index_gt_n;
     } push_elements;

    struct TM2x·Args·PushTM2x{
      TM2x *tape ;
      TM2x *tape_source;
      continuation nominal;
      continuation alloc_fail;
    } push_TM2x;

    struct TM2x·Args·ReadPop{
       TM2x *tape ;
       void *dst_element_pt ;
       address_t element_byte_n;
       continuation nominal;
       continuation pop_last;
       continuation alloc_fail;
    } read_pop;

    struct TM2x·Args·ResizeBytes{
      TM2x *tape;
      address_t after_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } resize_bytes;

    struct TM2x·Args·ResizeElements{
      TM2x *tape;
      address_t after_element_n;
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation index_gt_n;
    } resize_elements;

    struct TM2x·Args·WriteBytes{
      void *src_pt;
      TM2x *dst;
      address_t dst_byte_i;
      address_t byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation src_index_gt_n;
      continuation dst_index_gt_n;
    } write_bytes;


