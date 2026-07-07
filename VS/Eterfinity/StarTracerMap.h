#pragma once

// currently expanding / experimenting >>>----------------------------------------------------->>>

// memory layout >>>
	// testing >>>
		#define	REG0 0
		#define	REG1 1
		#define	REG2 2
		#define	REG3 4
		#define	REG4 5
		#define	REG5 6
		#define	REG6 7
		#define	REG7 8
	// <<<
	#define infi_pos_jump 32
	#define infi_pos_heap 33
	#define infi_pos_reinitcnt 34
	#define infi_pos_timer 35
	#define infi_pos_fncdata 64
	#define infi_pos_usrdata 128
// <<<

// execution layout >>>
	typedef enum eop
	{
		start = infi_pos_fncdata,
		infinity_memget_fail,
		fail,
		fail_input,
		reinitialize,
		clean,
		exe_test_1,
		exe_test_2,
		exe_test_3,
	}eop;
// <<<