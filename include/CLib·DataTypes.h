
// struct CLib·mallocn *ar = &Conveyance·Args_pt->CLib·mallocn;
typedef struct {
  void **pt;
  address_t n;
} CLib·Mallocn·Args;

typedef struct {
  CV·Lnk nominal;
  CV·Lnk fail;
} CLib·Mallocn·Lnks;

typedef struct{
  CV·Ptr conveyance;
  CLib·Mallocn·Args *args;
  CLib·Mallocn·Lnks *lnks;
} Clib·Mallocn·Lnk;
