/*
  Test if this version of cpp supports the push pragma

  gcc push_pragma.c

can make use of this to turn off unused variable message for some files, change
what is ingored here.
#pragma GCC diagnostic ignored "-Wuninitialized"
 
> ./a.out
inner
outer

 */
#include <stdio.h>

int main(){

  // still requires the undef X with this, when placed before or after the define
  // #pragma weak X

  #define Y 7
  #define X  "outer"

  // this did not work on my installation
  // #pragma MCPP push_macro("X")

  // this works
  #pragma push_macro("X")

  // this is required for X, even when X is declared weak, even when it was just pushed
  // cpp gives errors for this: #undef X, Y
  #undef X
  #undef Y

  #define X "inner"
  printf("%s\n", X);

  // no undef required for pop, but it does not hurt
  // #undef X 

  #pragma pop_macro("X")


  printf("%s\n", X);

}
   
