/*
 * PPC64 - Based on public domain code by Jeffrey Walton
 *
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */
	.text
	.file	"sha512-arm.c"
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4
.LCPI0_0:
	.xword	4794697086780616226
	.xword	8158064640168781261
.LCPI0_1:
	.xword	4131703408338449720
	.xword	6480981068601479193
.LCPI0_2:
	.xword	-2880145864133508542
	.xword	1334009975649890238
.LCPI0_3:
	.xword	8268148722764581231
	.xword	-9160688886553864527
.LCPI0_4:
	.xword	-1973867731355612462
	.xword	-1171420211273849373
.LCPI0_5:
	.xword	3308224258029322869
	.xword	5365058923640841347
.LCPI0_6:
	.xword	-7476448914759557205
	.xword	-6327057829258317296
.LCPI0_7:
	.xword	-4116276920077217854
	.xword	-3051310485924567259
.LCPI0_8:
	.xword	2861767655752347644
	.xword	3322285676063803686
.LCPI0_9:
	.xword	7280758554555802590
	.xword	8532644243296465576
.LCPI0_10:
	.xword	-6719396339535248540
	.xword	-6333637450476146687
.LCPI0_11:
	.xword	-3345356375505022440
	.xword	-2983346525034927856
.LCPI0_12:
	.xword	1847814050463011016
	.xword	2177327727835720531
.LCPI0_13:
	.xword	4115178125766777443
	.xword	5681478168544905931
.LCPI0_14:
	.xword	8399075790359081724
	.xword	8693463985226723168
.LCPI0_15:
	.xword	-8016688836872298968
	.xword	-6606660893046293015
	.text
	.globl	sha512_transform_armv8crypto
	.p2align	2
	.type	sha512_transform_armv8crypto,@function
sha512_transform_armv8crypto:
	str	d10, [sp, #-32]!
	stp	d9, d8, [sp, #16]
	ldr	q0, [x0]
	ldr	q1, [x0, #32]
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
	rev32	v28.16b, v28.16b
	add	v8.2d, v27.2d, v2.2d
	rev32	v29.16b, v29.16b
	add	v9.2d, v28.2d, v3.2d
	//APP
	sha512h	q31, q1, v8.2d
	//NO_APP
	//APP
	sha512h2	q26, q0, v8.2d
	//NO_APP
	mov	v8.16b, v31.16b
	add	v10.2d, v29.2d, v4.2d
	//APP
	sha512h	q8, q26, v9.2d
	//NO_APP
	//APP
	sha512h2	q26, q31, v9.2d
	//NO_APP
	mov	v9.16b, v8.16b
	rev32	v30.16b, v30.16b
	//APP
	sha512h	q9, q26, v10.2d
	//NO_APP
	//APP
	sha512h2	q26, q8, v10.2d
	//NO_APP
	mov	v10.16b, v9.16b
	//APP
	sha512su0	v27.2d, v28.2d
	//NO_APP
	add	v31.2d, v30.2d, v5.2d
	//APP
	sha512h	q10, q26, v31.2d
	//NO_APP
	//APP
	sha512h2	q26, q9, v31.2d
	//NO_APP
	mov	v9.16b, v10.16b
	//APP
	sha512su0	v28.2d, v29.2d
	//NO_APP
	//APP
	sha512su1	v27.2d, v29.2d, v30.2d
	//NO_APP
	add	v8.2d, v27.2d, v6.2d
	//APP
	sha512h	q9, q26, v8.2d
	//NO_APP
	//APP
	sha512h2	q26, q10, v8.2d
	//NO_APP
	mov	v10.16b, v9.16b
	//APP
	sha512su0	v29.2d, v30.2d
	//NO_APP
	//APP
	sha512su1	v28.2d, v30.2d, v27.2d
	//NO_APP
	//APP
	sha512su0	v30.2d, v27.2d
	//NO_APP
	add	v31.2d, v28.2d, v7.2d
	//APP
	sha512h	q10, q26, v31.2d
	//NO_APP
	//APP
	sha512h2	q26, q9, v31.2d
	//NO_APP
	mov	v9.16b, v10.16b
	//APP
	sha512su1	v29.2d, v27.2d, v28.2d
	//NO_APP
	//APP
	sha512su0	v27.2d, v28.2d
	//NO_APP
	//APP
	sha512su1	v30.2d, v28.2d, v29.2d
	//NO_APP
	//APP
	sha512su0	v28.2d, v29.2d
	//NO_APP
	add	v8.2d, v29.2d, v16.2d
	//APP
	sha512h	q9, q26, v8.2d
	//NO_APP
	//APP
	sha512h2	q26, q10, v8.2d
	//NO_APP
	mov	v10.16b, v9.16b
	//APP
	sha512su1	v27.2d, v29.2d, v30.2d
	//NO_APP
	//APP
	sha512su0	v29.2d, v30.2d
	//NO_APP
	add	v31.2d, v30.2d, v17.2d
	//APP
	sha512su1	v28.2d, v30.2d, v27.2d
	//NO_APP
	//APP
	sha512su0	v30.2d, v27.2d
	//NO_APP
	//APP
	sha512h	q10, q26, v31.2d
	//NO_APP
	//APP
	sha512h2	q26, q9, v31.2d
	//NO_APP
	mov	v9.16b, v10.16b
	add	v8.2d, v27.2d, v18.2d
	//APP
	sha512su1	v29.2d, v27.2d, v28.2d
	//NO_APP
	//APP
	sha512su0	v27.2d, v28.2d
	//NO_APP
	add	v31.2d, v28.2d, v19.2d
	//APP
	sha512su1	v30.2d, v28.2d, v29.2d
	//NO_APP
	//APP
	sha512su0	v28.2d, v29.2d
	//NO_APP
	//APP
	sha512h	q9, q26, v8.2d
	//NO_APP
	//APP
	sha512h2	q26, q10, v8.2d
	//NO_APP
	mov	v10.16b, v9.16b
	add	v8.2d, v29.2d, v20.2d
	//APP
	sha512su1	v27.2d, v29.2d, v30.2d
	//NO_APP
	//APP
	sha512su0	v29.2d, v30.2d
	//NO_APP
	//APP
	sha512h	q10, q26, v31.2d
	//NO_APP
	//APP
	sha512h2	q26, q9, v31.2d
	//NO_APP
	add	v31.2d, v30.2d, v21.2d
	//APP
	sha512su1	v28.2d, v30.2d, v27.2d
	//NO_APP
	//APP
	sha512su0	v30.2d, v27.2d
	//NO_APP
	//APP
	sha512su1	v29.2d, v27.2d, v28.2d
	//NO_APP
	//APP
	sha512su1	v30.2d, v28.2d, v29.2d
	//NO_APP
	add	v9.2d, v27.2d, v22.2d
	add	v27.2d, v28.2d, v23.2d
	add	v28.2d, v29.2d, v24.2d
	add	v29.2d, v30.2d, v25.2d
	mov	v30.16b, v10.16b
	//APP
	sha512h	q30, q26, v8.2d
	//NO_APP
	//APP
	sha512h2	q26, q10, v8.2d
	//NO_APP
	mov	v8.16b, v30.16b
	//APP
	sha512h	q8, q26, v31.2d
	//NO_APP
	//APP
	sha512h2	q26, q30, v31.2d
	//NO_APP
	mov	v30.16b, v8.16b
	//APP
	sha512h	q30, q26, v9.2d
	//NO_APP
	//APP
	sha512h2	q26, q8, v9.2d
	//NO_APP
	mov	v31.16b, v30.16b
	//APP
	sha512h	q31, q26, v27.2d
	//NO_APP
	//APP
	sha512h2	q26, q30, v27.2d
	//NO_APP
	mov	v27.16b, v31.16b
	//APP
	sha512h	q27, q26, v28.2d
	//NO_APP
	//APP
	sha512h2	q26, q31, v28.2d
	//NO_APP
	mov	v28.16b, v27.16b
	subs	x2, x2, #1
	//APP
	sha512h	q28, q26, v29.2d
	//NO_APP
	//APP
	sha512h2	q26, q27, v29.2d
	//NO_APP
	add	v0.2d, v28.2d, v0.2d
	add	v1.2d, v26.2d, v1.2d
	add	x1, x1, #128
	b.ne	.LBB0_2
.LBB0_3:
	str	q0, [x0]
	str	q1, [x0, #32]
	ldp	d9, d8, [sp, #16]
	ldr	d10, [sp], #32
	ret
.Lfunc_end0:
	.size	sha512_transform_armv8crypto, .Lfunc_end0-sha512_transform_armv8crypto
	.section	".note.GNU-stack","",@progbits
