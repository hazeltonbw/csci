/* Pointers
	int score = 40;
	int *ptr = &score;
	*ptr += 2;
	return score;
*/

.global main
main:
	LDR R1,=score 	//int *ptr = &score
	LDR R0,[R1]		//int temp = *ptr
	ADD R0, R0, #2	//temp += 2 (change it in register)
	STR R0,[R1]		//*ptr = temp
	BX LR			//return score

.data
score: .word 40		//int score = 40;
