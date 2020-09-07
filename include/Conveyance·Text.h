/*--------------------------------------------------------------------------------
  General conveyance

  Include this before other text that makes use of general conveyance.

  The general_convey call may be executed in a 'parent' conveyance. The callee is the 
  child.  

  Context for a child lives is found in the tableau declared in the parent.

  We use the dereference-up method.  If the general conveyance pointer is relative, then
  it points to actual conveyance pointer.  This can be recursive.

*/

// the connection that lead to the currently running code
CV·Lnk *CV·lnk;
