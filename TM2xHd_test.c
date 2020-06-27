
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "TM2x_malloc_counter.h"
#include "TM2x.h"
#include "TM2xHd.h"
#include "TM2x_Result.h"

typedef struct {
  uint ref;
  uint result;
} TM2xHdContext;

void TM2xHd_f0(void *context ,void *item_pt){
  uint item = *(uint *)item_pt;
  TM2xHdContext *cpt = context; 
  cpt->result = cpt->result && (item == cpt->ref++);
}

TM2x_Result test_0(){
  byte_length_t malloc_cnt = TM2x_malloc_cnt;
  byte_length_t outstanding_cnt = TM2x_outstanding_cnt;
  bool f[3];
  uint i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);
  TM2x *a0p = TM2x_alloc(byte_length_of(int));

  // make an array of data
  uint j=10;
  while(j < 100){
    TM2x_push_write(a0p ,&j);    
    ++j;
  }

  TM2xHdContext c;
  c.ref = 10;
  c.result = true;
  TM2xHd_foreach(&c ,a0p ,TM2xHd_f0);
  f[i++] = c.result;

  TM2x_dealloc(a0p);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = outstanding_cnt == TM2x_outstanding_cnt;
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_0 ");
  return r;
}

bool TM2xHd_p0(void *context ,void *item_pt){
  uint item = *(uint *)item_pt;
  return item >= 100 && item < 356;
}
bool TM2xHd_p1(void *context ,void *item_pt){
  uint item = *(uint *)item_pt;
  return item >= 100 && item < 355;
}
bool TM2xHd_p2(void *context ,void *item_pt){
  uint item = *(uint *)item_pt;
  return item == 248;
}
bool TM2xHd_p3(void *context ,void *item_pt){
  uint item = *(uint *)item_pt;
  return item == 355;
}
bool TM2xHd_p4(void *context ,void *item_pt){
  uint item = *(uint *)item_pt;
  return item == 356;
}

TM2x_Result test_1(){
  byte_length_t malloc_cnt = TM2x_malloc_cnt;
  byte_length_t outstanding_cnt = TM2x_outstanding_cnt;
  bool f[7];
  uint i = 0;

  TM2x_Result r ,*rp; rp = &r;
  TM2x_Result_init(rp);
  TM2x *a0p = TM2x_alloc(byte_length_of(int));

  // make an array of data
  uint j=100;
  while(j < 356){
    TM2x_push_write(a0p ,&j);    
    ++j;
  }

  f[i++] = TM2xHd_all(NULL ,a0p ,TM2xHd_p0);
  f[i++] = !TM2xHd_all(NULL ,a0p ,TM2xHd_p1);
  f[i++] = TM2xHd_exists(NULL ,a0p ,TM2xHd_p3);
  f[i++] = !TM2xHd_exists(NULL ,a0p ,TM2xHd_p4);

  TM2xHd_Mount(a0p ,hd);
  TM2xHd_find(NULL ,hd ,TM2xHd_p2);
  uint t0 = TM2xHd_Read(hd ,uint);
  f[i++] = TM2xHd_is_on_tape(hd) && t0 == 248;
  
  TM2x_dealloc(a0p);
  f[i++] = malloc_cnt == TM2x_malloc_cnt;
  f[i++] = outstanding_cnt == TM2x_outstanding_cnt;
  TM2x_Result_tally(rp ,f ,i);
  if( r.failed > 0 ) TM2x_Result_print(&r ,"test_0 ");
  return r;
}

int main(){
  TM2x_Result r ,acc ,*accp; accp=&acc;
  TM2x_Result_init(accp);

  r = test_0(); TM2x_Result_accumulate(accp ,&r);
  r = test_1(); TM2x_Result_accumulate(accp ,&r);

  TM2x_Result_print(accp ,"TM2xHd_test results: ");
  return acc.failed;
}
