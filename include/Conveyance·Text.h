

/*--------------------------------------------------------------------------------
  General conveyance

  Include this before other text that makes use of general conveyance.

  The general_convey call may be executed in a 'parent' conveyance. The callee is the 
  child.  Context lives in the parent, so the parent's context is in the grandparent.

  We use the dereference-up method.  If the conveyance field is equal to the context
  field, then the conveyance is relative to the parent's context (which is located in the
  grandparent).  Such calls leave the parent.

*/

  union CV·GeneralConvey·Ptr{

    struct{
      CV·Ptr conveyance;
      void *context;
    } direct;

    struct{
      address_t offset;
      address_t same_offset;
    } relative; 

  };

  // Makes a relative GeneralConvey·Ptr given a variable to put it in a namespace, the type, and the
  // name of the continuation.
  // e.g.  make_relative_gcp(t.mul_ib_0.cons.gt_address_t_n ,TM2x ,CopyElements ,gt_address_t_n);
  #define CV·make_relative_gcp(gcp ,ns ,type ,member)                     \
    gcp.relative.offset = offsetof(ns##·##type##·Context ,cons) + offsetof(ns##·##type##·Cons ,member); \
    gcp.relative.same_offset = gcp.relative.offset;                       \
    ;

  /*
    Creates a context struct for a conveyance.

    for example, CV·make_context(TM2x ,CopyElements); ->

    struct TM2x·CopyElements·Context{
      struct TM2x·CopyElements·Args args;
      struct TM2x·CopyElements·Cons cons;
    };
  */
  #define CV·make_context(ns ,type)\
    struct ns##·Context·##type{ struct ns##·##type##·Args args; struct ns##·##type##·Cons cons; }


  // arguments pad dedicated to general_convey
  struct{
    void *this_context; // points into the grandparent tableau
    CV·GeneralConvey·Ptr next;  // set this to point to your CV·GeneralConvey·Ptr
  } CV·GeneralConvey·args;

  CV·def(CV·general_convey){
    if( CV·GeneralConvey·args.next.relative.offset == CV·GeneralConvey·args.next.relative.same_offset ){
      CV·GeneralConvey·args.next = *(CV·GeneralConvey·Ptr *)
        (
         (address_t)CV·GeneralConvey·args.this_context + CV·GeneralConvey·args.next.relative.offset
         );
      convey CV·general_convey;
    }
    CV·GeneralConvey·args.context = CV·GeneralConvey·args.next->direct.context;     
    CV·convey CV·GeneralConvey·args.next->direct.conveyance;                 

  } CV·end(CV·general_convey);
  
