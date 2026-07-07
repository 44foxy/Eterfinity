#pragma once

// currently expanding / experimenting >>>----------------------------------------------------->>>

// execution layout >>>
	typedef enum eop
	{
		op_start,
		op_infinity_memget_fail,
		op_fail,
		op_fail_input,
		op_reinitialize,
		op_clean,
		op_start_http_server,
		op_frequency_sweep,
		op_test,
		op_test_1,
		op_null
	}eop;
// <<<

// infinity layout >>>
	typedef enum einfilayout
	{
		// infinity processor section
		REG0,
		REG1,
		REG2,
		REG3,
		REG4,
		REG5,
		REG6,
		REG7,
		// internal section
		heap = 64,
		reinit_count,
		timer,
		// data section
		dat_socket_http_server = 128,
		dat_test_var,
		dat_reinit_count,
	}eop;
// <<<