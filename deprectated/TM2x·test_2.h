/*
Copies bytes from one tape machine to another.  When instead we want to copy from a C array,
we may create a tape machine header that points to the C array, and then do the copy.


*/

  SQ·def(test_2){
    SQ·Sequence ah_dist ,check_copy ,nominal ,fail ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·check_copy ,SQ·nominal ,SQ·fail ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = T02x·alloc_array_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint fi = 0;  // count

    // ----------------------------------------
    // the source machine
    //
      char cs[] = {'h' ,'e' ,'l' ,'l' ,'o'};
      T02x·Tape src = { .base_pt = cs ,.n = 4};

    // ----------------------------------------
    // result tableau
    //
      address_t n = 4;  // input constant
      T02x·Tape *dst;             // result of alloc_Tape_heap, it gets distributed
      address_t offset = 0;  // input constant

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(ah  ,T02x·AllocTapeHeap   ,&&T02x·alloc_Tape_heap);
      SQ·make_Lnk(cb  ,T02x·AllocArray      ,&&T02x·alloc_array);
      SQ·make_Lnk(cpb ,T02x·CopyContiguous  ,&&T02x·copy_contiguous_bytes);
      SQ·make_Lnk(da  ,T02x·DeallocArray    ,&&T02x·dealloc_array);
      SQ·make_Lnk(dh  ,T02x·DeallocTapeHeap ,&&T02x·dealloc_Tape_heap);

      ah_lnks.nominal.sequence = &&ah_dist;
      ah_lnks.fail.sequence = &&fail;

      cb_lnks.nominal = AS(cpb_lnk ,SQ·Lnk);
      cb_lnks.fail_alloc.sequence = &&fail;

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
      f[fi++] = constructed_cnt == T02x·alloc_array_count;
      Result·Tallies·tally("test_2" ,&results ,f ,fi);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(test_3);
    } SQ·end(report)

  }SQ·end(test_2)
