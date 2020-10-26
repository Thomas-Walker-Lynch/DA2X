
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "misc.h"
#include "MallocCounter.h"
#include "Result.h"

#include "Sequence.h"
#include "CLib.h"
#include "Inclusive.h"
#include "T0.h"
#define T02x·TEST
#include "T02x.h"

int main(){
  SQ·Sequence test_0 ,SQ·test_0 ,test_1 ,SQ·test_1 ,test_2  ,SQ·test_2 ,tests_finished, SQ·tests_finished;

  #include "Sequence·Text.h"
  #include "CLib·Text.h"
  #include "Inclusive·Text.h"
  #include "T02x·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  SQ·continue(test_0);
  #include "T02x·test_0.h"
  #include "T02x·test_1.h"
  #include "T02x·test_2.h"

  SQ·def(tests_finished){
    Result·Tallies·print("T02x·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  } SQ·end(tests_finished);

  abort();

}

