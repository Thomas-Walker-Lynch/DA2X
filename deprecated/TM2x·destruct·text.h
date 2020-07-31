

  extern address_t TM2x·constructed_count;

  TM2x·destruct:{
    free(TM2x·destruct·args.tape->base_pt);
    TM2x·constructed_count--;
    continue_from *TM2x·destruct·args.nominal;
    cend
  }
