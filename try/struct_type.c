/*
  struct name in struct space can be the same as the instance of struct name.
  typdef created type can not be the same as the instance name.

  gcc struct_type.c

*/
#include <stdio.h>

struct aa {
  int x;
} aa;

typedef struct{
  int y;
} ss;

ss ss;
/*
struct_type.c:17:4: error: ‘ss’ redeclared as different kind of symbol
   17 | ss ss;
*/

int main(){

  struct aa bb ,cc;
  
  aa.x = 3;
  bb.x = 5;
  cc.x = 7; 

  printf(" %d %d %d \n" ,aa.x ,bb.x ,cc.x);

  ss tt ,uu ,vv;

  tt.y = 2;
  uu.y = 4;
  vv.y = 6;

  printf(" %d %d %d \n" ,tt.y ,uu.y ,vv.y);

}
