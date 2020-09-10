#if 0

  // Sort of smoke tests, allocates and constructs and array of elements, checks the allocation size.
  // This the first that makes use of a context pad.
  test_1:{
    Conveyance nominal ,fail ,cleanup ,report;

    Conveyance·swap();
    LC(lc ,test_args, 0);
    CX(cx ,TM2x·Test ,test_0);
    cx->malloc_cnt = MallocCounter·count;
    cx->constructed_cnt = TM2x·constructed_count;
    cx->i = 0;
    cx->continuation = lc->continuation;
    Result·Tallies·init(&cx->results);

    //allocate
    AR(ar ,TM2x·alloc_heap ,0);
    ar->tape = &cx->tape;
    ar->nominal = &&nominal;
    ar->fail = &&fail;
    continue_from TM2x·alloc_heap;

    nominal:{
      Conveyance nominal;
      cx->f[cx->i++] = true;

      //construct
      AR(ar ,TM2x·construct_elements ,0);
      ar->tape = cx->tape;
      ar->element_n = 63;
      ar->element_byte_n = 3;
      ar->nominal = &&nominal;
      ar->index_gt_n = &&fail;
      ar->alloc_fail = &&fail;
      continue_from TM2x·construct_elements;

      nominal:{
        cx->f[cx->i++] = Test·CLib·allocation_n == 255;
        continue_from cleanup;
        cend;
      }
      cend;
    }

    fail:{
      cx->f[cx->i++] = false;
      continue_from cleanup;
      cend;
    }

    cleanup:{
      // destruct and deallocate
      AR(ar ,TM2x·destruct_dealloc_heap ,0);
      ar->tape = cx->tape;
      ar->nominal = &&report;
      continue_from TM2x·destruct_dealloc_heap;
      cend;
    }

    report:{
      cx->f[cx->i++] = cx->malloc_cnt == MallocCounter·count;
      cx->f[cx->i++] = cx->constructed_cnt == TM2x·constructed_count;
      Result·Tallies·tally("test_1" ,&cx->results ,cx->f ,cx->i);
      Result·Tallies·accumulate(accumulated_results_pt ,&cx->results);
      continue_from *cx->continuation;
      cend;
    }

    cend;
  }

#endif
