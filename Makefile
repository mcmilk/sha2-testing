.PHONY: all clean

all: clean sha2_tests

CC	= clang
#CC	= gcc
#CFLAGS	= -g -O2 -mavx 
CFLAGS	= -O2
# gcc -mavx -c sha256_vectorized.c

CIFRA	= cifra/blockwise.o cifra/sha256.o cifra/sha512.o
SBASE	= sbase/sha256.o sbase/sha512-256.o sbase/sha512.o
FREEBSD	= freebsd/sha256c.o freebsd/sha512c.o
CPPCR	= cppcrypto/Sha2.o

OBJS	= impl_bsd.o impl_cifra.o impl_openssl.o impl_sbase.o \
	  impl_cppcrypto.o sha2_tests.o
OBJS	+= $(CIFRA) $(SBASE) $(FREEBSD) $(CPPCR)

sha2_tests: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o sha2_tests -lcrypto

clean:
	rm -f $(OBJS) sha2_tests
