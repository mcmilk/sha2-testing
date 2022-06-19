
/*
 * ARMv8 SHA256 - Based on public domain code by Jeffrey Walton
 *
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#if defined(__aarch64__)
	.arch armv8-a+crypto
	.text
	.align	2
	.p2align 4,,11
	.global	sha256_transform_armv8crypto
	.type	sha256_transform_armv8crypto, %function
sha256_transform_armv8crypto:
.LFB4340:
	.cfi_startproc
	ldp	q2, q1, [x0]
	cbz	x2, .L9
	adrp	x4, .LANCHOR0
	add	x3, x4, :lo12:.LANCHOR0
	stp	d8, d9, [sp, -32]!
	.cfi_def_cfa_offset 32
	.cfi_offset 72, -32
	.cfi_offset 73, -24
	ldr	q26, [x4, #:lo12:.LANCHOR0]
	str	d10, [sp, 16]
	.cfi_offset 74, -16
	ldp	q25, q24, [x3, 16]
	ldp	q23, q22, [x3, 48]
	ldp	q21, q20, [x3, 80]
	ldp	q19, q18, [x3, 112]
	ldp	q17, q16, [x3, 144]
	ldp	q7, q6, [x3, 176]
	ldp	q5, q4, [x3, 208]
	ldr	q3, [x3, 240]
	.p2align 3,,7
.L3:
	subs	x2, x2, #1
	ldp	q30, q29, [x1]
	mov	v8.16b, v2.16b
	mov	v0.16b, v1.16b
	rev32	v30.16b, v30.16b
	rev32	v29.16b, v29.16b
	ldp	q28, q27, [x1, 32]
	add	x1, x1, 64
	add	v9.4s, v26.4s, v30.4s
	add	v31.4s, v25.4s, v29.4s
	rev32	v28.16b, v28.16b
	rev32	v27.16b, v27.16b
	sha256h	q8, q1, v9.4s
	sha256h2	q0, q2, v9.4s
	add	v9.4s, v24.4s, v28.4s
	sha256su0	v30.4s, v29.4s
	sha256su0	v29.4s, v28.4s
	mov	v10.16b, v8.16b
	sha256su1	v30.4s, v28.4s, v27.4s
	sha256su0	v28.4s, v27.4s
	sha256h	q10, q0, v31.4s
	sha256h2	q0, q8, v31.4s
	add	v8.4s, v23.4s, v27.4s
	sha256su1	v29.4s, v27.4s, v30.4s
	sha256su0	v27.4s, v30.4s
	mov	v31.16b, v10.16b
	sha256su1	v28.4s, v30.4s, v29.4s
	sha256h	q31, q0, v9.4s
	sha256h2	q0, q10, v9.4s
	add	v10.4s, v30.4s, v22.4s
	sha256su0	v30.4s, v29.4s
	sha256su1	v27.4s, v29.4s, v28.4s
	mov	v9.16b, v31.16b
	sha256h	q9, q0, v8.4s
	sha256h2	q0, q31, v8.4s
	add	v31.4s, v29.4s, v21.4s
	sha256su1	v30.4s, v28.4s, v27.4s
	sha256su0	v29.4s, v28.4s
	mov	v8.16b, v9.16b
	sha256su1	v29.4s, v27.4s, v30.4s
	sha256h	q8, q0, v10.4s
	sha256h2	q0, q9, v10.4s
	add	v10.4s, v28.4s, v20.4s
	sha256su0	v28.4s, v27.4s
	mov	v9.16b, v8.16b
	sha256su1	v28.4s, v30.4s, v29.4s
	sha256h	q9, q0, v31.4s
	sha256h2	q0, q8, v31.4s
	add	v31.4s, v27.4s, v19.4s
	sha256su0	v27.4s, v30.4s
	mov	v8.16b, v9.16b
	sha256su1	v27.4s, v29.4s, v28.4s
	sha256h	q8, q0, v10.4s
	sha256h2	q0, q9, v10.4s
	add	v10.4s, v30.4s, v18.4s
	sha256su0	v30.4s, v29.4s
	mov	v9.16b, v8.16b
	sha256su1	v30.4s, v28.4s, v27.4s
	sha256h	q9, q0, v31.4s
	sha256h2	q0, q8, v31.4s
	add	v31.4s, v29.4s, v17.4s
	sha256su0	v29.4s, v28.4s
	mov	v8.16b, v9.16b
	sha256su1	v29.4s, v27.4s, v30.4s
	sha256h	q8, q0, v10.4s
	sha256h2	q0, q9, v10.4s
	add	v10.4s, v28.4s, v16.4s
	sha256su0	v28.4s, v27.4s
	mov	v9.16b, v8.16b
	sha256su1	v28.4s, v30.4s, v29.4s
	sha256h	q9, q0, v31.4s
	sha256h2	q0, q8, v31.4s
	add	v31.4s, v27.4s, v7.4s
	sha256su0	v27.4s, v30.4s
	mov	v8.16b, v9.16b
	sha256su1	v27.4s, v29.4s, v28.4s
	add	v28.4s, v28.4s, v4.4s
	sha256h	q8, q0, v10.4s
	sha256h2	q0, q9, v10.4s
	add	v10.4s, v30.4s, v6.4s
	add	v27.4s, v27.4s, v3.4s
	mov	v9.16b, v8.16b
	sha256h	q9, q0, v31.4s
	sha256h2	q0, q8, v31.4s
	add	v8.4s, v29.4s, v5.4s
	mov	v31.16b, v9.16b
	sha256h	q31, q0, v10.4s
	sha256h2	q0, q9, v10.4s
	mov	v30.16b, v31.16b
	sha256h	q30, q0, v8.4s
	sha256h2	q0, q31, v8.4s
	mov	v29.16b, v30.16b
	sha256h	q29, q0, v28.4s
	sha256h2	q0, q30, v28.4s
	mov	v8.16b, v29.16b
	sha256h	q8, q0, v27.4s
	sha256h2	q0, q29, v27.4s
	add	v2.4s, v2.4s, v8.4s
	add	v1.4s, v1.4s, v0.4s
	bne	.L3
	stp	q2, q1, [x0]
	ldr	d10, [sp, 16]
	ldp	d8, d9, [sp], 32
	.cfi_restore 73
	.cfi_restore 72
	.cfi_restore 74
	.cfi_def_cfa_offset 0
	ret
	.p2align 2,,3
.L9:
	stp	q2, q1, [x0]
	ret
	.cfi_endproc
.LFE4340:
	.size	sha256_transform_armv8crypto, .-sha256_transform_armv8crypto
	.section	.rodata
	.align	4
	.set	.LANCHOR0,. + 0
	.type	K, %object
	.size	K, 256
K:
	.word	1116352408
	.word	1899447441
	.word	-1245643825
	.word	-373957723
	.word	961987163
	.word	1508970993
	.word	-1841331548
	.word	-1424204075
	.word	-670586216
	.word	310598401
	.word	607225278
	.word	1426881987
	.word	1925078388
	.word	-2132889090
	.word	-1680079193
	.word	-1046744716
	.word	-459576895
	.word	-272742522
	.word	264347078
	.word	604807628
	.word	770255983
	.word	1249150122
	.word	1555081692
	.word	1996064986
	.word	-1740746414
	.word	-1473132947
	.word	-1341970488
	.word	-1084653625
	.word	-958395405
	.word	-710438585
	.word	113926993
	.word	338241895
	.word	666307205
	.word	773529912
	.word	1294757372
	.word	1396182291
	.word	1695183700
	.word	1986661051
	.word	-2117940946
	.word	-1838011259
	.word	-1564481375
	.word	-1474664885
	.word	-1035236496
	.word	-949202525
	.word	-778901479
	.word	-694614492
	.word	-200395387
	.word	275423344
	.word	430227734
	.word	506948616
	.word	659060556
	.word	883997877
	.word	958139571
	.word	1322822218
	.word	1537002063
	.word	1747873779
	.word	1955562222
	.word	2024104815
	.word	-2067236844
	.word	-1933114872
	.word	-1866530822
	.word	-1538233109
	.word	-1090935817
	.word	-965641998
	.section	.note.GNU-stack,"",@progbits
#endif
