//This file has two functions in it, foo and bar
//The other files have one each. 
//Par: 6 strokes

//Foo should be the assembly version of this function:
//int foo(int x) { return 4*x; }
.global foo
foo:
	LSL R0, #2
	BX LR

//Bar should be the assembly version of this function:
//int bar(int x, int y) { return xy - pow(y,2); } y(x-y)
.global bar
bar:
	SUB R0, R0, R1
	MUL R0, R0, R1
	BX LR
	// 6 strokes
