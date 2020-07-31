#ifndef TM2X_H
#define TM2X_H

/*
  If we are to have thread safety, this file must be included within a function
  such as main(), so that it will be allocated on the stack.

  I an only hope that copying arguments to an args struct, and then copying
  it to a variables in a continuation is pattern that will be reduced to
  one copy by the optimizer. The optimizer can also potentially reduce the
  size of the args struct due to unused members and unused fields within
  memebers.

*/



//--------------------------------------------------------------------------------
// arg structs
//    C requires forward referencing, so all of these come first.  I would
//    rather have put them with the text so as to keep related things together.
//
  union{

    struct AllocHeap{
      TM2x *tape;
      continuation nominal;
      continuation fail;
    } alloc_heap;

    struct ConstructBytes{
      TM2x *tape;
      address_t byte_n;   // extent of the array, in bytes
      continuation nominal;
      continuation alloc_fail;
    } construct_bytes;

    struct ConstructElements{
      TM2x *tape;
      address_t element_n;  // extent of the array, in elements
      address_t element_byte_n; // extent of the element, in bytes
      continuation nominal;
      continuation index_gt_n;
      continuation alloc_fail;
    } construct_elements;

    struct ConstructWrite{
      TM2x *tape;
      TM2x *tape_source;
      continuation nominal;
      continuation fail;
    } construct_write;

    struct ConstructWriteBytes{
      TM2x *tape;
      void *source_pt;
      address_t byte_n;
      continuation nominal;
      continuation fail;
    } construct_write_bytes;

    struct ConstructWriteElements{
      TM2x *tape;
      void *source_pt;
      address_t element_n;
      address_t element_byte_n;
      continuation nominal;
      continuation index_gt_n;
      continuation fail;
    } construct_write_elements;

    struct ConstructWriteTM2x{
      TM2x *tape;
      TM2x *tape_source;
      continuation nominal;
      continuation fail;
    } construct_write_TM2x;

    struct CopyBytes{
      TM2x *src;
      address_t src_byte_i;
      TM2x *dst;
      address_t dst_byte_i;
      address_t byte_n;
      continuation nominal;
      continuation src_index_gt_n;
      continuation dst_index_gt_n;
      continuation alloc_fail;
    } copy_bytes;

    struct CopyElements{
      TM2x *src;
      address_t src_element_i;
      TM2x *dst;
      address_t dst_element_i;
      address_t element_n;  // index of nth element of the copy region
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation src_index_gt_n;
      continuation dst_index_gt_n;
    } copy_elements;

    struct DeallocHeap{
      TM2x **tape;
      continuation nominal;
    } dealloc_heap;

    struct Destruct{
      TM2x *tape;
      continuation nominal;
    } destruct;

    struct Index·Read{
      TM2x *tape;
      address_t index;
      address_t element_n;
      address_t element_byte_n;
      void *dst_element_pt;
      continuation nominal;
      continuation index_gt_n;
    } index·read;

    struct Index·ToPt{
       TM2x *tape ;
       address_t index;
       address_t element_byte_n;
       void **pt;
       continuation nominal;
       continuation index_gt_n;
    } index·to_pt;

    struct{
       TM2x *tape;
       address_t element_byte_n;
       continuation nominal;
       continuation pop_last;
       continuation alloc_fail;
    } pop;

    struct Push{
      TM2x *tape;
      void *element_base_pt;
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } push;

    struct PushBytes{
      TM2x *tape;
      void *source_pt;
      address_t source_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } push_bytes;

    struct PushElements{
      TM2x *tape ;
      void *base_pt;
      address_t element_n ;
      address_t element_byte_n ;
      continuation nominal;
      continuation alloc_fail;
      continuation index_gt_n;
     } push_elements;

    struct PushTM2x{
      TM2x *tape ;
      TM2x *tape_source;
      continuation nominal;
      continuation alloc_fail;
    } push_TM2x;

    struct ReadPop{
       TM2x *tape ;
       void *dst_element_pt ;
       address_t element_byte_n;
       continuation nominal;
       continuation pop_last;
       continuation alloc_fail;
    } read_pop;

    struct ResizeBytes{
      TM2x *tape;
      address_t after_byte_n;
      continuation nominal;
      continuation alloc_fail;
    } resize_bytes;

    struct ResizeElements{
      TM2x *tape;
      address_t after_element_n;
      address_t element_byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation index_gt_n;
    } resize_elements;

    struct WriteBytes{
      void *src_pt;
      TM2x *dst;
      address_t dst_byte_i;
      address_t byte_n;
      continuation nominal;
      continuation alloc_fail;
      continuation src_index_gt_n;
      continuation dst_index_gt_n;
    } write_bytes;

  } TM2x·args;

//--------------------------------------------------------------------------------
// local structs
//    C requires forward referencing, so all of these come first.  I would
//    rather have put them with the text so as to keep related things together.
//
  union{
    struct{
      address_t alloc_byte_n;
    }construct_bytes;


  } TM2x·local;

/*--------------------------------------------------------------------------------
  text

    local variables for each routine come from a struct declared next to the routine.  In
    the case this code is included at some level on the stack, e.g. in the main routine,
    this assures that references to the local variables will be in the same stack frame,
    even if the conveyance happens to be called from within a function.  This facilitates
    mixing a conveyances library with function calls.

    Namespaces done either through struct or name mangling, or both. The 'S' macro
    is short for 'name Space'. S0 is local variables.  S1 the space of arguments.
    Namespaces with larger number suffixes are typically the argument named spaces
    for continuations.

*/
   
  //----------------------------------------
  //  Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic()
  //  macro.  This does not allocate data for the array itself.
  #pragma push_macro("S1")
  #pragma push_macro("S2")
  #undef S1
  #undef S2
  #define S1 TM2x·args.alloc_heap
  #define S2 CLib·mallocn·args
  TM2x·alloc_heap:{
    S2.pt      = S1.tape;
    S2.n       = byte_n_of(TM2x);
    S2.nominal = S1.malloc_nominal;
    S2.fail    = S1.malloc_fail;
    continue_from CLib·mallocn;
    cend;
  }
  #pragma pop("S1")
  #pragma pop("S2")

  //----------------------------------------
  //  Construct an allocated array. 
  //  Given the exent in bytes, sets aside heap memory for the data.
  #pragma push_macro("S0")
  #pragma push_macro("S1")
  #pragma push_macro("S2")
  #undef S0
  #undef S1
  #undef S2
  #define S0 TM2x·local.construct_bytes
  #define S1 TM2x·args.construct_bytes
  #define S2 CLib·mallocn·args
  TM2x·construct_bytes:{

    TM2x·constructed_count++; // to assist with debugging
    S1.tape->byte_n = S1.byte_n;
    S0.alloc_byte_n = binary_interval_inclusive_upper_bound(S1.byte_n);

    S2.pt      = (void **)&(S1.tape->base_pt);
    S2.n       = S0.alloc_byte_n;
    S2.nominal = S1.nominal;
    S2.fail    = S1.alloc_fail;
    continue_from CLib·mallocn;
    cend;
  }
  #pragma pop("S0")
  #pragma pop("S1")
  #pragma pop("S2")

  TM2x·construct_elements:{
    TM2x *tape               = TM2x·args.construct_elements.tape;      
    address_t element_n      = TM2x·args.construct_elements.element_n;    
    address_t element_byte_n = TM2x·args.construct_elements.element_byte_n;    
    continuation nominal     = TM2x·args.construct_elements.nominal;
    continuation alloc_fail  = TM2x·args.construct_elements.alloc_fail;
    continuation index_gt_n  = TM2x·args.construct_elements.index_gt_n;

    address_t byte_n;
    inclusive·mul_ib·args.an = element_n;
    inclusive·mul_ib·args.bn = element_byte_n;
    inclusive·mul_ib·args.cn = &byte_n;
    inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
    inclusive·mul_ib·args.gt_address_n = index_gt_n;
    continue_from inclusive·mul_ib;

    mul_ib·nominal:{
      TM2x·args.construct_bytes.tape       = tape;
      TM2x·args.construct_bytes.byte_n     = byte_n;
      TM2x·args.construct_bytes.nominal    = nominal;
      TM2x·args.construct_bytes.alloc_fail = alloc_fail;
      continue_from TM2x·construct_bytes;
      cend;
    }

    cend;
  }

  construct_write_bytes:{
           TM2x *tape      = TM2x·args.construct_write_bytes.tape;
           void *source_pt = TM2x·args.construct_write_bytes.source_pt;
       address_t byte_n    = TM2x·args.construct_write_bytes.byte_n;
    continuation nominal   = TM2x·args.construct_write_bytes.nominal;
    continuation fail      = TM2x·args.construct_write_bytes.fail;

    TM2x·args.construct_bytes.tape = tape;      
    TM2x·args.construct_bytes.tape_source = tape_source->base_pt;  
    TM2x·args.construct_bytes.byte_n = tape_source->byte_n;
    TM2x·args.construct_bytes.continuation nominal = &&construct_nominal;
    TM2x·args.construct_bytes.continuation fail = fail;
    continue_from TM2x·construct_bytes;

    construct_nominal:{
      memcpyn(tape->base_pt, source_pt, byte_n);
      continue_from *nominal;
      cend;
    }

    cend;
  }

  TM2x·construct_write_elements:{
           TM2x *tape            = TM2x·args.construct_write_elements.tape;           
           void *source_pt       = TM2x·args.construct_write_elements.source_pt;        
       address_t element_n       = TM2x·args.construct_write_elements.element_n;      
       address_t element_byte_n  = TM2x·args.construct_write_elements.element_byte_n; 
    continuation nominal         = TM2x·args.construct_write_elements.nominal;        
    continuation fail            = TM2x·args.construct_write_elements.fail;           
    continuation index_gt_n       = TM2x·args.construct_write_elements.index_gt_n;      

    address_t byte_n;
    inclusive·mul_ib·args.an = element_n;
    inclusive·mul_ib·args.bn = element_byte_n;
    inclusive·mul_ib·args.cn = &byte_n;
    inclusive·mul_ib·args.nominal = &&mul_ib·nominal;
    inclusive·mul_ib·args.gt_address_n = index_gt_n;
    continue_from inclusive·mul_ib;

    mul_ib·nominal:{
      TM2x·args.construct_write_bytes.tape      = tape;
      TM2x·args.construct_write_bytes.source_pt = source_pt;
      TM2x·args.construct_write_bytes.byte_n    = byte_n;
      TM2x·args.construct_write_bytes.nominal   = nominal;
      TM2x·args.construct_write_bytes.fail      = fail;
      continue_from TM2x·construct_write_bytes;
      cend;
    }

    cend;
  }

  //  Writes one element.
  TM2x·args.construct_write.{
            TM2x *tape            = TM2x·args.construct_write.tape;
            void *element_pt      = TM2x·args.construct_write.element_pt;
       address_t  element_byte_n  = TM2x·args.construct_write.element_byte_n;
    continuation  nominal         = TM2x·args.construct_write.nominal;
    continuation  fail            = TM2x·args.construct_write.fail;

    TM2x·args.construct_write_bytes.tape      = tape;
    TM2x·args.construct_write_bytes.source_pt = element_pt;
    TM2x·args.construct_write_bytes.byte_n    = element_byte_n;
    TM2x·args.construct_write_bytes.nominal   = nominal;
    TM2x·args.construct_write_bytes.fail      = fail;
    continue_from TM2x·construct_write_bytes;
    cend;
  }

  TM2x·construct_write_TM2x{
    TM2x *tape            = TM2x·args.construct_write_TM2x.tape;           
    TM2x *tape_source     = TM2x·args.construct_write_TM2x.tape_source;    
    continuation nominal  = TM2x·args.construct_write_TM2x.continuation nominal; 
    continuation fail     = TM2x·args.construct_write_TM2x.continuation fail;    

    TM2x·args.construct_write_bytes.tape = tape;      
    TM2x·args.construct_write_bytes.tape_source = tape_source->base_pt;  
    TM2x·args.construct_write_bytes.source_byte_n = tape_source->byte_n;
    TM2x·args.construct_write_bytes.continuation nominal = nominal;
    TM2x·args.construct_write_bytes.continuation fail = fail;
    continue_from TM2x·construct_write_bytes;
    cend;
  };

  TM2x·copy_bytes:{
           TM2x *src             = TM2x·args.copy_bytes.src;          
       address_t src_byte_i      = TM2x·args.copy_bytes.src_byte_i;   
           TM2x *dst             = TM2x·args.copy_bytes.dst;          
       address_t dst_byte_i      = TM2x·args.copy_bytes.dst_byte_i;   
       address_t byte_n          = TM2x·args.copy_bytes.byte_n;       
    continuation nominal         = TM2x·args.copy_bytes.nominal;      
    continuation alloc_fail      = TM2x·args.copy_bytes.alloc_fail;   
    continuation src_index_gt_n   = TM2x·args.copy_bytes.src_index_gt_n;
    continuation dst_index_gt_n   = TM2x·args.copy_bytes.dst_index_gt_n;
  } 

  TM2x·copy_elements:{
           TM2x *src             = TM2x·args.copy_elements.src;
       address_t src_element_i   = TM2x·args.copy_elements.src_element_i;
           TM2x *dst             = TM2x·args.copy_elements.dst;
       address_t dst_element_i   = TM2x·args.copy_elements.dst_element_i;
       address_t element_n       = TM2x·args.copy_elements.element_n;
       address_t element_byte_n  = TM2x·args.copy_elements.element_byte_n;
    continuation nominal         = TM2x·args.copy_elements.nominal;
    continuation alloc_fail      = TM2x·args.copy_elements.alloc_fail;
    continuation src_index_gt_n   = TM2x·args.copy_elements.src_index_gt_n;
    continuation dst_index_gt_n   = TM2x·args.copy_elements.dst_index_gt_n;
  };

  //  deallocation for dynamically allocated headers.
  TM2x·dealloc_heap:{
    TM2x·args.destruct(TM2x·dealloc_heap.tape);
    free(TM2x·args.dealloc_heap.tape);
    continue_from *TM2x·args.dealloc_heap.nominal;
    cend;
  }

  extern address_t TM2x·constructed_count;

  TM2x·destruct:{
    TM2x *tape           = 
    continuation nominal = ;
  
  free(TM2x·args.destruct.tape->base_pt);
    TM2x·constructed_count--;
    continue_from *TM2x·args.destruct.nominal;
    cend
  }

  /*
  Copy elements at index of the given tape, to the location specified by dst_element_pt.

  Set element_n to 0 to read the one element from location specified by the given index.

  Our attention is focused on the tape, so we call this a 'read' operation.

  */

  TM2x·index·read:{
    TM2x *tape                = TM2x·args.index·read.tape;              
    address_t index           = TM2x·args.index·read.index;         
    address_t element_n       = TM2x·args.index·read.element_byte_n;
    address_t element_byte_n  = TM2x·args.index·read.element_byte_n;
    void *dst_element_pt      = TM2x·args.index·read.dst_element_pt;    
    continuation nominal      = TM2x·args.index·read.nominal;
    continuation index_gt_n   = TM2x·args.index·read.index_gt_n;

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
      TM2x·args.index·to_pt.tape           = tape;
      TM2x·args.index·to_pt.index          = index;     
      TM2x·args.index·to_pt.element_byte_n = element_byte_n;
      TM2x·args.index·to_pt.pt             = &src_element_pt;              
      TM2x·args.index·to_pt.nominal        = &&index_nominal;        
      TM2x·args.index·to_pt.index_gt_n     = index_gt_n;
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
    TM2x *tape               = TM2x·args.index·to_pt.tape;
    address_t index          = TM2x·args.index·to_pt.index;
    address_t element_byte_n = TM2x·args.index·to_pt.element_byte_n;
    void **pt                = TM2x·args.index·to_pt.pt;
    continuation nominal     = TM2x·args.index·to_pt.nominal;
    continuation index_gt_n = TM2x·args.index·to_pt.index_gt_n;

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
     TM2x *tape                = TM2x·args.pop.tape;           
     address_t element_byte_n  = TM2x·args.pop.element_byte_n; 
     continuation nominal      = TM2x·args.pop.nominal;        
     continuation pop_last     = TM2x·args.pop.pop_last;       
     continuation alloc_fail   = TM2x·args.pop.alloc_fail;     
  } TM2x·args.pop.







  TM2x·push_bytes:{
    TM2x *tape              = TM2x·push_bytes.args.tape;           
    void *source_pt         = TM2x·push_bytes.args.source_pt;      
    address_t source_byte_n = TM2x·push_bytes.args.source_byte_n;  
    continuation nominal    = TM2x·push_bytes.args.nominal;        
    continuation alloc_fail = TM2x·push_bytes.args.alloc_fail;     
  }








  TM2x·args.push_elements.{
    TM2x *tape                = TM2x·args.push_elements.tape;
    void *base_pt             = TM2x·args.push_elements.base_pt;
    address_t element_n       = TM2x·args.push_elements.element_n;
    address_t element_byte_n  = TM2x·args.push_elements.element_byte_n;
    continuation nominal      = TM2x·args.push_elements.nominal;
    continuation alloc_fail   = TM2x·args.push_elements.alloc_fail;
    continuation index_gt_n    = TM2x·args.push_elements.index_gt_n;
   }

    TM2x·push:{
      TM2x *tape                 = TM2x·args.push.tape;
      void *element_base_pt      = TM2x·args.push.element_base_pt;
      address_t element_byte_n   = TM2x·args.push.element_byte_n;
      continuation nominal       = TM2x·args.push.nominal;
      continuation alloc_fail    = TM2x·args.push.alloc_fail;
      cend;
    }

  TM2x·args.push_TM2x.{
    TM2x *tape                = TM2x·args.push_TM2x.tape;
    TM2x *tape_source         = TM2x·args.push_TM2x.tape_source;
    continuation nominal      = TM2x·args.push_TM2x.nominal;
    continuation alloc_fail   = TM2x·args.push_TM2x.alloc_fail;
  }

  TM2x·read_pop:{
    TM2x *tape                 = TM2x·args.read_pop.TM2x *tape;            
    void *dst_element_pt       = TM2x·args.read_pop.void *dst_element_pt;  
    address_t element_byte_n   = TM2x·args.read_pop.address_t element_byte_n;
    continuation nominal       = TM2x·args.read_pop.continuation nominal;   
    continuation pop_last      = TM2x·args.read_pop.continuation pop_last;  
    continuation alloc_fail    = TM2x·args.read_pop.continuation alloc_fail;
    cend;
  }



  /*
    Dynamic allocation of the TM2x header.  For static allocation use the AllocStatic() macro.
    This does not allocate data for the array itself.
  */

  #ifdef TM2x·TEST
    extern address_t TM2x·test_after_allocation_n;
  #endif

  extern address_t TM2x·constructed_count;

  TM2x·resize_bytes:{
    // shorten the arg names, give the optimizer something more to do
    TM2x *tape = TM2x·args.resize_bytes.tape;
    address_t after_byte_n = TM2x·args.resize_bytes.after_byte_n;
    continuation nominal = TM2x·args.resize_bytes.nominal;
    continuation alloc_fail = TM2x·args.resize_bytes.alloc_fail;

    address_t before_alloc_n = binary_interval_inclusive_upper_bound(tape->byte_n);
    address_t after_alloc_n = binary_interval_inclusive_upper_bound(after_byte_n);

    if( after_alloc_n == before_alloc_n ){
      tape->byte_n = after_byte_n;
      continue_via_trampoline nominal;
    }

    char *after_base_pt;

    #include "CLib·mallocn·args.h"
    CLib·mallocn·args.pt      = (void **)&after_base_pt;
    CLib·mallocn·args.n       = after_alloc_n;
    CLib·mallocn·args.nominal = &&malloc_nominal;
    CLib·mallocn·args.fail    = &&malloc_fail; 
    #include "CLib·mallocn.h"
    continue_from CLib·mallocn;

    malloc_nominal:{
      #ifdef TM2x·TEST
        TM2x·test_after_allocation_n = after_alloc_n;
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

  #ifdef TM2x·TEST
    extern address_t TM2x·test_after_allocation_n;
  #endif

  extern address_t TM2x·constructed_count;

  TM2x·F_PREFIX continuation TM2x·resize_elements:{
    TM2x *tape                = TM2x·args.resize_elements.tape;
    address_t after_element_n = TM2x·args.resize_elements.after_element_n;
    address_t element_byte_n  = TM2x·args.resize_elements.element_byte_n;
    continuation nominal      = TM2x·args.resize_elements.nominal;
    continuation alloc_fail   = TM2x·args.resize_elements.alloc_fail;
    continuation index_gt_n    = TM2x·args.resize_elements.index_gt_n;

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
  #ifndef TM2X_TEXT_H
  #define TM2X_TEXT_H

  // ls *text.h | sed -e 's/^/#include "/g' | sed -e 's/ *$/"/g'
  #include "CLib·mallocn·text.h"
  #include "Continuation·text.h"
  #include "inclusive·mul_ib·text.h"
  #include "inclusive·text.h"
  #include "TM2x·alloc_heap·text.h"
  #include "TM2x·construct_bytes·text.h"
  #include "TM2x·construct_elements·text.h"
  #include "TM2x·construct_write_bytes·text.h"
  #include "TM2x·construct_write_elements·text.h"
  #include "TM2x·construct_write·text.h"
  #include "TM2x·construct_write_TM2x·text.h"
  #include "TM2x·copy_bytes·text.h"
  #include "TM2x·copy_elements·text.h"
  #include "TM2x·dealloc_heap·text.h"
  #include "TM2x·destruct·text.h"
  #include "TM2x·index·read·text.h"
  #include "TM2x·index·to_pt·text.h"
  #include "TM2x·misc·text.h"
  #include "TM2x·pop·text.h"
  #include "TM2x·push_bytes·text.h"
  #include "TM2x·push_elements·text.h"
  #include "TM2x·push·text.h"
  #include "TM2x·push_TM2x·text.h"
  #include "TM2x·read_pop·text.h"
  #include "TM2x·resize_bytes·text.h"
 #include "TM2x·resize_elements·text.h"
 #include "TM2x·text.h"
 #include "TM2x·write_bytes·text.h"

 #endif

 /*

 Copies a region stemming from src_pt to src_pt + byte_n on to the 
 dst tape starting from byte offset dst_byte_i.

 The only tape explicitly identified is the dst tape, so we say that
 we are writing the dst tape.

 */
 TM2x·write_bytes:{
           TM2x *dst             = TM2x·args.write_bytes.dst          
      address_t  dst_byte_i      = TM2x·args.write_bytes.dst_byte_i   
           void *src_pt          = TM2x·args.write_bytes.src_pt       
      address_t  byte_n          = TM2x·args.write_bytes.byte_n       
   continuation  nominal         = TM2x·args.write_bytes.nominal      
   continuation  alloc_fail      = TM2x·args.write_bytes.alloc_fail   
   continuation  src_index_gt_n   = TM2x·args.write_bytes.src_index_gt_n
   continuation  dst_index_gt_n   = TM2x·args.write_bytes.dst_index_gt_n
 }
