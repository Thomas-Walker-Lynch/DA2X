

#define S0(x) CLib·mallocn· ## x

struct{
  void **pt;
  address_t n;
  continuation nominal;
  continuation fail;
}S0(args);

#undef S0



