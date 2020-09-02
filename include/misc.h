#ifndef MISC_H
#define MISC_H

  #ifndef INLINE_PREFIX
    //#define INLINE_PREFIX static
    //#define INLINE_PREFIX extern inline
    #define INLINE_PREFIX static inline
  #endif


// see try/var.c
  #define CAT(x ,y) x ## y
  #define CAT2(x ,y) CAT(x ,y)
  #define VAR(x) CAT2(x, __LINE__)

#define AS(X ,Y) *&(*(Y*)&X)

#endif
