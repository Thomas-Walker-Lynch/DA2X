/*
  This is not a traditional header, and can not be used as such.

  #include "TM2x·text.h" after the Args and Data unions.

  Provided that this is included into main or another function, the outer scope instances
  here, e.g. TM2·constructed_count, will be on the stack, and thus thread safe.

  Would be nice if we could give an inline option to conveyances.

*/
#include "TM2x.h"

/*
struct Text·TM2x{
  Conveyance alloc_heap;
} Text·TM2x
={
  &&TM2x·alloc_heap
};
*/

address_t TM2x·constructed_count = 0;

#define MINIMUM_ALLOC_EXTENT 15
address_t power_2_extent_w_lower_bound(address_t byte_n){
  if( byte_n < MINIMUM_ALLOC_EXTENT) return MINIMUM_ALLOC_EXTENT;
  return power_2_extent(byte_n);
}

goto TM2x·end;

//----------------------------------------
//  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic()
//  macro.  This does not allocate data for the array itself.
TM2x·alloc_heap:{
  Conveyance·update();
  struct TM2x·alloc_heap *lc = &Conveyance·Locals_pt->TM2x·alloc_heap;

  struct CLib·mallocn    *ar = &Conveyance·Args_pt->CLib·mallocn;
  ar->pt      = (void **)lc->tape;
  ar->n       = byte_n_of(TM2x);
  ar->nominal = lc->nominal;
  ar->fail    = lc->fail;
  continue_from CLib·mallocn;

  cend;
}

//----------------------------------------
//  Construct an allocated array. 
//  Given the exent in bytes, sets aside heap memory for the data.
TM2x·construct_bytes:{
  Conveyance·update();
  struct TM2x·construct_bytes *lc = &Conveyance·Locals_pt->TM2x·construct_bytes;

  TM2x·constructed_count++; // to assist with debugging
  lc->tape->byte_n = lc->byte_n;
  lc->alloc_byte_n = power_2_extent_w_lower_bound(lc->byte_n);

  struct CLib·mallocn *ar = &Conveyance·Args_pt->CLib·mallocn;
  ar->pt      = (void **)&(lc->tape->base_pt);
  ar->n       = lc->alloc_byte_n;
  ar->nominal = lc->nominal;
  ar->fail    = lc->alloc_fail;
  continue_from CLib·mallocn;

  cend;
}

#if 0


TM2x·construct_elements:{
  TM2x *tape               = Args.TM2x·construct_elements.tape;      
  address_t element_n      = Args.TM2x·construct_elements.element_n;    
  address_t element_byte_n = Args.TM2x·construct_elements.element_byte_n;    
  Conveyance nominal     = Args.TM2x·construct_elements.nominal;
  Conveyance alloc_fail  = Args.TM2x·construct_elements.alloc_fail;
  Conveyance index_gt_n  = Args.TM2x·construct_elements.index_gt_n;

  address_t byte_n;
  inclusive·mul_ib·args.an = element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    Args.TM2x·construct_bytes.tape       = tape;
    Args.TM2x·construct_bytes.byte_n     = byte_n;
    Args.TM2x·construct_bytes.nominal    = nominal;
    Args.TM2x·construct_bytes.alloc_fail = alloc_fail;
    continue_from TM2x·construct_bytes;
    cend;
  }

  cend;
}

construct_write_bytes:{
         TM2x *tape      = Args.TM2x·construct_write_bytes.tape;
         void *source_pt = Args.TM2x·construct_write_bytes.source_pt;
     address_t byte_n    = Args.TM2x·construct_write_bytes.byte_n;
  Conveyance nominal   = Args.TM2x·construct_write_bytes.nominal;
  Conveyance fail      = Args.TM2x·construct_write_bytes.fail;

  Args.TM2x·construct_bytes.tape = tape;      
  Args.TM2x·construct_bytes.tape_source = tape_source->base_pt;  
  Args.TM2x·construct_bytes.byte_n = tape_source->byte_n;
  Args.TM2x·construct_bytes.nominal = &&construct_nominal;
  Args.TM2x·construct_bytes.fail = fail;
  continue_from TM2x·construct_bytes;

  construct_nominal:{
    memcpyn(tape->base_pt, source_pt, byte_n);
    continue_from *nominal;
    cend;
  }

  cend;
}

TM2x·construct_write_elements:{
         TM2x *tape            = Args.TM2x·construct_write_elements.tape;           
         void *source_pt       = Args.TM2x·construct_write_elements.source_pt;        
     address_t element_n       = Args.TM2x·construct_write_elements.element_n;      
     address_t element_byte_n  = Args.TM2x·construct_write_elements.element_byte_n; 
  Conveyance nominal         = Args.TM2x·construct_write_elements.nominal;        
  Conveyance fail            = Args.TM2x·construct_write_elements.fail;           
  Conveyance index_gt_n       = Args.TM2x·construct_write_elements.index_gt_n;      

  address_t byte_n;
  inclusive·mul_ib·args.an = element_n;
  inclusive·mul_ib·args.bn = element_byte_n;
  inclusive·mul_ib·args.cn = &byte_n;
  inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
  inclusive·mul_ib·args.gt_address_n = index_gt_n;
  continue_from inclusive·mul_ib;

  mul_ib·nominal:{
    Args.TM2x·construct_write_bytes.tape      = tape;
    Args.TM2x·construct_write_bytes.source_pt = source_pt;
    Args.TM2x·construct_write_bytes.byte_n    = byte_n;
    Args.TM2x·construct_write_bytes.nominal   = nominal;
    Args.TM2x·construct_write_bytes.fail      = fail;
    continue_from TM2x·construct_write_bytes;
    cend;
  }

  cend;
}

//  Writes one element.
Args.TM2x·construct_write.{
          TM2x *tape            = Args.TM2x·construct_write.tape;
          void *element_pt      = Args.TM2x·construct_write.element_pt;
     address_t  element_byte_n  = Args.TM2x·construct_write.element_byte_n;
  Conveyance  nominal         = Args.TM2x·construct_write.nominal;
  Conveyance  fail            = Args.TM2x·construct_write.fail;

  Args.TM2x·construct_write_bytes.tape      = tape;
  Args.TM2x·construct_write_bytes.source_pt = element_pt;
  Args.TM2x·construct_write_bytes.byte_n    = element_byte_n;
  Args.TM2x·construct_write_bytes.nominal   = nominal;
  Args.TM2x·construct_write_bytes.fail      = fail;
  continue_from TM2x·construct_write_bytes;
  cend;
}

TM2x·construct_write_TM2x{
  TM2x *tape            = Args.TM2x·construct_write_TM2x.tape;           
  TM2x *tape_source     = Args.TM2x·construct_write_TM2x.tape_source;    
  Conveyance nominal  = Args.TM2x·construct_write_TM2x.Conveyance nominal; 
  Conveyance fail     = Args.TM2x·construct_write_TM2x.Conveyance fail;    

  Args.TM2x·construct_write_bytes.tape = tape;      
  Args.TM2x·construct_write_bytes.tape_source = tape_source->base_pt;  
  Args.TM2x·construct_write_bytes.source_byte_n = tape_source->byte_n;
  Args.TM2x·construct_write_bytes.nominal = nominal;
  Args.TM2x·construct_write_bytes.fail = fail;
  continue_from TM2x·construct_write_bytes;
  cend;
};

TM2x·copy_bytes:{
         TM2x *src             = Args.TM2x·copy_bytes.src;          
     address_t src_byte_i      = Args.TM2x·copy_bytes.src_byte_i;   
         TM2x *dst             = Args.TM2x·copy_bytes.dst;          
     address_t dst_byte_i      = Args.TM2x·copy_bytes.dst_byte_i;   
     address_t byte_n          = Args.TM2x·copy_bytes.byte_n;       
  Conveyance nominal         = Args.TM2x·copy_bytes.nominal;      
  Conveyance alloc_fail      = Args.TM2x·copy_bytes.alloc_fail;   
  Conveyance src_index_gt_n   = Args.TM2x·copy_bytes.src_index_gt_n;
  Conveyance dst_index_gt_n   = Args.TM2x·copy_bytes.dst_index_gt_n;
} 

TM2x·copy_elements:{
         TM2x *src             = Args.TM2x·copy_elements.src;
     address_t src_element_i   = Args.TM2x·copy_elements.src_element_i;
         TM2x *dst             = Args.TM2x·copy_elements.dst;
     address_t dst_element_i   = Args.TM2x·copy_elements.dst_element_i;
     address_t element_n       = Args.TM2x·copy_elements.element_n;
     address_t element_byte_n  = Args.TM2x·copy_elements.element_byte_n;
  Conveyance nominal         = Args.TM2x·copy_elements.nominal;
  Conveyance alloc_fail      = Args.TM2x·copy_elements.alloc_fail;
  Conveyance src_index_gt_n   = Args.TM2x·copy_elements.src_index_gt_n;
  Conveyance dst_index_gt_n   = Args.TM2x·copy_elements.dst_index_gt_n;
};

//  deallocation for dynamically allocated headers.
TM2x·dealloc_heap:{
  Args.TM2x·destruct(TM2x·dealloc_heap.tape);
  free(Args.TM2x·dealloc_heap.tape);
  continue_from *Args.TM2x·dealloc_heap.nominal;
  cend;
}

extern address_t TM2x·constructed_count;

TM2x·destruct:{
  TM2x *tape           = 
  Conveyance nominal = ;

free(Args.TM2x·destruct.tape->base_pt);
  TM2x·constructed_count--;
  continue_from *Args.TM2x·destruct.nominal;
  cend
}

/*
Copy elements at index of the given tape, to the location specified by dst_element_pt.

Set element_n to 0 to read the one element from location specified by the given index.

Our attention is focused on the tape, so we call this a 'read' operation.

*/

TM2x·index·read:{
  TM2x *tape                = Args.TM2x·index·read.tape;              
  address_t index           = Args.TM2x·index·read.index;         
  address_t element_n       = Args.TM2x·index·read.element_byte_n;
  address_t element_byte_n  = Args.TM2x·index·read.element_byte_n;
  void *dst_element_pt      = Args.TM2x·index·read.dst_element_pt;    
  Conveyance nominal      = Args.TM2x·index·read.nominal;
  Conveyance index_gt_n   = Args.TM2x·index·read.index_gt_n;

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

TM2x·index·to_pt{
  TM2x *tape               = Args.TM2x·index·to_pt.tape;
  address_t index          = Args.TM2x·index·to_pt.index;
  address_t element_byte_n = Args.TM2x·index·to_pt.element_byte_n;
  void **pt                = Args.TM2x·index·to_pt.pt;
  Conveyance nominal     = Args.TM2x·index·to_pt.nominal;
  Conveyance index_gt_n = Args.TM2x·index·to_pt.index_gt_n;

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






TM2x·pop:{
   TM2x *tape                = Args.TM2x·pop.tape;           
   address_t element_byte_n  = Args.TM2x·pop.element_byte_n; 
   Conveyance nominal      = Args.TM2x·pop.nominal;        
   Conveyance pop_last     = Args.TM2x·pop.pop_last;       
   Conveyance alloc_fail   = Args.TM2x·pop.alloc_fail;     
} Args.TM2x·pop.







TM2x·push_bytes:{
  TM2x *tape              = TM2x·push_bytes.args.tape;           
  void *source_pt         = TM2x·push_bytes.args.source_pt;      
  address_t source_byte_n = TM2x·push_bytes.args.source_byte_n;  
  Conveyance nominal    = TM2x·push_bytes.args.nominal;        
  Conveyance alloc_fail = TM2x·push_bytes.args.alloc_fail;     
}








Args.TM2x·push_elements.{
  TM2x *tape                = Args.TM2x·push_elements.tape;
  void *base_pt             = Args.TM2x·push_elements.base_pt;
  address_t element_n       = Args.TM2x·push_elements.element_n;
  address_t element_byte_n  = Args.TM2x·push_elements.element_byte_n;
  Conveyance nominal      = Args.TM2x·push_elements.nominal;
  Conveyance alloc_fail   = Args.TM2x·push_elements.alloc_fail;
  Conveyance index_gt_n    = Args.TM2x·push_elements.index_gt_n;
 }

  TM2x·push:{
    TM2x *tape                 = Args.TM2x·push.tape;
    void *element_base_pt      = Args.TM2x·push.element_base_pt;
    address_t element_byte_n   = Args.TM2x·push.element_byte_n;
    Conveyance nominal       = Args.TM2x·push.nominal;
    Conveyance alloc_fail    = Args.TM2x·push.alloc_fail;
    cend;
  }

Args.TM2x·push_TM2x.{
  TM2x *tape                = Args.TM2x·push_TM2x.tape;
  TM2x *tape_source         = Args.TM2x·push_TM2x.tape_source;
  Conveyance nominal      = Args.TM2x·push_TM2x.nominal;
  Conveyance alloc_fail   = Args.TM2x·push_TM2x.alloc_fail;
}

TM2x·read_pop:{
  TM2x *tape                 = Args.TM2x·read_pop.TM2x *tape;            
  void *dst_element_pt       = Args.TM2x·read_pop.void *dst_element_pt;  
  address_t element_byte_n   = Args.TM2x·read_pop.address_t element_byte_n;
  Conveyance nominal       = Args.TM2x·read_pop.Conveyance nominal;   
  Conveyance pop_last      = Args.TM2x·read_pop.Conveyance pop_last;  
  Conveyance alloc_fail    = Args.TM2x·read_pop.Conveyance alloc_fail;
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

TM2x·resize_bytes:{
  // shorten the arg names, give the optimizer something more to do
  TM2x *tape = Args.TM2x·resize_bytes.tape;
  address_t after_byte_n = Args.TM2x·resize_bytes.after_byte_n;
  Conveyance nominal = Args.TM2x·resize_bytes.nominal;
  Conveyance alloc_fail = Args.TM2x·resize_bytes.alloc_fail;

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


TM2x·F_PREFIX Conveyance TM2x·resize_elements:{
  TM2x *tape                = Args.TM2x·resize_elements.tape;
  address_t after_element_n = Args.TM2x·resize_elements.after_element_n;
  address_t element_byte_n  = Args.TM2x·resize_elements.element_byte_n;
  Conveyance nominal      = Args.TM2x·resize_elements.nominal;
  Conveyance alloc_fail   = Args.TM2x·resize_elements.alloc_fail;
  Conveyance index_gt_n    = Args.TM2x·resize_elements.index_gt_n;

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
TM2x·write_bytes:{
          TM2x *dst             = Args.TM2x·write_bytes.dst          
     address_t  dst_byte_i      = Args.TM2x·write_bytes.dst_byte_i   
          void *src_pt          = Args.TM2x·write_bytes.src_pt       
     address_t  byte_n          = Args.TM2x·write_bytes.byte_n       
  Conveyance  nominal         = Args.TM2x·write_bytes.nominal      
  Conveyance  alloc_fail      = Args.TM2x·write_bytes.alloc_fail   
  Conveyance  src_index_gt_n   = Args.TM2x·write_bytes.src_index_gt_n
  Conveyance  dst_index_gt_n   = Args.TM2x·write_bytes.dst_index_gt_n
}

#endif

TM2x·end:;
