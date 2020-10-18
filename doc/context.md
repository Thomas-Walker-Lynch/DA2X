
# Intro

  Our goal here is to identify techniques for implementing in the C language function like
  entities that we call 'sequences’. The C language is one step away from assembly, and
  thus only two steps away from the processor hardware.  Hopefully this will make the
  implications for processor hardware more clear than when we used the Common Lisp code in
  prior chapters.

# Allocation, Deallocation, Reading, Writing, and Copying

  A memory allocation of is a place to put data.  An allocation is in an a sense an
  abstraction of physical memory device. Like for memory, an allocation has a fixed size,
  and data may be written to it and then later read it back.

  Data refers to the values of the bits found in an allocation.  All data used in a
  computer is copied from a source allocation to a destination allocation.  The data at
  the source is not affected, while the formerly at the destination is clobbered.  There
  are no additional data movement operations.  The terms ‘read’ and ‘write’ simply focus
  on what is happening at one or the other ends of the copy, but do not change what is
  happending at the other end.

# Persistence

  The adjective ‘static’ applies to things resolved by the compiler, linker, or perhaps
  loader; or by an interpreter without taking into account run time state.

  The adjective ‘dynamic’ means something is resolved by executing the program, or at
  least will potentially be resolved that way.

  In the C language lexical scope is a static concept. We can see it when we read our
  program source, but it will be gone by run time.  At run time we will instead have
  dynamic scope for such things as stack frames, and variable lifetimes.

  The process of ‘initialization’ is simply the first write to some data after the data
  has been allocated.  When data is exposed after allocation and before the first write,
  there is read before write hazard.  Generally code is malformed if it reads data before
  initializing it. The term ‘static initialization’ means that a variable was given a
  value at compile time. 

  The C language provides syntax for the initialization of data, though what can be done
  with these C ‘initializers’ is quite limited. When an initializer is applied at compile
  time to statically allocated data, we say that the data has been statically
  initialized. After data is ‘initialized’, if it is never written again, then we say that
  the data is ‘constant’.

  The offsets for the fields of a `struct` are statically initialized constants, and may be
  accessed through the `offsetof` macro.  The compiler may place these directly into
  program text. In general statically initialized constants provide an opportunity for
  compiler optimizations.

  If we have a ‘mutability’ service, we might be able to set data to be ‘read only’ for a
  duration of time, and not read only at other times.  It is fairly common for people to
  refer to read only data as being constant; however, when mutability can be changed, the
  compiler can not take advantage of data being constant, so it is not really useful
  to say that read-only data of this type is ‘constant’.

  The state machine controller of a Turing Machine is static and constant. This is
  noteworthy because our program is the controller definition for our processor. Hence, we
  would not expect that requiring a program to be a statically initialized constant would
  limit their computational power.  If the function pointers in our program do not change
  between uses, the structure of our program will be constant.  One way to assure that the
  function pointers will not change between uses is to make them constants also. With an a
  sufficiently expressive statically coded language, it will be possible to write an
  interpreter where the language being interpreted does not have a not static structure.
  To do this, our non-static program would be coded as data.  The data would then be
  changed at run time to modify the structure of the program.


# Types of allocation

  Memory allocation is the art of setting aside memory to be used by a program. The most
  common types of allocation are: static, program stack base, program stack, and heap.

  All allocators have two main operations on their interface, `allocate` and `deallocate`.
  These are commonly shortened to `alloc`, and `dealloc`. We say that data is a ‘alive’
  after it has been allocated and before it has been deallocated. When the stack is used
  for memory allocation the allocation operator is called `push` and and the deallocation
  operator is `pop`, or sometimes `push` and `pull`.  Languages with garbage collection
  typically have implied allocations when variables are declared, and then periodically
  they scan for orphaned objects and deallocate them all at once as a part of a big
  operation.  When a heap is used we typically keep a free list.  We alloc blocks and
  take them off the free list, then dealloc them to put them back on the free list.

## Static allocation

  The compiler will create a symbol table that associates identifiers with the locations
  of data in memory.  Each location will be either an absolute address or a relative
  offset, but in either case it will be a constant. In the C language paradigm the goal of
  the compiler, linker, and loader, is to embed these constant location values into the
  instructions of the program. 

  Data that has an absolute address determined at compile time is said to have been
  statically allocated.  Such data is only deallocated when the process terminates and releases
  its virtual memory space. For statically allocated data all threads will see the same
  data located in the same place.

  Typically the term ‘static data’ is used to refer to statically allocated data.

## stack base allocation

  The program stack is an instance of a stack data structure, though one that is
  automatically managed possibly with help from the operating system and hardware.

  With ‘program stack base’ allocation, our data is placed in the first stack frame.  This
  is the one that will be allocated to the `main()` function in C.  The first stack frame
  is special as it will never be popped off the stack while the program is running.  This
  gives program stack base allocated data some properties in common with statically
  allocated data: such data has a fixed location, and such data will not be deallocated
  for the entire duration the program is running.

  When a process spawns a new thread, that thread will get a new copy of the
  stack. Conventionally the copy is done in an efficient manner by using the virtual
  memory system and copy on write pages.  Hence, unlike for static allocation, for
  ‘program stack base’ allocation each thread will have its own copy of the allocated
  data.

  The astute reader will note that ‘program stack base’ and ‘program stack’ allocation are
  a first-rest pattern applied to a single program stack.

## Program stack allocation

  Static data and program stack base data live for duration of the program.  In contrast,
  stack allocated data comes to life at run time when the corresponding stack frame is
  pushed, and its life ends when the corresponding stack frame is popped.

  In C a lexical scope starts with an opening brace, and ends with a matching closing
  brace.  Although scope may be nested, all declared variables will be placed in the stack
  frame of the containing function. The enforcement of the nesting of lexical scope within
  the function is due to the compiler itself refusing to allow a programmer to make use of
  out of scope variables. [I am not sure if this behavior is standard, or required by
  the specification.]

  The compiled code will address arguments and local variables at constant offsets
  relative to the base of the function's stack frame. Each function call will start with
  the allocation of a stack frame, thus giving each function call its own copy of
  arguments and variables. Because a function uses stack relative addressing to find its
  variables on the stack, the same code will be usable without modification against any
  stack frame instance. Upon return from a function the stack frame will be deallocated.

  When we use the ampersand operator, ‘&’, on a local variable we will get its absolute
  address.  No matter how far down in the call nesting we go, this absolute address will
  still locate the same value. If we keep such an address in a data structure that is
  generally accessible, there is a hazard that the address will be used after the located
  variable has been deallocated, i.e. used after the function for which it is a local
  variable has returned.

  Although a systems programmer would never do it, we tools smiths could write inline
  assembly to manually allocate and deallocate data on the program stack. This would work
  out provided that our matching allocation/deallocation pairs occur within one function,
  that we deallocate in reverse order than we did the allocations, and that the stack is
  in its original state before the function returns.

  Most programs are written by composing a large number of small functions.  Functions
  need to have their arguments in the same place relative to the stack frame each time
  they are called.  Consequently a great deal of effort will be spent moving data into
  stack frames before function calls. This problem inspired AMD to provide a ‘fast call’
  mode where arguments are passed through registers. Also stack allocation is considered a
  bottleneck for both optimization and hardware acceleration.

## Heap allocation

  With ‘heap’ allocation we have a library of functions that allow us to request blocks of
  memory to be allocated from a free list, then later to be deallocated and put back on
  the free list. In C it is conventional to use the ‘stdlib’ functions which define only
  one heap to be shared by all functions. Heap overhead such as the free list base pointer
  will be statically allocated. The one stdlib heap will be shared by all threads. Modern
  versions of the heap have mutex locks already built in so as to assure thread safety.

# C terminology for storage allocation classes

  The C programming language specification speaks of ‘storage allocation classes’ that are
  built into the language: `register`, `static`, and `auto`.  

  Specifying the `register` storage allocation class is a request to the compiler to place
  the given variable in a register. A C compiler is free to ignore the request and to
  allocate such a variable instead as `auto` class. It is rare to see the `register`
  storage class keyword used because it is almost always better to let the compiler decide
  what should go into a register, and in addition, the compiler is free to ignore it
  anyway.

  Specifying the `static` allocation class for a variable will cause the variable to be
  allocated statically in memory.  This is the default for variables declared at global
  scope.  In very old versions of the C language this used to be the end of the
  story. However, in the spirit of not leaving well enough alone the standards committee
  has added an additional meaning to `static`.  A variable that is allocated statically
  because it was declared at global scope is available to other modules (other source
  files) through the `extern` keyword.  This has always been the case.  The part that is
  new is that if a variable is explicitly declared as static it will not be available to
  other modules through the `extern` keyword. It is fairly useful to be able to set the
  lexical scope of a variable to just the module, so we sometimes see the static keyword
  used.

  Functions in C are always declared at global scope (foregoing gcc
  extensions). Declaring a function is identical to declaring a function pointer, and a
  function pointer is data.  Hence the `static` keyword works the same on functions as
  it does on other data.

  If an inline function is declared `static`, and the compiler decides to ignore the
  request to inline the function, then the function become a `static` function.

  In C `auto` class variables are allocated on the program stack.  This is the default for
  variables declared inside of a function, including inside the main() function.  It is
  rare to see the `auto` storage class keyword used because this is already the default
  behavior inside functions, and at global scope it is illegal to use it.

  So the C terminology for ‘storage allocation class’ overlaps with the generic
  terminology used for allocation, yet it differs in places.  We will use the generic
  terminology in this text.  That will then have to be reduced to correct code.

# Sequences and Continuation

  This is a novel concept introduced here in support of the TTCA.

  A sequence is analogous to a function.  Where as a program will ‘call’ a function, a program
  will ‘continue’ a sequence. We continue to a sequence by executing a continue statement.  A continue
  statement begins with the keyword `continue` and that is followed by the name of the sequence.
  
  ````
      continue mul_ib;
  ```` 

  A sequence is defined by starting with a `SQ·def` macro and ending with a `SQ·end` macro.
  I include a set of matching braces so that my editor C-mode does not get confused.

  This is the syntax used when defining a sequence:


````
      SQ·def(name){


        
      } SQ·end(name);
````

  Unlike functions, sequences do not return. A sequence must continue further or exit
  the program before reaching the closing brace (i.e. the `SQ·end` macro).  If execution
  reaches the closing brace bad things will happen.

  Due to limitations of C labels which are used in the cdef macro, currently a sequence
  may not be declared at global scope. They must be declared within functions.

  Functions do a lot of implied work on the stack.  Arguments, local variables, and
  the return address are pushed, and then later the function returns and they are
  popped.  Sequences do no such implied work on the stack. If the stack is used,
  it is used through explicit functions for manipulating it.

  As will become apparent as we dig further into this discussion, we have two types of
  sequences. Firstly, we have locally defined sequences that are nested within the
  lexical scope of some encapsulating body such as a function or another sequence.  The
  connections between these sequences are set by the encapsulating body.  Secondly we
  have general use sequences. These accept arguments with names like ‘nominal’ and
  ‘fail’.  These arguments are then set at run time to determine the connections between
  the sequences.

# Encapsulating functions

  An encapsulating function is a special form function used to hold sequences. The
  definition of an encapsulating function starts with the `encapsulation(name)` macro, and
  ends with an `eend` macro.

  By contract with the programmer:

  1. We required that all paths of execution stemming from the point of entry will lead to
  a `leave_to` macro call. If we hit the `eend` macro, bad things will happen.

  2. The return value must be one of the `SequencePtr`s that was passed into the
  encapsulation.

  3. Sequences must be declared on the first line of a lexical scope they appear in. (If
  they are not declared, then they will all appear at the top level function scope
  independent of where they occur in lexical scope.)


````
      encapsulation(f)(int i ,SequencePtr not_five ,SequencePtr five){
        Sequence a ,b;

        int j = 7;
        ink k = 9;

        continue a;

        cdef(a){
          continue b;
          cend;
        }

        cdef(b){
          if( i + j + k == 21 )
            leave_to five;
          else
            leave_to not_five;
          cend;
        }

        eend;
      }
````

  Here `f` accepts as arguments an integer and two `SequencePtrs`. The sequences `a` and `b`
  are defined inside the lexical scope of `f`, and neither `a` nor `b` continue  a  sequence
  defined outside of `f`'s lexical scope.

  This function picks one of the passed in sequence pointers to `leave_to`. Here the
  term ‘leave’ refers to leaving the context defined by the encapsulation.  By contract
  with the programmer, an encapsulating function may only `leave_to` a `SequencePtr`
  argument value that was passed in.

  Because `leave_to` returns a sequence pointer we may continue a sequence defined outside 
  of the encapsulation, as shown here:

````
    int main(){
      Sequence not_five ,five;

      int i = 5;

      continue *f( i ,&&not_five ,&&five);

      cdef(not_five){
        printf("%d" ,i);
        return 1;
        cend;
      }

      cdef(five){
        printf("%d" ,i+1);
        return 0;
        cend;
      }

    }
````

  Here `not_five` and `five` are sequences defined in the `main()` function.  The call
  to `f` will continue through to be either `not_five` or to `five`. An examination of `f`
  will show that it always returns the five continuation. Hopefully the optimizer would
  catch on to that and eliminate the function call and the `not_five` sequence.

  Variables declared in an encapsulating function, as for all functions, are by default
  declared in the function's stack frame.  C calls this the ‘auto’ storage class. Thus,
  function encapsulated sequences may share the variables declared in the encapsulation.
  Together we call these variables the ‘context’ of the sequences.

  Though functions normally have only one point of return, we use a trampoline to
  effectively give encapsulating functions multiple points of return. If we had more
  execution over compilation we could eliminate the return and trampoline, and instead pop
  the context off the stack and continue directly to the outer scope. Perhaps someday the
  compiler optimizer will recognize such patterns and do this replacement for us. Also
  likely is that we will end up with a new computer language with native support for
  sequences.

  Gcc has a nested function extension which makes it possible to define encapsulating
  functions inside of other functions. Nested functions may make use of variables found
  in the outer lexical scope context.

## Bound buffers

  Suppose that for each sequence we statically allocate dedicated memory for context,
  and perhaps also for arguments.  Hence there would be one dedicated buffer per
  sequence.

  This would be inefficient as all sequences would be reserving allocated memory even
  when they are not called.  However, it is not much memory, and there are a number of
  computational advantages: 1) It gets rid of the stack bottleneck.  2) it is easy for the
  processor to get ahead in computation 3) simpler for the compiler optimizer to reason
  about 4) simpler for the programmer to reason about.

  This is similar to one line from a reservation station.  We only need the one line
  because of having a single thread of execution.  We typically do not need to keep tokens
  because usually the order of arrival of the operands is known.

  However, there is a problem in that the same function can not be called at two different
  nesting levels without interference between them on the buffer. Each would need their
  own instance of the buffer - just as we would in hardware if we had multiple instances
  of the same execution unit. If we try to perform static analysis then we have the
  problems discussed in the pads section.  If we allocate buffers on entry to the
  sequence, and then deallocate them on exit, we have a pattern similar to
  function encapsulation.  We will explore this further down in this document.

# Pads

  A data pad is a fixed length memory buffer shared by multiple sequences. It may be
  bound to any number of types. In C we will declare these types in advance as `struct`s,
  leading to pad type being a union of `struct`s.

  Because sequences do not return, there is no reason to place their arguments nor a
  return address on to the stack.  Instead, to pass arguments to a sequence we write
  those arguments to a pad, and then the sequence pulls them off the pad as needed.  We
  will then recycle the pad to pass arguments to the next sequence.

  We may do a similar thing with a call to an encapsulation. If we have arguments that are
  not to become messages between the nested sequences, i.e. not to become part of the context,
  then we may use a pad to pass these arguments to the encapsulation.

  While using a pad, a call to a function encapsulation of sequences might look like
  this:

  ````
    P0(p0 ,Inclusive·3opLL ,0);
    p0->a0 = p1->element_n;
    p0->a1 = p1->element_byte_n;
    p0->rpt = &cx->byte_n;
    continue *Inclusive·mul_ext(nominal ,gt_address_t_n);

  ````

  In this example, the P0 macro sets up a pointer to point to the arguments pad. The
  arguments are then copied to the pad, and finally we continue the `Inclusive·mul_ext`
  encapsulation.  Later in our document we will meet `Inclusive·mul_ext` again, though
  as a sequence rather than as an encapsulating function.

  The following example is what the `alloc_array_elements` encapsulation might look like in
  the TM2x·Tape library. We make use of two pads.  One for arguments and one for local
  variables.  We often swap these upon entering an encapsulation so that we might more
  easily build the arguments pad for the next sequence.  The P1 macro sets up a pointer
  to point to this second pad.


  ````
  encapsulation(alloc_array_elements)
    (
     ContinuationPtr nominal
     ,ContinuationPtr index_gt_n
     ,ContinuationPtr alloc_fail
     ){
    Sequence scale ,alloc_array_bytes ,local_index_gt_n ,local_nominal ,local_alloc_fail;
    Sequence·swap();
    P1(p1 ,TM2x·alloc_array_elements ,1);

    tape = p1->tape;
    address_t byte_n;

    continue scale;

    cdef(scale){
      P0(p0 ,Inclusive·3opLL ,0);
      p0->a0 = p1->element_n;
      p0->a1 = p1->element_byte_n;
      p0->rpt = &byte_n;
      continue Inclusive·mul_ext(&&alloc_array_bytes ,&&local_index_gt_n);
      cend;
    };

    cdef(alloc_array_bytes){
      P0(p0 ,TM2x·alloc_array_bytes ,0);
      p0->tape       = tape;
      p0->byte_n     = byte_n;
      continue TM2x·alloc_array_bytes(&&local_nominal ,&&local_alloc_fail);
      cend;
    };

    cdef(local_index_gt_n){
      leave_to index_gt_n;
      cend;
    }

    cdef(local_nominal){
      leave_to nominal;
      cend;
    }

    cdef(local_alloc_fail){
      leave_to alloc_fail;
      cend;
    }


    cend;
  }
  ````

  It is too bad we need the local sequences, `local_index_gt_n`, `local_nominal`, and
  `local_alloc_fail`.  Their sole purpose is to maintain the integrity of the
  encapsulation.  By having `TM2x·alloc_array_bytes` and `Inclusive·mul_ext` first
  continue locally we assure that the stack frame gets popped.  If we did not need to pop
  the stack frame, `TM2x·alloc_array_bytes` and `Inclusive·mul_ext` could continue directly to
  `index_gt_n`, `nominal`, and `alloc_fail`.


# Mixing functions with general use sequences

  Suppose we have defined a general use sequence somewhere for purposes of sharing
  it. It might even be part of a sequence library.  In such a case we might end up with
  code something like this:

````
    encapsulation(f)(SequencePtr nominal ,SequencePtr alloc_fail){

      ...

      struct cx *cx = &cxdat;
      struct p1 *p1 = &p1dat;

      P0(p0 ,Inclusive·3opLL ,0);
      p0->a0 = p1->element_n;
      p0->a1 = p1->element_byte_n;
      p0->rpt = &cx->byte_n;
      p0->nominal = &&alloc_array_bytes;
      p0->gt_address_t_n = p1->index_gt_n;
      continue Inclusive·mul_ext;

      cdef(alloc_array_bytes){
        leave_to nominal;
        cend;
      };

      ...

    }
````

  Here p1 is another data pad. cx is defined in the containing function, although that is
  not shown.

  This time `Inclusive·mul_ext` is a general use sequence from a library. It was included
  into main.  It accepts two values, `a` and `b`, and writes a result to `rtp`.  This
  general use sequence has two continuation arguments, `nominal` and `gt_address_t_n`.
  If the product would overflow the result type, `Inclusive·mul_ext` continues with
  `gt_address_t_n` and no result is written.  Otherwise, it writes the result and
  continues with `nominal`.

  The line `continue Inclusive·mul_ext` will take us out of the containing function to
  execute code found in main. This violates our encapsulation contract, which is why we
  used the term ‘containing function’ instead of ‘encapsulating function’.

  The `Inclusive·mul_ext` sequence will have been compiled against the stack frame of
  main, but when we take the continuation from `f` to `Inclusive·mul_ext` our stack pointer
  will be pointing to the stack frame for `f`, which is the wrong value for
  `Inclusive·mul_ext`. If the `Inclusive·mul_ext` sequence does not use the stack, then
  things might work out; however, this would be hard to accomplish in the C language,
  because stack usage is deeply ingrained with the creation of locals and temporary
  variables. Even if we declare a value to hold a pointer to where local data is really
  stored, that pointer will be in a local variable.  If we try to get around this and
  declare that pointer to be of ‘register’ storage allocation class, C will not guarantee
  that it ends up in a register. The compiler is free to make it a local `auto`
  class variable despite our request to make it a register.

  Assuming that by some miracle things went well `Inclusive·mul_ext` then continues to either
  `alloc_array_bytes` or to `p1->index_gt_n`.

  The sequence `alloc_array_bytes` was defined in the lexical scope for `f`.  Hence
  continueing to it will restore order to the universe.  `alloc_array_bytes` then returns
  from the function via `leave_to nominal`.

  Had we instead continueed `p1->index_gt_n`, the stack to code correspondence would
  remain messed up because `p1->index_gt_n` is not defined within `f`.

  When all sequences out of `f` return to `f`, we say that `f` ‘encapsulates
  sequences with side trips’.  As described in this section, when using the C
  language this is a hazardous pattern.

# Only function encapsulated sequences

  If we require that all general use sequences be function encapsulated, then we
  can use `continue *` to call any of them without having stack pointer hazards.

  When a library function is small we can hope that the optimizer will make the call
  overhead go away by just including the contents of the function.  We can make this more
  likely by declaring the function inline. If it does not inline, then for a normal
  function call our arguments will be redundantly copied into function stack frames.

  Now suppose we have a large library of small function encapsulated sequences, where
  the functions have been declared inline. Although the compiler is free to ignore the
  inline keyword, suppose that the God of C has smiled upon us and the functions really
  are inlined.  In this case not only will the code be duplicated, but all the
  local variables from all the inlined expansion will end up separately and simultaneously
  allocated on the containing functions stack frame.  They will remain there until
  the containing function returns.  If the containing function is `main()`, then they
  will all be there from the start of the program until the program exits.

  Another drawback of this approach is that we will have no general use sequences, but
  rather a function library.  The local use sequences may be of some use, but I had
  hoped the method would generalize.

  Despite the storage inefficiency we must note that this solution does successfully
  manage the allocation of contexts.  


# Sequence encapsulation

  In this section we discuss the approach of using a sequence to encapsulate other
  sequences, thus possibly eliminating all encapsulating functions at a given
  level of computation.  For example we might nest all our sequences in `main()`
  or in other sequences. Then there would be only one relevant stack frame and
  no alignment issues.

  Any local variable that we declare in such a sequence, even a nested one, will end up
  on the stack frame of the containing function. This would be inefficient because locals
  are not needed simultaneously, indeed we might find at run time that some are not used.
  Hence we might want to find alternative means of allocating local variables.

  I use the term ‘context’ to refer to variables that are shared among encapsulated
  sequences.  Because sequences flow in one direction and do not return, such sharing
  takes the form of message passing.  Hence we need to be able to pass messages, and
  having context is one way of accomplishing that.

  When we have messages we will also need a means for addressing the allocation and
  deallocation of messages.

  This is a common pattern:

````
            .--c1
    context .  |
            .  [c2]
             \ |   \
             c1.c3  elsewhere
               | \
````

  c1 is a sequence, c3 is a local sequence defined within c1´s lexical scope.  c2 is a
  general use sequence. At run time c1 will continue c2 before reaching c3.  In turn
  c2 might continue c3 or it might continue elsewhere.  If it continues elsewhere there is
  a good chance that execution will never reach c3.

  c1 allocates some context and leaves that behind for c3 to read. Because it is possible
  that we might not ever reach c3 it is unclear as to how we can guarantee that the
  context gets deallocated.

  Here is a concrete example of this pattern. Here `TM2x·alloc_array_elements` corresponds to c1.
  `Inclusive·mul_ext` corresponds to c2, and `alloc_array_bytes` corresponds to c3.
  `TM2x·alloc_array_elements` is an encapsulating sequence. `alloc_array_bytes` is local
  sequence, and `Inclusive·mul_ext` is a general purpose sequence.  

  Note that execution flow from in `TM2x·alloc_array_elements` never reaches
  `alloc_array_bytes`, rather we reach the end of dynamic scope for
  `TM2x·alloc_array_elements` when it continues to `Inclusive·mul_ext`, yet the static scope
  continues to the closing bracket, so `alloc_array_bytes` is defined within the lexical
  scope of of `TM2x·alloc_array_elements`.  What this accomplishes for us is to make the
  `alloc_array_bytes` entry point viewable to only `TM2x·alloc_array_elements`.
  `TM2x·alloc_array_elements` then uses its ability to see this entry point to give a value
  to the `Inclusive·mul_ext`'s `nominal` sequence argument.

````
    cdef(TM2x·alloc_array_elements){
      Sequence alloc_array_bytes;
      Sequence·swap();
      P1(p1 ,TM2x·alloc_array_elements ,1);

      // CX is a macro that points `cx` at a context pad and gives it type
      CX(cx ,TM2x0 ,alloc_array_elements);
      cx->tape       = p1->tape;
      cx->nominal    = p1->nominal;
      cx->alloc_fail = p1->alloc_fail;

      // P0 is a macro that points `p0` to the arguments pad and gives it type.
      P0(p0 ,Inclusive·3opLL ,0);
      p0->a0 = p1->element_n;
      p0->a1 = p1->element_byte_n;
      p0->rpt = &cx->byte_n;
      p0->nominal = &&alloc_array_bytes;
      p0->gt_address_t_n = p1->index_gt_n;
      continue Inclusive·mul_ext;

      cdef(alloc_array_bytes){
        P0(p0 ,TM2x·alloc_array_bytes ,0);
        p0->tape       = cx->tape;
        p0->byte_n     = cx->byte_n;
        p0->nominal    = cx->nominal;
        p0->alloc_fail = cx->alloc_fail;
        continue TM2x·alloc_array_bytes;
        cend;
      };

      cend;
    }
````

  In this example we use pads for sending arguments.  By convention arguments are always placed
  on `p0`, while `p1` is used as a scratch pad. The swap statement swaps the `p0` and the
  `p1` pads; hence after the swap `TM2x·alloc_array_elements`'s arguments are found on the `p1`
  pad.  This swapping is reminiscent of D flip-flops in hardware.  It registers our inputs to
  a place they will not be overwritten while we set up the inputs for the next
  computation.

  The `CX` macro allocates context, `cx`. Unlike the arguments and scratch pads, which
  might be overwritten on the next sequence call, `cx` will persist until it is
  deallocated.

  After setting up the `p0` pad, this code continues to general purpose sequence
  `Inclusive·mul_ext`, which has its `nominal` sequence argument set to
  `alloc_array_bytes`.  Note that its `gt_address_t_n` sequence argument has been set to
  go elsewhere.

  So we have an open question. How does the context get deallocated?

## Have a garbage collector deallocate messages

  Relative to our example, a conventional garbage collector would not free the message to c3
  if c2 goes elsewhere because the message is still being pointed at.  The garbage
  collector has no way to know that the in limbo execution in elsewhere will not suddenly
  continue c3, or if, on the other hand, it will never continue c3.

  If we identify an algorithm for deallocating the message sent to c3, then it would be
  possible to use that algorithm to instead zero out the message pointer, or put it on a
  list - then the garbage collector could find and deallocate orphaned messages.  However,
  then this yet to be identified algorithm would be providing that answer to the question
  as to how we deallocate messages. Any such algorithm could instead do the deallocation
  directly.

## Context pads

  Suppose we use a recycled pad for the context, just as we suggested for argument
  passing.  Because code can be nested, we will need more than one such pad.

  As long as our program structure is static, the number of pads needed can be determined
  from the static analysis of the program.  With a static structure will be the structure
  of the code, not the run time behavior, that determines the number of pads required.

  It is surprising to find that, because sequences do not return, that a many recursive
  structures which we might expect to require an unbounded number of pads, actually only
  require one.

  Consider for example, if we add tail recursion to our diagram whereby c3 conditionally
  continues into c1.


````
            .--c1
    context .  |
            .  [c2]
             \ |   \
             c1.c3  elsewhere
               | \
              c1

````

   We still only need one context pad, because once we continue from c3 the context pad
   used to send a message from c1 to c3 is no longer needed.

   Now consider a structure where c2 that ‘somewhere else’ the unspecified other continuation
   for c2 mentioned is a continuation back into c1.


````
            .--c1-<--<.
    context .  |      |
            .  [c2]   ^
             \ |   \__|
               c3
               | \


   (c1 c2)(+) c3

    c1 c2 c3
    c1 c2 c1 c2 c3

````

   When, during execution, c2 continues to c1, c1 will still be holding context for c3.
   This context was computed the first time we continued into c1. However, no matter how
   many times we go through this sub-loop, we still only visit c3 one time. Hence upon the
   second trip through c1 we need to either act like it is our first time through, and
   continue fresh on our context pad, or we c1 must be designed to compute the cumulative
   context for c3.  So here too only one pad is needed. If the cumulative message gets
   longer on each loop, and we do not know how many loops will be taken, the pad will
   surely hold a pointer to the heap where the growing structure is stored.  There is
   still only one message, thus we still only need one pad.

   In the following diagram we include c3 in the continuation loop:

````
            .--c1-<--<.
    context .  |      |
            .  [c2]   ^
             \ |   \  |
               c3     ^
               |  \___|


     (c1 c2 c3)(*)... | (c1 c2 c3)(*) c1 c2 ...


````
   When c3 continues into c1 the context is no longer needed, and thus the pad may be
   reused.  This is in fact the first case we discussed, it is just that we included
   the lines in the graph showing the loop instead of showing it as recursion.

   As an example where we need more than one pad, consider a that we have a library
   of separately maintained sequences. This library would need to have its own
   context pads.

   The context pad approach will use less memory than giving each sequence it's own
   context, but it might not be an optimal solution.  For example, at run time, execution
   might not ever pass into deeper nesting layers, yet their context will have been
   allocated. It would be more efficient, from a memory usage standpoint, to only allocate
   pads for deeper nesting layers when they are entered. But if we employ a strategy
   for allocating pads, then we need an algorithm for deallocating them.

   And what about programs that do not have static structure?  This is certainly possible
   because we do make extensive use of the analog of function pointers, sequence pointers. 

   We can extend static analysis to cover simple dynamic structures where the sequence
   arguments are selected from a small number of alternatives. There will exist
   computations for which we can not know in static analysis which selections will be made,
   but we can place all of the possible selections into a set. However, we will run into
   trouble if are conclusions about nesting levels do not have disjoint sets. Extending
   the analysis gets even more difficult as we further generalize the which dynamic
   structures we are willing to analyze.

   Hence, context pads can be a solution to statically analyzable code structures, but
   it is not a general solution. Our TM2x·Tape library is pretty easy to analyze, and given
   the efficiency of context pads, I will probably use them there.

### Context stack

````
            .--c1
    context .  |
            .  [c2]
             \ |   \
             c1.c3  elsewhere
               | \


````

   Suppose that as part of sequence c1 we allocate the context on the stack. The
   question then becomes, when does the context get popped off the stack.  If c2
   goes elsewhere we might not ever go to c3 so it would not be sufficient to put
   the pop there.

   We can not make a rule that leaving c1 by any route pops the stack, because we
   will take a side trip through c2 to get to c3.  If we pop the stack when leaving
   to c2 the context will be gone when we continue c3.

   This suggests that we need sequence encapsulation in analogy to function
   encapsulation.  If we add that, then the only difference between this and function
   encapsulation is that we would not return to the caller.

## Explicit message passing

````
            .--c1
    context .  |
            .  [c2]
             \ |   \
              [c3]  elsewhere
               | \


````

   In this execution flow, c1 is sending a message to c3.  Now suppose that c3 is not
   defined in c1's lexical scope, and that c3 is a general use sequence. Also, let us
   limit analysis here to a single thread of execution.

   c3 still needs two messages, one provided directly as part of being continued into from
   c2.  The other sent by c1 during an earlier point in the execution stream. c3 is
   generally available to be called from multiple sources, so it will need some way to
   know which messages correspond to which when putting them in pairs.

   In data flow systems we accomplish such alignment of messages by giving each a token,
   and then having a reservations stations in front of execution units.  Here our
   execution units are the sequences. Only when a set of matching tokens are received,
   i.e. when all the messages in a synchronized set have arrived, do we continue with
   execution. This approach would require even more memory than dedicating a context pad
   to each sequence.  It would also be unusual to do such a thing when we are not
   synchronizing data between separate threads of execution. It is a too heavy of a
   solution for something like our TM2x·Tape library.

   We will also need some means of allocating and deallocating messages. If explicit
   deallocation is required, c3 cannot be solely responsible for deallocating the message
   from c1, because c2 might continue elsewhere and thus the c3 sequence might not ever
   run.

   Suppose for synchronization we make our ContinuationPtr type hold a pair of pointers.  One
   pointer would be to the sequence to be continued into as before.  The other
   pointer would point to the message.  Thus when c2 continues into c3 it would hand
   it both the arguments and the message. The two both came from the same continuation
   pointer, so like entangled particles, they are already synchronized.

   There is only one path of execution for a given thread.  Hence we could make the
   message for c3 a struct that contains all of the arguments independent of the source,
   c1 would then allocate the message, it would be sent to c2 and c2 would fill in
   more fields in the message, and then the message arrives at c3 where it is used.

   Suppose our message for c3 were allocated on the heap. Just before c2 continues into
   c3, c2 code would go through the unused continuation pointers and deallocate their
   messages. In general, when a sequence continues forward to another sequence it
   would deallocate all the messages in the unused continuation pointers.  This is a
   possible solution to the deallocation problem.

   However, there is a third problem.  And that is setting up the call topology, or
   in the colloquial,  ‘wiring up’ the calls.  General use sequences need to have
   values for the SequencePtr fields, and we need to know when messages are allocated
   and deallocated.  The encapsulating function approach solved these problems
   by providing a layer over the top of the generic sequences where the SequencePtr
   could be given values.


## Sequence encapsulation with context on the stack

   This approach uses an encapsulating sequence to wire up the generic sequences,
   and to provide context for message passing.

````
    cdef(c0){

      continue push(byte_n_of(struct c0) ,cx); // cx points to the stack frame

      swap
      .. copy required p1 fields to cx

      // c1
      cdef(byte_n){
        P0(p0 ,Inclusive·3opLL ,0);
        p0->a0             = p1->element_n;
        p0->a1             = p1->element_byte_n;
        p0->rpt            = &cx->byte_n;
        p0->nominal        = &&src_byte_i;
        p0->gt_address_t_n = pop(byte_n_of(struct c0 ,cx->src_index_gt_n);    // goes elsewhere
        continue Inclusive·mul_ext;
      }

      // c2
      cdef(src_byte_i){
        P0(p0 ,Inclusive·3opLL ,0);
        p0->a0             = cx->src_element_i;
        p0->a1             = cx->element_byte_n;
        p0->rpt            = &cx->src_byte_i;
        p0->nominal        = &&dst_byte_i;
        p0->gt_address_t_n = pop(byte_n_of(struct c0 ,cx->src_index_gt_n);  // goes elsewhere
        continue Inclusive·mul_idx;
        cend;
      }

      // c3
      cdef(dst_byte_i){
        P0(p0 ,Inclusive·3opLL ,0);
        p0->a0             = cx->dst_element_i;
        p0->a1             = cx->element_byte_n;
        p0->rpt            = &cx->dst_byte_i;
        p0->nominal        = &&copy_contiguous_bytes;
        p0->gt_address_t_n = pop(byte_n_of(struct c0 ,cx->dst_index_gt_n);   // goes elsewhere
        continue Inclusive·mul_idx;
        cend;
      }

      // c4
      cdef(copy_contiguous_bytes){
        P0(p0 ,TM2x·construct_copy_contiguous_bytes ,0);
        p0->src             = cx->src;
        p0->src_byte_i      = cx->src_byte_i;
        p0->dst             = cx->dst;
        p0->dst_byte_i      = cx->dst_byte_i;
        p0->byte_n          = cx->byte_n;
        p0->nominal         = pop(byte_n_of(struct c0 ,cx->nominal);         // goes elsewhere
        p0->src_index_gt_n  = pop(byte_n_of(struct c0 ,cx->src_index_gt_n);  // goes elsewhere
        p0->dst_index_gt_n  = pop(byte_n_of(struct c0 ,cx->dst_index_gt_n);  // goes elsewhere
        continue TM2x·copy_contiguous_bytes;
        cend;
      }


      cend
    }
````
Here push and pop are gasket sequences.  They actually receive the arguments
on p1, and they ignore p0.  The p1 args are the size of the push or pop, and
the sequence to come after.  After the push or pop, they continue the sequence
argument, and as the p0 pad is unchanged the new sequence receives its arguments.

This is very close to an encapsulated function; however there is no trampoline. It is a
sort of ‘this is how you wire it up’ for the compiler, and then a direct run
at run time.

## Sequence encapsulation using generic cx_alloc and cx_dealloc

The problem with stack usage is that it has to occur in order. It is difficult
for a processor to execute ahead, or for an optimizer to move code around the
stack pops and pushes.  We could instead `allocate_context` and `deallocate_context`
and then use any algorithm we want to accomplish those steps.  In the simplest case
we would use a context pad and there would be no allocation or deallocation work. In a more
challenging case we would use a heap algorithm.  In the most typical case we would use
stack push and pop.

````
    cdef(c0){

      continue cx_alloc(byte_n_of(struct c0) ,cx); 

      swap
      .. copy required p1 fields to cx

      // c1
      cdef(byte_n){
        P0(p0 ,Inclusive·3opLL ,0);
        p0->a0             = p1->element_n;
        p0->a1             = p1->element_byte_n;
        p0->rpt            = &cx->byte_n;
        p0->nominal        = &&src_byte_i;
        p0->gt_address_t_n = cx_dealloc(byte_n_of(struct c0) ,cx->src_index_gt_n);    // goes elsewhere
        continue Inclusive·mul_ext;
      }

      // c1
      cdef(byte_n){
        P0(p0 ,Inclusive·3opLL ,0);
        p0->a0             = p1->element_n;
        p0->a1             = p1->element_byte_n;
        p0->rpt            = &cx->byte_n;
        p0->nominal        = &&src_byte_i;
        p0->gt_address_t_n = &&leave
        p1->n              = byte_n_of(struct c0);
        p1->sequence     = cx->src_index_gt_n
        continue Inclusive·mul_ext;
      }

      cdef(leave){
        .. do the dealloc
        continue *p1->sequence;
      }     



      // c2
      cdef(src_byte_i){
        P0(p0 ,Inclusive·3opLL ,0);
        p0->a0             = cx->src_element_i;
        p0->a1             = cx->element_byte_n;
        p0->rpt            = &cx->src_byte_i;
        p0->nominal        = &&dst_byte_i;
        p0->gt_address_t_n = cx_dealloc(byte_n_of(struct c0) ,cx->src_index_gt_n);  // goes elsewhere
        continue Inclusive·mul_idx;
        cend;
      }

      // c3
      cdef(dst_byte_i){
        P0(p0 ,Inclusive·3opLL ,0);
        p0->a0             = cx->dst_element_i;
        p0->a1             = cx->element_byte_n;
        p0->rpt            = &cx->dst_byte_i;
        p0->nominal        = &&copy_contiguous_bytes;
        p0->gt_address_t_n = cx_dealloc(byte_n_of(struct c0) ,cx->dst_index_gt_n);   // goes elsewhere
        continue Inclusive·mul_idx;
        cend;
      }

      // c4
      cdef(copy_contiguous_bytes){
        P0(p0 ,TM2x·construct_copy_contiguous_bytes ,0);
        p0->src             = cx->src;
        p0->src_byte_i      = cx->src_byte_i;
        p0->dst             = cx->dst;
        p0->dst_byte_i      = cx->dst_byte_i;
        p0->byte_n          = cx->byte_n;
        p0->nominal         = cx_dealloc(byte_n_of(struct c0) ,cx->nominal);         // goes elsewhere
        p0->src_index_gt_n  = cx_dealloc(byte_n_of(struct c0) ,cx->src_index_gt_n);  // goes elsewhere
        p0->dst_index_gt_n  = cx_dealloc(byte_n_of(struct c0) ,cx->dst_index_gt_n);  // goes elsewhere
        continue TM2x·copy_contiguous_bytes;
        cend;
      }


      cend
 } 

```` 

With a context pad the dealloc step does nothing.  We just re-allocate the pad later.  We
already saw the stack paradigm. Generally the allocation can be moved to just above the
call, however, with a heap like algorithm, the allocation can be moved anywhere before the
call, even all the way to the point of the program starting.

It might be better to break out the various messages instead of having one context that
holds all the local messages, although the one context is simpler to memory manage.  Also,
note we could put the arguments into the sequences context instead of handling them
separately.  If so, then the context would have to be created before the `continue` call so
that the caller can copy the arguments in.

This example looks like a nice generic statement of the problem. It looks like we can
assign cx_alloc and cx_dealloc to different functions so as to implement any of the
proposed context management methods.

# Tableaux

The method of tableaux is related to the method of dedicated buffers. Instead of
giving each sequence a dedicated buffer, which give each continue call a dedicated
buffer.  We will initially use static buffers and require that the program be static
and constant.  Later we can loosen these constraints and accommodate stack allocation
or pads as well.

We start by defining a `Connector`.

````
  struct Connector{
    SequencePtr entry;
    struct Connector *connections;
    void *arguments;
  };
````

The three fields in the connect provide everything a sequence needs to run.  The
entry field provides the entry point,  the connections is a list of connectors to
other sequences.  These will have names like `nominal` and `alloc_fail`, etc.  The
arguments are being passed in to the sequence.


We have something analogous to a program counter.  It points the currently connector
for the currently running sequence.  This connector will be found on the caller's
tableau.

````
  Connector *current;
````

When a general purpose sequence runs it will use `current` for finding its
arguments and continuation sequences.

The tableau then allocates all the buffers dedicated to the encapsulated
sequence calls. This will be allocated in the encapsulating functions stack
frame.  As we plan to initially place all the sequences in main(), this will
be stack base allocated.

````
  struct CopyContiguousElements·Tableau{

    struct{
      struct Inclusive·Args·3opLL0 args;
      struct Inclusive·Cons·3opLL cons;
    } mul_ib_0;

    struct{
      struct Inclusive·Args·3opLL0 args;
      struct Inclusive·Cons·3opLL cons;
    } mul_ei_bi_0;

    struct{
      struct Inclusive·Args·3opLL0 args;
      struct Inclusive·Cons·3opLL cons;
    } mul_ei_bi_1;

    struct{
      struct TM2x·Args·copy_contiguous_bytes0 args;
      struct TM2x·Cons·copy_contiguous_bytes cons;
    } copy_contiguous_bytes_0;

  } CopyContiguousElements·tableau;
````

The above is the tableau for the copy_contiguous_elements sequence.  Each field is dedicated to
each sequence that may be called while performing the copy_contiguous_elements operation.

The tableau will then be used as a sort of chalkboard during run time. When a sequence
dereferences a result argument, and writes a result, that result will be written into an
argument for another sequence.

Before we may use a tableau, we must wire up the sequence connections to make a circuit.
Here this is done with a nested function (a gcc extension).

This connection function is called once before the sequences are run.

With the first version, the tableaux are stack base allocated at compile time.  Once the
tableaux are allocated they must be wired up.  As our program structure is static this can
be done even before the program runs.


````
#define CopyContiguousElements·tableau
void copy_element_init(){ 
  // results
  t.mul_ib_0.args.rpt    = &t.copy_contiguous_bytes_0.args.byte_n;
  t.mul_ei_bi_0.args.rpt = &t.copy_contiguous_bytes_0.args.src_byte_i;
  t.mul_ei_bi_1.args.rpt = &t.copy_contiguous_bytes_0.args.copy_contiguous_bytes_0.dst_byte_i;

  // connectors
  t.mul_ib_0.cons.nominal= (Connector) 
    { .entry = &&Inclusive·mul_idx 
      ,.connections = &t.mul_ei_bi_0.cons
      ,.args = &t.mul_ei_bi_0.args
    }
  t.mul_ib_0.cons.gt_address_t_n = (struct TM2x·Cons·copy_contiguous_elements)(current->cons)->gt_address_t_n;

  t.mul_ib_1.cons.nominal= (Connector) 
    { .entry = &&Inclusive·mul_idx 
      ,.connections = &t.mul_ei_bi_1.cons
      ,.args = &t.mul_ei_bi_1.args
    }
  t.mul_ib_1.cons.gt_address_t_n = (struct TM2x·Cons·copy_contiguous_elements)(current->cons)->gt_address_t_n;

  t.copy_contiguous_bytes_0.cons.mominal = current.connections.nominal;
  t.copy_contiguous_bytes_0.cons.src_index_gt_n = current.connections->src_index_gt_n;
  t.copy_contiguous_bytes_0.cons.src_index_gt_n = current.connections->src_index_gt_n;
}
````

## General continue

Lets consider three nesting levels of sequence encapsulation, grandparent sequence,
parent sequence, and children sequences.  Let's refer to these with the shorter names
of: grandparent, parent, and children.

Each sequence is associated with one tableau. The parent's tableau has a field for the
context of each child. It has an addition field that holds a pointer that points to its
own context. The parent's context will be in the grandparent's tableau.


````
  struct CopyContiguousElements·Tableau{

    struct CopyContiguousElements·Context *this_context; // context is found in the grand parent tableau at this point

    struct MulIb0·Context{
      struct Inclusive·Args·3opLL0 args;
      struct Inclusive·Cons·3opLL cons;
    } mul_ib_0;

    struct MulEiBi0·Context{
      struct Inclusive·Args·3opLL0 args;
      struct Inclusive·Cons·3opLL cons;
    } mul_ei_bi_0;

    struct MulEiBi1·Context{
      struct Inclusive·Args·3opLL0 args;
      struct Inclusive·Cons·3opLL cons;
    } mul_ei_bi_1;

    struct CopyContiguousBytes0·Context{
      struct TM2x·Args·copy_contiguous_bytes0 args;
      struct TM2x·Cons·copy_contiguous_bytes cons;
    } copy_contiguous_bytes_0;

  } CopyContiguousElements·tableau;
````

For a dedicated sequence there will only be one grandparent.  However for a
general purpose sequence, we may continue into the same parent from multiple
different grandparent's.

Say we start execution at the grandparent.  The grandparent then desires to continue a
general purpose parent. The grandparent does this by first setting the parent's context
pointer.  The grandparent then continues to the parent.

### Copy-down

According to the ‘copy-down’ algorithm, the parent sequence shares its leave pointers
with its children, buy copying them into the correct points in the tableau. Then when
a child follows one of these connections it leaves directly without having to pass through
any code in the parent's lexical scope.

The parent sequence then uses the arguments from the context to perform computation. If the
result of a computation is for a child sequence, the parent sequence writes the
result into its tableau where the child has its context. If the result of the computation
is to go to the grandparent, then the sequence uses the address given to it as an
argument to know where to write the result. If temporary variables are required, at least
for now, those are allocated with the arguments.

The parent may leave before continueing to a child by using one of the connections listed
in its context.  A child may leave in the same manner a child may leave by using one
of its connections.

### Short circuits

Once a child leaves a parent sequence's encapsulation, the tableau belonging to the
parent is no longer needed.

What if a general sequence has children, and thus has a tableau, and one of those
children is itself.  Given that connections are constant, this would lead to an infinitely
recursive static structure.  Now suppose, that we curry the general use sequence with
a constant argument.  Hence the same sequence behaves differently at different levels.
It might then be reasonable to write such a program.

### Dereference-up

With copy-down, we execute a routine before run time to wire up the sequences. However,
we can not complete the wiring for general use sequences because their connections at
run time depend upon where they are called from.  Hence at run time when we continue to a
general use sequence we run another connection routine.  Each sequence with children
will have its own routine for doing this.  This run time wiring routine completes the
wiring for that portion of the network. This is an eloquent lazy evaluation approach to
wiring the sequences together.  However, the procrastinated part of the work might have
a lot of copying to do and thus might slow down execution.  This is because each of the
parent's connections might have to be copied to many children. Also because this work
is done at run time the connections map will not be a statically initialized constant.

An alternative algorithm, ‘dereference-up’, to some extent overcomes these drawbacks. With
dereference-up a `GeneralSequencePtr` may be either indirect and relative to another
context, or it may be direct. In either case it will be compile time computable and remain
constant at run time.  When the pointer is indirect it may point to another indirect
pointer, but the chain will eventually arrive at a direct pointer.

With dereference-up the time saved by not having a separate ‘just before call’ connection
step, is traded for the time spent dereferencing pointers to find the call point in the
first place. Indpendent how that tradeoff turns out the connection map can be a statically
initialized constant, in theory.  I say "in theory", because in the C language, if we can
not get the map initialization into C's initializer form, we will have no way to give our
constant initialization code to the compiler. A not so elegant part of copy down is that
we might end up doing a lot of copies that will never be used. With dereference up we
only pay cost on the path that we use.

To implement dereference-up we give each tableau two common fields.  One points to the 
grandparent's tableau, the other points to the context being used by the child in the 
parent's tableau. Hence our abstract base class, to borrow a term from C++, will look
like this:

````
   struct Tableau{
     struct Tableau *grandparent;
     struct Context *child_context;
     };
````

Each of the individual sequence tableau's will have these same first two fields followed
by all the child context structs, if any.

Suppose we have a parent general use sequence that holds context for a number of
children.  This parent will have a number of connections held in its context struct. These
connections are typically called something like ‘nominal’ and ‘fail’.  They are
continuations for the sequence.  

If we were doing copy-down we would copy these connections directly into the corresponding
children connections.  Then when the child continues to such a connection it will do so
directly to where the parent was told to continue.

With dereference-up we instead copy *pointers* to the parent connections into the
corresponding children connections. Then when a child continues to such a connection it finds
a pointer instead of a connection. It then dereferences that pointer to find the actual
connection. This dereferencing occurs automatically as part of the `general_continue`
statement.  Thus we say that we have two types of `GeneralSequence·Ptr` which are in
union.  A *indirect* `GeneralSequence·Ptr` which is the pointer we have been discussing,
and a *direct* `GeneralSequence·Ptr` which is an actual connection.

A direct `GeneralSequence·Ptr` has two fields, a pointer to the code to be continueed, and
a pointer to the sequence's context.

When `general_continue` is called it is given a `GeneralSequence·Ptr` and *another
argument*.  We will get to this *another argument* in a moment.  The `general_continue`
arguments pad is stack base allocated and acts as a sort of higher level program counter.
Hence, the `general_continue` arguments are available to the called sequence, i.e. the
child sequence, while it runs.

When the child goes to continue a connection, it might find in the place of the expected
connection that instead there is an offset value serving as said pointer.  This offset is
relative to the parent's context, which is held in the grandparent's tableau. Thus given
the base of the parent's context, the child may add the offset, and have a derived
direct pointer to the connection.

So the question is then, how does a child find the parent's context, so that it can
complete the pointer indirection?  Whatever method used must be capable of chaining further
to cover the case that the parent's connection is also indirect.

The parent has a pointer to its context when it continues the child, so it could just pass
that as the *another argument*,  but then we run into a problem of chaining, as then we
would need, but not have, a pointer to the context for the grandparent.

As another proposal we might pass a pointer to the parent's tableau as *another argument*, 
and then make the indirect pointers relative to the tableau instead of relative to the
context.  Furthermore we would give each tableau a pointer to the next tableau further up
in the continue chain.  Then when the child runs into an indirect general sequence pointer,
it can look up the pointer to the tableau that holds in the parent's context, and then add
the offset to that to find the next connection in the chain.  

With this approach, this becomes the code for making an indirect pointer, which will
be a constant:

````
    #define SQ·make_indirect_gcp(gcp ns_grandparent ,ns_parent ,sequence_name ,continuation_name) \
      gcp.indirect.offset =                                                 \
        offsetof(ns_grandparent##·Tableau ,sequence_name)                 \
        + offsetof(ns_parent##·Context ,cons)                               \
        + offsetof(ns_parent##·Cons ,continuation_name);                    \
      gcp.indirect.same_offset = gcp.indirect.offset;                       \
      ;
````

The pointers are made at wire up time, which is before the program runs.  Ideally they
would be made by the compiler.  At compile time we will know the namsespace for the
parent, `ns_parent`, as that is where the tableau is that we are initializing.  However, for a
general use sequence, the type of the grandparent depends on who is continueing the general
use sequence, so there might not be a single value for this at compile time.

OK, so we add a second pointer to the top of the tableau abstract parent type, and this is a
pointer to the current child sequence's context.  As the `current_child_context` is now
in the tableau, it need not be an argument for `general_continue`.  `general_continue` is left
with a single argument, that of a pointer to the tableau.

# Dereference-up algorithm proposal

Sequence c0 has a tableau that holds contexts for other general purpose sequences. c1 is
such a sequence.  c0 then continues c1.  c1 also has a tableau, and it holds contexts for
other sequences also, including for c2.

Suppose we executing in c1 and reach the point where we will call `general_continue c2`.

## Before continueing `general_continue`

`general_continue` is in the main lexical scope.  It makes uses an arguments pad, and the pad is
stack base allocated and also within the main lexical scope.

we must copy `general_continue`'s two arguments to its arguments pad before executing
`continue general_continue`.  One argument is a pointer to a tableau, and the other is a copy
of  a `GeneralSequence·Ptr`.  

Specifically in our example case, the c1 sequence copies a pointer to its tableau to
`general_continue`'s arguments pad, and it copies the connection it wants to follow to the
arguments pad.  It then executes `continue general_continue`.

## direct `general_continue` to a child

In this case c1's tableau holds c2's context (arguments and connections).  Thus c2 is 
encapsulated by c1. 

For a direct connection, the `continue general` statement executed in c1 does the following:
1. Copies the connection leading to c2 to `GeneralConvey·args.next`.  This is the second
   argument.
2. Places a copy of the c2's context pointer into c1's `ns##·tableau.context_in_use`.
   This pointer is found in the second argument passed in.
3. It then continues c2. 

After these steps there are three pointers to c2's context.  One is at the top of
the c1's tableau, and the two others are in the original and the copy of the
connection. Perhaps we can optimize out this redundancy later.

## c2 execution

Among the first things that c2 does is that it copies `GeneralConvey·args.tableau`, which
points to c1's tableau, into its own `ns##·Tableau.tableau_up`.  This will be needed later
for resolving indirect `GeneralSequence·Ptr` values.

c2 was obliged to do this copy, because c1 and `general_continue` do not know where the c2's
tableau is located, whereas c2 has this information compiled into it. Perhaps we could
have instead added a child tableau pointer to connections. (another potential other improvement
to add to the list along with separating out the constant connection network.)

## c2 leaves c1's encapsulation

In this case c2 has an indirect connection that points into c1's connections, and that
connection leads to a place outside of c1's encapsulation, say at c3.  The indirect
connection holds an offset that is relative to c1's context.

In preparation to continueing `general_continue` c2 copies arguments.  The first argument
is a pointer to c2's tableau.  The second argument is a copy of the connection. This
step is identical to the description in ‘Before continueing `general_continue`. c2 then
continues `general_continue`.

The indirect `general_continue` does the following:

1. It uses its first argument to find c2's tableau. It then access the `tableau_up` field
   to locate c1's tableau.
2. It copies the pointer to c1's tableau into the first argument. Thus overwriting
   the tableau pointer to c2's tableau.
3. It then accesses the `tableau_up` field in c1's tableau to locate c0's tableau.
   It then uses the `context_in_use` field in c0's tableau to find c1's context. 
4. Given a pointer to c1's context, `general_continue` adds the offset provided in its
   second argument to locate c1's leave connection to c3.  `general_continue` then copies
   this connection into its own second argument.  At this point we are in an analogous
   position to where we started, but for c1 rather than for c2.
5. `general_continue` then continues to `general_continue`. In a well formed program, eventually
   any chain of indirect pointer will eventually lead to a direct pointer.
6. Among the first things that c3 does is that it copies `GeneralConvey·args.tableau`, which
   points to c1's tableau, into its own `ns##·Tableau.tableau_up`.  This will mess up ..
   
This is too complex to start with .. an obvious simplification would be to put prior 
context pointers on the stack  and then pop and use them when derefering up..
   
.. copy-down is simpler to understand and probably to debug, so it is a better place to
get started.
