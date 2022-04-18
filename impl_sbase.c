
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <stdlib.h>
#include "sha2_impl.h"

#include "sbase/sha2.h"

static int sbase_SHA256_Init(void **ctx)
{
	struct sha256 *c = malloc(sizeof(struct sha256));
	if (!c) exit(111);
	sha256_init(c);
	*ctx = c;
	return 0;
}

static int sbase_SHA256_Update(void *ctx, const void *data, size_t len)
{
	sha256_update(ctx, data, len);
	return 0;
}

static int sbase_SHA256_Final(void *ctx, unsigned char *md)
{
	sha256_sum(ctx, md);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha256_sbase_impl = {
	.init = sbase_SHA256_Init,
	.update = sbase_SHA256_Update,
	.final = sbase_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-sbase"
};

static int sbase_SHA512_Init(void **ctx)
{
	struct sha512 *c = malloc(sizeof(struct sha512));
	if (!c) exit(111);
	sha512_init(c);
	*ctx = c;
	return 0;
}

static int sbase_SHA512_Update(void *ctx, const void *data, size_t len)
{
	sha512_update(ctx, data, len);
	return 0;
}

static int sbase_SHA512_Final(void *ctx, unsigned char *md)
{
	sha512_sum(ctx, md);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha512_sbase_impl = {
	.init = sbase_SHA512_Init,
	.update = sbase_SHA512_Update,
	.final = sbase_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-sbase"
};

static int sbase_SHA512_256_Init(void **ctx)
{
	struct sha512 *c = malloc(sizeof(struct sha512));
	sha512_256_init(c);
	*ctx = c;
	return 0;
}

static int sbase_SHA512_256_Update(void *ctx, const void *data, size_t len)
{
	sha512_256_update(ctx, data, len);
	return 0;
}

static int sbase_SHA512_256_Final(void *ctx, unsigned char *md)
{
	sha512_sum(ctx, md);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha512_256_sbase_impl = {
	.init = sbase_SHA512_256_Init,
	.update = sbase_SHA512_256_Update,
	.final = sbase_SHA512_256_Final,
	.digest_len = 32,
	.name = "sha512_256-sbase"
};
