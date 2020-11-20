/*
  alloc, constr4uct, destruct, and dealloc a T02x array, and see if the code crashes.

*/
  SQ·def(test_0){
    SQ·Sequence ah_dist ,nominal ,fail ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·nominal ,SQ·fail ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = T02x·alloc_array_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);

    bool f[256]; // flags
    f[0] = false;
    f[1] = false;
    uint f·i = 2; 

    // ----------------------------------------
    // result tableau
    //
      address_t n = 9;
      T0·Root *tape = malloc(sizeof(T02x·Root));

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(construct ,T0·Construct ,t02x.construct);
      SQ·make_Lnk(destruct  ,T0·Destruct  ,t02x.destruct);

      construct_args.tape = tape;
      construct_args.n = &n;
      construct_lnks.fail_alloc.sequence = &&fail;
      construct_lnks.nominal.sequence = &&nominal;

      destruct_args.tape = tape;
      destruct_lnks.nominal.sequence = &&finish;

    SQ·continue_indirect(construct_lnk);

    SQ·def(fail){
      f[f·i++] = false;
      SQ·continue(finish);
    }SQ·end(fail);

    SQ·def(nominal){
      f[0] = true;
      f[f·i++] = Test·CLib·allocation_n == 15;
      SQ·continue_indirect(destruct_lnk);
    }SQ·end(nominal);

    SQ·def(finish){
      f[1] = true;
      free(tape);
      SQ·continue(report);
    }SQ·end(finish);

    SQ·def(report){
      f[f·i++] = malloc_cnt == MallocCounter·count;
      f[f·i++] = constructed_cnt == T02x·alloc_array_count;
      Result·Tallies·tally("test_0" ,&results ,f ,f·i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(tests_finished);
    } SQ·end(report);

  }SQ·end(test_0)
