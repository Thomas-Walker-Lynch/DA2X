/*

  Instances of the T02x root struct are created using C methods for allocation. 

 ‘construction’ initializes the root struct with a newly allocated data array. 
 (Initialization means to write data to the array for the first time.)

 ‘destruction’ frees the data array from the heap. If a destructed T02x root
 struct is to be used again, it must be ‘constructed’ again first.

*/

// 'thread static' allocation class
address_t T02x·alloc_array_count = 0;

// allocates the array data on the heap, attaches it to the root struct
//
  SQ·def(T02x·construct){
    T02x·alloc_array_count++; // to assist with debugging
    T0·Construct·Lnk *lnk = (T0·Construct·Lnk *)SQ·lnk;
    T02x·Root *tape = (T02x·Root *) lnk->args->tape;
    address_t n = *lnk->args->n;

    address_t alloc_n = T02x·alloc_n(n);
    if( alloc_n == address_t_n ){
      SQ·continue_indirect(lnk->lnks->fail_alloc);
    }
    #if TEST
      Test·CLib·allocation_n = alloc_n;
    #endif
    void *base_pt = malloc(alloc_n + 1);
    if( !base_pt ){
      SQ·continue_indirect(lnk->lnks->fail_alloc);
    }
    tape->n = n;
    tape->base_pt = base_pt;
    SQ·continue_indirect(lnk->lnks->nominal);

  } SQ·end(T02x·construct);

// After the header is destructed it may not be reused unless it is re-constructialized.
//
  SQ·def(T02x·destruct){
    T02x·alloc_array_count--; // to assist with debugging
    T0·Destruct·Lnk *lnk = (T0·Destruct·Lnk *)SQ·lnk;
    T02x·Root *tape = (T02x·Root *) lnk->args->tape;
    free(tape->base_pt);
    SQ·continue_indirect(lnk->lnks->nominal);  
  } SQ·end(T02x·destruct);

/* When operating on a tape, we often create a second temporary tape to accumulate changes
   on. When finished we move the contents of the temporary tape back to the tape we
   are operating on.  This instruction sequence does the move back.  Hence the ‘src’
   will be the temporary tape, and the ‘dst’ the tape being worked on.  After the move, the
   src tape would have to be constructialized if it is to be used again.
*/
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

/*
   `*lnk->args->n` is the extent of the requested extension area. If the extended tape
   fits within the allocation then all we have to do is modify tape->n.  Otherwise we have
   to make a new larger allocation and move the original data to it.

   After lengthening the tape the extension area is unitialized.  By contract the 
   programmer may not read it before having written it.

   We return a pointer to the first element in the extension area. There are caveats
   regarding the use of this pointer.  See the docs.
   
   Extents are positive integers that range from zero to address_t_n.  Hence 
   the expression, `address_t_n - *lnk->args->n` will never underflow nor overflow.

   The expression    

      `tape->n > address_t_n - *lnk->args->n - 1 ` 

   has the same mathematical meaning as:

     `tape->n + 1 + *lnk->args->n > address_t_n' 

   I didn't write it this second way because *lnk->args->n + tape->n` can overflow. In
   the second form it is clear that the question being asked is if this extension
   would causes us to overflow the address space.

   We will use >= instead of > to avoid the n + 1 problem converting an extent to a length
   for malloc.

*/
  SQ·def(T02x·lengthen){
    SQ·Sequence copy_array_data ,SQ·copy_array_data;
    T0·Lengthen·Lnk *lnk = (T0·Lengthen·Lnk *)SQ·lnk;
    T02x·Root *tape = (T02x·Root *) lnk->args->tape;

    if( tape->n >= address_t_n - *lnk->args->n ){
      SQ·continue_indirect(lnk->lnks->fail_alloc);
    }

    address_t alloc_n = T02x·alloc_n(tape->n);
    address_t resized_n =  *lnk->args->n + tape->n + 1;
    address_t resized_alloc_n = T02x·alloc_n(resized_n);
    if( alloc_n == resized_alloc_n ){
      *lnk->ress->new_area_pt = tape->base_pt + tape->n + 1;
      tape->n = resized_n;
      SQ·continue_indirect(lnk->lnks->nominal);
    }

    #if TEST
      Test·CLib·allocation_n = resized_alloc_n;
    #endif
    void *base_pt = malloc(resized_alloc_n + 1);
    if( !base_pt ){
      SQ·continue_indirect(lnk->lnks->fail_alloc);
    }
    *lnk->ress->new_area_pt = base_pt + tape->n + 1;
    memcpy(base_pt ,tape->base_pt ,tape->n + 1);

    free(tape->base_pt);
    tape->base_pt = base_pt;
    tape->n = resized_n;
    SQ·continue_indirect(lnk->lnks->nominal);

  } SQ·end(T02x·lengthen);

/*
   `*lnk->args->n` may be thought of as an extension area to be removed. Just like
   we were undoing an length operation that added an extension area of extent n.

*/
SQ·def(T02x·shorten){
  T0·Shorten·Lnk *lnk = (T0·Shorten·Lnk *)SQ·lnk;
  T02x·Root *tape = (T02x·Root *) lnk->args->tape;

  if( *lnk->args->n == tape->n ){
    SQ·continue_indirect(lnk->lnks->fail_empty);
  }
  if( *lnk->args->n > tape->n ){
    SQ·continue_indirect(lnk->lnks->fail_underflow);
  }

  address_t alloc_n = T02x·alloc_n(tape->n);
  address_t resized_n = tape->n - *lnk->args->n - 1;
  address_t resized_alloc_n = T02x·alloc_n(resized_n);

  if( alloc_n == resized_alloc_n ){
    tape->n = resized_n;
    SQ·continue_indirect(lnk->lnks->nominal);
  }

  // resized_alloc_n will be smaller than alloc_n, so it will not overflow by adding 1
  // resized_n will be less than n ...
  #if TEST
    Test·CLib·allocation_n = resized_alloc_n;
  #endif
  void *base_pt = malloc(resized_alloc_n + 1);
  if( !base_pt ){
    SQ·continue_indirect(lnk->lnks->fail_alloc);
  }
  memcpy(base_pt ,tape->base_pt ,resized_n + 1);
  free(tape->base_pt);
  tape->base_pt = base_pt;
  tape->n = resized_n;
  SQ·continue_indirect(lnk->lnks->nominal);

} SQ·end(T02x·shorten);



T0·Iface t02x;
t02x.construct  = &&T02x·construct;
t02x.destruct   = &&T02x·destruct;
t02x.move_array = &&T02x·move_array;            
t02x.lengthen   = &&T02x·lengthen;              
t02x.shorten    = &&T02x·shorten;

