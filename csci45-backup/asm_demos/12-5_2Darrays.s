//extern "C" void asm_arr(int *arr,int *end);

.global asm_arr
asm_arr:
	PUSH {LR}
    PUSH {R4-R11}

	MOV R4, R0 //Save arr into R4
	MOV R5, R1 //Save end into R5
top:
	LDR R6, [R4] //int x = arr[0]
	ADD R6, #1	 //x++;
	STR R6, [R4] //arr[0] = x;
	ADD R4, #4	 //arr++;
	CMP R4, R5 	 //Is arr >= end?
	BLT top

	POP {R4-R11}
    POP {PC}
