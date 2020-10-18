#ifndef TM2X_H
#define TM2X_H

/*
  If we are to have thread safety, this file must be included within a function
  such as main(), so that it will be allocated on the stack.

  I an only hope that copying arguments to an args struct, and then copying
  it to a variables in a continuation is pattern that will be reduced to
  one copy by the optimizer. The optimizer can also potentially reduce the
  size of the args struct due to unused members and unused fields within
  memebers.

*/



//--------------------------------------------------------------------------------
// arg structs
//    C requires forward referencing, so all of these come first.  I would
//    rather have put them with the text so as to keep related things together.
//
  union{

    struct AllocHeap{
      TM2x·Tape*tape;
      continuation nominal;
      continuation fail;
    } alloc_Tape_heap;

    struct ConstructBytes{
      TM2x·Tape*tape;
      address_t byte_n;
      continuation nominal;
      continuation alloc_fail;
    } alloc_array_bytes;

    struct ConstructBytes{
      TM2x·Tape*tape;
      address_t element_n;  // number of elements
      address_t element_byte_n; // index of last byte in element
      continuation nominal;
      continuation alloc_fail;
      continuation index_gt_n;
    } alloc_array_bytes;

    struct ConstructWrite{
      TM2x·Tape*tape;
      TM2x·Tape*tape_source;
      continuation nominal;
      continuation fail;
    } construct_write;

    struct ConstructWriteBytes{
      TM2x·Tape*tape;
      void *source_pt;
      address_t byte_n;
      continuation nominal;
      continuation fail;
    } construct_write_bytes;

    struct ConstructWriteElements{
      TM2x·Tape*tape;
      void *source_pt;
      address_t element_n;
      address_t element_byte_n;
      continuation nominal;
      continuation fail;
      continuation index_gt_n;
    } construct_write_elements;

    struct ConstructWriteTM2x{
      TM2x·Tape*tape;
      TM2x·Tape*tape_source;
      continuation nominal;
      continuation fail;
    } construct_write_TM2x;

    struct CopyContiguousBytes{
      TM2x·Tape*src;
      address_t src_byte_i;
      TM2x·Tape*dst;
      address_t dst_byte_i;
      address_t byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation bad_src_index;
      continuation bad_dst_index;
    } copy_contiguous_bytes;

    struct CopyContiguousElements{
      TM2x·Tape*src;
      address_t src_element_i;
      TM2x·Tape*dst;
      address_t dst_element_i;
      address_t element_n;  // index of nth element of the copy region
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation bad_src_index;
      continuation bad_dst_index;
    } copy_contiguous_elements;

    struct DeallocHeap{
      TM2x·Tape**tape;
      continuation nominal;
    } dealloc_Tape_heap;

    struct Destruct{
      TM2x·Tape*tape;
      continuation nominal;
    } destruct;

    struct Index·Read{
      TM2x·Tape*tape;
      address_t index;
      address_t element_n;
      address_t element_byte_n;
      void *dst_element_pt;
      continuation nominal;
      continuation index_gt_n;
    } index·read;

    struct Index·ToPt{
       TM2x·Tape*tape ;
       address_t index;
       address_t element_byte_n;
       void **pt;
       continuation nominal;
       continuation index_gt_n;
    } index·to_pt;

    struct{
       TM2x·Tape*tape;
       address_t element_byte_n;
       continuation nominal;
       continuation pop_last;
       continuation alloc_fail;
    } pop;

    struct Push{
      TM2x·Tape*tape;
      void *element_base_pt;
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } push;

    struct PushBytes{
      TM2x·Tape*tape;
      void *source_pt;
      address_t source_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } push_bytes;

    struct PushElements{
      TM2x·Tape*tape ;
      void *base_pt;
      address_t element_n ;
      address_t element_byte_n ;
      continuation nominal;
      continuation alloc_fail;
      continuation index_gt_n;
     } push_elements;

    struct PushTM2x{
      TM2x·Tape*tape ;
      TM2x·Tape*tape_source;
      continuation nominal;
      continuation alloc_fail;
    } push_TM2x;

    struct ReadPop{
       TM2x·Tape*tape ;
       void *dst_element_pt ;
       address_t element_byte_n;
       continuation nominal;
       continuation pop_last;
       continuation alloc_fail;
    } read_pop;

    struct ResizeBytes{
      TM2x·Tape*tape;
      address_t after_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } resize_bytes;

    struct ResizeElements{
      TM2x·Tape*tape;
      address_t after_element_n;
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation index_gt_n;
    } resize_elements;

    struct WriteBytes{
      void *src_pt;
      TM2x·Tape*dst;
      address_t dst_byte_i;
      address_t byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation bad_src_index;
      continuation bad_dst_index;
    } write_bytes;

  } TM2x·args;

