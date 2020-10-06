/*
Similar to test_0, but uses construct_elements instead of construct_elements to construct
the array.

*/

  // allocate, construct, destruct, deallocate an array
  SQ·def(test_1){
    SQ·Sequence ah_dist ,nominal ,fail ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·nominal ,SQ·fail ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = TM2x·constructed_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint i = 0;  // count

    // ----------------------------------------
    // result tableau
    //
      address_t element_n = 9;
      address_t element_byte_n = 3; // extent of 32 bit int in elements
      TM2x *tm2x; // set by alloc_heap, then distributed

    // ----------------------------------------
    // Links
    //
      TM2x·AllocHeap·Args ah_args;
      TM2x·AllocHeap·Ress ah_ress;
      TM2x·AllocHeap·Lnks ah_lnks;
      TM2x·AllocHeap·Lnk  ah_lnk;
      ah_lnk.args = &ah_args;
      ah_lnk.ress = &ah_ress;
      ah_lnk.lnks = &ah_lnks;
      ah_lnk.sequence = &&TM2x·alloc_heap;

      TM2x·ConstructElements·Args ce_args;
      TM2x·ConstructElements·Lnks ce_lnks;
      TM2x·ConstructElements·Lnk  ce_lnk;
      ce_lnk.args = &ce_args;
      ce_lnk.lnks = &ce_lnks;
      ce_lnk.sequence = &&TM2x·construct_elements;

      TM2x·Destruct·Args       da_args;
      TM2x·Destruct·Lnks       da_lnks;
      TM2x·Destruct·Lnk        da_lnk;
      da_lnk.args = &da_args;
      da_lnk.lnks = &da_lnks;
      da_lnk.sequence = &&TM2x·destruct;

      TM2x·DeallocHeap·Args    dh_args;
      TM2x·DeallocHeap·Lnks    dh_lnks;
      TM2x·DeallocHeap·Lnk     dh_lnk;
      dh_lnk.args = &dh_args;
      dh_lnk.lnks = &dh_lnks;
      dh_lnk.sequence = &&TM2x·dealloc_heap;

      ah_lnks.nominal.sequence = &&ah_dist;
      ah_lnks.fail.sequence = &&fail;

      ce_lnks.nominal = AS(da_lnk ,SQ·Lnk);
      ce_lnks.alloc_fail.sequence = &&fail;

      da_lnks.nominal = AS(dh_lnk ,SQ·Lnk);
      dh_lnks.nominal.sequence = &&nominal;


    // ----------------------------------------
    // sequence results point into the tableau
    //
      ah_ress.tm2x = &tm2x;

    // ----------------------------------------
    // seqeuence args point into the tableau
    //
      ce_args.element_n = &element_n;
      ce_args.element_byte_n = &element_byte_n;

      // The alloc_heap result is a pointer to the allocation.  The distribution sequence that
      // follows it distributes this pointer to the parameters of other rourtines. Consequently
      // those parameters are not set here.

    SQ·continue_indirect(ah_lnk);

    SQ·def(ah_dist){ // distribute the allocation
      ce_args.tm2x = tm2x;
      da_args.tm2x = tm2x;
      dh_args.tm2x = tm2x;
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
      f[i++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_1" ,&results ,f ,i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(test_2);
    } SQ·end(report)

  }SQ·end(test_1)
