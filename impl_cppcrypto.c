
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <stdlib.h>
#include "sha2_impl.h"

#include "cppcrypto/sha256.h"
#include "cppcrypto/sha512.h"

/*************************************************************************/
static int cppcrypto_SHA256_Init(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init(c);
	*ctx = c;
	return 0;
}

static int cppcrypto_SHA256_Update(void *ctx, const void *data, size_t len)
{
	sha256_update(ctx, data, len);
	return 0;
}

static int cppcrypto_SHA256_Final(void *ctx, unsigned char *md)
{
	sha256_final(ctx, md);
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
	sha512_256_init(c);
	*ctx = c;
	return 0;
}

static int cppcrypto_SHA512_256_Update(void *ctx, const void *data, size_t len)
{
	sha512_256_update(ctx, data, len);
	return 0;
}

static int cppcrypto_SHA512_256_Final(void *ctx, unsigned char *md)
{
	sha512_256_final(ctx, md);
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
	sha512_init(c);
	*ctx = c;
	return 0;
}

static int cppcrypto_SHA512_Update(void *ctx, const void *data, size_t len)
{
	sha512_update(ctx, data, len);
	return 0;
}

static int cppcrypto_SHA512_Final(void *ctx, unsigned char *md)
{
	sha512_final(ctx, md);
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

#if defined(__aarch64__) || defined(__arm__)
#include <sys/auxv.h>
#include <asm/hwcap.h>

int have_neon(void)
{
#if defined HWCAP_NEON
    return getauxval(AT_HWCAP) & HWCAP_NEON;
#elif defined HWCAP_FP
    return getauxval(AT_HWCAP) & HWCAP_FP;
#else
    return 0;
#endif
}

int have_sha256_ce(void)
{
#if defined HWCAP_SHA2
    return getauxval(AT_HWCAP) & HWCAP_SHA2;
#elif defined HWCAP2_SHA2
    return getauxval(AT_HWCAP2) & HWCAP2_SHA2;
#else
    return 0;
#endif
}

int have_sha512_ce(void)
{
#if defined HWCAP_SHA512
    return getauxval(AT_HWCAP) & HWCAP_SHA512;
#elif defined HWCAP2_SHA512
    return getauxval(AT_HWCAP2) & HWCAP2_SHA512;
#else
    return 0;
#endif
}

/*************************************************************************/
#if defined(__aarch64__)
extern void sha256_noloader_armv8(uint32_t s[8], const void *data, size_t blks);
static int noloader_SHA256_Init_armv8(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_noloader_armv8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_noloder_armv8_impl = {
	.init = noloader_SHA256_Init_armv8,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_sha256_ce,
	.name = "sha256-noloader-armv8"
};

/*************************************************************************/
extern void sha512_block_armv8(uint64_t s[8], const void *data, size_t blks);
static int ossl_SHA512_Init_armv8(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_armv8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_armv8_impl = {
	.init = ossl_SHA512_Init_armv8,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_sha512_ce,
	.name = "sha512-ossl-armv8"
};
#endif

/*************************************************************************/
extern void sha256_block_neon(uint32_t s[8], const void *data, size_t blks);
static int ossl_SHA256_Init_neon(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_neon);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_neon_impl = {
	.init = ossl_SHA256_Init_neon,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_neon,
	.name = "sha256-ossl-neon"
};

/*************************************************************************/
extern void sha256_block_armv8(uint32_t s[8], const void *data, size_t blks);
static int ossl_SHA256_Init_armv8(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_armv8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_armv8_impl = {
	.init = ossl_SHA256_Init_armv8,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_sha256_ce,
	.name = "sha256-ossl-armv8"
};

/*************************************************************************/
extern void sha256_block_data_order(uint32_t s[8], const void *data, size_t blks);
static int ossl_SHA256_Init_block_order(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_data_order);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_data_order_impl = {
	.init = ossl_SHA256_Init_block_order,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-ossl-armv7"
};

/*************************************************************************/
#if !defined(__aarch64__)
extern void sha512_block_neon(uint64_t s[8], const void *data, size_t blks);
static int ossl_SHA512_Init_neon(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_neon);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_neon_impl = {
	.init = ossl_SHA512_Init_neon,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-ossl-neon"
};
#endif

/*************************************************************************/
extern void sha512_block_data_order(uint64_t s[8], const void *data, size_t blks);
static int ossl_SHA512_Init_block_order(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_data_order);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_data_order_impl = {
	.init = ossl_SHA512_Init_block_order,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-ossl-armv7"
};
#endif

#if defined(__PPC64__)

#include <sys/auxv.h>

int have_isa207(void)
{
#if (defined(AT_HWCAP2) && defined(PPC_FEATURE2_ARCH_2_07))
    return getauxval(AT_HWCAP2) & PPC_FEATURE2_ARCH_2_07;
#else
    return 0;
#endif
}

/*************************************************************************/
extern void sha256_process_p8(uint32_t s[8], const void *data, size_t blks);
static int cppcrypto_SHA256_Init_ppc64(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_process_p8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_noloader_ppc64_impl = {
	.init = cppcrypto_SHA256_Init_ppc64,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_isa207,
	.name = "sha256-noloader-ppc64"
};

/*************************************************************************/
extern void sha512_process_p8(uint64_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA512_Init_ppc64(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_process_p8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_noloader_ppc64_impl = {
	.init = cppcrypto_SHA512_Init_ppc64,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_isa207,
	.name = "sha512-noloader-ppc64"
};

/*************************************************************************/
extern void sha256_block_ppc(uint32_t s[8], const void *data, size_t blks);
static int ossl_SHA256_Init_ppc64(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_ppc);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_ppc64_impl = {
	.init = ossl_SHA256_Init_ppc64,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-ossl-ppc64"
};

/*************************************************************************/
extern void sha512_block_ppc(uint64_t state[8], const void *data, size_t blks);
static int ossl_SHA512_Init_ppc64(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_ppc);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_ppc64_impl = {
	.init = ossl_SHA512_Init_ppc64,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-ossl-ppc64"
};

/*************************************************************************/
extern void sha256_block_p8(uint32_t s[8], const void *data, size_t blks);
static int ossl_SHA256_Init_p8(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_p8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_ppc64p8_impl = {
	.init = ossl_SHA256_Init_p8,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_isa207,
	.name = "sha256-ossl-ppc64p8"
};

/*************************************************************************/
extern void sha512_block_p8(uint64_t state[8], const void *data, size_t blks);
static int ossl_SHA512_Init_p8(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_p8);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_ppc64p8_impl = {
	.init = ossl_SHA512_Init_p8,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_isa207,
	.name = "sha512-ossl-ppc64p8"
};
#endif

#if defined(__x86_64)
static inline int have_ssse3(void) { return (__builtin_cpu_supports("ssse3")); }
static inline int have_avx(void) { return (__builtin_cpu_supports("avx")); }
static inline int have_avx2(void) { return (__builtin_cpu_supports("avx2")); }
//static inline int have_sse41(void) { return (__builtin_cpu_supports("sse4.1")); }
//static inline int have_sse42(void) { return (__builtin_cpu_supports("sse4.2")); }
//static inline int have_avx512(void) { return (__builtin_cpu_supports("avx512f") && __builtin_cpu_supports("avx512vl")); }

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
extern void sha256_transform_ssse3(uint32_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA256_Init_ssse3(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_transform_ssse3);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_intel_ssse3_impl = {
	.init = cppcrypto_SHA256_Init_ssse3,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_ssse3,
	.name = "sha256-intel-ssse3"
};

/*************************************************************************/
extern void sha256_transform_avx(uint32_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA256_Init_avx(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_transform_avx);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_intel_avx_impl = {
	.init = cppcrypto_SHA256_Init_avx,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_avx,
	.name = "sha256-intel-avx"
};

/*************************************************************************/
extern void sha256_block_data_order(uint32_t state[8], const void *data, size_t blks);
static int ossl_SHA256_Init_x64(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_data_order);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_x64_impl = {
	.init = ossl_SHA256_Init_x64,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.name = "sha256-ossl-x64"
};

/*************************************************************************/
extern void sha256_block_data_order_ssse3(uint32_t state[8], const void *data, size_t blks);
static int ossl_SHA256_Init_ssse3(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_data_order_ssse3);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_ssse3_impl = {
	.init = ossl_SHA256_Init_ssse3,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_avx,
	.name = "sha256-ossl-ssse3"
};

/*************************************************************************/
extern void sha256_block_data_order_avx(uint32_t state[8], const void *data, size_t blks);
static int ossl_SHA256_Init_avx(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_data_order_avx);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_avx_impl = {
	.init = ossl_SHA256_Init_avx,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_avx,
	.name = "sha256-ossl-avx"
};

/*************************************************************************/
extern void sha256_block_data_order_avx2(uint32_t state[8], const void *data, size_t blks);
static int ossl_SHA256_Init_avx2(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_data_order_avx2);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_avx2_impl = {
	.init = ossl_SHA256_Init_avx2,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_avx2,
	.name = "sha256-ossl-avx2"
};

/*************************************************************************/
extern void sha256_transform_ni(uint32_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA256_Init_ni(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_transform_ni);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_intel_ni_impl = {
	.init = cppcrypto_SHA256_Init_ni,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_shani,
	.name = "sha256-intel-ni"
};

/*************************************************************************/
extern void sha256_block_data_order_shaext(uint32_t state[8], const void *data, size_t blks);
static int ossl_SHA256_Init_ni(void **ctx)
{
	sha256_ctx *c = malloc(sizeof(sha256_ctx));
	if (!c) exit(111);
	sha256_init_tf(c, sha256_block_data_order_shaext);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha256_ossl_ni_impl = {
	.init = ossl_SHA256_Init_ni,
	.update = cppcrypto_SHA256_Update,
	.final = cppcrypto_SHA256_Final,
	.digest_len = 32,
	.is_supported = have_shani,
	.name = "sha256-ossl-ni"
};

/*************************************************************************/
extern void sha512_transform_ssse3(uint64_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA512_Init_ssse3(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_transform_ssse3);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_intel_ssse3_impl = {
	.init = cppcrypto_SHA512_Init_ssse3,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_ssse3,
	.name = "sha512-intel-ssse3"
};

/*************************************************************************/
extern void sha512_block_data_order(uint64_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA512_Init_x64(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_data_order);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_x64_impl = {
	.init = cppcrypto_SHA512_Init_x64,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.name = "sha512-ossl-x64"
};

/*************************************************************************/
extern void sha512_transform_avx(uint64_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA512_Init_avx(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_transform_avx);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_intel_avx_impl = {
	.init = cppcrypto_SHA512_Init_avx,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_avx,
	.name = "sha512-intel-avx"
};

/*************************************************************************/
extern void sha512_transform_avx2(uint64_t state[8], const void *data, size_t blks);
static int cppcrypto_SHA512_Init_avx2(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_transform_avx2);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_intel_avx2_impl = {
	.init = cppcrypto_SHA512_Init_avx2,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_avx2,
	.name = "sha512-intel-avx2"
};

/*************************************************************************/
extern void sha512_block_data_order_avx(uint64_t state[8], const void *data, size_t blks);
static int ossl_SHA512_Init_avx(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_data_order_avx);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_avx_impl = {
	.init = ossl_SHA512_Init_avx,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_avx,
	.name = "sha512-ossl-avx"
};

/*************************************************************************/
extern void sha512_block_data_order_avx2(uint64_t state[8], const void *data, size_t blks);
static int ossl_SHA512_Init_avx2(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_init_tf(c, sha512_block_data_order_avx2);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512_ossl_avx2_impl = {
	.init = ossl_SHA512_Init_avx2,
	.update = cppcrypto_SHA512_Update,
	.final = cppcrypto_SHA512_Final,
	.digest_len = 64,
	.is_supported = have_avx2,
	.name = "sha512-ossl-avx2"
};

static int ossl_SHA512_256_Init_avx2(void **ctx)
{
	sha512_ctx *c = malloc(sizeof(sha512_ctx));
	if (!c) exit(111);
	sha512_256_init_tf(c, sha512_block_data_order_avx2);
	*ctx = c;
	return 0;
}

const sha2_impl_ops_t sha512t_ossl_avx2_impl = {
	.init = ossl_SHA512_256_Init_avx2,
	.update = cppcrypto_SHA512_256_Update,
	.final = cppcrypto_SHA512_256_Final,
	.digest_len = 64,
	.is_supported = have_avx2,
	.name = "sha512_256-ossl-avx2"
};

#endif
