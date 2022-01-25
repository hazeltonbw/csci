	.arch armv6
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 18, 4
	.file	"Hangman.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,4
	.global	guessed
	.bss
	.align	2
	.type	guessed, %object
	.size	guessed, 4
guessed:
	.space	4
	.global	board
	.align	2
	.type	board, %object
	.size	board, 4
board:
	.space	4
	.global	HangWord
	.align	2
	.type	HangWord, %object
	.size	HangWord, 4
HangWord:
	.space	4
	.global	guess
	.type	guess, %object
	.size	guess, 1
guess:
	.space	1
	.global	gmax
	.align	2
	.type	gmax, %object
	.size	gmax, 4
gmax:
	.space	4
	.global	HangmanArray
	.data
	.align	2
	.type	HangmanArray, %object
	.size	HangmanArray, 42
HangmanArray:
	.byte	32
	.byte	95
	.byte	95
	.byte	95
	.byte	95
	.byte	32
	.byte	32
	.byte	124
	.byte	32
	.byte	32
	.byte	124
	.byte	32
	.byte	32
	.byte	124
	.byte	32
	.byte	32
	.byte	32
	.byte	32
	.byte	32
	.byte	124
	.byte	32
	.byte	32
	.byte	32
	.byte	32
	.byte	32
	.byte	124
	.byte	32
	.byte	32
	.byte	32
	.byte	32
	.byte	32
	.byte	124
	.byte	32
	.byte	32
	.byte	32
	.byte	32
	.byte	95
	.byte	124
	.byte	95
	.byte	95
	.byte	95
	.byte	32
	.text
	.align	2
	.global	_Z8ArraySetv
	.type	_Z8ArraySetv, %function
_Z8ArraySetv:
	.fnstart
.LFB970:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	str	fp, [sp, #-4]!
	add	fp, sp, #0
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	cmp	r3, #1
	bne	.L2
	ldr	r3, .L9+4
	mov	r2, #79
	strb	r2, [r3, #16]
	b	.L1
.L2:
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	cmp	r3, #2
	bne	.L4
	ldr	r3, .L9+4
	mov	r2, #124
	strb	r2, [r3, #22]
	b	.L1
.L4:
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	cmp	r3, #3
	bne	.L5
	ldr	r3, .L9+4
	mov	r2, #124
	strb	r2, [r3, #28]
	b	.L1
.L5:
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	cmp	r3, #4
	bne	.L6
	ldr	r3, .L9+4
	mov	r2, #47
	strb	r2, [r3, #33]
	b	.L1
.L6:
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	cmp	r3, #5
	bne	.L7
	ldr	r3, .L9+4
	mov	r2, #92
	strb	r2, [r3, #35]
	b	.L1
.L7:
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	cmp	r3, #6
	bne	.L8
	ldr	r3, .L9+4
	mov	r2, #92
	strb	r2, [r3, #15]
	b	.L1
.L8:
	ldr	r3, .L9
	ldr	r3, [r3, #0]
	cmp	r3, #7
	bne	.L1
	ldr	r3, .L9+4
	mov	r2, #47
	strb	r2, [r3, #17]
.L1:
	add	sp, fp, #0
	ldmfd	sp!, {fp}
	bx	lr
.L10:
	.align	2
.L9:
	.word	gmax
	.word	HangmanArray
	.cantunwind
	.fnend
	.size	_Z8ArraySetv, .-_Z8ArraySetv
	.section	.rodata
	.align	2
.LC0:
	.ascii	"clear\000"
	.text
	.align	2
	.global	_Z10CrudeClearv
	.type	_Z10CrudeClearv, %function
_Z10CrudeClearv:
	.fnstart
.LFB971:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	ldr	r0, .L12
	bl	system
	ldmfd	sp!, {fp, pc}
.L13:
	.align	2
.L12:
	.word	.LC0
	.fnend
	.size	_Z10CrudeClearv, .-_Z10CrudeClearv
	.section	.rodata
	.align	2
.LC1:
	.ascii	"\000"
	.text
	.align	2
	.global	_Z5Resetv
	.type	_Z5Resetv, %function
_Z5Resetv:
	.fnstart
.LFB972:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	ldr	r0, .L15
	ldr	r1, .L15+4
	bl	_ZNSsaSEPKc
	ldr	r0, .L15+8
	ldr	r1, .L15+4
	bl	_ZNSsaSEPKc
	ldr	r0, .L15+12
	ldr	r1, .L15+4
	bl	_ZNSsaSEPKc
	bl	_Z10CrudeClearv
	ldr	r3, .L15+16
	mov	r2, #0
	str	r2, [r3, #0]
	ldr	r3, .L15+20
	mov	r2, #32
	strb	r2, [r3, #16]
	ldr	r3, .L15+20
	mov	r2, #32
	strb	r2, [r3, #22]
	ldr	r3, .L15+20
	mov	r2, #32
	strb	r2, [r3, #28]
	ldr	r3, .L15+20
	mov	r2, #32
	strb	r2, [r3, #33]
	ldr	r3, .L15+20
	mov	r2, #32
	strb	r2, [r3, #35]
	ldr	r3, .L15+20
	mov	r2, #32
	strb	r2, [r3, #15]
	ldr	r3, .L15+20
	mov	r2, #32
	strb	r2, [r3, #17]
	ldmfd	sp!, {fp, pc}
.L16:
	.align	2
.L15:
	.word	HangWord
	.word	.LC1
	.word	board
	.word	guessed
	.word	gmax
	.word	HangmanArray
	.fnend
	.size	_Z5Resetv, .-_Z5Resetv
	.section	.rodata
	.align	2
.LC2:
	.ascii	"\012\012\000"
	.align	2
.LC3:
	.ascii	" \000"
	.align	2
.LC4:
	.ascii	"_ \000"
	.text
	.align	2
	.global	_Z10PrintBoardv
	.type	_Z10PrintBoardv, %function
_Z10PrintBoardv:
	.fnstart
.LFB973:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #16
	sub	sp, sp, #16
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L18
.L21:
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L19
.L20:
	ldr	r1, .L27
	ldr	r2, [fp, #-8]
	mov	r3, r2
	mov	r3, r3, asl #1
	add	r3, r3, r2
	mov	r3, r3, asl #1
	ldr	r2, [fp, #-12]
	add	r3, r3, r2
	add	r3, r1, r3
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	ldr	r0, .L27+4
	mov	r1, r3
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L19:
	ldr	r3, [fp, #-12]
	cmp	r3, #5
	movgt	r3, #0
	movle	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L20
	ldr	r0, .L27+4
	ldr	r1, .L27+8
	bl	_ZNSolsEPFRSoS_E
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L18:
	ldr	r3, [fp, #-8]
	cmp	r3, #6
	movgt	r3, #0
	movle	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L21
	ldr	r0, .L27+4
	ldr	r1, .L27+12
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, #0
	str	r3, [fp, #-16]
	b	.L22
.L26:
	ldr	r0, .L27+16
	ldr	r1, [fp, #-16]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #32
	movne	r3, #0
	moveq	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	beq	.L23
	ldr	r0, .L27+4
	ldr	r1, .L27+20
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	b	.L24
.L23:
	ldr	r0, .L27+16
	ldr	r1, [fp, #-16]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #95
	movne	r3, #0
	moveq	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	beq	.L25
	ldr	r0, .L27+4
	ldr	r1, .L27+24
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	b	.L24
.L25:
	ldr	r0, .L27+16
	ldr	r1, [fp, #-16]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	ldr	r0, .L27+4
	mov	r1, r3
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L27+20
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
.L24:
	ldr	r3, [fp, #-16]
	add	r3, r3, #1
	str	r3, [fp, #-16]
.L22:
	ldr	r0, .L27+16
	bl	_ZNKSs6lengthEv
	mov	r3, r0
	mov	r2, r3
	ldr	r3, [fp, #-16]
	cmp	r2, r3
	movls	r3, #0
	movhi	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L26
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L28:
	.align	2
.L27:
	.word	HangmanArray
	.word	_ZSt4cout
	.word	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.word	.LC2
	.word	board
	.word	.LC3
	.word	.LC4
	.fnend
	.size	_Z10PrintBoardv, .-_Z10PrintBoardv
	.align	2
	.global	_Z10CheckBoardv
	.type	_Z10CheckBoardv, %function
_Z10CheckBoardv:
	.fnstart
.LFB974:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #8
	sub	sp, sp, #8
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L30
.L33:
	ldr	r0, .L34
	ldr	r1, [fp, #-8]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #95
	movne	r3, #0
	moveq	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	beq	.L31
	mov	r3, #0
	b	.L32
.L31:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L30:
	ldr	r0, .L34
	bl	_ZNKSs6lengthEv
	mov	r3, r0
	mov	r2, r3
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	movls	r3, #0
	movhi	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L33
	mov	r3, #1
.L32:
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L35:
	.align	2
.L34:
	.word	board
	.fnend
	.size	_Z10CheckBoardv, .-_Z10CheckBoardv
	.align	2
	.global	_Z12AddToGuessedv
	.type	_Z12AddToGuessedv, %function
_Z12AddToGuessedv:
	.fnstart
.LFB975:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #8
	sub	sp, sp, #8
	mov	r3, #0
	str	r3, [fp, #-8]
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L37
.L39:
	ldr	r0, .L41
	ldr	r1, [fp, #-12]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r2, [r3, #0]	@ zero_extendqisi2
	ldr	r3, .L41+4
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r2, r3
	movne	r3, #0
	moveq	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	beq	.L38
	mov	r3, #1
	str	r3, [fp, #-8]
.L38:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L37:
	ldr	r0, .L41
	bl	_ZNKSs6lengthEv
	mov	r3, r0
	mov	r2, r3
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	movls	r3, #0
	movhi	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L39
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L36
	ldr	r3, .L41+4
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	ldr	r0, .L41
	mov	r1, r3
	bl	_ZNSspLEc
	ldr	r3, .L41+8
	ldr	r3, [r3, #0]
	add	r2, r3, #1
	ldr	r3, .L41+8
	str	r2, [r3, #0]
.L36:
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L42:
	.align	2
.L41:
	.word	guessed
	.word	guess
	.word	gmax
	.fnend
	.size	_Z12AddToGuessedv, .-_Z12AddToGuessedv
	.align	2
	.global	_Z5Guessii
	.type	_Z5Guessii, %function
_Z5Guessii:
	.fnstart
.LFB976:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #24
	sub	sp, sp, #24
	str	r0, [fp, #-24]
	str	r1, [fp, #-28]
	mov	r3, #0
	str	r3, [fp, #-8]
	mov	r3, #0
	str	r3, [fp, #-12]
	b	.L44
.L54:
	ldr	r2, [fp, #-24]
	ldr	r3, [fp, #-28]
	rsb	r3, r3, r2
	str	r3, [fp, #-16]
	ldr	r0, .L56
	ldr	r1, [fp, #-12]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r2, [r3, #0]	@ zero_extendqisi2
	ldr	r3, .L56+4
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r2, r3
	bne	.L45
	ldr	r3, [fp, #-16]
	cmp	r3, #0
	bne	.L45
	mov	r3, #1
	b	.L46
.L45:
	mov	r3, #0
.L46:
	cmp	r3, #0
	beq	.L47
	ldr	r0, .L56+8
	ldr	r1, [fp, #-12]
	bl	_ZNSsixEj
	mov	r3, r0
	ldr	r2, .L56+4
	ldrb	r2, [r2, #0]	@ zero_extendqisi2
	strb	r2, [r3, #0]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	b	.L48
.L47:
	ldr	r0, .L56
	ldr	r1, [fp, #-12]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	mov	r2, r3
	ldr	r3, .L56+4
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	sub	r3, r3, #32
	cmp	r2, r3
	bne	.L49
	ldr	r2, [fp, #-28]
	ldr	r3, [fp, #-24]
	cmp	r2, r3
	bne	.L49
	mov	r3, #1
	b	.L50
.L49:
	mov	r3, #0
.L50:
	cmp	r3, #0
	beq	.L51
	ldr	r0, .L56+8
	ldr	r1, [fp, #-12]
	bl	_ZNSsixEj
	mov	r3, r0
	ldr	r2, .L56+4
	ldrb	r2, [r2, #0]	@ zero_extendqisi2
	sub	r2, r2, #32
	uxtb	r2, r2
	strb	r2, [r3, #0]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	b	.L48
.L51:
	ldr	r0, .L56
	ldr	r1, [fp, #-12]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	mov	r2, r3
	ldr	r3, .L56+4
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	add	r3, r3, #32
	cmp	r2, r3
	bne	.L52
	ldr	r3, [fp, #-28]
	add	r2, r3, #1
	ldr	r3, [fp, #-24]
	add	r3, r3, #1
	cmp	r2, r3
	bne	.L52
	mov	r3, #1
	b	.L53
.L52:
	mov	r3, #0
.L53:
	cmp	r3, #0
	beq	.L48
	ldr	r0, .L56+8
	ldr	r1, [fp, #-12]
	bl	_ZNSsixEj
	mov	r3, r0
	ldr	r2, .L56+4
	ldrb	r2, [r2, #0]	@ zero_extendqisi2
	add	r2, r2, #32
	uxtb	r2, r2
	strb	r2, [r3, #0]
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L48:
	ldr	r3, [fp, #-12]
	add	r3, r3, #1
	str	r3, [fp, #-12]
.L44:
	ldr	r0, .L56+8
	bl	_ZNKSs6lengthEv
	mov	r3, r0
	mov	r2, r3
	ldr	r3, [fp, #-12]
	cmp	r2, r3
	movls	r3, #0
	movhi	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L54
	ldr	r3, [fp, #-8]
	cmp	r3, #0
	bne	.L55
	bl	_Z12AddToGuessedv
.L55:
	bl	_Z8ArraySetv
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L57:
	.align	2
.L56:
	.word	HangWord
	.word	guess
	.word	board
	.fnend
	.size	_Z5Guessii, .-_Z5Guessii
	.align	2
	.global	_Z9checkwordSs
	.type	_Z9checkwordSs, %function
_Z9checkwordSs:
	.fnstart
.LFB977:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #16
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	mov	r3, #0
	str	r3, [fp, #-8]
	ldr	r0, [fp, #-16]
	bl	_ZNKSs6lengthEv
	mov	r3, r0
	cmp	r3, #0
	movne	r3, #0
	moveq	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	beq	.L68
	mov	r3, #0
	b	.L60
.L67:
	ldr	r0, [fp, #-16]
	ldr	r1, [fp, #-8]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #32
	moveq	r3, #0
	movne	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	beq	.L62
	ldr	r0, [fp, #-16]
	ldr	r1, [fp, #-8]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #64
	bls	.L63
	ldr	r0, [fp, #-16]
	ldr	r1, [fp, #-8]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #90
	bls	.L64
.L63:
	ldr	r0, [fp, #-16]
	ldr	r1, [fp, #-8]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #96
	bls	.L65
	ldr	r0, [fp, #-16]
	ldr	r1, [fp, #-8]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #122
	bls	.L64
.L65:
	mov	r3, #1
	b	.L66
.L64:
	mov	r3, #0
.L66:
	cmp	r3, #0
	beq	.L62
	mov	r3, #0
	b	.L60
.L62:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
	b	.L61
.L68:
	mov	r0, r0	@ nop
.L61:
	ldr	r0, [fp, #-16]
	bl	_ZNKSs6lengthEv
	mov	r3, r0
	mov	r2, r3
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	movls	r3, #0
	movhi	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L67
	mov	r3, #1
.L60:
	mov	r0, r3
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
	.fnend
	.size	_Z9checkwordSs, .-_Z9checkwordSs
	.section	.rodata
	.align	2
.LC5:
	.ascii	"Welcome to Hangman! Please enter a word or phrase: "
	.ascii	"\000"
	.text
	.align	2
	.global	_Z11InitialWordv
	.type	_Z11InitialWordv, %function
_Z11InitialWordv:
	.fnstart
.LFB978:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {r4, fp, lr}
	.save {r4, fp, lr}
	.setfp fp, sp, #8
	add	fp, sp, #8
	.pad #12
	sub	sp, sp, #12
.L72:
	ldr	r0, .L77
	ldr	r1, .L77+4
.LEHB0:
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L77+8
	bl	_ZNSolsEPFRSoS_E
	ldr	r0, .L77+12
	ldr	r1, .L77+16
	bl	_ZSt7getlineIcSt11char_traitsIcESaIcEERSt13basic_istreamIT_T0_ES7_RSbIS4_S5_T1_E
	sub	r3, fp, #16
	mov	r0, r3
	ldr	r1, .L77+16
	bl	_ZNSsC1ERKSs
.LEHE0:
	sub	r3, fp, #16
	mov	r0, r3
.LEHB1:
	bl	_Z9checkwordSs
.LEHE1:
	mov	r3, r0
	mov	r4, r3
	sub	r3, fp, #16
	mov	r0, r3
.LEHB2:
	bl	_ZNSsD1Ev
	cmp	r4, #0
	bne	.L76
.L70:
	bl	_Z10CrudeClearv
.LEHE2:
	b	.L72
.L76:
	mov	r0, r0	@ nop
.L75:
	sub	sp, fp, #8
	ldmfd	sp!, {r4, fp, pc}
.L74:
	sub	r3, fp, #16
	mov	r0, r3
	bl	_ZNSsD1Ev
.LEHB3:
	bl	__cxa_end_cleanup
.LEHE3:
.L78:
	.align	2
.L77:
	.word	_ZSt4cout
	.word	.LC5
	.word	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.word	_ZSt3cin
	.word	HangWord
	.global	__gxx_personality_v0
	.personality	__gxx_personality_v0
	.handlerdata
.LLSDA978:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE978-.LLSDACSB978
.LLSDACSB978:
	.uleb128 .LEHB0-.LFB978
	.uleb128 .LEHE0-.LEHB0
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB1-.LFB978
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L74-.LFB978
	.uleb128 0
	.uleb128 .LEHB2-.LFB978
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB978
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
.LLSDACSE978:
	.text
	.fnend
	.size	_Z11InitialWordv, .-_Z11InitialWordv
	.section	.rodata
	.align	2
.LC6:
	.ascii	"Source: https://github.com/JCAMP17/Hangman-Final-Pr"
	.ascii	"oject.git\012\000"
	.align	2
.LC7:
	.ascii	"Please enter the secret key. The passkey is \000"
	.align	2
.LC8:
	.ascii	"Enter a letter: \000"
	.align	2
.LC9:
	.ascii	"Wrong Guesses: \000"
	.align	2
.LC10:
	.ascii	"You must enter a valid letter.\000"
	.align	2
.LC11:
	.ascii	"LOSER! Press enter to play again.\000"
	.align	2
.LC12:
	.ascii	"WINNER! Press enter to play again.\000"
	.text
	.align	2
	.global	main
	.type	main, %function
main:
	.fnstart
.LFB979:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #24
	sub	sp, sp, #24
	mov	r0, #0
	bl	time
	mov	r3, r0
	mov	r0, r3
	bl	srand
	bl	rand
	mov	r2, r0
	ldr	r3, .L96
	smull	r1, r3, r3, r2
	mov	r1, r3, asr #5
	mov	r3, r2, asr #31
	rsb	r3, r3, r1
	mov	r1, #100
	mul	r3, r1, r3
	rsb	r3, r3, r2
	add	r3, r3, #1
	str	r3, [fp, #-12]
	ldr	r3, [fp, #-12]
	cmp	r3, #0
	bge	.L80
	ldr	r0, .L96+4
	ldr	r1, .L96+8
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
.L80:
	ldr	r0, .L96+4
	ldr	r1, .L96+12
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, [fp, #-12]
	bl	_ZNSolsEi
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
	sub	r3, fp, #24
	ldr	r0, .L96+20
	mov	r1, r3
	bl	_ZNSirsERi
.L94:
	bl	_Z11InitialWordv
	ldr	r3, [fp, #-24]
	mov	r3, r3, asr #1
	str	r3, [fp, #-16]
	bl	_Z10CrudeClearv
	mov	r3, #0
	str	r3, [fp, #-8]
	b	.L81
.L84:
	ldr	r0, .L96+24
	ldr	r1, [fp, #-8]
	bl	_ZNSsixEj
	mov	r3, r0
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #32
	movne	r3, #0
	moveq	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	beq	.L82
	ldr	r0, .L96+28
	mov	r1, #32
	bl	_ZNSspLEc
	b	.L83
.L82:
	ldr	r0, .L96+28
	mov	r1, #95
	bl	_ZNSspLEc
.L83:
	ldr	r3, [fp, #-8]
	add	r3, r3, #1
	str	r3, [fp, #-8]
.L81:
	ldr	r0, .L96+24
	bl	_ZNKSs6lengthEv
	mov	r3, r0
	mov	r2, r3
	ldr	r3, [fp, #-8]
	cmp	r2, r3
	movls	r3, #0
	movhi	r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L84
	bl	_Z10PrintBoardv
	ldr	r0, .L96+4
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
	ldr	r3, [fp, #-12]
	mov	r3, r3, asr #2
	str	r3, [fp, #-20]
	b	.L85
.L91:
	ldr	r0, .L96+4
	ldr	r1, .L96+32
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
	ldr	r0, .L96+20
	ldr	r1, .L96+36
	bl	_ZStrsIcSt11char_traitsIcEERSt13basic_istreamIT_T0_ES6_RS3_
	ldr	r3, .L96+36
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #64
	bls	.L86
	ldr	r3, .L96+36
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #90
	bls	.L87
.L86:
	ldr	r3, .L96+36
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #96
	bls	.L88
	ldr	r3, .L96+36
	ldrb	r3, [r3, #0]	@ zero_extendqisi2
	cmp	r3, #122
	bhi	.L88
.L87:
	bl	_Z10CrudeClearv
	ldr	r0, [fp, #-20]
	ldr	r1, [fp, #-16]
	bl	_Z5Guessii
	bl	_Z10PrintBoardv
	ldr	r0, .L96+4
	ldr	r1, .L96+40
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+44
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+48
	bl	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKSbIS4_S5_T1_E
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
	b	.L89
.L88:
	ldr	r0, .L96+4
	ldr	r1, .L96+52
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
.L89:
	ldr	r3, .L96+56
	ldr	r3, [r3, #0]
	cmp	r3, #6
	bgt	.L95
.L85:
	bl	_Z10CheckBoardv
	mov	r3, r0
	eor	r3, r3, #1
	uxtb	r3, r3
	cmp	r3, #0
	bne	.L91
	b	.L90
.L95:
	mov	r0, r0	@ nop
.L90:
	ldr	r3, .L96+56
	ldr	r3, [r3, #0]
	cmp	r3, #6
	ble	.L92
	ldr	r0, .L96+4
	ldr	r1, .L96+60
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
	b	.L93
.L92:
	ldr	r0, .L96+4
	ldr	r1, .L96+64
	bl	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	mov	r3, r0
	mov	r0, r3
	ldr	r1, .L96+16
	bl	_ZNSolsEPFRSoS_E
.L93:
	ldr	r0, .L96+20
	bl	_ZNSi3getEv
	ldr	r0, .L96+20
	bl	_ZNSi3getEv
	bl	_Z5Resetv
	b	.L94
.L97:
	.align	2
.L96:
	.word	1374389535
	.word	_ZSt4cout
	.word	.LC6
	.word	.LC7
	.word	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
	.word	_ZSt3cin
	.word	HangWord
	.word	board
	.word	.LC8
	.word	guess
	.word	.LC2
	.word	.LC9
	.word	guessed
	.word	.LC10
	.word	gmax
	.word	.LC11
	.word	.LC12
	.fnend
	.size	main, .-main
	.align	2
	.type	_Z41__static_initialization_and_destruction_0ii, %function
_Z41__static_initialization_and_destruction_0ii:
	.fnstart
.LFB1042:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	.save {fp, lr}
	.setfp fp, sp, #4
	add	fp, sp, #4
	.pad #16
	sub	sp, sp, #16
	str	r0, [fp, #-16]
	str	r1, [fp, #-20]
	ldr	r3, [fp, #-16]
	cmp	r3, #1
	bne	.L98
	ldr	r2, [fp, #-20]
	ldr	r3, .L102
	cmp	r2, r3
	bne	.L98
	ldr	r0, .L102+4
.LEHB4:
	bl	_ZNSt8ios_base4InitC1Ev
.LEHE4:
	ldr	r3, .L102+8
	ldr	r0, .L102+4
	mov	r1, r3
	ldr	r2, .L102+12
	bl	__aeabi_atexit
	sub	r3, fp, #8
	mov	r0, r3
	bl	_ZNSaIcEC1Ev
	sub	r3, fp, #8
	ldr	r0, .L102+16
	ldr	r1, .L102+20
	mov	r2, r3
.LEHB5:
	bl	_ZNSsC1EPKcRKSaIcE
.LEHE5:
	sub	r3, fp, #8
	mov	r0, r3
	bl	_ZNSaIcED1Ev
	ldr	r3, .L102+24
	ldr	r0, .L102+16
	mov	r1, r3
	ldr	r2, .L102+12
	bl	__aeabi_atexit
	ldr	r0, .L102+28
.LEHB6:
	bl	_ZNSsC1Ev
	ldr	r3, .L102+24
	ldr	r0, .L102+28
	mov	r1, r3
	ldr	r2, .L102+12
	bl	__aeabi_atexit
	ldr	r0, .L102+32
	bl	_ZNSsC1Ev
	ldr	r3, .L102+24
	ldr	r0, .L102+32
	mov	r1, r3
	ldr	r2, .L102+12
	bl	__aeabi_atexit
	b	.L98
.L101:
	sub	r3, fp, #8
	mov	r0, r3
	bl	_ZNSaIcED1Ev
	bl	__cxa_end_cleanup
.LEHE6:
.L98:
	sub	sp, fp, #4
	ldmfd	sp!, {fp, pc}
.L103:
	.align	2
.L102:
	.word	65535
	.word	_ZStL8__ioinit
	.word	_ZNSt8ios_base4InitD1Ev
	.word	__dso_handle
	.word	guessed
	.word	.LC1
	.word	_ZNSsD1Ev
	.word	board
	.word	HangWord
	.personality	__gxx_personality_v0
	.handlerdata
.LLSDA1042:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1042-.LLSDACSB1042
.LLSDACSB1042:
	.uleb128 .LEHB4-.LFB1042
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB5-.LFB1042
	.uleb128 .LEHE5-.LEHB5
	.uleb128 .L101-.LFB1042
	.uleb128 0
	.uleb128 .LEHB6-.LFB1042
	.uleb128 .LEHE6-.LEHB6
	.uleb128 0
	.uleb128 0
.LLSDACSE1042:
	.text
	.fnend
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.align	2
	.type	_GLOBAL__sub_I_guessed, %function
_GLOBAL__sub_I_guessed:
	.fnstart
.LFB1043:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	stmfd	sp!, {fp, lr}
	add	fp, sp, #4
	mov	r0, #1
	ldr	r1, .L105
	bl	_Z41__static_initialization_and_destruction_0ii
	ldmfd	sp!, {fp, pc}
.L106:
	.align	2
.L105:
	.word	65535
	.cantunwind
	.fnend
	.size	_GLOBAL__sub_I_guessed, .-_GLOBAL__sub_I_guessed
	.section	.init_array,"aw",%init_array
	.align	2
	.word	_GLOBAL__sub_I_guessed(target1)
	.section	.rodata
	.align	2
	.type	_ZZL18__gthread_active_pvE20__gthread_active_ptr, %object
	.size	_ZZL18__gthread_active_pvE20__gthread_active_ptr, 4
_ZZL18__gthread_active_pvE20__gthread_active_ptr:
	.word	_ZL22__gthrw_pthread_cancelm
	.weakref	_ZL20__gthrw_pthread_oncePiPFvvE,pthread_once
	.weakref	_ZL27__gthrw_pthread_getspecificj,pthread_getspecific
	.weakref	_ZL27__gthrw_pthread_setspecificjPKv,pthread_setspecific
	.weakref	_ZL22__gthrw_pthread_createPmPK14pthread_attr_tPFPvS3_ES3_,pthread_create
	.weakref	_ZL20__gthrw_pthread_joinmPPv,pthread_join
	.weakref	_ZL21__gthrw_pthread_equalmm,pthread_equal
	.weakref	_ZL20__gthrw_pthread_selfv,pthread_self
	.weakref	_ZL22__gthrw_pthread_detachm,pthread_detach
	.weakref	_ZL22__gthrw_pthread_cancelm,pthread_cancel
	.weakref	_ZL19__gthrw_sched_yieldv,sched_yield
	.weakref	_ZL26__gthrw_pthread_mutex_lockP15pthread_mutex_t,pthread_mutex_lock
	.weakref	_ZL29__gthrw_pthread_mutex_trylockP15pthread_mutex_t,pthread_mutex_trylock
	.weakref	_ZL31__gthrw_pthread_mutex_timedlockP15pthread_mutex_tPK8timespec,pthread_mutex_timedlock
	.weakref	_ZL28__gthrw_pthread_mutex_unlockP15pthread_mutex_t,pthread_mutex_unlock
	.weakref	_ZL26__gthrw_pthread_mutex_initP15pthread_mutex_tPK19pthread_mutexattr_t,pthread_mutex_init
	.weakref	_ZL29__gthrw_pthread_mutex_destroyP15pthread_mutex_t,pthread_mutex_destroy
	.weakref	_ZL30__gthrw_pthread_cond_broadcastP14pthread_cond_t,pthread_cond_broadcast
	.weakref	_ZL27__gthrw_pthread_cond_signalP14pthread_cond_t,pthread_cond_signal
	.weakref	_ZL25__gthrw_pthread_cond_waitP14pthread_cond_tP15pthread_mutex_t,pthread_cond_wait
	.weakref	_ZL30__gthrw_pthread_cond_timedwaitP14pthread_cond_tP15pthread_mutex_tPK8timespec,pthread_cond_timedwait
	.weakref	_ZL28__gthrw_pthread_cond_destroyP14pthread_cond_t,pthread_cond_destroy
	.weakref	_ZL26__gthrw_pthread_key_createPjPFvPvE,pthread_key_create
	.weakref	_ZL26__gthrw_pthread_key_deletej,pthread_key_delete
	.weakref	_ZL30__gthrw_pthread_mutexattr_initP19pthread_mutexattr_t,pthread_mutexattr_init
	.weakref	_ZL33__gthrw_pthread_mutexattr_settypeP19pthread_mutexattr_ti,pthread_mutexattr_settype
	.weakref	_ZL33__gthrw_pthread_mutexattr_destroyP19pthread_mutexattr_t,pthread_mutexattr_destroy
	.ident	"GCC: (Debian 4.6.3-14+rpi1) 4.6.3"
	.section	.note.GNU-stack,"",%progbits
