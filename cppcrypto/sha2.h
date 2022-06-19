
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#ifndef _SHA2_H
#define _SHA2_H

#include <stdint.h>

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define cpu_to_be32(x) __builtin_bswap32(x)
#define cpu_to_be64(x) __builtin_bswap64(x)
#else
#define cpu_to_be32(x) (x)
#define cpu_to_be64(x) (x)
#endif

/* SHA2-256 */
typedef struct {
	uint32_t state[8];
	uint64_t count[2];
	uint32_t wbuf[16];
	void *f;
} sha256_ctx;

typedef void (*sha256_transform_f)(sha256_ctx * ctx, void *m,
				   int num_blks);

void sha256_begin(sha256_ctx * ctx);
void sha256_init(sha256_ctx * ctx, sha256_transform_f func);
void sha256_hash(const uint8_t *source, uint32_t sourceLen,
		 sha256_ctx * ctx);
void sha256_end(uint8_t *result, sha256_ctx * ctx);

/* SHA2-512 */
typedef struct {
	uint64_t state[8];
	uint64_t count[2];
	uint64_t wbuf[16];
	void *f;
} sha512_ctx;

typedef void (*sha512_transform_f)(sha512_ctx * ctx, void *m,
				   int num_blks);

void sha512_begin(sha512_ctx * ctx);
void sha512_init(sha512_ctx * ctx, sha512_transform_f func);
void sha512_hash(const uint8_t *source, uint64_t sourceLen,
		 sha512_ctx * ctx);
void sha512_end(uint8_t *result, sha512_ctx * ctx);

/* SHA2-512-256 */
void sha512_256_begin(sha512_ctx * ctx);
void sha512_256_init(sha512_ctx * ctx, sha512_transform_f func);
#define sha512_256_hash(s,l,c) sha512_hash(s,l,c)
void sha512_256_end(uint8_t *result, sha512_ctx * ctx);

/* generic */
void sha256_transform(sha256_ctx * ctx, void *mp, int num_blks);
void sha512_transform(sha512_ctx * ctx, void *mp, int num_blks);

void sha256_transform_shani(sha256_ctx * ctx, void *mp, int num_blks);

#endif
