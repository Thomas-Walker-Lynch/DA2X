/*
Good sign, the optimizer appears to eliminate all of the computation, the only 
thing left is the call to print the passed message:
gcc -s -std=gnu2x -Wall -O3 -I../include -L../lib  -o Inclusive·test.s Inclusive·test.c 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

//#include "Result.h"
#include "Conveyance.h"
#include "Inclusive.h"

int main(){

  union Conveyance·Args{
    #include "Inclusive·Locals.h"
  }Conveyance·Args;

  union Conveyance·Locals{
    #include "Inclusive·Locals.h"
  }Conveyance·Locals;

  #include "Conveyance·Text.h"
  #include "Inclusive·Text.h"

  uint64_t r;
  struct Inclusive·3opLL  *s = &Conveyance·Args_pt->Inclusive·3opLL;
  s->a0 = 541;
  s->a1 = 727;
  s->rpt = &r;
  s->nominal = &&nominal;
  s->gt_address_t_n = &&get_address_t_n;
  continue_from Inclusive·mul_ib;

  /*
  #pragma push_macro("S1")
  #undef S1
  #define S1 Conveyance·Args_pt->Inclusive·3opLL
  S1.a0 = 541;
  S1.a1 = 727;
  S1.rpt = &r;
  S1.nominal = &&nominal;
  S1.gt_address_t_n = &&gt_address_t_n;
  continue_from Inclusive·mul_ib;
  #pragma pop_macro("S1") 
  */

  nominal:{
    if( r == 394575 ){
      printf("passed");
      exit(0);
    }
    printf("failed bad result");
    exit(1);
    cend;
  }
  gt_address_t_n:{
    printf("failed overflow");
    exit(1);
    cend;
  }

}
