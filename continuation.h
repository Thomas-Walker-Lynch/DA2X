#ifndef continuation_H
#define continuation_H

  // continuations by trampoline
  #define continuations __label__
  #define continue_into goto *
  #define continue_from return
  #define continue_from_local goto
  typedef void **continuation;
  

#endif
