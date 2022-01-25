/* 
 * https://developer.arm.com/docs/100748/0611/using-assembly-and-intrinsics-in-c-or-c-code/writing-inline-assembly-code
 */

#include <stdio.h>

int add(int i, int j)
{
  int res = 0;
  __asm ("ADD %[result], %[input_i], %[input_j]"
    : [result] "=r" (res)
    : [input_i] "r" (i), [input_j] "r" (j)
  );
  return res;
}

int main()
{
  int a = 11;
  int b = 12;
  int c = 0;

  c = add(a,b);

  printf("Result of %d + %d = %d\n", a, b, c);
  
  //Bonus - Maybe this clears an array from cache?
  int arr[100];
  __builtin___clear_cache(arr,arr+99);
}
