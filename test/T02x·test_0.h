/*
Allocates a T02x·Tape header struct on the heap.  Constructs an array.  Destructs the array.
Deallocates the header.


*/

  // allocate, construct, destruct, deallocate an array
  SQ·def(test_0){
    SQ·Sequence ah_dist ,nominal ,fail ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·nominal ,SQ·fail ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = T02x·alloc_array_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count

    // ----------------------------------------
    // result tableau
    //
      address_t n = 9;
      T02x·Tape *tape; // will point to a heap allocated Tape structure.

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(ah  ,T0·AllocTapeHeap   ,&&T02x·alloc_Tape_heap);
      SQ·make_Lnk(aa  ,T0·AllocArray      ,&&T02x·alloc_array);
      SQ·make_Lnk(da  ,T0·DeallocArray    ,&&T02x·dealloc_array);
      SQ·make_Lnk(dh  ,T0·DeallocTapeHeap ,&&T02x·dealloc_Tape_heap);

      ah_ress.tape = (T0·Tape **)&tape;
      ah_lnks.nominal.sequence = &&ah_dist;
      ah_lnks.fail.sequence = &&fail;

      aa_args.n = &n;
      aa_lnks.nominal = AS(da_lnk ,SQ·Lnk);
      aa_lnks.fail_alloc.sequence = &&fail;

      da_lnks.nominal = AS(dh_lnk ,SQ·Lnk);
      dh_lnks.nominal.sequence = &&nominal;


    SQ·continue_indirect(ah_lnk);

    // Instruction sequences such as alloc_array, dealloc_array, and even
    // dalloc_tape_heap, gather a tape argument.  Hence their args structure will be
    // initialized with a pointer to a tape structure. In this test we allocate said tape
    // structure on the heap.  Thus we may only initialize the relevant args structures
    // after the tape has been allocated.  With a literal read of our code, the allocation
    // of the tape structure and the initialization of the arg pointers will occur at run
    // time, but an astute optimizer would notice that in this case both may be done at
    // compile time. T02x·test_1 has an example where the tape is placed directly on the
    // result tableau instead of on the heap.
    SQ·def(ah_dist){ 
      aa_args.tape = (T0·Tape *)tape;
      da_args.tape = (T0·Tape *)tape;
      dh_args.tape = (T0·Tape *)tape;
      SQ·continue_indirect(aa_lnk); // continue to allocate the array
    }SQ·end(ah_dist);

    SQ·def(nominal){
      f[i++] = Test·CLib·allocation_n == 15;
      f[i++] = true;
      SQ·continue(report);
    }SQ·end(nominal);

    SQ·def(fail){
      f[i++] = false;
      SQ·continue(report);
    } SQ·end(fail);

    SQ·def(report){
      f[i++] = malloc_cnt == MallocCounter·count;
      f[i++] = constructed_cnt == T02x·alloc_array_count;
      Result·Tallies·tally("test_0" ,&results ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(test_1);
    } SQ·end(report)

  }SQ·end(test_0)
