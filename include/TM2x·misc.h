#ifndef MISC_H
#define MISC_H

  #ifndef TM2x·F_PREFIX 
    //#define TM2x·F_PREFIX static
    //#define TM2x·F_PREFIX extern inline
    #define TM2x·F_PREFIX static inline
  #endif

  #define CAT2(x ,y) x ## y
  #define CAT(x ,y) CAT2(x ,y)
  #define VAR(x) CAT(x, __LINE__)

#endif
