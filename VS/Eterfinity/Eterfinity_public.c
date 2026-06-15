#include <intrin.h>
#include <stdio.h>
#include <Windows.h>

#define LOG
#define DBG

#ifdef LOG
#define log(str, ...) \
		printf(str, __VA_ARGS__)
#else 
#define dbglog(str, ...)
#endif

#ifdef DBG
#define dbglog(str, ...) \
		printf(str, __VA_ARGS__)
#else 
#define dbglog(str, ...)
#endif

typedef union uni
{
	char c;
	short s;
	long l;
	long long ll;
	char* cp;
	short* sp;
	long* lp;
	long long* llp;
	unsigned char uc;
	unsigned short us;
	unsigned long ul;
	unsigned long long ull;
	unsigned char* ucp;
	unsigned short* usp;
	unsigned long* ulp;
	unsigned long long* ullp;
	void* vp;
}uni;

typedef struct node_t
{
	char name[32];
	uni origin;
	uni forward;
	uni below;
	uni value;
}node_t;

uni mem; // memory
node_t* node; // current node
uni next; // right symbol from node
uni prev; // left symbol from node
uni temp; // temporary variables
uni orinode; // origin marker node

typedef enum ops { nop, oriori, nexori, orinex, nexnex, nexexe, exenex, nexvoi, voivoi, voinex, exeori }ops;
void _nop(); void _oriori(); void _nexori();  void _orinex(); void _nexnex(); void _nexexe(); void _exenex(); void _nexvoi(); void _voivoi(); void _voinex(); void _exeori();
void (*fops[11])() = { _nop, _oriori, _nexori, _orinex, _nexnex, _nexexe, _exenex, _nexvoi, _voivoi, _voinex, _exeori };

// route operation
#define routeop(l, r, op) \
	fops[(cmatch(cdref(prev), l) & cmatch(cdref(next), r)) * op]() 

// construct operation route
#define constructoproute(rt) \
	void _##rt() \
	{ \
		dbglog("routing --- %s >>> ", #rt); \
		nodeimprint; \
		dbglog("imprint --- %s\n", node->name); \
		temp.ll = 1;

#define WKEY(x) if(GetAsyncKeyState(x) >> 16)
#define KEY_CODE_ESC WKEY(27)
#define KEY_CODE_0 WKEY(96)
#define KEY_CODE_1 WKEY(97)
#define KEY_CODE_2 WKEY(98)
#define KEY_CODE_3 WKEY(99)
#define KEY_CODE_4 WKEY(100)

#define uniwrap(x) ((uni)x)
#define nodewrap(x) ((node_t*)x)
#define nodeorigin nodewrap(node->origin.vp)
#define nodeforward nodewrap(node->forward.vp)
#define nodebelow nodewrap(node->below.vp)
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

// memory size
#define MEM_S 1024ll * 1024ll * 1024ll

// Accelerated memory management >>>
#define ACCEL_VARS(size) \
	uni A; llref(A) = ((size) / 8); \
	uni B; llref(B) = ((size) - (llref(A) * 8)) / 4; \
	uni C;	llref(C) = ((size) - (llref(A) * 8 + llref(B) * 4)) / 2; \
	uni D; llref(D) = (size) % 2; \
	uni __i

#define arr_arr_copy(dst, src, type, i) (dst).type[i] = src.type[i]
#define arr_var_copy(dst, src, type, i) (dst).type[i] = *src.type
#define __i_A llref(__i)
#define __i_B llref(__i) + llref(A) * 2
#define __i_C llref(__i) + llref(A) * 4 + llref(B) * 2
#define __i_D llref(__i) + llref(A) * 8 + llref(B) * 4 + llref(C) * 2

#define ACCEL_COPY(dst, src, size) \
	{ \
		ACCEL_VARS(size); \
		for(llref(__i) = 0; llref(__i) < llref(A); llref(__i)++) { arr_arr_copy(dst, src, llp, __i_A); } \
		for(llref(__i) = 0; llref(__i) < llref(B); llref(__i)++) { arr_arr_copy(dst, src, lp, __i_B); } \
		for(llref(__i) = 0; llref(__i) < llref(C); llref(__i)++) { arr_arr_copy(dst, src, sp, __i_C); } \
		for(llref(__i) = 0; llref(__i) < llref(D); llref(__i)++) { arr_arr_copy(dst, src, cp, __i_D); } \
	}

#define ACCEL_SET(dst, src, size) \
	{ \
		ACCEL_VARS(size); \
		for(llref(__i) = 0; __i.ll < llref(A); llref(__i)++) { arr_var_copy(dst, src, llp, __i_A); } \
		for(llref(__i) = 0; __i.ll < llref(B); llref(__i)++) { arr_var_copy(dst, src, lp, __i_B); } \
		for(llref(__i) = 0; __i.ll < llref(C); llref(__i)++) { arr_var_copy(dst, src, sp, __i_C); } \
		for(llref(__i) = 0; __i.ll < llref(D); llref(__i)++) { arr_var_copy(dst, src, cp, __i_D); } \
	}

#define memget(uni, size) \
	uni.vp = malloc(size)

#define memset(dst, val, size) \
	{ \
		uni set; \
		uni set_p; \
		llref(set) = val; \
		llpref(set_p) = &llref(set); \
		ACCEL_SET(dst, set_p, size) \
	}

#define memcpy(dst, src, size) \
	{ \
		ACCEL_COPY(dst, src, size) \
	}

#define cmatch(l, r) \
	(__lzcnt64(l ^ r) >> 6)

#define nonalphanumerical(ap) \
	((cdref(ap) < 'a' || cdref(ap) > 'z') && (cdref(ap) < 'A' || cdref(ap) > 'Z') && (cdref(ap) < '0' || cdref(ap) > '9'))

// jump within next symbols
#define nextjumpforward \
{ \
	prev = next; \
	temp.ll = 0; \
	cpref(next)++; \
	while (1) { if(nonalphanumerical(next)) break; cpref(next)++; } \
}

// imprint node name into memory of current node
#define nodeimprint \
{\
	cpref(next)--; \
	cpref(prev)++; \
	uni dst; \
	dst.vp = node->name; \
	memset(dst, 0, 32); \
	memcpy(dst, prev, cpref(next) - cpref(prev) + 1) \
	nodeorigin = vpref(orinode); \
	cpref(next)++; \
}

// compare symbol differences
#define prevcomparenext(a, b) if (cmatch(cdref(prev), a) && cmatch(cdref(next), b))

#define nodegoforward (node++)
#define nodegobackward (node--)
#define nodejumporinode node = vpref(orinode);
#define nodejumporigin node = node->vpref(origin);
#define nodejumpforward node = node->vpref(forward);
#define nodejumpbelow node = node->vpref(below);

char enginecoretext[] =
"#mem>build"
		"#uni"
			">name>it|nodename"
			">give>it|nodevalue"
		"##"
		"#node"
			">name>it|nodename"
		"##"
"##"
">mem build uni name it testparam give it 8591"
">mem build node name it mynewnode"
">";

#define ENGINE_SIZ sizeof(enginecoretext)

void _nop() {}
constructoproute(oriori)

}
constructoproute(nexori)

}
constructoproute(orinex)

}
constructoproute(nexnex)

}
constructoproute(nexexe)

}
constructoproute(exenex)

}
constructoproute(nexvoi)

}
constructoproute(voivoi)

}
constructoproute(voinex)

}
constructoproute(exeori)

}

int main()
{
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	memget(mem, MEM_S);
	if (!vpref(mem))
		return 1;
	memset(mem, 0, MEM_S);

	node = vpref(mem);
	vpref(node->origin) = node;
	vpref(orinode) = node;
	cpref(next) = enginecoretext;

	uni now;
	now.ull = __rdtsc();

nextrun:
	KEY_CODE_ESC{ goto exit; };
	nextjumpforward;
	routeop('#', '#', oriori);
	routeop('>', '#', nexori);
	routeop('#', '>', orinex);
	routeop('>', '>', nexnex);
	routeop('>', '|', nexexe);
	routeop('|', '>', exenex);
	routeop('>', ' ', nexvoi);
	routeop(' ', ' ', voivoi);
	routeop(' ', '>', voinex);
	routeop('|', '#', exeori);
	if (temp.ll == 0)
		goto protofail;
	goto nextrun;

protofail:
	log("Parse time --- %llu\n", __rdtsc() - now.ull);
	log("Proto Fail--->\n");
	while (1)
	{
		KEY_CODE_0
		{
			log("Engine re-init in 1 second>>>\n");
			Sleep(1000);
			cpref(next) = enginecoretext;
			now.ull = __rdtsc();
			goto nextrun;
		}
		KEY_CODE_ESC
		{
			goto exit;
		}
		Sleep(20);
	}

exit:
	log("Exiting>>>\n");
	free(vpref(mem));
}