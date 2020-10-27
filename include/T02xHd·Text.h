
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


SQ·def(T02xHd·read_to_point){
  T0Hd·ReadToPoint·Lnk *lnk = (T0Hd·ReadToPoint·Lnk *)SQ·lnk;
  address_t rn = *lnk->args->n;
  address_t  i = lnk->args->hd->i;
  address_t tn = lnk->args->hd->tape->n;
  if( tn - i > rn ){
    SQ·continue_indirect(lnk->lnks->underflow);
  }
  memcpyn(lnk->args->pt ,lnk->args->hd->tape->base_pt + i ,rn);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·read_to_point);


SQ·def(T02xHd·write_to_point){
  T0Hd·WriteToPoint·Lnk *lnk = (T0Hd·WriteToPoint·Lnk *)SQ·lnk;
  address_t wn = *lnk->args->n;
  address_t  i = lnk->args->hd->i;
  address_t tn = lnk->args->hd->tape->n;
  if( tn - i > rn ){
    SQ·continue_indirect(lnk->lnks->overflow);
  }
  memcpyn(lnk->args->hd->tape->base_pt + i ,lnk->args->pt ,wn);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHd·write_to_point);


