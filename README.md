# DA2x

A doubling array in C

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

  The 'element' is a semantic unit, and memory management is based on bytes, so we need
  both of these concepts.  This leads to a bit of a confusing situation where we have two
  length measures for an array, one for its length in elements, and one for its length
  in bytes.  In order to disambiguate these two length measures it has become conventional in C
  programming to use the term 'length' when counting elements, and the term 'size' when
  counting bytes.

  A memory allocation must have the same size, or larger size, than the size of the array
  being allocated.  Hence, we must distinguish between the size of the array we are storing
  in memory and the size of the allocation that the array is stored in.  If the allocation size
  is larger than the array size, there will be some allocated memory that goes unused.

## Allocation Algorithm

  We are implementing a dynamic array, i.e. one that may grow in length when elements
  are added to the end of it.  This in turn leads to a dynamic memory allocation problem.
  The apporach we use here is that when an array grows in size beyond that of the current
  allocation, we make a new allocation of twice the size of the original, and then copy
  the contents of the original array into this newly allocated area.

  Conversely, when the array data becomes 1/4 or less than the heap allocation, we 
  collapse the allocation to half its former size; however, we never make the array
  smaller than the initial heap allocation.

  Arrays will expanded as a result of using `DA2x_push_alloc` or one of the routines that
  call it, and, except for the minimum case, will collapse after a `DA2x_pop` cause the
  data to shrink to less than 1/4 of the allocation size.


## Files

  The main array code is a set of inline functions defined in `DA2x.h`.
  
  An iterator and quantifiers are defined in `DA2xIt.h`
  
  The file `DA2x.c`, which makes to `DA2x.o` defines a counter that may be used 
  to check the balance between `DA2x_init` and `DA2x_data_dealloc` calls. 

  Eventually DA2x.c will also hold the non-linine definitions which the compiler will
  fall back upon should the `DA2x_F_PREFIX` be changed to `extern inline` and the compiler
  opts not to use the inline definition.  Currently definitions are `static inline`.
  
## Array Usage

  Either manually instantiate the `DA2x` struct statically, or dynamically.  Then use `DA2x_init`
  on the instance.  When finished with the instance call `DA2x_data_dealloc` to release the heap data.
  Or, alternatively, use the macro `DA2x_Make` to statically allocate and initialize in one step, or
  call `DA2x_alloc` to make a `DA2x` struct instance on the heap and ot initialize it. The use 
  `DA2x_dealloc` to free the data array and the `DA2x` struct.

  Note the example usage in the test files.

  
  
