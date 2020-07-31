/*

  do labels respect static scoping?

  on top of speghetti .. all covered with cheese ...

  A gcc extension allows you to declare labels, and the declared labels
  follow scope rules.

  2020-07-11T16:31:15Z
  > gcc -g  example·nested_labeling_3.c
  example·nested_labeling_3.c: In function ‘main’:
  example·nested_labeling_3.c:42:5: error: label ‘c’ used but not defined
     42 |     goto c;
        |     ^~~~

  commenting out the declaration of label c:

  2020-07-11T16:33:47Z
  > ./a.out
  outer a:;
  first a:;
  second a:;
  outer b:;

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define address_t_n UINT64_MAX
#define address_t uint64_t
#define continue_via_trampoline return
typedef void **continuation;

int main(){
  __label__ a ,b ,end;

  a:;
  fprintf(stderr, "outer a:;\n");

  {//first
    __label__ a;
    goto a;
      goto end;
    a:;
    fprintf(stderr, "first a:;\n");
    goto c;    
  }
  goto end;

  {//second
    //    __label__ c;
    goto c;
      goto end;
    c:;
    fprintf(stderr, "second a:;\n");
    goto b;
  }

  b:;
    fprintf(stderr, "outer b:;\n");

 end:;

}
