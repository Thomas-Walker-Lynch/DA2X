#ifndef continuation_H
#define continuation_H

  // continuations by trampoline
  #define continuations __label__
  #define continue_into goto *
  #define continue_via_trampoline return
  #define continue_from goto
  typedef void **continuation;
  

#endif
