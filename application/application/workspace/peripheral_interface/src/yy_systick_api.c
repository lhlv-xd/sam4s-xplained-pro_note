/*
 * yy_systick_api.c
 *
 * Created: 2025/4/8 下午 04:18:55
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yy_systick_api.h"
#include "yy_peripheral_init.h"

/* variable */
volatile static uint32_t tick_counter;

/** 
 * @brief Systick Init 
 */
void yy_systick_init(void) 
{
	#define SYSTEM_CLOCK_FREQ SystemCoreClock
	#define TICK_FREQ 1000
	
	SysTick->LOAD = (SYSTEM_CLOCK_FREQ / TICK_FREQ) - 1;
	SysTick->VAL = 0UL;
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Handler(void) 
{
	tick_counter++;
}

/** 
 * @brief get ticket
 */
uint32_t yy_get_systick(void) 
{
	return tick_counter;
}

/** 
 * @brief test systick features
 */
void test_systick_api()
{
	uint32_t start, end;
	start = yy_get_systick();
	//delay_ms(1000);
	yy_delay_1s_by_while();
	end = yy_get_systick();
	
	printf("timer: %d (ms)\r\n", end - start);
	
}