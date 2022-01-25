/*
extern "C" void asm_print_array(int *arr, size_t ROWS, size_t COLS);
extern "C" void print_int(int x) { cout << x; }
extern "C" void print_space() { cout << " "; }
extern "C" void print_newline() { cout << endl; }

void print_array(int *arr, size_t ROWS, size_t COLS) {
    for (size_t i = 0; i < ROWS; i++) {
        for (size_t j = 0; j < COLS; j++)
            cout << arr[i*COLS+j] << " ";
        cout << endl;
    }
}
*/

.global asm_print_array
asm_print_array:
    PUSH {LR}
    PUSH {R4-R11}
	MOV R4, R0 //arr
	MOV R5, R1 //ROWS
	MOV R6, R2 //COLS
	MOV R7, #-1 //i
outerloop:
	ADDS R7, #1
	BLGT print_newline //Don't print a newline before the first row
	CMP R7,R5
	BGE done
	MOV R8, #-1 //j
innerloop:
	ADD R8, #1
	CMP R8, R6
	BGE outerloop

	//MLA = Multiply + Accumulate (Multiply & Add)
	MLA R9, R7, R6, R8 //Compute i*COLS+j
	MOV R0, #4   //Ints are 4 bytes each, don't forget this
	MUL R9, R9, R0
	LDR R0, [R4,R9]
	BL print_int
	BL print_space
	BAL innerloop

done:
	BL print_newline
	POP {R4-R11}
    POP {PC}

