/*
Copies elements from one machine to another.

Currnenly this is just a copy of the copy_contiguous_bytes test.

*/

  SQ·def(test_3){
    SQ·Sequence ah_dist ,check_copy ,nominal ,fail ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·check_copy ,SQ·nominal ,SQ·fail ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = TM2x·alloc_array_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint fi = 0;  // count

    // ----------------------------------------
    // the source machine
    //
      char cs[] = {'h' ,'e' ,'l' ,'l' ,'o'};
      TM2x·Tape src = { .base_pt = cs ,.n = 4};

    // ----------------------------------------
    // result tableau
    //
      address_t n = 4;  // input constant
      TM2x·Tape *dst;    // result of alloc_Tape_heap, it gets distributed
      address_t offset = 0;  // input constant

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(ah  ,TM2x·AllocTapeHeap   ,&&TM2x·alloc_Tape_heap);
      SQ·make_Lnk(cb  ,TM2x·AllocArray      ,&&TM2x·alloc_array);
      SQ·make_Lnk(cpb ,TM2x·CopyContiguous  ,&&TM2x·copy_contiguous_bytes);
      SQ·make_Lnk(da  ,TM2x·DeallocArray    ,&&TM2x·dealloc_array);
      SQ·make_Lnk(dh  ,TM2x·DeallocTapeHeap ,&&TM2x·dealloc_Tape_heap);

      ah_lnks.nominal.sequence = &&ah_dist;
      ah_lnks.fail.sequence = &&fail;

      cb_lnks.nominal = AS(cpb_lnk ,SQ·Lnk);
      cb_lnks.alloc_fail.sequence = &&fail;

      cpb_lnks.nominal.sequence = &&check_copy;
      cpb_lnks.src_index_gt_n.sequence = &&fail;
      cpb_lnks.dst_index_gt_n.sequence = &&fail;

      da_lnks.nominal = AS(dh_lnk ,SQ·Lnk);
      dh_lnks.nominal.sequence = &&nominal;


    // ----------------------------------------
    // sequence results point into the tableau
    //
      ah_ress.tape = &dst;

    // ----------------------------------------
    // seqeuence args point into the tableau
    //
      cb_args.n = &n;
     
      cpb_args.src = &src;
      cpb_args.src_0 = &offset;
      cpb_args.dst_0 = &offset;
      cpb_args.n = &n;

      // .dst arguments are assigned in the ah_dist sequence

    SQ·continue_indirect(ah_lnk);

    SQ·def(ah_dist){ // distribute the allocation
      cb_args.tape = dst;
      cpb_args.dst = dst;
      da_args.tape = dst;
      dh_args.tape = dst;
      SQ·continue_indirect(cb_lnk); // continue to construct bytes
    }SQ·end(ah_dist);

    SQ·def(check_copy){
      f[fi++] = !bcmp(dst->base_pt ,cs ,5);
      SQ·continue_indirect(da_lnk); // continue to construct bytes
    }SQ·end(check_copy);

    SQ·def(nominal){
      f[fi++] = Test·CLib·allocation_n == 15;
      f[fi++] = true;
      SQ·continue(report);
    }SQ·end(nominal);

    SQ·def(fail){
      f[fi++] = false;
      SQ·continue(report);
    } SQ·end(fail);

    SQ·def(report){
      f[fi++] = malloc_cnt == MallocCounter·count;
      f[fi++] = constructed_cnt == TM2x·alloc_array_count;
      Result·Tallies·tally("test_3" ,&results ,f ,fi);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(tests_finished);
    } SQ·end(report)

  }SQ·end(test_3)
