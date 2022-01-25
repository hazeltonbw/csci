//Any time you type "my_if" below it expands into these three lines of code
.macro my_if
	CMP R4, R5 //Compare R4 and R5
	MOV R0, R7
	MOV R1, R8
	MOV R2, R6
.endm

//This is how you make a function
//int add_function(int x, int y) { return x+y; }
.global add_function
add_function:
	PUSH {LR} //Save Link Register - i.e. the return address
	PUSH {R4-R11} //Preserve registers - not technically necessary here, but it's a good habit for you to get into
    ADD R0, R0, R1 //First parameter is R0, second is R1, return value is R0
	POP {R4-R11} //Restore saved registers
	POP {PC} //Return to Link Register

//To compile: "gcc 7_functions.s read_int.c"
//Or look inside read_int.c to see how to turn it into a shared object library
.global main
main:
	PUSH {LR} 
	PUSH {R4-R11}
	BL prompt //BL is how you call a function by name
	BL read_int //This I wrote in C, returns an int in R0
	MOV R4, R0
	MOV R7, R0 //We change R4 below so save a copy
	BL read_int
	MOV R5, R0
	MOV R8, R0 //Ditto
	BL read_int
	MOV R6, R0

	BL print_signed_compare
	//This is replaced by the my_if macro above
	//CMP R4, R5 //Compare R4 and R5
	//MOV R0, R7
	//MOV R1, R8
	//MOV R2, R6
	my_if
	BLLT less_than //Prints R4 is less than R5
	my_if
	BLEQ equal_to  //Prints R4 is equal to R5
	my_if
	BLGT greater_than //Prints R4 is greater than R5

	//Now do signed comparison (have to do comparison again because the bits are probably cleared by the previous function calls
	BL print_unsigned_compare
	my_if
	BLCC unsigned_less_than
	my_if
	BLEQ unsigned_equal_to  //Prints R4 is equal to R5
	my_if
	BLCS unsigned_greater_than

	//Now we want to return if x is >= y and x <= z
	SUB R4, R4, R5 
	SUB R5, R6, R5
	my_if
	BLCC within
	my_if
	BLCS not_within

	POP {R4-R11}
	POP {PC}

