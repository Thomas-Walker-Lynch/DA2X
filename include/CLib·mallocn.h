
#define S0(x) CLib·mallocn· ## x

  // If CLIB·MALLOCN·DEFAULT_ARGS is not defined, you must provide your own definitions.
  // It is possible to include the defaults, then #undef, then #define a new definition.
  // Copmiler optimization should remove unused fields of the above struct.

  // C macro names must be identifers, so we can not include the namespace on the
  // macro names.  We avoid collisions because macro names are always all caps, and
  // and these will be undef'ed right after the inline code is included.
  #ifdef DEFAULT_ARGS
  #define CLib·mallocn·pt      S0(args.pt)
  #define CLib·mallocn·n       S0(args.n)      
  #define CLib·mallocn·nominal S0(args.nominal) 
  #define CLib·mallocn·fail    S0(args.fail)
  #endif
  #undef DEFAULT_ARGS

  CLib·mallocn:{
    if( CLib·mallocn·n == address_t_n ) continue_from fail;
    *CLib·mallocn·pt = malloc(CLib·mallocn·n+1);
    if(!*CLib·mallocn·pt) continue_from CLib·mallocn·fail;
    continue_from CLib·mallocn·nominal;
    cend
  }

  #undef CLib·mallocn·pt
  #undef CLib·mallocn·n 
  #undef CLib·mallocn·nominal
  #undef CLib·mallocn·fail

#undef S0
