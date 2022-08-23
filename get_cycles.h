
/*
 * Copyright (c) 2022 Tino Reichardt <milky-zfs@mcmilk.de>
 */

#ifndef _SYS_GET_CYCLES_H
#define _SYS_GET_CYCLES_H

#ifdef __cplusplus
extern "C" {
#endif

/* cycle counter for various platforms
 *
 * usage:
 * cycles_t c_start, c_stop;
 * c_start = get_cycles();
 * <some code to test>
 * c_stop = get_cycles();
 * printf("ticks needed for code are: %u\n", c_stop - c_start);
 */
#if defined(__i386__)
typedef unsigned long long cycles_t;
static inline cycles_t get_cycles(void)
{
	cycles_t tick;
	asm volatile ("rdtsc":"=A" (tick));
	return tick;
}
#elif defined(__x86_64__)
typedef unsigned long long cycles_t;
static inline cycles_t get_cycles(void)
{
	unsigned int tickl, tickh;
	asm volatile ("rdtsc":"=a" (tickl), "=d"(tickh));
	return ((cycles_t) tickh << 32) | tickl;
}
#elif defined(__s390__)
typedef unsigned long long cycles_t;
static inline cycles_t get_cycles(void)
{
	cycles_t tick;
	asm volatile ("stck %0":"=Q" (tick)::"cc");
	return tick >> 2;
}
#elif defined(__alpha__)
typedef unsigned int cycles_t;
static inline cycles_t get_cycles(void)
{
	unsigned int tick;
	asm volatile ("rpcc %0":"=r" (tick));
	return tick;
}
#elif defined(__sparc__)
typedef long long cycles_t;
static inline cycles_t get_cycles(void)
{
	long long tick;
	asm volatile ("rd %%tick,%0":"=r" (tick));
	return tick;
}
#elif defined(_MSC_VER)
#include <intrin.h>
#pragma intrinsic(__rdtsc)
typedef unsigned __int64 cycles_t;
static inline cycles_t get_cycles(void)
{
	return __rdtsc();
}
#elif defined(HAVE_ARMV7A_CNTVCT)
typedef uint64_t ticks;
static inline ticks getticks(void)
{
	uint32_t Rt, Rt2 = 0;
	asm volatile("mrrc p15, 1, %0, %1, c14" : "=r"(Rt), "=r"(Rt2));
	return (((uint64_t)Rt) | (((uint64_t)Rt2) << 32));
}
#elif defined(HAVE_ARMV7A_PMCCNTR)
typedef uint64_t ticks;
static inline ticks getticks(void)
{
	uint32_t r;
	asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r));
	return r;
}
#else
typedef uint64_t cycles_t;
static inline cycles_t get_cycles(void)
{
	return 0;
}
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SYS_GET_CYCLES_H */
