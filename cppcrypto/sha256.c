
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#include <string.h>
#include "sha256.h"

/* SHA256 */
void sha256_init(sha256_ctx *ctx)
{
	sha256_init_tf(ctx, sha256_transform);
}

void sha256_init_tf(sha256_ctx *ctx, sha256_f func)
{
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
	ctx->count[0] = 0;
	ctx->count[1] = 0;
	ctx->tf = func;
}

void sha256_update(sha256_ctx *ctx, const uint8_t *data, size_t len)
{
	uint64_t pos = ctx->count[0];
	uint64_t total = ctx->count[1];
	uint8_t *m = ctx->wbuf;

	if (pos && pos + len >= 64) {
		memcpy(m + pos, data, 64 - pos);
		ctx->tf(ctx->state, m, 1);
		len -= 64 - pos;
		total += (64 - pos) * 8;
		data += 64 - pos;
		pos = 0;
	}

	if (len >= 64) {
		uint32_t blocks = len / 64;
		uint32_t bytes = blocks * 64;
		ctx->tf(ctx->state, data, blocks);
		len -= bytes;
		total += (bytes) * 8;
		data += bytes;
	}
	memcpy(m + pos, data, len);

	pos += len;
	total += len * 8;
	ctx->count[0] = pos;
	ctx->count[1] = total;
}

void sha256_final(sha256_ctx *ctx, uint8_t *result)
{
	uint64_t mlen, pos = ctx->count[0];
	uint8_t *m = ctx->wbuf;
	uint32_t *R = (uint32_t*)result;

	m[pos++] = 0x80;
	if (pos > 56) {
		memset(m + pos, 0, (size_t)(64 - pos));
		ctx->tf(ctx->state, m, 1);
		pos = 0;
	}

	memset(m + pos, 0, (size_t)(64 - pos));
	mlen = cpu_to_be64(ctx->count[1]);
	memcpy(m + (64 - 8), &mlen, 64 / 8);
	ctx->tf(ctx->state, m, 1);

	R[0] = cpu_to_be32(ctx->state[0]);
	R[1] = cpu_to_be32(ctx->state[1]);
	R[2] = cpu_to_be32(ctx->state[2]);
	R[3] = cpu_to_be32(ctx->state[3]);
	R[4] = cpu_to_be32(ctx->state[4]);
	R[5] = cpu_to_be32(ctx->state[5]);
	R[6] = cpu_to_be32(ctx->state[6]);
	R[7] = cpu_to_be32(ctx->state[7]);
	memset(ctx, 0, sizeof(*ctx));
}
