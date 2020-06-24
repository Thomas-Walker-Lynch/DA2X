
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

size_t DA2_malloc_cnt = 0;
#define malloc(size) (DA2_malloc_cnt++ ,malloc(size))
#define free(pt) (DA2_malloc_cnt-- ,free(pt))

#include "DA2x_malloc_counter.h"
#include "DA2x.h"
#include "DA2xIt.h"
#include "DA2x_Result.h"

typedef struct {
  uint ref;
  uint result;
} DA2xItClosure;

bool DA2xIT_f0(uint *item ,DA2xItClosure *c){
  c->result = c->result && (*item == *(c->ref++));
}

DA2x_Result test_0(){
  size_t malloc_cnt = DA2_malloc_cnt;
  bool f[5];
  uint i = 0;

  DA2x_Result r ,*rp; rp = &r;
  DA2x_Result_init(rp);

  DA2x a0 ,*a0p; a0p=&a0;
  DA2x_init(a0p ,sizeof(int));

  uint j=10;
  while(j < 100){
    DA2x_push_write(a0p ,&j);    
    ++j;
  }

  DA2xITClosure c;
  c.ref = 10;
  c.result = true;
  Da2xIt_foreach(a0p ,DA2xIT_f0 ,&c);
  f[i++] = c.result;

  DA2x_data_dealloc(a0p);
  f[i++] = malloc_cnt == DA2_malloc_cnt;
  DA2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) DA2x_Result_print(&r ,"test_0 ");
  return r;
}

int main(){
  DA2x_Result r ,acc ,*accp; accp=&acc;
  DA2x_Result_init(accp);

  r = test_0(); DA2x_Result_accumulate(accp ,&r);

  DA2x_Result_print(accp ,"DA2xIt_test results: ");
  return acc.failed;
}
