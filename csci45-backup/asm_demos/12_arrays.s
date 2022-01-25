/* Static Arrays
	int arr[100];
	const int MULTIPLIER = 2;
	for (int i = 0; i < 100; i++) 
		arr[i] = MULTIPLIER * i;
	printf("Arr[10] = %i\n",arr[10]);
	return 0;
*/

//char *str = "Hello World"
//str[4] = 'A';
//Let's say R5 contains str
//R6 contains 4
//MOV R7, #65
//STRB R7, [R5,R6] //str[4] = 'A'

//LDR and STR load and store ints (32 bits)
//LDRB and STRB load and store chars (8 bits)

.global main
main:
	LDR R1, =arr	//int arr[100];
	MOV R2, #0		//i = 0;
	MOV R3, #MULTIPLIER //MULTIPLIER = 2
	MOV R4, #BPI	//4 bytes per int

//for (int i = 0; i < 100; i++)
top: 
	CMP R2, #100	//i < 100
	BGE bottom
	MUL R5, R2, R3	//int temp = MULTIPLIER * i

	//Since ARM is byte addressed and ints are four bytes each, we must compute how many memory addresses we are to the right by multiplying the number of ints we've written by 4
	MUL R6, R2, R4	//int offset = (4 * i)
	STR R5, [R1,R6]	//arr[offset] = temp

	ADD R2, R2, #1	//i++
	BAL top
bottom:
	//Now we will print arr[10] with a printf
	MOV R2, #10
	MUL R6, R2, R4 //Offset = 10 * 4 bytes
	LDR R0, =print_string //First param the string
	LDR R1, [R1,R6] //Second param arr[10]
	BL printf		//Call printf

	//WARNING - R0 through R3 are now invalid, do not use after this point
	//But we're done anyway, so I don't care.
	MOV R0,	#0 //Return 0
	MOV R7, #1		//Exit(0)
	SWI 0			//Syscall

.data
.equ MULTIPLIER, 2 //const int MULTIPLIER = 2
.equ BPI, 4 //4 bytes per int
arr: .space 400 //400 bytes reserved (100 ints)
print_string: .asciz "Arr[10] = %i\n"









