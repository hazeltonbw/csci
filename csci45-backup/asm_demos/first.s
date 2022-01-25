/* Hello my name is comment */
.global main
main:

MOV R0, #0 	@Hi, this is a comment
MOV R1, #101 //Super awesome
MOV R2, #5

loop:
	CMP R1,R2
	BLT finale
	ADD R0, R0, #1
	SUB R1, R1, R2
BAL loop

finale:
	//MOV R0, R1 //R0 is the return value
	MOV R7, #1 //System Call 1 - Exit
	SWI 0 //Software Interrupt - calls exit()
