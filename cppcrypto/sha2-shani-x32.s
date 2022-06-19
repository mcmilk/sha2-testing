
/*
 * Intel SHANI - Based on public domain code by Jeffrey Walton
 *
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#if defined(__i386)
	.text
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4
.LCPI0_0:
	.byte	3
	.byte	2
	.byte	1
	.byte	0
	.byte	7
	.byte	6
	.byte	5
	.byte	4
	.byte	11
	.byte	10
	.byte	9
	.byte	8
	.byte	15
	.byte	14
	.byte	13
	.byte	12
.LCPI0_1:
	.long	1116352408
	.long	1899447441
	.long	3049323471
	.long	3921009573
.LCPI0_2:
	.long	961987163
	.long	1508970993
	.long	2453635748
	.long	2870763221
.LCPI0_3:
	.long	3624381080
	.long	310598401
	.long	607225278
	.long	1426881987
.LCPI0_4:
	.long	1925078388
	.long	2162078206
	.long	2614888103
	.long	3248222580
.LCPI0_5:
	.long	3835390401
	.long	4022224774
	.long	264347078
	.long	604807628
.LCPI0_6:
	.long	770255983
	.long	1249150122
	.long	1555081692
	.long	1996064986
.LCPI0_7:
	.long	2554220882
	.long	2821834349
	.long	2952996808
	.long	3210313671
.LCPI0_8:
	.long	3336571891
	.long	3584528711
	.long	113926993
	.long	338241895
.LCPI0_9:
	.long	666307205
	.long	773529912
	.long	1294757372
	.long	1396182291
.LCPI0_10:
	.long	1695183700
	.long	1986661051
	.long	2177026350
	.long	2456956037
.LCPI0_11:
	.long	2730485921
	.long	2820302411
	.long	3259730800
	.long	3345764771
.LCPI0_12:
	.long	3516065817
	.long	3600352804
	.long	4094571909
	.long	275423344
.LCPI0_13:
	.long	430227734
	.long	506948616
	.long	659060556
	.long	883997877
.LCPI0_14:
	.long	958139571
	.long	1322822218
	.long	1537002063
	.long	1747873779
.LCPI0_15:
	.long	1955562222
	.long	2024104815
	.long	2227730452
	.long	2361852424
.LCPI0_16:
	.long	2428436474
	.long	2756734187
	.long	3204031479
	.long	3329325298
	.text
	.globl	sha256_transform_shani
	.type	sha256_transform_shani,@function
sha256_transform_shani:
	subl	$60, %esp
	movl	72(%esp), %ecx
	movl	64(%esp), %eax
	movdqu	(%eax), %xmm0
	movdqu	16(%eax), %xmm1
	pshufd	$177, %xmm0, %xmm0
	pshufd	$27, %xmm1, %xmm2
	movdqa	%xmm0, %xmm3
	palignr	$8, %xmm2, %xmm3
	pblendw	$240, %xmm0, %xmm2
	testl	%ecx, %ecx
	jle	.LBB0_3
	movl	68(%esp), %edx
	incl	%ecx
.LBB0_2:
	movdqa	%xmm2, 32(%esp)
	movdqa	%xmm3, %xmm6
	movdqa	%xmm3, 16(%esp)
	movdqu	(%edx), %xmm5
	movdqu	16(%edx), %xmm4
	movdqa	.LCPI0_0, %xmm1
	pshufb	%xmm1, %xmm5
	movdqa	%xmm5, %xmm0
	paddd	.LCPI0_1, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	pshufb	%xmm1, %xmm4
	movdqa	%xmm4, %xmm0
	paddd	.LCPI0_2, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm4, %xmm5
	movdqu	32(%edx), %xmm6
	pshufb	%xmm1, %xmm6
	movdqa	%xmm6, %xmm0
	paddd	.LCPI0_3, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm6, %xmm4
	movdqu	48(%edx), %xmm7
	pshufb	%xmm1, %xmm7
	movdqa	%xmm7, %xmm0
	paddd	.LCPI0_4, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm7, %xmm1
	palignr	$4, %xmm6, %xmm1
	paddd	%xmm5, %xmm1
	sha256msg2	%xmm7, %xmm1
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm7, %xmm6
	movdqa	%xmm1, %xmm0
	paddd	.LCPI0_5, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm1, %xmm5
	palignr	$4, %xmm7, %xmm5
	paddd	%xmm4, %xmm5
	sha256msg2	%xmm1, %xmm5
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm1, %xmm7
	movdqa	%xmm5, %xmm0
	paddd	.LCPI0_6, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm5, %xmm4
	palignr	$4, %xmm1, %xmm4
	paddd	%xmm6, %xmm4
	sha256msg2	%xmm5, %xmm4
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm5, %xmm1
	movdqa	%xmm4, %xmm0
	paddd	.LCPI0_7, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm4, %xmm6
	palignr	$4, %xmm5, %xmm6
	paddd	%xmm7, %xmm6
	sha256msg2	%xmm4, %xmm6
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm4, %xmm5
	movdqa	%xmm6, %xmm0
	paddd	.LCPI0_8, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm6, %xmm7
	palignr	$4, %xmm4, %xmm7
	paddd	%xmm1, %xmm7
	sha256msg2	%xmm6, %xmm7
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm6, %xmm4
	movdqa	%xmm7, %xmm0
	paddd	.LCPI0_9, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm7, %xmm1
	palignr	$4, %xmm6, %xmm1
	paddd	%xmm5, %xmm1
	sha256msg2	%xmm7, %xmm1
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm7, %xmm6
	movdqa	%xmm1, %xmm0
	paddd	.LCPI0_10, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm1, %xmm5
	palignr	$4, %xmm7, %xmm5
	paddd	%xmm4, %xmm5
	sha256msg2	%xmm1, %xmm5
	movdqa	%xmm5, %xmm4
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm1, %xmm7
	movdqa	%xmm5, %xmm0
	paddd	.LCPI0_11, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	palignr	$4, %xmm1, %xmm5
	paddd	%xmm6, %xmm5
	movdqa	%xmm4, %xmm6
	sha256msg2	%xmm4, %xmm5
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm4, %xmm1
	movdqa	%xmm5, %xmm0
	paddd	.LCPI0_12, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	movdqa	%xmm5, %xmm4
	palignr	$4, %xmm6, %xmm4
	paddd	%xmm7, %xmm4
	sha256msg2	%xmm5, %xmm4
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	sha256msg1	%xmm5, %xmm6
	movaps	%xmm6, (%esp)
	movdqa	%xmm4, %xmm6
	palignr	$4, %xmm5, %xmm6
	paddd	%xmm1, %xmm6
	sha256msg2	%xmm4, %xmm6
	sha256msg1	%xmm4, %xmm5
	movdqa	%xmm6, %xmm7
	palignr	$4, %xmm4, %xmm7
	movdqa	%xmm4, %xmm0
	paddd	.LCPI0_13, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	paddd	(%esp), %xmm7
	sha256msg2	%xmm6, %xmm7
	movdqa	%xmm7, %xmm1
	palignr	$4, %xmm6, %xmm1
	movdqa	%xmm6, %xmm0
	paddd	.LCPI0_14, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	paddd	%xmm5, %xmm1
	sha256msg2	%xmm7, %xmm1
	movdqa	%xmm7, %xmm0
	paddd	.LCPI0_15, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	paddd	.LCPI0_16, %xmm1
	pshufd	$14, %xmm0, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	movdqa	%xmm1, %xmm0
	sha256rnds2	%xmm0, %xmm3, %xmm2
	pshufd	$14, %xmm1, %xmm0
	sha256rnds2	%xmm0, %xmm2, %xmm3
	paddd	16(%esp), %xmm3
	paddd	32(%esp), %xmm2
	decl	%ecx
	addl	$64, %edx
	cmpl	$1, %ecx
	jg	.LBB0_2
.LBB0_3:
	pshufd	$27, %xmm3, %xmm0
	pshufd	$177, %xmm2, %xmm1
	movdqa	%xmm0, %xmm2
	pblendw	$240, %xmm1, %xmm2
	palignr	$8, %xmm0, %xmm1
	movdqu	%xmm2, (%eax)
	movdqu	%xmm1, 16(%eax)
	addl	$60, %esp
	retl
.Lfunc_end0:
	.size	sha256_transform_shani, .Lfunc_end0-sha256_transform_shani
	.section	".note.GNU-stack","",@progbits
#endif
