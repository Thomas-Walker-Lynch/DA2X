

/*--------------------------------------------------------------------------------
  General conveyance

  Include this before other text that makes use of general conveyance.

  The general_convey call may be executed in a 'parent' conveyance. The callee is the 
  child.  

  Context for a child lives is found in the tableau declared in the parent.

  We use the dereference-up method.  If the general conveyance pointer is relative, then
  it points to actual conveyance pointer.  This can be recursive.

*/

  /*
    A general conveyance's context contains its arguments, temporary variable space, and 
    connection information.  The context may change from call to call. The context
    for each conveyance is unique, but here is an abstract parent type.

  */
  struct Context{
  };

  /*
    A Tableau holds the contexts for child conveyances. Hence the Tableau declared with a
    a given conveyance is used by its children. We use the tableau_up pointer when derefercing
    indirect GeneralConveyance·Ptr connections.
  */
  struct Tableau{
    struct Tableau *tableau_up; // the tableau one up in the convey chain
    struct Convext *context_in_use;
    // child context structs follow ...
  };

  union CV·GeneralConveyance·Ptr{

    struct{
      CV·Ptr conveyance;
      Context *context;
    } direct;

    struct{
      address_t offset;
      address_t same_offset;
    } indirect; // relative to the top of the tableau

  };

  /*
    Makes an indirect GeneralConvey·Ptr.
    Value is the offset relative to the child conveyance's context.
  */
    #define CV·make_indirect_gcp(gcp ns ,conveyance_name ,continuation_name) \
      gcp.indirect.offset =                                                 \
        offsetof(ns##·Context ,cons)                                        \
        + offsetof(ns##·Cons ,continuation_name);                           \
      gcp.indirect.same_offset = gcp.indirect.offset;                       \
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

/*
  General convey accepts arguments the dedicated pad shown below.

  Starting from the parent conveyance, conveys  to the child conveyance.

  The parent's tableau holds context for all children.

  There are two types of GeneralConveyance·Ptr,  direct and indirect.

  A direct pointer holds a child conveyance entry point and a pointer to the child's context.
  The child's context is located in the parent's tableau.

*/  
  struct{
    Tableau *tableau; 
    CV·GeneralConveyance·Ptr next;  // set this to point to your CV·GeneralConveyance·Ptr
  } CV·GeneralConvey·args;

  #define is_direct() \
     CV·GeneralConvey·args.next.indirect.offset != CV·GeneralConvey·args.next.indirect.same_offset

  CV·def(CV·general_convey){
    if( is_direct() ){
      CV·GeneralConvey·args.context = CV·GeneralConvey·args.next->direct.context;     
      CV·convey CV·GeneralConvey·args.next->direct.conveyance;                 
    }
    CV·GeneralConvey·args.next = *(CV·GeneralConveyance·Ptr *)
      (
       (address_t)CV·GeneralConvey·args.parent + CV·GeneralConvey·args.next.indirect.offset
       );
    CV·GeneralConvey·args.parent = parent->parent;
    convey CV·general_convey;

  } CV·end(CV·general_convey);
  
