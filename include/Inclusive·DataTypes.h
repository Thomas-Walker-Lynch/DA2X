
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
} Inclusive·3opLL·Args;

typedef struct {
  address_t *r;
} Inclusive·3opLL·Ress;

typedef struct {
  SQ·Lnk nominal;
  SQ·Lnk gt_address_t_n;
} Inclusive·3opLL·Lnks;

// retypes SQ·Lnk
typedef struct{
  SQ·Ptr sequence;
  Inclusive·3opLL·Args *args;
  Inclusive·3opLL·Ress *ress;
  Inclusive·3opLL·Lnks *lnks;
} Inclusive·3opLL·Lnk;
