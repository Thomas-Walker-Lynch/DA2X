#ifndef MISC_H
#define MISC_H

  #define CAT2(x ,y) x ## y
  #define CAT(x ,y) CAT2(x ,y)
  #define VAR(x) CAT(x, __LINE__)

#endif
