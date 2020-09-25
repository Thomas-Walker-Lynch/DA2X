
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
  SQ·Sequence test_0 ,test_1;

  #include "Sequence·Text.h"
  #include "CLib·Text.h"
  #include "Inclusive·Text.h"
  #include "TM2x·Text.h"

  Result·Tallies accumulated_results ,*accumulated_results_pt;
  accumulated_results_pt=&accumulated_results;
  Result·Tallies·init(accumulated_results_pt);

  SQ·continue(test_0);
  #include "TM2x·test_0.h"
  #include "TM2x·test_1.h"
  #include "TM2x·test_2.h"

  SQ·def(tests_finished){
    Result·Tallies·print("TM2x·test results" ,accumulated_results_pt);
    return accumulated_results.failed;
  } SQ·end(tests_finished);

  abort();

}

