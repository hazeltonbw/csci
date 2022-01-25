#include <stdio.h>

void prompt() {
	printf("Enter three numbers.\n1) A number you want to shift.\n2) How many binary digits you want to shift it.\n3) An odd number means shift left, an even number means shift right.\n");
}

int read_int() {
	int x = 0;
	scanf("%i",&x);
	return x;
}

void print_int(int x) {
	printf("%i\n",x);
}
