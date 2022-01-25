.global iota
iota:
	PUSH {R4, LR}

	@R0 contains the address in memory the array begins
	@R1 contains an int holding the size of the array
	@R2 contains an int holding the value to start with
	
	MOV R4, R1, LSL #2 // sizeof(arr) * sizeof(int) 
	ADD R4, R0 // r4 = end of array

	loop:
		CMP R0, R4
		BGE return
		STR R2, [R0], #4
		ADD R2, #1
		B loop


	//If you want to print a number to the screen for debugging purposes,
	// this is how you do it:
	@MOV R0,R7 //We want to print R7
	@BL print_number

return:
	POP {R4, PC}
