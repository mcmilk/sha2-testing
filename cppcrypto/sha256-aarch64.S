/*
 * ARMv8 SHA - Based on public domain code by Jeffrey Walton
 *
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */
	.text
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4
.LCPI0_0:
	.word	1116352408
	.word	1899447441
	.word	3049323471
	.word	3921009573
.LCPI0_1:
	.word	961987163
	.word	1508970993
	.word	2453635748
	.word	2870763221
.LCPI0_2:
	.word	3624381080
	.word	310598401
	.word	607225278
	.word	1426881987
.LCPI0_3:
	.word	1925078388
	.word	2162078206
	.word	2614888103
	.word	3248222580
.LCPI0_4:
	.word	3835390401
	.word	4022224774
	.word	264347078
	.word	604807628
.LCPI0_5:
	.word	770255983
	.word	1249150122
	.word	1555081692
	.word	1996064986
.LCPI0_6:
	.word	2554220882
	.word	2821834349
	.word	2952996808
	.word	3210313671
.LCPI0_7:
	.word	3336571891
	.word	3584528711
	.word	113926993
	.word	338241895
.LCPI0_8:
	.word	666307205
	.word	773529912
	.word	1294757372
	.word	1396182291
.LCPI0_9:
	.word	1695183700
	.word	1986661051
	.word	2177026350
	.word	2456956037
.LCPI0_10:
	.word	2730485921
	.word	2820302411
	.word	3259730800
	.word	3345764771
.LCPI0_11:
	.word	3516065817
	.word	3600352804
	.word	4094571909
	.word	275423344
.LCPI0_12:
	.word	430227734
	.word	506948616
	.word	659060556
	.word	883997877
.LCPI0_13:
	.word	958139571
	.word	1322822218
	.word	1537002063
	.word	1747873779
.LCPI0_14:
	.word	1955562222
	.word	2024104815
	.word	2227730452
	.word	2361852424
.LCPI0_15:
	.word	2428436474
	.word	2756734187
	.word	3204031479
	.word	3329325298
	.text
	.globl	sha256_noloader_armv8_ce
	.p2align	2
	.type	sha256_noloader_armv8_ce,@function
sha256_noloader_armv8_ce:
	str	d10, [sp, #-32]!
	stp	d9, d8, [sp, #16]
	ldp	q0, q1, [x0]
	cbz	x2, .LBB0_3
	adrp	x8, .LCPI0_0
	ldr	q2, [x8, :lo12:.LCPI0_0]
	adrp	x8, .LCPI0_1
	ldr	q3, [x8, :lo12:.LCPI0_1]
	adrp	x8, .LCPI0_2
	ldr	q4, [x8, :lo12:.LCPI0_2]
	adrp	x8, .LCPI0_3
	ldr	q5, [x8, :lo12:.LCPI0_3]
	adrp	x8, .LCPI0_4
	ldr	q6, [x8, :lo12:.LCPI0_4]
	adrp	x8, .LCPI0_5
	ldr	q7, [x8, :lo12:.LCPI0_5]
	adrp	x8, .LCPI0_6
	ldr	q16, [x8, :lo12:.LCPI0_6]
	adrp	x8, .LCPI0_7
	ldr	q17, [x8, :lo12:.LCPI0_7]
	adrp	x8, .LCPI0_8
	ldr	q18, [x8, :lo12:.LCPI0_8]
	adrp	x8, .LCPI0_9
	ldr	q19, [x8, :lo12:.LCPI0_9]
	adrp	x8, .LCPI0_10
	ldr	q20, [x8, :lo12:.LCPI0_10]
	adrp	x8, .LCPI0_11
	ldr	q21, [x8, :lo12:.LCPI0_11]
	adrp	x8, .LCPI0_12
	ldr	q22, [x8, :lo12:.LCPI0_12]
	adrp	x8, .LCPI0_13
	ldr	q23, [x8, :lo12:.LCPI0_13]
	adrp	x8, .LCPI0_14
	ldr	q24, [x8, :lo12:.LCPI0_14]
	adrp	x8, .LCPI0_15
	ldr	q25, [x8, :lo12:.LCPI0_15]
.LBB0_2:
	ldp	q27, q28, [x1]
	ldp	q29, q30, [x1, #32]
	mov	v31.16b, v0.16b
	mov	v26.16b, v1.16b
	rev32	v27.16b, v27.16b
	add	v8.4s, v27.4s, v2.4s
	rev32	v28.16b, v28.16b
	sha256h	q31, q1, v8.4s
	add	v9.4s, v28.4s, v3.4s
	sha256h2	q26, q0, v8.4s
	mov	v8.16b, v31.16b
	rev32	v29.16b, v29.16b
	sha256h	q8, q26, v9.4s
	add	v10.4s, v29.4s, v4.4s
	sha256h2	q26, q31, v9.4s
	mov	v9.16b, v8.16b
	rev32	v30.16b, v30.16b
	sha256h	q9, q26, v10.4s
	sha256su0	v27.4s, v28.4s
	add	v31.4s, v30.4s, v5.4s
	sha256h2	q26, q8, v10.4s
	mov	v10.16b, v9.16b
	sha256su1	v27.4s, v29.4s, v30.4s
	sha256h	q10, q26, v31.4s
	sha256su0	v28.4s, v29.4s
	add	v8.4s, v27.4s, v6.4s
	sha256h2	q26, q9, v31.4s
	mov	v9.16b, v10.16b
	sha256su1	v28.4s, v30.4s, v27.4s
	sha256h	q9, q26, v8.4s
	sha256su0	v29.4s, v30.4s
	add	v31.4s, v28.4s, v7.4s
	sha256h2	q26, q10, v8.4s
	mov	v10.16b, v9.16b
	sha256su0	v30.4s, v27.4s
	sha256su1	v29.4s, v27.4s, v28.4s
	sha256h	q10, q26, v31.4s
	sha256su0	v27.4s, v28.4s
	sha256su1	v30.4s, v28.4s, v29.4s
	add	v8.4s, v29.4s, v16.4s
	sha256h2	q26, q9, v31.4s
	mov	v9.16b, v10.16b
	sha256su0	v28.4s, v29.4s
	sha256su1	v27.4s, v29.4s, v30.4s
	sha256h	q9, q26, v8.4s
	sha256su0	v29.4s, v30.4s
	add	v31.4s, v30.4s, v17.4s
	sha256su1	v28.4s, v30.4s, v27.4s
	sha256h2	q26, q10, v8.4s
	mov	v10.16b, v9.16b
	sha256su0	v30.4s, v27.4s
	sha256su1	v29.4s, v27.4s, v28.4s
	sha256h	q10, q26, v31.4s
	add	v8.4s, v27.4s, v18.4s
	sha256su0	v27.4s, v28.4s
	sha256h2	q26, q9, v31.4s
	sha256su1	v30.4s, v28.4s, v29.4s
	mov	v9.16b, v10.16b
	add	v31.4s, v28.4s, v19.4s
	sha256su0	v28.4s, v29.4s
	sha256h	q9, q26, v8.4s
	sha256su1	v27.4s, v29.4s, v30.4s
	sha256h2	q26, q10, v8.4s
	add	v8.4s, v29.4s, v20.4s
	sha256su0	v29.4s, v30.4s
	mov	v10.16b, v9.16b
	sha256su1	v28.4s, v30.4s, v27.4s
	sha256h	q10, q26, v31.4s
	sha256h2	q26, q9, v31.4s
	add	v31.4s, v30.4s, v21.4s
	sha256su0	v30.4s, v27.4s
	sha256su1	v29.4s, v27.4s, v28.4s
	sha256su1	v30.4s, v28.4s, v29.4s
	add	v9.4s, v27.4s, v22.4s
	add	v27.4s, v28.4s, v23.4s
	add	v28.4s, v29.4s, v24.4s
	add	v29.4s, v30.4s, v25.4s
	mov	v30.16b, v10.16b
	sha256h	q30, q26, v8.4s
	sha256h2	q26, q10, v8.4s
	mov	v8.16b, v30.16b
	sha256h	q8, q26, v31.4s
	sha256h2	q26, q30, v31.4s
	mov	v30.16b, v8.16b
	sha256h	q30, q26, v9.4s
	sha256h2	q26, q8, v9.4s
	mov	v31.16b, v30.16b
	sha256h	q31, q26, v27.4s
	sha256h2	q26, q30, v27.4s
	mov	v27.16b, v31.16b
	sha256h	q27, q26, v28.4s
	sha256h2	q26, q31, v28.4s
	mov	v28.16b, v27.16b
	sha256h	q28, q26, v29.4s
	sha256h2	q26, q27, v29.4s
	subs	x2, x2, #1
	add	v0.4s, v28.4s, v0.4s
	add	v1.4s, v26.4s, v1.4s
	add	x1, x1, #64
	b.ne	.LBB0_2
.LBB0_3:
	stp	q0, q1, [x0]
	ldp	d9, d8, [sp, #16]
	ldr	d10, [sp], #32
	ret
.Lfunc_end0:
	.size	sha256_noloader_armv8_ce, .Lfunc_end0-sha256_noloader_armv8_ce
	.section	".note.GNU-stack","",@progbits
