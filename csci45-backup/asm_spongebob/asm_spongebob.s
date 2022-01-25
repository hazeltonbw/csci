.global asm_spongebob 
asm_spongebob:
	push {lr}
	push {r4-r6}

	@ if the char * starts with a null char, do nothing.
	//cmp r0, #0 
	//beq return

	@ set up counter, move ptr into r4 so we can iterate over it.
	mov r5, #0 @ counter
	mov r4, r0 @ char * str

	@ start loop
	top:
		ldrb r6, [r4,r5] @ load each byte, use counter to increment
		cmp r6, #0
		beq return

		mov r0, r6
		bl isalpha
		cmp r0, #0
		bne coinflip // if (isalpha(c)) coinflip()
		
		add r5, #1
		b top

	coinflip: 
		bl rand
		ands r0, r0, #1
		mov r0, r6
		beq lowercasify
		bne uppercasify

	uppercasify:
		cmp r0, #'a'
		cmpge r0, #'z'
		bicle r0, #32 // bit clear
		// https://www.keil.com/support/man/docs/armasm/armasm_dom1361289864906.htm
		strb r0, [r4,r5]
		add r5, #1
		b top

	lowercasify:
		cmp r0, #'A'
		cmpge r0, #'Z'
		orrle r0, #32
		strb r0, [r4,r5]
		add r5, #1
		b top

	return:
		pop {r4-r6}
		pop {pc}
