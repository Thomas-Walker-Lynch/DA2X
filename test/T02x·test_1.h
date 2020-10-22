/*
Similar to test_0, but uses alloc_array_elements instead of alloc_array_elements to construct
the array.

*/

  // allocate, construct, destruct, deallocate an array
  SQ·def(test_1){
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
      address_t n_Element = 9;
      address_t element_n_Byte = 3; // extent of 32 bit int in elements
      T02x·Tape *tape;  // will point to a heap allocated Tape structure.

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(ah  ,T02x·AllocTapeHeap   ,&&T02x·alloc_Tape_heap);
      SQ·make_Lnk(aa  ,T02x·AllocArrayElements ,&&T02x·alloc_array_elements);
      SQ·make_Lnk(da  ,T02x·DeallocArray    ,&&T02x·dealloc_array);
      SQ·make_Lnk(dh  ,T02x·DeallocTapeHeap ,&&T02x·dealloc_Tape_heap);

      ah_ress.tape = &tape;
      ah_lnks.nominal.sequence = &&ah_dist;
      ah_lnks.fail.sequence = &&fail;

      aa_args.n_Element = &n_Element;
      aa_args.element_n_Byte = &element_n_Byte;
      aa_lnks.nominal = AS(da_lnk ,SQ·Lnk);
      aa_lnks.fail_alloc.sequence = &&fail;

      da_lnks.nominal = AS(dh_lnk ,SQ·Lnk);
      dh_lnks.nominal.sequence = &&nominal;

    SQ·continue_indirect(ah_lnk);

    // initialize our tape argument from the heap
    SQ·def(ah_dist){ 
      aa_args.tape = tape;
      da_args.tape = tape;
      dh_args.tape = tape;
      SQ·continue_indirect(aa_lnk); // continue to construct elements
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
      f[i++] = constructed_cnt == T02x·alloc_array_count;
      Result·Tallies·tally("test_1" ,&results ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(test_2);
    } SQ·end(report)

  }SQ·end(test_1)
