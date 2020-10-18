// 'thread static' allocation class
address_t TM2x·alloc_array_count = 0;

/*--------------------------------------------------------------------------------

  Memory management. 

*/

  // allocate a TM2x·Tape header on the heap
  // See also the TM2x·alloc_Tape_static macro in TM2x.h 
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
    m_ress.allocation = (void **)lnk->ress->tm2x;
    m_lnks.nominal = lnk->lnks->nominal;
    m_lnks.fail = lnk->lnks->fail;

    SQ·continue_indirect(m_lnk);

  } SQ·end(TM2x·alloc_Tape_heap);

  // allocates data on the heap
  SQ·def(TM2x·alloc_array_bytes){
    TM2x·alloc_array_count++; // to assist with debugging
    TM2x·AllocArray·Lnk *lnk = (TM2x·AllocArray·Lnk *)SQ·lnk;

    lnk->args->tm2x->n = *lnk->args->n;

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
      m_ress.allocation = (void **)&lnk->args->tm2x->base_pt;
      m_lnks.nominal = lnk->lnks->nominal;
      m_lnks.fail = lnk->lnks->alloc_fail;

    SQ·continue_indirect(m_lnk);

  } SQ·end(TM2x·alloc_array_bytes);

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
      SQ·make_Lnk(alloc_array_bytes ,TM2x·AllocArray ,&&TM2x·alloc_array_bytes);

      scale_ext_lnks = (Inclusive·3opLL·Lnks)
        { .nominal = AS(alloc_array_bytes_lnk ,SQ·Lnk)
          ,.gt_address_t_n = lnk->lnks->index_gt_n
        };

      alloc_array_bytes_lnks = (TM2x·AllocArray·Lnks)
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

      alloc_array_bytes_args.tm2x = lnk->args->tm2x;
      alloc_array_bytes_args.n = &n;

    SQ·continue_indirect(scale_ext_lnk);

  } SQ·end(TM2x·alloc_array_elements);

  // TM2x·Tape header may be constructed again and reused
  SQ·def(TM2x·dealloc_array){
    TM2x·alloc_array_count--; // to assist with debugging
    TM2x·DeallocArray·Lnk *lnk = (TM2x·DeallocArray·Lnk *)SQ·lnk;
    free(lnk->args->tm2x->base_pt);
    SQ·continue_indirect(lnk->lnks->nominal);  
  } SQ·end(TM2x·dealloc_array);

  // we are to deallocate the header from the heap
  SQ·def(TM2x·dealloc_Tape_heap){
    TM2x·DeallocTapeHeap·Lnk *lnk = (TM2x·DeallocTapeHeap·Lnk *)SQ·lnk;
    free(lnk->args->tm2x);
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(TM2x·dealloc_Tape_heap);


/*--------------------------------------------------------------------------------
 copying data

    If we copied as much as possible, then took the overflow upon hitting a bound, we
    would end up redoing the copy if the array expansion reallocates the array into a
    bigger heap block.  This due to 'resize', even by a small amount, possibly allocating
    a new array.

    With this implementation we do no copy until we see that the copy will fit.  If it
    does not fit we take the overflow continuation.

    In order to drop an area, first allocate a new destination tape that is smaller by the
    number of elements dropped.  Then copy the contiguous bytes up to the area to be 
    dropped, then copy the bytes after the area to be dropped. Then deallocate the 
    source machine.

    Analogously, to insert bytes, create a new destination machine and then do piecewise
    contiguous copies as for delete.

*/
  // copy_header will often be followed by the deallocation of the src tape header.  The
  // source destination nomenclature here is local, in the bigger picture the roles are
  // often the opposite.
  SQ·def(TM2x·copy_header){
    // some aliases
    TM2x·CopyTape·Lnk *lnk = (TM2x·CopyTape·Lnk *)SQ·lnk;
    TM2x·Tape *src = lnk->args->src;
    TM2x·Tape *dst = lnk->args->dst;

    dst->base_pt = src->base_pt;
    dst->n = src->n;
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(TM2x·copy_header);

  SQ·def(TM2x·copy_contiguous_bytes){
    // some aliases
    //
      TM2x·CopyContiguous·Lnk *lnk = (TM2x·CopyContiguous·Lnk *)SQ·lnk;
      TM2x·Tape *src = lnk->args->src;
      TM2x·Tape *dst = lnk->args->dst;
      address_t src_0 = *lnk->args->src_0;
      address_t dst_0 = *lnk->args->dst_0;
      address_t n = *lnk->args->n;
    if( 
       TM2x·n(src) < n
       ||
       TM2x·n(src) - n < src_0
        ){
      SQ·continue_indirect(lnk->lnks->src_index_gt_n);
    }
    if( 
       TM2x·n(dst) < n
       ||
       TM2x·n(dst) - n < dst_0
        ){
      SQ·continue_indirect(lnk->lnks->dst_index_gt_n);
    }
    memcpyn(TM2x·0_pt(dst) + dst_0, TM2x·0_pt(src) + src_0, n);
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(TM2x·copy_contiguous_bytes);


  SQ·def(TM2x·copy_contiguous_elements){
    TM2x·CopyContiguousElements·Lnk *lnk = (TM2x·CopyContiguousElements·Lnk *)SQ·lnk;

    // ----------------------------------------
    // local result tableau
    //
      address_t src_0;  
      address_t dst_0;  
      address_t ext_n;  

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(scale_src ,Inclusive·3opLL ,&&Inclusive·mul_idx);
      SQ·make_Lnk(scale_dst ,Inclusive·3opLL ,&&Inclusive·mul_idx);
      SQ·make_Lnk(scale_ext ,Inclusive·3opLL ,&&Inclusive·mul_ext);
      SQ·make_Lnk(copy_contiguous_bytes ,TM2x·CopyContiguous ,&&TM2x·copy_contiguous_bytes);

      scale_src_lnks = (Inclusive·3opLL·Lnks)
        {  .nominal = AS(scale_dst_lnk ,SQ·Lnk)
          ,.gt_address_t_n = lnk->lnks->src_index_gt_n
        };

      scale_dst_lnks = (Inclusive·3opLL·Lnks)
        {  .nominal = AS(scale_ext_lnk ,SQ·Lnk)
          ,.gt_address_t_n = lnk->lnks->dst_index_gt_n
        };

      scale_ext_lnks = (Inclusive·3opLL·Lnks)
        {  .nominal = AS(copy_contiguous_bytes_lnk ,SQ·Lnk)
          ,.gt_address_t_n = lnk->lnks->src_index_gt_n
        };

      copy_contiguous_bytes_lnks = (TM2x·CopyContiguous·Lnks)
        {  .nominal = lnk->lnks->nominal
          ,.src_index_gt_n = lnk->lnks->src_index_gt_n
          ,.dst_index_gt_n = lnk->lnks->dst_index_gt_n
        };

    // ----------------------------------------
    // sequence results point into the tableau
    //
      scale_src_ress.r = &src_0;
      scale_dst_ress.r = &dst_0;
      scale_ext_ress.r = &ext_n;

    // ----------------------------------------
    // seqeuence args point into this tableau or the parent tableau
    //
      scale_src_args = (Inclusive·3opLL·Args)
        {  .a_0 = lnk->args->src_element_0
          ,.a_1 = lnk->args->element_n_Byte
        };

      scale_dst_args = (Inclusive·3opLL·Args)
        {  .a_0 = lnk->args->dst_element_0
          ,.a_1 = lnk->args->element_n_Byte
        };

      scale_ext_args = (Inclusive·3opLL·Args)
        {  .a_0 = lnk->args->n_Element
          ,.a_1 = lnk->args->element_n_Byte
        };

      copy_contiguous_bytes_args  = (TM2x·CopyContiguous·Args)
        {  .src        = lnk->args->src
          ,.src_0 = &src_0
          ,.dst        = lnk->args->dst
          ,.dst_0 = &dst_0
          ,.n     = &ext_n
        };

    SQ·continue_indirect(scale_src_lnk);

  } SQ·end(TM2x·copy_contiguous_elements);

/*--------------------------------------------------------------------------------
 */


#if 0

  SQ·def(TM2x·resize){
    TM2x·Resize·Lnk *lnk = (TM2x·Resize·Lnk *)SQ·lnk;
    
    address_t alloc_n = TM2x·alloc_n(lnk->tape->n);
    address_t resized_alloc_n = TM2x·alloc_n(lnk->args->n);
    if( alloc_n == resized_alloc_n ) SQ·continue_indirect(lnk->lnks->nominal);
      
    // rtab

    SQ·continue_indirect(alloc_header_lnk);

    SQ·def(pt1){

      uint i = 0;
      pt1·lp0:{
        
        

        if(i == n) goto pt1·lp0_end;
        i++;
        goto pt1·lp0;

      } pt1·lp0_end;

    }SQ·end(pt1);

    

    
    
    


    memcpyn(TM2x·0_pt(dst) + dst_0, TM2x·0_pt(src) + src_0, n);
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(TM2x·resize);




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

