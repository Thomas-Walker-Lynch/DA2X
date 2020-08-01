#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "Result.h"

int main(){
  union{
    #include "Inclusive·Args"
  }Args;

  union{
    #include "Inclusive·Locals"
  }Locals;

  #include "Inclusive·text"

}
