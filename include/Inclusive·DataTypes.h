
/*
  All 3 operand address computations may use this.
*/

typedef struct {
  union {
    struct{
      address_t a_0;
      address_t a_1;
    };
    uint128_t r;
  };
  address_t *rpt;
} Inclusive·3opLL·Args;

typedef struct {
  CV·Lnk nominal;
  CV·Lnk gt_address_t_n;
} Inclusive·3opLL·Lnks;

// retypes CV·Lnk
typedef struct{
  CV·Ptr conveyance;
  Inclusive·3opLL·Args *args;
  Inclusive·3opLL·Lnks *lnks;
} Inclusive·3opLL·Lnk;
