#You are going to write two functions here:
# function_one
# function_two

.global function_one
function_one:
    PUSH {LR}
    PUSH {R4-R12}        @This preserves R4 through R12 
	

quit:
	MOV R0,#0			 @Return value of 0
    POP {R4-R12}         @Restore R4 through R12 for the calling function
	POP {PC}             @Return from a function

.global function_two
function_two:
    PUSH {LR}
    PUSH {R4-R12}        @This preserves R4 through R12 

quit2:
	MOV R0,#0			 @Return value of 0
    POP {R4-R12}         @Restore R4 through R12 for the calling function
	POP {PC}             @Return from a function
