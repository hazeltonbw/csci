// void custom_filter(unsigned char *in, unsigned char *out, int width, int height);
.global custom_filter
custom_filter:

	push {r4-r11,lr}

	mul r4, r3, r2 // width * height (used for offset)
	mov r5, r0
	add r5, r4
	add r5, r4
	add r5, r4
	mov r6, r0
	add r6, r4 // r6 = width * height + offset
	mov r7, r6
	add r7, r4 // r7 = 2(width * height) + offset
	// r0 = red pixels in, r6 = green pixels in, r7 = blue pixels in

	mov r8, r1
	mov r9, r1
	add r9, r4
	mov r10, r9
	add r10, r4
	top:

		vldmia.u8 r0!, {q0}
		vldmia.u8 r6!, {q1}
		vldmia.u8 r7!, {q2}


		vstmia.u8 r8!, {q1}	
		vstmia.u8 r9!, {q2}	
		vstmia.u8 r10!, {q0}	

		cmp r7, r5
		blt top
	pop {r4-r11,pc}
