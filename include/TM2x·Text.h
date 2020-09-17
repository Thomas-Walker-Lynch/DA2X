// 'thread static' allocation class
address_t TM2x·constructed_count = 0;

#ifdef TM2x·TEST
  address_t TM2x·Test·allocation_n = 0;
#endif

/*--------------------------------------------------------------------------------

  Here alloc, construct, destruct, dealloc cycle

*/
  // see the TM2x·alloc_static macro in TM2x.h 
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
    m_ress.allocated_data = (void **)&lnk->ress->tm2x;
    m_lnks.nominal = lnk->lnks->nominal;
    m_lnks.fail = lnk->lnks->fail;

    SQ·continue_indirect(m_lnk);

  } SQ·end(TM2x·alloc_heap);

  // Given an exent in bytes, sets aside heap memory for the data.
  SQ·def(TM2x·construct_bytes){
    TM2x·constructed_count++; // to assist with debugging
    TM2x·ConstructBytes·Lnk *lnk = (TM2x·ConstructBytes·Lnk *)SQ·lnk;

    CLib·Mallocn·Args m_args;
    CLib·Mallocn·Ress m_ress;
    CLib·Mallocn·Lnks m_lnks;
    CLib·Mallocn·Lnk m_lnk;
    m_lnk.args = &m_args;
    m_lnk.ress = &m_ress;
    m_lnk.lnks = &m_lnks;
    m_lnk.sequence = &&CLib·mallocn;

    lnk->args->tm2x->byte_n = lnk->args->byte_n;

    m_args.n  = power_2_extent_w_lower_bound(lnk->args->byte_n);
    m_ress.allocated_data = (void **)&lnk->args->tm2x->base_pt;
    m_lnks.nominal = lnk->lnks->nominal;
    m_lnks.fail = lnk->lnks->alloc_fail;

    SQ·continue_indirect(m_lnk);

  } SQ·end(TM2x·construct_bytes);


  SQ·def(TM2x·destruct){
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

#if 0

  // Deallocation for dynamically allocated headers.
  // TM2x0
  SQ·def(TM2x·destruct_dealloc_heap){
    Sequence destruct ,dealloc;

    Sequence·swap();
    LC(lc ,TM2x·destruct_dealloc_heap ,0);

    CX(cx ,TM2x0 ,destruct_dealloc_heap);
    cx->tm2x = lc->tm2x;
    cx->nominal = lc->nominal;

    continue destruct;

    SQ·def(destruct){
      AR(ar ,TM2x·destruct ,0);
      ar->tm2x = lc->tm2x;
      ar->nominal = &&dealloc;
      continue TM2x·destruct(); // nc
      SQ·end;
    }

    SQ·def(dealloc){
      free(cx->tm2x);
      continue *cx->nominal; 
      SQ·end;
    }

  }SQ·end(TM2x·destruct_dealloc_heap); 


//----------------------------------------
//  Dynamic allocation of the TM2x header.  For static allocation use the AllocoStatic()
//  macro.  This does not allocate data for the array itself.
// nc
SQ·def(TM2x·alloc_heap){
  Sequence·swap();
  LC(lc ,TM2x·alloc_heap ,0);

  AR(ar ,CLib·mallocn ,0);
  ar->pt      = (void **)lc->tm2x;
  ar->n       = byte_n_of(TM2x);
  ar->nominal = lc->nominal;
  ar->fail    = lc->fail;
  continue CLib·mallocn();
} SQ·end(TM2x·alloc_heap);

//----------------------------------------
//  Construct an allocated array. 

// TM2x0
SQ·def(TM2x·construct_elements){
  Sequence scale ,construct_bytes;

  Sequence·swap();
  LC(lc ,TM2x·construct_elements ,0);

  CX(cx ,TM2x0 ,construct_elements);
  cx->tm2x = lc->tm2x;
  cx->nominal = lc->nominal;
  cx->alloc_fail = lc->alloc_fail;

  continue scale;

  SQ·def(scale){
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0 = lc->element_n;
    ar->a1 = lc->element_byte_n;
    ar->nominal = &&construct_bytes;
    ar->index_gt_n = lc->index_gt_n;
    continue Inclusive·mul_ib; // nc
    SQ·end;
  };

  SQ·def(construct_bytes){
    Sequence·swap();
    LC(lc ,Inclusive·3opLL  ,2);
    
    AR(ar ,TM2x·construct_bytes ,0);
    ar->tm2x       = cx->tm2x;
    ar->byte_n     = lc->byte_n;
    ar->nominal    = cx->nominal;
    ar->alloc_fail = cx->alloc_fail;
    continue TM2x·construct_bytes(&&nominal ,&&alloc_fail); // nc
    SQ·end;
  };

}  SQ·end(TM2x·construct_elements);

// TM2x0
SQ·def(TM2x·construct_write_bytes){
  Sequence construct ,write;
  Sequence·swap();
  LC(lc ,TM2x·construct_write_bytes ,0);

  CX(cx ,TM2x0 ,construct_write_bytes);
  cx->tm2x      = lc->tm2x;
  cx->source_pt = lc->source_pt;
  cx->byte_n    = lc->byte_n;
  cx->nominal   = lc->nominal;

  continue construct;

  SQ·def(construct){
    AR(ar ,TM2x·construct_bytes.tm2x ,0);
    ar->tm2x = lc->tm2x;
    ar->byte_n = lc->byte_n;
    ar->nominal = &&write;
    ar->alloc_fail = lc->fail;
    continue TM2x·construct_bytes; // nc
    SQ·end;
  }
  
  SQ·def(write){
    memcpyn(TM2x·byte_0_pt(cx->tm2x), cx->source_pt, cx->byte_n);
    continue *cx->nominal;
    SQ·end;
  }

} SQ·end(TM2x·construct_write_bytes);


// uses context TM2x1
// depends on: mul_ib ,construct_write_bytes
// dependency with context: construct_write_bytes
SQ·def(TM2x·construct_write_elements){
  Sequence scale ,construct_write_bytes;
  Sequence·swap();
  LC(lc ,TM2x·construct_write_elements ,0);

  CX(cx ,TM2x1 ,construct_write_elements);
  cx->tm2x      = lc->tm2x;
  cx->source_pt = lc->source_pt;
  cx->nominal   = lc->nominal;
  cx->fail      = lc->fail;

  continue scale;

  SQ·def(scale){
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0             = lc->element_n;
    ar->a1             = lc->element_byte_n;
    ar->rpt            = &cx->byte_n;
    ar->nominal        = &&construct_write_bytes;
    ar->gt_address_t_n = lc->index_gt_n;
    continue Inclusive·mul_ib;
    SQ·end;
  }

  SQ·def(construct_write_bytes){
    AR(ar ,TM2x·construct_write_bytes ,0);
    ar->tm2x      = cx->tm2x;
    ar->source_pt = cx->source_pt;
    ar->byte_n    = cx->byte_n;
    ar->nominal   = cx->nominal;
    ar->fail      = cx->fail;
    continue TM2x·construct_write_bytes;
    SQ·end;
  }

} SQ·end(TM2x·construct_write_elements);

//  Writes one element.
SQ·defTM2x·construct_write){
  Sequence nominal;
  Sequence·swap();
  LC(lc ,TM2x·construct_write ,0);

  AR(ar ,TM2x·construct_write_bytes ,0);
  ar->tm2x      = lc->tm2x;
  ar->source_pt = lc->element_pt;
  ar->byte_n    = lc->element_byte_n;
  ar->nominal   = lc->nominal;
  ar->fail      = lc->fail;
  continue TM2x·construct_write_bytes;
  
} SQ·end(TM2x·construct_write);

// construct and initialize tm2x from another TM
INLINE_PREFIX ContinuationPtr construct_write_TM2x{
  Sequence·swap();
  LC(lc  ,TM2x·construct_write_TM2x ,0);

  AR(ar ,TM2x·construct_write_bytes ,0);
  ar->tm2x      = lc->tm2x;
  ar->source_pt = TM2x·byte_0_pt(lc->tm2x_source);
  ar->byte_n    = TM2x·byte_n(lc->tm2x_source);
  ar->nominal   = lc->nominal;
  ar->fail      = lc->fail;
  continue TM2x·construct_write_bytes;

  SQ·end;
};

SQ·def(TM2x·copy_bytes){
  AR(ar  ,TM2x·copy_bytes ,0);

  if( 
     TM2x·byte_n(ar->src) < ar->byte_n
     ||
     TM2x·byte_n(ar->src) - ar->byte_n < ar->src_byte_i
      )
    continue ar->src_index_gt_n;

  if( 
     TM2x·byte_n(ar->dst) < ar->byte_n
     ||
     TM2x·byte_n(ar->dst) - ar->byte_n < ar->dst_byte_i
      )
    continue ar->dst_index_gt_n;
  
  memcpyn(TM2x·byte_0_pt(ar->dst) + ar->dst_byte_i, TM2x·byte_0_pt(ar->src) + ar->src_byte_i, ar->byte_n);

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

