
/*
 * This code is based on public domain code within the cppcrypto-0.17 library.
 * Source: http://cppcrypto.sourceforge.net/
 * Author: kerukuro
 *
 * Copyright (c) 2022 Tino Reichardt
 */

#ifndef _SHA2_H
#define _SHA2_H

#include <stdint.h>

typedef struct {
	uint64_t count[2];
	uint32_t hash[8];
	uint32_t wbuf[16];
} sha256_ctx;

void sha256_begin(sha256_ctx * ctx);
void sha256_hash(const unsigned char *source, uint32_t sourceLen,
		 sha256_ctx * ctx);
void sha256_end(unsigned char *result, sha256_ctx * ctx);
void sha256(unsigned char *result, const unsigned char *source,
	    uint32_t sourceLen);

typedef struct {
	uint64_t count[2];
	uint64_t hash[8];
	uint64_t wbuf[16];
} sha512_ctx;

void sha512_begin(sha512_ctx * ctx);
void sha512_hash(const unsigned char *source, uint64_t sourceLen,
		 sha512_ctx * ctx);
void sha512_end(unsigned char *result, sha512_ctx * ctx);
void sha512(unsigned char *result, const unsigned char *source,
	    uint64_t sourceLen);

void sha512_256_begin(sha512_ctx * ctx);
#define sha512_256_hash(s,l,c) sha512_hash(s,l,c)
void sha512_256_end(unsigned char *result, sha512_ctx * ctx);

#endif
