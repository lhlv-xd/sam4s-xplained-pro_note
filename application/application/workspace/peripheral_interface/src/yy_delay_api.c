/*
 * yy_delay_api.c
 *
 * Created: 2025/5/19 下午 02:50:54
 *  Author: Yuyi_Chen
 */ 

#include "asf.h"
#include "yy_delay_api.h"
#include "yy_peripheral_init.h"

void yy_delay_1s_by_for()
{
	for (uint32_t i = 0; i < DELAY_1S_TIMES; i++) {
		__NOP();
	}
}

void yy_delay_1s_by_while()
{
	uint32_t clock_hz = sysclk_get_cpu_hz(); // 120MHz
	int timeout = clock_hz / 4;
	//int timeout = DELAY_1S_TIMES;
	
	while (timeout--) {
		__NOP();
	}
}