//Want a list of all NEON instructions?
//http://infocenter.arm.com/help/topic/com.arm.doc.dui0489e/CJAJIIGG.html

//This program will show simple VFP commands to do the following C++ code:
//double h, f = -1.1, y = 121.1;
//h = f * y;
//cout << "h = " << h << endl;
//h *= 3
//cout << "h = " << abs(h) << endl;
.global main
main:
	//Normal registers - R0 through R15 basically just hold ints
	//If you want to do stuff with floats, you use S0-S31 for single precision
	//If you want doubles instead, use D0-D31 for double precision
	LDR R0, =F //float *ptr = &F; 
	VLDR S0, [R0] //IMPORTANT - use VLDR instead of normal LDR, normal LDR will not work
	LDR R0, =Y //ptr = &Y
	VLDR S1, [R0] //float y = *ptr
	LDR R0, =THREE
	VLDR D3, [R0] //double three = *ptr, note the use of D3 - that tells it to load 64 bits
	VCVT.F64.F32 D1, S0 //This is how you cast in assembly
	VCVT.F64.F32 D2, S1 //double a = f; double b = y;
	VADD.F64 D0, D1, D2 //double c = a + b;
	VSUB.F64 D0, D1, D2 //double c = a - b;
	VMUL.F64 D0, D1, D2 //double c = a * b;
//print
	VMOV R2, R3, D0 //Move things between the NEON registers and normal ARM registers - this has two destination registers!!!! R2 and R3 are both destination registers
	//The ARM32 ABI specifies what parameters functions take
	//If you are only passing a double to a function like abs(x), then it uses R0&R1 to hold the double
	//If you are passing in a double as a second parameter, it always uses R2&R3
	LDR R0, =printStr //R0 is the string, R2 and R3 are the double to print
	BL printf
	//Remmeber with a function call - Just assume R0 through R3 are gone at this point

	//multiply 3 and abs
	VMUL.F64 D0, D0, D3 //c *= 3;
	VABS.F64 D0, D0 //c = abs(c)
	VMOV R2, R3, D0
	LDR R0, =printStr
	BL printf


	//exit(EXIT_SUCCESS);
	MOV R0, #0 //Return value
	MOV R7, #1 //Choose syscall 1 i.e. exit
	SWI 0 //Syscall

.data
F: .float -1.1 //float F = -1.1
Y: .float 121.1 //float Y = 121.1
THREE: .double 3 //double THREE = 3.0 //Because you can't use #3

printStr: .asciz "h = %f\n" //const char *printStr = "%h = %f\n"
printInt: .asciz "%i\n" //const char *printInt = "%i\n"
