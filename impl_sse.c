
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#if defined(__x86_64)

#include <stdlib.h>
#include "sha2_impl.h"

#include "sse/sha256.h"

static int cppcrypto_SHA256_Init(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_begin2(c);
	*ctx = c;
	return 0;
}

static int cppcrypto_SHA256_Update(void *ctx, const void *data, size_t len)
{
	sha256_hash2(data, len, ctx);
	return 0;
}

static int cppcrypto_SHA256_Final(void *ctx, unsigned char *md)
{
	sha256_end2(md, ctx);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_shani_impl = {
	.init = cppcrypto_SHA256_Init,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-cppcrypto-shani"
};

#endif
