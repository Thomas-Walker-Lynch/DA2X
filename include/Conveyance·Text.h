/*
This must be the first Text include.

*/

union Conveyance·Data *Conveyance·Args_pt = &Conveyance·Data0;
union Conveyance·Data *Conveyance·Locals_pt = &Conveyance·Data1;

// need to verify that this nested function call optimizes away
void Conveyance·update(){
  union Conveyance·Data *t1_locals = Conveyance·Args_pt;
  Conveyance·Args_pt = Conveyance·Locals_pt;
  Conveyance·Locals_pt = t1_locals;
}
