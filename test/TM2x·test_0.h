/*
Allocates a TM2x·Tape header struct on the heap.  Constructs an array.  Destructs the array.
Deallocates the header.


*/

  // allocate, construct, destruct, deallocate an array
  SQ·def(test_0){
    SQ·Sequence ah_dist ,nominal ,fail ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·nominal ,SQ·fail ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = TM2x·alloc_array_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count

    // ----------------------------------------
    // result tableau
    //
      address_t n = 9;
      TM2x·Tape *tape; // will point to a heap allocated Tape structure.

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(ah  ,TM2x·AllocTapeHeap   ,&&TM2x·alloc_Tape_heap);
      SQ·make_Lnk(aa  ,TM2x·AllocArray      ,&&TM2x·alloc_array);
      SQ·make_Lnk(da  ,TM2x·DeallocArray    ,&&TM2x·dealloc_array);
      SQ·make_Lnk(dh  ,TM2x·DeallocTapeHeap ,&&TM2x·dealloc_Tape_heap);

      ah_ress.tape = &tape;
      ah_lnks.nominal.sequence = &&ah_dist;
      ah_lnks.fail.sequence = &&fail;

      aa_args.n = &n;
      aa_lnks.nominal = AS(da_lnk ,SQ·Lnk);
      aa_lnks.alloc_fail.sequence = &&fail;

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
    // compile time. TM2x·test_1 has an example where the tape is placed directly on the
    // result tableau instead of on the heap.
    SQ·def(ah_dist){ 
      aa_args.tape = tape;
      da_args.tape = tape;
      dh_args.tape = tape;
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
      f[i++] = constructed_cnt == TM2x·alloc_array_count;
      Result·Tallies·tally("test_0" ,&results ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(test_1);
    } SQ·end(report)

  }SQ·end(test_0)
