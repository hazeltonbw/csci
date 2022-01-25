/*
int main() {
	int x = 21;
	int y = 3;
	int z = x * y;
	return z;
}

Note: after you run this, type "echo $?" to see the return value from a program
*/

.global main
main:
	MOV R1, #21 //x = 21
	MOV R2, #3 //y = 3
	MUL R0, R1, R2 //z = x * y
	BX LR  //Return from function, R0 is return value
