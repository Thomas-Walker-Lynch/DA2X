/*
  Dynamic allocation of the TM2x·Tape header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

struct{
  TM2x·Tape **tape;
  continuation nominal;
} TM2x·dealloc_Tape_heap;



