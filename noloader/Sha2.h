
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

void sha256_begin2(sha256_ctx * ctx);
void sha256_hash2(const unsigned char *source, uint32_t sourceLen,
		 sha256_ctx * ctx);
void sha256_end2(unsigned char *result, sha256_ctx * ctx);

#endif
