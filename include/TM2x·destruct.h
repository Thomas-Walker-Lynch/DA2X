
#define S0(x) TM2x·destruct· ## x

  extern address_t TM2x·constructed_count;

  #ifdef DEFAULT_ARGS
  #define tape    S0(args.tape)
  #define nominal S0(args.nominal) 
  #endif
  #undef DEFAULT_ARGS

  TM2x·destruct:{
    free(tape->base_pt);
    TM2x·constructed_count--;
    continue_from nominal;
    cend
  }

  #undef tape
  #undef nominal

#undef S0
