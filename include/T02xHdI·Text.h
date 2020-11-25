/*
  This iterator works even when lengthen or shorten operations occur between accesses.

  It is close to working when an entangled machine might perform a lengthen or shorten at
  the same time as an access.  Two issues: 1) coherency between tape->n and tape->base_pt 2)
  possibility of accessing tape->base_pt that has been freed.  Both can be solved by adding
  a mutex variable to the root struct, and then require owning the root struct before
  modifying it.  That would be a new version of the T02x·Root struct.

*/

SQ·def(T02xHdI·bind){
  T0Hd·Bind·Lnk *lnk = (T0Hd·Bind·Lnk *)SQ·lnk;
  T02x·Root *tape = (T02x·Root *) lnk->args->tape;
  T02xHdI·Root *hd = (T02xHdI·Root *) lnk->args->hd;
  hd->tape = tape;
  hd->i = 0;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·bind);

// When we consider the cell the head is on to be the first cell  of the righthand side, this returns
// the extent of the righthand side.
SQ·def(T02xHdI·rhs_n){
  T0Hd·StepRight·Lnk *lnk = (T0Hd·StepRight·Lnk *)SQ·lnk;
  address_t n = lnk->args->hd->tape->n;
  address_t i = lnk->args->hd->i;
  *lnk->ress->n = n - i;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·rhs_n);

SQ·def(T02xHdI·lhs_n){
  T0Hd·StepRight·Lnk *lnk = (T0Hd·StepRight·Lnk *)SQ·lnk;
  address_t i = lnk->args->hd->i;
  *lnk->ress->n = i;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·rhs_n);


SQ·def(T02xHdI·cue_leftmost){
  T0Hd·Leftmost·Lnk *lnk = (T0Hd·Leftmost·Lnk *)SQ·lnk;
  T02xHdI·Root *hd = lnk->args->hd;
  hd->i = 0;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·cue_leftmost);


SQ·def(T02xHdI·cue_rightmost){
  T0Hd·Rightmost·Lnk *lnk = (T0Hd·Rightmost·Lnk *)SQ·lnk;
  address_t en = *lnk->args->element_n;
  address_t  n =  lnk->args->hd->tape->n;
  if( en > n ){
    SQ·continue_indirect(lnk->lnks->left_of_leftmost);
  }
  lnk->args->hd->i = n - en;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·cue_rightmost);


SQ·def(T02xHdI·cue_i){
  T0Hd·Cue·Lnk *lnk = (T0Hd·Cue·Lnk *)SQ·lnk;
  address_t i = *lnk->args->i;
  address_t n = lnk->args->hd->tape->n;
  if( i > n ){
    SQ·continue_indirect(lnk->lnks->right_of_rightmost);
  }
  lnk->args->hd->i = i;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·cue_i);


SQ·def(T02xHdI·cue_pt){
  T0Hd·Cue·Lnk *lnk = (T0Hd·Cue·Lnk *)SQ·lnk;
  char *pti = *lnk->args->pt;
  char *pt0 = lnk->args->hd->tape->base_pt;
  if( pti < pt0 ){
    SQ·continue_indirect(lnk->lnks->left_of_leftmost);
  }
  address_t i  =  pti - pt0;
  address_t n = lnk->args->hd->tape->n;
  if( i > n ){
    SQ·continue_indirect(lnk->lnks->right_of_rightmost);
  }
  lnk->args->hd->i = i;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·cue_pt);


SQ·def(T02xHdI·step_left){
  T0Hd·StepLeft·Lnk *lnk = (T0Hd·StepLeft·Lnk *)SQ·lnk;
  address_t d = *lnk->args->d;
  address_t i = lnk->args->hd->i;
  if( d > i ){
    SQ·continue_indirect(lnk->lnks->left_of_leftmost);
  }
  lnk->args->hd->i -= d;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·step_left);


SQ·def(T02xHdI·step_right){
  T0Hd·StepRight·Lnk *lnk = (T0Hd·StepRight·Lnk *)SQ·lnk;
  address_t d = *lnk->args->d;
  address_t i = lnk->args->hd->i;
  address_t n = lnk->args->hd->tape->n;
  if( d > n - i ){
    SQ·continue_indirect(lnk->lnks->right_of_rightmost);
  }
  lnk->args->hd->i += d;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·step_right);


SQ·def(T02xHdI·read_to_pt){
  T0Hd·ReadToPt·Lnk *lnk = (T0Hd·ReadToPt·Lnk *)SQ·lnk;
  address_t x = *lnk->args->n; // eXtent of area to copy
  address_t i = lnk->args->hd->i;
  address_t n = lnk->args->hd->tape->n;
  if( n - i < x ){
    SQ·continue_indirect(lnk->lnks->underflow);
  }
  memcpyn(lnk->args->pt ,lnk->args->hd->tape->base_pt + i ,x);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·read_to_pt);


SQ·def(T02xHdI·write_from_pt){
  T0Hd·WriteFromPt·Lnk *lnk = (T0Hd·WriteFromPt·Lnk *)SQ·lnk;
  address_t x = *lnk->args->n;
  address_t i = lnk->args->hd->i;
  address_t n = lnk->args->hd->tape->n;
  if( n - i < x ){
    SQ·continue_indirect(lnk->lnks->overflow);
  }
  memcpyn(lnk->args->hd->tape->base_pt + i ,lnk->args->pt ,x);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02xHdI·write_from_pt);


SQ·def(T02xHdI·copy){
  T0Hd·Copy·Lnk *lnk = (T0Hd·Copy·Lnk *)SQ·lnk;
  T02xHdI·Root *src = lnk->args->src;
  T02xHdI·Root *dst = lnk->args->dst;
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
} SQ·end(T02xHdI·copy);


// t02x.bind_hd              = &&T02x·bind_hd;
