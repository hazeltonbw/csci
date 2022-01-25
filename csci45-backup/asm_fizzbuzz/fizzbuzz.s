/* Homework 2 - Assembly Fizzbuzz
 Your program must print the numbers from 1 to 100, except when:
 1) If the number is divisible by 15, print FizzBuzz instead, if not:
   2) If the number is divisible by 3, print Fizz instead
   3) If the number is divisible by 5, print Buzz instead
 I have provided you functions that will do the printing, you just need
 to do the control logic.

 Don't modify the C file at all, or your house will lose 50 points.

 Don't use R0 through R3 in this function (except in the one example below)
 They get overwritten every time you call a function.
 So use R4 through R10 for your logic

Any line marked with DM ("Don't Modify") should probably be left alone.
The rest of the source code is just example source code and can be deleted or changed.

*/
.global fizzbuzz 	     @DM - Don't modify
fizzbuzz:                @DM - Don't modify
	PUSH {LR}            @DM: Preserve LR for the calling function
	PUSH {R4-R7}        @DM: This preserves the R4 through R12 from the calling function
	MOV R4, #0
	MOV R5, #0 // COUNTER 3
	MOV R6, #0 // COUNTER 5
	top:
	ADD R4, R4, #1
	ADD R5, R5, #1
	ADD R6, R6, #1
	MOV R0, R4			 @Copy value of R4 into R0
	MOV R7, #0

	CMP R5, #3
	ADDEQ R7, #1
	MOVEQ R5, #0
	
	CMP R6, #5
	ADDEQ R7, #2
	MOVEQ R6, #0

	CMP R7, #0
	BLEQ print_number
	CMP R7, #1
	BLEQ print_fizz
	CMP R7, #2
	BLEQ print_buzz
	CMP R7, #3
	BLEQ print_fizzbuzz

	CMP R4, #100
	BLT top
return:
	POP {R4-R7}         @DM: Restore R4 through R12 for the calling function
	POP {PC}             @DM: Return from a function
