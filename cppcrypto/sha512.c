
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#include <string.h>
#include "sha512.h"

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define cpu_to_be64(x) __builtin_bswap64(x)
#else
#define cpu_to_be64(x) (x)
#endif

void sha512_init(sha512_ctx *ctx)
{
	sha512_init_tf(ctx, sha512_transform);
}

void sha512_init_tf(sha512_ctx *ctx, sha512_f func)
{
	ctx->state[0] = 0x6a09e667f3bcc908;
	ctx->state[1] = 0xbb67ae8584caa73b;
	ctx->state[2] = 0x3c6ef372fe94f82b;
	ctx->state[3] = 0xa54ff53a5f1d36f1;
	ctx->state[4] = 0x510e527fade682d1;
	ctx->state[5] = 0x9b05688c2b3e6c1f;
	ctx->state[6] = 0x1f83d9abfb41bd6b;
	ctx->state[7] = 0x5be0cd19137e2179;
	ctx->count[0] = 0;
	ctx->count[1] = 0;
	ctx->tf = func;
}

void sha512_final(sha512_ctx *ctx, uint8_t *result)
{
	uint64_t mlen, pos = ctx->count[0];
	uint8_t *m = ctx->wbuf;
	uint64_t *R = (uint64_t*)result;

	m[pos++] = 0x80;
	if (pos > 112) {
		memset(m + pos, 0, (size_t)(128 - pos));
		ctx->tf(ctx->state, m, 1);
		pos = 0;
	}
	memset(m + pos, 0, (size_t)(128 - pos));
	mlen = cpu_to_be64(ctx->count[1]);
	memcpy(m + (128 - 8), &mlen, 64 / 8);
	ctx->tf(ctx->state, m, 1);
	R[0] = cpu_to_be64(ctx->state[0]);
	R[1] = cpu_to_be64(ctx->state[1]);
	R[2] = cpu_to_be64(ctx->state[2]);
	R[3] = cpu_to_be64(ctx->state[3]);
	R[4] = cpu_to_be64(ctx->state[4]);
	R[5] = cpu_to_be64(ctx->state[5]);
	R[6] = cpu_to_be64(ctx->state[6]);
	R[7] = cpu_to_be64(ctx->state[7]);
	memset(ctx, 0, sizeof( *ctx));
}

void sha512_update(sha512_ctx *ctx, const uint8_t *data, size_t len)
{
	uint64_t pos = ctx->count[0];
	uint64_t total = ctx->count[1];
	uint8_t *m = ctx->wbuf;
	if (pos && pos + len >= 128) {
		memcpy(m + pos, data, (size_t)(128 - pos));
		ctx->tf(ctx->state, m, 1);
		len -= 128 - pos;
		total += (128 - pos) * 8;
		data += 128 - pos;
		pos = 0;
	}
	if (len >= 128) {
		uint64_t blocks = len / 128;
		uint64_t bytes = blocks * 128;
		ctx->tf(ctx->state, data, blocks);
		len -= bytes;
		total += (bytes) * 8;
		data += bytes;
	}
	memcpy(m + pos, data, (size_t)(len));
	pos += len;
	total += len * 8;
	ctx->count[0] = pos;
	ctx->count[1] = total;
}

/* SHA512_256 */
void sha512_256_init(sha512_ctx *ctx)
{
	sha512_256_init_tf(ctx, sha512_transform);
}

void sha512_256_init_tf(sha512_ctx *ctx, sha512_f func)
{
	ctx->state[0] = 0x22312194fc2bf72cULL;
	ctx->state[1] = 0x9f555fa3c84c64c2ULL;
	ctx->state[2] = 0x2393b86b6f53b151ULL;
	ctx->state[3] = 0x963877195940eabdULL;
	ctx->state[4] = 0x96283ee2a88effe3ULL;
	ctx->state[5] = 0xbe5e1e2553863992ULL;
	ctx->state[6] = 0x2b0199fc2c85b8aaULL;
	ctx->state[7] = 0x0eb72ddc81c52ca2ULL;
	ctx->count[0] = 0;
	ctx->count[1] = 0;
	ctx->tf = func;
}

void sha512_256_final(sha512_ctx *ctx, uint8_t *result)
{
	uint64_t mlen, pos = ctx->count[0];
	uint8_t *m = ctx->wbuf;
	uint64_t *R = (uint64_t*)result;

	m[pos++] = 0x80;
	if (pos > 112) {
		memset(m + pos, 0, (size_t)(128 - pos));
		ctx->tf(ctx->state, m, 1);
		pos = 0;
	}

	memset(m + pos, 0, (size_t)(128 - pos));
	mlen = cpu_to_be64(ctx->count[1]);
	memcpy(m + (128 - 8), &mlen, 64 / 8);
	ctx->tf(ctx->state, m, 1);

	R[0] = cpu_to_be64(ctx->state[0]);
	R[1] = cpu_to_be64(ctx->state[1]);
	R[2] = cpu_to_be64(ctx->state[2]);
	R[3] = cpu_to_be64(ctx->state[3]);
	memset(ctx, 0, sizeof( *ctx));
}
