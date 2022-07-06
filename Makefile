.PHONY: all

all: sha2_tests

update:
	git checkout .
	git pull

CC	= gcc
#CC	= clang

CFLAGS	= -Os -Wall

CIFRA	= cifra/blockwise.o cifra/sha256.o cifra/sha512.o
SBASE	= sbase/sha256.o sbase/sha512-256.o sbase/sha512.o
FREEBSD	= freebsd/sha256c.o freebsd/sha512c.o
CPPCR	= cppcrypto/sha256.o cppcrypto/sha512.o cppcrypto/sha2-generic.o
LZMA	= lzma/sha256.o
TOMCRYPT= tomcrypt/sha2.o

OBJS	= impl_bsd.o impl_cifra.o impl_openssl.o impl_sbase.o \
	  impl_cppcrypto.o impl_lzma.o impl_tomcrypt.o \
	  sha2_tests.o
OBJS	+= $(CIFRA) $(SBASE) $(FREEBSD) $(CPPCR) $(LZMA) $(TOMCRYPT)

HOSTTYPE := $(shell uname -m)
ifeq (,$(HOSTTYPE))
    $(error HOSTTYPE undefined)
endif

ifeq (i686,$(HOSTTYPE))
OBJS	+= cppcrypto/sha2-shani-x32.o
CFLAGS	+= -msha -msse4
endif

ifeq (x86_64,$(HOSTTYPE))
OBJS	+= intel/sha256_ssse3.o
OBJS	+= intel/sha512_ssse3.o
OBJS	+= intel/sha256_avx.o
OBJS	+= intel/sha256_ni.o
OBJS	+= intel/sha512_avx2.o
OBJS	+= intel/sha512_avx.o
#OBJS	+= cppcrypto/sha2-shani-x64.o
#OBJS	+= cppcrypto/sha256-sse.o
#OBJS	+= cppcrypto/sha256_compress_x86_64_avx.o
#OBJS	+= cppcrypto/sha256_compress_x86_64_avx2.o
#OBJS	+= cppcrypto/sha256_compress_x86_64_avx512.o
#OBJS	+= cppcrypto/sha512_compress_x86_64_avx.o
#OBJS	+= cppcrypto/sha512_compress_x86_64_avx2.o
#OBJS	+= cppcrypto/sha512_compress_x86_64_avx512.o
#CFLAGS	+= -msha -msse4
endif

ifeq (aarch64,$(HOSTTYPE))
OBJS	+= cppcrypto/sha256-aarch64.o
OBJS	+= cppcrypto/sha512-aarch64.o
ASFLAGS	+= -march=armv8-a+crypto+sha3
endif

ifeq (ppc64,$(HOSTTYPE))
OBJS	+= cppcrypto/sha256-ppc64.o cppcrypto/sha512-ppc64.o
CFLAGS	+= -mcpu=power8
endif

ifeq (ppc64le,$(HOSTTYPE))
OBJS	+= cppcrypto/sha256-ppc64le.o cppcrypto/sha512-ppc64le.o
CFLAGS	+= -mcpu=power8
endif

sha2_tests: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o sha2_tests -lcrypto

clean:
	rm -f $(OBJS) sha2_tests
