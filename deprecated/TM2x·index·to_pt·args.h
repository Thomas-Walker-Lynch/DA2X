
struct{
   TM2x·Tape*tape ;
   address_t index;
   address_t element_byte_n;
   void **pt;
   continuation nominal;
   continuation index_gt_n;
} TM2x·index·to_pt;
