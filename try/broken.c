/*

gcc -std=gnu2x -Wall -O0 -ggdb  -o broken broken.c 

*/

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef void **SQ·Ptr; 
SQ·Ptr target_pt;
uint i = 0;

int main(){

  goto test0;

  inline void do_jmp(SQ·Ptr target_pt){
    goto *target_pt;
  }
  
  test0:;

  i++; // gets optimized away
  printf("%x\n", i);
  goto report;

  nominal:
  i++;
  goto tests_finished;

  report:;
  target_pt = &&nominal;
  printf("test0: %p\n", &&test0);
  // this will be identical to &&test0 and we haven't even called do_jmp:
  printf("nominal: %p\n", target_pt); 

  if( i == 2 ){
    printf("foo!\n");
    goto tests_finished;
  }
  do_jmp(target_pt);

  tests_finished:;
}
