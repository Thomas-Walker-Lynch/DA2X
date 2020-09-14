/*
test_0 creates a tableau and continues mul_ib to multiple a couple of numbers.  mul_ib continues
to nominal or gt_address_t_n depending if there is a good result or there was an overflow.
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "misc.h"
#include "MallocCounter.h"
#include "Result.h"
#include "Sequence.h"
#include "Inclusive.h"

#include "Inclusive·DataTypes.h"

int main(){

  #include "Sequence·Text.h"
  #include "Inclusive·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  SQ·continue(test_0);

  SQ·def(test_0){
    SQ·Sequence nominal ,gt_address_t_n ,report;

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

      Inclusive·3opLL·Ress mul_ib_ress;
      mul_ib_ress.r = &r;

      Inclusive·3opLL·Lnks mul_ib_lnks;
      mul_ib_lnks.nominal.sequence = &&nominal;
      mul_ib_lnks.gt_address_t_n.sequence = &&gt_address_t_n;      

    // a link to mul_ib
    //
      Inclusive·3opLL·Lnk lnk_0;
      lnk_0.sequence = &&Inclusive·mul_ib;
      lnk_0.args = &mul_ib_args;
      lnk_0.ress = &mul_ib_ress;
      lnk_0.lnks = &mul_ib_lnks;

    SQ·continue_indirect( lnk_0 );

    // mul_ib continuations
    //
      SQ·def(nominal){
        f[i++] = r == 394575;
        SQ·continue(report);
      }SQ·end(nominal);

      SQ·def(gt_address_t_n){
        f[i++] = false;
        SQ·continue(report);
      }SQ·end(gt_address_t_n);

    SQ·def(report){
      f[i++] = malloc_cnt == MallocCounter·count;
      // f[i++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,results_pt ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,results_pt);
      SQ·continue(tests_finished);
    } SQ·end(report);

  } SQ·end(test_0);

  SQ·def(tests_finished){
    Result·Tallies·print("Inclusive·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  }SQ·end(tests_finished);


}
