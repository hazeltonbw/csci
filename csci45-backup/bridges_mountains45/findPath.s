  
 //void findPath(int *elev_data, int imgWidth, int imgHeight, int startRow, int maxVal)
.global findPath
findPath:
	push {lr}
	push {r4-r12}
	cmp r3, #0
	blt nope
	cmp r3, r2
	bge nope
	
	mov r4, #0 // int col = 0;
	// r5 = (startRow * imgWidth + col) * sizeof(int)
	sub r7, r1, #1 // imgWidth  - 1
	sub r8, r2, #1 // imgHeight - 1

	top:
		// if (col >= imgWidth - 1) 
		cmp r4, r7
		bge done

		mla r5, r3, r1, r4
		lsl r5, #2
		mov r6, #-1
		str r6, [r0, r5]

		// if (row >= imgHeight - 1) 
		cmp r3, r8
		bge bottom_row
		cmp r3, #0
		bge top_row
		add r4, #1
		
	top_row:
		// Check right and bottom right only
		ldr r10, [r0, r5]
		//cmp r3, r8 // if (startRow == imgHeight - 1)

	bottom_row:
		bal done

	general_case:
		bal done

nope:
	ldr r0, =text	
	bl printf
	bal done

done:
	pop {r4-r12}
	pop {pc}

.data
text:
	.asciz "Invalid starting row.\n"
