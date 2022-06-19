
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "sha2_impl.h"
#include "get_cycles.h"

#define ID_SHA256	1
#define ID_SHA512_256	2
#define ID_SHA512	3

/*
 * C version for testing typical SHA2 test vectors, see:
 * - https://csrc.nist.gov/projects/cryptographic-standards-and-guidelines/example-values
 * - https://www.di-mgt.com.au/sha_testvectors.html
 */
typedef struct {

	/* repeat message N times */
	const size_t input_cnt;

	/* input message and it's length */
	const size_t input_len;
	const void *input;

	/* hash value */
	const char *hash_sha256;
	const char *hash_sha512_256;
	const char *hash_sha512;
} test_t;

static test_t TestArray[] = {
	{1, 0, "",
	 "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
	 "c672b8d1ef56ed28ab87c3622c5114069bdd3ad7b8f9737498d0c01ecef0967a",
	 "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a921d36ce9ce"
	 "47d0d13c5d85f2b0ff8318d2877eec2f63b931bd47417a81a538327af927da3e"},
	{1, 3, "abc",
	 "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
	 "53048e2681941ef99b2e29b76b4c7dabe4c2d0c634fc6d46e0e2f13107e7af23",
	 "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a"
	 "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f"},
	{1, 56,
	 "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
	 "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1",
	 "bde8e1f9f19bb9fd3406c90ec6bc47bd36d8ada9f11880dbc8a22a7078b6a461",
	 "204a8fc6dda82f0a0ced7beb8e08a41657c16ef468b228a8279be331a703c335"
	 "96fd15c13b1b07f9aa1d3bea57789ca031ad85c7a71dd70354ec631238ca3445"},
	{1, 64,
	 "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno",
	 "2ff100b36c386c65a1afc462ad53e25479bec9498ed00aa5a04de584bc25301b",
	 "835f9207766637f832cb3022f9d386b8b9426876f398d6b013a4925cc752806d",
	 "90d1bdb9a6cbf9cb0d4a7f185ee0870456f440b81f13f514f4561a0811276352"
	 "3033245875b68209bb1f5d5215bac81e0d69f77374cc44d1be30f58c8b615141"},
	{1, 112,
	 "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
	 "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
	 "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1",
	 "3928e184fb8690f840da3988121d31be65cb9d3ef83ee6146feac861e19b563a",
	 "8e959b75dae313da8cf4f72814fc143f8f7779c6eb9f7fa17299aeadb6889018"
	 "501d289e4900f7e4331b99dec4b5433ac7d329eeb6dd26545e96e55b874be909"},
	{1000 * 1000, 1, "a",
	 "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0",
	 "9a59a052930187a97038cae692f30708aa6491923ef5194394dc68d56c74fb21",
	 "e718483d0ce769644e2e42c7bc15b4638e1f98b13b2044285632a803afa973eb"
	 "de0ff244877ea60a4cb0432ce577c31beb009c5c2c49aa2e4eadb217ad8cc09b"},
#if 0
	{16 * 1024 * 1024, 64,
	 "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmno",
	 "50e72a0e26442fe2552dc3938ac58658228c0cbfb1d2ca872ae435266fcd055e",
	 "b5855a6179802ce567cbf43888284c6ac7c3f6c48b08c5bc1e8ad75d12782c9e",
	 "b47c933421ea2db149ad6e10fce6c7f93d0752380180ffd7f4629a712134831d"
	 "77be6091b819ed352c2967a2e2d4fa5050723c9630691f1a05a7281dbe6c1086"},
#endif
	{0, 0, "", "", "", ""}
};

const char *progname = "sha2-testing";
const char *VERSION = "0.1";
int opt_benchmark = 0;
int opt_functional = 0;
int opt_verbose = 0;
int opt_iterations = 1;

static void version(void)
{
	printf("%s version %s\n"
	       "\nCopyright (c) 2022 Tino Reichardt" "\n"
	       "\n", progname, VERSION);
	exit(0);
}

static void usage(void)
{
	printf("\n Usage: %s [OPTION]"
	       "\n"
	       "\n Options:"
	       "\n  -b    Benchmarking mode."
	       "\n  -f    Functional testing."
	       "\n  -h    Display a help and quit."
	       "\n  -v    Be more verbose."
	       "\n  -V    Show version information and quit."
	       "\n"
	       "\n Additional Options:"
	       "\n  -i N  Set number of iterations for testing (default: 1)."
	       "\n"
	       "\n Report bugs to: https://github.com/mcmilk/sha2-testing/issues"
	       "\n", progname);

	exit(0);
}

#define	SEC				1
#define	MILLISEC			1000
#define	NANOSEC				1000000000

#define	MSEC2NSEC(m)	((time_t)(m) * (NANOSEC / MILLISEC))
#define	NSEC2MSEC(n)	((n) / (NANOSEC / MILLISEC))

#define MSEC_PER_SEC	1000L
#define USEC_PER_SEC	1000000L
#define NSEC_PER_SEC	1000000000L

#if defined(__sun__)
static uint64_t my_gethrtime(void)
{
	return (uint64_t)gethrtime();
}
#else
static uint64_t my_gethrtime(void)
{
	struct timespec ts;
#ifdef CLOCK_MONOTONIC_RAW
	clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
#else
	clock_gettime(CLOCK_MONOTONIC, &ts);
#endif
	return (uint64_t) ((ts.tv_sec * NSEC_PER_SEC) + ts.tv_nsec);
}
#endif

typedef struct {
	uint64_t bs1k;
	uint64_t bs4k;
	uint64_t bs16k;
	uint64_t bs64k;
	uint64_t bs256k;
	uint64_t bs1m;
	uint64_t bs4m;
	const sha2_impl_ops_t *sha2;
} chksum_stat_t;

static unsigned char fmt_tohex(unsigned char c);
static unsigned char fmt_tohex(unsigned char c)
{
	return ((unsigned char)(c >= 10 ? c - 10 + 'a' : c + '0'));
}

static size_t fmt_hexdump(unsigned char *dest, const unsigned char *src,
			  size_t len);
static size_t fmt_hexdump(unsigned char *dest, const unsigned char *src,
			  size_t len)
{
	register const unsigned char *s = src;
	size_t written = 0, i;

	if (!dest)
		return ((len > ((size_t)-1) / 2) ? (size_t)-1 : len * 2);
	for (i = 0; i < len; ++i) {
		dest[written] = fmt_tohex(s[i] >> 4);
		dest[written + 1] = fmt_tohex(s[i] & 15);
		written += 2;
	}

	return (written);
}

void check_result(const char *ref, const char *res, int len)
{
	if (strncmp(ref, res, len) != 0) {
		printf("Wrong Result! %s != %s\n", ref, res);
		exit(1);
	}
}

void test_with(const sha2_impl_ops_t * sha2, int id)
{
	int i, j;
	void *buffer;
	size_t bufsize = 0;
	cycles_t start, stop;

	for (i = 0; TestArray[i].input_cnt; i++) {
		if (TestArray[i].input_len > bufsize)
			bufsize = TestArray[i].input_len;
	}

	if (opt_verbose)
		printf("\nRunning algorithm correctness tests for %s (%d)\n",
		       sha2->name, sha2->digest_len);

	buffer = malloc(bufsize);
	if (!buffer) exit(111);
	for (i = 0; TestArray[i].input_cnt; i++) {
		test_t *cur = &TestArray[i];
		void *ctx;
		size_t bytes = 0;

		unsigned char digest[32 + 1];
		unsigned char result[256 + 1];

		buffer = realloc(buffer, cur->input_len);
		memcpy(buffer, cur->input, cur->input_len);

		start = get_cycles();
		sha2->init(&ctx);
		for (j = 0; j < (int)cur->input_cnt; j++) {
			sha2->update(ctx, buffer, cur->input_len);
		}
		sha2->final(ctx, digest);
		stop = get_cycles();

		result[fmt_hexdump(result, digest, sha2->digest_len)] = 0;
		switch (id) {
		case ID_SHA256:
			check_result(cur->hash_sha256, (const char*)result,
				     sha2->digest_len);
			if (opt_verbose)
				printf("HASH-ref:  %s\n", cur->hash_sha256);
			break;
		case ID_SHA512_256:
			check_result(cur->hash_sha512_256, (const char*)result,
				     sha2->digest_len);
			if (opt_verbose)
				printf("HASH-ref:  %s\n", cur->hash_sha512_256);
			break;
		case ID_SHA512:
			check_result(cur->hash_sha512, (const char*)result,
				     sha2->digest_len);
			if (opt_verbose)
				printf("HASH-ref:  %s\n", cur->hash_sha512);
			break;
		}

		bytes = TestArray[i].input_cnt * TestArray[i].input_len;

		printf("%-23s: %s (%lu) bytes=%llu\n",
		       sha2->name, result, (unsigned long)(stop - start),
		       (long long unsigned)bytes);
	}

	free(buffer);
}

static void chksum_run(chksum_stat_t * cs, int round, uint64_t * result)
{
	uint64_t start;
	uint64_t run_bw, run_time_ns, run_count, size = 0;
	uint32_t l, loops = 0;
	void *ctx;
	void *buf;
	unsigned char md[64 * 2 + 1];
	int rv;

	switch (round) {
	case 1:		/* 1k */
		size = 1 << 10;
		loops = 128;
		break;
	case 2:		/* 2k */
		size = 1 << 12;
		loops = 64;
		break;
	case 3:		/* 4k */
		size = 1 << 14;
		loops = 32;
		break;
	case 4:		/* 16k */
		size = 1 << 16;
		loops = 16;
		break;
	case 5:		/* 256k */
		size = 1 << 18;
		loops = 8;
		break;
	case 6:		/* 1m */
		size = 1 << 20;
		loops = 4;
		break;
	case 7:		/* 4m */
		size = 1 << 22;
		loops = 1;
		break;
	}

	buf = malloc(size);
	if (!buf)
		exit(111);

	/* warmup */
	start = my_gethrtime();
	rv = cs->sha2->init(&ctx);

	/* method not useable */
	if (rv == -1) return;

	run_count = 0;
	do {
		for (l = 0; l < loops; l++, run_count++)
			cs->sha2->update(ctx, buf, size);

		run_time_ns = my_gethrtime() - start;
	} while (run_time_ns < MSEC2NSEC(1));
	cs->sha2->final(ctx, md);

	/* benchmark */
	start = my_gethrtime();
	cs->sha2->init(&ctx);
	run_count = 0;
	do {
		for (l = 0; l < loops; l++, run_count++)
			cs->sha2->update(ctx, buf, size);

		run_time_ns = my_gethrtime() - start;
	} while (run_time_ns < MSEC2NSEC(2));
	cs->sha2->final(ctx, md);
	run_time_ns = my_gethrtime() - start;

	free(buf);
	run_bw = size * run_count * NANOSEC;
	run_bw /= run_time_ns;	/* B/s */
	*result = run_bw / 1024 / 1024;	/* MiB/s */
}

static void chksum_benchit(chksum_stat_t * cs)
{
	if (cs->sha2->is_supported && (cs->sha2->is_supported() == 0))
		return;

	chksum_run(cs, 1, &cs->bs1k);
	chksum_run(cs, 2, &cs->bs4k);
	chksum_run(cs, 3, &cs->bs16k);
	chksum_run(cs, 4, &cs->bs64k);
	chksum_run(cs, 5, &cs->bs256k);
	chksum_run(cs, 6, &cs->bs1m);
	chksum_run(cs, 7, &cs->bs4m);

	printf("%-23s", cs->sha2->name);
	printf("%8llu", (unsigned long long)cs->bs1k);
	printf("%8llu", (unsigned long long)cs->bs4k);
	printf("%8llu", (unsigned long long)cs->bs16k);
	printf("%8llu", (unsigned long long)cs->bs64k);
	printf("%8llu", (unsigned long long)cs->bs256k);
	printf("%8llu", (unsigned long long)cs->bs1m);
	printf("%8llu\n", (unsigned long long)cs->bs4m);
}

static const sha2_impl_ops_t *sha256_impls[] = {
	&sha256_cifra_impl,
	&sha256_sbase_impl,
	&sha256_ltc_impl,
	&sha256_lzma_impl,
	&sha256_bsd_impl,
	&sha256_cppcrypto_impl,
#if defined(__aarch64__)
	&sha256_cppcrypto_arm_impl,
#endif
#if defined(__PPC64__)
	&sha256_cppcrypto_ppc64_impl,
#endif
#if defined(__x86_64)
	&sha256_cppcrypto_shani_impl,
	&sha256_cppcrypto_ssse3_impl,
	&sha256_cppcrypto_avx_impl,
	&sha256_cppcrypto_ni_impl,
#endif
	&sha256_openssl_impl,
	NULL
};

static const sha2_impl_ops_t *sha512_256_impls[] = {
	&sha512_256_sbase_impl,
	&sha512_256_bsd_impl,
	&sha512_256_cppcrypto_impl,
	NULL
};

static const sha2_impl_ops_t *sha512_impls[] = {
	&sha512_cifra_impl,
	&sha512_sbase_impl,
	&sha512_bsd_impl,
	&sha512_cppcrypto_impl,
#if defined(__PPC64__)
	&sha512_cppcrypto_ppc64_impl,
#endif
#if defined(__x86_64)
	&sha512_cppcrypto_ssse3_impl,
	&sha512_cppcrypto_avx2_impl,
	&sha512_cppcrypto_avx_impl,
#endif
	&sha512_openssl_impl,
	NULL
};

int main(int argc, char *argv[])
{
	chksum_stat_t cs;
	int i, opt;

	/* same order as in help option -h */
	while ((opt = getopt(argc, argv, "bfvVi:h?")) != -1) {
		switch (opt) {
		case 'b':	/* benchmark */
			opt_benchmark = 1;
			break;

		case 'f':	/* functional tests */
			opt_functional = 1;
			break;

		case 'v':	/* be more verbose */
			opt_verbose++;
			break;

		case 'V':	/* version */
			version();
			break;

		case 'i':	/* iterations */
			opt_iterations = atoi(optarg);
			break;

		case 'h':
		case '?':
		default:
			usage();
			/* not reached */
		}
	}

	/* use benchmarking if no parameter was used */
	if (!opt_functional && !opt_benchmark)
		opt_benchmark = 1;

	/* tests for correctness */
	if (opt_functional) {
		for (i = 0; sha256_impls[i]; i++) { test_with(sha256_impls[i], ID_SHA256); }
		for (i = 0; sha512_256_impls[i]; i++) { test_with(sha512_256_impls[i], ID_SHA512_256); }
		for (i = 0; sha512_impls[i]; i++) { test_with(sha512_impls[i], ID_SHA512); }
	}

	if (opt_benchmark) {
		/* header */
		printf("%-23s", "implementation");
		printf("%8s", "1k");
		printf("%8s", "4k");
		printf("%8s", "16k");
		printf("%8s", "64k");
		printf("%8s", "256k");
		printf("%8s", "1m");
		printf("%8s\n", "4m");
		int j;
		for (j = 0; j < opt_iterations; j++) {
			for (i = 0; sha256_impls[i]; i++) {
				cs.sha2 = sha256_impls[i];
				chksum_benchit(&cs);
			}

			printf("\n");
			for (i = 0; sha512_256_impls[i]; i++) {
				cs.sha2 = sha512_256_impls[i];
				chksum_benchit(&cs);
			}

			printf("\n");
			for (i = 0; sha512_impls[i]; i++) {
				cs.sha2 = sha512_impls[i];
				chksum_benchit(&cs);
			}
		}
	}

	return 0;
}
