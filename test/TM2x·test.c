
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "misc.h"
#include "MallocCounter.h"
#include "Result.h"
#include "Conveyance.h"
#include "Inclusive.h"

#define TM2x·TEST
#include "TM2x.h"

#include "CLib·DataTypes.h"
#include "Inclusive·DataTypes.h"
#include "TM2x·DataTypes.h"

int main(){

  #include "Conveyance·Text.h"
  #include "CLib·Text.h"
  #include "Inclusive·Text.h"
  #include "TM2x·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  CV·convey(test_0);

  // allocate, construct, destruct, deallocate an array
  CV·def(test_0){
    CV·Conveyance nominal ,fail ,cleanup ,report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = TM2x·constructed_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count

    // tableau
    //
      TM2x·AllocHeap·Args ah_args;
      TM2x·AllocHeap·Lnks ah_lnks;
      TM2x·AllocHeap·Lnk ah_lnk;

      TM2x·ConstructBytes·Args cb_args;
      TM2x·ConstructBytes·Lnks cb_lnks;
      TM2x·ConstructBytes·Lnk cb_lnk;

      TM2x·Destruct·Args da_args;
      TM2x·Destruct·Lnks da_lnks;
      TM2x·Destruct·Lnk da_lnk;

      TM2x·DeallocHeap·Args dh_args;
      TM2x·DeallocHeap·Lnks dh_lnks;
      TM2x·DeallocHeap·Lnk dh_lnk;

      ah_lnk.args = &ah_args;
      ah_lnk.lnks = &ah_lnks;
      ah_lnk.conveyance = &&TM2x·alloc_heap;

      cb_lnk.args = &cb_args;
      cb_lnk.lnks = &cb_lnks;
      cb_lnk.conveyance = &&TM2x·construct_bytes;

      da_lnk.args = &da_args;
      da_lnk.lnks = &da_lnks;
      da_lnk.conveyance = &&TM2x·destruct;

      dh_lnk.args = &dh_args;
      dh_lnk.lnks = &dh_lnks;
      dh_lnk.conveyance = &&TM2x·dealloc_heap;

    // connections
    //
      ah_lnks.nominal = AS(cb_lnk ,CV·Lnk);
      ah_lnks.fail.conveyance = &&fail;

      cb_lnks.nominal = AS(da_lnk ,CV·Lnk);
      cb_lnks.alloc_fail.conveyance = &&fail;

      da_lnks.nominal = AS(dh_lnk ,CV·Lnk);
      dh_lnks.nominal.conveyance = &&nominal;

    // results
    //
      ah_args.pt = &cb_args.tm2x;


    CV·convey_indirect(ah_lnk);

    CV·def(nominal){
      f[i++] = true;
      CV·convey(report);
    }CV·end(nominal);

    CV·def(fail){
      f[i++] = false;
      CV·convey(report);
    } CV·end(fail);

    CV·def(report){
      f[i++] = malloc_cnt == MallocCounter·count;
      f[i++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,&results ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      CV·convey(tests_finished);
    } CV·end(report)

  }CV·end(test_0)


  CV·def(tests_finished){
    Result·Tallies·print("TM2x·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  } CV·end(tests_finished);

  abort();

}

