
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include "sha2_impl.h"

#include <openssl/sha.h>

static int openssl_SHA256_Init(void **ctx)
{
	SHA256_CTX *c = malloc(sizeof(SHA256_CTX));
	if (!c) exit(111);
	*ctx = c;
	return SHA256_Init(c);
}

static int openssl_SHA256_Update(void *ctx, const void *data, size_t len)
{
	SHA256_CTX *c = ctx;
	return SHA256_Update(c, data, len);
}

static int openssl_SHA256_Final(void *ctx, unsigned char *md)
{
	SHA256_CTX *c = ctx;
	int r = SHA256_Final(md, c);
	free(ctx);
	return r;
}

const sha2_impl_ops_t sha256_openssl_impl = {
	.init = openssl_SHA256_Init,
	.update = openssl_SHA256_Update,
	.final = openssl_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-openssl"
};

static int openssl_SHA512_Init(void **ctx)
{
	SHA512_CTX *c = malloc(sizeof(SHA512_CTX));
	if (!c) exit(111);
	*ctx = c;
	return SHA512_Init(c);
}

static int openssl_SHA512_Update(void *ctx, const void *data, size_t len)
{
	SHA512_CTX *c = ctx;
	return SHA512_Update(c, data, len);
}

static int openssl_SHA512_Final(void *ctx, unsigned char *md)
{
	SHA512_CTX *c = ctx;
	int r = SHA512_Final(md, c);
	free(ctx);
	return r;
}

const sha2_impl_ops_t sha512_openssl_impl = {
	.init = openssl_SHA512_Init,
	.update = openssl_SHA512_Update,
	.final = openssl_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-openssl"
};

