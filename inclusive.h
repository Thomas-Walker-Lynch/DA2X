#ifndef inclusive_H
#define inclusive_H
/*
  Address interval inclusive bound versions of some C library functions.

  To make inclusive bounds really work we would need some new C library functions.
  In this sections I provide some mockups.  The implementations of these mockups
  might not respect inclusive bound math.


*/

  #define byte_n_of(type) sizeof(type)-1

  // the n+1 could overflow:
  #define memcpyn(dst ,src ,n) memcpy(dst ,src ,n+1) 
  #define memcmpn(e0 ,e1 ,n) memcmp(e0 ,e1 ,n+1) 
  #define strncmpn(e0 ,e1 ,n) strncmp(e0 ,e1 ,n+1)
  #define str_octet_n(cstring) (strlen(cstring) - 1)

#endif
