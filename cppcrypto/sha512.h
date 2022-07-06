
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#ifndef _SHA512_H
#define _SHA512_H

#include <stdint.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define cpu_to_be64(x) __builtin_bswap64(x)
#else
#define cpu_to_be64(x) (x)
#endif

typedef void (*sha512_f)(uint64_t state[8], const void *data, size_t blks);

/* SHA2-512 */
typedef struct {
	uint64_t state[8];
	uint64_t count[2];
	uint8_t wbuf[128];
	sha512_f tf;
} sha512_ctx;

void sha512_init(sha512_ctx *ctx);
void sha512_init_tf(sha512_ctx *ctx, sha512_f tf);
void sha512_update(sha512_ctx *ctx, const uint8_t *data, size_t len);
void sha512_final(sha512_ctx *ctx, uint8_t *result);

/* SHA2-512-256 */
void sha512_256_init(sha512_ctx *ctx);
void sha512_256_init_tf(sha512_ctx *ctx, sha512_f func);
#define sha512_256_update(c,d,l) sha512_update(c,d,l)
void sha512_256_final(sha512_ctx *ctx, uint8_t *result);

/* generic transform function */
void sha512_transform(uint64_t state[8], const void *data, size_t blks);

#endif
