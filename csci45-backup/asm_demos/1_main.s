/*
int main() {
	return 42;
}

Note: after you run this, type "echo $?" to see the return value from a program
*/

.global main
main:
	MOV R0, #42 //R0 is always the return value from a function
	BX LR  //Return from function, R0 is return value

//This is another way of quitting, by invoking the stdlib exit() function
	BL exit

//This is an alternative way of quitting - by calling the _exit() syscall
	MOV R7, #1	//Choose Syscall #1
	SWI 0 		//Invoke Syscall
