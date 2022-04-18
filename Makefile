.PHONY: all

all: sha2_tests

CC	= gcc
#CC	= clang

CFLAGS	= -O2 -Wall

CIFRA	= cifra/blockwise.o cifra/sha256.o cifra/sha512.o
SBASE	= sbase/sha256.o sbase/sha512-256.o sbase/sha512.o
FREEBSD	= freebsd/sha256c.o freebsd/sha512c.o
CPPCR	= cppcrypto/Sha2.o
LZMA	= lzma/sha256.o
TOMCRYPT= tomcrypt/sha2.o

# undef, when not available
#SHANI	= noloader/Sha2.o
#CFLAGS	+= -msha -msse4.1 -DHAVE_SHANI

OBJS	= impl_bsd.o impl_cifra.o impl_openssl.o impl_sbase.o \
	  impl_cppcrypto.o impl_cppcrypto2.o impl_lzma.o impl_tomcrypt.o \
	  sha2_tests.o
OBJS	+= $(CIFRA) $(SBASE) $(FREEBSD) $(CPPCR) $(SHANI) $(LZMA) $(TOMCRYPT)

sha2_tests: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o sha2_tests
	#-lcrypto

clean:
	rm -f $(OBJS) sha2_tests
