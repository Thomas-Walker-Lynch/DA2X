# DA2x

A doubling array in C

## Nomenclature

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
  array where the elements are bytes.  As arrays is a sequence of elements, and elements
  are sequences of bytes, it follows that an array is also a sequence of bytes.  Hence,
  an array is two sequences all at once.

  Programmers typically assign some meaning to array elements, so we do not want to toss that
  concept aside and just use bytes. However, memory management really is based on
  bytes.  This leads to a bit of a confusing situation, we have two concepts of length
  for an array.  In order to disambiguate these two it has become conventional in C programming
  to use the term 'length' when counting elements, and the term 'size' when counting
  bytes.

  A memory allocation must have the same size, or larger size, than the size of the array
  being allocated.  Hence, we must distinguish between the size of the array we are storing
  in memory and the size of the allocation that the array is stored in.  If the allocation size
  is larger than the array size, there will be some allocated memory that goes unused.

## Algorithm

  Here we are implementing a dynamic array, i.e. one that may grow in length when elements
  are added to the end of it.  This in turn leads to a dynamic memory allocation problem.
  The apporach we use here is that when an array grows in size beyond that of the current
  allocation, we make a new allocation of twice the size of the original, and then copy
  the contents of the original array into this newly allocated area.

  The way the code is currently setup, once an array is initialized, the heap allocation
  will never be smaller than the initial heap allocation.  Apart from that, the allocation
  will automatically contract by 1/2 each time a pop() discovers, after the pop, that the
  data takes 1/4 or less of the total heap allocation.

## Files

  The main array code is a set of inline functions defined in `DA2x.h`.
  
  There is an iterator and quantifiers defined in a set of inline functions defined in DA2xIt.h
  
  There is a file `DA2x.c`, which makes to `DA2x.o` which defines a counter in case a person
  wants to balance the `DA2x_init` and `DA2x_data_dealloc` calls.  Later this file
  will also have the extern versions in case the `DA2x_F_PREFIX` is changed.
  
## Usage

  Instantiate the `DA2x` struct either statically, automatically.  Then `DA2x_init`
  the instance.  When finished with the instance call `DA2x_data_dealloc` to release the heap data.

  For dynamic allocation call DA2x_alloc to make a `DA2x` struct on the heap and initialize it in 
  one step.  When finished with it call `DA2x_dealloc` to free the array and the `DA2x` struct.
  If the array holds pointers to data that must also be freed, call `DA2xIt_dealloc`.

  Note the example usage in the test files.

  
  
