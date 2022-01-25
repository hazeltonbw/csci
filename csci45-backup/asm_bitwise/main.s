//For this assignment, you will do two things:
//First, the user will enter how many letters (a number 1 through 9) to
// convert into uppercase equivalents (without using toupper or cheats like that).
//The user will enter that many letters. You will then output each of those letters
// in upper case format. (If they were already uppercase, they shouldn't change).

//Second, you will write a for loop. The twist for this is that you can only use
// a *single register* to implement the for loop's variables to keep track of where it is
// and what the step size should be. (You can use other registers as normal to call
// the write syscall or to check for termination.) So not 3 registers like normally.
//The for loop will print out a diamond pattern like this:
// .
// ....
// .......
// ..........
// .......
// ....
// .
// The above represents a diamond of size == 4. The size you'll actually use
// will be equal to the original number input by the user up top in phase one.
.global _start
_start:
	//Print greeting
	MOV R0,#1		 @0 = stdin, 1 = stdout, 2 = stderr
	LDR R1,=greeting @Print from this string in the data segment
	MOV R2,#68       @68 characters to print
	MOV R7,#4		 @Choose the Write syscall (which is syscall 4)
	SWI 0			 @Syscall

	//Read from stdin one character

	MOV R0, #0
	LDR R1, =input
	MOV R2, #2 // read 2 chars, one char and one newline
	MOV R7, #3
	SWI 0

	//Convert that ASCII character to an integer of equal value
	LDRB R3, [R1]
	CMP R3, #'0'
	BLT quit
	CMP R3, #'9'
	BGT quit
	SUB R3, #'0' // GET INTEGER VALUE BY SUBTRACTING FROM ASCII VALUE

	MOV R0, #0 // STDIN = 0
	LDR R1, =input
	ADD R2, R3, #1 // dont forget endline
	MOV R7, #3 //  READ SYSTEM CALL
	SWI 0
	
	MOV R8, #0 // for (int i = 0; i < iterations; i++) 
	MOV R0, #1
	MOV R2, #1
	MOV R7, #4
	loop:
		CMP R8, R3
		BGE next
		LDRB R9, [R1, #0]
		CMP R9, #'a'
		CMPGE R9, #'z'
		BICLE R9, #32
		STRB R9, [R1]
		SWI 0
		ADD R8, #1
		ADD R1, #1
		b loop

	next:
		LDR R1, =endl
		MOV R2, #1
		SWI 0
		b diamond

	diamond:
		// lower 8 bits will be the amount of dots to print to screen
		// upper 8 bits will be loop counter * 2 - 1
		
		MOV R10, R3
		LSL R10, #1 // counter * 2
		SUB R10, #1
		LSL R10, #8
		ORR R10, #1
		loop2:
			MOV R7, #4
			AND R2, R10, #31
			ASR R10, #8

			CMP R10, #1
			BEQ end

			LDR R1, =dots
			SWI 0

			CMP R10, R3
			ADDGT R2, #3
			SUBLE R2, #3
			SUB R10, R10, #1
			LSL R10, #8
			ORR R10, R2

			LDR R1, =endl
			MOV R2, #1
			MOV R0, #1
			SWI 0
			b loop2
	
		end:
			LDR R1, =dots
			//MOV R0, #1
			//MOV R7, #4
			//MOV R2, #1
			SWI 0

			LDR R1, =endl
			SWI 0
			b quit

quit:
	MOV R7,#1		@Exit Syscall
	SWI 0

.data
greeting: .asciz "Please enter how many letters you would like to uppercaseify (1-9):\n"
input: .ascii "                                                                                                     "
dots: .ascii "................................................................................"
endl: .asciz "\n"
