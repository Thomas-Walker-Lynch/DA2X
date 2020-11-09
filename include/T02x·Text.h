// 'thread static' allocation class
address_t T02x·alloc_array_count = 0;

// Allocate a T02x·Root header on the heap.
// Note that it is also perfectly fine to statically allocate a T02x·Root.
SQ·def(T02x·alloc_Tape_heap){
  T0·AllocTapeHeap·Lnk *lnk = (T0·AllocTapeHeap·Lnk *)SQ·lnk;

  SQ·make_Lnk(m ,CLib·Mallocn ,&&CLib·mallocn);
  address_t n = n_of(T02x·Root ); // stack base allocated, so we can safely use its address
  m_args.n  = &n;
  m_ress.allocation = (void **)lnk->ress->tape;
  m_lnks.nominal = lnk->lnks->nominal;
  m_lnks.fail = lnk->lnks->fail;

  SQ·continue_indirect(m_lnk);

} SQ·end(T02x·alloc_Tape_heap);

// allocates data on the heap
SQ·def(T02x·alloc_array){
  T02x·alloc_array_count++; // to assist with debugging
  T0·AllocArray·Lnk *lnk = (T0·AllocArray·Lnk *)SQ·lnk;
  T02x·Root *tape = (T02x·Root *) lnk->args->tape;

  tape->n = *lnk->args->n;

  // local result tableau (stack base allocated, like everything else)
  //
    address_t alloc_n = T02x·alloc_n(*lnk->args->n);

    SQ·make_Lnk(m ,CLib·Mallocn ,&&CLib·mallocn);
    m_args.n  = &alloc_n;
    m_ress.allocation = (void **)&tape->base_pt;
    m_lnks.nominal = lnk->lnks->nominal;
    m_lnks.fail = lnk->lnks->fail_alloc;

  SQ·continue_indirect(m_lnk);

} SQ·end(T02x·alloc_array);

SQ·def(T02x·alloc_array_elements){
  T0·AllocArrayElements·Lnk *lnk = (T0·AllocArrayElements·Lnk *)SQ·lnk;

  // ----------------------------------------
  // result tableau
  //
    address_t n;  // result of mul_idx

  // ----------------------------------------
  // Links
  //
    SQ·make_Lnk(scale_ext ,Inclusive·3opLL ,&&Inclusive·mul_idx);
    SQ·make_Lnk(alloc_array ,T0·AllocArray ,&&T02x·alloc_array);

    scale_ext_lnks = (Inclusive·3opLL·Lnks)
      { .nominal = AS(alloc_array_lnk ,SQ·Lnk)
        ,.gt_address_t_n = lnk->lnks->index_gt_n
      };

    alloc_array_lnks = (T0·AllocArray·Lnks)
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

} SQ·end(T02x·alloc_array_elements);

// T02x·Root header may be constructed again and reused
SQ·def(T02x·dealloc_array){
  T02x·alloc_array_count--; // to assist with debugging
  T0·DeallocArray·Lnk *lnk = (T0·DeallocArray·Lnk *)SQ·lnk;
  T02x·Root *tape = (T02x·Root *) lnk->args->tape;
  free(tape->base_pt);
  SQ·continue_indirect(lnk->lnks->nominal);  
} SQ·end(T02x·dealloc_array);

// we are to deallocate the header from the heap
SQ·def(T02x·dealloc_Tape_heap){
  T0·DeallocTapeHeap·Lnk *lnk = (T0·DeallocTapeHeap·Lnk *)SQ·lnk;
  free(lnk->args->tape);
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02x·dealloc_Tape_heap);


// When operating on a single tape, we often create a temporary tape to accumulate changes
// on. When finished we move the contents of the temporary tape back to the single tape we
// are operating on.  This instruction sequence does the move.
SQ·def(T02x·move_array){
  // some aliases
  T0·MoveArray·Lnk *lnk = (T0·MoveArray·Lnk *)SQ·lnk;
  T02x·Root *src = (T02x·Root *)lnk->args->src;
  T02x·Root *dst = (T02x·Root *)lnk->args->dst;

  T02x·alloc_array_count--;
  free(dst->base_pt);
  dst->base_pt = src->base_pt;
  src->base_pt = NULL;
  dst->n = src->n;
  SQ·continue_indirect(lnk->lnks->nominal);
} SQ·end(T02x·move_array);

// resize version where the n arg is relative to the current length
SQ·def(T02x·lengthen){
  SQ·Sequence copy_array_data ,SQ·copy_array_data;
  T0·Lengthen·Lnk *lnk = (T0·Lengthen·Lnk *)SQ·lnk;
  T02x·Root *tape = (T02x·Root *) lnk->args->tape;

  address_t alloc_n = T02x·alloc_n(tape->n);
  address_t resized_n =  *lnk->args->n + tape->n + 1;
  address_t resized_alloc_n = T02x·alloc_n(resized_n);

  if( alloc_n == resized_alloc_n ){
    *lnk->ress->new_area_pt = tape->base_pt + tape->n + 1;
    tape->n = resized_n;
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  T02x·Root resized_tape;

  // lnks
  SQ·make_Lnk(alloc_array  ,T0·AllocArray ,&&T02x·alloc_array);
  SQ·make_Lnk(move_array   ,T0·MoveArray  ,&&T02x·move_array);

  alloc_array_args.tape = (T0·Root *)&resized_tape;
  alloc_array_args.n    = &resized_n;
  alloc_array_lnks.nominal.sequence = &&copy_array_data;
  alloc_array_lnks.fail_alloc = lnk->lnks->fail_alloc;

  move_array_args.src = (T0·Root *)&resized_tape;
  move_array_args.dst = (T0·Root *)tape;
  move_array_lnks.nominal = lnk->lnks->nominal;

  SQ·continue_indirect(alloc_array_lnk);

  SQ·def(copy_array_data){
    *lnk->ress->new_area_pt = resized_tape.base_pt + tape->n + 1;
    memcpyn(resized_tape.base_pt, tape->base_pt, tape->n);
    SQ·continue_indirect(move_array_lnk);
  }SQ·end(copy_array_data);

} SQ·end(T02x·lengthen);

// resize version where the n arg is relative to the current length
SQ·def(T02x·shorten){
  SQ·Sequence copy_array_data ,SQ·copy_array_data;
  T0·Shorten·Lnk *lnk = (T0·Shorten·Lnk *)SQ·lnk;
  T02x·Root *tape = (T02x·Root *) lnk->args->tape;

  if( *lnk->args->n == tape->n ){
    SQ·continue_indirect(lnk->lnks->empty);
  }
  if( *lnk->args->n > tape->n ){
    SQ·continue_indirect(lnk->lnks->fail_left_leftmost);
  }

  address_t alloc_n = T02x·alloc_n(tape->n);
  address_t resized_n = tape->n - *lnk->args->n - 1;
  address_t resized_alloc_n = T02x·alloc_n(resized_n);

  if( alloc_n == resized_alloc_n ){
    tape->n = resized_n;
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  // rtab
  T02x·Root resized_tape;

  // lnks
  SQ·make_Lnk(alloc_array  ,T0·AllocArray ,&&T02x·alloc_array);
  SQ·make_Lnk(move_array   ,T0·MoveArray  ,&&T02x·move_array);

  alloc_array_args.tape = (T0·Root *)&resized_tape;
  alloc_array_args.n    = &resized_n;
  alloc_array_lnks.nominal.sequence = &&copy_array_data;
  alloc_array_lnks.fail_alloc = lnk->lnks->fail_alloc;

  move_array_args.src = (T0·Root *)&resized_tape;
  move_array_args.dst = (T0·Root *)tape;
  move_array_lnks.nominal = lnk->lnks->nominal;

  SQ·continue_indirect(alloc_array_lnk);

  SQ·def(copy_array_data){
    memcpyn(resized_tape.base_pt, tape->base_pt, resized_n);
    SQ·continue_indirect(move_array_lnk);
  }SQ·end(copy_array_data);

} SQ·end(T02x·shorten);



T0·Iface t02x;
t02x.alloc_Tape_heap      = &&T02x·alloc_Tape_heap;
t02x.alloc_array          = &&T02x·alloc_array;           
t02x.alloc_array_elements = &&T02x·alloc_array_elements;  
t02x.dealloc_array        = &&T02x·dealloc_array;         
t02x.dealloc_Tape_heap    = &&T02x·dealloc_Tape_heap;     
t02x.move_array           = &&T02x·move_array;            
t02x.lengthen             = &&T02x·lengthen;              
t02x.shorten              = &&T02x·shorten;

