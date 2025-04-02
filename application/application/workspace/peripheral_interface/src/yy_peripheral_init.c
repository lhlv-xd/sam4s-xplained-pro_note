/*
 * yy_peripheral_init.c
 *
 * Created: 2025/4/2 下午 02:21:47
 *  Author: Yuyi_Chen
 */ 
#include <asf.h>
#include "yy_peripheral_init.h"



void yy_peripheral_init()
{
	sysclk_init();
	/* Uart Init */
	yy_uart_init();
}
