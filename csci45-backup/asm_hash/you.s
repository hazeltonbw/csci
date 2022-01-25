//YOU: Insert the first SIZE/2 elements from randos into hash_table using linear probing or whatever hash method you want
//Hash_table is of size SIZE
//void asm_hash_insert(int *hash_table, int *randos, int SIZE);
.global asm_hash_insert
asm_hash_insert:
	PUSH {FP, LR}
	PUSH {R4-R11}

	MOV R11, R2
	MOV R4, R2 
	ASR R4, #1 //  R4 = SIZE / 2 .... ONLY INSERTING HALF OF THE ELEMENTS...
			                ///////   THE OTHER HALF IS FOR SEARCH
	MOV R5, R0 // backup hash_table
	MOV R6, R1 // BACKUP RANDOS
	
	MOV R7, #0 // for (int i = 0; i < R4, i++) 
	loop:
		CMP R7, R4
		BGE quit
		LDR R0, [R6], #4
		MOV R9, R0 // store the random number
		MOV R1, R11 // random number % size of hash table
		//B find_empty_spot
		find_empty_spot:
			BL modulo
			MOV R8, R0 // INDEX NUMBER OF RANDOM NUMBER
			LSL R8, #2
			LDR R0, [R5, R8]
			CMP R0, #0 // IF ELEMENT IS 0, SPOT IS EMPTY. INSERT.
			STREQ R9, [R5, R8]
			MOVNE R0, R8
			MOVNE R1, R11
			ASRNE R0, #2
			ADDNE R0, #1
			BNE find_empty_spot

		ADD R7, #1
		B loop
	quit:
		POP {R4-R11}
		POP {FP, PC}
		BX LR
		
//YOU: Return true or false based on if the key is in the table
//Hash_table is of size SIZE
//bool asm_hash_search(int *hash_table, int key, int SIZE); 
.global asm_hash_search
asm_hash_search:
	PUSH {FP, LR}
	PUSH {R4-R11}

	MOV R5, R0 // BACKUP HASH TABLE
	MOV R6, R2 // BACKUP SIZE
	MOV R7, R1 // BACKUP KEY
	MOV R0, R1 // modulo(int numerator, int denominator)
	MOV R1, R6 // int denominator
			   // key % SIZE = hash
	look_for_key:
		BL modulo
		MOV R8, R0 // INDEX NUMBER OF RANDOM NUMBER
		LSL R8, #2
		LDR R0, [R5, R8]
		CMP R0, #0
		//BEQ return_false // if loaded value is 0, spot is empty, not in hash table
		MOVEQ R0, #0
		BEQ quit
		CMP R0, R7 // now compare against key
		MOVEQ R0, #1
		BEQ quit
		ASRNE R8, #2
		ADDNE R8, #1
		MOVNE R0, R8
		MOVNE R1, R6
		BNE look_for_key
