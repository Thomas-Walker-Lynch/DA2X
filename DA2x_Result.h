#ifndef DA2X_RESULT_H
#define DA2X_RESULT_H

typedef struct{
  uint passed;
  uint failed;
}DA2x_Result;
void DA2x_Result_init(DA2x_Result *rp){
  rp->passed = 0;
  rp->failed = 0;
}
void DA2x_Result_passed(DA2x_Result *rp){
  rp->passed++;
}
void DA2x_Result_failed(DA2x_Result *rp){
  rp->failed++;
}
void DA2x_Result_tally(DA2x_Result *rp ,bool *flags ,uint n){
  uint i = 0;
  while( i < n ){
    *flags ? DA2x_Result_passed(rp) : DA2x_Result_failed(rp);
  flags++;
  i++;
  }
}
void DA2x_Result_accumulate(DA2x_Result *acc ,DA2x_Result *rp){
  acc->passed += rp->passed;
  acc->failed += rp->failed;
}
void DA2x_Result_print(DA2x_Result *rp, char *mess){
  fprintf(stderr ,"%s passed: %u, failed: %u\n" ,mess ,rp->passed ,rp->failed);
}

#endif
