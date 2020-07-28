/*
  C is squirely about evaluating __LINE__ in with ##

  gcc -E var.c

> gcc -v
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/libexec/gcc/x86_64-redhat-linux/10/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-redhat-linux
Configured with: ../configure --enable-bootstrap --enable-languages=c,c++,fortran,objc,obj-c++,ada,go,d,lto --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-shared --enable-threads=posix --enable-checking=release --enable-multilib --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --with-gcc-major-version-only --with-linker-hash-style=gnu --enable-plugin --enable-initfini-array --with-isl --enable-offload-targets=nvptx-none --without-cuda-driver --enable-gnu-indirect-function --enable-cet --with-tune=generic --with-arch_32=i686 --build=x86_64-redhat-linux
Thread model: posix
Supported LTO compression algorithms: zlib zstd
gcc version 10.1.1 20200507 (Red Hat 10.1.1-1) (GCC) 

> gcc -E var.c
# 1 "var.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "var.c"
# 16 "var.c"
int main(){

  int unique_int1__LINE__;;
  int unique_int2__LINE__;
  int unique_int320;
}


*/

  #define CAT2(x ,y) x ## y
  #define VAR2(x) CAT2(x, __LINE__)

  #define CAT3b(x ,y) x ## y
  #define CAT3(x ,y) CAT3b(x ,y)
  #define VAR3(x) CAT3(x, __LINE__)


int main(){
  #define ui1 unique_int1 ## __LINE__; 
  int ui1;
  int VAR2(unique_int2);
  int VAR3(unique_int3); // this is the only one that worked
}
