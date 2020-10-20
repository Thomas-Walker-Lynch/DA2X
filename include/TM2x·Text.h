// 'thread static' allocation class
address_t TM2x·alloc_array_count = 0;

/*--------------------------------------------------------------------------------

  Memory management. 

*/

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
      m_lnks.fail = lnk->lnks->alloc_fail;

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
          ,.alloc_fail = lnk->lnks->alloc_fail
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


  // This should not appear on an interface.
  // Create a new 'resized' tape of the requested size, copy the data over, then copy the
  // the pointers in the resized tape header back to the original tape header.
  SQ·def(TM2x·resize){
    SQ·Sequence copy_data ,SQ·copy_data;
    TM2x·Resize·Lnk *lnk = (TM2x·Resize·Lnk *)SQ·lnk;
    
    address_t n = *lnk->args->n;
    address_t alloc_n = TM2x·alloc_n(lnk->args->tape->n);
    address_t resized_alloc_n = TM2x·alloc_n(n);
    if( alloc_n == resized_alloc_n ){
      lnk->args->tape->n = n;
      SQ·continue_indirect(lnk->lnks->nominal);
    }
  
    // rtab
    TM2x·Tape *original_tape = lnk->args->tape;
    TM2x·Tape resized_tape;

    // lnks
    SQ·make_Lnk(alloc_array  ,TM2x·AllocArray ,&&TM2x·alloc_array);
    SQ·make_Lnk(move_array    ,TM2x·MoveArray   ,&&TM2x·move_array);

    alloc_array_args.tape = &resized_tape;
    alloc_array_args.n    = lnk->args->n;
    alloc_array_lnks.nominal.sequence = &&copy_data;
    alloc_array_lnks.alloc_fail = lnk->lnks->alloc_fail;

    move_array_args.src = &resized_tape;
    move_array_args.dst = original_tape;
    move_array_lnks.nominal = lnk->lnks->nominal;

    SQ·continue_indirect(alloc_array_lnk);

    SQ·def(copy_data){
      address_t n = resized_tape.n < original_tape->n ? resized_tape.n : original_tape->n;
      memcpyn(resized_tape.base_pt, original_tape->base_pt, n);
      SQ·continue_indirect(move_array_lnk);
    }SQ·end(copy_data);

  } SQ·end(TM2x·resize);


#if 0

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

SQ·def(resize_bytes){
  // shorten the arg names, give the optimizer something more to do
  TM2x·Tape *tm2x = Args.TM2x·resize_bytes.tm2x;
  address_t after_n = Args.TM2x·resize_bytes.after_n;
  SequencePtr nominal = Args.TM2x·resize_bytes.nominal;
  SequencePtr alloc_fail = Args.TM2x·resize_bytes.alloc_fail;

  address_t before_alloc_n = TM2x·alloc_n(tm2x->n);
  address_t after_alloc_n = TM2x·alloc_n(after_n);

  if( after_alloc_n == before_alloc_n ){
    tm2x->n = after_n;
    continue_via_trampoline nominal;
  }

  char *after_base_pt;

  #include "Args.CLib·mallocn.h"
  Args.CLib·mallocn.pt      = (void **)&after_base_pt;
  Args.CLib·mallocn.n       = after_alloc_n;
  Args.CLib·mallocn.nominal = &&malloc_nominal;
  Args.CLib·mallocn.fail    = &&malloc_fail; 
  #include "CLib·mallocn.h"
  continue CLib·mallocn;

  SQ·def(malloc_nominal){
    #ifdef TM2x·TEST
      TM2x·Test·allocation_n = after_alloc_n;
    #endif
    address_t copy_n = after_n < tm2x->n ? after_n : tm2x->n;
    memcpyn( after_base_pt ,tm2x->base_pt ,copy_n);
    free(tm2x->base_pt);
    tm2x->base_pt = after_base_pt;
    tm2x->n = after_n;
    continue *nominal;
  } SQ·end(malloc_nominal){

  SQ·def(malloc_fail){
   continue *alloc_fail;
  } SQ·end(malloc_fail);
  
} SQ·end(resize_bytes);









INLINE_PREFIX ContinuationPtr index·to_pt{
  TM2x·Tape *tm2x               = Args.TM2x·index·to_pt.tm2x;
  address_t index          = Args.TM2x·index·to_pt.index;
  address_t element_n_Byte = Args.TM2x·index·to_pt.element_n_Byte;
  void **pt                = Args.TM2x·index·to_pt.pt;
  SequencePtr nominal     = Args.TM2x·index·to_pt.nominal;
  SequencePtr index_gt_n = Args.TM2x·index·to_pt.index_gt_n;

  address_t i;
  inclusive·mul_ext·args.an = index;
  inclusive·mul_ext·args.bn = element_n_Byte;
  inclusive·mul_ext·args.cn = &i;
  inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
  inclusive·mul_ext·args.gt_address_n = index_gt_n;
  continue inclusive·mul_ext;

  SQ·def(mul_ext·nominal){
    if( i > TM2x·n(tm2x) ) continue index_gt_n;
    *pt = (void *)(TM2x·0_pt(tm2x) + i);
    SQ·end;
  }

  SQ·end;
}



SQ·def(pop){
   TM2x·Tape *tm2x                = Args.TM2x·pop.tm2x;           
   address_t element_n_Byte  = Args.TM2x·pop.element_n_Byte; 
   SequencePtr nominal      = Args.TM2x·pop.nominal;        
   SequencePtr pop_last     = Args.TM2x·pop.pop_last;       
   SequencePtr alloc_fail   = Args.TM2x·pop.alloc_fail;     
} Args.TM2x·pop.







SQ·def(push_bytes){
  TM2x·Tape *tm2x              = TM2x·push_bytes.args.tm2x;           
  void *source_pt         = TM2x·push_bytes.args.source_pt;      
  address_t source_n = TM2x·push_bytes.args.source_n;  
  SequencePtr nominal    = TM2x·push_bytes.args.nominal;        
  SequencePtr alloc_fail = TM2x·push_bytes.args.alloc_fail;     
}








Args.TM2x·push_elements.{
  TM2x·Tape *tm2x                = Args.TM2x·push_elements.tm2x;
  void *base_pt             = Args.TM2x·push_elements.base_pt;
  address_t n_Element       = Args.TM2x·push_elements.n_Element;
  address_t element_n_Byte  = Args.TM2x·push_elements.element_n_Byte;
  SequencePtr nominal      = Args.TM2x·push_elements.nominal;
  SequencePtr alloc_fail   = Args.TM2x·push_elements.alloc_fail;
  SequencePtr index_gt_n    = Args.TM2x·push_elements.index_gt_n;
 }

  SQ·def(TM2x·push){
    TM2x·Tape *tm2x                 = Args.TM2x·push.tm2x;
    void *element_base_pt      = Args.TM2x·push.element_base_pt;
    address_t element_n_Byte   = Args.TM2x·push.element_n_Byte;
    SequencePtr nominal       = Args.TM2x·push.nominal;
    SequencePtr alloc_fail    = Args.TM2x·push.alloc_fail;
    SQ·end;
  }

Args.TM2x·push_TM2x.{
  TM2x·Tape *tm2x                = Args.TM2x·push_TM2x.tm2x;
  TM2x·Tape *tm2x_source         = Args.TM2x·push_TM2x.tm2x_source;
  SequencePtr nominal      = Args.TM2x·push_TM2x.nominal;
  SequencePtr alloc_fail   = Args.TM2x·push_TM2x.alloc_fail;
}

SQ·def(read_pop){
  TM2x·Tape *tm2x                 = Args.TM2x·read_pop.TM2x·Tape *tm2x;            
  void *dst_element_pt       = Args.TM2x·read_pop.void *dst_element_pt;  
  address_t element_n_Byte   = Args.TM2x·read_pop.address_t element_n_Byte;
  SequencePtr nominal       = Args.TM2x·read_pop.SequencePtr nominal;   
  SequencePtr pop_last      = Args.TM2x·read_pop.SequencePtr pop_last;  
  SequencePtr alloc_fail    = Args.TM2x·read_pop.SequencePtr alloc_fail;
  SQ·end;
}



/*
  Dynamic allocation of the TM2x·Tape header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#ifdef TM2x·TEST
  extern address_t TM2x·Test·allocation_n;
#endif

extern address_t TM2x·alloc_array_count;

SQ·def(resize_bytes){
  // shorten the arg names, give the optimizer something more to do
  TM2x·Tape *tm2x = Args.TM2x·resize_bytes.tm2x;
  address_t after_n = Args.TM2x·resize_bytes.after_n;
  SequencePtr nominal = Args.TM2x·resize_bytes.nominal;
  SequencePtr alloc_fail = Args.TM2x·resize_bytes.alloc_fail;

  address_t before_alloc_n = TM2x·alloc_n(tm2x->n);
  address_t after_alloc_n = TM2x·alloc_n(after_n);

  if( after_alloc_n == before_alloc_n ){
    tm2x->n = after_n;
    continue_via_trampoline nominal;
  }

  char *after_base_pt;

  #include "Args.CLib·mallocn.h"
  Args.CLib·mallocn.pt      = (void **)&after_base_pt;
  Args.CLib·mallocn.n       = after_alloc_n;
  Args.CLib·mallocn.nominal = &&malloc_nominal;
  Args.CLib·mallocn.fail    = &&malloc_fail; 
  #include "CLib·mallocn.h"
  continue CLib·mallocn;

  SQ·def(malloc_nominal){
    #ifdef TM2x·TEST
      TM2x·Test·allocation_n = after_alloc_n;
    #endif
    address_t copy_n = after_n < tm2x->n ? after_n : tm2x->n;
    memcpyn( after_base_pt ,tm2x->base_pt ,copy_n);
    free(tm2x->base_pt);
    tm2x->base_pt = after_base_pt;
    tm2x->n = after_n;
    continue *nominal;
    SQ·end
  }

  SQ·def(malloc_fail){
   continue *alloc_fail;
   SQ·end
  }

  SQ·end
}
/*
  Dynamic allocation of the TM2x·Tape header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/


SQ·def(F_PREFIX SequencePtr TM2x·resize_elements){
  TM2x·Tape *tm2x                = Args.TM2x·resize_elements.tm2x;
  address_t after_n_Element = Args.TM2x·resize_elements.after_n_Element;
  address_t element_n_Byte  = Args.TM2x·resize_elements.element_n_Byte;
  SequencePtr nominal      = Args.TM2x·resize_elements.nominal;
  SequencePtr alloc_fail   = Args.TM2x·resize_elements.alloc_fail;
  SequencePtr index_gt_n    = Args.TM2x·resize_elements.index_gt_n;

  address_t after_n;
  #include "inclusive·mul_ext·args.h"
  inclusive·mul_ext·args.an = after_n_Element;
  inclusive·mul_ext·args.bn = element_n_Byte;
  inclusive·mul_ext·args.cn = &after_n;
  inclusive·mul_ext·args.nominal = &&mul_ext·nominal;
  inclusive·mul_ext·args.gt_address_n = index_gt_n;
  continue inclusive·mul_ext;

  SQ·def(mul_ext·nominal){
    resize_bytes·args.tm2x = tm2x;
    resize_bytes·args.after_n = after_n;
    resize_bytes·args.nominal = nominal;
    resize_bytes·args.alloc_fail = alloc_fail;
    contine_from TM2x·resize_bytes;
    SQ·end;
  }

  SQ·end;
}

/*

Copies a region stemming from src_pt to src_pt + n on to the 
dst tm2x starting from byte offset dst_i.

The only tm2x explicitly identified is the dst tm2x, so we say that
we are writing the dst tm2x.

*/
SQ·def(write_bytes){
          TM2x·Tape *dst               = Args.TM2x·write_bytes.dst          
     address_t  dst_i        = Args.TM2x·write_bytes.dst_i   
          void *src_pt            = Args.TM2x·write_bytes.src_pt       
     address_t  n            = Args.TM2x·write_bytes.n       
  SequencePtr  nominal          = Args.TM2x·write_bytes.nominal      
  SequencePtr  alloc_fail       = Args.TM2x·write_bytes.alloc_fail   
  SequencePtr  src_index_gt_n   = Args.TM2x·write_bytes.src_index_gt_n
  SequencePtr  dst_index_gt_n   = Args.TM2x·write_bytes.dst_index_gt_n
}

#endif

