/*
   makes use of the trampoline technique, and a gcc extension to hold labels in variables

   > gcc -g -o example·trampoline example·trampoline.c
   > ./example·trampoline 
      mallocn succeded 

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define memory_byte_n UINT64_MAX
#define address_t uint64_t
#define continue_from return
typedef void **continuation;

continuation mallocn(void **pt ,address_t n ,continuation success ,continuation fail){
  if( n == memory_byte_n ) continue_from fail;
  *pt = malloc(n+1);
  if(!*pt) continue_from fail;
  continue_from success;
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
