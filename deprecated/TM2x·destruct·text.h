

  extern address_t TM2x·alloc_array_count;

  TM2x·dealloc_array:{
    free(TM2x·dealloc_array·args.tape->base_pt);
    TM2x·alloc_array_count--;
    continue_from *TM2x·dealloc_array·args.nominal;
    cend
  }
