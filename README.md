
--------------------------------

The example-pound-define-lambdas branch implements redefinition of argument variables
names in continuations performed by #include for the first few functions in the former
TM2x.lib.h.  With this method a parent continuation can share variables with child
continuations. We achieve true usage of variables in scope through the continuation
call.

The code is pretty, but the the lack of functionality in the cpp macro language combined
with the lack of namespace structures conspired to cause a lot of typing and very long
names for arguments and local variables in the continuations.

Hence, I am going to move to a model where continuations always read their arguments from
a partner struct. I will rely upon the compiler's optimizer to recognize the redundant use
of the struct and to clean things up.



# TM2x

This is a dynamic array for C, along with an iterator.  The 2x refers to
the fact that the allocation is doubled each time the array expands beyond
its bound. 

This array is kind of expanding tape as described in the tm library.  Hence the name, Tape
Machine 2x.

## Faux Namespaces with a unicode character
  
  C doesn't have namespaces, so I do the conventional thing of prefixing all
  identifiers on the interface with the namespace (the library name). Initially
  this was followed by an underscore.  

  Gosh I wish we could just use '::' in identifiers to separate the namepace part from the
  rest of the identifier.  Since C99 some unicode has been allowed. There are other colon
  like characters that work in identifiers, but using two different colons would be
  confusing.  The central raised dot is allowed in identifiers, so I used that instead
  of double colons.

  For example:
    wish for:  `TM2x::alloc_heap`
       using:  `TM2x·alloc_heap`

  Better yet would be a namespace facility for C.

## Using Gcc extensions

  The code makes use of these:
  1. typeof
  2. variable holds a &&label value
  3. empty structures
  4. declared labels ('local labels')
  5. 128 bit unsigned int

  In the near future, will probably make use of 
  3. nested functions

  And this looks useful, but have used it yet:
  4. statement expressions

## Installation

  `make test` should buid and run the tests.  The output should be identical to the contents of the file
  `test_results_expected.txt`. (In the future the tests should probably be modified so only the passed
  failed results are needed.)

  After the tests pass, `make share` installs the dynamic array into ../env/include  and ../env/lib. 
  
  My projects are always embeded in a project directory that has an env directory for
  releasing module code.  The modules are individual git projects.  See my git 'project'.
   
  After install, the usual drill, include the header files in your program, and compile against the library.


## Array Fundamentals

  In mathematics, a sequence consists of a series of indexable elements.

     e_0, e_1, ... e_i, ... e_ntt

  Where each index is a natural number. The natural number n+1 is said to be the 'length'
  of the sequence. 

  We would like to mimic this structure in our computer programs.  Hence we introduce a
  data type called an 'array'.  The elements form a sequence, so each element has a
  natural number index. n+1 is the length of the element sequence, so we also say that n+1
  is the length of the array.

  A computer processor initially reads data from system memory. System memory is an array
  of elements, where the elements are bytes, and the indexes are called 'addresses'.
  
  Elements in an array are actually little arrays themselves. Elements are arrays of memory bytes.
  Hence, while each element has an index from the base of the array, each byte in the elements
  also has an address in memory.

  The recursive nature of memory type leads to a bit of a confusing situation. For
  example, we have three lengths measures for an array of the type we declare in our
  program.  One for its length in elements, another for its length in bytes. Bytes in the
  array can be indexes from 0 to n within the array, but those same bytes will have
  indexes ranging from 0 being the first byte in memory to n being the last byte in
  memory.

## Address and index variable naming convention

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


## Allocation algorithm

  We allocate in the smallest power of 2 sizes that the data set fits in.
  
  Attempting to push on a full allocation will cause the allocation to double, then
  the push will occur.
  
  If after pop byte_n is equal to the inclusive upper bound of a binary interval,
  the array contracts to that size.

## Allocation nomenclature

   alloc     - reserves memory large enough to hold a TM2x struct
   construct - sets field values for TM2x struct, allocates space for data on the heap, 
               variations can take arguments and write some initial data

   static  - allocation on the stack or a static page
   heap    - allocation on the heap
   
  All Tm2x structs must go through allocation and formatting before being written.
  All Tm2x structs must be written before being red.

  When the words 'read' or 'write' appear in a function name, the read destination, or
  the write source is a pointer to a location and one element is copied.  For reads the 
  copy source is in the array.  For writes the copy destination is in the array. Otherwise
  both operations are just copies.

  When the word 'copy' appears in a function name, the read destination, or the write source
  is another array rather than just one element.

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
  
## Continuations

  `continuation` is the continuation type.
  `continue_into` precedes functions that accept continuation arguments.
  `confinue_from` causes a continuation to be taken by going through the trampoline
  `contianue_local` invokes a continuation within the same scope

  I have found a reasonable technique for doing continuations in C. What would be 
  lambdas are code segments followed by a label. Instead of passing the lambdas into
  the functions directly, instead a tampoline bounces the label backout.  Thus the 
  code segment is at the same level in the code as the function call it was 'passed into'
  and thus can see the context variables. This approach has the advantage of being
  easy on the stack.
  
  There are a few disadvantages. 1) The label scoping is a bit messed up, all code segments
  at a given level can see all labels so following good structure is by convention and the 
  label names must be uique. 2) Labels can only be used on statements.  However
  a loan semicolon is a statement, so I just follow all labels with ':;' instead of just ';'.
  Then anything or nothing may follow a label. 3) We can not pass in functions like 'be(true)'
  and then easily turn a continuation function into a bool returning function. C mode gets
  confused, and it is no fun to fight the electric indentation.
  
