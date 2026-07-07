#include "startracer.h"

yufi infinity[infinity_size] = { 0 };

jump_build(start)
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	
	infi* affinityMask = 1llu << 0;
	SetProcessAffinityMask(GetCurrentProcess(), affinityMask);

	_memget_(infi_heap, infinity_heap_size);
	_memset_(vpref(infi_heap), 0, infinity_heap_size);
	
	jumpzero;
	jump_set_if_zero(!!vpref(infi_heap), reinitialize);
	jump_set_if_zero(1, infinity_memget_fail);
	
	infi_reinit_cnt_acc = reinit_cnt;
	infi_reinit_cnt_acc++;
	
	timer_acc = __rdtsc();
}

jump_build(infinity_memget_fail)
{
	log("Failed allocating memory space, exiting :::>>>\n");
	ExitProcess(1);
}

jump_build(fail)
{
	log("Fail --- average cycle count per reinitialization: %llu  :::>>>\n", ((__rdtsc() - timer_acc) / reinit_cnt));
	infi_reinit_cnt_acc = reinit_cnt;
	infi_reinit_cnt_acc++;
	jump_set(fail_input);
}

jump_build(fail_input)
{
	jumpzero;
	jump_set_if_zero(KEY_CODE_0, reinitialize);
	jump_set_if_zero(KEY_CODE_ESC, clean);
	jump_set_if_zero(1, fail_input);
	delay(20);
	timer_acc = __rdtsc();
}

jump_build(reinitialize)
{
	infi_user_acc(0, ull) = 0; // test harness - opt
	infi_reinit_cnt_acc--;
	jumpzero;
}

jump_build(clean)
{ 
	log("Exiting :::>>>\n");
	free(vpref(infi_heap));
	WSACleanup();
	ExitProcess(0);
}

jump_build(exe_test_1)
{
	dbglog("Executed test route 1 >>>\n");
	infi_user_acc(0, ull)++;
	jumpzero;
}

jump_build(exe_test_2)
{
	dbglog("Executed test route 2 >>>\n");
	infi_user_acc(0, ull)++;
	jumpzero;
}

jump_build(exe_test_3)
{
	dbglog("Executed test route 3 >>>\n");
	infi_user_acc(0, ull)++;
	jumpzero;
}