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

  #include "Conveyance·Text.h"

  #include "Inclusive·DataTypes.h"
  #include "Inclusive·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  CV·convey(test0);

  CV·def(test0){
    //    CV·Conveyance nominal ,gt_address_t_n ,report;

    address_t malloc_cnt = MallocCounter·count;
    // address_t constructed_cnt = TM2x·constructed_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count
    uint64_t r;

    CV·def(nominal){
      f[i++] = r == 394575;
      CV·convey(report);
    }CV·end(nominal);

    CV·def(gt_address_t_n){
      f[i++] = false;
      CV·convey(report);
    }CV·end(gt_address_t_n);

    CV·def(report){
      f[i++] = malloc_cnt == MallocCounter·count;
      // f[i++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,results_pt ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,results_pt);
      CV·convey(tests_finished);
    } CV·end(report);

    Inclusive·3opLL·Args mul_ib_args;
    mul_ib_args.a_0 = 541;
    mul_ib_args.a_1 = 727;
    mul_ib_args.rpt = &r;

    Inclusive·3opLL·Lnks mul_ib_lnks;
    mul_ib_lnks.nominal.conveyance = &&nominal;
    mul_ib_lnks.gt_address_t_n.conveyance = &&gt_address_t_n;      

    CV·Lnk lnk_0;
    lnk_0.conveyance = &&Inclusive·mul_ib;
    lnk_0.args = (CV·Args *)&mul_ib_args;
    lnk_0.lnks = (CV·Lnks *)&mul_ib_lnks;

    CV·convey_indirect( lnk_0 );

  } CV·end(test0);

  CV·def(tests_finished){
    Result·Tallies·print("Inclusive·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  }CV·end(tests_finished);


}
