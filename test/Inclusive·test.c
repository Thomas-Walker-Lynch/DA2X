/*
Good sign, the optimizer appears to eliminate all of the computation, the only 
thing left is the call to print the passed message:
gcc -s -std=gnu2x -Wall -O3 -I../include -L../lib  -o Inclusive·test.s Inclusive·test.c 
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "Result.h"
#include "Conveyance.h"
#include "Inclusive.h"

int main(){

  union Conveyance·Data{
    #include "Inclusive·Data.h"
  };
  union Conveyance·Data Conveyance·Data0 ,Conveyance·Data1;
  #include "Conveyance·Text.h"
  #include "Inclusive·Text.h"

  Result·Tallies res ,*resp; resp = &res;
  Result·Tallies·init(resp);
  bool f[256];
  uint i = 0;

  continue_from test0;

  test0:{
    Conveyances nominal ,gt_address_t_n;

    uint64_t r;
    struct Inclusive·3opLL  *ar = &Conveyance·Args_pt->Inclusive·3opLL;
    ar->a0 = 541;
    ar->a1 = 727;
    ar->rpt = &r;
    ar->nominal = &&nominal;
    ar->gt_address_t_n = &&gt_address_t_n;
    continue_from Inclusive·mul_ib;

    nominal:{
      f[i++] = r == 394575;
      continue_from report;
      cend;
    }
    gt_address_t_n:{
      f[i++] = false;
      continue_from report;
      cend;
    }

    cend;
  }

  report:{
    Result·Tallies·tally("test_0" ,resp ,f ,i);
    Result·Tallies·print("Inclusive·test results" ,resp);
    exit(resp->failed);
    cend;
  }


}
