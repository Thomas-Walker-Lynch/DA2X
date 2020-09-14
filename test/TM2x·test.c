
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "misc.h"
#include "MallocCounter.h"
#include "Result.h"
#include "Sequence.h"
#include "Inclusive.h"

#define TM2x·TEST
#include "TM2x.h"

#include "CLib·DataTypes.h"
#include "Inclusive·DataTypes.h"
#include "TM2x·DataTypes.h"

int main(){

  #include "Sequence·Text.h"
  #include "CLib·Text.h"
  #include "Inclusive·Text.h"
  #include "TM2x·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  SQ·continue(test_0);

  // allocate, construct, destruct, deallocate an array
  SQ·def(test_0){
    SQ·Sequence nominal ,fail ,cleanup ,report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = TM2x·constructed_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count

    // Args
    //
      TM2x·AllocHeap·Args      ah_args;
      TM2x·ConstructBytes·Args cb_args;
      TM2x·Destruct·Args       da_args;
      TM2x·DeallocHeap·Args    dh_args;

      cb_args.byte_n = 9;

    // results
    //
      TM2x·AllocHeap·Ress ah_ress;
      //      TM2x·ConstructBytes·Ress cb_ress;
      //      TM2x·Destruct·Ress da_ress;
      //      TM2x·DeallocHeap·Ress dh_ress;

      ah_ress.tm2x = &cb_args.tm2x;
      ..           = &da_args.tm2x; // share result to multiple places ..

    // Lnks
    //
      TM2x·AllocHeap·Lnks      ah_lnks;
      TM2x·ConstructBytes·Lnks cb_lnks;
      TM2x·Destruct·Lnks       da_lnks;
      TM2x·DeallocHeap·Lnks    dh_lnks;

    // construct each Lnk
    //
      TM2x·AllocHeap·Lnk       ah_lnk;
      ah_lnk.args = &ah_args;
      ah_lnk.ress = &ah_ress;
      ah_lnk.lnks = &ah_lnks;
      ah_lnk.sequence = &&TM2x·alloc_heap;

      TM2x·ConstructBytes·Lnk  cb_lnk;
      cb_lnk.args = &cb_args;
      //      cb_lnk.ress = &cb_ress;
      cb_lnk.lnks = &cb_lnks;
      cb_lnk.sequence = &&TM2x·construct_bytes;

      TM2x·Destruct·Lnk        da_lnk;
      da_lnk.args = &da_args;
      //      da_lnk.ress = &da_ress;
      da_lnk.lnks = &da_lnks;
      da_lnk.sequence = &&TM2x·destruct;

      TM2x·DeallocHeap·Lnk     dh_lnk;
      dh_lnk.args = &dh_args;
      //      dh_lnk.ress = &dh_ress;
      dh_lnk.lnks = &dh_lnks;
      dh_lnk.sequence = &&TM2x·dealloc_heap;

    // connect links
    //
      ah_lnks.nominal = AS(cb_lnk ,SQ·Lnk);
      ah_lnks.fail.sequence = &&fail;

      cb_lnks.nominal = AS(da_lnk ,SQ·Lnk);
      cb_lnks.alloc_fail.sequence = &&fail;

      da_lnks.nominal = AS(dh_lnk ,SQ·Lnk);
      dh_lnks.nominal.sequence = &&nominal;


    SQ·continue_indirect(ah_lnk);

    SQ·def(nominal){
      f[i++] = true;
      SQ·continue(report);
    }SQ·end(nominal);

    SQ·def(fail){
      f[i++] = false;
      SQ·continue(report);
    } SQ·end(fail);

    SQ·def(report){
      f[i++] = malloc_cnt == MallocCounter·count;
      f[i++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,&results ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(tests_finished);
    } SQ·end(report)

  }SQ·end(test_0)


  SQ·def(tests_finished){
    Result·Tallies·print("TM2x·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  } SQ·end(tests_finished);

  abort();

}

