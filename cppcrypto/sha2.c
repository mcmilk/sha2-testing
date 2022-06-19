
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 * Public domain with CC0 1.0.
 */

#include <string.h>

#include "sha2.h"

static sha256_transform_f transfunc256 = NULL;
static sha512_transform_f transfunc512 = NULL;

void sha512_init(sha512_ctx * ctx, sha512_transform_f func)
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
	transfunc512 = func;
}

void sha512_begin(sha512_ctx * ctx)
{
	sha512_init(ctx, sha512_transform);
}

void sha512_end(uint8_t *result, sha512_ctx * ctx)
{
	int i;
	uint64_t mlen, pos = ctx->count[0];
	uint8_t *m = (uint8_t *) ctx->wbuf;
	m[pos++] = 0x80;
	if (pos > 112) {
		memset(m + pos, 0, (size_t)(128 - pos));
		transfunc512(ctx, m, 1);
		pos = 0;
	}
	memset(m + pos, 0, (size_t)(128 - pos));
	mlen = cpu_to_be64(ctx->count[1]);
	memcpy(m + (128 - 8), &mlen, 64 / 8);
	transfunc512(ctx, m, 1);
	for (i = 0; i < 8; i++) {
		ctx->state[i] = cpu_to_be64(ctx->state[i]);
	}
	memcpy(result, ctx->state, 64);
}

void sha512_hash(const uint8_t *data, uint64_t len, sha512_ctx * ctx)
{
	uint64_t pos = ctx->count[0];
	uint64_t total = ctx->count[1];
	uint8_t *m = (uint8_t *) ctx->wbuf;
	if (pos && pos + len >= 128) {
		memcpy(m + pos, data, (size_t)(128 - pos));
		transfunc512(ctx, m, 1);
		len -= 128 - pos;
		total += (128 - pos) * 8;
		data += 128 - pos;
		pos = 0;
	}
	if (len >= 128) {
		uint64_t blocks = len / 128;
		uint64_t bytes = blocks * 128;
		transfunc512(ctx, (void *)data, blocks);
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

/* SHA256 */
void sha256_init(sha256_ctx * ctx, sha256_transform_f func)
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
	transfunc256 = func;
}

void sha256_begin(sha256_ctx * ctx)
{
	sha256_init(ctx, sha256_transform);
}

void sha256_end(uint8_t *result, sha256_ctx * ctx)
{
	int i;
	uint64_t mlen, pos = ctx->count[0];
	uint8_t *m = (uint8_t *) ctx->wbuf;
	m[pos++] = 0x80;

	if (pos > 56) {
		memset(m + pos, 0, (size_t)(64 - pos));
		transfunc256(ctx, m, 1);
		pos = 0;
	}

	memset(m + pos, 0, (size_t)(56 - pos));
	mlen = cpu_to_be64(ctx->count[1]);
	memcpy(m + (64 - 8), &mlen, 64 / 8);
	transfunc256(ctx, m, 1);

	for (i = 0; i < 8; i++) {
		ctx->state[i] = cpu_to_be32(ctx->state[i]);
	}
	memcpy(result, ctx->state, 32);
}

void sha256_hash(const uint8_t *data, uint32_t len, sha256_ctx * ctx)
{
	uint64_t pos = ctx->count[0];
	uint64_t total = ctx->count[1];
	uint8_t *m = (uint8_t *) ctx->wbuf;

	if (pos && pos + len >= 64) {
		memcpy(m + pos, data, 64 - pos);
		transfunc256(ctx, m, 1);
		len -= 64 - pos;
		total += (64 - pos) * 8;
		data += 64 - pos;
		pos = 0;
	}

	if (len >= 64) {
		uint32_t blocks = len / 64;
		uint32_t bytes = blocks * 64;
		transfunc256(ctx, (void *)data, blocks);
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

/* SHA512_256 */
void sha512_256_init(sha512_ctx * ctx, sha512_transform_f func)
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
	transfunc512 = func;
}

void sha512_256_begin(sha512_ctx * ctx)
{
	sha512_256_init(ctx, sha512_transform);
}

void sha512_256_end(uint8_t *result, sha512_ctx * ctx)
{
	int i;
	uint64_t mlen, pos = ctx->count[0];
	uint8_t *m = (uint8_t *) ctx->wbuf;

	m[pos++] = 0x80;
	if (pos > 112) {
		memset(m + pos, 0, (size_t)(128 - pos));
		transfunc512(ctx, m, 1);
		pos = 0;
	}

	memset(m + pos, 0, (size_t)(128 - pos));
	mlen = cpu_to_be64(ctx->count[1]);
	memcpy(m + (128 - 8), &mlen, 64 / 8);
	transfunc512(ctx, m, 1);

	for (i = 0; i < 4; i++) {
		ctx->state[i] = cpu_to_be64(ctx->state[i]);
	}
	memcpy(result, ctx->state, 64);
}
