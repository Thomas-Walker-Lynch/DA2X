# 1 "TM2x·test.c"
# 1 "/home/morpheus/projects/tranche_dev/TM2x/test//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "TM2x·test.c"

# 1 "/usr/include/stdlib.h" 1 3 4
# 25 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 33 "/usr/include/bits/libc-header-start.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 465 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 452 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 453 "/usr/include/sys/cdefs.h" 2 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 454 "/usr/include/sys/cdefs.h" 2 3 4
# 466 "/usr/include/features.h" 2 3 4
# 489 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 490 "/usr/include/features.h" 2 3 4
# 34 "/usr/include/bits/libc-header-start.h" 2 3 4
# 26 "/usr/include/stdlib.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 1 3 4
# 209 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 3 4

# 209 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 321 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 3 4
typedef int wchar_t;
# 32 "/usr/include/stdlib.h" 2 3 4







# 1 "/usr/include/bits/waitflags.h" 1 3 4
# 40 "/usr/include/stdlib.h" 2 3 4
# 1 "/usr/include/bits/waitstatus.h" 1 3 4
# 41 "/usr/include/stdlib.h" 2 3 4
# 55 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/floatn.h" 1 3 4
# 119 "/usr/include/bits/floatn.h" 3 4
# 1 "/usr/include/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/bits/floatn-common.h" 3 4
# 1 "/usr/include/bits/long-double.h" 1 3 4
# 25 "/usr/include/bits/floatn-common.h" 2 3 4
# 120 "/usr/include/bits/floatn.h" 2 3 4
# 56 "/usr/include/stdlib.h" 2 3 4


typedef struct
  {
    int quot;
    int rem;
  } div_t;



typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;





__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
# 97 "/usr/include/stdlib.h" 3 4
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;



extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;



extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 176 "/usr/include/stdlib.h" 3 4
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));




extern int strfromd (char *__dest, size_t __size, const char *__format,
       double __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));

extern int strfromf (char *__dest, size_t __size, const char *__format,
       float __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));

extern int strfroml (char *__dest, size_t __size, const char *__format,
       long double __f)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3)));
# 385 "/usr/include/stdlib.h" 3 4
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;


extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;




# 1 "/usr/include/sys/types.h" 1 3 4
# 27 "/usr/include/sys/types.h" 3 4


# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/timesize.h" 1 3 4
# 29 "/usr/include/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 142 "/usr/include/bits/types.h" 2 3 4
# 1 "/usr/include/bits/time64.h" 1 3 4
# 143 "/usr/include/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 30 "/usr/include/sys/types.h" 2 3 4



typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;


typedef __loff_t loff_t;




typedef __ino_t ino_t;
# 59 "/usr/include/sys/types.h" 3 4
typedef __dev_t dev_t;




typedef __gid_t gid_t;




typedef __mode_t mode_t;




typedef __nlink_t nlink_t;




typedef __uid_t uid_t;





typedef __off_t off_t;
# 97 "/usr/include/sys/types.h" 3 4
typedef __pid_t pid_t;





typedef __id_t id_t;




typedef __ssize_t ssize_t;





typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;





typedef __key_t key_t;




# 1 "/usr/include/bits/types/clock_t.h" 1 3 4






typedef __clock_t clock_t;
# 127 "/usr/include/sys/types.h" 2 3 4

# 1 "/usr/include/bits/types/clockid_t.h" 1 3 4






typedef __clockid_t clockid_t;
# 129 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/time_t.h" 1 3 4






typedef __time_t time_t;
# 130 "/usr/include/sys/types.h" 2 3 4
# 1 "/usr/include/bits/types/timer_t.h" 1 3 4






typedef __timer_t timer_t;
# 131 "/usr/include/sys/types.h" 2 3 4
# 144 "/usr/include/sys/types.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 1 3 4
# 145 "/usr/include/sys/types.h" 2 3 4



typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;




# 1 "/usr/include/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 156 "/usr/include/sys/types.h" 2 3 4


typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;


typedef int register_t __attribute__ ((__mode__ (__word__)));
# 176 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/endian.h" 1 3 4
# 24 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/endian.h" 1 3 4
# 35 "/usr/include/bits/endian.h" 3 4
# 1 "/usr/include/bits/endianness.h" 1 3 4
# 36 "/usr/include/bits/endian.h" 2 3 4
# 25 "/usr/include/endian.h" 2 3 4
# 35 "/usr/include/endian.h" 3 4
# 1 "/usr/include/bits/byteswap.h" 1 3 4
# 33 "/usr/include/bits/byteswap.h" 3 4
static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{

  return __builtin_bswap16 (__bsx);



}






static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{

  return __builtin_bswap32 (__bsx);



}
# 69 "/usr/include/bits/byteswap.h" 3 4
__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{

  return __builtin_bswap64 (__bsx);



}
# 36 "/usr/include/endian.h" 2 3 4
# 1 "/usr/include/bits/uintn-identity.h" 1 3 4
# 32 "/usr/include/bits/uintn-identity.h" 3 4
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}

static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}

static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
# 37 "/usr/include/endian.h" 2 3 4
# 177 "/usr/include/sys/types.h" 2 3 4


# 1 "/usr/include/sys/select.h" 1 3 4
# 30 "/usr/include/sys/select.h" 3 4
# 1 "/usr/include/bits/select.h" 1 3 4
# 22 "/usr/include/bits/select.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 23 "/usr/include/bits/select.h" 2 3 4
# 31 "/usr/include/sys/select.h" 2 3 4


# 1 "/usr/include/bits/types/sigset_t.h" 1 3 4



# 1 "/usr/include/bits/types/__sigset_t.h" 1 3 4




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 5 "/usr/include/bits/types/sigset_t.h" 2 3 4


typedef __sigset_t sigset_t;
# 34 "/usr/include/sys/select.h" 2 3 4



# 1 "/usr/include/bits/types/struct_timeval.h" 1 3 4







struct timeval
{
  __time_t tv_sec;
  __suseconds_t tv_usec;
};
# 38 "/usr/include/sys/select.h" 2 3 4

# 1 "/usr/include/bits/types/struct_timespec.h" 1 3 4
# 10 "/usr/include/bits/types/struct_timespec.h" 3 4
struct timespec
{
  __time_t tv_sec;



  __syscall_slong_t tv_nsec;
# 26 "/usr/include/bits/types/struct_timespec.h" 3 4
};
# 40 "/usr/include/sys/select.h" 2 3 4



typedef __suseconds_t suseconds_t;





typedef long int __fd_mask;
# 59 "/usr/include/sys/select.h" 3 4
typedef struct
  {






    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];


  } fd_set;






typedef __fd_mask fd_mask;
# 91 "/usr/include/sys/select.h" 3 4

# 101 "/usr/include/sys/select.h" 3 4
extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
# 113 "/usr/include/sys/select.h" 3 4
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);
# 126 "/usr/include/sys/select.h" 3 4

# 180 "/usr/include/sys/types.h" 2 3 4





typedef __blksize_t blksize_t;






typedef __blkcnt_t blkcnt_t;



typedef __fsblkcnt_t fsblkcnt_t;



typedef __fsfilcnt_t fsfilcnt_t;
# 227 "/usr/include/sys/types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes.h" 1 3 4
# 23 "/usr/include/bits/pthreadtypes.h" 3 4
# 1 "/usr/include/bits/thread-shared-types.h" 1 3 4
# 44 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/pthreadtypes-arch.h" 1 3 4
# 21 "/usr/include/bits/pthreadtypes-arch.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 22 "/usr/include/bits/pthreadtypes-arch.h" 2 3 4
# 45 "/usr/include/bits/thread-shared-types.h" 2 3 4




typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;

typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
# 74 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/struct_mutex.h" 1 3 4
# 22 "/usr/include/bits/struct_mutex.h" 3 4
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;

  unsigned int __nusers;



  int __kind;

  short __spins;
  short __elision;
  __pthread_list_t __list;
# 53 "/usr/include/bits/struct_mutex.h" 3 4
};
# 75 "/usr/include/bits/thread-shared-types.h" 2 3 4
# 87 "/usr/include/bits/thread-shared-types.h" 3 4
# 1 "/usr/include/bits/struct_rwlock.h" 1 3 4
# 23 "/usr/include/bits/struct_rwlock.h" 3 4
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;

  int __cur_writer;
  int __shared;
  signed char __rwelision;




  unsigned char __pad1[7];


  unsigned long int __pad2;


  unsigned int __flags;
# 55 "/usr/include/bits/struct_rwlock.h" 3 4
};
# 88 "/usr/include/bits/thread-shared-types.h" 2 3 4




struct __pthread_cond_s
{
  __extension__ union
  {
    __extension__ unsigned long long int __wseq;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __wseq32;
  };
  __extension__ union
  {
    __extension__ unsigned long long int __g1_start;
    struct
    {
      unsigned int __low;
      unsigned int __high;
    } __g1_start32;
  };
  unsigned int __g_refs[2] ;
  unsigned int __g_size[2];
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
};
# 24 "/usr/include/bits/pthreadtypes.h" 2 3 4



typedef unsigned long int pthread_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;




typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;



typedef unsigned int pthread_key_t;



typedef int pthread_once_t;


union pthread_attr_t
{
  char __size[56];
  long int __align;
};

typedef union pthread_attr_t pthread_attr_t;




typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;


typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;





typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;

typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;





typedef volatile int pthread_spinlock_t;




typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;

typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
# 228 "/usr/include/sys/types.h" 2 3 4



# 395 "/usr/include/stdlib.h" 2 3 4






extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));


extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));





extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };

extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));

extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));

extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));



extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));







extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;

  };


extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;

extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;






extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));







extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__))
     __attribute__ ((__alloc_size__ (2, 3)));



extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));


# 1 "/usr/include/alloca.h" 1 3 4
# 24 "/usr/include/alloca.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 1 3 4
# 25 "/usr/include/alloca.h" 2 3 4







extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));






# 569 "/usr/include/stdlib.h" 2 3 4





extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;




extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;




extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (2))) ;



extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));







extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));





extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 647 "/usr/include/stdlib.h" 3 4
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));





extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));


extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));






extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
# 675 "/usr/include/stdlib.h" 3 4
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 688 "/usr/include/stdlib.h" 3 4
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
# 710 "/usr/include/stdlib.h" 3 4
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
# 731 "/usr/include/stdlib.h" 3 4
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 784 "/usr/include/stdlib.h" 3 4
extern int system (const char *__command) ;
# 800 "/usr/include/stdlib.h" 3 4
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;






typedef int (*__compar_fn_t) (const void *, const void *);
# 820 "/usr/include/stdlib.h" 3 4
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;







extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
# 840 "/usr/include/stdlib.h" 3 4
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;






extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;


__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
# 872 "/usr/include/stdlib.h" 3 4
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;




extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;




extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));

extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));





extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));


extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));



extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));

extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__));







extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
# 957 "/usr/include/stdlib.h" 3 4
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
# 1003 "/usr/include/stdlib.h" 3 4
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 1013 "/usr/include/stdlib.h" 3 4
# 1 "/usr/include/bits/stdlib-float.h" 1 3 4
# 1014 "/usr/include/stdlib.h" 2 3 4
# 1023 "/usr/include/stdlib.h" 3 4

# 3 "TM2x·test.c" 2
# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 1 3 4
# 34 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 37 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/bits/types/__fpos_t.h" 1 3 4




# 1 "/usr/include/bits/types/__mbstate_t.h" 1 3 4
# 13 "/usr/include/bits/types/__mbstate_t.h" 3 4
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/bits/types/__fpos_t.h" 2 3 4




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 40 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/__fpos64_t.h" 1 3 4
# 10 "/usr/include/bits/types/__fpos64_t.h" 3 4
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 41 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/__FILE.h" 1 3 4



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 42 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/FILE.h" 1 3 4



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 43 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/bits/types/struct_FILE.h" 1 3 4
# 35 "/usr/include/bits/types/struct_FILE.h" 3 4
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
# 44 "/usr/include/stdio.h" 2 3 4
# 52 "/usr/include/stdio.h" 3 4
typedef __gnuc_va_list va_list;
# 84 "/usr/include/stdio.h" 3 4
typedef __fpos_t fpos_t;
# 133 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 134 "/usr/include/stdio.h" 2 3 4



extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
# 173 "/usr/include/stdio.h" 3 4
extern FILE *tmpfile (void) ;
# 187 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;




extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
# 204 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;







extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);
# 227 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 246 "/usr/include/stdio.h" 3 4
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 279 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
# 292 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;





extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
# 379 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));






extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 432 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));




extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 485 "/usr/include/stdio.h" 3 4
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);






extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 510 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);
# 521 "/usr/include/stdio.h" 3 4
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);
# 537 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;
# 603 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) ;







extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);
# 673 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);







extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);
# 707 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 731 "/usr/include/stdio.h" 3 4
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 757 "/usr/include/stdio.h" 3 4
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;







extern void perror (const char *__s);





# 1 "/usr/include/bits/sys_errlist.h" 1 3 4
# 26 "/usr/include/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern const char *const sys_errlist[];
# 782 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 800 "/usr/include/stdio.h" 3 4
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
# 840 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 858 "/usr/include/stdio.h" 3 4
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 873 "/usr/include/stdio.h" 3 4

# 4 "TM2x·test.c" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4

# 1 "/usr/include/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4







# 1 "/usr/include/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4





typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 71 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 87 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 101 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stdint.h" 2 3 4
# 5 "TM2x·test.c" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stdbool.h" 1 3 4
# 6 "TM2x·test.c" 2


# 1 "../include/MallocCounter.h" 1




# 4 "../include/MallocCounter.h"
static size_t MallocCounter\U000000b7count = 0;
# 9 "TM2x·test.c" 2
# 1 "../include/TM2x.h" 1



# 1 "../include/TM2xHd.lib.h" 1





# 1 "/usr/include/string.h" 1 3 4
# 26 "/usr/include/string.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/string.h" 2 3 4






# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 1 3 4
# 34 "/usr/include/string.h" 2 3 4
# 43 "/usr/include/string.h" 3 4

# 43 "/usr/include/string.h" 3 4
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 91 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 122 "/usr/include/string.h" 3 4
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



# 1 "/usr/include/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/bits/types/locale_t.h" 3 4
# 1 "/usr/include/bits/types/__locale_t.h" 1 3 4
# 28 "/usr/include/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 154 "/usr/include/string.h" 2 3 4


extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 226 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 253 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 273 "/usr/include/string.h" 3 4
extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 303 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 330 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 385 "/usr/include/string.h" 3 4
extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
# 410 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)));
# 428 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/strings.h" 1 3 4
# 23 "/usr/include/strings.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/stddef.h" 1 3 4
# 24 "/usr/include/strings.h" 2 3 4










extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bcopy (const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 68 "/usr/include/strings.h" 3 4
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 96 "/usr/include/strings.h" 3 4
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));



# 433 "/usr/include/string.h" 2 3 4



extern void explicit_bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));


extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 499 "/usr/include/string.h" 3 4

# 7 "../include/TM2xHd.lib.h" 2
# 1 "../include/TM2x.lib.h" 1





# 1 "/usr/include/assert.h" 1 3 4
# 64 "/usr/include/assert.h" 3 4



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



# 7 "../include/TM2x.lib.h" 2
# 1 "../include/inclusive.h" 1
# 13 "../include/inclusive.h"
# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/limits.h" 1 3 4
# 34 "/usr/lib/gcc/x86_64-redhat-linux/10/include/limits.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/syslimits.h" 1 3 4






# 1 "/usr/lib/gcc/x86_64-redhat-linux/10/include/limits.h" 1 3 4
# 195 "/usr/lib/gcc/x86_64-redhat-linux/10/include/limits.h" 3 4
# 1 "/usr/include/limits.h" 1 3 4
# 26 "/usr/include/limits.h" 3 4
# 1 "/usr/include/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/limits.h" 2 3 4
# 183 "/usr/include/limits.h" 3 4
# 1 "/usr/include/bits/posix1_lim.h" 1 3 4
# 27 "/usr/include/bits/posix1_lim.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/posix1_lim.h" 2 3 4
# 161 "/usr/include/bits/posix1_lim.h" 3 4
# 1 "/usr/include/bits/local_lim.h" 1 3 4
# 38 "/usr/include/bits/local_lim.h" 3 4
# 1 "/usr/include/linux/limits.h" 1 3 4
# 39 "/usr/include/bits/local_lim.h" 2 3 4
# 162 "/usr/include/bits/posix1_lim.h" 2 3 4
# 184 "/usr/include/limits.h" 2 3 4



# 1 "/usr/include/bits/posix2_lim.h" 1 3 4
# 188 "/usr/include/limits.h" 2 3 4
# 196 "/usr/lib/gcc/x86_64-redhat-linux/10/include/limits.h" 2 3 4
# 8 "/usr/lib/gcc/x86_64-redhat-linux/10/include/syslimits.h" 2 3 4
# 35 "/usr/lib/gcc/x86_64-redhat-linux/10/include/limits.h" 2 3 4
# 14 "../include/inclusive.h" 2
# 1 "../include/Continuation.h" 1
# 10 "../include/Continuation.h"
  
# 10 "../include/Continuation.h"
 typedef void **continuation;
# 15 "../include/inclusive.h" 2
# 33 "../include/inclusive.h"
  typedef unsigned __int128 uint128_t;





  static inline continuation mul_ib(uint64_t an ,uint64_t bn ,uint64_t *cn ,continuation nominal ,continuation overflow){
    uint128_t d_an = an, d_bn = bn, d_cn;
    d_cn = d_an * d_bn + d_an + d_bn;
    if( d_cn > 
# 42 "../include/inclusive.h" 3 4
              (18446744073709551615UL) 
# 42 "../include/inclusive.h"
                          ) return overflow;
    *cn = d_cn;
    return nominal;
  }

  static inline uint64_t binary_interval_inclusive_upper_bound(uint64_t byte_n){
    if( byte_n == 0 ) return 1;
    return (1 << (64 - __builtin_clz(byte_n))) - 1;
  }
# 8 "../include/TM2x.lib.h" 2

# 1 "../include/misc.h" 1
# 10 "../include/TM2x.lib.h" 2
# 1 "../include/TM2x·misc.h" 1
# 11 "../include/TM2x.lib.h" 2
# 27 "../include/TM2x.lib.h"
  static inline continuation mallocn(void **pt ,uint64_t n ,continuation nominal ,continuation fail){
    if( n == 
# 28 "../include/TM2x.lib.h" 3 4
            (18446744073709551615UL) 
# 28 "../include/TM2x.lib.h"
                        ) return fail;
    *pt = (MallocCounter\U000000b7count++ ,malloc(n+1));
    if(!*pt) return fail;
    return nominal;
  }




  extern uint64_t TM2x\U000000b7constructed_count;




  typedef struct {
    char *base_pt;
    uint64_t byte_n;
  } TM2x;
# 54 "../include/TM2x.lib.h"
  static inline void TM2x\U000000b7destruct(TM2x *tape){
    (MallocCounter\U000000b7count-- ,free(tape->base_pt));
    TM2x\U000000b7constructed_count--;
  }


  static inline continuation TM2x\U000000b7alloc_heap
  ( TM2x **tape
   ,uint64_t element_n
   ,uint64_t element_byte_n
   ,continuation nominal
   ,continuation fail
   ){
    return mallocn((void **)tape ,sizeof(TM2x)-1 ,nominal ,fail);
  }
  static inline void TM2x\U000000b7dealloc_heap(TM2x *tape){
    TM2x\U000000b7destruct(tape);
    (MallocCounter\U000000b7count-- ,free(tape));
  }



    extern uint64_t TM2x\U000000b7test_after_allocation_n;

  static inline continuation TM2x\U000000b7resize_bytes
  ( TM2x *tape
   ,uint64_t after_byte_n
   ,continuation nominal
   ,continuation alloc_fail
   ){

    uint64_t before_alloc_n = binary_interval_inclusive_upper_bound(tape->byte_n);
    uint64_t after_alloc_n = binary_interval_inclusive_upper_bound(after_byte_n);

    if( after_alloc_n == before_alloc_n ){
      tape->byte_n = after_byte_n;
      return nominal;
    }

    char *after_base_pt;





# 1 "../include/CLib·mallocn.h" 1
# 19 "../include/CLib·mallocn.h"
  CLib\U000000b7mallocn:{
    if( after_alloc_n == 
# 20 "../include/CLib·mallocn.h" 3 4
            (18446744073709551615UL) 
# 20 "../include/CLib·mallocn.h"
                        ) goto malloc_fail;
    (void **)&after_base_pt = (MallocCounter\U000000b7count++ ,malloc(after_alloc_n+1));
    if(!*(void **)&after_base_pt) goto malloc_fail;
    goto malloc_nominal;
    abort();
  }
# 100 "../include/TM2x.lib.h" 2

    goto CLib\U000000b7mallocn;

    malloc_nominal:{

        TM2x\U000000b7test_after_allocation_n = after_alloc_n;

      uint64_t copy_n = after_byte_n < tape->byte_n ? after_byte_n : tape->byte_n;
      memcpy(after_base_pt ,tape->base_pt ,copy_n+1);
      (MallocCounter\U000000b7count-- ,free(tape->base_pt));
      tape->base_pt = after_base_pt;
      tape->byte_n = after_byte_n;
      return nominal;
      abort();
    }
    malloc_fail:{
     return alloc_fail;
     abort();
    }

  }

  static inline continuation TM2x\U000000b7resize_elements
  ( TM2x *tape
    ,uint64_t after_element_n
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_index
    ){
    uint64_t after_byte_n;
    goto * mul_ib(after_element_n ,element_byte_n ,&after_byte_n ,&&mul_ib\U000000b7nominal ,&&mul_ib\U000000b7overflow);
    mul_ib\U000000b7nominal:{
      return TM2x\U000000b7resize_bytes(tape ,after_byte_n ,nominal ,alloc_fail);
    }
    mul_ib\U000000b7overflow:{
      return bad_index;
    }
  }

  static inline uint64_t TM2x\U000000b7constructed(TM2x *tape){
    return TM2x\U000000b7constructed_count;
  }
# 151 "../include/TM2x.lib.h"
  static inline continuation TM2x\U000000b7construct_bytes
  ( TM2x *tape
   ,uint64_t byte_n
   ,continuation construct_nominal
   ,continuation construct_alloc_fail
   ){
    TM2x\U000000b7constructed_count++;
    tape->byte_n = byte_n;
    uint64_t alloc_byte_n = binary_interval_inclusive_upper_bound(byte_n);
    goto * mallocn( (void **)&(tape->base_pt) ,alloc_byte_n ,&&mallocn_nominal ,&&mallocn_fail);
      mallocn_nominal: return construct_nominal;
      mallocn_fail: return construct_alloc_fail;
  }
  static inline continuation TM2x\U000000b7construct_elements
  ( TM2x *tape
    ,uint64_t element_n
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_index
    ){
    uint64_t byte_n;
    goto * mul_ib(element_n ,element_byte_n ,&byte_n ,&&mul_ib\U000000b7nominal ,&&mul_ib\U000000b7overflow);
    mul_ib\U000000b7nominal:{
      return TM2x\U000000b7construct_bytes(tape ,byte_n ,nominal ,alloc_fail);
    }
    mul_ib\U000000b7overflow:{
      return bad_index;
    }
  }





  static inline continuation TM2x\U000000b7alloc_heap_construct
  ( TM2x **tape
    ,uint64_t element_n
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation fail
    ,continuation bad_index
    ){
    goto * mallocn((void **)tape ,sizeof(TM2x)-1 ,&&mallocn_nominal ,&&mallocn_fail);
      mallocn_nominal:
        goto * TM2x\U000000b7construct_elements(*tape ,element_n ,element_byte_n ,&&construct_nominal ,&&construct_fail ,&&construct_bad_index);
          construct_fail: return fail;
          construct_nominal: return nominal;
          construct_bad_index: return bad_index;
      mallocn_fail: return fail;
    }

  static inline continuation TM2x\U000000b7construct_write_bytes
  ( TM2x *tape
    ,void *source_pt
    ,uint64_t source_byte_n
    ,continuation nominal
    ,continuation fail
    ){
    goto * TM2x\U000000b7construct_bytes(tape ,source_byte_n ,&&construct_nominal ,&&construct_fail);
      construct_nominal:
        memcpy(tape->base_pt ,source_pt ,source_byte_n+1);
        return nominal;
      construct_fail: return fail;
  }


  static inline continuation TM2x\U000000b7construct_write
  ( TM2x *tape
    ,void *element_base_pt
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation fail
    ){
    return TM2x\U000000b7construct_write_bytes(tape ,element_base_pt ,element_byte_n ,nominal ,fail);
  }


  static inline continuation TM2x\U000000b7construct_write_elements
  ( TM2x *tape
    ,void *base_pt
    ,uint64_t element_n
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation fail
    ,continuation bad_index
    ){
    uint64_t byte_n;
    goto * mul_ib(element_n ,element_byte_n ,&byte_n ,&&mul_ib\U000000b7nominal ,&&mul_ib\U000000b7overflow);
    mul_ib\U000000b7nominal:{
      return TM2x\U000000b7construct_write(tape ,base_pt ,byte_n ,nominal ,fail);
    }
    mul_ib\U000000b7overflow:{
      return bad_index;
    }
  }


  static inline continuation TM2x\U000000b7construct_write_TM2x
  ( TM2x *tape
    ,TM2x *tape_source
    ,continuation nominal
    ,continuation fail
    ){
    return TM2x\U000000b7construct_write(tape ,tape_source->base_pt ,tape_source->byte_n ,nominal ,fail);
  }
# 270 "../include/TM2x.lib.h"
  static inline char *TM2x\U000000b7byte_0_pt(TM2x *tape){
    return tape->base_pt;
  }
  static inline void *TM2x\U000000b7element_0_pt(TM2x *tape){
    return tape->base_pt;
  }


  static inline uint64_t TM2x\U000000b7byte_n(TM2x *tape){
    return tape->byte_n;
  }


  static inline uint64_t TM2x\U000000b7element_n(TM2x *tape ,uint64_t element_byte_n){
    return tape->byte_n/(element_byte_n + 1);
  }


  static inline char *TM2x\U000000b7byte_n_pt(TM2x *tape){
    return tape->base_pt + tape->byte_n;
  }
  static inline void *TM2x\U000000b7element_n_pt(TM2x *tape ,uint64_t element_byte_n){
    return TM2x\U000000b7byte_n_pt(tape) - element_byte_n;
  }
# 302 "../include/TM2x.lib.h"
  static inline void *TM2x\U000000b7element_i_pt(TM2x *tape ,uint64_t index ,uint64_t element_byte_n){
    return TM2x\U000000b7byte_0_pt(tape) + element_byte_n * index + index;
  }

  static inline void TM2x\U000000b7read(TM2x *tape ,uint64_t index ,void *dst_element_pt ,uint64_t element_byte_n){
    void *src_element_pt = TM2x\U000000b7element_i_pt(tape ,index ,element_byte_n);
    memcpy(dst_element_pt ,src_element_pt ,element_byte_n+1);
  }


  static inline continuation TM2x\U000000b7write_bytes
  ( void *src_pt
    ,TM2x *dst
    ,uint64_t dst_byte_i
    ,uint64_t byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_src_index
    ,continuation bad_dst_index
    ){
    if( (uint64_t)(src_pt + byte_n) < (uint64_t)src_pt ) return bad_src_index;
    if( dst_byte_i + byte_n > TM2x\U000000b7byte_n(dst) ) return bad_dst_index;
    memcpy(TM2x\U000000b7byte_0_pt(dst) + dst_byte_i ,src_pt ,byte_n+1);
  }

  static inline void TM2x\U000000b7write(TM2x *tape ,uint64_t index ,void *src_element_pt ,uint64_t element_byte_n){
    void *dst_element_pt = TM2x\U000000b7element_i_pt(tape ,index ,element_byte_n);
    memcpy(dst_element_pt ,src_element_pt ,element_byte_n+1);
  }



  static inline continuation TM2x\U000000b7copy_bytes
  ( TM2x *src
    ,uint64_t src_byte_i
    ,TM2x *dst
    ,uint64_t dst_byte_i
    ,uint64_t byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_src_index
    ,continuation bad_dst_index
    ){
    if( src_byte_i + byte_n > TM2x\U000000b7byte_n(src) ) return bad_src_index;
    if( dst_byte_i + byte_n > TM2x\U000000b7byte_n(dst) ) return bad_dst_index;
    memcpy(TM2x\U000000b7byte_0_pt(dst) + dst_byte_i ,TM2x\U000000b7byte_0_pt(dst) + src_byte_i ,byte_n+1);
  }



  static inline continuation TM2x\U000000b7copy_elements
  ( TM2x *src
    ,uint64_t src_element_i
    ,TM2x *dst
    ,uint64_t dst_element_i
    ,uint64_t element_n
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_src_index
    ,continuation bad_dst_index
    ){

    __label__ nominal ,overflow;
    uint64_t src_byte_i;
    goto * mul_ib(src_element_i ,element_byte_n ,&src_byte_i ,&&nominal ,&&overflow);

    nominal:{
      __label__ nominal;
      uint64_t dst_byte_i;
      goto * mul_ib(dst_element_i ,element_byte_n ,&dst_byte_i ,&&nominal ,&&overflow);
      nominal:{
        __label__ nominal;
        uint64_t byte_n;
        goto * mul_ib(element_n ,element_byte_n ,&byte_n ,&&nominal ,&&overflow);
        nominal:{
          return TM2x\U000000b7copy_bytes
            ( src
              ,src_byte_i
              ,dst
              ,dst_byte_i
              ,byte_n
              ,nominal
              ,alloc_fail
              ,bad_src_index
              ,bad_dst_index
              );
        }
      }
    }

    overflow:{
      return bad_src_index;
    }

  }




  static inline continuation TM2x\U000000b7push_bytes
  ( TM2x *tape
    ,void *source_pt
    ,uint64_t source_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ){
    uint64_t push_pt = TM2x\U000000b7byte_n(tape) + 1;
    uint64_t after_byte_n = push_pt + source_byte_n;
    goto * TM2x\U000000b7resize_bytes(tape ,after_byte_n ,&&resize_nominal ,&&resize_fail);

    resize_nominal:{
      memcpy(TM2x\U000000b7byte_0_pt(tape) + push_pt ,source_pt ,source_byte_n+1);
      return nominal;
    }

    resize_fail:{
      return alloc_fail;
    }
  }


  static inline continuation TM2x\U000000b7push
  ( TM2x *tape
    ,void *element_base_pt
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ){
    return TM2x\U000000b7push_bytes(tape ,element_base_pt ,element_byte_n ,nominal ,alloc_fail);
  }


  static inline continuation TM2x\U000000b7push_elements
  ( TM2x *tape
    ,void *base_pt
    ,uint64_t element_n
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation alloc_fail
    ,continuation bad_index
    ){
    uint64_t byte_n;
    goto * mul_ib(element_n ,element_byte_n ,&byte_n ,&&mul_ib\U000000b7nominal ,&&mul_ib\U000000b7overflow);
    mul_ib\U000000b7nominal:{
      return TM2x\U000000b7push(tape ,base_pt ,byte_n ,nominal ,alloc_fail);
    }
    mul_ib\U000000b7overflow:{
      return bad_index;
    }
  }


  static inline continuation TM2x\U000000b7push_TM2x
  ( TM2x *tape
    ,TM2x *tape_source
    ,continuation nominal
    ,continuation alloc_fail
    ){
    return TM2x\U000000b7push(tape ,tape_source->base_pt ,tape_source->byte_n ,nominal ,alloc_fail);
  }





  static inline continuation TM2x\U000000b7pop
  ( TM2x *tape
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation pop_last
    ,continuation alloc_fail
    ){

    uint64_t before_byte_n = TM2x\U000000b7byte_n(tape);
    if( before_byte_n <= element_byte_n ) return pop_last;
    uint64_t after_byte_n = before_byte_n - element_byte_n - 1;
    TM2x\U000000b7resize_bytes(tape ,after_byte_n ,&&resize_nominal ,&&alloc_fail);
    resize_nominal:{
      return nominal;
    }
    alloc_fail:{
      return alloc_fail;
    }
  }



  static inline continuation TM2x\U000000b7read_pop
  ( TM2x *tape
    ,void *dst_element_pt
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation pop_last
    ,continuation alloc_fail
    ){
    memcpy(dst_element_pt ,TM2x\U000000b7element_n_pt(tape ,element_byte_n) ,element_byte_n+1);
    goto * TM2x\U000000b7pop(tape ,element_byte_n ,&&pop_nominal ,&&pop_pop_last ,&&pop_alloc_fail);
    pop_nominal:{ return nominal;}
    pop_pop_last:{ return pop_last;}
    pop_alloc_fail:{ return alloc_fail;}
  }
# 8 "../include/TM2xHd.lib.h" 2
# 27 "../include/TM2xHd.lib.h"
  typedef struct {
    char *element_pt;
  } TM2xHd;






  static inline continuation TM2xHd\U000000b7is_on_tape
  ( TM2x *tape
    ,TM2xHd *hd
    ,continuation is_true
    ,continuation is_false
    ){
    if( hd->element_pt <= TM2x\U000000b7byte_n_pt(tape) && hd->element_pt >= TM2x\U000000b7byte_0_pt(tape) ) return is_true;
    return is_false;
  }
  static inline continuation TM2xHd\U000000b7at_element_n
  ( TM2x *tape
    ,TM2xHd *hd
    ,uint64_t element_byte_n
    ,continuation is_true
    ,continuation is_false
    ){
    if( hd->element_pt == TM2x\U000000b7element_n_pt(tape ,element_byte_n) ) return is_true;
    return is_false;
  }





  static inline void TM2xHd\U000000b7rewind(TM2x *tape ,TM2xHd *hd){
    hd->element_pt = TM2x\U000000b7byte_0_pt(tape);
  }

  static inline void TM2xHd\U000000b7unguarded_step(TM2xHd *hd ,uint64_t element_byte_n){
    hd->element_pt += element_byte_n + 1;
  }

  static inline continuation TM2xHd\U000000b7step
  ( TM2x *tape
    ,TM2xHd *hd
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation end_of_tape
    ){
    goto * TM2xHd\U000000b7at_element_n(tape ,hd ,element_byte_n ,&&at_n ,&&not_at_n);
    at_n:{
      return end_of_tape;
    }
    not_at_n:{
      TM2xHd\U000000b7unguarded_step(hd ,element_byte_n);
      return nominal;
    }
  }

  static inline void *TM2xHd\U000000b7pt(TM2xHd *hd){
    return hd->element_pt;
  }

  static inline void TM2xHd\U000000b7read(TM2xHd *hd ,uint64_t element_byte_n ,void *dst_pt){
    memcpy(dst_pt ,hd->element_pt ,element_byte_n+1);
  }



  static inline void TM2xHd\U000000b7write(TM2xHd *hd ,uint64_t element_byte_n ,void *src_element_pt){
    memcpy(hd->element_pt ,src_element_pt ,element_byte_n+1);
  }
# 108 "../include/TM2xHd.lib.h"
  static inline continuation TM2x\U000000b7cat
  ( TM2x *tape_acc
    ,TM2x *tape_src
    ,uint64_t element_byte_n
    ,continuation nominal
    ,continuation allocation_failed
    ){
    TM2xHd TM2xHd\U000000b7hd_src ,*hd_src; hd_src = &TM2xHd\U000000b7hd_src; TM2xHd\U000000b7rewind(tape_src ,hd_src);;
    loop:{
      goto * TM2x\U000000b7push(tape_acc ,TM2xHd\U000000b7pt(hd_src) ,element_byte_n ,&&pw_nominal ,&&pw_allocation_failed);
      pw_nominal:{
        goto * TM2xHd\U000000b7step(tape_src ,hd_src ,element_byte_n ,&&loop ,&&at_n);
        at_n:{
          return nominal;
        }
      }
      pw_allocation_failed:{
        return allocation_failed;
      }
    }
  }



  static inline void TM2xHd\U000000b7apply_to_each
  ( TM2x *tape
    ,TM2xHd *hd
    ,uint64_t element_byte_n
    ,void *context
    ,void f(void *context ,void *el ,uint64_t element_byte_n)
    ){
    TM2xHd\U000000b7apply_to_each:{
      void *element_pt = TM2xHd\U000000b7pt(hd);
      f(context ,element_pt ,element_byte_n);
      goto * TM2xHd\U000000b7at_element_n(tape ,hd ,element_byte_n ,&&hd_at_n ,&&hd_not_at_n);
      hd_at_n:{
        return;
      }
      hd_not_at_n:{
        TM2xHd\U000000b7unguarded_step(hd ,element_byte_n);
        goto TM2xHd\U000000b7apply_to_each;
      }
    }
  }


  static inline continuation TM2xHd\U000000b7all
  ( TM2x *tape
    ,TM2xHd *hd
    ,uint64_t element_byte_n
    ,void *context
    ,continuation pred(void *context ,void *el ,uint64_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation true_for_all
    ,continuation an_exception
    ){
    TM2xHd\U000000b7all:{
      goto * pred(context ,TM2xHd\U000000b7pt(hd) ,element_byte_n ,&&pred_true ,&&pred_false);
      pred_true:{
        goto * TM2xHd\U000000b7at_element_n(tape ,hd ,element_byte_n ,&&at_n , &&not_at_n);
        at_n:{
          return true_for_all;
        }
        not_at_n:{
          TM2xHd\U000000b7unguarded_step(hd ,element_byte_n);
          goto TM2xHd\U000000b7all;
        }
      }
      pred_false:{
        return an_exception;
      }
    }
  }

  static inline continuation TM2xHd\U000000b7exists
  ( TM2x *tape
    ,TM2xHd *hd
    ,uint64_t element_byte_n
    ,void *context
    ,continuation pred(void *context ,void *el ,uint64_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation found_one
    ,continuation not_on_tape
    ){
    TM2xHd\U000000b7exists:{
      goto * pred(context ,TM2xHd\U000000b7pt(hd) ,element_byte_n ,&&pred_true ,&&pred_false );
      pred_true:{
        return found_one;
      }
      pred_false:{
        goto * TM2xHd\U000000b7at_element_n(tape ,hd ,element_byte_n ,&&hd_at_n , &&hd_not_at_n);
        hd_at_n:{
          return not_on_tape;
        }
        hd_not_at_n:{
          TM2xHd\U000000b7unguarded_step(hd ,element_byte_n);
          goto TM2xHd\U000000b7exists;
        }
      }
    }
  }
# 217 "../include/TM2xHd.lib.h"
  static inline continuation TM2xHd\U000000b7push_not_exists
  ( TM2x *tape_dst
    ,void *src_element_pt
    ,uint64_t element_byte_n
    ,continuation pred(void *context ,void *el ,uint64_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation wrote_it
    ,continuation already_on_tape_dst
    ,continuation allocate_failed
    ){
    TM2xHd TM2xHd\U000000b7hd ,*hd; hd = &TM2xHd\U000000b7hd; TM2xHd\U000000b7rewind(tape_dst ,hd);;
    goto * TM2xHd\U000000b7exists
      ( tape_dst
        ,hd
        ,element_byte_n
        ,src_element_pt
        ,pred
        ,&&found_one
        ,&&not_found
        );
    found_one:{
      return already_on_tape_dst;
    }
    not_found:{
      goto * TM2x\U000000b7push(tape_dst ,src_element_pt ,element_byte_n ,&&pw_wrote_it ,&&pw_alloc_failed);
      pw_wrote_it:{
        return wrote_it;
      }
      pw_alloc_failed:{
        return allocate_failed;
      }
    }
  }






  static inline continuation TM2xHd\U000000b7accumulate_union
  ( TM2x *set_acc
    ,TM2x *set_src
    ,TM2xHd *hd_src
    ,uint64_t element_byte_n
    ,continuation pred(void *context ,void *el ,uint64_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,
# 261 "../include/TM2xHd.lib.h" 3 4
    _Bool 
# 261 "../include/TM2xHd.lib.h"
         *subset
    ,continuation nominal
    ,continuation allocation_failed
    ){
    if(subset) *subset = 
# 265 "../include/TM2xHd.lib.h" 3 4
                        1
# 265 "../include/TM2xHd.lib.h"
                            ;
    TM2xHd\U000000b7accumulate_union:{
      goto * TM2xHd\U000000b7push_not_exists
        ( set_acc
          ,TM2xHd\U000000b7pt(hd_src)
          ,element_byte_n
          ,pred
          ,&& pw_wrote_it
          ,&& pw_already_on_tape
          ,&& pw_allocate_failed
          );

      pw_wrote_it:{
        if(subset) *subset = 
# 278 "../include/TM2xHd.lib.h" 3 4
                            0
# 278 "../include/TM2xHd.lib.h"
                                 ;
        goto pw_already_on_tape;
      }

      pw_already_on_tape:{
        __label__ at_n ,not_at_n;
        goto * TM2xHd\U000000b7at_element_n(set_src ,hd_src ,element_byte_n ,&&at_n , &&not_at_n);
        at_n:{
          return nominal;
        }
        not_at_n:{
          TM2xHd\U000000b7unguarded_step(hd_src ,element_byte_n);
          goto TM2xHd\U000000b7accumulate_union;
        }}

      pw_allocate_failed:{
        return allocation_failed;
      }
    }}





  static inline continuation TM2xHd\U000000b7init_intersection
  ( TM2x *set_intersection
    ,TM2x *set_a
    ,TM2x *set_b
    ,uint64_t element_byte_n
    ,continuation pred(void *context ,void *el ,uint64_t element_byte_n ,continuation pred_true ,continuation pred_false)
    ,continuation init_intersection\U000000b7nominal
    ,continuation init_intersection\U000000b7empty
    ,continuation init_intersection\U000000b7allocation_failed
    ){
    TM2xHd TM2xHd\U000000b7hd_a ,*hd_a; hd_a = &TM2xHd\U000000b7hd_a; TM2xHd\U000000b7rewind(set_a ,hd_a);;
    TM2xHd TM2xHd\U000000b7hd_b ,*hd_b; hd_b = &TM2xHd\U000000b7hd_b; TM2xHd\U000000b7rewind(set_b ,hd_b);;


    continuation do_write = &&init;

    exists:{
      goto * TM2xHd\U000000b7exists
        ( set_b
          ,hd_b
          ,element_byte_n
          ,TM2xHd\U000000b7pt(hd_a)
          ,pred
          ,do_write
          ,&&next
          );
    }

    init:{
      __label__ nominal ,alloc_fail;
      goto * TM2x\U000000b7construct_write
        ( set_intersection
          ,TM2xHd\U000000b7pt(hd_a)
          ,element_byte_n
          ,&&nominal
          ,&&alloc_fail
          );
      nominal:{
        do_write = &&extend;
        goto next;
      }
      alloc_fail:{
        return init_intersection\U000000b7allocation_failed;
      }
    }

    extend:{
      __label__ nominal ,alloc_fail;
      goto * TM2x\U000000b7push
        ( set_intersection
          ,TM2xHd\U000000b7pt(hd_a)
          ,element_byte_n
          ,&&nominal
          ,&&alloc_fail
          );
      nominal:{
        goto next;
      }
      alloc_fail:{
        return init_intersection\U000000b7allocation_failed;
      }
    }

    next:{
      __label__ end_of_tape;
      TM2xHd\U000000b7rewind(set_b ,hd_b);
      goto * TM2xHd\U000000b7step
        ( set_a
          ,hd_a
          ,element_byte_n
          ,&&exists
          ,&&end_of_tape
          );
      end_of_tape:{
          if( do_write == &&init )
            return init_intersection\U000000b7empty;
          else
            return init_intersection\U000000b7nominal;
      }
    }
  }






  static inline continuation TM2xHd\U000000b7true
  ( void *context
    ,TM2x *tape
    ,TM2xHd *hd
    ,uint64_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    return pred_true;
  }

  static inline continuation TM2xHd\U000000b7false
  ( void *context
    ,void *a_e0
    ,uint64_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    return pred_false;
  }

  static inline continuation TM2xHd\U000000b7pred_bytes_eq
  ( void *context
    ,void *a_e0
    ,uint64_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    char *e0 = a_e0;
    char *e1 = context;
    if( memcmp(e0 ,e1 ,element_byte_n+1) == 0 )
      return pred_true;
    else
      return pred_false;
  }

  static inline continuation TM2xHd\U000000b7pred_cstring_eq
  ( void *context
    ,void *a_e0
    ,uint64_t element_byte_n
    ,continuation pred_true
    ,continuation pred_false
    ){
    char *e0 = a_e0;
    char *e1 = context;
    if( strncmp(e0 ,e1 ,element_byte_n+1) == 0 )
      return pred_true;
    else
      return pred_false;
  }





  static inline void TM2xHd\U000000b7f_free(void *context ,void *element_pt ,uint64_t element_byte_n){
    (MallocCounter\U000000b7count-- ,free(element_pt));
  }



  static inline void TM2xHd\U000000b7f_print_int(void *context ,void *element_pt ,uint64_t element_byte_n){
    fprintf(
# 451 "../include/TM2xHd.lib.h" 3 4
           stderr 
# 451 "../include/TM2xHd.lib.h"
                  ,"%s%d" ,(char *)context ,*(int *)element_pt);
  }
# 5 "../include/TM2x.h" 2
# 10 "TM2x·test.c" 2
# 1 "../include/Result.h" 1



typedef struct{
  uint passed;
  uint failed;
  uint n;
}Result\U000000b7Tallies;
void Result\U000000b7Tallies\U000000b7init(Result\U000000b7Tallies *rp){
  rp->passed = 0;
  rp->failed = 0;
}
void Result\U000000b7Tallies\U000000b7passed(Result\U000000b7Tallies *rp){
  rp->passed++;
}
void Result\U000000b7Tallies\U000000b7failed(Result\U000000b7Tallies *rp){
  rp->failed++;
}
void Result\U000000b7Tallies\U000000b7tally(char *mess ,Result\U000000b7Tallies *rp ,
# 19 "../include/Result.h" 3 4
                                                            _Bool 
# 19 "../include/Result.h"
                                                                 *flags ,uint n){
  uint i = 0;
  while( i < n ){
    *flags ? Result\U000000b7Tallies\U000000b7passed(rp) : Result\U000000b7Tallies\U000000b7failed(rp);
  flags++;
  i++;
  }
  fprintf(
# 26 "../include/Result.h" 3 4
         stderr 
# 26 "../include/Result.h"
                ,"%s: %u flags ,%u passed. %u failed.\n" ,mess ,n ,rp->passed ,rp->failed);
}
void Result\U000000b7Tallies\U000000b7accumulate(Result\U000000b7Tallies *acc ,Result\U000000b7Tallies *rp){
  acc->passed += rp->passed;
  acc->failed += rp->failed;
}
void Result\U000000b7Tallies\U000000b7print(char *mess ,Result\U000000b7Tallies *rp){
  fprintf(
# 33 "../include/Result.h" 3 4
         stderr 
# 33 "../include/Result.h"
                ,"%s: %u passed. %u failed.\n" ,mess ,rp->passed ,rp->failed);
}
# 11 "TM2x·test.c" 2

uint64_t TM2x\U000000b7test_after_allocation_n = 0;

Result\U000000b7Tallies test_0(){
  uint64_t malloc_cnt = MallocCounter\U000000b7count;
  uint64_t constructed_cnt = TM2x\U000000b7constructed_count;
  
# 17 "TM2x·test.c" 3 4
 _Bool 
# 17 "TM2x·test.c"
      f[5];
  uint i = 0;

  Result\U000000b7Tallies r ,*rp; rp = &r;
  Result\U000000b7Tallies\U000000b7init(rp);

  TM2x TM2x\U000000b7a0p ,*a0p; a0p = &TM2x\U000000b7a0p;; goto * TM2x\U000000b7construct_elements(a0p ,0 ,sizeof(int32_t)-1, &&nominal ,&&fail ,&&fail);;
  nominal:{
    f[i] = 
# 25 "TM2x·test.c" 3 4
          1
# 25 "TM2x·test.c"
              ;
    goto end;
  }
  fail:{
    f[i] = 
# 29 "TM2x·test.c" 3 4
          0
# 29 "TM2x·test.c"
               ;
    goto end;
  }
  end:{
    i++;
  }

  int32_t j = -5;
  int32_t k;

  f[i++] = TM2x\U000000b7byte_n(a0p) == 3;
  TM2x\U000000b7write(a0p ,0 ,&(j) ,sizeof(typeof(j))-1);
  TM2x\U000000b7read(a0p ,0 ,&k ,sizeof(typeof(k))-1);
  f[i++] = k == -5;

  TM2x\U000000b7destruct(a0p);
  f[i++] = malloc_cnt == MallocCounter\U000000b7count;
  f[i++] = constructed_cnt == TM2x\U000000b7constructed_count;
  Result\U000000b7Tallies\U000000b7tally("test_0" ,rp ,f ,i);
  return r;
}

Result\U000000b7Tallies test_1(){
  uint64_t malloc_cnt = MallocCounter\U000000b7count;
  uint64_t constructed_cnt = TM2x\U000000b7constructed_count;
  Result\U000000b7Tallies r ,*rp; rp = &r;
  Result\U000000b7Tallies\U000000b7init(rp);

  
# 57 "TM2x·test.c" 3 4
 _Bool 
# 57 "TM2x·test.c"
      f[256];
  uint i = 0;

  TM2x a0,*a0p; a0p = &a0;
  goto * TM2x\U000000b7construct_elements(a0p ,1 ,sizeof(int32_t)-1 ,&&construct_nominal ,&&construct_fail ,&&construct_fail);
  construct_fail:{
    f[i] = 
# 63 "TM2x·test.c" 3 4
          0
# 63 "TM2x·test.c"
               ;
    goto construct_end;
  }
  construct_nominal:{
    f[i] = 
# 67 "TM2x·test.c" 3 4
          1
# 67 "TM2x·test.c"
              ;
  }
  construct_end:{
    i++;
  }
  f[i++] = a0p->byte_n == 7;

  goto * TM2x\U000000b7resize_elements(a0p ,3 ,sizeof(int32_t)-1 ,&&resize_nominal ,&&resize_fail ,&&resize_fail);
  resize_fail:{
    f[i] = 
# 76 "TM2x·test.c" 3 4
          0
# 76 "TM2x·test.c"
               ;
    goto resize_end;
  }
  resize_nominal:{
    f[i] = 
# 80 "TM2x·test.c" 3 4
          1
# 80 "TM2x·test.c"
              ;
  }
  resize_end:{
      i++;
  }
  f[i++] = a0p->byte_n == 15;



    int32_t x;
    x = 1; TM2x\U000000b7write(a0p ,0 ,&(x) ,sizeof(typeof(x))-1);
    x = 2; TM2x\U000000b7write(a0p ,1 ,&(x) ,sizeof(typeof(x))-1);
    x = 3; TM2x\U000000b7write(a0p ,2 ,&(x) ,sizeof(typeof(x))-1);
    x = 4; TM2x\U000000b7write(a0p ,3 ,&(x) ,sizeof(typeof(x))-1);



    int32_t y;
    {
      __label__ read_pop\U000000b7nominal ,read_pop\U000000b7pop_last ,read_pop\U000000b7alloc_fail ,read_pop\U000000b7end;
      uint j = 4;
      while( j > 1 ){
        goto * TM2x\U000000b7read_pop(a0p ,&y ,sizeof(typeof(y))-1 ,&&read_pop\U000000b7nominal ,&&read_pop\U000000b7pop_last ,&&read_pop\U000000b7alloc_fail);
        read_pop\U000000b7nominal:{
          f[i] = 
# 104 "TM2x·test.c" 3 4
                1
# 104 "TM2x·test.c"
                    ;
          goto read_pop\U000000b7end;
        }
        read_pop\U000000b7pop_last:{
          f[i] = 
# 108 "TM2x·test.c" 3 4
                0
# 108 "TM2x·test.c"
                     ;
          goto read_pop\U000000b7end;
        }
        read_pop\U000000b7alloc_fail:{
          f[i] = 
# 112 "TM2x·test.c" 3 4
                0
# 112 "TM2x·test.c"
                     ;
          goto read_pop\U000000b7end;
        }
        read_pop\U000000b7end:{
          i++;
        }
        f[i] = y == j;
        i++;
        --j;
      }
    }

    {
      __label__ read_pop\U000000b7nominal ,read_pop\U000000b7pop_last ,read_pop\U000000b7alloc_fail ,read_pop\U000000b7end;
      goto * TM2x\U000000b7read_pop(a0p ,&y ,sizeof(typeof(y))-1 ,&&read_pop\U000000b7nominal ,&&read_pop\U000000b7pop_last ,&&read_pop\U000000b7alloc_fail);
      read_pop\U000000b7nominal:{
        f[i] = 
# 128 "TM2x·test.c" 3 4
              0
# 128 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7pop_last:{
        f[i] = 
# 132 "TM2x·test.c" 3 4
              1
# 132 "TM2x·test.c"
                  ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7alloc_fail:{
        f[i] = 
# 136 "TM2x·test.c" 3 4
              0
# 136 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7end:{
        i++;
      }
      f[i++] = y == 1;
    }
    f[i++] = a0p->byte_n == 3;

  TM2x\U000000b7destruct(a0p);
  f[i++] = malloc_cnt == MallocCounter\U000000b7count;
  f[i++] = constructed_cnt == TM2x\U000000b7constructed_count;
  Result\U000000b7Tallies\U000000b7tally("test_1" ,rp ,f ,i);
  return r;
}

Result\U000000b7Tallies test_2(){
  uint64_t malloc_cnt = MallocCounter\U000000b7count;
  uint64_t constructed_cnt = TM2x\U000000b7constructed_count;
  
# 156 "TM2x·test.c" 3 4
 _Bool 
# 156 "TM2x·test.c"
      f[256];
  uint i = 0;

  Result\U000000b7Tallies r ,*rp; rp = &r;
  Result\U000000b7Tallies\U000000b7init(rp);

  TM2x TM2x\U000000b7a0 ,*a0; a0 = &TM2x\U000000b7a0;; goto * TM2x\U000000b7construct_elements(a0 ,0 ,sizeof(int32_t)-1, &&nominal ,&&fail ,&&fail);;
  nominal:{
    f[i] = 
# 164 "TM2x·test.c" 3 4
          1
# 164 "TM2x·test.c"
              ;
    goto end;
  }
  fail:{
    f[i] = 
# 168 "TM2x·test.c" 3 4
          0
# 168 "TM2x·test.c"
               ;
  }
  end:{
    i++;
  }
  f[i++] = a0->byte_n == 3;

  int32_t x=1,y=0;
  TM2x\U000000b7write(a0 ,0 ,&(x) ,sizeof(typeof(x))-1);

  ++x;
  goto * TM2x\U000000b7push(a0 ,&x ,sizeof(typeof(x))-1 ,&&push_nominal_0 ,&&push_allocation_failed_0);
  push_allocation_failed_0:{
    f[i] = 
# 181 "TM2x·test.c" 3 4
          0
# 181 "TM2x·test.c"
               ;
    goto push_end_0;
  }
  push_nominal_0:{
    f[i] = 
# 185 "TM2x·test.c" 3 4
          1
# 185 "TM2x·test.c"
              ;
  }
  push_end_0:{
    i++;
  }
  f[i++] = TM2x\U000000b7test_after_allocation_n == 7;
  TM2x\U000000b7read(a0 ,1 ,&y ,3);
  f[i++] = x==y;

  ++x;
  goto * TM2x\U000000b7push(a0 ,&x ,sizeof(typeof(x))-1 ,&&push_nominal_1 ,&&push_allocation_failed_1);
  push_allocation_failed_1:{
    f[i] = 
# 197 "TM2x·test.c" 3 4
          0
# 197 "TM2x·test.c"
               ;
    goto push_end_1;
  }
  push_nominal_1:{
    f[i] = 
# 201 "TM2x·test.c" 3 4
          1
# 201 "TM2x·test.c"
              ;
  }
  push_end_1:{
    i++;
  }
  f[i++] = TM2x\U000000b7test_after_allocation_n == 15;

  ++x;
  goto * TM2x\U000000b7push(a0 ,&x ,sizeof(typeof(x))-1 ,&&push_nominal_2 ,&&push_allocation_failed_2);
  push_allocation_failed_2:{
    f[i] = 
# 211 "TM2x·test.c" 3 4
          0
# 211 "TM2x·test.c"
               ;
    goto push_end_2;
  }
  push_nominal_2:{
    f[i] = 
# 215 "TM2x·test.c" 3 4
          1
# 215 "TM2x·test.c"
              ;
  }
  push_end_2:{
    i++;
  }
  f[i++] = TM2x\U000000b7test_after_allocation_n == 15;

  ++x;
  goto * TM2x\U000000b7push(a0 ,&x ,sizeof(typeof(x))-1 ,&&push_nominal_3 ,&&push_allocation_failed_3);
  push_allocation_failed_3:{
    f[i] = 
# 225 "TM2x·test.c" 3 4
          0
# 225 "TM2x·test.c"
               ;
    goto push_end_3;
  }
  push_nominal_3:{
    f[i] = 
# 229 "TM2x·test.c" 3 4
          1
# 229 "TM2x·test.c"
              ;
  }
  push_end_3:{
    i++;
  }
  f[i++] = TM2x\U000000b7test_after_allocation_n == 31;

  y=111222;
    {
      __label__ read_pop\U000000b7nominal ,read_pop\U000000b7pop_last ,read_pop\U000000b7alloc_fail ,read_pop\U000000b7end;
      goto * TM2x\U000000b7read_pop(a0 ,&y ,sizeof(typeof(y))-1 ,&&read_pop\U000000b7nominal ,&&read_pop\U000000b7pop_last ,&&read_pop\U000000b7alloc_fail);
      read_pop\U000000b7nominal:{
        f[i] = 
# 241 "TM2x·test.c" 3 4
              1
# 241 "TM2x·test.c"
                  ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7pop_last:{
        f[i] = 
# 245 "TM2x·test.c" 3 4
              0
# 245 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7alloc_fail:{
        f[i] = 
# 249 "TM2x·test.c" 3 4
              0
# 249 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7end:{
        i++;
      }
    }
  f[i++] = y == 5;
  f[i++] = TM2x\U000000b7test_after_allocation_n == 15;

    {
      __label__ read_pop\U000000b7nominal ,read_pop\U000000b7pop_last ,read_pop\U000000b7alloc_fail ,read_pop\U000000b7end;
      goto * TM2x\U000000b7read_pop(a0 ,&y ,sizeof(typeof(y))-1 ,&&read_pop\U000000b7nominal ,&&read_pop\U000000b7pop_last ,&&read_pop\U000000b7alloc_fail);
      read_pop\U000000b7nominal:{
        f[i] = 
# 263 "TM2x·test.c" 3 4
              1
# 263 "TM2x·test.c"
                  ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7pop_last:{
        f[i] = 
# 267 "TM2x·test.c" 3 4
              0
# 267 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7alloc_fail:{
        f[i] = 
# 271 "TM2x·test.c" 3 4
              0
# 271 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7end:{
        i++;
      }
    }
  f[i++] = y == 4;
  f[i++] = TM2x\U000000b7test_after_allocation_n == 15;
    {
      __label__ read_pop\U000000b7nominal ,read_pop\U000000b7pop_last ,read_pop\U000000b7alloc_fail ,read_pop\U000000b7end;
      goto * TM2x\U000000b7read_pop(a0 ,&y ,sizeof(typeof(y))-1 ,&&read_pop\U000000b7nominal ,&&read_pop\U000000b7pop_last ,&&read_pop\U000000b7alloc_fail);
      read_pop\U000000b7nominal:{
        f[i] = 
# 284 "TM2x·test.c" 3 4
              1
# 284 "TM2x·test.c"
                  ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7pop_last:{
        f[i] = 
# 288 "TM2x·test.c" 3 4
              0
# 288 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7alloc_fail:{
        f[i] = 
# 292 "TM2x·test.c" 3 4
              0
# 292 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7end:{
        i++;
      }
    }
  f[i++] = y == 3;
  f[i++] = TM2x\U000000b7test_after_allocation_n == 7;

    {
      __label__ read_pop\U000000b7nominal ,read_pop\U000000b7pop_last ,read_pop\U000000b7alloc_fail ,read_pop\U000000b7end;
      goto * TM2x\U000000b7read_pop(a0 ,&y ,sizeof(typeof(y))-1 ,&&read_pop\U000000b7nominal ,&&read_pop\U000000b7pop_last ,&&read_pop\U000000b7alloc_fail);
      read_pop\U000000b7nominal:{
        f[i] = 
# 306 "TM2x·test.c" 3 4
              1
# 306 "TM2x·test.c"
                  ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7pop_last:{
        f[i] = 
# 310 "TM2x·test.c" 3 4
              0
# 310 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7alloc_fail:{
        f[i] = 
# 314 "TM2x·test.c" 3 4
              0
# 314 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7end:{
        i++;
      }
    }
  f[i++] = y == 2;
  f[i++] = TM2x\U000000b7test_after_allocation_n == 3;

    {
      __label__ read_pop\U000000b7nominal ,read_pop\U000000b7pop_last ,read_pop\U000000b7alloc_fail ,read_pop\U000000b7end;
      goto * TM2x\U000000b7read_pop(a0 ,&y ,sizeof(typeof(y))-1 ,&&read_pop\U000000b7nominal ,&&read_pop\U000000b7pop_last ,&&read_pop\U000000b7alloc_fail);
      read_pop\U000000b7nominal:{
        f[i] = 
# 328 "TM2x·test.c" 3 4
              0
# 328 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7pop_last:{
        f[i] = 
# 332 "TM2x·test.c" 3 4
              1
# 332 "TM2x·test.c"
                  ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7alloc_fail:{
        f[i] = 
# 336 "TM2x·test.c" 3 4
              0
# 336 "TM2x·test.c"
                   ;
        goto read_pop\U000000b7end;
      }
      read_pop\U000000b7end:{
        i++;
      }
    }
  f[i++] = y == 1;
  f[i++] = TM2x\U000000b7test_after_allocation_n == 3;

  TM2x\U000000b7destruct(a0);
  f[i++] = malloc_cnt == MallocCounter\U000000b7count;
  f[i++] = constructed_cnt == TM2x\U000000b7constructed_count;

  Result\U000000b7Tallies\U000000b7tally("test_2" ,rp ,f ,i);
  return r;
}

int main(){
  Result\U000000b7Tallies r ,acc ,*accp; accp=&acc;
  Result\U000000b7Tallies\U000000b7init(accp);

  r = test_0(); Result\U000000b7Tallies\U000000b7accumulate(accp ,&r);
  r = test_1(); Result\U000000b7Tallies\U000000b7accumulate(accp ,&r);
  r = test_2(); Result\U000000b7Tallies\U000000b7accumulate(accp ,&r);

  Result\U000000b7Tallies\U000000b7print("TM2x·test results" ,accp);
  return acc.failed;
}
