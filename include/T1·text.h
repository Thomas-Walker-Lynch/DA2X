SQ·def(T1·construct){
  T1·Construct·Lnk *lnk = (T1·Construct·Lnk *)SQ·lnk;
  T1·Tape *tape = lnk->args->tape;

  tape->empty = true;
  tape->tape0 = NULL;
  tape->t0 = lnk->args->t0;

  SQ·continue_indirect(lnk->lnks->nominal);

} SQ·end(T1·construct);

SQ·def(T1·destruct){
  T1·Destruct·Lnk *lnk = (T1·Destruct·Lnk *)SQ·lnk;
  T1·Tape *tape = lnk->args->tape;

  if(tape->empty){
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  tape->empty = true;
  SQ·make_Lnk(dealloc_array ,T0·DeallocArray ,tape->t0.dealloc_array);
  dealloc_array_args.tape = tape->tape0;
  dealloc_array_lnks.nominal = lnk->lnks->nominal;
  SQ·continue_indirect(dealloc_array_lnk);

} SQ·end(T1·destruct);

SQ·def(T1·move){
  T1·Move·Lnk *lnk = (T1·Move·Lnk *)SQ·lnk;
  T1·Tape *src = lnk->args->src;
  T1·Tape *dst = lnk->args->dst;

  if( src->empty && dst->empty ){
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  SQ·make_Lnk(destruct ,T1·Destruct ,&&T1·destruct);
  if( src->empty ){
    destruct_args.tape = dst;
    destruct_lnks.nominal = lnk->lnks->nominal;
    SQ·continue_indirect(destruct_lnk);
  }

  if( dst->empty ){
    dst->empty = false;
    dst->tape  = src->tape;
    src->empty = true;
    src->tape  = NULL;
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  T1·Tape *old_dst_tape = dst->tape;
  dst->tape = src->tape;
  src->tape = old_dst_tape;

  destruct_args.tape = src;
  destruct_lnks.nominal = lnk->lnks->nominal;
  SQ·continue_indirect(destruct_lnk);

} SQ·end(T1·move);


SQ·def(T1·lengthen){
  T1·Lengthen·Lnk *lnk = (T1·Lengthen·Lnk *)SQ·lnk;
  T1·Tape *tape = lnk->args->tape;

  if(tape->empty){
    tape->empty = false;
    SQ·make_Lnk(alloc ,T0·AllocTapeHeap ,tape->t0.alloc_tape_heap);
    alloc_ress.tape = &lnk->args->tape->tape0;
    alloc_lnks.nominal.success = &&dist;
    alloc_lnks.fail = lnk->lnks->fail_alloc;
    SQ·continue_indirect(alloc_lnk);
    SQ·def(dist){
      SQ·make_Lnk(alloc_array ,T0·Alloc_ArrayTapeHeap ,tape->t0.alloc_array);
      alloc_array_args.tape = lnk->args->tape->tape0;
      alloc_array_args.n = lnk->args->n;
      alloc_array_lnks.nominal.sequence = &&note_new_area;
      alloc_array_lnks.fail = lnk->lnks->fail_alloc;
      SQ·continue_indirect(alloc_array_lnk);
      SQ·def(note_new_area){
        lnk->ress.new_area = ... need the base_pt from the t0

lnk->lnks->nominal;

      } SQ·end(note_new_areay);
    } SQ·end(dist);
  }

  SQ·make_Lnk(lengthen ,T0·Lengthen ,tape->t0.lengthen);
  lengthen_ress.tape = &lnk->args->tape->tape0;
  lengthen_lnks.nominal.success = &&dist;
  lengthen_lnks.fail = lnk->lnks->fail_lengthen;
  SQ·continue_indirect(lengthen_lnk);



} SQ·end(T1·lengthen);
