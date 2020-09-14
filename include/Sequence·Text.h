/*--------------------------------------------------------------------------------
  General sequence

  Include this before other text that makes use of general sequence.

  The general_continue call may be executed in a 'parent' sequence. The callee is the 
  child.  

  Context for a child lives is found in the tableau declared in the parent.

  We use the dereference-up method.  If the general sequence pointer is relative, then
  it points to actual sequence pointer.  This can be recursive.

*/

// the connection that lead to the currently running code
SQ·Lnk *SQ·lnk;
