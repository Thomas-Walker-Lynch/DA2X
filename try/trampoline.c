/*
   makes use of the trampoline technique, and a gcc extension to hold labels in variables

   > gcc -g  example·trampoline.c
   > ./a.out
      mallocn succeded 

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define address_t_n UINT64_MAX
#define address_t uint64_t
#define continue_via_trampoline return
typedef void **continuation;

continuation mallocn(void **pt ,address_t n ,continuation success ,continuation fail){
  if( n == address_t_n ) continue_via_trampoline fail;
  *pt = malloc(n+1);
  if(!*pt) continue_via_trampoline fail;
  continue_via_trampoline success;
}

int main(){
  void *pt;
  goto *mallocn(&pt ,10 ,&&success ,&&fail);
  fail:
    fprintf(stderr, "mallocn failed \n");
    return 1;
  success:
    fprintf(stderr, "mallocn succeded \n");
    return 0;
}
