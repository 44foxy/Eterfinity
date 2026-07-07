#include "StarTracer.h"

yufi infinity[infinity_size] = { 0 };

//#define __overhead_test__
//#define __deploy__

int main()
{
// <<<--------------------------------------->>>
	jump_imprint(decide)
		jump_if(!vpref(infi_heap), op_start);
		jump_if(!infi_acc(dat_reinit_count, ull), op_frequency_sweep);
#ifdef __overhead_test__
		jump_if(infi_acc(dat_reinit_count, ull)--, op_null);
#elif !__deploy__
		jump_if(!infi_acc(dat_test_var, ull), op_test);
		jump_if(infi_acc(dat_test_var, ull), op_test_1);
#else

#endif
	jump_phase(decide);
// <<<--------------------------------------->>>
// >>>
	jump_imprint(op_start)
		WSADATA wsa;
		WSAStartup(MAKEWORD(2, 2), &wsa);

		SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
		SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

		infi* affinityMask = 1llu << 0;
		SetProcessAffinityMask(GetCurrentProcess(), affinityMask);

		_memget_(infi_heap, infinity_heap_size);
		_memset_(vpref(infi_heap), 0, infinity_heap_size);

		jump_if(!vpref(infi_heap), op_infinity_memget_fail);

		infi_timer = __rdtsc();
	jump_phase(op_reinitialize);
// <<<
// >>>
	jump_imprint(op_reinitialize)
		infi_acc(dat_reinit_count, ull) = reinit_cnt;
		infi_timer = __rdtsc();
	jump_phase(decide);
// <<<
// >>>
	jump_imprint(op_infinity_memget_fail)
		log("Failed allocating memory space, exiting :::>>>\n");
		ExitProcess(1);
	jump_phase(decide);
// <<<
// >>>
	jump_imprint(op_frequency_sweep)
		infi_timer = ((__rdtsc() - infi_timer) / reinit_cnt);
		// AMD Ryzen 7 5800X 3.8GHz
		// __overhead__ => Frequency sweep: 1.90000e+09 Hz | cycle count: 2
		// !__overhead__ => Frequency sweep: 7.60000e+08 Hz | cycle count: 5 <OR> Frequency sweep: 6.33333e+08 Hz | cycle count: 6
		log("Frequency sweep: %.5e Hz | cycle count: %llu\n", 3.8e9 / infi_timer, infi_timer);
		jump_imprint(freq_input)
			jump_if(KEY_CODE_ESC, op_clean);
#ifdef __overhead_test__
			jump_if(1, op_reinitialize);
#else
			jump_if(KEY_CODE_0, op_reinitialize);
#endif
	jump_phase(freq_input);
// <<<
// >>>
	jump_imprint(op_test)
		infi_acc(dat_reinit_count, ull)--;
		infi_acc(dat_test_var, ull) = !infi_acc(dat_test_var, ull);
	jump_phase(decide);
// <<<
// >>>
	jump_imprint(op_test_1)
		infi_acc(dat_test_var, ull) = !infi_acc(dat_test_var, ull);
	jump_phase(decide);
// <<<
// >>>
	jump_imprint(op_clean)
		log("Exiting :::>>>\n");
		free(vpref(infi_heap));
		WSACleanup();
		ExitProcess(0);
	jump_phase(decide);
// <<<
// >>>
	jump_imprint(op_null)
		infi_acc(dat_test_var, ull)++;
	jump_phase(decide);
// <<<
}