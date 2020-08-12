/*
  This is not a traditional header, and can not be used as such.

  #include "TM2x·text.h" after the Args and Data unions.

  Provided that this is included into main or another function, the outer scope instances
  here, e.g. TM2·constructed_count, will be on the stack, and thus thread safe.

  Would be nice if we could give an inline option to conveyances.

*/
#include "TM2x.h"

// interfaces will be used for L2
/*
struct Text·TM2x{
  ConveyancePtr alloc_heap;
} Text·TM2x
={
  &&TM2x·alloc_heap
};
*/

// 'thread static' allocation class
address_t TM2x·constructed_count = 0;

#define MINIMUM_ALLOC_EXTENT 15
address_t power_2_extent_w_lower_bound(address_t byte_n){
  if( byte_n < MINIMUM_ALLOC_EXTENT) return MINIMUM_ALLOC_EXTENT;
  return power_2_extent(byte_n);
}

// no swap, uses only AR
TM2x·F_PREFIX ContinuationPtr TM2x·destruct(){
  AR(ar ,TM2x·destruct ,0);
  free(ar->tape->base_pt);
  TM2x·constructed_count--;
  leave_continue_from *ar->nominal;
  cend
}

// no swap, uses only AR
TM2x·F_PREFIX ContinuationPtr TM2x·dealloc_heap(){
  AR(ar ,TM2x·destruct ,0);
  free(ar->tape);
  leave_continue_from *ar->nominal;
  cend;
}

// Deallocation for dynamically allocated headers.
// swap, uses ar and lc
TM2x·F_PREFIX ContinuationPtr destruct_dealloc_heap(){
  Conveyance destruct ,dealloc;
  Conveyance·swap();
  LC(lc ,TM2x·dealloc_heap ,0);

  TM2x *cx_tape = lc->tape;
  ContinuationPtr cx_nominal = lc->nominal;

  continue_from destruct;

  destruct:{
    AR(ar ,TM2x·destruct ,1);
    ar->tape = lc->tape;
    ar->nominal = &&dealloc;
    continue_from *TM2x·destruct();
    cend;
  }

  dealloc:{
    free(cx_tape);
    leave_continue_from cx_nominal;
    cend;
  }

  cend;
}

//----------------------------------------
//  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic()
//  macro.  This does not allocate data for the array itself.
//  Ah too bad, the only reason context is here is to pop the context.
TM2x·F_PREFIX ContinuationPtr alloc_heap(){
  Conveyance·swap();
  LC(lc ,TM2x·alloc_heap ,0);

  ContinuationPtr cx_nominal = lc->nominal;
  ContinuationPtr cx_fail    = lc->fail;

  AR(ar ,CLib·mallocn ,0);
  ar->pt      = (void **)lc->tape;
  ar->n       = byte_n_of(TM2x);
  ar->nominal = &&nominal;
  ar->fail    = &&fail;
  continue_from *CLib·mallocn();

  nominal:{
    leave_continue_from cx_nominal;
    cend;
  }
  fail:{
    leave_continue_from cx_fail;
    cend;
  }

  cend;
}

//----------------------------------------
//  Construct an allocated array. 
//  Given the exent in bytes, sets aside heap memory for the data.
TM2x·F_PREFIX ContinuationPtr construct_bytes(){
  Conveyance·swap();
  LC(lc ,TM2x·construct_bytes ,1);
  TM2x·constructed_count++; // to assist with debugging
  lc->tape->byte_n = lc->byte_n;
  lc->alloc_byte_n = power_2_extent_w_lower_bound(lc->byte_n);

  ContinuationPtr cx_nominal = lc->nominal;
  ContinuationPtr cx_alloc_fail = lc->alloc_fail;

  AR(ar ,CLib·mallocn ,0);
  ar->pt      = (void **)&(lc->tape->base_pt);
  ar->n       = lc->alloc_byte_n;
  ar->nominal = &&nominal;
  ar->fail    = &&alloc_fail;
  continue_from CLib·mallocn;

  nominal:{
    leave_continue_from cx_nominal;
    cend;
  }
  alloc_fail:{
    leave_continue_from cx_alloc_fail;
    cend;
  }

  cend;
}

// uses context TM2x0
// depends on: construct_bytes
TM2x·F_PREFIX ContinuationPtr construct_elements
  (
   ContinuationPtr cx_nominal 
   ,ContinuationPtr cx_index_gt_n
   ,ContinuationPtr cx_alloc_fail
   ){
  Conveyance scale ,construct_bytes;
  Conveyance·swap();
  LC(lc ,TM2x·construct_elements ,1);

  tape = lc->tape;
  address_t byte_n;

  continue_from scale;

  scale:{
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0 = lc->element_n;
    ar->a1 = lc->element_byte_n;
    ar->rpt = &byte_n;
    continue_from Inclusive·mul_ib(&&construct_bytes ,&&index_gt_n);
    cend;
  };

  construct_bytes:{
    AR(ar ,TM2x·construct_bytes ,0);
    ar->tape       = tape;
    ar->byte_n     = byte_n;
    continue_from TM2x·construct_bytes(&&nominal ,&&alloc_fail);
    cend;
  };

  index_gt_n:{
    leave_continue_from cx->index_gt_n;
    cend;
  }

  nominal:{
    leave_continue_from cx_nominal;
    cend;
  }

  alloc_fail:{
    leave_continue_from cx_alloc_fail;
    cend;
  }
    

  cend;
}

// uses context TM2x0
// depends on: construct_bytes
construct_write_bytes(){
  Conveyance construct ,write;
  Conveyance·swap();
  LC(lc ,TM2x·construct_write_bytes ,0);

  CX(cx ,TM2x0 ,construct_write_bytes);
  cx->tape      = lc->tape;
  cx->source_pt = lc->source_pt;
  cx->byte_n    = lc->byte_n;
  cx->nominal   = lc->nominal;

  continue_from construct;

  construct:{
    AR(ar ,TM2x·construct_bytes.tape ,0);
    ar->tape = lc->tape;
    ar->byte_n = lc->byte_n;
    ar->nominal = &&write;
    ar->alloc_fail = lc->fail;
    continue_from TM2x·construct_bytes;
    cend;
  }
  
  write:{
    memcpyn(TM2x·byte_0_pt(cx->tape), cx->source_pt, cx->byte_n);
    continue_from *cx->nominal;
    cend;
  }

  cend;
}

// uses context TM2x1
// depends on: mul_ib ,construct_write_bytes
// dependency with context: construct_write_bytes
TM2x·F_PREFIX ContinuationPtr construct_write_elements(){
  Conveyance scale ,construct_write_bytes;
  Conveyance·swap();
  LC(lc ,TM2x·construct_write_elements ,0);

  CX(cx ,TM2x1 ,construct_write_elements);
  cx->tape      = lc->tape;
  cx->source_pt = lc->source_pt;
  cx->nominal   = lc->nominal;
  cx->fail      = lc->fail;

  continue_from scale;

  scale:{
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0             = lc->element_n;
    ar->a1             = lc->element_byte_n;
    ar->rpt            = &cx->byte_n;
    ar->nominal        = &&construct_write_bytes;
    ar->gt_address_t_n = lc->index_gt_n;
    continue_from Inclusive·mul_ib;
    cend;
  }

  construct_write_bytes:{
    AR(ar ,TM2x·construct_write_bytes ,0);
    ar->tape      = cx->tape;
    ar->source_pt = cx->source_pt;
    ar->byte_n    = cx->byte_n;
    ar->nominal   = cx->nominal;
    ar->fail      = cx->fail;
    continue_from TM2x·construct_write_bytes;
    cend;
  }

  cend;
}

//  Writes one element.
Args.TM2x·construct_write(){
  Conveyance nominal;
  Conveyance·swap();
  LC(lc ,TM2x·construct_write ,0);

  AR(ar ,TM2x·construct_write_bytes ,0);
  ar->tape      = lc->tape;
  ar->source_pt = lc->element_pt;
  ar->byte_n    = lc->element_byte_n;
  ar->nominal   = lc->nominal;
  ar->fail      = lc->fail;
  continue_from TM2x·construct_write_bytes;

  cend;
}

// construct and initialize tape from another TM
TM2x·F_PREFIX ContinuationPtr construct_write_TM2x{
  Conveyance·swap();
  LC(lc  ,TM2x·construct_write_TM2x ,0);

  AR(ar ,TM2x·construct_write_bytes ,0);
  ar->tape      = lc->tape;
  ar->source_pt = TM2x·byte_0_pt(lc->tape_source);
  ar->byte_n    = TM2x·byte_n(lc->tape_source);
  ar->nominal   = lc->nominal;
  ar->fail      = lc->fail;
  continue_from TM2x·construct_write_bytes;

  cend;
};

TM2x·F_PREFIX ContinuationPtr copy_bytes(){
  AR(ar  ,TM2x·copy_bytes ,0);

  if( 
     TM2x·byte_n(ar->src) < ar->byte_n
     ||
     TM2x·byte_n(ar->src) - ar->byte_n < ar->src_byte_i
      )
    continue_from ar->src_index_gt_n;

  if( 
     TM2x·byte_n(ar->dst) < ar->byte_n
     ||
     TM2x·byte_n(ar->dst) - ar->byte_n < ar->dst_byte_i
      )
    continue_from ar->dst_index_gt_n;
  
  memcpyn(TM2x·byte_0_pt(ar->dst) + ar->dst_byte_i, TM2x·byte_0_pt(ar->src) + ar->src_byte_i, ar->byte_n);

} 

TM2x·F_PREFIX ContinuationPtr copy_elements(){
  Conveyance nominal ,byte_n ,src_byte_i ,dst_byte_i ,copy_bytes;
  Conveyance·swap();
  AR(ar ,TM2x·construct_write_elements ,0);

  CX(cx ,TM2x0 ,construct_write_elements);
  cx->src            = ar->src;
  cx->src_element_i  = ar->src_element_i;
  cx->dst            = ar->dst;
  cx->dst_element_i  = ar->dst_element_i;
  cx->element_n      = ar->element_n ;
  cx->element_byte_n = ar->element_byte_n;
  cx->nominal        = ar->nominal;
  cx->src_index_gt_n = ar->src_index_gt_n;
  cx->dst_index_gt_n = ar->dst_index_gt_n;

  //cx->byte_n;
  //cx->src_byte_i;
  //cx->dst_byte_i;

  continue_from byte_n;

  byte_n:{
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0             = cx->element_n;
    ar->a1             = cx->element_byte_n;
    ar->rpt            = &cx->byte_n;
    ar->nominal        = &&src_byte_i;
    ar->gt_address_t_n = cx->src_index_gt_n;
    continue_from Inclusive·mul_ib;
  }

  src_byte_i:{
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0             = cx->src_element_i;
    ar->a1             = cx->element_byte_n;
    ar->rpt            = &cx->src_byte_i;
    ar->nominal        = &&dst_byte_i;
    ar->gt_address_t_n = cx->src_index_gt_n;
    continue_from Inclusive·mul_ei_bi;
    cend;
  }

  dst_byte_i:{
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0             = cx->dst_element_i;
    ar->a1             = cx->element_byte_n;
    ar->rpt            = &cx->dst_byte_i;
    ar->nominal        = &&copy_bytes;
    ar->gt_address_t_n = cx->dst_index_gt_n;
    continue_from Inclusive·mul_ei_bi;
    cend;
  }

  copy_bytes:{
    AR(ar ,TM2x·construct_copy_bytes ,0);
    ar->src             = cx->src;
    ar->src_byte_i      = cx->src_byte_i;
    ar->dst             = cx->dst;
    ar->dst_byte_i      = cx->dst_byte_i;
    ar->byte_n          = cx->byte_n;
    ar->nominal         = cx->nominal;
    ar->src_index_gt_n  = cx->src_index_gt_n;
    ar->dst_index_gt_n  = cx->dst_index_gt_n;
    continue_from TM2x·copy_bytes;
    cend;
  }

  cend;
}

#if 0


/*
Copy elements at index of the given tape, to the location specified by dst_element_pt.

Set element_n to 0 to read the one element from location specified by the given index.

Our attention is focused on the tape, so we call this a 'read' operation.

*/

TM2x·F_PREFIX ContinuationPtr index·read(){
  TM2x *tape               = Args.TM2x·index·read.tape;              
  address_t index          = Args.TM2x·index·read.index;         
  address_t element_n      = Args.TM2x·index·read.element_byte_n;
  address_t element_byte_n = Args.TM2x·index·read.element_byte_n;
  void *dst_element_pt     = Args.TM2x·index·read.dst_element_pt;    
  ConveyancePtr nominal    = Args.TM2x·index·read.nominal;
  ConveyancePtr index_gt_n = Args.TM2x·index·read.index_gt_n;

  // byte_n relative to element_0_pt.
  address_t region_byte_n;
  inclusive·mul_ib·args.an = element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &region_byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    address_t byte_i;
    inclusive·mul_ib·args.an = index;
    inclusive·mul_ib·args.bn = element_byte_n;
    inclusive·mul_ib·args.cn = &byte_i
    inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
    inclusive·mul_ib·args.gt_address_n = index_gt_n;
    continue_from inclusive·mul_ib;


    void *src_element_pt;
    Args.TM2x·index·to_pt.tape           = tape;
    Args.TM2x·index·to_pt.index          = index;     
    Args.TM2x·index·to_pt.element_byte_n = element_byte_n;
    Args.TM2x·index·to_pt.pt             = &src_element_pt;              
    Args.TM2x·index·to_pt.nominal        = &&index_nominal;        
    Args.TM2x·index·to_pt.index_gt_n     = index_gt_n;
    continue_from TM2x·index·to_pt;
  }

  index_nominal:{


    mul_ib·nominal:{
      if( 

    }


    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
    cend;
  }

  cend;
}

TM2x·F_PREFIX ContinuationPtr index·to_pt{
  TM2x *tape               = Args.TM2x·index·to_pt.tape;
  address_t index          = Args.TM2x·index·to_pt.index;
  address_t element_byte_n = Args.TM2x·index·to_pt.element_byte_n;
  void **pt                = Args.TM2x·index·to_pt.pt;
  ConveyancePtr nominal     = Args.TM2x·index·to_pt.nominal;
  ConveyancePtr index_gt_n = Args.TM2x·index·to_pt.index_gt_n;

  address_t byte_i;
  inclusive·mul_ib·args.an = index;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_i;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    if( byte_i > TM2x·byte_n(tape) ) continue_from index_gt_n;
    *pt = (void *)(TM2x·byte_0_pt(tape) + byte_i);
    cend;
  }

  cend;
}






TM2x·F_PREFIX ContinuationPtr pop(){
   TM2x *tape                = Args.TM2x·pop.tape;           
   address_t element_byte_n  = Args.TM2x·pop.element_byte_n; 
   ConveyancePtr nominal      = Args.TM2x·pop.nominal;        
   ConveyancePtr pop_last     = Args.TM2x·pop.pop_last;       
   ConveyancePtr alloc_fail   = Args.TM2x·pop.alloc_fail;     
} Args.TM2x·pop.







TM2x·F_PREFIX ContinuationPtr push_bytes(){
  TM2x *tape              = TM2x·push_bytes.args.tape;           
  void *source_pt         = TM2x·push_bytes.args.source_pt;      
  address_t source_byte_n = TM2x·push_bytes.args.source_byte_n;  
  ConveyancePtr nominal    = TM2x·push_bytes.args.nominal;        
  ConveyancePtr alloc_fail = TM2x·push_bytes.args.alloc_fail;     
}








Args.TM2x·push_elements.{
  TM2x *tape                = Args.TM2x·push_elements.tape;
  void *base_pt             = Args.TM2x·push_elements.base_pt;
  address_t element_n       = Args.TM2x·push_elements.element_n;
  address_t element_byte_n  = Args.TM2x·push_elements.element_byte_n;
  ConveyancePtr nominal      = Args.TM2x·push_elements.nominal;
  ConveyancePtr alloc_fail   = Args.TM2x·push_elements.alloc_fail;
  ConveyancePtr index_gt_n    = Args.TM2x·push_elements.index_gt_n;
 }

  TM2x·push:{
    TM2x *tape                 = Args.TM2x·push.tape;
    void *element_base_pt      = Args.TM2x·push.element_base_pt;
    address_t element_byte_n   = Args.TM2x·push.element_byte_n;
    ConveyancePtr nominal       = Args.TM2x·push.nominal;
    ConveyancePtr alloc_fail    = Args.TM2x·push.alloc_fail;
    cend;
  }

Args.TM2x·push_TM2x.{
  TM2x *tape                = Args.TM2x·push_TM2x.tape;
  TM2x *tape_source         = Args.TM2x·push_TM2x.tape_source;
  ConveyancePtr nominal      = Args.TM2x·push_TM2x.nominal;
  ConveyancePtr alloc_fail   = Args.TM2x·push_TM2x.alloc_fail;
}

TM2x·F_PREFIX ContinuationPtr read_pop(){
  TM2x *tape                 = Args.TM2x·read_pop.TM2x *tape;            
  void *dst_element_pt       = Args.TM2x·read_pop.void *dst_element_pt;  
  address_t element_byte_n   = Args.TM2x·read_pop.address_t element_byte_n;
  ConveyancePtr nominal       = Args.TM2x·read_pop.ConveyancePtr nominal;   
  ConveyancePtr pop_last      = Args.TM2x·read_pop.ConveyancePtr pop_last;  
  ConveyancePtr alloc_fail    = Args.TM2x·read_pop.ConveyancePtr alloc_fail;
  cend;
}



/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#ifdef TM2x·TEST
  extern address_t TM2x·Test·allocation_n;
#endif

extern address_t TM2x·constructed_count;

TM2x·F_PREFIX ContinuationPtr resize_bytes(){
  // shorten the arg names, give the optimizer something more to do
  TM2x *tape = Args.TM2x·resize_bytes.tape;
  address_t after_byte_n = Args.TM2x·resize_bytes.after_byte_n;
  ConveyancePtr nominal = Args.TM2x·resize_bytes.nominal;
  ConveyancePtr alloc_fail = Args.TM2x·resize_bytes.alloc_fail;

  address_t before_alloc_n = power_2_extent_w_lower_bound(tape->byte_n);
  address_t after_alloc_n = power_2_extent_w_lower_bound(after_byte_n);

  if( after_alloc_n == before_alloc_n ){
    tape->byte_n = after_byte_n;
    continue_via_trampoline nominal;
  }

  char *after_base_pt;

  #include "Args.CLib·mallocn.h"
  Args.CLib·mallocn.pt      = (void **)&after_base_pt;
  Args.CLib·mallocn.n       = after_alloc_n;
  Args.CLib·mallocn.nominal = &&malloc_nominal;
  Args.CLib·mallocn.fail    = &&malloc_fail; 
  #include "CLib·mallocn.h"
  continue_from CLib·mallocn;

  malloc_nominal:{
    #ifdef TM2x·TEST
      TM2x·Test·allocation_n = after_alloc_n;
    #endif
    address_t copy_n = after_byte_n < tape->byte_n ? after_byte_n : tape->byte_n;
    memcpyn( after_base_pt ,tape->base_pt ,copy_n);
    free(tape->base_pt);
    tape->base_pt = after_base_pt;
    tape->byte_n = after_byte_n;
    continue_from *nominal;
    cend
  }

  malloc_fail:{
   continue_from *alloc_fail;
   cend
  }

  cend
}
/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/


TM2x·F_PREFIX ContinuationPtr F_PREFIX ConveyancePtr TM2x·resize_elements(){
  TM2x *tape                = Args.TM2x·resize_elements.tape;
  address_t after_element_n = Args.TM2x·resize_elements.after_element_n;
  address_t element_byte_n  = Args.TM2x·resize_elements.element_byte_n;
  ConveyancePtr nominal      = Args.TM2x·resize_elements.nominal;
  ConveyancePtr alloc_fail   = Args.TM2x·resize_elements.alloc_fail;
  ConveyancePtr index_gt_n    = Args.TM2x·resize_elements.index_gt_n;

  address_t after_byte_n;
  #include "inclusive·mul_ib·args.h"
  inclusive·mul_ib·args.an = after_element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &after_byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
   resize_bytes·args.tape = tape;
   resize_bytes·args.after_byte_n = after_byte_n;
   resize_bytes·args.nominal = nominal;
   resize_bytes·args.alloc_fail = alloc_fail;
   contine_from TM2x·resize_bytes;
   cend;
  }

  cend;
}

/*

Copies a region stemming from src_pt to src_pt + byte_n on to the 
dst tape starting from byte offset dst_byte_i.

The only tape explicitly identified is the dst tape, so we say that
we are writing the dst tape.

*/
TM2x·F_PREFIX ContinuationPtr write_bytes(){
          TM2x *dst             = Args.TM2x·write_bytes.dst          
     address_t  dst_byte_i      = Args.TM2x·write_bytes.dst_byte_i   
          void *src_pt          = Args.TM2x·write_bytes.src_pt       
     address_t  byte_n          = Args.TM2x·write_bytes.byte_n       
  ConveyancePtr  nominal         = Args.TM2x·write_bytes.nominal      
  ConveyancePtr  alloc_fail      = Args.TM2x·write_bytes.alloc_fail   
  ConveyancePtr  src_index_gt_n   = Args.TM2x·write_bytes.src_index_gt_n
  ConveyancePtr  dst_index_gt_n   = Args.TM2x·write_bytes.dst_index_gt_n
}

#endif

