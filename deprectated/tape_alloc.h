#if 0
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

#endif

#if 0
t02x.alloc_Tape_heap      = &&T02x·alloc_Tape_heap;
t02x.alloc_array          = &&T02x·alloc_array;           
t02x.alloc_array_elements = &&T02x·alloc_array_elements;  
t02x.dealloc_array        = &&T02x·dealloc_array;         
t02x.dealloc_Tape_heap    = &&T02x·dealloc_Tape_heap;     
#endif

typedef struct {
#if 0
  SQ·Ptr alloc_Tape_heap; // a convenience function
  SQ·Ptr alloc_array;
  SQ·Ptr alloc_array_elements;
  SQ·Ptr dealloc_array;
  SQ·Ptr dealloc_Tape_heap;
#endif
  SQ·Ptr init;
  SQ·Ptr move_array;
  SQ·Ptr lengthen;
  SQ·Ptr shorten;
} T0·Iface;


#if 0

typedef struct{
} T0·AllocTapeHeap·Args;
typedef struct{
  T0·Root **tape;
} T0·AllocTapeHeap·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail;
} T0·AllocTapeHeap·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·AllocTapeHeap·Args *args;
  T0·AllocTapeHeap·Ress *ress;
  T0·AllocTapeHeap·Lnks *lnks;
} T0·AllocTapeHeap·Lnk;

typedef struct{
  T0·Root *tape;
  address_t *n;   // extent of the array, in bytes
} T0·AllocArray·Args;
typedef struct{
} T0·AllocArray·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk fail_alloc;
} T0·AllocArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·AllocArray·Args *args;
  T0·AllocArray·Ress *ress;
  T0·AllocArray·Lnks *lnks;
} T0·AllocArray·Lnk;

typedef struct{
  T0·Root *tape;
  address_t *n_Element;  // extent of the array, in elements
  address_t *element_n_Byte; // extent of the element, in bytes
} T0·AllocArrayElements·Args;
typedef struct{
} T0·AllocArrayElements·Ress;
typedef struct{
  SQ·Lnk nominal;
  SQ·Lnk index_gt_n;
  SQ·Lnk fail_alloc;
} T0·AllocArrayElements·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·AllocArrayElements·Args *args;
  T0·AllocArrayElements·Ress *ress;
  T0·AllocArrayElements·Lnks *lnks;
} T0·AllocArrayElements·Lnk;

typedef struct{
  T0·Root *tape;
} T0·DeallocArray·Args;
typedef struct{
} T0·DeallocArray·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·DeallocArray·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·DeallocArray·Args *args;
  T0·DeallocArray·Ress *ress;
  T0·DeallocArray·Lnks *lnks;
} T0·DeallocArray·Lnk;

typedef struct{
  T0·Root *tape;
} T0·DeallocTapeHeap·Args;
typedef struct{
} T0·DeallocTapeHeap·Ress;
typedef struct{
  SQ·Lnk nominal;
} T0·DeallocTapeHeap·Lnks;
typedef struct{
  SQ·Ptr sequence;
  T0·DeallocTapeHeap·Args *args;
  T0·DeallocTapeHeap·Ress *ress;
  T0·DeallocTapeHeap·Lnks *lnks;
} T0·DeallocTapeHeap·Lnk;
#endif
