#include "startracer_esp.h"
#include "lwip/sockets.h"
#include "esp_cpu.h"
yufi infinity[infinitysize] = { 0 };
buildjump(startcst)
{
    infireinitcnt++;
	jumpset(reinitialize);
	timeracc = esp_cpu_get_cycle_count();
}
buildjump(fail)
{
	log("Fail --- decider average cycle count until failing: %lu  :::>>>\n", ((esp_cpu_get_cycle_count() - timeracc) / reinitcnt));
	infireinitcnt = reinitcnt;
	infireinitcnt++;
	jumpset(fail_input);
}
buildjump(fail_input)
{
	jumpzero;
	jumpsetifzero(1, reinitialize);
	timeracc = esp_cpu_get_cycle_count();
}
buildjump(reinitialize)
{
	infiacc(0, ul) = 0; // test harness - opt
	infireinitcnt--;
	jumpzero;
}
buildjump(exe_test_1)
{
	dbglog("Executed test route 1 >>>\n");
	infiacc(0, ul)++; // "heavy" work
	jumpset(exe_test_2);
}
buildjump(exe_test_2)
{
	dbglog("Executed test route 2 >>>\n");
	infiacc(0, ul)++;  // "heavy" work
	jumpset(exe_test_3);
}
buildjump(exe_test_3)
{
	dbglog("Executed test route 3 >>>\n");
	infiacc(0, ul)++;  // "heavy" work
	jumpzero;
}
int app_main()
{
    printf("Engaging StarTracer :::>>>\n");

	linkjump(startcst);
	linkjump(fail);
	linkjump(fail_input);
	linkjump(reinitialize);
	linkjump(exe_test_1);
	linkjump(exe_test_2);
	linkjump(exe_test_3);

	infireinitcnt = reinitcnt;

	jumpset(startcst);
	goto jump_test_harness; // testing
jump_overhead: // 54 cycles
	while(1){
		jumpdecision;
	}
	goto jump_overhead;

jump_test_harness: // 276 cycles 
	while(1){
		jumpsetifzero(match(infiacc(0, ul), 0ul), exe_test_1);
		jumpdecision;
	}
	goto jump_test_harness;
}