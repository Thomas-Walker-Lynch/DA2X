
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define TM2x·TEST
#include "TM2x.h"
#include "MallocCounter.h"
#include "Result.h"
#include "Conveyance.h"
#include "Inclusive.h"

int main(){

  // ----------------------------------------
  // Includes Conveyance library, and local conveyances

  #include "CLib·DataTypes.h"
  #include "Inclusive·DataTypes.h"
  #include "TM2x·DataTypes.h"
  struct test_args0{
    ConveyancePtr continuation;
  };

  union Conveyance·Data{
    #include "CLib·Data.h"
    #include "Inclusive·Data.h"
    #include "TM2x·Data.h"
    struct test_args0 test_args;
  };
  union Conveyance·Data Conveyance·Data0 ,Conveyance·Data1;

  #include "TM2x·Context.h"
  union {
    struct CX·TM2x·Test·test_0 {
      address_t malloc_cnt;
      address_t constructed_cnt;
      Result·Tallies results;
      bool f[256];
      uint i;
      TM2x *tape;
      ConveyancePtr continuation;
    } test_0;
  } CX·TM2x·Test;

  #include "Conveyance·Text.h"
  #include "CLib·Text.h"
  #include "Inclusive·Text.h"
  #include "TM2x·Text.h"

  // ----------------------------------------
  //  test code

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  ConveyancePtr tests[] = {&&test_0 ,&&test_1 ,&&tests_finished};
  ConveyancePtr *test_pt = tests;

  test_commutator:{
    AR(ar ,test_args ,0);
    ar->continuation = &&test_commutator;
    test_pt++;
    continue_from **(test_pt - 1);
  }

  test_0:{
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
      AR(ar ,TM2x·construct_bytes ,0);
      ar->tape = cx->tape;
      ar->byte_n = 48;
      ar->nominal = &&nominal;
      ar->alloc_fail = &&fail;
      continue_from TM2x·construct_bytes;

      nominal:{
        cx->f[cx->i++] = Test·CLib·allocation_n == 63;
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
      Result·Tallies·tally("test_0" ,&cx->results ,cx->f ,cx->i);
      Result·Tallies·accumulate(accumulated_results_pt ,&cx->results);
      continue_from *cx->continuation;
      cend;
    }

    cend;
  }

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

  tests_finished:{
    Result·Tallies·print("TM2x·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  }


  abort();

}

