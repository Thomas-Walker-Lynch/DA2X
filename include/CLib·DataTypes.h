
// struct CLib·mallocn *ar = &Conveyance·Args_pt->CLib·mallocn;
typedef struct {
  address_t n;
} CLib·Mallocn·Args;

typedef struct {
  void **allocated_data;
} CLib·Mallocn·Ress;

typedef struct {
  CV·Lnk nominal;
  CV·Lnk fail;
} CLib·Mallocn·Lnks;

typedef struct{
  CV·Ptr conveyance;
  CLib·Mallocn·Args *args;
  CLib·Mallocn·Lnks *lnks;
} CLib·Mallocn·Lnk;
