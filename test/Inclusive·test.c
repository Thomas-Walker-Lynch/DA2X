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

  #include "Inclusive·DataTypes.h"
  #include "Conveyance·Text.h"
  #include "Inclusive·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  convey(test0);

  CV·def(test0){
    Conveyance nominal ,gt_address_t_n ,report;

    address_t malloc_cnt = MallocCounter·count;
    // address_t constructed_cnt = TM2x·constructed_count;

    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count

#pragma push_macro("ARGS")
#pragma push_macro("CNXS")
#define ARGS ((Inclusive·3opLL·Args *)CV·args)
#define CNXS ((Inclusive·3opLL·Cnxs *)CV·cnxs)

    uint64_t r;
    register struct Inclusive·3opLL0 *ar = &Conveyance·Args_pt->Inclusive·3opLL;
    ARGS->a0 = 541;
    ARGS->a1 = 727;
    ARGS->rpt = &r;
    CNXS->nominal.convyeance = &&nominal;
    CNXS->gt_address_t_n.conveyance = &&gt_address_t_n;
    general_convey(Inclusive·mul_ib);

#pragma pop_macro("ARGS")
#pragma pop_macro("CNXS")

    CV·def(nominal){
      f[i++] = r == 394575;
      convey(report);
    }CV·end(nominal);

    CV·def(gt_address_t_n){
      f[i++] = false;
      convey(report);
    }CV·end(gt_address_t_n);

    CV·def(report){
      f[i++] = malloc_cnt == MallocCounter·count;
      // f[i++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,results_pt ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,results_pt);
      convey(tests_finished);
    } CV·end(report);

  } CV·end(test0);

  CV·cdef(tests_finished){
    Result·Tallies·print("Inclusive·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  }CV·end(tests_finished);


}
