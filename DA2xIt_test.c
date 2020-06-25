
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "DA2x_malloc_counter.h"
#include "DA2x.h"
#include "DA2xIt.h"
#include "DA2x_Result.h"

typedef struct {
  uint ref;
  uint result;
} DA2xItClosure;

void DA2xIt_f0(void *item_pt , void *closure){
  uint item = *(uint *)item_pt;
  DA2xItClosure *cpt = closure; 
  cpt->result = cpt->result && (item == cpt->ref++);
}

DA2x_Result test_0(){
  size_t malloc_cnt = DA2x_malloc_cnt;
  size_t outstanding_cnt = DA2x_outstanding_cnt;
  bool f[3];
  uint i = 0;

  DA2x_Result r ,*rp; rp = &r;
  DA2x_Result_init(rp);
  DA2x *a0p = DA2x_alloc(sizeof(int));

  // make an array of data
  uint j=10;
  while(j < 100){
    DA2x_push_write(a0p ,&j);    
    ++j;
  }

  DA2xItClosure c;
  c.ref = 10;
  c.result = true;
  DA2xIt_foreach(a0p ,DA2xIt_f0 ,&c);
  f[i++] = c.result;

  DA2x_dealloc(a0p);
  f[i++] = malloc_cnt == DA2x_malloc_cnt;
  f[i++] = outstanding_cnt == DA2x_outstanding_cnt;
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
