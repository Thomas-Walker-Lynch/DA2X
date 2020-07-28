/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#define S0(x) TM2x·dealloc_heap ## x

  extern address_t TM2x·constructed_count;

  #ifdef DEFAULT_ARGS
  #define tape      S0(args.tape)
  #define nominal   S0(args.nominal) 
  #endif
  #undef DEFAULT_ARGS

  TM2x·dealloc_heap:{
    TM2x·destruct(tape);
    free(tape);
    continue_from nominal;
    cend
  }

  #undef tape
  #undef nominal

#undef S0
