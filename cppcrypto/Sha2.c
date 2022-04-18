
/*
 * This code is based on public domain code within the cppcrypto-0.17 library.
 * Source: http://cppcrypto.sourceforge.net/
 * Author: kerukuro
 *
 * Copyright (c) 2022 Tino Reichardt
 */

#include <string.h>
#include <byteswap.h>

#include "Sha2.h"

typedef void (*sha256_transform_f)(sha256_ctx * ctx, void *m,
				   uint64_t num_blks);
typedef void (*sha512_transform_f)(sha512_ctx * ctx, void *m,
				   uint64_t num_blks);

sha256_transform_f transfunc256 = NULL;
sha512_transform_f transfunc512 = NULL;

/* SHA512 */
static const uint64_t K[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

#define Ch(x,y,z)	((z) ^ ((x) & ((y) ^ (z))))
#define Maj(x,y,z)	(((x) & (y)) | ((z) & ((x) ^ (y))))

#define rotr64(x,n)	(((x) >> n) | ((x) << (64 - n)))
#define sum0(x)		(rotr64((x), 28) ^ rotr64((x), 34) ^ rotr64((x), 39))
#define sum1(x)		(rotr64((x), 14) ^ rotr64((x), 18) ^ rotr64((x), 41))
#define sigma0(x)	(rotr64((x), 1)  ^ rotr64((x), 8)  ^ ((x) >> 7))
#define sigma1(x)	(rotr64((x), 19) ^ rotr64((x), 61) ^ ((x) >> 6))

#define WU(j) (W[j & 15] += sigma1(W[(j + 14) & 15]) + W[(j + 9) & 15] + sigma0(W[(j + 1) & 15]))

#define COMPRESS_ROUND(i, j, K) \
		   T1 = h + sum1(e) + Ch(e, f, g) + K[i + j] + (i? WU(j): W[j]); \
			T2 = sum0(a) + Maj(a, b, c); \
			h = g; \
			g = f; \
			f = e; \
			e = d + T1; \
			d = c; \
			c = b; \
			b = a; \
			a = T1 + T2;

void sha512_transform(sha512_ctx * ctx, void *mp, uint64_t num_blks)
{
	uint64_t blk;
	for (blk = 0; blk < num_blks; blk++) {
		uint64_t W[16];
		uint64_t a, b, c, d, e, f, g, h;
		uint64_t T1, T2;
		int i;

		for (i = 0; i < 128 / 8; i++) {
			W[i] =
			    bswap_64((((const uint64_t *)(mp))[blk * 16 + i]));
		}

		a = ctx->hash[0];
		b = ctx->hash[1];
		c = ctx->hash[2];
		d = ctx->hash[3];
		e = ctx->hash[4];
		f = ctx->hash[5];
		g = ctx->hash[6];
		h = ctx->hash[7];

		for (i = 0; i <= 79; i += 16) {
			COMPRESS_ROUND(i, 0, K);
			COMPRESS_ROUND(i, 1, K);
			COMPRESS_ROUND(i, 2, K);
			COMPRESS_ROUND(i, 3, K);
			COMPRESS_ROUND(i, 4, K);
			COMPRESS_ROUND(i, 5, K);
			COMPRESS_ROUND(i, 6, K);
			COMPRESS_ROUND(i, 7, K);
			COMPRESS_ROUND(i, 8, K);
			COMPRESS_ROUND(i, 9, K);
			COMPRESS_ROUND(i, 10, K);
			COMPRESS_ROUND(i, 11, K);
			COMPRESS_ROUND(i, 12, K);
			COMPRESS_ROUND(i, 13, K);
			COMPRESS_ROUND(i, 14, K);
			COMPRESS_ROUND(i, 15, K);
		}
		ctx->hash[0] += a;
		ctx->hash[1] += b;
		ctx->hash[2] += c;
		ctx->hash[3] += d;
		ctx->hash[4] += e;
		ctx->hash[5] += f;
		ctx->hash[6] += g;
		ctx->hash[7] += h;
	}
}

void sha512_begin(sha512_ctx * ctx)
{
	ctx->hash[0] = 0x6a09e667f3bcc908;
	ctx->hash[1] = 0xbb67ae8584caa73b;
	ctx->hash[2] = 0x3c6ef372fe94f82b;
	ctx->hash[3] = 0xa54ff53a5f1d36f1;
	ctx->hash[4] = 0x510e527fade682d1;
	ctx->hash[5] = 0x9b05688c2b3e6c1f;
	ctx->hash[6] = 0x1f83d9abfb41bd6b;
	ctx->hash[7] = 0x5be0cd19137e2179;
	ctx->count[0] = 0;
	ctx->count[1] = 0;

	if (!transfunc512)
		transfunc512 = sha512_transform;
}

void sha512_end(unsigned char *result, sha512_ctx * ctx)
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
	mlen = bswap_64(ctx->count[1]);
	memcpy(m + (128 - 8), &mlen, 64 / 8);
	transfunc512(ctx, m, 1);
	for (i = 0; i < 8; i++) {
		ctx->hash[i] = bswap_64(ctx->hash[i]);
	}
	memcpy(result, ctx->hash, 64);
}

void sha512_hash(const unsigned char *data, uint64_t len, sha512_ctx * ctx)
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
static const uint32_t SHA256_K[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#undef sum0
#undef sum1
#undef sigma0
#undef sigma1

#define rotr32(x,n)	(((x) >> n) | ((x) << (32 - n)))
#define sum0(x)		(rotr32((x), 2) ^ rotr32((x), 13) ^ rotr32((x), 22))
#define sum1(x)		(rotr32((x), 6) ^ rotr32((x), 11) ^ rotr32((x), 25))
#define sigma0(x)	(rotr32((x), 7) ^ rotr32((x), 18) ^ ((x) >> 3))
#define sigma1(x)	(rotr32((x), 17) ^ rotr32((x), 19) ^ ((x) >> 10))

void sha256_transform(sha256_ctx * ctx, void *mp, uint64_t num_blks)
{
	uint64_t blk;
	for (blk = 0; blk < num_blks; blk++) {
		uint32_t W[16];
		uint32_t a, b, c, d, e, f, g, h;
		uint32_t T1, T2;
		int i;

		for (i = 0; i < 64 / 4; i++) {
			W[i] =
			    bswap_32((((const uint32_t *)(mp))[blk * 16 + i]));
		}

		a = ctx->hash[0];
		b = ctx->hash[1];
		c = ctx->hash[2];
		d = ctx->hash[3];
		e = ctx->hash[4];
		f = ctx->hash[5];
		g = ctx->hash[6];
		h = ctx->hash[7];

		for (i = 0; i <= 63; i += 16) {
			COMPRESS_ROUND(i, 0, SHA256_K);
			COMPRESS_ROUND(i, 1, SHA256_K);
			COMPRESS_ROUND(i, 2, SHA256_K);
			COMPRESS_ROUND(i, 3, SHA256_K);
			COMPRESS_ROUND(i, 4, SHA256_K);
			COMPRESS_ROUND(i, 5, SHA256_K);
			COMPRESS_ROUND(i, 6, SHA256_K);
			COMPRESS_ROUND(i, 7, SHA256_K);
			COMPRESS_ROUND(i, 8, SHA256_K);
			COMPRESS_ROUND(i, 9, SHA256_K);
			COMPRESS_ROUND(i, 10, SHA256_K);
			COMPRESS_ROUND(i, 11, SHA256_K);
			COMPRESS_ROUND(i, 12, SHA256_K);
			COMPRESS_ROUND(i, 13, SHA256_K);
			COMPRESS_ROUND(i, 14, SHA256_K);
			COMPRESS_ROUND(i, 15, SHA256_K);
		}
		ctx->hash[0] += a;
		ctx->hash[1] += b;
		ctx->hash[2] += c;
		ctx->hash[3] += d;
		ctx->hash[4] += e;
		ctx->hash[5] += f;
		ctx->hash[6] += g;
		ctx->hash[7] += h;
	}
}

void sha256_begin(sha256_ctx * ctx)
{
	ctx->hash[0] = 0x6a09e667;
	ctx->hash[1] = 0xbb67ae85;
	ctx->hash[2] = 0x3c6ef372;
	ctx->hash[3] = 0xa54ff53a;
	ctx->hash[4] = 0x510e527f;
	ctx->hash[5] = 0x9b05688c;
	ctx->hash[6] = 0x1f83d9ab;
	ctx->hash[7] = 0x5be0cd19;
	ctx->count[0] = 0;
	ctx->count[1] = 0;

	if (!transfunc256)
		transfunc256 = sha256_transform;
}

void sha256_end(unsigned char *result, sha256_ctx * ctx)
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
	mlen = bswap_64(ctx->count[1]);
	memcpy(m + (64 - 8), &mlen, 64 / 8);
	transfunc256(ctx, m, 1);

	for (i = 0; i < 8; i++) {
		ctx->hash[i] = bswap_32(ctx->hash[i]);
	}
	memcpy(result, ctx->hash, 32);
}

void sha256_hash(const unsigned char *data, uint32_t len, sha256_ctx * ctx)
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
void sha512_256_begin(sha512_ctx * ctx)
{
	ctx->hash[0] = 0x22312194fc2bf72cULL;
	ctx->hash[1] = 0x9f555fa3c84c64c2ULL;
	ctx->hash[2] = 0x2393b86b6f53b151ULL;
	ctx->hash[3] = 0x963877195940eabdULL;
	ctx->hash[4] = 0x96283ee2a88effe3ULL;
	ctx->hash[5] = 0xbe5e1e2553863992ULL;
	ctx->hash[6] = 0x2b0199fc2c85b8aaULL;
	ctx->hash[7] = 0x0eb72ddc81c52ca2ULL;
	ctx->count[0] = 0;
	ctx->count[1] = 0;

	if (!transfunc512)
		transfunc512 = sha512_transform;
}

void sha512_256_end(unsigned char *result, sha512_ctx * ctx)
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
	mlen = bswap_64(ctx->count[1]);
	memcpy(m + (128 - 8), &mlen, 64 / 8);
	transfunc512(ctx, m, 1);
	for (i = 0; i < 4; i++) {
		ctx->hash[i] = bswap_64(ctx->hash[i]);
	}
	memcpy(result, ctx->hash, 64);
}
