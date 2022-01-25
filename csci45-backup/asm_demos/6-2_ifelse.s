/*
int main() {
	int x = 32;
	int y = 20;
	if (x > y) 
		return 68;
	else
		return -10;
}

Note: after you run this, type "echo $?" to see the return value from a program
*/

//Note that we could do if and else using the code from 6, so this is just
//showing a different way of doing conditionals using suffixes

.global main
main:
	MOV R1, #32 //x = 32
	MOV R2, #20 //x = 20
	CMP R1,R2
	MOV R0, #68
	MOVLE R0, #-10
	BX LR  //Return from function, R0 is return value
