/*
int main() {
	int x = 32;
	int y = 8;
	int z = x / y;
	return z;
}

Note: after you run this, type "echo $?" to see the return value from a program
*/

//THERE IS NO DIVIDE COMMAND, BUT...
//We can right shift to do division by powers of 2

.global main
main:
	MOV R0, #32 //x = 32;
	MOV R0, R0, LSR #3 //x = x >> 3; (Divide by 2^3.)
	BX LR  //Return from function, R0 is return value
