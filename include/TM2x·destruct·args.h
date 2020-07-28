

#define S0(x) TM2x·destruct· ## x

struct{
  TM2x *tape;
  continuation nominal;
}S0(args);

#undef S0



