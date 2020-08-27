/*
  bit copy of a struct

> gcc -g  -O0 struct_copy.c
> ./a.out
p1.a0: 10; p1.a1: 11
d.uints.u0: ffffffff; d.uints.u1: fffffffe
d0.uints.u0: ffffffff; d0.uints.u1: fffffffe
d1.uints.u0: ffffffff; d1.uints.u1: fffffffe

*/

#include <stdio.h>
#include <stdlib.h>

struct pair{
  uint a0;
  uint a1;
};

union data{
  struct Data·Uints{
    uint u0;
    uint u1;
  } uints;

  struct  Data·Ints{
    int i0;
    int i1;
  } ints;
};

int main(){
  // ----------------------------------------
  // test 1
  //
    struct pair p0, p1;
    p0.a0 = 10;
    p0.a1 = 11;

    p1 = p0;  // the struct bit copy

    printf("p1.a0: %u; p1.a1: %u\n" ,p1.a0 ,p1.a1);

  // ----------------------------------------
  // test 2 - copy union member strucs
  //
    #if 0
      //struct_copy.c: In function ‘main’:
      //struct_copy.c:45:13: error: incompatible types when assigning to type ‘struct Data·Uints’ from type ‘struct Data·Ints’
      // 45 |   d.uints = d.ints; // the struct bit copy, into itself, rather pointless, but should work
      // get the same error when the  structs are anonymous

      union data d;
      d.ints.i0 = -1;
      d.ints.i1 = -2;

      d.uints = d.ints; // the struct bit copy, into itself, rather pointless, but should work

      printf("d.uints.u0: %x; d.uints.u1: %x\n" ,d.uints.u0 ,d.uints.u1);
    #endif

    #if 0
      //struct_copy.c: In function ‘main’:
      //struct_copy.c:57:21: error: conversion to non-scalar type requested
      //   57 |   d.uints = (struct Data·Uints)d.ints; // the struct bit copy, into itself, rather pointless, but should work
      //      |                     ^~~~~~~~~~

      union data d;
      d.ints.i0 = -1;
      d.ints.i1 = -2;

      d.uints = (struct Data·Uints)d.ints; // the struct bit copy, into itself, rather pointless, but should work

      printf("d.uints.u0: %x; d.uints.u1: %x\n" ,d.uints.u0 ,d.uints.u1);
    #endif

    // but this works...
    union data d;
    d.ints.i0 = -1;
    d.ints.i1 = -2;

    d.uints = *(struct Data·Uints *)&d.ints; // the struct bit copy, into itself, rather pointless, but should work

    printf("d.uints.u0: %x; d.uints.u1: %x\n" ,d.uints.u0 ,d.uints.u1);

  // ----------------------------------------
  // copy unions - uses data d from the prior test
  //
    union data d0 = d;
    union data d1;
    d1 = d;
    
    printf("d0.uints.u0: %x; d0.uints.u1: %x\n" ,d0.uints.u0 ,d0.uints.u1);
    printf("d1.uints.u0: %x; d1.uints.u1: %x\n" ,d1.uints.u0 ,d1.uints.u1);


}
