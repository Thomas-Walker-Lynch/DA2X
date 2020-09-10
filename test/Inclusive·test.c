/*
test_0 creates a tableau and conveys mul_ib to multiple a couple of numbers.  mul_ib continues
to nominal or gt_address_t_n depending if there is a good result or there was an overflow.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "misc.h"
#include "MallocCounter.h"
#include "Result.h"
#include "Conveyance.h"
#include "Inclusive.h"

#include "Inclusive·DataTypes.h"

int main(){

  #include "Conveyance·Text.h"
  #include "Inclusive·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  CV·convey(test_0);

  CV·def(test_0){
    CV·Conveyance nominal ,gt_address_t_n ,report;

    address_t malloc_cnt = MallocCounter·count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count
    uint64_t r;

    // child argguments and connections
    //
      Inclusive·3opLL·Args mul_ib_args;
      mul_ib_args.a_0 = 541;
      mul_ib_args.a_1 = 727;
      mul_ib_args.rpt = &r;

      Inclusive·3opLL·Lnks mul_ib_lnks;
      mul_ib_lnks.nominal.conveyance = &&nominal;
      mul_ib_lnks.gt_address_t_n.conveyance = &&gt_address_t_n;      

    // a link to mul_ib
    //
      Inclusive·3opLL·Lnk lnk_0;
      lnk_0.conveyance = &&Inclusive·mul_ib;
      lnk_0.args = &mul_ib_args;
      lnk_0.lnks = &mul_ib_lnks;

    CV·convey_indirect( lnk_0 );

    // mul_ib continuations
    //
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

  } CV·end(test_0);

  CV·def(tests_finished){
    Result·Tallies·print("Inclusive·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  }CV·end(tests_finished);


}
