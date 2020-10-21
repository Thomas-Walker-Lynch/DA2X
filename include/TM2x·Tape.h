// 'thread static' allocation class
address_t TM2x·alloc_array_count = 0;

// Allocate a TM2x·Tape header on the heap.
// Note that it is also perfectly fine to statically allocate a TM2x·Tape.
SQ·def(TM2x·alloc_Tape_heap){
  TM2x·AllocTapeHeap·Lnk *lnk = (TM2x·AllocTapeHeap·Lnk *)SQ·lnk;

  CLib·Mallocn·Args m_args;
  CLib·Mallocn·Ress m_ress;
  CLib·Mallocn·Lnks m_lnks;
  CLib·Mallocn·Lnk m_lnk;
  m_lnk.args = &m_args;
  m_lnk.ress = &m_ress;
  m_lnk.lnks = &m_lnks;
  m_lnk.sequence = &&CLib·mallocn;

  address_t n = n_of(TM2x·Tape ); // stack base allocated, so we can safely use its address
  m_args.n  = &n;
  m_ress.allocation = (void **)lnk->ress->tape;
  m_lnks.nominal = lnk->lnks->nominal;
  m_lnks.fail = lnk->lnks->fail;

  SQ·continue_indirect(m_lnk);

} SQ·end(TM2x·alloc_Tape_heap);

// allocates data on the heap
SQ·def(TM2x·alloc_array){
  TM2x·alloc_array_count++; // to assist with debugging
  TM2x·AllocArray·Lnk *lnk = (TM2x·AllocArray·Lnk *)SQ·lnk;

  lnk->args->tape->n = *lnk->args->n;

  // local result tableau (stack base allocated, like everything else)
  //
    address_t alloc_n = TM2x·alloc_n(*lnk->args->n);

    CLib·Mallocn·Args m_args;
    CLib·Mallocn·Ress m_ress;
    CLib·Mallocn·Lnks m_lnks;
    CLib·Mallocn·Lnk m_lnk;
    m_lnk.args = &m_args;
    m_lnk.ress = &m_ress;
    m_lnk.lnks = &m_lnks;
    m_lnk.sequence = &&CLib·mallocn;

    m_args.n  = &alloc_n;
    m_ress.allocation = (void **)&lnk->args->tape->base_pt;
    m_lnks.nominal = lnk->lnks->nominal;
    m_lnks.fail = lnk->lnks->fail_alloc;

  SQ·continue_indirect(m_lnk);

} SQ·end(TM2x·alloc_array);

SQ·def(TM2x·alloc_array_elements){
  TM2x·AllocArrayElements·Lnk *lnk = (TM2x·AllocArrayElements·Lnk *)SQ·lnk;

  // ----------------------------------------
  // result tableau
  //
    address_t n;  // result of mul_idx

  // ----------------------------------------
  // Links
  //
    SQ·make_Lnk(scale_ext ,Inclusive·3opLL ,&&Inclusive·mul_idx);
    SQ·make_Lnk(alloc_array ,TM2x·AllocArray ,&&TM2x·alloc_array);

    scale_ext_lnks = (Inclusive·3opLL·Lnks)
      { .nominal = AS(alloc_array_lnk ,SQ·Lnk)
        ,.gt_address_t_n = lnk->lnks->index_gt_n
      };

    alloc_array_lnks = (TM2x·AllocArray·Lnks)
      { .nominal = lnk->lnks->nominal
        ,.fail_alloc = lnk->lnks->fail_alloc
      };

  // ----------------------------------------
  // sequence results point into the tableau
  //
    scale_ext_ress.r = &n;

  // ----------------------------------------
  // seqeuence args point into the tableau
  //
    scale_ext_args.a_0 = lnk->args->n_Element;
    scale_ext_args.a_1 = lnk->args->element_n_Byte;

    alloc_array_args.tape = lnk->args->tape;
    alloc_array_args.n = &n;

  SQ·continue_indirect(scale_ext_lnk);

} SQ·end(TM2x·alloc_array_elements);

// TM2x·Tape header may be constructed again and reused
SQ·def(TM2x·dealloc_array){
  TM2x·alloc_array_count--; // to assist with debugging
  TM2x·DeallocArray·Lnk *lnk = (TM2x·DeallocArray·Lnk *)SQ·lnk;
  free(lnk->args->tape->base_pt);
  SQ·continue_indirect(lnk->lnks->nominal);  
} SQ·end(TM2x·dealloc_array);

// we are to deallocate the header from the heap
SQ·def(TM2x·dealloc_Tape_heap){
  TM2x·DeallocTapeHeap·Lnk *lnk = (TM2x·DeallocTapeHeap·Lnk *)SQ·lnk;
  free(lnk->args->tape);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(TM2x·dealloc_Tape_heap);


// When operating on a single tape, we often create a temporary tape to accumulate changes
// on. When finished we move the contents of the temporary tape back to the single tape we
// are operating on.  This instruction sequence does the move.
SQ·def(TM2x·move_array){
  // some aliases
  TM2x·MoveArray·Lnk *lnk = (TM2x·MoveArray·Lnk *)SQ·lnk;
  TM2x·Tape *src = lnk->args->src;
  TM2x·Tape *dst = lnk->args->dst;

  TM2x·alloc_array_count--;
  free(dst->base_pt);
  dst->base_pt = src->base_pt;
  src->base_pt = 0; 
  dst->n = src->n;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(TM2x·move_array);

// resize version where the n arg is relative to the current length
SQ·def(TM2x·lengthen){
  SQ·Sequence copy_array_data ,SQ·copy_array_data;
  TM2x·Lengthen·Lnk *lnk = (TM2x·Lengthen·Lnk *)SQ·lnk;
  TM2x·Tape *tape = lnk->args->tape;

  address_t alloc_n = TM2x·alloc_n(tape->n);
  address_t resized_n =  *lnk->args->n + tape->n + 1;
  address_t resized_alloc_n = TM2x·alloc_n(resized_n);

  if( alloc_n == resized_alloc_n ){
    *lnk->ress->new_area_pt = tape->base_pt + tape->n + 1;
    tape->n = resized_n;
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  TM2x·Tape resized_tape;

  // lnks
  SQ·make_Lnk(alloc_array  ,TM2x·AllocArray ,&&TM2x·alloc_array);
  SQ·make_Lnk(move_array   ,TM2x·MoveArray  ,&&TM2x·move_array);

  alloc_array_args.tape = &resized_tape;
  alloc_array_args.n    = &resized_n;
  alloc_array_lnks.nominal.sequence = &&copy_array_data;
  alloc_array_lnks.fail_alloc = lnk->lnks->fail_alloc;

  move_array_args.src = &resized_tape;
  move_array_args.dst = tape;
  move_array_lnks.nominal = lnk->lnks->nominal;

  SQ·continue_indirect(alloc_array_lnk);

  SQ·def(copy_array_data){
    *lnk->ress->new_area_pt = resized_tape.base_pt + tape->n + 1;
    memcpyn(resized_tape.base_pt, tape->base_pt, tape->n);
    SQ·continue_indirect(move_array_lnk);
  }SQ·end(copy_array_data);

} SQ·end(TM2x·lengthen);

// resize version where the n arg is relative to the current length
SQ·def(TM2x·shorten){
  SQ·Sequence copy_array_data ,SQ·copy_array_data;
  TM2x·Shorten·Lnk *lnk = (TM2x·Shorten·Lnk *)SQ·lnk;
  TM2x·Tape *tape = lnk->args->tape;

  if( *lnk->args->n == tape->n ){
    SQ·continue_indirect(lnk->lnks->empty);
  }
  if( *lnk->args->n > tape->n ){
    SQ·continue_indirect(lnk->lnks->fail_left_leftmost);
  }

  address_t alloc_n = TM2x·alloc_n(tape->n);
  address_t resized_n = tape->n - *lnk->args->n - 1;
  address_t resized_alloc_n = TM2x·alloc_n(resized_n);

  if( alloc_n == resized_alloc_n ){
    tape->n = resized_n;
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  // rtab
  TM2x·Tape resized_tape;

  // lnks
  SQ·make_Lnk(alloc_array  ,TM2x·AllocArray ,&&TM2x·alloc_array);
  SQ·make_Lnk(move_array   ,TM2x·MoveArray  ,&&TM2x·move_array);

  alloc_array_args.tape = &resized_tape;
  alloc_array_args.n    = &resized_n;
  alloc_array_lnks.nominal.sequence = &&copy_array_data;
  alloc_array_lnks.fail_alloc = lnk->lnks->fail_alloc;

  move_array_args.src = &resized_tape;
  move_array_args.dst = tape;
  move_array_lnks.nominal = lnk->lnks->nominal;

  SQ·continue_indirect(alloc_array_lnk);

  SQ·def(copy_array_data){
    memcpyn(resized_tape.base_pt, tape->base_pt, resized_n);
    SQ·continue_indirect(move_array_lnk);
  }SQ·end(copy_array_data);

} SQ·end(TM2x·shorten);

