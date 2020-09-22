#ifndef RESULT_H
#define RESULT_H

typedef struct{
  uint passed;
  uint failed;
  uint n;
}Result·Tallies;

void Result·Tallies·init(Result·Tallies *rp){
  rp->passed = 0;
  rp->failed = 0;
}

void Result·Tallies·passed(Result·Tallies *rp){
  rp->passed++;
}

void Result·Tallies·failed(Result·Tallies *rp){
  rp->failed++;
}

void Result·Tallies·tally(char *mess ,Result·Tallies *rp ,bool *flags ,uint n){
  uint i = 0;
  while( i < n ){
    *flags ? Result·Tallies·passed(rp) : Result·Tallies·failed(rp);
  flags++;
  i++;
  }
  fprintf(stderr ,"%s: %u flags, %u passed, %u failed.\n" ,mess ,n ,rp->passed ,rp->failed);
}

void Result·Tallies·accumulate(Result·Tallies *acc ,Result·Tallies *rp){
  acc->passed += rp->passed;
  acc->failed += rp->failed;
}

void Result·Tallies·print(char *mess ,Result·Tallies *rp){
  fprintf(stderr ,"%s: %u passed, %u failed.\n" ,mess ,rp->passed ,rp->failed);
}

#endif
