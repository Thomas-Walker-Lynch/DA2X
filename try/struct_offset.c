/*
  Pointer use wiht offsetof ?  No, it insists on having the literal type name and literal
  field name.

> gcc struct_offset.c 
> ./a.out
offset: 4 

*/
#include <stdio.h>
#include <stdlib.h>  // needed for uint
#include <stddef.h>  // needed for offsetof

struct Aa {
  uint x;
  uint y;
} aa;

int main(){

  struct Aa *aa_pt = &aa;
  
  // size_t offset = offsetof(struct Aa ,aa_pt->y);
  // struct_offset.c: In function ‘main’:
  // struct_offset.c:21:19: error: ‘struct Aa’ has no member named ‘aa_pt’
  //  21 |   size_t offset = offsetof(struct Aa ,aa_pt->y);
  //     |                   ^~~~~~~~

  // size_t offset = offsetof(*aa_pt ,y);
  // struct_offset.c: In function ‘main’:
  // struct_offset.c:31:28: error: expected specifier-qualifier-list before ‘*’ token
  //    31 |   size_t offset = offsetof(*aa_pt ,y);
  //       |                            ^

  size_t offset = offsetof(struct Aa ,y);

  printf("offset: %zu \n" ,offset);

}
