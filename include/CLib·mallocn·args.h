
struct{
  void **pt;
  address_t n;
  continuation nominal;
  continuation fail;
}CLib·mallocn·args;

// If CLIB·MALLOCN·DEFAULT_ARGS is not defined, you must provide your own definitions.
// It is possible to include the defaults, then #undef, then #define a new definition.
// Copmiler optimization should remove unused fields of the above struct.
#ifdef CLIB·MALLOCN·DEFAULT_ARGS
  #define CLib·mallocn·args·pt      CLib·mallocn·args.pt
  #define CLib·mallocn·args·n       CLib·mallocn·args.n
  #define CLib·mallocn·args·nominal CLib·mallocn·args.nominal
  #define CLib·mallocn·args·fail    CLib·mallocn·args.fail
#endif
#undef CLIB·MALLOCN·DEFAULT_ARGS
