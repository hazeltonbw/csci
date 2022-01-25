/*

You have to write these two functions in ASM:

int c_fun_one(int i, int j) {
	return 9*i + 7*j;
}

int c_fun_two(int i, int j) {
	return (4+i) - (j/4);
}
*/

.global asm_fun_one
asm_fun_one:
	PUSH {LR}
	PUSH {R4-R5}

	//Write yo code here: return 9*i + 7*j
	MOV R4, #9
	MOV R5, #7
	MUL R0, R4
	MUL R1, R5
	ADD R0, R1
	b quit

quit:
	POP {R4-R5}         @Restore R4 through R12 for the calling function
	POP {PC}             @Return from a function


.global asm_fun_two
asm_fun_two:
	PUSH {LR}

	ADD R0, #4
	MOV R1, R1, LSR #2
	SUB R0, R0, R1
	b quit2
	//Write yo code here: return (4+i) - (j/4)

quit2:
	POP {PC}             @Return from a function
