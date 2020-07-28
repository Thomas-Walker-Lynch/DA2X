/*
  This does work, but it will mess up the C code formatting in emacs.

  gcc -o cend cend.c

*/
#include <stdlib.h>
#include <stdio.h>

#define cbegin(x) x:{
#define cend abort();}

int main(){
  goto block;
  goto end;
  cbegin(block)
    printf("all good");
    goto end;
  cend;
  end:;
}

