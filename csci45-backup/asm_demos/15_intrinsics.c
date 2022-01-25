#include <stdio.h>
//This isn't installed on the server correctly
#include <arm_acle.h>    /* Include ACLE intrinsics */

int foo(int a, int b)
{
#ifdef ARM32
	return __qadd(a, b);  /* Saturated add of a and b */
#else 
#warning This should be saturating but it aint
	return a+b;
#endif
}

int main() {
	printf("5 + 5 = %i\n",foo(5,5));
	printf("1000000000 + 1000000000 = %i\n",foo(1000000000 ,1000000000));
	printf("1000000000 + 2000000000 = %i\n",foo(1000000000 ,2000000000));
}
