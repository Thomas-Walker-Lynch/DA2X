#include <stdio.h>
#include "misc.h"
#include "Sequence.h"
#include "Inclusive.h"
#include "Inclusive·Types.h"

int main(){
  SQ·Sequence nominal ,SQ·nominal ,gt_address_t_n ,SQ·gt_address_t_n;
  #include "Sequence·Text.h"
  #include "Inclusive·Text.h"

  // result Tableau
    address_t a_0 = 541;
    address_t a_1 = 727;
    address_t r;

  // make a link
    SQ·make_Lnk(mul ,Inclusive·3opLL ,&&Inclusive·mul_ext)
    mul_args.a_0 = &a_0;
    mul_args.a_1 = &a_1;
    mul_ress.r = &r;
    mul_lnks.nominal.sequence = &&nominal;
    mul_lnks.gt_address_t_n.sequence = &&gt_address_t_n;

  SQ·continue_indirect( mul_lnk );

  SQ·def(nominal){
    if( r == 394575 ){
      printf("glorious\n");
      return 0;
    }
    printf("wrong answer\n");
    return 1;
  }SQ·end(nominal);

  SQ·def(gt_address_t_n){
    printf("product unexpectedly overflowed\n");
    return 1;
  }SQ·end(gt_address_t_n);

}
