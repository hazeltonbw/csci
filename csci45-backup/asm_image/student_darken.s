#Write your image darkening code here in assembly
//void sdarken(unsigned char *in,unsigned char *out, int width, int height)
.global sdarken
sdarken:
	push {lr}
	mul r3, r2, r3 // width * height
	// r3 = (width * height) * 3                               /
	add r3, r3, lsl #1 //(width * height) << 1 + (width*height)/
	                   // prefer this instead of mul           / 
					   // don't need any registers this way    /
	//mul r3, r5, r3   // better than this way                 /
	////////////////////////////////////////////////////////////
	add r3, r0 // add memory address of array *in
	top:

	// LOADS 128 BITS AT A TIME
	/*
		vld1.u8 {q0}, [r0]! // load 128-8 bit unsigned chars into q0, and
							// increment the pointer of r0 after! 
		vshr.u8 q0, #1 // shift all the bits loaded right 1 time (value / 2)
		vst1.u8 {q0}, [r1]! // store the bits into r1,
							// then increment the pointer of r1!
	*/


	// LOADS 256 BITS AT A TIME, USING Q0 AND Q1 REGISTER
		vldmia.u8 r0!, {d0-d3}
		vshr.u8 q0, #1
		vshr.u8 q1, #1
		vstmia r1!, {d0-d3}
		cmp r0, r3 
		blt top

	pop {pc}
