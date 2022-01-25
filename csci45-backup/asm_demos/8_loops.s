/*
//Program to compute powers of 2
int main() {
	int x = 1;
	int y = 5; //2 ^ 5 power this means
	for (int i = 0; i < y; i++) { //We will actually do this by counting down
		x *= 2;
	}
	return x;
}

Note: after you run this, type "echo $?" to see the return value from a program
*/

//Note that we could do if and else using the code from 6, so this is just
//showing a different way of doing conditionals using suffixes

.global main
main:
	MOV R4, #1 //x = 1
	MOV R5, #5 //y = 5
	MOV R6, #2 //We'll be multiplying by 2, and MUL doesn't allow immediates

top: 
	SUBS R5, R5, #1 //--y and then compare y with 0 with -S suffix
	BLT done //If y < 0 then finish
	MUL R4, R4, R6 //x *= 2
	BAL top //Go back to the top of the loop

done:
	MOV R0, R4 //return x;
	BX LR  //Return from function, R0 is return value
