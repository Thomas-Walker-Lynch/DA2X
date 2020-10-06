/*
Example of specific use instruction sequences.

*/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "misc.h"
#include "Sequence.h"

int main(int argc ,char **argv){
  SQ·Sequence reduce ,SQ·reduce ,expand ,SQ·expand;

  uint32_t i;
  if( argc != 2 || !sscanf(argv[1], "%" SCNu32, &i) ){
    fprintf(stderr ,"expected a positive numeric argument that fits in uint32_t");
    return 1;
  }

  SQ·continue(reduce);

  SQ·def(reduce){
    printf("%" PRIu32 "\n", i);
    if( i == 1 ) return 0;
    if( i & 0x1 ) SQ·continue(expand);
    i = i >> 1;
    SQ·continue(reduce);
  }SQ·end(reduce);
    
  SQ·def(expand){
    uint64_t result = (uint64_t) i * 3 + 1;
    if( result > UINT32_MAX ){
      printf("exploded!");
      return 2;
    }
    i = result;
    SQ·continue(reduce);
  }SQ·end(expand);

}
