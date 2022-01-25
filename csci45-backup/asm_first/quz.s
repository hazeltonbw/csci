//Write the C++ equivalent of this code:
//int quz(int x, int y, int z, int w) { return (x-y)*(z+w) - (x-y)*(-1*z + -1*w); }
//Par: 7 strokes

.global quz
quz:
	SUB R0, R0, R1 // X-Y
	ADD R2, R2, R3
	MUL R0, R0, R2
	ADD R0, R0, R0
	BX LR
	// 7 strokes
