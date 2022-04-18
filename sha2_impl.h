
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#ifndef	_SHA2_IMPL_H
#define	_SHA2_IMPL_H

#include <sys/types.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHA256_DIGEST_LENGTH  32
#define SHA256_BLOCK_SIZE     64

#define SHA512_DIGEST_LENGTH  64
#define SHA512_BLOCK_SIZE     128

#define SHA512_256_DIGEST_LENGTH  32

typedef int (*sha2_init_f)(void **ctx);
typedef int (*sha2_update_f)(void *ctx, const void *data, size_t len);
typedef int (*sha2_final_f)(void *ctx, unsigned char *md);
typedef int (*sha2_is_supported_f)(void);

typedef struct sha2_impl_ops {
	sha2_init_f init;
	sha2_update_f update;
	sha2_final_f final;
	sha2_is_supported_f is_supported;
	int digest_len;
	const char *name;
} sha2_impl_ops_t;

extern const sha2_impl_ops_t sha256_cifra_impl;
extern const sha2_impl_ops_t sha512_cifra_impl;

extern const sha2_impl_ops_t sha256_openssl_impl;
extern const sha2_impl_ops_t sha512_openssl_impl;

extern const sha2_impl_ops_t sha256_sbase_impl;
extern const sha2_impl_ops_t sha512_sbase_impl;
extern const sha2_impl_ops_t sha512_256_sbase_impl;

extern const sha2_impl_ops_t sha256_bsd_impl;
extern const sha2_impl_ops_t sha512_bsd_impl;
extern const sha2_impl_ops_t sha512_256_bsd_impl;

extern const sha2_impl_ops_t sha256_cppcrypto_impl;
extern const sha2_impl_ops_t sha512_cppcrypto_impl;
extern const sha2_impl_ops_t sha512_256_cppcrypto_impl;

#ifdef	__cplusplus
}
#endif

#endif /* _SHA2_IMPL_H */