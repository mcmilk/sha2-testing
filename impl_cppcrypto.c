
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <stdlib.h>
#include "sha2_impl.h"

#include "cppcrypto/sha2.h"

/*************************************************************************/
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

/*************************************************************************/
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

/*************************************************************************/
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

#if defined(__aarch64__)
extern void sha256_transform_armv8crypto(sha256_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA256_Init_arm(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init(c, sha256_transform_armv8crypto);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_arm_impl = {
	.init = cppcrypto_SHA256_Init_arm,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-cppcrypto-armv8"
};
#endif

#if defined(__PPC64__)
extern void sha256_process_p8(sha256_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA256_Init_ppc64(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init(c, sha256_process_p8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_ppc64_impl = {
	.init = cppcrypto_SHA256_Init_ppc64,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-cppcrypto-ppc64"
};

extern void sha512_process_p8(sha512_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA512_Init_ppc64(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init(c, sha512_process_p8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_cppcrypto_ppc64_impl = {
	.init = cppcrypto_SHA512_Init_ppc64,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 32,
	.name = "sha512-cppcrypto-ppc64"
};
#endif

#if defined(__x86_64)
static inline int have_sse2(void) { return (__builtin_cpu_supports("sse2")); }
static inline int have_ssse3(void) { return (__builtin_cpu_supports("ssse3")); }
static inline int have_sse41(void) { return (__builtin_cpu_supports("sse4.1")); }
static inline int have_sse42(void) { return (__builtin_cpu_supports("sse4.2")); }
static inline int have_avx(void) { return (__builtin_cpu_supports("avx")); }
static inline int have_avx2(void) { return (__builtin_cpu_supports("avx2")); }
static inline int have_avx512f(void) { return (__builtin_cpu_supports("avx512f")); }
static inline int have_avx512vl(void) { return (__builtin_cpu_supports("avx512vl")); }

#include <cpuid.h>
static inline int have_shani(void) {
    unsigned int CPUInfo[4];
    __cpuid(0, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    if (CPUInfo[0] < 7)
        return 0;

    __cpuid_count(7, 0, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
    return CPUInfo[1] & (1 << 29); /* SHA */
}

/*************************************************************************/
extern void sha256_transform_ssse3(sha256_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA256_Init_ssse3(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init(c, sha256_transform_ssse3);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_ssse3_impl = {
	.init = cppcrypto_SHA256_Init_ssse3,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_ssse3,
	.name = "sha256-cppcrypto-ssse3"
};

/*************************************************************************/
extern void sha256_transform_avx(sha256_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA256_Init_avx(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init(c, sha256_transform_avx);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_avx_impl = {
	.init = cppcrypto_SHA256_Init_avx,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_avx,
	.name = "sha256-cppcrypto-avx"
};

/*************************************************************************/
extern void sha256_transform_ni(sha256_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA256_Init_ni(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init(c, sha256_transform_ni);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_ni_impl = {
	.init = cppcrypto_SHA256_Init_ni,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_shani,
	.name = "sha256-cppcrypto-ni"
};

/*************************************************************************/
extern void sha256_transform_shani(sha256_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA256_Init_shani(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init(c, sha256_transform_shani);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_cppcrypto_shani_impl = {
	.init = cppcrypto_SHA256_Init_shani,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_shani,
	.name = "sha256-cppcrypto-shani"
};

/*************************************************************************/
extern void sha512_transform_ssse3(sha512_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA512_Init_ssse3(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init(c, sha512_transform_ssse3);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_cppcrypto_ssse3_impl = {
	.init = cppcrypto_SHA512_Init_ssse3,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_ssse3,
	.name = "sha512-cppcrypto-ssse3"
};

/*************************************************************************/
extern void sha512_transform_avx(sha512_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA512_Init_avx(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init(c, sha512_transform_avx);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_cppcrypto_avx_impl = {
	.init = cppcrypto_SHA512_Init_avx,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_avx,
	.name = "sha512-cppcrypto-avx"
};

/*************************************************************************/
extern void sha512_transform_avx2(sha512_ctx * ctx, void *mp, int num_blks);
static int cppcrypto_SHA512_Init_avx2(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init(c, sha512_transform_avx2);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_cppcrypto_avx2_impl = {
	.init = cppcrypto_SHA512_Init_avx2,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_avx2,
	.name = "sha512-cppcrypto-avx2"
};

#endif
