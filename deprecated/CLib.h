#ifndef CLIB_H
#define CLIB_H





CLib·mallocn:{
  if( CLib·mallocn.args.n == address_t_n ) continue_from fail;
  *CLib·mallocn.args.pt = malloc(CLib·mallocn.args.n+1);
  if(!*CLib·mallocn.args.pt) continue_from *CLib·mallocn.args.fail;
  continue_from *CLib·mallocn.args.nominal;
  cend;
}


#endif
