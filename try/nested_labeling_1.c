/*

   do labels respect static scoping?

   on top of speghetti .. all covered with cheese ...

   2020-07-10T11:38:28Z
   > gcc -g example·nested_labeling.c
   example·nested_labeling.c: In function ‘main’:
   example·nested_labeling.c:29:3: error: duplicate label ‘a’
      29 |   a:;
         |   ^
   example·nested_labeling.c:23:2: note: previous definition of ‘a’ was here
      23 |  a:;
         |  ^
   example·nested_labeling.c:36:3: error: duplicate label ‘a’
      36 |   a:;
         |   ^
   example·nested_labeling.c:23:2: note: previous definition of ‘a’ was here
      23 |  a:;
         |  ^

   .. Braces do not introduce a new context for labels, as they would for other
   declarations.  Hence, the manual namespacing you see in TM2xHd.h

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define address_t_n UINT64_MAX
#define address_t uint64_t
#define continue_via_trampoline return
typedef void **continuation;

int main(){

 a:;
  fprintf(stderr, "outer a:;\n");

  {//first
    goto a;
      goto end;
  a:;
    fprintf(stderr, "first a:;\n");
  }

  {//second
    goto a;
      goto end;
  a:;
    fprintf(stderr, "second a:;\n");
    goto b;
  }
  goto end;

 b:;
  fprintf(stderr, "outer b:;\n");

 end:;

}
