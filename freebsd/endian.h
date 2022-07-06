/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2002 Thomas Moestl <tmm@FreeBSD.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD$
 */
/*
 * Portions copyright (c) 2018, ARM Limited and Contributors.
 * All rights reserved.
 */

/* *BSD has it's own _MACHINE_ENDIAN_H_ */
#ifndef MY_MACHINE_ENDIAN_H_
#define MY_MACHINE_ENDIAN_H_

#include <sys/types.h>
#include <strings.h>
#include <stdint.h>
#include <string.h>

static inline void
be32enc(void *pp, uint32_t u)
{
	uint8_t *p = (uint8_t *)pp;

	p[0] = (u >> 24) & 0xff;
	p[1] = (u >> 16) & 0xff;
	p[2] = (u >> 8) & 0xff;
	p[3] = u & 0xff;
}

static inline void
be64enc(void *pp, uint64_t u)
{
	uint8_t *p = (uint8_t *)pp;

	be32enc(p, (uint32_t)(u >> 32));
	be32enc(p + 4, (uint32_t)(u & 0xffffffffU));
}

#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

/* Copy a vector of big-endian uint32_t into a vector of bytes */
#define	be32enc_vect(dst, src, len)	\
	memcpy((void *)dst, (const void *)src, (size_t)len)

/* Copy a vector of big-endian uint64_t into a vector of bytes */
#define	be64enc_vect(dst, src, len)	\
	memcpy((void *)dst, (const void *)src, (size_t)len)

/* Copy a vector of bytes into a vector of big-endian uint32_t */
#define	be32dec_vect(dst, src, len)	\
	memcpy((void *)dst, (const void *)src, (size_t)len)

/* Copy a vector of bytes into a vector of big-endian uint64_t */
#define	be64dec_vect(dst, src, len)	\
	memcpy((void *)dst, (const void *)src, (size_t)len)

#else

static inline uint32_t
be32dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return (((unsigned)p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static inline uint64_t
be64dec(const void *pp)
{
	uint8_t const *p = (uint8_t const *)pp;

	return (((uint64_t)be32dec(p) << 32) | be32dec(p + 4));
}

/*
 * Encode a length len/4 vector of (uint32_t) into a length len vector of
 * (unsigned char) in big-endian form.  Assumes len is a multiple of 4.
 */
static inline void
be32enc_vect(unsigned char *dst, const uint32_t *src, size_t len)
{
	size_t i;

	for (i = 0; i < len / 4; i++)
		be32enc(dst + i * 4, src[i]);
}

/*
 * Decode a big-endian length len vector of (unsigned char) into a length
 * len/4 vector of (uint32_t).  Assumes len is a multiple of 4.
 */
static inline void
be32dec_vect(uint32_t *dst, const unsigned char *src, size_t len)
{
	size_t i;

	for (i = 0; i < len / 4; i++)
		dst[i] = be32dec(src + i * 4);
}

/*
 * Encode a length len/4 vector of (uint64_t) into a length len vector of
 * (unsigned char) in big-endian form.  Assumes len is a multiple of 8.
 */
static inline void
be64enc_vect(unsigned char *dst, const uint64_t *src, size_t len)
{
	size_t i;

	for (i = 0; i < len / 8; i++)
		be64enc(dst + i * 8, src[i]);
}

/*
 * Decode a big-endian length len vector of (unsigned char) into a length
 * len/4 vector of (uint64_t).  Assumes len is a multiple of 8.
 */
static inline void
be64dec_vect(uint64_t *dst, const unsigned char *src, size_t len)
{
	size_t i;

	for (i = 0; i < len / 8; i++)
		dst[i] = be64dec(src + i * 8);
}

#endif /* BYTE_ORDER != BIG_ENDIAN */

#endif /* ENDIAN_H */
