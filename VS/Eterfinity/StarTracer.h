#pragma once
#include "StarTracerMap.h"
#include <intrin.h>
#include <stdio.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

// data handling >>>
	typedef unsigned long long infi;

	#define infinity_size (1ull << 15ull)
	#define infinity_heap_size (1ull << 30ull)

	typedef union yufi
	{
		char c; short s; long l; long long ll; char* cp; short* sp; long* lp; long long* llp;
		unsigned char uc; unsigned short us; unsigned long ul; unsigned long long ull; 
		unsigned char* ucp; unsigned short* usp; unsigned long* ulp; unsigned long long* ullp;
		void* vp; float fl; float* flp; double d; double* dp;
		void (*fp)();
	}yufi;

	extern yufi infinity[infinity_size];
// <<<

// data type referencing >>>
	#define cdref(x) (*(x).cp)
	#define sdref(x) (*(x).sp)
	#define ldref(x) (*(x).lp)
	#define lldref(x) (*(x).llp)
	#define vpref(x) x.vp
	#define cpref(x) x.cp
	#define spref(x) x.sp
	#define lpref(x) x.lp
	#define llpref(x) x.llp
	#define cref(x) x.c
	#define sref(x) x.s
	#define lref(x) x.l
	#define llref(x) x.ll
	#define ullref(x) x.ull
	#define fpref(x) x.fp
// <<<

// memory control >>>
	#define accel_vars(size) \
		yufi A; llref(A) = ((size) / 8); \
		yufi B; llref(B) = ((size) - (llref(A) * 8)) / 4; \
		yufi C;	llref(C) = ((size) - (llref(A) * 8 + llref(B) * 4)) / 2; \
		yufi D; llref(D) = (size) % 2; \
		yufi __i

	#define arr_arr_copy(dst, src, type, i) (dst).type[i] = src.type[i]
	#define arr_var_copy(dst, src, type, i) (dst).type[i] = *src.type
	#define __i_A llref(__i)
	#define __i_B llref(__i) + llref(A) * 2
	#define __i_C llref(__i) + llref(A) * 4 + llref(B) * 2
	#define __i_D llref(__i) + llref(A) * 8 + llref(B) * 4 + llref(C) * 2

	#define _memcpy_(dst, src, size) \
		{ \
			accel_vars(size); \
			for(llref(__i) = 0; ((llref(__i) - llref(A)) >> 63); llref(__i)++) { arr_arr_copy(dst, src, llp, __i_A); } \
			for(llref(__i) = 0; ((llref(__i) - llref(B)) >> 63); llref(__i)++) { arr_arr_copy(dst, src, lp, __i_B); } \
			for(llref(__i) = 0; ((llref(__i) - llref(C)) >> 63); llref(__i)++) { arr_arr_copy(dst, src, sp, __i_C); } \
			for(llref(__i) = 0; ((llref(__i) - llref(D)) >> 63); llref(__i)++) { arr_arr_copy(dst, src, cp, __i_D); } \
		}

	#define accel_set(dst, src, size) \
		{ \
			accel_vars(size); \
			for(llref(__i) = 0; (llref(__i) - llref(A)) >> 63; llref(__i)++) { arr_var_copy(dst, src, llp, __i_A); } \
			for(llref(__i) = 0; (llref(__i) - llref(B)) >> 63; llref(__i)++) { arr_var_copy(dst, src, lp, __i_B); } \
			for(llref(__i) = 0; (llref(__i) - llref(C)) >> 63; llref(__i)++) { arr_var_copy(dst, src, sp, __i_C); } \
			for(llref(__i) = 0; (llref(__i) - llref(D)) >> 63; llref(__i)++) { arr_var_copy(dst, src, cp, __i_D); } \
		}

	#define _memget_(yuf, size) \
		yuf.vp = malloc(size)

	#define _memset_(dst, val, size) \
		{ \
			yufi ds; \
			vpref(ds) = dst; \
			yufi set; \
			yufi set_p; \
			llref(set) = val; \
			llpref(set_p) = &llref(set); \
			accel_set(ds, set_p, size) \
		}
// <<<

// arithmetic flow control >>>
	#define match(a, b) \
		(!(a ^ b))

	#define lower(a, b, type)\
		((((type)((a) - (b))) >> ((sizeof(type) << 3) - 1)) & 1)

	#define higher(a, b, type)\
		lower(b, a, type)

	#define lowereq(a, b, type)\
		lower(a, b + 1, type)

	#define highereq(a, b, type)\
		higher(a + 1, b, type)

	#define range(c, from, to, type) \
		(highereq(c, from, type) & lowereq(c, to, type))

	#define non_alphanumerical(c) \
		(!(range(c, 'a', 'z', char) | range(c, 'A', 'Z', char) | range(c, '0', '9', char)))
// <<<

// input handling >>>
	#define WKEY(x) ((GetAsyncKeyState(x) >> 16) & 1)
	#define KEY_CODE_ESC	WKEY(27)
	#define KEY_CODE_0		WKEY(96)
	#define KEY_CODE_1		WKEY(97)
	#define KEY_CODE_2		WKEY(98)
	#define KEY_CODE_3		WKEY(99)
	#define KEY_CODE_4		WKEY(100)
// <<<

// compile time debugging options >>>
	#define LOG // console logging - opt
	//#define DBG // console debug logging - opt
	//#define DELAY // delay toggle - opt

	#ifdef LOG
		#define log(str, ...) \
			printf(str, __VA_ARGS__)
	#else 
		#define log(str, ...)
	#endif

	#ifdef DBG
		#define dbglog(str, ...) \
			printf(str, __VA_ARGS__)
	#else 
		#define dbglog(str, ...)
	#endif

	#ifdef DELAY
		#define delay(ms) \
			Sleep(ms)
	#else 
		#define delay(ms)
	#endif
// <<<

// currently expanding / experimenting >>>----------------------------------------------------->>>

// StarTracer jump section >>>
	#define jump_build(name) \
		void ___##name()

	#define jump_link(name) \
		extern void ___##name();\
		ullref(infinity[name]) = ___##name;

	#define jump_acc \
		ullref(infinity[infi_pos_jump])

	#define jump_set_if_zero(cmd, route) \
		jump_acc |= (~!jump_acc + 1ull) & (~cmd + 1ull) & route

	#define jumpzero \
		jump_acc = 0

	#define jump_set(x) \
		jump_acc = x

	#define jump_to_decision(name) \
		jump_set_if_zero(!!infi_reinit_cnt_acc, reinitialize); \
		jump_set_if_zero(1, fail); \
		infinity[jump_acc].fp(); \
		goto name
// <<<

// virtual memory access >>>
	#define infi_user_acc(pos, type) \
		infinity[infi_pos_usrdata + pos].type

	#define infi_heap infinity[infi_pos_heap]

	#define infi_heap_acc(pos, type) \
		((yufi*)&infinity[infi_pos_heap].llp[pos])->type

	#define timer_acc \
		ullref(infinity[infi_pos_timer])
// <<<

// reinitialization capability (for profiling sustained compute) >>>
	#define reinit_cnt \
		1'000'000

	#define infi_reinit_cnt_acc \
		ullref(infinity[infi_pos_reinitcnt])
// <<<