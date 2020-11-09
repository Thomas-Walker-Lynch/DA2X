
SQ·def(T02xHd·init_hd){
  T0Hd·InitHd·Lnk *lnk = (T0Hd·InitHd·Lnk *)SQ·lnk;
  T02x·Root *tape = (T02x·Root *) lnk->args->tape;
  T02xHd·Root *hd = (T02xHd·Root *) lnk->args->tape;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·init_hd);

SQ·def(T02xHd·remaining){
  T0Hd·StepRight·Lnk *lnk = (T0Hd·StepRight·Lnk *)SQ·lnk;
  address_t n = lnk->args->hd->tape->n;
  address_t i = lnk->args->hd->i;
  *lnk->ress->r = n - i;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·step_right);


SQ·def(T02xHd·leftmost){
  T0Hd·Leftmost·Lnk *lnk = (T0Hd·Leftmost·Lnk *)SQ·lnk;
  T02xHd·Root *hd = lnk->args->hd;
  hd->i = 0;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·leftmost);


SQ·def(T02xHd·rightmost){
  T0Hd·Rightmost·Lnk *lnk = (T0Hd·Rightmost·Lnk *)SQ·lnk;
  address_t en = *lnk->args->element_n;
  address_t  n =  lnk->args->hd->tape->n;
  if( en > n ){
    SQ·continue_indirect(lnk->lnks->left_of_leftmost);
  }
  lnk->args->hd->i = n - en;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·rightmost);


SQ·def(T02xHd·cue){
  T0Hd·Cue·Lnk *lnk = (T0Hd·Cue·Lnk *)SQ·lnk;
  address_t i = *lnk->args->i;
  address_t n = lnk->args->hd->tape->n;
  if( i > n ){
    SQ·continue_indirect(lnk->lnks->right_of_rightmost);
  }
  lnk->args->hd->i = i;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·cue);


SQ·def(T02xHd·step_left){
  T0Hd·StepLeft·Lnk *lnk = (T0Hd·StepLeft·Lnk *)SQ·lnk;
  address_t d = *lnk->args->d;
  address_t i = lnk->args->hd->i;
  if( d > i ){
    SQ·continue_indirect(lnk->lnks->left_of_leftmost);
  }
  lnk->args->hd->i -= d;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·step_left);


SQ·def(T02xHd·step_right){
  T0Hd·StepRight·Lnk *lnk = (T0Hd·StepRight·Lnk *)SQ·lnk;
  address_t d = *lnk->args->d;
  address_t i = lnk->args->hd->i;
  address_t n = lnk->args->hd->tape->n;
  if( d > n - i ){
    SQ·continue_indirect(lnk->lnks->right_of_rightmost);
  }
  lnk->args->hd->i += d;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·step_right);


SQ·def(T02xHd·read_to_pt){
  T0Hd·ReadToPt·Lnk *lnk = (T0Hd·ReadToPt·Lnk *)SQ·lnk;
  address_t x = *lnk->args->n; // eXtent of area to copy
  address_t i = lnk->args->hd->i;
  address_t n = lnk->args->hd->tape->n;
  if( n - i < x ){
    SQ·continue_indirect(lnk->lnks->underflow);
  }
  memcpyn(lnk->args->pt ,lnk->args->hd->tape->base_pt + i ,x);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·read_to_pt);


SQ·def(T02xHd·write_from_pt){
  T0Hd·WriteFromPt·Lnk *lnk = (T0Hd·WriteFromPt·Lnk *)SQ·lnk;
  address_t x = *lnk->args->n;
  address_t i = lnk->args->hd->i;
  address_t n = lnk->args->hd->tape->n;
  if( n - i < x ){
    SQ·continue_indirect(lnk->lnks->overflow);
  }
  memcpyn(lnk->args->hd->tape->base_pt + i ,lnk->args->pt ,x);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·write_from_pt);


SQ·def(T02xHd·copy){
  T0Hd·Copy·Lnk *lnk = (T0Hd·Copy·Lnk *)SQ·lnk;
  T02xHd·Root *src = lnk->args->src;
  T02xHd·Root *dst = lnk->args->dst;
  address_t x = *lnk->args->n;
  bool underflow = src->tape->n - src->i < x;
  bool overflow  = dst->tape->n - dst->i < x;
  if( underflow || overflow ){
    SQ·Lnk misfit = lnk->lnks.misfit;
    misfit.args->underflow = &underflow;
    misfit.args->overflow  = &overflow;
    SQ·continue_indirect(misfit);
  }
  memcpyn(dst->tape->base_pt + dst->i ,src->tape->base_pt + src->i ,x);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·copy);


// t02x.init_hd              = &&T02x·init_hd;
