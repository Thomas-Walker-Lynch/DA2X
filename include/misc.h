#ifndef MISC_H
#define MISC_H

// see try/var.c
  #define CAT(x ,y) x ## y
  #define CAT2(x ,y) CAT(x ,y)
  #define VAR(x) CAT2(x, __LINE__)

#endif
