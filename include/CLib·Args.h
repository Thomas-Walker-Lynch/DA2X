#ifndef CLIB_ARGS_H
#define CLIB_ARGS_H

struct{
  void **pt;
  address_t n;
  continuation nominal;
  continuation fail;
} CLib·mallocn;

#endif
