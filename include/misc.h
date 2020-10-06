#ifndef MISC_H
#define MISC_H

// how to handle small functions
//   eventually we will want extern inline so as not to have duplicates when inlining is
//   not possible.
//
  #ifndef INLINE_PREFIX
    //#define INLINE_PREFIX static
    //#define INLINE_PREFIX extern inline
    #define INLINE_PREFIX static inline
  #endif

// make a temp var in a macro, see try/var.c
//
  #define CAT(x ,y) x ## y
  #define CAT2(x ,y) CAT(x ,y)
  #define VAR(x) CAT2(x, __LINE__)

// read X as through it is type T, no questions asked
//
  #define AS(X ,T) (*(T*)&X)

#endif
