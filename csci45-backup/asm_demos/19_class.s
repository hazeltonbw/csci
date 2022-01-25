//To compile this:  g++ 19_class.s class.cc

/*
To work with a class or struct, we need to know the offsets of each member variable. We can compute this by hand...

struct SSN_Record {
	int ssn; //Offset +0
	char initials[3]; //Offset +4
	long long phone_number; //Offset +8
	char *name; //Offset +16
	char *address; //Offset +20
};
*/

//To make the code more readble, turn the offsets into consts
.equ SSN, 0
.equ INITIALS, 4
.equ PHONE_NUMBER, 8
.equ NAME, 16
.equ ADDRESS, 20

//extern void asm_mess_with_ssn(SSN_Record *);
//This function will add a number to each member variable
//R0 is a pointer to an SSN_Record to mess with
.global asm_mess_with_ssn
asm_mess_with_ssn:
	PUSH {LR} 
	PUSH {R4-R11}

	LDR R1, [R0,#SSN] //Load 32 bits
	ADD R1, #1
	STR R1, [R0,#SSN]

	LDR R1, [R0,#PHONE_NUMBER]
	ADD R1, #2
	STR R1, [R0,#PHONE_NUMBER]

	LDR R1, [R0,#NAME] 
	ADD R1, #1 //What is this doing, and why is it probably wrong?
	STR R1, [R0,#NAME]

	LDR R1, [R0,#ADDRESS] 
	LDR R2, [R1]
	ADD R2, #3
	STR R2, [R1]

/* Why does this seg fault?
	LDR R1, [R0,#INITIALS] 
	LDRB R2, [R1]
	ADD R2, #1
	STRB R2, [R1]
*/


	POP {R4-R11}
	POP {PC}
