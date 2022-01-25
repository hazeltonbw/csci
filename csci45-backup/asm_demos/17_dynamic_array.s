//To compile: gcc 17_dynamic_array.s read_int.c

//Memory management is really hard to do well.
//Well, allocating memory is easy. Deallocating is hard.
//We will use sbrk(x) to allocate x bytes of memory
//Type man sbrk for more info

//In this example, we will allocate RAM
//using the sbrk "system call". (It's actually a library function masquerading as the old syscall.)
//int x;
//cin >> x;
//int *ptr = new int[x];
//if (ptr == -1) exit(EXIT_FAILURE);
//else {
//  ptr[100] = 53;
//	exit(EXIT_SUCCESS);
//}

.global main
main:
PUSH {LR}
PUSH {R4-R12}

BL read_int //Get how many bytes to allocate into R0
MOV R4, R0 //Save into R4
MOV R0, R0, LSL #2 //Multiply by 4, since ints are 4B
//Note: Experimentation shows the limit between 100MB and 1GB for this system call
BL sbrk //Allocate R0 bytes
CMP R0, #-1 //-1 is returned on an error
BEQ die
MOV R5, R0 //Save pointer into R5
//Now write 53 to element 100
MOV R1, #53
MOV R2, #400 //Index 100 is 100*4 bytes in, since ints are 4 bytes each
STR R1, [R5,R2] //ptr[100] = 53

done:
MOV R0, #0 //0 is EXIT_SUCCESS
POP {R4-R12}
POP {PC}

die:
MOV R0, #1 //1 is EXIT_FAILURE
POP {R4-R12}
POP {PC}

