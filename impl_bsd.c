
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <stdlib.h>
#include "sha2_impl.h"

#include "freebsd/sha256.h"
#include "freebsd/sha512.h"
#include "freebsd/sha512t.h"

static int bsd_SHA256_Init(void **ctx)
{
	SHA256_CTX *c = malloc(sizeof(SHA256_CTX));
	if (!c) exit(111);
	*ctx = c;
	SHA256_Init(c);
	return 0;
}

static int bsd_SHA256_Update(void *ctx, const void *data, size_t len)
{
	SHA256_CTX *c = ctx;
	SHA256_Update(c, data, len);
	return 0;
}

static int bsd_SHA256_Final(void *ctx, unsigned char *md)
{
	SHA256_CTX *c = ctx;
	SHA256_Final(md, c);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha256_bsd_impl = {
	.init = bsd_SHA256_Init,
	.update = bsd_SHA256_Update,
	.final = bsd_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-bsd"
};

static int bsd_SHA512_Init(void **ctx)
{
	SHA512_CTX *c = malloc(sizeof(SHA512_CTX));
	if (!c) exit(111);
	*ctx = c;
	SHA512_Init(c);
	return 0;
}

static int bsd_SHA512_Update(void *ctx, const void *data, size_t len)
{
	SHA512_CTX *c = ctx;
	SHA512_Update(c, data, len);
	return 0;
}

static int bsd_SHA512_Final(void *ctx, unsigned char *md)
{
	SHA512_CTX *c = ctx;
	SHA512_Final(md, c);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha512_bsd_impl = {
	.init = bsd_SHA512_Init,
	.update = bsd_SHA512_Update,
	.final = bsd_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-bsd"
};

static int bsd_SHA512_256_Init(void **ctx)
{
	SHA512_CTX *c = malloc(sizeof(SHA512_CTX));
	if (!c) exit(111);
	*ctx = c;
	SHA512_256_Init(c);
	return 0;
}

static int bsd_SHA512_256_Update(void *ctx, const void *data, size_t len)
{
	SHA512_CTX *c = ctx;
	SHA512_256_Update(c, data, len);
	return 0;
}

static int bsd_SHA512_256_Final(void *ctx, unsigned char *md)
{
	SHA512_CTX *c = ctx;
	SHA512_256_Final(md, c);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha512_256_bsd_impl = {
	.init = bsd_SHA512_256_Init,
	.update = bsd_SHA512_256_Update,
	.final = bsd_SHA512_256_Final,
	.digest_len = 32,
	.name = "sha512_256-bsd"
};
