
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
  CV·def(test_0):{
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
      ah_lnk.args = &ah_args;
      ah_lnk.lnks = &ah_lnks;
      ah_lnk.conveyance = &&TM2x·alloc_heap;

      TM2x·ConstructBytes·Args cb_args;
      TM2x·ConstructBytes·Lnks cb_lnks;
      TM2x·ConstructBytes·Lnk cb_lnk;
      cb_lnk.args = &cb_args;
      cb_lnk.lnks = &cb_lnks;
      cb_lnk.conveyance = &&TM2x·construct_bytes;

      TM2x·Destruct·Args da_args;
      TM2x·Destruct·Lnks da_lnks;
      TM2x·Destruct·Lnk da_lnk;
      da_lnk.args = &da_args;
      da_lnk.lnks = &da_lnks;
      da_lnk.conveyance = &&TM2x·destruct;

      TM2x·DeallocateHeap·Args dh_args;
      TM2x·DeallocateHeap·Lnks dh_lnks;
      TM2x·DeallocateHeap·Lnk dh_lnk;
      dh_lnk.args = &dh_args;
      dh_lnk.lnks = &dh_lnks;
      dh_lnk.conveyance = &&TM2x·deallocate_heap;

      ah_lnks.nominal = cb_lnk;
      ah_lnks.fail.conveyance = &&fail;

      cb_lnks.nominal = da_lnk;
      cb_lnks.alloc_fail = &&fail;

      da_lnks.nominal = dh_lnk;
      dh_lnks.nominal.conveyance = &&nominal;

    CV·convey_indirect(ah_lnk);

    CV·def(nominal){
      cx->f[cx->i++] = true;
      CV·convey(report);
    }CV·end(nominal);

    CV·def(fail){
      cx->f[cx->i++] = false;
      CV·convey(report);
    } CV·end(fail);

    CV·def(report){
      cx->f[cx->i++] = cx->malloc_cnt == MallocCounter·count;
      cx->f[cx->i++] = cx->constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,&cx->results ,cx->f ,cx->i);
      Result·Tallies·accumulate(accumulated_results_pt ,&cx->results);
      CV·convey(&&tests_finished);
    } CV·end(report)

  }CV·end(test_0)

#if 0

  // Sort of smoke tests, allocates and constructs and array of elements, checks the allocation size.
  // This the first that makes use of a context pad.
  test_1:{
    Conveyance nominal ,fail ,cleanup ,report;

    Conveyance·swap();
    LC(lc ,test_args, 0);
    CX(cx ,TM2x·Test ,test_0);
    cx->malloc_cnt = MallocCounter·count;
    cx->constructed_cnt = TM2x·constructed_count;
    cx->i = 0;
    cx->continuation = lc->continuation;
    Result·Tallies·init(&cx->results);

    //allocate
    AR(ar ,TM2x·alloc_heap ,0);
    ar->tape = &cx->tape;
    ar->nominal = &&nominal;
    ar->fail = &&fail;
    continue_from TM2x·alloc_heap;

    nominal:{
      Conveyance nominal;
      cx->f[cx->i++] = true;

      //construct
      AR(ar ,TM2x·construct_elements ,0);
      ar->tape = cx->tape;
      ar->element_n = 63;
      ar->element_byte_n = 3;
      ar->nominal = &&nominal;
      ar->index_gt_n = &&fail;
      ar->alloc_fail = &&fail;
      continue_from TM2x·construct_elements;

      nominal:{
        cx->f[cx->i++] = Test·CLib·allocation_n == 255;
        continue_from cleanup;
        cend;
      }
      cend;
    }

    fail:{
      cx->f[cx->i++] = false;
      continue_from cleanup;
      cend;
    }

    cleanup:{
      // destruct and deallocate
      AR(ar ,TM2x·destruct_dealloc_heap ,0);
      ar->tape = cx->tape;
      ar->nominal = &&report;
      continue_from TM2x·destruct_dealloc_heap;
      cend;
    }

    report:{
      cx->f[cx->i++] = cx->malloc_cnt == MallocCounter·count;
      cx->f[cx->i++] = cx->constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_1" ,&cx->results ,cx->f ,cx->i);
      Result·Tallies·accumulate(accumulated_results_pt ,&cx->results);
      continue_from *cx->continuation;
      cend;
    }

    cend;
  }

#endif

  CV·(tests_finished){
    Result·Tallies·print("TM2x·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  } CV·(tests_finished);

  abort();

}

