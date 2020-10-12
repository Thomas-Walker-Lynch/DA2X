/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

struct{
  TM2x **tape;
  continuation nominal;
} TM2x·dealloc_header_heap;



