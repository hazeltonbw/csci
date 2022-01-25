//Learning point for today:
//ARM32 is BYTE-ADDRESSABLE MEMORY
//LDR loads 32 bits from a memory address (I think it has be 32 bit aligned)
//LDRB loads 8 bits from a memory address (it can be any byte in memory)
//STR stores 32 bits from a register to memory (32-bit aligned)
//STRB stores 8 bits to a memory address
//NOTE: STR VIOLATES THE PATTERN OF ARM32. THE FIRST PARAMETER IS THE SOURCE
//  NOT THE DESTINATION

//void delete_bs(char *str);
.global delete_bs
delete_bs:
	PUSH {LR}
    PUSH {R4-R11}

	//R0 is set to be the start of a memory block holding a string
	LDRB R1, [R0,#0] //Read the first byte from the string
	CMP R1, #'B' //Is it a B?
	MOVEQ R1, #' ' //If it is, delete it
	STRB R1, [R0,#0] //Write it back into RAM


done:
    POP {R4-R11}
    POP {PC}
