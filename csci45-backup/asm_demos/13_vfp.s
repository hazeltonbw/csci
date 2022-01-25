/* How to do floats and doubles
Might need to compile with: gcc 13_vfp.s -mfpu=neon

	//Example of using floats and doubles...
	double p = 3.1415f; //Load a float into a double
	double TWO = 2.0;
	p = p / TWO; //Look - division exists!
	printf("PI / 2 = %f",p);

	//Example computing radioactive decay
	const int SIZE = 100;
	double arr[SIZE];
	const float DIVISOR = 1.3;
	arr[0] = 200;
	for (int i = 1; i < SIZE; i++) {
		arr[i] = arr[i-1] / DIVISOR;
		printf("Arr[%i] = %f\n",i,arr[i]);
	}
	return 0;
*/

.global main
main:
	// *************************************************
	// NOTE: register D0 is S0 & S1, D1 is S2 & S3, etc.
	//  I.e. they are the same registers, but can be
	//  used in either 32 bit or 64 bit modes
	// *************************************************

	//This part will load PI, divide it by 2, and print it

	//    double p = 3.1415f; //We're going to load a float into a double
	LDR R0, =PI //Load the address of PI into R0
	VLDR S0,[R0] //Load from the address into S0 single precision (32-bit) float register
	//PI is a .float (32-bit) so we will convert to 64-bit
	VCVT.F64.F32 D4, S0	//Convert from 32-bit float to 64-bit double float

	// double TWO = 2.0; 
	LDR R0, =TWO
	VLDR D5, [R0]
	//No need to convert it from F32 to F64 since it is a .double down below, not a .float

	VDIV.F64 D3,D4,D5 //D3 = D4 / D5 (i.e. PI / 2) The .F64 means do 64-bit float division

	//    printf("PI / 2 = %f",p);
	VMOV R2, R3, D3 //Prepare parameters to be passed to printf. NOTE THIS IS WEIRD - R0, R2 and R3!?
	//What happened to R1? Answer: When doing doubles as params, they go into either R0&R1 or R2&R3.
	LDR R0, =print_string1
	BL printf
	# Uncomment these lines to quit here
	# MOV R0, #0	//Return 0
	# MOV R7, #1	//Exit(0)
	# SWI 0			//Syscall


	//Now we will do the second part
	// const int SIZE = 100;
	// double arr[SIZE];
	// const float DIVISOR = 1.3;
	// arr[0] = 200;

	MOV R7, #BPD //8 bytes per double

	LDR R0, =TWO_HUNDRED
	VLDR D0, [R0] //D0 (64 bit float register) = 200.0
	LDR R0, =DIVISOR
	VLDR D1, [R0] //D1 (64 bit float register) = 1.3

	LDR R4, =arr	//double arr[100]; (This is 100 * 8 = 800 bytes long)
	MOV R5, #0 		//Counter
	VSTR D0,[R4]	//arr[0] = 200;

//for (int i = 0; i < SIZE; i++)
top:
//printf("Arr[%i] = %f\n",i,arr[i]);
	MOV R1, R5 //R1 = i
	VMOV R2, R3, D0 //THIS IS STILL WEIRD
	LDR R0, =print_string2
	BL printf

	ADD R5, R5, #1 //i++
	CMP R5, #SIZE //i >= 100
	BGE bottom
	MUL R6, R5, R7 //Offset = 8 * i
	VDIV.F64 D0, D0, D1 //D0 /= 1.3
	//VMOV.F64 D0, D2
	VSTR D0,[R4,R6]	//arr[i] = D0;
	BAL top

	//Note I don't do anything with the data stored to RAM anywhere, since it was easier to just print it when computing it. But if I wanted to use it later:
	//VLDR.F64 D0,[R4,R6] //Loads arr[R6] into D0

	//The kicker here is that D0 and R0 are a totally different set of registers, so you have to move them back and forth to do printfs and such, and that can hurt performance. It's best to just stick in VFP world as much as you can when you are worried about performance.

bottom:
	MOV R0, #0	//Return 0
	MOV R7, #1	//Exit(0)
	SWI 0			//Syscall

.data
TWO: .double 2
TWO_HUNDRED: .double 200
PI: .float 3.1415
DIVISOR: .double 1.3
.equ BPD, 8 //8 bytes per double
.equ SIZE, 100 //100 elements in our array
//arr: .space BPD*SIZE //800 bytes reserved (100 doubles)
arr: .space 800 //800 bytes reserved (100 doubles)
print_string:  .asciz "Hello World!\n"
print_string1: .asciz "-----\nPI / 2 = %f\n-----\n"
print_string2: .asciz "Arr[%i]\t=\t%018.14f grams\n"
