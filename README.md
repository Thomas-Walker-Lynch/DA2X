# TM2x

This is a dynamic array for C, along with an iterator.  The 2x refers to
the feature that the allocation is doubled each time the array expands.

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

  Then according to our nomenclature we start with the container, then name the element type,
  give the subscript, then give the type.
  
  ```
          array_byte_0_pt
          memory_byte_0_pt
  ```

   `array_byte_0_pt` is a pointer to the first byte in an array.  `memory_byte_n_pt` is a pointer
   to the last byte in memory.  Where the container context is clear we leave that off.  In 
   most of our array implementation the container is clearly the array.  Hence,
   
  ```
          element_n_pt
  ```

   in the array implementation `element_n_pt` would be a pointer to the last element in the array.
   
   When the subscript is given as a variable we are asking about that variable's value. Hence,
   
   ```
       array_byte_n
       byte_n
   ```
   for a 16 byte array these both would have the value 15.  In the second one the array container is implied.
   Suppose this same array had elements that were 4 byte integers, then 
   
   ```
       array_element_n
   ```
   Would have the value of 3.
   
   Note that to get the nth byte we would have

   ```
       byte_0_pt[byte_n]
   ```
   
   Note and to get the nth element:
   
   ```
       ((int *)byte_0_pt)[element_n]
   ```
   
   Or even:
   
   ```
       *((int *)byte_0_pt element_n)
   ```

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

## Eliminating `allocation_np1_pt` and Inclusive Bounds for Small Memories

  At the time of this writing, attotw, (2020-06-27T14:57:19Z in case you want to look it
  up on github), our array implementaiton uses an exclusive upper bound convention, where
  the pointer `byte_0_pt` locates the first byte in the array, and the pointer
  `byte_np1_pt`, where np1 stands for n plus 1, is used to bound the data in the array,
  and `allocation_np1_pt` is used to bound the allocation.  We also use a doubling algorithm
  on expansion, and hystersis on collapse with a 1/4 size threshold.
  
  With this dynamic array algorithm the `allocation_np1_pt` value is always a simple power
  of two, or a bound on the memory as a whole.  If we collapsed immediately instead of
  using hysterisis and the 1/4 threshold rule, we would not need the `allocation_np1_pt`
  pointer at all, because it would point to either the end of memory or to the top of the
  binade of `byte_np1_pt` value.  Eg.  when `byte_np1_pt` is 4, 5, or 6, 7, `allocation_np1_pt`
  would be 8.  I.e. 100, 101, 110, 111 would be bound by 1000. Etc.

  A nice property of 'np1' bounding pointers the ability to represent zero length objects.
  Hence when `byte_np1_pt` is equal to `byte_0_pt` we know the array is zero length.
  Philosophically, in the computation theory sense, the zero length array is an
  interesting object.  With the zero length array, the name of the pointer we called
  `byte_0_pt` becomes a misnomer, because there is no byte 0 in an empty array.  Another
  thing that is a bit funny is that though the array exists, and we know it exists because
  the base pointer is not null, it has no members. It is not entirely clear what that
  means for an array with no members to 'exist'.  But this next thing is the most
  consequential:

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
  

