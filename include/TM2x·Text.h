// 'thread static' allocation class
address_t TM2x·constructed_count = 0;

address_t TM2x·constructed(TM2x *tape){
  return TM2x·constructed_count;
}


/*--------------------------------------------------------------------------------

  Here ‘allocation’ and ‘deallocation’ refer to the header struct. Where as ‘construction’
  and ‘destruction’ refer to the allocation deallocation of the data part of the array,
  and setting the value of data pointer in the header struct.

*/

  #pragma push_macro("ARGS")
  #pragma push_macro("CNXS")
  #define ARGS() ((TM2x·Destruct·Args *)CV·args)
  #define CNXS() ((TM2x·Destruct·Cnxs *)CV·cnxs)

    CV·def(TM2x·destruct){
      free(ARGS->tape->base_pt);
      general_conveay(CNXS->nominal);  
    } CV·end(TM2x·destruct);

  #pragma pop_macro("ARGS")
  #pragma pop_macro("CNXS")


  #pragma push_macro("ARGS")
  #pragma push_macro("CNXS")
  #define ARGS() ((TM2x·DeallocHeap·Args *)CV·args)
  #define CNXS() ((TM2x·DeallocHeap·Cnxs *)CV·cnxs)

    // we are to deallocate the header from the heap
    CV·def(TM2x·dealloc_heap){
      free(ARGS->tape);
      general_convey(CNXS->nominal;
    } CV·end(TM2x·dealloc_heap);

  #pragma pop_macro("ARGS")
  #pragma pop_macro("CNXS")

#if 0

  // Deallocation for dynamically allocated headers.
  // TM2x0
  CV·def(TM2x·destruct_dealloc_heap){
    Conveyance destruct ,dealloc;

    Conveyance·swap();
    LC(lc ,TM2x·destruct_dealloc_heap ,0);

    CX(cx ,TM2x0 ,destruct_dealloc_heap);
    cx->tape = lc->tape;
    cx->nominal = lc->nominal;

    convey destruct;

    CV·def(destruct){
      AR(ar ,TM2x·destruct ,0);
      ar->tape = lc->tape;
      ar->nominal = &&dealloc;
      convey TM2x·destruct(); // nc
      CV·end;
    }

    CV·def(dealloc){
      free(cx->tape);
      convey *cx->nominal; 
      CV·end;
    }

  }CV·end(TM2x·destruct_dealloc_heap); 


//----------------------------------------
//  Dynamic allocation of the TM2x header.  For static allocation use the AllocoStatic()
//  macro.  This does not allocate data for the array itself.
// nc
CV·def(TM2x·alloc_heap){
  Conveyance·swap();
  LC(lc ,TM2x·alloc_heap ,0);

  AR(ar ,CLib·mallocn ,0);
  ar->pt      = (void **)lc->tape;
  ar->n       = byte_n_of(TM2x);
  ar->nominal = lc->nominal;
  ar->fail    = lc->fail;
  convey CLib·mallocn();
} CV·end(TM2x·alloc_heap);

//----------------------------------------
//  Construct an allocated array. 
//  Given the exent in bytes, sets aside heap memory for the data.
// nc
CV·def(TM2x·construct_bytes){
  TM2x·constructed_count++; // to assist with debugging

  Conveyance·swap();
  LC(lc ,TM2x·construct_bytes ,1);
  lc->tape->byte_n = lc->byte_n;
  lc->alloc_byte_n = power_2_extent_w_lower_bound(lc->byte_n);

  AR(ar ,CLib·mallocn ,0);
  ar->pt      = (void **)&(lc->tape->base_pt);
  ar->n       = lc->alloc_byte_n;
  ar->nominal = lc->nominal;
  ar->fail    = lc->alloc_fail;
  convey CLib·mallocn;

} CV·end(TM2x·construct_bytes);

// TM2x0
CV·def(TM2x·construct_elements){
  Conveyance scale ,construct_bytes;

  Conveyance·swap();
  LC(lc ,TM2x·construct_elements ,0);

  CX(cx ,TM2x0 ,construct_elements);
  cx->tape = lc->tape;
  cx->nominal = lc->nominal;
  cx->alloc_fail = lc->alloc_fail;

  convey scale;

  CV·def(scale){
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0 = lc->element_n;
    ar->a1 = lc->element_byte_n;
    ar->nominal = &&construct_bytes;
    ar->index_gt_n = lc->index_gt_n;
    convey Inclusive·mul_ib; // nc
    CV·end;
  };

  CV·def(construct_bytes){
    Conveyance·swap();
    LC(lc ,Inclusive·3opLL  ,2);
    
    AR(ar ,TM2x·construct_bytes ,0);
    ar->tape       = cx->tape;
    ar->byte_n     = lc->byte_n;
    ar->nominal    = cx->nominal;
    ar->alloc_fail = cx->alloc_fail;
    convey TM2x·construct_bytes(&&nominal ,&&alloc_fail); // nc
    CV·end;
  };

}  CV·end(TM2x·construct_elements);

// TM2x0
CV·def(TM2x·construct_write_bytes){
  Conveyance construct ,write;
  Conveyance·swap();
  LC(lc ,TM2x·construct_write_bytes ,0);

  CX(cx ,TM2x0 ,construct_write_bytes);
  cx->tape      = lc->tape;
  cx->source_pt = lc->source_pt;
  cx->byte_n    = lc->byte_n;
  cx->nominal   = lc->nominal;

  convey construct;

  CV·def(construct){
    AR(ar ,TM2x·construct_bytes.tape ,0);
    ar->tape = lc->tape;
    ar->byte_n = lc->byte_n;
    ar->nominal = &&write;
    ar->alloc_fail = lc->fail;
    convey TM2x·construct_bytes; // nc
    CV·end;
  }
  
  CV·def(write){
    memcpyn(TM2x·byte_0_pt(cx->tape), cx->source_pt, cx->byte_n);
    convey *cx->nominal;
    CV·end;
  }

} CV·end(TM2x·construct_write_bytes);


// uses context TM2x1
// depends on: mul_ib ,construct_write_bytes
// dependency with context: construct_write_bytes
CV·def(TM2x·construct_write_elements){
  Conveyance scale ,construct_write_bytes;
  Conveyance·swap();
  LC(lc ,TM2x·construct_write_elements ,0);

  CX(cx ,TM2x1 ,construct_write_elements);
  cx->tape      = lc->tape;
  cx->source_pt = lc->source_pt;
  cx->nominal   = lc->nominal;
  cx->fail      = lc->fail;

  convey scale;

  CV·def(scale){
    AR(ar ,Inclusive·3opLL ,0);
    ar->a0             = lc->element_n;
    ar->a1             = lc->element_byte_n;
    ar->rpt            = &cx->byte_n;
    ar->nominal        = &&construct_write_bytes;
    ar->gt_address_t_n = lc->index_gt_n;
    convey Inclusive·mul_ib;
    CV·end;
  }

  CV·def(construct_write_bytes){
    AR(ar ,TM2x·construct_write_bytes ,0);
    ar->tape      = cx->tape;
    ar->source_pt = cx->source_pt;
    ar->byte_n    = cx->byte_n;
    ar->nominal   = cx->nominal;
    ar->fail      = cx->fail;
    convey TM2x·construct_write_bytes;
    CV·end;
  }

} CV·end(TM2x·construct_write_elements);

//  Writes one element.
CV·defTM2x·construct_write){
  Conveyance nominal;
  Conveyance·swap();
  LC(lc ,TM2x·construct_write ,0);

  AR(ar ,TM2x·construct_write_bytes ,0);
  ar->tape      = lc->tape;
  ar->source_pt = lc->element_pt;
  ar->byte_n    = lc->element_byte_n;
  ar->nominal   = lc->nominal;
  ar->fail      = lc->fail;
  convey TM2x·construct_write_bytes;
  
} CV·end(TM2x·construct_write);

// construct and initialize tape from another TM
INLINE_PREFIX ContinuationPtr construct_write_TM2x{
  Conveyance·swap();
  LC(lc  ,TM2x·construct_write_TM2x ,0);

  AR(ar ,TM2x·construct_write_bytes ,0);
  ar->tape      = lc->tape;
  ar->source_pt = TM2x·byte_0_pt(lc->tape_source);
  ar->byte_n    = TM2x·byte_n(lc->tape_source);
  ar->nominal   = lc->nominal;
  ar->fail      = lc->fail;
  convey TM2x·construct_write_bytes;

  CV·end;
};

CV·def(TM2x·copy_bytes){
  AR(ar  ,TM2x·copy_bytes ,0);

  if( 
     TM2x·byte_n(ar->src) < ar->byte_n
     ||
     TM2x·byte_n(ar->src) - ar->byte_n < ar->src_byte_i
      )
    convey ar->src_index_gt_n;

  if( 
     TM2x·byte_n(ar->dst) < ar->byte_n
     ||
     TM2x·byte_n(ar->dst) - ar->byte_n < ar->dst_byte_i
      )
    convey ar->dst_index_gt_n;
  
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
         CC.mul_ib_0.gt_address_t_n = ((TM2x·CopyElements·Cnxs *)CV·cnxs)->src_index_gt_n;
      CC.mul_ei_bi_0.gt_address_t_n = ((TM2x·CopyElements·Cnxs *)CV·cnxs)->src_index_gt_n;
      CC.mul_ei_bi_1.gt_address_t_n = ((TM2x·CopyElements·Cnxs *)CV·cnxs)->dst_index_gt_n;
      CC.mul_ei_bi_1.nominal        = ((TM2x·CopyElements·Cnxs *)CV·cnxs)->nominal;
    } CV·end(TM2x·CopyElements·connect_finish);

    CV·def(TM2x·copy_elements){
      TM2x·CopyElements·connect_finish();
      CV·args = (CV·Args *) &CA.mul_ib_0;
      CV·cnxs = (CV·Cnxs *) &CC.mul_ib_0;
      convey(Inclusive·mul_ib);
    } CV·end(TM2x·copy_elements);

  #pragma pop_macro("CC")
  #pragma pop_macro("CA")

#endif

#if 0


/*
Copy elements at index of the given tape, to the location specified by dst_element_pt.

Set element_n to 0 to read the one element from location specified by the given index.

Our attention is focused on the tape, so we call this a 'read' operation.

*/

CV·def(index·read){
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
  convey inclusive·mul_ib;

  CV·def(mul_ib·nominal){
    address_t byte_i;
    inclusive·mul_ib·args.an = index;
    inclusive·mul_ib·args.bn = element_byte_n;
    inclusive·mul_ib·args.cn = &byte_i
    inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
    inclusive·mul_ib·args.gt_address_n = index_gt_n;
    convey inclusive·mul_ib;


    void *src_element_pt;
    Args.TM2x·index·to_pt.tape           = tape;
    Args.TM2x·index·to_pt.index          = index;     
    Args.TM2x·index·to_pt.element_byte_n = element_byte_n;
    Args.TM2x·index·to_pt.pt             = &src_element_pt;              
    Args.TM2x·index·to_pt.nominal        = &&index_nominal;        
    Args.TM2x·index·to_pt.index_gt_n     = index_gt_n;
    convey TM2x·index·to_pt;
  }

  CV·def(index_nominal){


    CV·def(mul_ib·nominal){
      if( 

    }


    memcpyn(dst_element_pt, src_element_pt, element_byte_n);
    CV·end;
  }

  CV·end;
}

INLINE_PREFIX ContinuationPtr index·to_pt{
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
  convey inclusive·mul_ib;

  CV·def(mul_ib·nominal){
    if( byte_i > TM2x·byte_n(tape) ) convey index_gt_n;
    *pt = (void *)(TM2x·byte_0_pt(tape) + byte_i);
    CV·end;
  }

  CV·end;
}






CV·def(pop){
   TM2x *tape                = Args.TM2x·pop.tape;           
   address_t element_byte_n  = Args.TM2x·pop.element_byte_n; 
   ConveyancePtr nominal      = Args.TM2x·pop.nominal;        
   ConveyancePtr pop_last     = Args.TM2x·pop.pop_last;       
   ConveyancePtr alloc_fail   = Args.TM2x·pop.alloc_fail;     
} Args.TM2x·pop.







CV·def(push_bytes){
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

  CV·def(TM2x·push){
    TM2x *tape                 = Args.TM2x·push.tape;
    void *element_base_pt      = Args.TM2x·push.element_base_pt;
    address_t element_byte_n   = Args.TM2x·push.element_byte_n;
    ConveyancePtr nominal       = Args.TM2x·push.nominal;
    ConveyancePtr alloc_fail    = Args.TM2x·push.alloc_fail;
    CV·end;
  }

Args.TM2x·push_TM2x.{
  TM2x *tape                = Args.TM2x·push_TM2x.tape;
  TM2x *tape_source         = Args.TM2x·push_TM2x.tape_source;
  ConveyancePtr nominal      = Args.TM2x·push_TM2x.nominal;
  ConveyancePtr alloc_fail   = Args.TM2x·push_TM2x.alloc_fail;
}

CV·def(read_pop){
  TM2x *tape                 = Args.TM2x·read_pop.TM2x *tape;            
  void *dst_element_pt       = Args.TM2x·read_pop.void *dst_element_pt;  
  address_t element_byte_n   = Args.TM2x·read_pop.address_t element_byte_n;
  ConveyancePtr nominal       = Args.TM2x·read_pop.ConveyancePtr nominal;   
  ConveyancePtr pop_last      = Args.TM2x·read_pop.ConveyancePtr pop_last;  
  ConveyancePtr alloc_fail    = Args.TM2x·read_pop.ConveyancePtr alloc_fail;
  CV·end;
}



/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/

#ifdef TM2x·TEST
  extern address_t TM2x·Test·allocation_n;
#endif

extern address_t TM2x·constructed_count;

CV·def(resize_bytes){
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
  convey CLib·mallocn;

  CV·def(malloc_nominal){
    #ifdef TM2x·TEST
      TM2x·Test·allocation_n = after_alloc_n;
    #endif
    address_t copy_n = after_byte_n < tape->byte_n ? after_byte_n : tape->byte_n;
    memcpyn( after_base_pt ,tape->base_pt ,copy_n);
    free(tape->base_pt);
    tape->base_pt = after_base_pt;
    tape->byte_n = after_byte_n;
    convey *nominal;
    CV·end
  }

  CV·def(malloc_fail){
   convey *alloc_fail;
   CV·end
  }

  CV·end
}
/*
  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
  This does not allocate data for the array itself.
*/


CV·def(F_PREFIX ConveyancePtr TM2x·resize_elements){
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
  convey inclusive·mul_ib;

  CV·def(mul_ib·nominal){
    resize_bytes·args.tape = tape;
    resize_bytes·args.after_byte_n = after_byte_n;
    resize_bytes·args.nominal = nominal;
    resize_bytes·args.alloc_fail = alloc_fail;
    contine_from TM2x·resize_bytes;
    CV·end;
  }

  CV·end;
}

/*

Copies a region stemming from src_pt to src_pt + byte_n on to the 
dst tape starting from byte offset dst_byte_i.

The only tape explicitly identified is the dst tape, so we say that
we are writing the dst tape.

*/
CV·def(write_bytes){
          TM2x *dst               = Args.TM2x·write_bytes.dst          
     address_t  dst_byte_i        = Args.TM2x·write_bytes.dst_byte_i   
          void *src_pt            = Args.TM2x·write_bytes.src_pt       
     address_t  byte_n            = Args.TM2x·write_bytes.byte_n       
  ConveyancePtr  nominal          = Args.TM2x·write_bytes.nominal      
  ConveyancePtr  alloc_fail       = Args.TM2x·write_bytes.alloc_fail   
  ConveyancePtr  src_index_gt_n   = Args.TM2x·write_bytes.src_index_gt_n
  ConveyancePtr  dst_index_gt_n   = Args.TM2x·write_bytes.dst_index_gt_n
}

#endif

