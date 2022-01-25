//Write a function that doubles all the elements in the array
//extern "C" void asm_double(uint32_t *arr, int size);

//I will write code that does this:
//int i = 0;
//while (i < size) arr[i++] *= 2;

.global asm_double
asm_double:
    PUSH {LR}
    PUSH {R4-R11}

	//Option 1 - Range-based loop
	//Range based loops run from one pointer to another pointer
	//We can compute the address of the end pointer
	//base + offset, offset is 4 * size
	MOV R4, R0 //arr = Base .... begin pointer
	MOV R5, R1, LSL #2 //size * 4 = Offset
	ADD R5, R4, R5 //End pointer = base+offset
top:
	CMP R4, R5
	BGE done
	LDR R6, [R4] 		//temp = arr[0]
	MOV R6, R6, LSL #1 	//temp *= 2
	STR R6, [R4]		//arr[0] = temp
	ADD R4, R4, #4		//arr++
	BAL top



	/* Option 2 - Regular For Loop

top:
	CMP R6,R5 //if (i >= size) break;
	BGE done
	LSL R7, R6, #2 //offset = i * 4
	LDR R8, [R4,R7] //temp = arr[i]
	LSL R8, #1		//temp *= 2
	STR R8, [R4,R7] //arr[i] = temp
	ADD R6, #1		//i++
	BAL top
	*/
	
done:
	POP {R4-R11}
	POP {PC}
