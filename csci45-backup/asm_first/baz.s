//Write the assembly equivalent of this C++ code:
//int baz(int x, int y, int z) { return 5*x + 5*x*y + 5*x*y*z; }
//Par: 11 strokes
.global baz
baz:
	ADD R0, R0, R0, LSL #2 // 5*x    (4 + 1) * x
	MUL R1, R0, R1
	MUL R2, R1, R2
	ADD R0, R0, R1
	ADD R0, R0, R2
	BX LR
	// 11 strokes
