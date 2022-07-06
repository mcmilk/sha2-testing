
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#ifndef _SHA256_H
#define _SHA256_H

#include <stdint.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define cpu_to_be32(x) __builtin_bswap32(x)
#define cpu_to_be64(x) __builtin_bswap64(x)
#else
#define cpu_to_be32(x) (x)
#define cpu_to_be64(x) (x)
#endif

typedef void (*sha256_f)(uint32_t state[8], const void *data, size_t blks);

/* SHA2-256 */
typedef struct {
	uint32_t state[8];
	uint64_t count[2];
	uint8_t wbuf[64];
	sha256_f tf;
} sha256_ctx;

void sha256_init(sha256_ctx *ctx);
void sha256_init_tf(sha256_ctx *ctx, sha256_f func);
void sha256_update(sha256_ctx *ctx, const uint8_t *data, size_t len);
void sha256_final(sha256_ctx *ctx, uint8_t *result);

/* generic transform function */
void sha256_transform(uint32_t state[8], const void *data, size_t blks);

#endif
//void sha256_block_data_order(SHA256_CTX *ctx, const void *in, size_t num);
