#pragma once
#include <stdio.h>
#define infinitysize 512 
typedef unsigned long infi;
#define iw(x) ((infi)(x))
typedef union yufi
{
	char c; short s; long l; char* cp; short* sp; long* lp;
	unsigned char uc; unsigned short us; unsigned long ul;
	unsigned char* ucp; unsigned short* usp; unsigned long* ulp;
	void* vp; float fl; float* flp;
	void (*fp)();
}yufi;

// adding yufi handling on only what is needed
#define cdref(x) (*(x).cp)
#define sdref(x) (*(x).sp)
#define ldref(x) (*(x).lp)
#define vpref(x) x.vp
#define cpref(x) x.cp
#define spref(x) x.sp
#define lpref(x) x.lp
#define cref(x) x.c
#define sref(x) x.s
#define lref(x) x.l
#define ulref(x) x.ul
#define fpref(x) x.fp

// hardware saturating memory control >>>
#define ACCEL_VARS(size) \
	yufi B; lref(A) = ((size) / 4); \
	yufi C;	lref(B) = ((size) - (lref(B) * 4)) / 2; \
	yufi D; lref(C) = (size) % 2; \
	yufi __i

#define arr_arr_copy(dst, src, type, i) (dst).type[i] = src.type[i]
#define arr_var_copy(dst, src, type, i) (dst).type[i] = *src.type
#define __i_A lref(__i)
#define __i_B lref(__i) + lref(A) * 2
#define __i_C lref(__i) + lref(A) * 4 + lref(B) * 2

#define memcpy_n(dst, src, size) \
	{ \
		ACCEL_VARS(size); \
		for(lref(__i) = 0; ((lref(__i) - lref(A)) >> 63); lref(__i)++) { arr_arr_copy(dst, src, lp, __i_A); } \
		for(lref(__i) = 0; ((lref(__i) - lref(B)) >> 63); lref(__i)++) { arr_arr_copy(dst, src, sp, __i_B); } \
		for(lref(__i) = 0; ((lref(__i) - lref(C)) >> 63); lref(__i)++) { arr_arr_copy(dst, src, cp, __i_C); } \
	}

#define ACCEL_SET(dst, src, size) \
	{ \
		ACCEL_VARS(size); \
		for(lref(__i) = 0; (lref(__i) - lref(A)) >> 63; lref(__i)++) { arr_var_copy(dst, src, lp, __i_A); } \
		for(lref(__i) = 0; (lref(__i) - lref(B)) >> 63; lref(__i)++) { arr_var_copy(dst, src, sp, __i_B); } \
		for(lref(__i) = 0; (lref(__i) - lref(C)) >> 63; lref(__i)++) { arr_var_copy(dst, src, cp, __i_C); } \
	}

#define memset_n(dst, val, size) \
	{ \
		yufi ds; \
		vpref(ds) = dst; \
		yufi set; \
		yufi set_p; \
		lref(set) = val; \
		lpref(set_p) = &lref(set); \
		ACCEL_SET(ds, set_p, size) \
	}
// <<<
// "magic of bit arithmetic" >>>
#define match(l, r) \
	(__builtin_clz(l ^ r) >> 5)

#define clower(ap, c)\
	(((((signed char)cdref(ap)) - ((signed char)(c))) >> 7) & 1)

#define chigher(ap, c)\
	clower(c, ap)

#define clowereq(ap, c)\
	clower(ap, c + 1)

#define chighereq(ap, c)\
	chigher(ap + 1, c)

#define range(ap, from, to) \
	(chighereq(ap, from) & clowereq(ap, to))

#define nonalphanumerical(ap) \
	(!(range(ap, 'a', 'z') | range(ap, 'A', 'Z') | range(ap, '0', '9')))
// macros have the most incredible debugging capabilities in existence >>>
#define LOG // console logging - opt
//#define DBG // console debug logging - opt
//#define DELAY // delay toggle - opt

#ifdef LOG
#define log(str, ...) \
	printf(str, __VA_ARGS__)
#define log_s(str) \
	printf(str)
#else 
#define log(str, ...)
#define log_s(str)
#endif

#ifdef DBG
#define dbglog(str, ...) \
	printf(str, __VA_ARGS__)
#define dbglog_s(str) \
	printf(str)
#else 
#define dbglog(str, ...)
#define dbglog_s(str)
#endif

#ifdef DELAY
#define delay(ms) \
	Sleep(ms)
#else 
#define delay(ms)
#endif
// <<<
// currently expanding >>>----------------------------------------------------->>>

#define IFPOS_jump 0
#define IFPOS_reinitcnt 1
#define IFPOS_timer 2
#define IFPOS_fncdata 32
#define IFPOS_usrdata 128

// StarTracer jump architecture >>>
typedef enum eop
{
	startcst = IFPOS_fncdata,
	infinity_memget_fail,
	fail,
	fail_input,
	reinitialize,
	clean,
	exe_test_1,
	exe_test_2,
	exe_test_3,
}eop;
void _startcst();
void _fail();
void _fail_input();
void _reinitialize();
void _exe_test_1();
void _exe_test_2();
void _exe_test_3();

#define buildjump(name) \
	void _##name()

#define linkjump(name) \
	ulref(infinity[name]) = iw(_##name);

#define jump \
	ulref(infinity[IFPOS_jump])

#define jumpsetifzero(cmd, route) \
	jump |= (~!jump + 1ul) & (~cmd + 1ul) & route // little thought black magic~

#define jumpzero \
	jump = 0

#define jumpset(x) \
	jump = x

#define jumpdecision \
	jumpsetifzero(!!infireinitcnt, reinitialize); \
	jumpsetifzero(1, fail); \
	infinity[jump].fp()
// <<<
// virtual memory access >>>
#define infiacc(pos, type) \
	infinity[IFPOS_usrdata + pos].type

#define timeracc \
	ulref(infinity[IFPOS_timer])
// <<<
// reinitialization capability >>>
#define reinitcnt \
	1000

#define infireinitcnt \
	ulref(infinity[IFPOS_reinitcnt])
// <<<