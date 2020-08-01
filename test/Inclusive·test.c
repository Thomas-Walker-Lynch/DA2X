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

  union{
    #include "Inclusive·Args.h"
  }Args;

  union{
    #include "Inclusive·Locals.h"
  }Locals;

  //-------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------

  uint64_t r;

  #pragma push_macro("S1")
  #undef S1
  #define S1 Args.Inclusive·3op
  S1.a0 = 541;
  S1.a1 = 727;
  S1.rpt = &r;
  S1.nominal = &&nominal;
  S1.gt_address_t_n = &&gt_address_t_n;
  continue_from Inclusive·mul_ib;
  #pragma pop_macro("S1") 

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

  exraneous:{
    printf("here!");
  }

  //-------------------------------------------------------------------------------------
  //-------------------------------------------------------------------------------------

  #include "Inclusive·text.h"

}
