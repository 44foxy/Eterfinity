#include "StarTracer.h"
int main()
{
	jump_link(start);
	jump_link(infinity_memget_fail);
	jump_link(fail);
	jump_link(fail_input);
	jump_link(reinitialize);
	jump_link(clean);
	jump_link(exe_test_1);
	jump_link(exe_test_2);
	jump_link(exe_test_3);

	jump_set(start);

	//goto jump_test_harness; // comment for overhead test, uncomment for harness test

jump_overhead: // 5-6 cycles output log -- Ryzen 7 5800X
	jump_to_decision(jump_overhead);

jump_test_harness: // 35-36 cycles output log -- Ryzen 7 5800X
	jump_set_if_zero(match(infi_user_acc(0, ull), 0ull), exe_test_1);
	jump_set_if_zero(match(infi_user_acc(0, ull), 1ull), exe_test_2);
	jump_set_if_zero(match(infi_user_acc(0, ull), 2ull), exe_test_3);
	jump_to_decision(jump_test_harness);
}