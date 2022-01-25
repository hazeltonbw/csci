	.global asm_if		@DM - Don't modify
asm_if:					@DM - Don't modify
	PUSH {LR}			@DM: Preserve LR for the calling function
	PUSH {R4-R12}		@DM: This preserves the R4 through R12 from the calling function


	/*
int c_if(int a, int b, int c, int d) {
	return ((a | b) && (c | d)) || ((a | ~d) & (~b & d));
}
*/
	//Write yo code here
	// A | B //
	ORRS R4, R0, R1
	MOVEQ R0, #0 // if the first OR is false, no need to continue
	BEQ return

	ORRS R4, R2, R3 
	MOVEQ R0, #0
	BEQ return
	MOVNE R0, #1
	BNE return

	MVN R5, R4
	ORRS R5, R5, R0

return:
	POP {R4-R12}         @DM: Restore R4 through R12 for the calling function
	POP {PC}             @DM: Return from a function

