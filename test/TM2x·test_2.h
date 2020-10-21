/*
Allocates a tape, then resizes it.


*/

  // allocate, construct, destruct, dealloc an array
  SQ·def(test_2){
    SQ·Sequence ah_dist ,initialize ,extend ,check ,fail ,report;
    SQ·Sequence SQ·ah_dist ,SQ·initialize ,SQ·extend ,SQ·check ,SQ·fail ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = TM2x·alloc_array_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint fi = 0;  // count

    // ----------------------------------------
    // result tableau
    //
      address_t n0 = 9;
      address_t n1 = 18;
      TM2x·Tape tape;

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(allocate   ,TM2x·AllocArray   ,&&TM2x·alloc_array);
      SQ·make_Lnk(resize     ,TM2x·Resize       ,&&TM2x·resize);
      SQ·make_Lnk(dealloc ,TM2x·DeallocArray ,&&TM2x·dealloc_array);

      allocate_args.tape = &tape;
      allocate_args.n = &n0;
      allocate_lnks.nominal.sequence = &&initialize;
      allocate_lnks.fail_alloc.sequence = &&fail;

      resize_args.tape = &tape;
      resize_args.n = &n1;
      resize_lnks.nominal.sequence = &&extend;
      resize_lnks.fail_alloc.sequence = &&fail;

      dealloc_args.tape = &tape;
      dealloc_lnks.nominal.sequence = &&report;

    SQ·continue_indirect(allocate_lnk);

    SQ·def(initialize){
      f[fi++] = Test·CLib·allocation_n == power_2_extent(9);

      // inclusive bounds loop (missing from  C)
      uint8_t i = 0;
      uint8_t *pt = (uint8_t *)tape.base_pt;
      lp0:
        *pt = i;
        if( i == tape.n ) goto lp0_end;
        pt++;
        i++;
        goto lp0;
      lp0_end:

      SQ·continue_indirect(resize_lnk);
    }SQ·end(initialize);

    SQ·def(extend){
      f[fi++] = Test·CLib·allocation_n == power_2_extent(18);

      uint8_t i = 0;
      uint8_t *pt = (uint8_t *)tape.base_pt;
      do{
        f[fi++] = *pt == i;
        pt++;
        i++;
      }while( i <= 9 );
      lp1:
        *pt = i;
        if( i == 18 ) goto lp1_end;
        pt++;
        i++;
        goto lp1;
      lp1_end:
      SQ·continue(check);

    }SQ·end(extend);

    SQ·def(check){
      uint8_t i = 0;
      uint8_t *pt = (uint8_t *)tape.base_pt;
      lp2:
        f[fi++] = *pt == i;
        if( i == 18 ) goto lp2_end;
        pt++;
        i++;
        goto lp2;
      lp2_end:
      SQ·continue_indirect(dealloc_lnk);
    }SQ·end(check);

    SQ·def(fail){
      f[fi++] = false;
      SQ·continue(report);
    } SQ·end(fail);

    SQ·def(report){
      f[fi++] = malloc_cnt == MallocCounter·count;
      f[fi++] = constructed_cnt == TM2x·alloc_array_count;

      Result·Tallies·tally("test_2" ,&results ,f ,fi);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(tests_finished);
    } SQ·end(report)

  }SQ·end(test_2)
