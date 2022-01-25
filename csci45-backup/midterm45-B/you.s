//Task: Rewrite the c_fibber function here in assembly
//Function signature:
//void asm_fibber(int *arr, size_t index, size_t count);

//This is the only file in this directory you can modify
//The only function you can call is a BL to print_int to help debug your code

//Hint 1: To do int x = arr[0], do this (R4 is x, R5 is arr):
//	LDR R4, [R5,#0]
//Hint 2: To do int x = arr[1], do this:
//	LDR R4, [R5,#4]
//(In other words, each int is **4 bytes** past the previous one
//Hint 3: You will segfault if you don't check arr to be a null pointer
//Hint 4: You will segfault if you fail to check to see if index is < 2

.global asm_fibber
asm_fibber:
	PUSH {LR}
	PUSH {R4-R11}
	CMP R0, #0
	BEQ done

	CMP R1, #2
	BLT done
	
	MOV R7, R1 // i = index;
	ADD R8, R1, R2 // index+count
top:
	CMP R7, R8
	BGE done	

	// same thing as arr[i-1]
	SUB R9, R7, #1
	LSL R9, #2 // multiply by 4 to get int offset location
	LDR R4, [R0, R9] // load arr[i-1] into R4 using arr+R9 offset


	// same thing as arr[i-2]
	SUB R10, R7, #2
	LSL R10, #2
	LDR R5, [R0, R10] // load arr[i-2] into R5 using arr+R10 offset

	ADD R11, R5, R4 // add arr[i-1] + arr[i-2], store into r11
	MOV R6, R7, LSL#2 // grab index offset (index*sizeof(int)) --- index*4bytes
	STR R11, [R0, R6] // finally, store the result of R11 into r0+r6
	
	ADD R7, #1 // increment index
	BAL top 
done:
	POP {R4-R11}
	POP {PC}
