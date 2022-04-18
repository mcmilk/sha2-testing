
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <stdlib.h>
#include "sha2_impl.h"

#include "tomcrypt/sha2.h"

static int ltc_SHA256_Init(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	ltc_sha256_begin(c);
	*ctx = c;
	return 0;
}

static int ltc_SHA256_Update(void *ctx, const void *data, size_t len)
{
	ltc_sha256_hash(data, len, ctx);
	return 0;
}

static int ltc_SHA256_Final(void *ctx, unsigned char *md)
{
	ltc_sha256_end(md, ctx);
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha256_ltc_impl = {
	.init = ltc_SHA256_Init,
	.update = ltc_SHA256_Update,
	.final = ltc_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-tomcrypt"
};
