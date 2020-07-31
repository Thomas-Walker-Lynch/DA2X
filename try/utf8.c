/*

utf8 in identifiers was added as part of the C99 standard

It was hard to find a good reference of what is allowed and what isn't.  Everything I tried
from UTF-8 in idenifiers did not work, so it is far from being anything.

https://en.cppreference.com/w/cpp/language/identifiers#Unicode_characters_in_identifiers

  2020-07-11T12:42:11Z
  > gcc -std=gnu18 example·utf8.c 
  > ./a.out
  àños:


*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define address_t_n UINT64_MAX
#define address_t uint64_t
#define continue_via_trampoline return
typedef void **continuation;

int main(){
  uint Δ = 1;
  fprintf(stderr, "Δ:%u\n" ,Δ);
  int à·ños = -5;
  fprintf(stderr, "len:%u à·ños:%d\n" ,strlen("à·ños") ,à·ños);
}
