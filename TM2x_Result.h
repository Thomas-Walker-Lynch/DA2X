#ifndef DA2X_RESULT_H
#define DA2X_RESULT_H

typedef struct{
  uint passed;
  uint failed;
  uint n;
}TM2x_Result;
void TM2x_Result_init(TM2x_Result *rp){
  rp->passed = 0;
  rp->failed = 0;
}
void TM2x_Result_passed(TM2x_Result *rp){
  rp->passed++;
}
void TM2x_Result_failed(TM2x_Result *rp){
  rp->failed++;
}
void TM2x_Result_tally(char *mess ,TM2x_Result *rp ,bool *flags ,uint n){
  uint i = 0;
  while( i < n ){
    *flags ? TM2x_Result_passed(rp) : TM2x_Result_failed(rp);
  flags++;
  i++;
  }
  fprintf(stderr ,"%s: %u flags ,%u passed. %u failed.\n" ,mess ,n ,rp->passed ,rp->failed);
}
void TM2x_Result_accumulate(TM2x_Result *acc ,TM2x_Result *rp){
  acc->passed += rp->passed;
  acc->failed += rp->failed;
}
void TM2x_Result_print(char *mess ,TM2x_Result *rp){
  fprintf(stderr ,"%s: %u passed. %u failed.\n" ,mess ,rp->passed ,rp->failed);
}

#endif
