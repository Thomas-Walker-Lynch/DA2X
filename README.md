
This attempt at writing a purve conveyance version of the TM2x library highlighted the 
need to manage context data, i.e. data that is sent as a message to a continuation that
will be run in the future, but not one being directly called.  This is analogous to context
shared with lambda functions.


# TM2x

A dynamic array for C, along with an iterator.  It is written in C.

This is an implementation of the 'tape machine' described in the TTCA book. Hence the TM for
'tape machine'.  Upon reaching an allocation limit, the array allocation doubles, hence
the 2x in the name.

## GCC extensions used

  1. 128 bit unsigned int
  2. typeof
  3. variable holds a &&label value
  4. declared labels ('local labels')
  5. `#pragma push_macro/pop_macro`
  6. statement expressions
  7. `__builtin_clz`
  8. nested functions

## Namespaces

  Data structures, name mangling, and push/pop macros are used to manage namespaces.

  I am very thankful to have a unicode character as supported in the C90 spec to use to
  separate the namespace from the rest of the identifier:

    conventional:  `TM2x::alloc_heap`
           using:  `TM2x·alloc_heap`

   Of course, the double colon is not available fo idnetifier names in C.

   In the following 'S' is short for 'space' which in turn is short for 'namespace'.  When
   there is more than one namespace I follow the S with a number.

```
   #pragma push_macro("S")
   #undef S0
   #define S TM2x

      ...
      S·x = 5

   #pragma pop("S")

```

## Identifier case convention

   ALL_CAPS - macros.
   
   CamelCase - types and namespaces, except for built in types and types in other
   libraries.

   lower_case - everything else.

## Building the Library

  `make test` should buid and run the tests.  The output should be identical to the contents of the file
  `test_results_expected.txt`. (In the future the tests should probably be modified so only the passed
  failed results are needed.)

  After the tests pass, `make share` installs the dynamic array into ../env/include  and ../env/lib.

  My projects are always embeded in a project directory that has an env directory for
  releasing module code.  The modules are individual git projects.  See my git 'project'.

  After install, the usual drill, include the header files in your program, and compile against the library.

## Usage

  In the main of the program that is intended to use conveyance libraries, #include all the `...args.h`
  header files in a union called 'Args'.  Immediately after that declare another union called `Text`
  and #include the `...text.h` files there.  In the test directory you can find some examples.

## Conveyances

  The library is a collection of segments of code that are called as 'conveyances'.

  Each convenyance has one entry point and potentially multiple exit points.  The entry point
  is the name of the conveyance, and the exit points are called continuations.  A conveyance
  does not have a return statement, which is why it is not called a function.  A conveyance is
  guaranteed to follow a continuation before reaching the closing brace.

  One enters a convenyance by banching to it. We call such a branch a 'continuation'.

  The header file `Conveyance.h` provides some syntax hacks to give the programmer a feeling that
  C has direct support for conveyances.

## What is an Array

  You are already familiar with arrays of course.  This section just provides us with a common
  language for talking about them in some detail.

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

  A variable that holds an index value will consists of a series of words separated by
  underscores.  The first word is the object we are talking about. The second word is the
  semantic concept for an element in that object, and the third is a number that
  identifies the index relative to the object.  I then allow for a suffix.  If the suffix
  is `_pt`, the value is relative to the start of memory rather than relative to the start
  of the array.

  Here are two examples:
    ```
          array_byte_n
          array_element_n_pt
    ```

  Here the variable `array_byte_n` will hold a natural number that is the subscript of the
  last byte in the array. As the array may expand, this value may be modified.  We call
  this value the 'extent' of the array, here measured in bytes.  Generally the extent of
  an array measured in bytes, plus 1, will be the 'size' or the 'length' of the array.

  In contrast, the variable `array_element_n_pt` will hold the address of the element at
  index `array_element_n`.

  Consider another example,
    ```
          array_byte_0
          array_byte_0_pt
    ```

   We might expect that the value of a variable called `array_byte_0` would be zero.
   A variable called `array_byte_0_pt` would be the address of the first byte of the array
   relative to the start of memory.  This is also called: 'the array's location in memory',
   'a pointer to the first byte in the array', 'a pointer to the first element in the array',
   and 'the array base'.

   Since the object here is obviously 'array' we will drop that part.

   To access the nth byte in the array, the last byte, we write:

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

  Inversely, reducing the size of the array through pop will cause the allocation
  to contract when power of two boundaries are passed.

## Array instantiation and use.

  To use a dynamic array, we must first 'allocate' the header structure. There are
  generally three storage allocation classes for allocation.

   static  - allocation on directly in memory
   stack   - allocation on a stack frame
   heap    - allocation on the heap

  The C language used to have storage class keywords of 'register', 'static', and 'auto',
  where auto class referred to stack allocation. Allocation classes have since been
  dropped from the language.  If a variable is declared at global scope it will be static
  allocated. If a variable is declared in a function then it will be allocated on the
  stack. If a person really needs a register, one must resort to inline asm. Somewhat
  confusingly the 'static' storage class keyword has now been repurposed to mean that a
  declaration is only lexibly visible within file.

  Arrays that are static (storage class) allocated are not thread safe. This is because
  thread safety is achieve because each thread has its own stack, but a statically
  allocated array is not on a stack.

  After the header structure has been allocated we must 'construct' the array by
  allocating some space on the heap and setting the header structure to point to it.
  After construction we have an array 'instance', and we may write and read the array.

  Generally it is undesirable to read data that has never been written.  This makes the
  first write so special that we give it the name 'initialization'.  It is common to
  eliminate the hazard of potentially reading uninitialized data by combining
  intialization with construction, though this is not as common with arrays as it is with
  other objects.

  Actually all data is either 'copied' or 'clobbered'.  The terms 'read' and 'write' refer
  to copies where the source, for read, or the destination, for write, can be referred to
  to with a pronoun without ambiguity.  In our case the 'it' or 'this' pronoun is the TM2x
  type object involved in the copy, whereas the other end of the copy is just a plain old
  poitner to memory.  When a copy moves data between two TM2x's we call the operation a
  'copy'.
