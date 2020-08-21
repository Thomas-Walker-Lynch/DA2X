/*

  > gcc -g static0.c static1.c
  > ./a.out
  i: 5

  > gcc -g -DSTATIC static0.c static1.c
  /usr/bin/ld: /home/morpheus/projects/tranche_dev/tmp/cchpRkvn.o: in function `f':
  /home/morpheus/projects/tranche_dev/TM2x/try/static1.c:8: undefined reference to `i'
  collect2: error: ld returned 1 exit status


*/

#ifdef STATIC
  static int i = 5;
#else
  int i = 5;
#endif

extern void f();

int main(){
  f();
  return 0;
}
