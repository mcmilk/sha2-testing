/*
 * PPC64 - Based on public domain code by Jeffrey Walton
 *
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#if (defined(__PPC64__) && defined(__BIG_ENDIAN__))
	.machine power8
	.section	".text"
	.align 2
	.globl sha512_process_p8
	.section	".opd","aw"
	.align 3
sha512_process_p8:
	.quad	.L.sha512_process_p8,.TOC.@tocbase,0
	.previous
	.type	sha512_process_p8, @function
.L.sha512_process_p8:
.LFB30:
	.cfi_startproc
	mflr 0
	li 9,16
	addis 10,2,.LANCHOR0@toc@ha
	addi 10,10,.LANCHOR0@toc@l
	addi 8,10,16
	addi 7,10,32
	addi 6,10,48
	addi 11,10,64
	.cfi_register 65, 0
	bl _savegpr0_21
	.cfi_offset 21, -88
	.cfi_offset 22, -80
	.cfi_offset 23, -72
	.cfi_offset 24, -64
	.cfi_offset 25, -56
	.cfi_offset 26, -48
	.cfi_offset 27, -40
	.cfi_offset 28, -32
	.cfi_offset 29, -24
	.cfi_offset 30, -16
	.cfi_offset 31, -8
	.cfi_offset 65, 16
	addi 0,1,-96
	addi 31,10,96
	bl _savevr_20
	.cfi_offset 97, -288
	.cfi_offset 98, -272
	.cfi_offset 99, -256
	.cfi_offset 100, -240
	.cfi_offset 101, -224
	.cfi_offset 102, -208
	.cfi_offset 103, -192
	.cfi_offset 104, -176
	.cfi_offset 105, -160
	.cfi_offset 106, -144
	.cfi_offset 107, -128
	.cfi_offset 108, -112
	addi 30,10,112
	addi 12,10,80
	addis 22,2,.LC0@toc@ha
	rldicr 29,10,0,59
	lxvd2x 37,3,9
	li 9,32
	lxvd2x 42,0,3
	rldicr 8,8,0,59
	li 0,16
	rldicr 7,7,0,59
	lxvd2x 41,3,9
	li 9,48
	li 28,32
	rldicr 6,6,0,59
	li 27,48
	lxvd2x 38,3,9
	rldicr 11,11,0,59
	li 26,64
	rldicr 12,12,0,59
	li 25,80
	rldicr 31,31,0,59
	li 24,96
	rldicr 30,30,0,59
	li 23,112
	addi 22,22,.LC0@toc@l
.L2:
	addi 9,5,-1
	cmpwi 0,9,-1
	extsw 5,9
	bne 0,.L4
	stxvw4x 42,0,3
	li 9,16
	addi 0,1,-96
	stxvw4x 37,3,9
	li 9,32
	stxvw4x 41,3,9
	li 9,48
	stxvw4x 38,3,9
	bl _restvr_20
	b _restgpr0_21
	.cfi_remember_state
	.cfi_restore 31
	.cfi_restore 30
	.cfi_restore 29
	.cfi_restore 28
	.cfi_restore 27
	.cfi_restore 26
	.cfi_restore 25
	.cfi_restore 24
	.cfi_restore 23
	.cfi_restore 22
	.cfi_restore 21
	.cfi_restore 65
	.cfi_restore 108
	.cfi_restore 107
	.cfi_restore 106
	.cfi_restore 105
	.cfi_restore 104
	.cfi_restore 103
	.cfi_restore 102
	.cfi_restore 101
	.cfi_restore 100
	.cfi_restore 99
	.cfi_restore 98
	.cfi_restore 97
.L4:
	.cfi_restore_state
	lxvw4x 32,0,4
	lxvw4x 43,0,29
	vsldoi 4,9,9,8
	vsldoi 8,6,6,8
	li 21,4
	addi 9,10,128
	mtctr 21
	vsldoi 12,10,10,8
	vshasigmad 1,9,1,15
	lxvw4x 39,0,8
	lxvw4x 62,0,6
	xxsel 45,38,36,41
	vsldoi 16,5,5,8
	vaddudm 13,13,8
	vaddudm 8,0,11
	xxlor 35,32,32
	vsldoi 11,11,11,8
	vsldoi 0,0,0,8
	vaddudm 13,13,8
	vshasigmad 8,10,1,0
	xxlor 34,32,32
	vaddudm 0,0,11
	vaddudm 13,13,1
	xxlxor 33,42,44
	xxsel 33,44,37,33
	vaddudm 16,13,16
	vaddudm 1,1,8
	xxsel 40,36,41,48
	vaddudm 1,1,13
	vshasigmad 13,16,1,15
	xxlxor 43,42,33
	vaddudm 13,6,13
	xxsel 43,42,44,43
	vaddudm 0,0,13
	vshasigmad 13,1,1,0
	vaddudm 0,0,8
	vaddudm 11,11,13
	vaddudm 31,5,0
	vaddudm 11,11,0
	lxvw4x 32,4,0
	xxsel 40,41,48,63
	vshasigmad 13,31,1,15
	vaddudm 8,8,4
	vaddudm 4,0,7
	xxlor 50,32,32
	vsldoi 7,7,7,8
	vsldoi 0,0,0,8
	vaddudm 8,8,4
	vshasigmad 4,11,1,0
	xxlor 49,32,32
	vaddudm 0,0,7
	vaddudm 8,8,13
	xxlxor 45,43,33
	xxsel 45,33,42,45
	vaddudm 12,8,12
	vaddudm 13,13,4
	xxsel 36,48,63,44
	vaddudm 13,13,8
	vshasigmad 8,12,1,15
	vaddudm 8,9,8
	vshasigmad 7,13,1,0
	vaddudm 0,0,8
	xxlxor 40,45,43
	xxsel 40,43,33,40
	vaddudm 0,0,4
	lxvw4x 36,0,7
	vaddudm 8,8,7
	vaddudm 15,10,0
	vaddudm 0,8,0
	lxvw4x 40,4,28
	xxsel 39,63,44,47
	vshasigmad 14,15,1,15
	xxlxor 60,32,45
	vaddudm 7,7,14
	xxsel 60,45,43,60
	vaddudm 14,8,4
	xxlor 51,40,40
	vsldoi 8,8,8,8
	vaddudm 7,7,14
	vaddudm 7,7,16
	vshasigmad 16,0,1,0
	vaddudm 14,7,1
	vaddudm 28,28,16
	vsldoi 16,4,4,8
	xxlor 36,40,40
	vaddudm 28,28,7
	vshasigmad 1,14,1,15
	xxsel 39,44,47,46
	vaddudm 8,8,16
	vaddudm 7,7,1
	xxlxor 33,60,32
	vaddudm 8,7,8
	xxsel 33,32,45,33
	vshasigmad 7,28,1,0
	vaddudm 8,8,31
	vaddudm 1,1,7
	vaddudm 11,8,11
	vaddudm 1,1,8
	lxvw4x 40,4,27
	xxsel 48,47,46,43
	vshasigmad 31,11,1,15
	xxlxor 58,33,60
	vaddudm 16,16,31
	xxsel 58,60,32,58
	vaddudm 31,8,30
	xxlor 39,40,40
	vsldoi 8,8,8,8
	vaddudm 16,16,31
	vaddudm 12,16,12
	vshasigmad 16,1,1,0
	vaddudm 31,12,13
	vaddudm 26,26,16
	vsldoi 13,30,30,8
	xxlor 48,40,40
	vaddudm 26,26,12
	vshasigmad 30,31,1,15
	xxsel 44,46,43,63
	vaddudm 8,8,13
	xxlxor 53,58,33
	vshasigmad 13,26,1,0
	vaddudm 12,12,30
	xxsel 53,33,60,53
	vaddudm 12,12,8
	vaddudm 21,21,13
	vaddudm 12,12,15
	vaddudm 30,12,0
	vaddudm 21,21,12
	lxvw4x 32,0,11
	lxvw4x 44,4,26
	xxsel 47,43,63,62
	vshasigmad 13,30,1,15
	vaddudm 15,15,13
	vaddudm 13,12,0
	xxlor 40,44,44
	vsldoi 0,0,0,8
	vsldoi 12,12,12,8
	vaddudm 15,15,13
	xxlxor 45,53,58
	vaddudm 15,15,14
	xxsel 45,58,33,45
	vshasigmad 14,21,1,0
	vaddudm 28,15,28
	vaddudm 13,13,14
	vshasigmad 29,28,1,15
	xxsel 46,63,62,60
	vaddudm 13,13,15
	xxlor 47,44,44
	vaddudm 14,14,29
	vaddudm 12,12,0
	lxvw4x 61,0,12
	xxlxor 32,45,53
	vaddudm 12,14,12
	xxsel 32,53,58,32
	vaddudm 12,12,11
	vshasigmad 11,13,1,0
	vaddudm 0,0,11
	vaddudm 1,12,1
	vaddudm 0,0,12
	lxvw4x 44,4,25
	xxsel 43,62,60,33
	vshasigmad 27,1,1,15
	xxlxor 56,32,45
	vaddudm 11,11,27
	xxsel 56,45,53,56
	vaddudm 27,12,29
	xxlor 46,44,44
	vsldoi 29,29,29,8
	vsldoi 12,12,12,8
	vaddudm 11,11,27
	vaddudm 11,11,31
	vshasigmad 31,0,1,0
	vaddudm 26,11,26
	vaddudm 24,24,31
	xxlor 63,44,44
	vaddudm 12,12,29
	vaddudm 24,24,11
	vshasigmad 27,26,1,15
	xxsel 43,60,33,58
	xxlxor 54,56,32
	vaddudm 11,11,27
	lxvw4x 59,0,31
	xxsel 54,32,45,54
	vaddudm 12,11,12
	vshasigmad 11,24,1,0
	vaddudm 12,12,30
	vaddudm 22,22,11
	lxvw4x 43,4,24
	vaddudm 21,12,21
	vaddudm 22,22,12
	xxsel 61,33,58,53
	vshasigmad 12,21,1,15
	xxlor 62,43,43
	vaddudm 29,29,12
	vaddudm 12,11,27
	vsldoi 27,27,27,8
	vsldoi 11,11,11,8
	vaddudm 29,29,12
	xxlxor 44,54,56
	vaddudm 29,29,28
	xxsel 44,56,32,44
	vshasigmad 28,22,1,0
	vaddudm 13,29,13
	vaddudm 12,12,28
	vshasigmad 25,13,1,15
	xxsel 60,58,53,45
	vaddudm 12,12,29
	xxlor 61,43,43
	vaddudm 28,28,25
	vaddudm 11,11,27
	vaddudm 11,28,11
	vshasigmad 28,12,1,0
	vaddudm 11,11,1
	xxlxor 33,44,54
	xxsel 33,54,56,33
	vaddudm 0,11,0
	vaddudm 1,1,28
	vshasigmad 25,0,1,15
	xxsel 59,53,45,32
	vaddudm 23,1,11
	lxvw4x 43,4,23
	lxvw4x 33,0,30
	addi 4,4,128
	vaddudm 27,27,25
	vaddudm 25,11,1
	xxlor 60,43,43
	vsldoi 1,1,1,8
	vsldoi 11,11,11,8
	vaddudm 27,27,25
	xxlxor 57,55,44
	vaddudm 27,27,26
	xxsel 57,44,54,57
	vshasigmad 26,23,1,0
	vaddudm 24,27,24
	vaddudm 25,25,26
	vshasigmad 20,24,1,15
	xxsel 58,45,32,56
	vaddudm 25,25,27
	xxlor 59,43,43
	vaddudm 26,26,20
	vaddudm 11,11,1
	vshasigmad 1,25,1,0
	vaddudm 11,26,11
	xxlxor 58,57,55
	xxsel 58,55,44,58
	vaddudm 11,11,21
	vaddudm 1,26,1
	vaddudm 20,11,22
	vaddudm 1,1,11
.L3:
	vshasigmad 26,28,0,15
	vshasigmad 11,2,0,0
	lvx 22,0,9
	addi 21,9,16
	vshasigmad 21,20,1,15
	vaddudm 2,14,2
	vaddudm 11,15,11
	vaddudm 3,3,26
	xxsel 58,32,56,52
	vaddudm 3,3,11
	vaddudm 26,26,21
	vaddudm 11,3,22
	vaddudm 11,11,26
	xxlxor 58,33,57
	vaddudm 13,11,13
	xxsel 58,57,55,58
	vshasigmad 11,1,1,0
	vaddudm 12,13,12
	vaddudm 26,26,11
	vsldoi 11,22,22,8
	vshasigmad 22,27,0,15
	vaddudm 26,26,13
	vshasigmad 13,18,0,0
	vaddudm 18,31,18
	vaddudm 13,13,22
	vshasigmad 22,12,1,15
	vaddudm 2,13,2
	xxsel 45,56,52,44
	vaddudm 0,22,0
	vaddudm 13,13,11
	vshasigmad 11,26,1,0
	vaddudm 0,13,0
	xxlxor 45,58,33
	xxsel 45,33,57,45
	vaddudm 0,0,2
	vaddudm 13,13,11
	vaddudm 23,0,23
	vshasigmad 11,3,0,15
	vaddudm 21,13,0
	vshasigmad 0,17,0,0
	lvx 13,0,21
	addi 21,9,32
	vaddudm 17,17,30
	xxlor 0,55,55
	vaddudm 0,0,11
	vshasigmad 11,23,1,15
	vaddudm 18,0,18
	xxsel 32,52,44,55
	vaddudm 11,11,24
	vshasigmad 24,21,1,0
	vaddudm 0,0,18
	vaddudm 0,0,11
	xxlxor 43,53,58
	xxsel 43,58,33,43
	vaddudm 0,0,13
	vsldoi 13,13,13,8
	vaddudm 11,11,24
	vaddudm 25,0,25
	vshasigmad 24,2,0,15
	vaddudm 11,11,0
	vshasigmad 0,19,0,0
	vaddudm 19,19,29
	vaddudm 0,0,24
	vshasigmad 24,25,1,15
	vaddudm 17,0,17
	xxsel 32,44,55,57
	vaddudm 24,24,20
	vaddudm 0,0,13
	xxlxor 45,43,53
	vaddudm 0,0,24
	xxsel 45,53,58,45
	vshasigmad 24,11,1,0
	vaddudm 0,0,17
	vaddudm 13,13,24
	vshasigmad 24,18,0,15
	vaddudm 1,0,1
	vaddudm 22,13,0
	vshasigmad 0,4,0,0
	lvx 13,0,21
	addi 21,9,48
	vshasigmad 23,1,1,15
	vaddudm 4,4,28
	vaddudm 0,0,24
	xxsel 56,0,57,33
	vaddudm 19,0,19
	vaddudm 24,24,23
	vaddudm 0,19,13
	vsldoi 13,13,13,8
	vaddudm 0,0,24
	vshasigmad 24,22,1,0
	vaddudm 12,0,12
	xxlxor 32,54,43
	xxsel 32,43,53,32
	vaddudm 23,12,26
	vaddudm 0,0,24
	vaddudm 26,0,12
	vshasigmad 0,7,0,0
	vshasigmad 12,17,0,15
	vaddudm 7,7,27
	vaddudm 0,0,12
	xxsel 44,57,33,55
	vaddudm 4,0,4
	vshasigmad 0,23,1,15
	vaddudm 13,12,13
	vshasigmad 12,26,1,0
	vaddudm 0,4,0
	vaddudm 0,0,13
	xxlor 45,0,0
	vaddudm 0,0,13
	xxlxor 45,58,54
	xxsel 45,54,43,45
	vaddudm 21,0,21
	vaddudm 13,13,12
	vshasigmad 12,19,0,15
	vshasigmad 20,21,1,15
	vaddudm 24,13,0
	vshasigmad 0,16,0,0
	lvx 13,0,21
	addi 21,9,64
	vaddudm 0,0,12
	xxsel 44,33,55,53
	vaddudm 7,0,7
	vaddudm 12,12,20
	vaddudm 0,7,13
	vsldoi 13,13,13,8
	vaddudm 0,0,12
	xxlxor 44,56,58
	vaddudm 0,0,25
	xxsel 44,58,54,44
	vshasigmad 25,24,1,0
	vaddudm 11,0,11
	vaddudm 12,12,25
	vaddudm 20,12,0
	vshasigmad 0,8,0,0
	vshasigmad 12,4,0,15
	vaddudm 16,16,0
	vshasigmad 0,11,1,15
	vaddudm 12,12,3
	vaddudm 16,12,16
	xxsel 44,55,53,43
	vaddudm 0,16,0
	vaddudm 13,12,13
	vaddudm 0,0,13
	vshasigmad 13,20,1,0
	vaddudm 1,0,1
	xxlxor 32,52,56
	xxsel 32,56,58,32
	vaddudm 22,1,22
	vaddudm 0,0,13
	vshasigmad 13,7,0,15
	vshasigmad 12,22,1,15
	vaddudm 25,0,1
	vshasigmad 0,15,0,0
	lvx 1,0,21
	addi 21,9,80
	vaddudm 13,13,2
	vaddudm 8,8,0
	vaddudm 8,13,8
	xxsel 45,53,43,54
	vaddudm 0,8,1
	vaddudm 13,13,12
	vshasigmad 12,25,1,0
	vaddudm 0,0,13
	xxlxor 45,57,52
	xxsel 45,52,56,45
	vaddudm 0,0,23
	vaddudm 13,13,12
	vaddudm 26,0,26
	vshasigmad 12,16,0,15
	vaddudm 13,13,0
	vsldoi 0,1,1,8
	vshasigmad 1,14,0,0
	vaddudm 12,12,18
	xxlor 0,58,58
	vaddudm 15,15,1
	xxsel 33,43,54,58
	vaddudm 15,12,15
	vshasigmad 12,26,1,15
	vaddudm 1,1,0
	xxlxor 32,45,57
	vaddudm 12,15,12
	vshasigmad 26,31,0,0
	xxsel 32,57,52,32
	vaddudm 1,1,12
	vshasigmad 12,13,1,0
	vaddudm 14,14,26
	vaddudm 1,1,21
	vaddudm 0,0,12
	lvx 12,0,21
	addi 21,9,96
	vaddudm 23,1,24
	vaddudm 0,0,1
	vshasigmad 1,8,0,15
	vshasigmad 26,23,1,15
	xxlxor 56,32,45
	vaddudm 1,1,17
	xxsel 56,45,57,56
	vaddudm 14,14,1
	xxsel 33,54,0,55
	vaddudm 1,1,26
	vaddudm 26,14,12
	vaddudm 1,1,26
	lvx 26,0,21
	addi 21,9,112
	addi 9,9,128
	vaddudm 1,1,11
	vshasigmad 11,0,1,0
	vaddudm 24,24,11
	vaddudm 20,1,20
	vshasigmad 11,30,0,0
	vaddudm 24,24,1
	vsldoi 1,12,12,8
	vshasigmad 12,15,0,15
	vaddudm 31,31,11
	vshasigmad 11,20,1,15
	vaddudm 12,12,19
	vaddudm 31,31,12
	xxsel 44,0,55,52
	vaddudm 11,31,11
	vaddudm 12,12,1
	xxlxor 33,56,32
	vaddudm 12,12,11
	vshasigmad 11,24,1,0
	xxsel 33,32,45,33
	vaddudm 22,12,22
	vshasigmad 12,29,0,0
	vaddudm 1,1,11
	vaddudm 21,22,25
	vaddudm 30,12,30
	vaddudm 22,1,22
	vshasigmad 1,14,0,15
	xxsel 43,55,52,53
	vaddudm 1,1,4
	xxlxor 44,54,56
	vaddudm 30,30,1
	vshasigmad 1,21,1,15
	xxsel 44,56,32,44
	vaddudm 11,11,1
	vaddudm 1,30,26
	vsldoi 26,26,26,8
	vaddudm 11,11,1
	xxlor 33,0,0
	vaddudm 11,11,1
	vshasigmad 1,22,1,0
	vaddudm 12,12,1
	vaddudm 13,11,13
	vshasigmad 1,31,0,15
	vaddudm 12,12,11
	vshasigmad 11,28,0,0
	vaddudm 1,1,7
	vaddudm 29,11,29
	xxsel 43,52,53,45
	vaddudm 29,29,1
	vshasigmad 1,13,1,15
	vaddudm 11,11,26
	vshasigmad 26,12,1,0
	vaddudm 1,29,1
	vaddudm 11,11,1
	xxlxor 33,44,54
	xxsel 33,54,56,33
	vaddudm 23,11,23
	vshasigmad 11,27,0,0
	vaddudm 1,1,26
	vaddudm 0,23,0
	lvx 26,0,21
	vaddudm 28,11,28
	vaddudm 23,1,23
	vshasigmad 1,30,0,15
	xxsel 43,53,45,32
	vaddudm 1,1,16
	xxlxor 57,55,44
	vaddudm 28,28,1
	vshasigmad 1,0,1,15
	xxsel 57,44,54,57
	vaddudm 11,11,1
	vaddudm 1,28,26
	vsldoi 26,26,26,8
	vaddudm 11,11,1
	vshasigmad 1,23,1,0
	vaddudm 11,11,20
	vaddudm 25,25,1
	vshasigmad 1,29,0,15
	vaddudm 24,11,24
	vaddudm 25,25,11
	vshasigmad 11,3,0,0
	vaddudm 1,1,8
	vaddudm 27,11,27
	xxsel 43,45,32,56
	vaddudm 27,27,1
	vshasigmad 1,24,1,15
	vaddudm 11,11,26
	xxlxor 58,57,55
	vaddudm 1,27,1
	xxsel 58,55,44,58
	vaddudm 11,11,1
	vshasigmad 1,25,1,0
	vaddudm 11,11,21
	vaddudm 1,26,1
	vaddudm 20,11,22
	vaddudm 1,1,11
	bdnz .L3
	lxvw4x 43,0,22
	vperm 1,1,25,11
	vperm 12,23,12,11
	vperm 24,20,24,11
	vperm 0,0,13,11
	vaddudm 10,10,1
	vaddudm 5,5,12
	vaddudm 9,9,24
	vaddudm 6,6,0
	b .L2
	.long 0
	.byte 0,9,0,1,0,11,0,0
	.cfi_endproc
.LFE30:
	.size	sha512_process_p8,.-.L.sha512_process_p8
	.section	.rodata.cst16,"aM",@progbits,16
	.align 4
.LC0:
	.byte	0
	.byte	1
	.byte	2
	.byte	3
	.byte	4
	.byte	5
	.byte	6
	.byte	7
	.byte	16
	.byte	17
	.byte	18
	.byte	19
	.byte	20
	.byte	21
	.byte	22
	.byte	23
	.section	.rodata
	.align 4
	.set	.LANCHOR0,. + 0
	.type	_ZL6KEY512, @object
	.size	_ZL6KEY512, 640
_ZL6KEY512:
	.quad	4794697086780616226
	.quad	8158064640168781261
	.quad	-5349999486874862801
	.quad	-1606136188198331460
	.quad	4131703408338449720
	.quad	6480981068601479193
	.quad	-7908458776815382629
	.quad	-6116909921290321640
	.quad	-2880145864133508542
	.quad	1334009975649890238
	.quad	2608012711638119052
	.quad	6128411473006802146
	.quad	8268148722764581231
	.quad	-9160688886553864527
	.quad	-7215885187991268811
	.quad	-4495734319001033068
	.quad	-1973867731355612462
	.quad	-1171420211273849373
	.quad	1135362057144423861
	.quad	2597628984639134821
	.quad	3308224258029322869
	.quad	5365058923640841347
	.quad	6679025012923562964
	.quad	8573033837759648693
	.quad	-7476448914759557205
	.quad	-6327057829258317296
	.quad	-5763719355590565569
	.quad	-4658551843659510044
	.quad	-4116276920077217854
	.quad	-3051310485924567259
	.quad	489312712824947311
	.quad	1452737877330783856
	.quad	2861767655752347644
	.quad	3322285676063803686
	.quad	5560940570517711597
	.quad	5996557281743188959
	.quad	7280758554555802590
	.quad	8532644243296465576
	.quad	-9096487096722542874
	.quad	-7894198246740708037
	.quad	-6719396339535248540
	.quad	-6333637450476146687
	.quad	-4446306890439682159
	.quad	-4076793802049405392
	.quad	-3345356375505022440
	.quad	-2983346525034927856
	.quad	-860691631967231958
	.quad	1182934255886127544
	.quad	1847814050463011016
	.quad	2177327727835720531
	.quad	2830643537854262169
	.quad	3796741975233480872
	.quad	4115178125766777443
	.quad	5681478168544905931
	.quad	6601373596472566643
	.quad	7507060721942968483
	.quad	8399075790359081724
	.quad	8693463985226723168
	.quad	-8878714635349349518
	.quad	-8302665154208450068
	.quad	-8016688836872298968
	.quad	-6606660893046293015
	.quad	-4685533653050689259
	.quad	-4147400797238176981
	.quad	-3880063495543823972
	.quad	-3348786107499101689
	.quad	-1523767162380948706
	.quad	-757361751448694408
	.quad	500013540394364858
	.quad	748580250866718886
	.quad	1242879168328830382
	.quad	1977374033974150939
	.quad	2944078676154940804
	.quad	3659926193048069267
	.quad	4368137639120453308
	.quad	4836135668995329356
	.quad	5532061633213252278
	.quad	6448918945643986474
	.quad	6902733635092675308
	.quad	7801388544844847127
#endif
