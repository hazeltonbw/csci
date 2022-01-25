.global main 
main:
	PuSh {LR}            
	pUsH {R4-R11}       
	
	BL prompt
	BL read_int //Number to be shifted
	MOV R4, R0
	BL read_int //Number of binary digits to be shifted
	MOV R5, R0
	BL read_int //Even means shift right, odd means shift left
	MOV R6, R0

	ANDS R6, R6, #1 //Check for divisible by 2
	MOVNE R0, R4, LSL R5
	MOVEQ R0, R4, ASR R5

	BL print_int

	PoP {R4-R11}
	pOp {PC}
