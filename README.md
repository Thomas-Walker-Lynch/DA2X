# TM2x

This is a dynamic array for C, along with an iterator.  The 2x refers to
the feature that the allocation is doubled each time the array expands.
Hence the name, Tape Machine 2x.

This array is kind of expanding tape as described in the tm library.

## Fundamentals

  In mathematics, a sequence consists of a series of indexable elements.

     e_0, e_1, ... e_i, ... e_n

  Where each index is a natural number. The natural number n+1 is said to be the 'length'
  of the sequence. 

  We would like to mimic this structure in our computer programs.  Hence we introduce a
  data type called an 'array'.  The elements form a sequence, so each element has a
  natural number index. n+1 is the length of the element sequence, so we also say that n+1
  is the length of the array.

  A computer processor works by pulling all data from system memory. System memory is
  an array of elements, where the elements are bytes, and the indexes are called 'addresses'.
  
  Elements in an array are actually little arrays themselves. Elements are arrays of memory bytes.
  Hence, while each element has an index from the base of the array, each byte in the elements
  also has an address in memory.

  The recursive nature of memory type leads to a bit of a confusing situation. For
  example, we have three lengths measures for an array of the type we declare in our
  program.  One for its length in elements, another for its length in bytes. Bytes in the
  array can be indexes from 0 to n within the array, but those same bytes will have
  indexes ranging from 0 being the first byte in memory to n being the last byte in
  memory.

  So as to try and keep all this straight, I have introduced the following nomenclature for
  naming indexes. Note indexes are natural numbers. Here we are talking about the indexes on
  the elements, be they bytes or something else, not the elements themselves.
  
  A variable that holds an index value will consists of a series of words separated by
  underscores.  The first word is the object we are talking about. The second word is the
  semantic concept for an element in that object, and the third is a number that
  identifies the index relative to the object.  I then allow for a suffix.  If the suffix
  is `_pt`, the value is relative to the start of memory rather than relative to the start
  of the object.

  Here are two examples:
    ```
          array_byte_n
          array_element_n_pt
    ```

  Here the variable `array_byte_n` will hold a natural number that is the subscript of the last
  byte in the array. We do not know in advance as to the value of `n` here, because we do not know
  in advance how long the array is.

  In contrast, the variable `array_byte_n_pt` will hold the natural number that is the subscript
  for the byte in memory that corresponds to the first byte of the last element in the array.
  This is also known as a 'last element pointer'.

  Consider another example,
    ```
          array_byte_0
          array_byte_0_pt
    ```

   We would expect that the value of the variable `array_byte_0` is zero.  The variable belongs
   to the array object, and it is array relative index for the first byte.  The second variable,
   `array_byte_0_pt` is more interesting. This will be the address of the first byte of the array
   relative to the start of memory.  This may be called the 'array's location in memory' or a 'pointer
   to the first byte in the array', or even 'the array base'.  It will also be a pointer to the first
   element in the array, and to the start of the memory alloction for the array.  The array base is a 
   busy concept.

   If the object is obvious, we will drop it from the variable name.

   To access the nth byte in the array we write:

   ```
       byte_0_pt[byte_n]
   ```
   
   And to access the ith element when that element is an 'int':
   
   ```
       ((int *)byte_0_pt)[element_i]
   ```
   
   Or even:
   
   ```
       *((int *)byte_0_pt + element_i)
   ```


## Allocation Algorithm

  We allocate in the smallest power of 2 sizes that the data set fits in.
  
  Attempting to push on a full allocation will cause the allocation to double, then
  the push will occur.
  
  If after pop byte_n is equal to the inclusive upper bound of a binary interval,
  the array contracts to that size.


## Files

  The main array code is a set of inline functions defined in `TM2x.h`.
  
  An iterator and quantifiers are defined in `TM2xHd.h`
  
  The file `TM2x.c`, which makes to `TM2x.o` defines a counter that may be used 
  to check the balance between `TM2x_init` and `TM2x_data_dealloc` calls. 

  Eventually TM2x.c will also hold the non-linine definitions which the compiler will
  fall back upon should the `TM2x_F_PREFIX` be changed to `extern inline` and the compiler
  opts not to use the inline definition.  Currently definitions are `static inline`.
  
## Array Usage

  1. Manually instantiate a `TM2x` struct statically, or dynamically.  Then use
     `TM2x_init` on the instance.  When finished with the instance call
     `TM2x_data_dealloc` to release the heap data.  If the TM2x struct was manually
     instatiated on the heap, free it.
  
  2. Use the macro `TM2x_Make` to statically allocate and initialize in one step. When
     finished with the instance call `TM2x_data_dealloc` to release the heap data.

  3. Call `TM2x_alloc` to make a `TM2x` struct instance on the heap and to initialize it
     all in one step. When finished call `TM2x_dealloc` to free both the data
     array and the `TM2x` struct.

  Note the example usage in the test files.

## Eliminating `allocation_np1_pt` and Inclusive Bounds for Small Memories

  At the time of this writing, attotw, (2020-06-27T14:57:19Z in case you want to look it
  up on github), our array implementaiton uses an exclusive upper bound convention, where
  the pointer `byte_0_pt` locates the first byte in the array, and the pointer
  `byte_np1_pt`, where np1 stands for n plus 1, is used to bound the data in the array,
  and `allocation_np1_pt` is used to bound the allocation.  We also use a doubling algorithm
  on expansion, with hystersis and collapse on a 1/4 size threshold.
  
  The exclusive allocation bound pointer, `allocation_np1_pt`, minus the base pointer,
  i.e. the allocation size, will either extend to the end of memory, or will be a power of
  two.  If we collapsed immediately instead of using current hysterisis rule,
  `allocation_np1_pt` pointer could be computed from the memory size and the `byte_np1_pt`
  value.  Eg.  when `byte_np1` is 4, 5, or 6, 7, `allocation_np1` would be 8.
  I.e. `byte_np1` values of 100, 101, 110, 111 are all bounded to a binade with the
  value 1000. Etc.

  A nice property of using exclusive, 'np1', style bounding pointers is the ability to
  represent zero length objects.  Hence when `byte_np1_pt` is equal to `byte_0_pt` we know
  the array is zero length.  Philosophically, in the computation theory sense, the zero
  length array is an interesting object.  With the zero length array, the name of the
  pointer we called `byte_0_pt` becomes a misnomer, because there is no byte 0 in an empty
  array.  Another thing that is a bit funny is that though the array exists, and we know
  it exists because the base pointer is not null, it has no members. It is not entirely
  clear what that means for an array with no members to 'exist'.  But this next thing is
  the most consequential:

  For a memory between `2^(n-1) + 1` to `2^n` in size, we must implement n bit pointers.
  However for the end case of `2^n` sized memory, to be able to use exclusive upper bound
  pointers, we will require pointers of length n+1 rather than length n. This will affect
  all registers, buffers, and programs that use pointers. And through such a larger unsigned
  integer at n+1 bits could encode twice as many values as an integer with n bits, we will
  use only one of those encodings.
  
  OK, suppose I change this implementation for a dynamic array and use an inclusive upper
  bound instead of an exclusive upper bound.  I.e. instead of saying that the array is
  bound by the pointer `byte_np1_pt`, let us bound the array with `byte_n_pt. Such an
  implementation will be useful when we want to limit our array allocation to a single
  page of memory, say in an implementation that uses mapped pages, if we have a special
  machine with a small memory, or if we were designing our own hardware and wanted to
  implement an array over a memory buffer.

  For purposes of visualization of end case you might imagine that there are 16 bytes of
  memory, that a pointer is 4 bits, an that array elements are 1 or two bytes. With such a
  small memory we do not want to waste a single byte. Suppose further that we do not allow
  overflows when performing arithmetic.  I.e. we do not want to build into the
  implementation dependencies on the specific behavior of what happens when we add 1 to
  1111. (It would be good to test this code with such a model, but that has not been done
  yet.)

  With this new implementation all arithmetic for the array is done in a manner that it
  will never overflow or underflow and all values may be held within the representation.
  However, the C library routines which we need, `malloc` and `sizeof`, do not conform.
  Maybe someday we will go new versions of those, but for now, as a hack, I just created
  `#define` versions of the routines we wish for, and then these expand out to the
  the C library versions. The type `size_t` is actually the address type for the machine
  C is targetting, so for clarity I aliased that to `address_t`.

  When we use inclusive bounds on our data, we lose the ability to represent a zero length
  array.  Instead the smallest array, where `byte_0_pt` equals `byte_n_pt`, will have one
  element in it. In trade for this we will no longer have to debate the meaning of an
  array existing though it has no elements in it, and `byte_0_pt` will indeed alawys point
  to byte 0.  If our array is being used for something like a FIFO we will have to use an
  external flag to represent when the FIFO is empty.  But again, we find this to be
  conceptually clean because that is a special case that changes the behavior of pulling
  from the FIFO.  Had we had an array that could be empty, would have found ourselves
  always checking for that case separately, i.e. using the array in an anomolous manner
  before using it as an array. Arguably then, the new approach is cleaner.
  
## Removing the `element_byte_n` field from the dynamic array header

  attotw, 2020-06-30T11:15:57Z, the dynamic arrays keeps an `element_byte_n` field.  This
  field is convenient for development.  
  
  The C compiler always knows how big the element is when it reads or writes an array. The 
  problem comes when we pass an element address through a void pointer. Within such a 
  function we have no way to call '`sizeof`' (or '`byte_n_of`') when calling memcpy or
  other routines than need to know how many bytes are in an element.  We are left with 
  two choices, one is to pass the element size into all functions on the dynamic array
  that might need it, or to add the element size to the array header struct.

  Function calls are inlined so there is no overhead passing in `element_byte_n`.  In
  contrast keeping `element_byte_n` in the array header costs another word of memory for
  each header.  There are also optimization issues.  The compiler might be confused by the
  same information, which is a constant at run time, being held in two places.
  Furthermore the optimizer is unlikely to reduce the size of the struct and use the
  sizeof information it already has.
  
  Hence I have modified the code to pass `element_byte_n` (the size of the elements) though
  the interface.
  
## Empty arrays

  Often times dynamic arrays are used as stacks.  Code that pushes an element on to a stack
  typically does not consider and empty stack to be a special case.  But the way the code
  is attotw, the first element must be written to the stack base, then further elements
  may be pushed, so push code has to treat an nearly initialized stack differently.
  
  Actually, if the array could be empty, the special code for treating the empty case does not
  go away, rather it just moves to the other side of the dynamic array interface.  Moving
  it into the library code would be better because then the programmer does not have to spin
  it fresh each time he or she uses the array.
  
  In this array implementation we do not use inclusive arithmetic with no overflows, and
  we allow that all memory, including address 0, can be addressed. Hence, should we follow
  these constraints, we do not have address 0 to use as a NULL valued flag.  I am sorely
  tempted to use `base_pt == NULL` to indicate the array is empty, but so much work has
  been put into the inclusive arithmetic I will not do this now.

  There is another thing we can do to flag special cases. Note that if an array takes up
  the whole of memory, then it must be based at `memory_byte_0`. This is because we do not
  wrap the array around the buffer, and we do not wrap around the buffer because we did
  not specify an overflow behavior for the arithmetic. Hence, we could enumerate special
  states for the array, including that it is empty, by setting `byte_n` in the header
  struct to `memory_byte_n` and then enumerate alternative states using a non-zero `base_pt`
  value.  However, if we do this, then our code will not be able later implement an array with
  wrap around.  Wrap around is probbly would not work for other reasons also.
  
  As this is the first version, just to keep things simple, I will add an empty flag. It will
  make for clean code.


   
   
