
/*
 * based on:
 * Tom St Denis, tomstdenis@gmail.com, http://libtom.org
 *
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#ifndef _SHA2_H
#define _SHA2_H

#include <stdint.h>

#define SHA256_DIGEST_SIZE  32
#define SHA256_BLOCK_SIZE   64

typedef struct {
	uint32_t highLength;
	uint32_t lowLength;
	uint32_t state[8];
	unsigned int curlen;
	unsigned char buf[64];
} sha256_ctx;

void ltc_sha256_begin(sha256_ctx * ctx);
void ltc_sha256_hash(const unsigned char *data, unsigned int len, sha256_ctx * ctx);
void ltc_sha256_end(unsigned char *hval, sha256_ctx * ctx);

#endif
