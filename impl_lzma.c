
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <stdlib.h>
#include "sha2_impl.h"

#include "lzma/sha256.h"

static int lzma_SHA256_Init(void **ctx)
{
	lzma_check_state *c = malloc(sizeof(lzma_check_state));
	if (!c) exit(111);
	lzma_sha256_init(c);
	*ctx = c;
	return 0;
}

static int lzma_SHA256_Update(void *ctx, const void *data, size_t len)
{
	lzma_sha256_update(data, len, ctx);
	return 0;
}

static int lzma_SHA256_Final(void *ctx, unsigned char *md)
{
	lzma_check_state *c = ctx;
	lzma_sha256_finish(ctx);
	size_t i;
	for (i = 0; i < 64; ++i)
		md[i] = c->buffer.u8[i];
	free(ctx);
	return 0;
}

const sha2_impl_ops_t sha256_lzma_impl = {
	.init = lzma_SHA256_Init,
	.update = lzma_SHA256_Update,
	.final = lzma_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-lzma"
};
