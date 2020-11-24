/*
  alloc, constr4uct, destruct, and dealloc a T02x array, and see if the code crashes.

*/
  SQ·def(test_1){
    SQ·Sequence ah_dist ,nominal ,fail ,finish ,cleanup ,report;
    SQ·Sequence SQ·ah_dist ,SQ·nominal ,SQ·fail ,SQ·finish ,SQ·cleanup ,SQ·report;

    address_t malloc_cnt = MallocCounter·count;
    address_t constructed_cnt = T02x·alloc_array_count;
    Result·Tallies results ,*results_pt;
    results_pt = &results;
    Result·Tallies·init(results_pt);

    bool f[256]; // flags
    uint f·i = 0; 

    // ----------------------------------------
    // result tableau
    //
      address_t n = 9;
      address_t dn0 = 245;
      address_t dn1 = 191;
      T02x·Root tape;
      uint8_t *napt;

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(construct ,T0·Construct ,t02x.construct);
      SQ·make_Lnk(lengthen  ,T0·Lengthen  ,t02x.lengthen);
      SQ·make_Lnk(shorten   ,T0·Shorten   ,t02x.shorten);
      SQ·make_Lnk(destruct  ,T0·Destruct  ,t02x.destruct);

      construct_args.tape = (T0·Root *)&tape;
      construct_args.n = &n;
      construct_lnks.fail_alloc.sequence = &&fail;
      construct_lnks.nominal.sequence = &&init;

      lengthen_args.tape = (T0·Root *)&tape;
      lengthen_args.n = &dn0;
      lengthen_ress.new_area_pt = (char **)&napt;
      lengthen_lnks.fail_alloc.sequence = &&fail;
      lengthen_lnks.nominal.sequence = &&check_lengthen;

      shorten_args.tape = (T0·Root *)&tape;
      shorten_args.n = &dn1;
      shorten_lnks.fail_alloc.sequence = &&fail;
      shorten_lnks.nominal.sequence = &&check_shorten;

      destruct_args.tape = (T0·Root *)&tape;
      destruct_lnks.nominal.sequence = &&report;

    SQ·continue_indirect(construct_lnk);

    SQ·def(fail){
      f[f·i++] = false;
      SQ·continue(report);
    }SQ·end(fail);

    SQ·def(init){
      f[f·i++] = Test·CLib·allocation_n == 15;
      uint8_t i = 0;
      uint8_t *pt0 = (uint8_t *)AS(tape ,T02x·Root).base_pt;
      uint8_t *pt1 = pt0 + AS(tape ,T02x·Root).n;
      lp0:{
        *pt0 = i;
        if(pt0 == pt1) goto lp0_end;
        pt0++;
        i++;
        goto lp0;
        lp0_end:;
      }
      SQ·continue_indirect(lengthen_lnk);
    }SQ·end(init);

    SQ·def(check_lengthen){
      f[f·i++] = Test·CLib·allocation_n == 255;
      f[f·i++] = AS(tape ,T02x·Root).n == 255;

      // init extension
      {
        uint8_t i = 10;
        uint8_t *pt0 = napt;
        uint8_t *pt1 = pt0 + dn0;
        lp1:{
          *pt0 = i;
          if(pt0 == pt1) goto lp1_end;
          pt0++;
          i++;
          goto lp1;
          lp1_end:;
        }}

      // check values for whole array
      {
        uint8_t i = 0;
        uint8_t *pt0 = (uint8_t *)AS(tape ,T02x·Root).base_pt;
        uint8_t *pt1 = pt0 + 255;
        lp2:{
          if(*pt0 != i) f[f·i++] = false;
          if(pt0 == pt1) goto lp2_end;
          pt0++;
          i++;
          goto lp2;
          lp2_end:;
        }}
      
      SQ·continue_indirect(shorten_lnk);
    }SQ·end(check_lengthen);

    SQ·def(check_shorten){
      f[f·i++] = Test·CLib·allocation_n == 63;
      f[f·i++] = AS(tape ,T02x·Root).n == 63;

      // check values for whole array
      {
        uint8_t i = 0;
        uint8_t *pt0 = (uint8_t *)AS(tape ,T02x·Root).base_pt;
        uint8_t *pt1 = pt0 + 63;
        lp3:{
          if(*pt0 != i) f[f·i++] = false;
          if(pt0 == pt1) goto lp3_end;
          pt0++;
          i++;
          goto lp3;
          lp3_end:;
        }}
      SQ·continue_indirect(destruct_lnk);
    }SQ·end(check_shorten);

    SQ·def(report){
      f[f·i++] = malloc_cnt == MallocCounter·count;
      f[f·i++] = constructed_cnt == T02x·alloc_array_count;
      Result·Tallies·tally("test_1" ,&results ,f ,f·i);
      Result·Tallies·accumulate(accumulated_results_pt ,&results);
      SQ·continue(tests_finished);
    } SQ·end(report);

  }SQ·end(test_1)
