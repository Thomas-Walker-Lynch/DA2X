/*
  This does work, but it will messes up the C code formatting in emacs.

  gcc cend.c

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

