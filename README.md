# TM2x

This is just a dynamic array for C along with an iterator.  The 2x refers to
the fact that the allocation is doubled each time the array expands.

This is a version of the expanding tape as described in the tm library also in this repo.
Hence the name, Tape Machine 2x.

## Fundamentals

  In mathematics, a sequence consists of a series of indexable elements.

     e_0, e_1, ... e_i, ... e_n

  Where each index is a natural number. The natural number n+1 is said to be the 'length'
  of the sequence. 

  We would like to mimic this structure in our computer programs.  Hence we introduce a
  data type called an 'array'.  An array is a compact allocation of 'elements' in memory.
  The elements form a sequence, so each element has a natural number index. n+1 is
  the length of the element sequence, so we also say that n+1 is the length of the
  array.
  
  An 'element' in turn is a compact allocation of 'bytes'. The element itself is a sort of
  array where the elements are bytes.  As an array is a sequence of elements, and elements
  are sequences of bytes, it follows that an array is also a sequence of bytes.  Hence,
  an array is both a sequence of elements, and a sequence of bytes.

  To the programmer an 'element' is a semantic unit.  When doing memory management in C
  everything is based on bytes.  This leads to a bit of a confusing situation where we
  have two length measures for an array, one for its length in elements, and one for its
  length in bytes.  Conventionally lengths in bytes are referred to as an object's *size*,
  where as the number of elements in an array would remain the arrays *length*, but this
  notation is limited because bytes are also made of bits, and sometimes we want to name
  the element type.  Hence we will use the term 'length\_[bits|bytes|elements|..]'.  Hence an
  array has a 'bit length', a 'byte length', and an 'element length'.  If the array
  elements are characters the array will have a 'character length', etc..

  A memory allocation must have the same byte length, or larger byte length, than the byte
  length of the array being put in it.  Hence, we must distinguish between the byte length
  of the array we are storing in memory and the byte length of the allocation that the
  array is stored in.  If the allocation's byte length is larger than the array's byte
  length, there will be some allocated memory that goes unused.

## Allocation Algorithm

  We are implementing a dynamic array, i.e. one that may grow in length when elements
  are added to the end of it.  This in turn leads to a dynamic memory allocation problem.
  The apporach we use here is that when an array grows in byte length beyond that of the current
  allocation, we make a new allocation of twice the byte length of the original, and then copy
  the contents of the original array into this newly allocated area.

  Conversely, when the array data becomes 1/4 or less than the heap allocation, we 
  collapse the allocation to half its former byte length; however, we never make the array
  smaller than the initial heap allocation.

  Arrays will expanded as a result of using `TM2x_push_alloc` or one of the routines that
  call it, and, except for the minimum case, will collapse after a `TM2x_pop` cause the
  data to shrink to less than 1/4 of the allocation's byte length.

## Files

  The main array code is a set of inline functions defined in `TM2x.h`.
  
  An iterator and quantifiers are defined in `TM2xHd.h`
  
  The file `TM2x.c`, which makes to `TM2x.o` defines a counter that may be used 
  to check the balance between `TM2x_init` and `TM2x_data_dealloc` calls. 

  Eventually TM2x.c will also hold the non-linine definitions which the compiler will
  fall back upon should the `TM2x_F_PREFIX` be changed to `extern inline` and the compiler
  opts not to use the inline definition.  Currently definitions are `static inline`.
  
## Array Usage

  Either manually instantiate the `TM2x` struct statically, or dynamically.  Then use `TM2x_init`
  on the instance.  When finished with the instance call `TM2x_data_dealloc` to release the heap data.
  Or, alternatively, use the macro `TM2x_Make` to statically allocate and initialize in one step, or
  call `TM2x_alloc` to make a `TM2x` struct instance on the heap and ot initialize it. The use 
  `TM2x_dealloc` to free the data array and the `TM2x` struct.

  Note the example usage in the test files.

  
  
