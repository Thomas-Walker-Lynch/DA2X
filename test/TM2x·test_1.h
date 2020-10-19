/*
Similar to test_0, but uses alloc_array_elements instead of alloc_array_elements to construct
the array.

*/

  // allocate, construct, destruct, deallocate an array
  SQ·def(test_1){
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
      address_t n_Element = 9;
      address_t element_n_Byte = 3; // extent of 32 bit int in elements
      TM2x·Tape *tape; // set by alloc_Tape_heap, then distributed

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(ah  ,TM2x·AllocTapeHeap   ,&&TM2x·alloc_Tape_heap);
      SQ·make_Lnk(ce  ,TM2x·AllocArrayElements ,&&TM2x·alloc_array_elements);
      SQ·make_Lnk(da  ,TM2x·DeallocArray    ,&&TM2x·dealloc_array);
      SQ·make_Lnk(dh  ,TM2x·DeallocTapeHeap ,&&TM2x·dealloc_Tape_heap);

      ah_lnks.nominal.sequence = &&ah_dist;
      ah_lnks.fail.sequence = &&fail;

      ce_lnks.nominal = AS(da_lnk ,SQ·Lnk);
      ce_lnks.alloc_fail.sequence = &&fail;

      da_lnks.nominal = AS(dh_lnk ,SQ·Lnk);
      dh_lnks.nominal.sequence = &&nominal;


    // ----------------------------------------
    // sequence results point into the tableau
    //
      ah_ress.tape = &tape;

    // ----------------------------------------
    // seqeuence args point into the tableau
    //
      ce_args.n_Element = &n_Element;
      ce_args.element_n_Byte = &element_n_Byte;

      // The alloc_Tape_heap result is a pointer to the allocation.  The distribution sequence that
      // follows it distributes this pointer to the parameters of other rourtines. Consequently
      // those parameters are not set here.

    SQ·continue_indirect(ah_lnk);

    SQ·def(ah_dist){ // distribute the allocation
      ce_args.tape = tape;
      da_args.tape = tape;
      dh_args.tape = tape;
      SQ·continue_indirect(ce_lnk); // continue to construct elements
    }SQ·end(ah_dist);

    SQ·def(nominal){
      f[i++] = Test·CLib·allocation_n == 63;
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
      Result·Tallies·tally("test_1" ,&results ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(test_2);
    } SQ·end(report)

  }SQ·end(test_1)
