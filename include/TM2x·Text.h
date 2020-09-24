// 'thread static' allocation class
address_t TM2x·constructed_count = 0;

/*--------------------------------------------------------------------------------

  Memory management. See also the TM2x·alloc_static macro in TM2x.h 

*/

  // allocate a TM2x header on the heap
  SQ·def(TM2x·alloc_heap){
    TM2x·AllocHeap·Lnk *lnk = (TM2x·AllocHeap·Lnk *)SQ·lnk;

    CLib·Mallocn·Args m_args;
    CLib·Mallocn·Ress m_ress;
    CLib·Mallocn·Lnks m_lnks;
    CLib·Mallocn·Lnk m_lnk;
    m_lnk.args = &m_args;
    m_lnk.ress = &m_ress;
    m_lnk.lnks = &m_lnks;
    m_lnk.sequence = &&CLib·mallocn;

    address_t n = byte_n_of(TM2x); // stack base allocated, so we can safely use its address
    m_args.n  = &n;
    m_ress.allocation = (void **)lnk->ress->tm2x;
    m_lnks.nominal = lnk->lnks->nominal;
    m_lnks.fail = lnk->lnks->fail;

    SQ·continue_indirect(m_lnk);

  } SQ·end(TM2x·alloc_heap);

  // allocates data on the heap
  SQ·def(TM2x·construct_bytes){
    TM2x·constructed_count++; // to assist with debugging
    TM2x·ConstructBytes·Lnk *lnk = (TM2x·ConstructBytes·Lnk *)SQ·lnk;

    lnk->args->tm2x->byte_n = *lnk->args->byte_n;

    // local result tableau (stack base allocated, like everything else)
    //
      address_t alloc_byte_n = power_2_extent_w_lower_bound(*lnk->args->byte_n);

      CLib·Mallocn·Args m_args;
      CLib·Mallocn·Ress m_ress;
      CLib·Mallocn·Lnks m_lnks;
      CLib·Mallocn·Lnk m_lnk;
      m_lnk.args = &m_args;
      m_lnk.ress = &m_ress;
      m_lnk.lnks = &m_lnks;
      m_lnk.sequence = &&CLib·mallocn;

      m_args.n  = &alloc_byte_n;
      m_ress.allocation = (void **)&lnk->args->tm2x->base_pt;
      m_lnks.nominal = lnk->lnks->nominal;
      m_lnks.fail = lnk->lnks->alloc_fail;

    SQ·continue_indirect(m_lnk);

  } SQ·end(TM2x·construct_bytes);

  // TM2x header may be constructed again and reused
  SQ·def(TM2x·destruct){
    TM2x·constructed_count--; // to assist with debugging
    TM2x·Destruct·Lnk *lnk = (TM2x·Destruct·Lnk *)SQ·lnk;
    free(lnk->args->tm2x->base_pt);
    SQ·continue_indirect(lnk->lnks->nominal);  
  } SQ·end(TM2x·destruct);

  // we are to deallocate the header from the heap
  SQ·def(TM2x·dealloc_heap){
    TM2x·DeallocHeap·Lnk *lnk = (TM2x·DeallocHeap·Lnk *)SQ·lnk;
    free(lnk->args->tm2x);
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(TM2x·dealloc_heap);


  // TM2x0
  SQ·def(TM2x·construct_elements){
    TM2x·ConstructElements·Lnk *lnk = (TM2x·ConstructElements·Lnk *)SQ·lnk;

    // local links
    //
      Inclusive·3opLL·Args m_args;
      Inclusive·3opLL·Ress m_ress;
      Inclusive·3opLL·Lnks m_lnks;
      Inclusive·3opLL·Lnk m_lnk;
      m_lnk.args = &m_args;
      m_lnk.ress = &m_ress;
      m_lnk.lnks = &m_lnks;
      m_lnk.sequence = &&Inclusive·mul_ei_bi;

      TM2x·ConstructBytes·Args cb_args;
      TM2x·ConstructBytes·Ress cb_ress;
      TM2x·ConstructBytes·Lnks cb_lnks;
      TM2x·ConstructBytes·Lnk cb_lnk;
      cb_lnk.args = &cb_args;
      cb_lnk.ress = &cb_ress;
      cb_lnk.lnks = &cb_lnks;
      cb_lnk.sequence = &&TM2x·construct_bytes;

      m_lnks.nominal = AS(cb_lnk ,SQ·Lnk);
      m_lnks.gt_address_t_n = lnk->lnks->index_gt_n;

      cb_lnks.nominal = lnk->lnks->nominal;
      cb_lnks.alloc_fail = lnk->lnks->alloc_fail;

    // local data
    //
      address_t byte_n;

      m_args.a_0 = lnk->args->element_n;
      m_args.a_1 = lnk->args->element_byte_n;
      m_ress.r = &byte_n;

      cb_args.tm2x = lnk->args->tm2x;
      cb_args.byte_n = &byte_n;

    SQ·continue_indirect(m_lnk);

  } SQ·end(TM2x·construct_elements);

#if 0


//--------------------------------------------------------------------------------
// copying data
//
  SQ·def(TM2x·copy_bytes){
    TM2x·CopyBytes·Lnk *lnk = (TM2x·CopyBytes·Lnk *)SQ·lnk;

    tm2x *src = lnk->args->src;
    tm2x *dst = lnk->args->dst;

    address_t src_byte_0 = *lnk->args->src_byte_0;
    address_t dst_byte_0 = *lnk->args->dst_byte_0;

    address_t byte_n = *lnk->args->byte_n;

    if( 
       TM2x·byte_n(src) < byte_n
       ||
       TM2x·byte_n(src) - byte_n < src_byte_0
        )
      continue_indirect(lnk->lnks->src_index_gt_n);

    if( 
       TM2x·byte_n(dst) < byte_n
       ||
       TM2x·byte_n(dst) - byte_n < dst_byte_0
        )
      continue_indirect(lnk->lnks->dst_index_gt_n);

    memcpyn(TM2x·byte_0_pt(dst) + dst_byte_0, TM2x·byte_0_pt(src) + src_byte_0, byte_n);

  } 





//--------------------------------------------------------------------------------
// copy elements
//

  struct {
    Inclusive·3opLL·Args mul_ib_0;
    Inclusive·3opLL·Args mul_ei_bi_0;
    Inclusive·3opLL·Args mul_ei_bi_1;
    TM2x·CopyBytes·Args copy_bytes_0;
  } TM2x·CopyElements·child_args;

  struct {
    Inclusive·3opLL·Cnxs mul_ib_0;
    Inclusive·3opLL·Cnxs mul_ei_bi_0;
    Inclusive·3opLL·Cnxs mul_ei_bi_1;
    TM2x·CopyBytes·Cnxs copy_bytes_0;
  } TM2x·CopyElements·child_cxs;

  #pragma push_macro("CA")
  #pragma push_macro("CC")
  #define CA CopyElements·child_args;
  #define CC CopyElements·child_cnxs;

    static void TM2x·CopyElements·dataflow_static(){
      CA.mul_ib_0.rpt    = &CA.copy_bytes_0.byte_n;// scales element_n to byte_n
      CA.mul_ei_bi_0.rpt = &CA.copy_bytes_0.src_byte_i;// scale src element index to src byte index
      CA.mul_ei_bi_1.rpt = &CA.copy_bytes_0.dst_byte_i;// scale dst element index to dst byte index
    }
    CopyElements·dataflow_static();

    static void TM2x·CopyElements·connect_static(){ 
      CC.mul_ib_0.nominal   = init_cnx( Inclusive ,mul_ei_bi_0 );
      CC.mul_ei_bi_0.nominal= init_cnx( Inclusive ,mul_ei_bi_1 );
    }
    CopyElements·connect_static();

    static inline TM2x·CopyElements·connect_finish(){
         CC.mul_ib_0.gt_address_t_n = ((TM2x·CopyElements·Cnxs *)SQ·cnxs)->src_index_gt_n;
      CC.mul_ei_bi_0.gt_address_t_n = ((TM2x·CopyElements·Cnxs *)SQ·cnxs)->src_index_gt_n;
      CC.mul_ei_bi_1.gt_address_t_n = ((TM2x·CopyElements·Cnxs *)SQ·cnxs)->dst_index_gt_n;
      CC.mul_ei_bi_1.nominal        = ((TM2x·CopyElements·Cnxs *)SQ·cnxs)->nominal;
    } SQ·end(TM2x·CopyElements·connect_finish);

    SQ·def(TM2x·copy_elements){
      TM2x·CopyElements·connect_finish();
      SQ·args = (SQ·Args *) &CA.mul_ib_0;
      SQ·cnxs = (SQ·Cnxs *) &CC.mul_ib_0;
      continue(Inclusive·mul_ib);
    } SQ·end(TM2x·copy_elements);

  #pragma pop_macro("CC")
  #pragma pop_macro("CA")

#endif

#if 0


/*
Copy elements at index of the given tm2x, to the location specified by dst_element_pt.

Set element_n to 0 to read the one element from location specified by the given index.

Our attention is focused on the tm2x, so we call this a 'read' operation.

*/

SQ·def(index·read){
  TM2x *tm2x               = Args.TM2x·index·read.tm2x;              
  address_t index          = Args.TM2x·index·read.index;         
  address_t element_n      = Args.TM2x·index·read.element_byte_n;
  address_t element_byte_n = Args.TM2x·index·read.element_byte_n;
  void *dst_element_pt     = Args.TM2x·index·read.dst_element_pt;    
  SequencePtr nominal    = Args.TM2x·index·read.nominal;
  SequencePtr index_gt_n = Args.TM2x·index·read.index_gt_n;

  // byte_n relative to element_0_pt.
  address_t region_byte_n;
  inclusive·mul_ib·args.an = element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &region_byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue inclusive·mul_ib;

  SQ·def(mul_ib·nominal){
    address_t byte_i;
    inclusive·mul_ib·args.an = index;
    inclusive·mul_ib·args.bn = element_byte_n;
    inclusive·mul_ib·args.cn = &byte_i
    inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
    inclusive·mul_ib·args.gt_address_n = index_gt_n;
    continue inclusive·mul_ib;


    void *src_element_pt;
    Args.TM2x·index·to_pt.tm2x           = tm2x;
    Args.TM2x·index·to_pt.index          = index;     
    Args.TM2x·index·to_pt.element_byte_n = element_byte_n;
    Args.TM2x·index·to_pt.pt             = &src_element_pt;              
    Args.TM2x·index·to_pt.nominal        = &&index_nominal;        
    Args.TM2x·index·to_pt.index_gt_n     = index_gt_n;
    continue TM2x·index·to_pt;
  }

  SQ·def(index_nominal){


    SQ·def(mul_ib·nominal){
      if( 

    }


    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
    SQ·end;
  }

  SQ·end;
}

INLINE_PREFIX ContinuationPtr index·to_pt{
  TM2x *tm2x               = Args.TM2x·index·to_pt.tm2x;
  address_t index          = Args.TM2x·index·to_pt.index;
  address_t element_byte_n = Args.TM2x·index·to_pt.element_byte_n;
  void **pt                = Args.TM2x·index·to_pt.pt;
  SequencePtr nominal     = Args.TM2x·index·to_pt.nominal;
  SequencePtr index_gt_n = Args.TM2x·index·to_pt.index_gt_n;

  address_t byte_i;
  inclusive·mul_ib·args.an = index;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_i;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue inclusive·mul_ib;

  SQ·def(mul_ib·nominal){
    if( byte_i > TM2x·byte_n(tm2x) ) continue index_gt_n;
    *pt = (void *)(TM2x·byte_0_pt(tm2x) + byte_i);
    SQ·end;
  }

  SQ·end;
}






SQ·def(pop){
   TM2x *tm2x                = Args.TM2x·pop.tm2x;           
   address_t element_byte_n  = Args.TM2x·pop.element_byte_n; 
   SequencePtr nominal      = Args.TM2x·pop.nominal;        
   SequencePtr pop_last     = Args.TM2x·pop.pop_last;       
   SequencePtr alloc_fail   = Args.TM2x·pop.alloc_fail;     
} Args.TM2x·pop.







SQ·def(push_bytes){
  TM2x *tm2x              = TM2x·push_bytes.args.tm2x;           
  void *source_pt         = TM2x·push_bytes.args.source_pt;      
  address_t source_byte_n = TM2x·push_bytes.args.source_byte_n;  
  SequencePtr nominal    = TM2x·push_bytes.args.nominal;        
  SequencePtr alloc_fail = TM2x·push_bytes.args.alloc_fail;     
}








Args.TM2x·push_elements.{
  TM2x *tm2x                = Args.TM2x·push_elements.tm2x;
  void *base_pt             = Args.TM2x·push_elements.base_pt;
  address_t element_n       = Args.TM2x·push_elements.element_n;
  address_t element_byte_n  = Args.TM2x·push_elements.element_byte_n;
  SequencePtr nominal      = Args.TM2x·push_elements.nominal;
  SequencePtr alloc_fail   = Args.TM2x·push_elements.alloc_fail;
  SequencePtr index_gt_n    = Args.TM2x·push_elements.index_gt_n;
 }

  SQ·def(TM2x·push){
    TM2x *tm2x                 = Args.TM2x·push.tm2x;
    void *element_base_pt      = Args.TM2x·push.element_base_pt;
    address_t element_byte_n   = Args.TM2x·push.element_byte_n;
    SequencePtr nominal       = Args.TM2x·push.nominal;
    SequencePtr alloc_fail    = Args.TM2x·push.alloc_fail;
    SQ·end;
  }

Args.TM2x·push_TM2x.{
  TM2x *tm2x                = Args.TM2x·push_TM2x.tm2x;
  TM2x *tm2x_source         = Args.TM2x·push_TM2x.tm2x_source;
  SequencePtr nominal      = Args.TM2x·push_TM2x.nominal;
  SequencePtr alloc_fail   = Args.TM2x·push_TM2x.alloc_fail;
}

SQ·def(read_pop){
  TM2x *tm2x                 = Args.TM2x·read_pop.TM2x *tm2x;            
  void *dst_element_pt       = Args.TM2x·read_pop.void *dst_element_pt;  
  address_t element_byte_n   = Args.TM2x·read_pop.address_t element_byte_n;
  SequencePtr nominal       = Args.TM2x·read_pop.SequencePtr nominal;   
  SequencePtr pop_last      = Args.TM2x·read_pop.SequencePtr pop_last;  
  SequencePtr alloc_fail    = Args.TM2x·read_pop.SequencePtr alloc_fail;
  SQ·end;
}



/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#ifdef TM2x·TEST
  extern address_t TM2x·Test·allocation_n;
#endif

extern address_t TM2x·constructed_count;

SQ·def(resize_bytes){
  // shorten the arg names, give the optimizer something more to do
  TM2x *tm2x = Args.TM2x·resize_bytes.tm2x;
  address_t after_byte_n = Args.TM2x·resize_bytes.after_byte_n;
  SequencePtr nominal = Args.TM2x·resize_bytes.nominal;
  SequencePtr alloc_fail = Args.TM2x·resize_bytes.alloc_fail;

  address_t before_alloc_n = power_2_extent_w_lower_bound(tm2x->byte_n);
  address_t after_alloc_n = power_2_extent_w_lower_bound(after_byte_n);

  if( after_alloc_n == before_alloc_n ){
    tm2x->byte_n = after_byte_n;
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
    address_t copy_n = after_byte_n < tm2x->byte_n ? after_byte_n : tm2x->byte_n;
    memcpyn( after_base_pt ,tm2x->base_pt ,copy_n);
    free(tm2x->base_pt);
    tm2x->base_pt = after_base_pt;
    tm2x->byte_n = after_byte_n;
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
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/


SQ·def(F_PREFIX SequencePtr TM2x·resize_elements){
  TM2x *tm2x                = Args.TM2x·resize_elements.tm2x;
  address_t after_element_n = Args.TM2x·resize_elements.after_element_n;
  address_t element_byte_n  = Args.TM2x·resize_elements.element_byte_n;
  SequencePtr nominal      = Args.TM2x·resize_elements.nominal;
  SequencePtr alloc_fail   = Args.TM2x·resize_elements.alloc_fail;
  SequencePtr index_gt_n    = Args.TM2x·resize_elements.index_gt_n;

  address_t after_byte_n;
  #include "inclusive·mul_ib·args.h"
  inclusive·mul_ib·args.an = after_element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &after_byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue inclusive·mul_ib;

  SQ·def(mul_ib·nominal){
    resize_bytes·args.tm2x = tm2x;
    resize_bytes·args.after_byte_n = after_byte_n;
    resize_bytes·args.nominal = nominal;
    resize_bytes·args.alloc_fail = alloc_fail;
    contine_from TM2x·resize_bytes;
    SQ·end;
  }

  SQ·end;
}

/*

Copies a region stemming from src_pt to src_pt + byte_n on to the 
dst tm2x starting from byte offset dst_byte_i.

The only tm2x explicitly identified is the dst tm2x, so we say that
we are writing the dst tm2x.

*/
SQ·def(write_bytes){
          TM2x *dst               = Args.TM2x·write_bytes.dst          
     address_t  dst_byte_i        = Args.TM2x·write_bytes.dst_byte_i   
          void *src_pt            = Args.TM2x·write_bytes.src_pt       
     address_t  byte_n            = Args.TM2x·write_bytes.byte_n       
  SequencePtr  nominal          = Args.TM2x·write_bytes.nominal      
  SequencePtr  alloc_fail       = Args.TM2x·write_bytes.alloc_fail   
  SequencePtr  src_index_gt_n   = Args.TM2x·write_bytes.src_index_gt_n
  SequencePtr  dst_index_gt_n   = Args.TM2x·write_bytes.dst_index_gt_n
}

#endif

