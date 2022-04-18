
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <stdlib.h>
#include "sha2_impl.h"

#include "cppcrypto/Sha2.h"

static int cppcrypto_SHA256_Init(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_begin(c);
	*ctx = c;
	return 0;
}

static int cppcrypto_SHA256_Update(void *ctx, const void *data, size_t len)
{
	sha256_hash(data, len, ctx);
	return 0;
}

static int cppcrypto_SHA256_Final(void *ctx, unsigned char *md)
{
	sha256_end(md, ctx);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_impl = {
	.init = cppcrypto_SHA256_Init,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-cppcrypto"
};

static int cppcrypto_SHA512_Init(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_begin(c);
	*ctx = c;
	return 0;
}

static int cppcrypto_SHA512_Update(void *ctx, const void *data, size_t len)
{
	sha512_hash(data, len, ctx);
	return 0;
}

static int cppcrypto_SHA512_Final(void *ctx, unsigned char *md)
{
	sha512_end(md, ctx);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha512_cppcrypto_impl = {
	.init = cppcrypto_SHA512_Init,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-cppcrypto"
};

static int cppcrypto_SHA512_256_Init(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_256_begin(c);
	*ctx = c;
	return 0;
}

static int cppcrypto_SHA512_256_Update(void *ctx, const void *data, size_t len)
{
	sha512_256_hash(data, len, ctx);
	return 0;
}

static int cppcrypto_SHA512_256_Final(void *ctx, unsigned char *md)
{
	sha512_256_end(md, ctx);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha512_256_cppcrypto_impl = {
	.init = cppcrypto_SHA512_256_Init,
	.update = cppcrypto_SHA512_256_Update,
	.final = cppcrypto_SHA512_256_Final,
	.digest_len = 32,
	.name = "sha512_256-cppcrypto"
};
