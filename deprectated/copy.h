
  SQ·def(T02x·copy_contiguous_bytes){
    // some aliases
    //
      T02x·CopyContiguous·Lnk *lnk = (T02x·CopyContiguous·Lnk *)SQ·lnk;
      T02x·Root *src = lnk->args->src;
      T02x·Root *dst = lnk->args->dst;
      address_t src_0 = *lnk->args->src_0;
      address_t dst_0 = *lnk->args->dst_0;
      address_t n = *lnk->args->n;
    if( 
       T02x·n(src) < n
       ||
       T02x·n(src) - n < src_0
        ){
      SQ·continue_indirect(lnk->lnks->src_index_gt_n);
    }
    if( 
       T02x·n(dst) < n
       ||
       T02x·n(dst) - n < dst_0
        ){
      SQ·continue_indirect(lnk->lnks->dst_index_gt_n);
    }
    memcpyn(T02x·0_pt(dst) + dst_0, T02x·0_pt(src) + src_0, n);
    SQ·continue_indirect(lnk->lnks->nominal);
  } SQ·end(T02x·copy_contiguous_bytes);


  SQ·def(T02x·copy_contiguous_elements){
    T02x·CopyContiguousElements·Lnk *lnk = (T02x·CopyContiguousElements·Lnk *)SQ·lnk;

    // ----------------------------------------
    // local result tableau
    //
      address_t src_0;  
      address_t dst_0;  
      address_t ext_n;  

    // ----------------------------------------
    // Links
    //
      SQ·make_Lnk(scale_src ,Inclusive·3opLL ,&&Inclusive·mul_idx);
      SQ·make_Lnk(scale_dst ,Inclusive·3opLL ,&&Inclusive·mul_idx);
      SQ·make_Lnk(scale_ext ,Inclusive·3opLL ,&&Inclusive·mul_ext);
      SQ·make_Lnk(copy_contiguous_bytes ,T02x·CopyContiguous ,&&T02x·copy_contiguous_bytes);

      scale_src_lnks = (Inclusive·3opLL·Lnks)
        {  .nominal = AS(scale_dst_lnk ,SQ·Lnk)
          ,.gt_address_t_n = lnk->lnks->src_index_gt_n
        };

      scale_dst_lnks = (Inclusive·3opLL·Lnks)
        {  .nominal = AS(scale_ext_lnk ,SQ·Lnk)
          ,.gt_address_t_n = lnk->lnks->dst_index_gt_n
        };

      scale_ext_lnks = (Inclusive·3opLL·Lnks)
        {  .nominal = AS(copy_contiguous_bytes_lnk ,SQ·Lnk)
          ,.gt_address_t_n = lnk->lnks->src_index_gt_n
        };

      copy_contiguous_bytes_lnks = (T02x·CopyContiguous·Lnks)
        {  .nominal = lnk->lnks->nominal
          ,.src_index_gt_n = lnk->lnks->src_index_gt_n
          ,.dst_index_gt_n = lnk->lnks->dst_index_gt_n
        };

    // ----------------------------------------
    // sequence results point into the tableau
    //
      scale_src_ress.r = &src_0;
      scale_dst_ress.r = &dst_0;
      scale_ext_ress.r = &ext_n;

    // ----------------------------------------
    // seqeuence args point into this tableau or the parent tableau
    //
      scale_src_args = (Inclusive·3opLL·Args)
        {  .a_0 = lnk->args->src_element_0
          ,.a_1 = lnk->args->element_n_Byte
        };

      scale_dst_args = (Inclusive·3opLL·Args)
        {  .a_0 = lnk->args->dst_element_0
          ,.a_1 = lnk->args->element_n_Byte
        };

      scale_ext_args = (Inclusive·3opLL·Args)
        {  .a_0 = lnk->args->n_Element
          ,.a_1 = lnk->args->element_n_Byte
        };

      copy_contiguous_bytes_args  = (T02x·CopyContiguous·Args)
        {  .src        = lnk->args->src
          ,.src_0 = &src_0
          ,.dst        = lnk->args->dst
          ,.dst_0 = &dst_0
          ,.n     = &ext_n
        };

    SQ·continue_indirect(scale_src_lnk);

  } SQ·end(T02x·copy_contiguous_elements);
