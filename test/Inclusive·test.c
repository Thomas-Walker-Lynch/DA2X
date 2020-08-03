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
#include "MallocCounter.h"

int main(){

  union Conveyance·Data{
    #include "Inclusive·Data.h"
  };
  union Conveyance·Data Conveyance·Data0 ,Conveyance·Data1;
  #include "Conveyance·Text.h"
  #include "Inclusive·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  continue_from test0;

  test0:{
    Conveyance nominal ,gt_address_t_n ,report;

    address_t malloc_cnt = MallocCounter·count;
    // address_t constructed_cnt = TM2x·constructed_count;

    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count

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

    report:{
      f[i++] = malloc_cnt == MallocCounter·count;
      // f[i++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,results_pt ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,results_pt);
      continue_from tests_finished;
      cend;
    }

    cend;
  }

  tests_finished:{
    Result·Tallies·print("Inclusive·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  }


}
