
#define S0(x) CLib·mallocn· ## x

  // If CLIB·MALLOCN·DEFAULT_ARGS is not defined, you must provide your own definitions.
  // It is possible to include the defaults, then #undef, then #define a new definition.
  // Copmiler optimization should remove unused fields of the above struct.

  // C macro names must be identifers, so we can not include the namespace on the
  // macro names.  We avoid collisions because macro names are always all caps, and
  // and these will be undef'ed right after the inline code is included.
  #ifdef DEFAULT_ARGS
  #define pt      S0(args.pt)
  #define n       S0(args.n)      
  #define nominal S0(args.nominal) 
  #define fail    S0(args.fail)
  #endif
  #undef DEFAULT_ARGS

  CLib·mallocn:{
    if( n == address_t_n ) continue_from fail;
    *pt = malloc(n+1);
    if(!*pt) continue_from fail;
    continue_from nominal;
    cend
  }

  #undef pt
  #undef n 
  #undef nominal
  #undef fail

#undef S0
