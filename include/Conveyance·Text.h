/*
Must include this before other text that makes use of general conveyance

*/

//GeneralConveyancePtr
union CV·GeneralConvey·Ptr{

  struct{
    ConveyancePtr conveyance;
    void *context;
  } direct;

  struct{
    address_t offset;
    address_t same_offset;
  } relative; 

};

// arguments pad dedicated to general_convey
struct{
  void *context; // location of context in the grandparent tableau
  CV·GeneralConvey·Ptr *next;  // set this to point to your CV·GeneralConvey·Ptr
} CV·GeneralConvey·args;

// uses dereference-up
CV·def(CV·general_convey){
  if( CV·GeneralConvey·args.next->relative.offset == CV·GeneralConvey·args.next->relative.same_offset ){
    CV·GeneralConvey·args.next = (CV·GeneralConvey·Ptr *)
      (
       (address_t)CV·GeneralConvey·args.context + CV·GeneralConvey·args.next.relative.offset
       );
    convey CV·general_convey;
  }
  CV·GeneralConvey·args.context = CV·GeneralConvey·args.next->direct.context;     
  CV·convey CV·GeneralConvey·args.next->direct.conveyance;                 
  CV·end;
}
  
