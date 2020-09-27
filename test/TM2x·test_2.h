/*
Copies bytes from one tape machine to another.  When instead we want to copy from a C array,
we may create a tape machine header that points to the C array, and then do the copy.


*/

  SQ·def(test_2){
    SQ·Sequence ah_dist ,check_copy ,nominal ,fail ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·check_copy ,SQ·nominal ,SQ·fail ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = TM2x·constructed_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);
    bool f[256]; // flags
    uint fi = 0;  // count

    // ----------------------------------------
    // the source machine
    //
      char cs[] = {'h' ,'e' ,'l' ,'l' ,'o'};
      TM2x src = { .base_pt = cs ,.byte_n = 4};

    // ----------------------------------------
    // result tableau
    //
      address_t byte_n = 4;
      TM2x *dst; // set by alloc_heap, then distributed
      address_t offset = 0;

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

      TM2x·ConstructBytes·Args cb_args;
      TM2x·ConstructBytes·Lnks cb_lnks;
      TM2x·ConstructBytes·Lnk  cb_lnk;
      cb_lnk.args = &cb_args;
      cb_lnk.lnks = &cb_lnks;
      cb_lnk.sequence = &&TM2x·construct_bytes;

      TM2x·CopyBytes·Args cpb_args;
      TM2x·CopyBytes·Lnks cpb_lnks;
      TM2x·CopyBytes·Lnk  cpb_lnk;
      cpb_lnk.args = &cpb_args;
      cpb_lnk.lnks = &cpb_lnks;
      cpb_lnk.sequence = &&TM2x·copy_bytes;

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
      ah_ress.tm2x = &dst;

    // ----------------------------------------
    // seqeuence args point into the tableau
    //
      cb_args.byte_n = &byte_n;
     
      cpb_args.src = &src;
      cpb_args.src_byte_0 = &offset;
      cpb_args.dst_byte_0 = &offset;
      cpb_args.byte_n = &byte_n;

      // .dst arguments are assigned in the ah_dist sequence

    SQ·continue_indirect(ah_lnk);

    SQ·def(ah_dist){ // distribute the allocation
      cb_args.tm2x = dst;
      cpb_args.dst = dst;
      da_args.tm2x = dst;
      dh_args.tm2x = dst;
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
      f[fi++] = constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_0" ,&results ,f ,fi);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(tests_finished);
    } SQ·end(report)

  }SQ·end(test_2)
