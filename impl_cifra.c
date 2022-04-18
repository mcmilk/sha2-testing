
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include "sha2_impl.h"
#include "cifra/sha2.h"

static int cifra_SHA256_Init(void **ctx)
{
	cf_sha256_context *c = malloc(sizeof(cf_sha256_context));
	if (!c) exit(111);
	*ctx = c;
	cf_sha256_init(c);
	return 0;
}

static int cifra_SHA256_Update(void *ctx, const void *data, size_t len)
{
	cf_sha256_context *c = ctx;
	cf_sha256_update(c, data, len);
	return 0;
}

static int cifra_SHA256_Final(void *ctx, unsigned char *md)
{
	cf_sha256_context *c = ctx;
	cf_sha256_digest_final(c, md);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha256_cifra_impl = {
	.init = cifra_SHA256_Init,
	.update = cifra_SHA256_Update,
	.final = cifra_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-cifra"
};

static int cifra_SHA512_Init(void **ctx)
{
	cf_sha512_context *c = malloc(sizeof(cf_sha512_context));
	if (!c) exit(111);
	*ctx = c;
	cf_sha512_init(c);
	return 0;
}

static int cifra_SHA512_Update(void *ctx, const void *data, size_t len)
{
	cf_sha512_context *c = ctx;
	cf_sha512_update(c, data, len);
	return 0;
}

static int cifra_SHA512_Final(void *ctx, unsigned char *md)
{
	cf_sha512_context *c = ctx;
	cf_sha512_digest_final(c, md);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha512_cifra_impl = {
	.init = cifra_SHA512_Init,
	.update = cifra_SHA512_Update,
	.final = cifra_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-cifra"
};
