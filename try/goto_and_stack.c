/*
  gcc -O0 -ggdb goto_and_stack.c
  gcc -S -O0 goto_and_stack.c
*/
#include "stdio.h"
int main(int argc){
  int a = 5;
  {
    int a[1127];
    int i=0;
    while(i < 128){
      a[i] = i;
      i++;
    }
    if( argc == 2 ) goto bail;
    i=0;
    while(i < 128){
      printf("%d" ,a[i]);
      printf("\n");
      i++;
    }
  }
  {
    int a[2121];
    int i=0;
    while(i < 128){
      a[i] = 2*i;
      i++;
    }
    i=0;
    while(i < 128){
      printf("%d" ,a[i]);
      printf("\n");
      i++;
    }
  }
  {
    int a[1024 * 1024 * 1024];
    int i=0;
    while(i < 128){
      a[i] = 2*i;
      i++;
    }
    a[1024*1024*1024 - 1] = 5;
    i=0;
    while(i < 128){
      printf("%d" ,a[i]);
      printf("\n");
      i++;
    }
    printf("%d" ,a[1024*1024*1024 - 1]);
  }
  bail:
  printf("finishing %d" ,a);
  return argc;
}
 
