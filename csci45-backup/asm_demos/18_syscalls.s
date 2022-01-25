//System calls (syscalls) are the interface between a program and the operating system (OS). OSes do things like check file permissions and so forth before allowing a program to do just anything - this gateway is the syscall mechanism.
//To invoke a syscall, you put the number of the syscall into R7 (weird, I know) and then do a SWI 0. (The 0 doesn't mean anything, but SWI means software interrupt - which turns control over to the OS.)
//The parameters to a syscall are still passed in through R0 through R3, and the return value is in R0

//How do you know which syscall is which number?
//http://syscalls.kernelgrok.com/

//To quit, put #1 into R7 and then SWI 0. This will quit your program. Why? Because the exit syscall is syscall 1.

//To read or write to the standard input and output (normally the keyboard and screen) use syscalls #3 and #4. To use them properly, you need to have some strings set up in advance (see .data section below)

//To fork a process, use syscall 2, etc.

//This code does the following, but without using the c or c++ standard libraries:
//cout << "What is your age (2 digits)?\n";
//cin >> x;
//cout << "Your age+10 = " << x+10 << endl;

//It's buggy if you are 90+ years old - why?

.global main
main:
	PUSH {LR}
	PUSH {R4-R11}

	//To print something you need...
	//0) File descriptor (stdout == 1, stderr == 2)
	MOV R0, #1
	//1) a pointer to a string
	LDR R1,=greeting
	//2) the length of the string (count it, sigh)
	#MOV R2, #29
	//2) Or let the assembler do it for you!
	LDR R2, =greeting_len
	//3) Give the syscall number (write is syscall 4)
	MOV R7, #4
	//4) Then SWI 0
	SWI 0

	//To read from the keyboard you need...
	//0) File descriptor (stdin == 0)
	MOV R0, #0
	//1) char * to write the data into
	LDR R1, =input
	//2) count of how many digits to read - remember to add +1 for the newline character!
	MOV R2, #3
	//3) Give the syscall number (read is syscall 3)
	MOV R7, #3
	//4) Then SWI 0
	SWI 0

	//Now we load the data for the first byte read
	LDR R0, =input
	LDRB R1, [R0,#0] //The #0 is unnecessary, but I want to highlight that I'm just reading the first character
	ADD R1, R1, #1 //Add 1 to it
	STRB R1, [R0] //Then write it back

	//Now print the output...
	MOV R0, #1 //stdout
	LDR R1, =output
	MOV R2, #14 //14 letters
	MOV R7, #4 //Write syscall
	SWI 0

	//Now print the new age - think we should do a macro?
	//(Macros are in demo file 7 here.)
	MOV R0, #1 //stdout
	LDR R1, =input
	MOV R2, #2 //2 letters
	MOV R7, #4 //Write syscall
	SWI 0

	//Now print a newline
	MOV R0, #1 //stdout
	LDR R1, =endl
	MOV R2, #1 //2 letters
	MOV R7, #4 //Write syscall
	SWI 0

	POP {R4-R11}
	POP {PC}

.data
endl: .asciz "\n"
greeting: .asciz "What is your age (2 digits)?\n"
greeting_len = . - greeting
output: .asciz "Your age+10 = "
input: .asciz "                                 "














