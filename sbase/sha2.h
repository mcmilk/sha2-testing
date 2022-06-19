
/* public domain sha256 implementation based on fips180-3 */

#include <stdint.h>

struct sha256 {
	uint64_t len;		/* processed message length */
	uint32_t h[8];		/* hash state */
	uint8_t buf[64];	/* message block buffer */
};

void sb_sha256_init(void *ctx);
void sb_sha256_update(void *ctx, const void *m, unsigned long len);
void sb_sha256_sum(void *ctx, uint8_t md[32]);

struct sha512 {
	uint64_t len;		/* processed message length */
	uint64_t h[8];		/* hash state */
	uint8_t buf[128];	/* message block buffer */
};

void sb_sha512_init(void *ctx);
void sb_sha512_update(void *ctx, const void *m, unsigned long len);
void sb_sha512_sum(void *ctx, uint8_t md[64]);

void sb_sha512_256_init(void *ctx);
#define sb_sha512_256_update  sb_sha512_update
void sb_sha512_256_sum(void *ctx, uint8_t md[32]);

#define SHA256_DIGEST_LENGTH  32
#define SHA512_DIGEST_LENGTH  64
#define SHA512_256_DIGEST_LENGTH  32
