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
	/* Systick Init */
	yy_systick_init();
	
	/* Uart Init */
	yy_uart_init();
	
	/* I2c Init (Slave) */
	yy_i2c_slave_init(I2C_TWI1, SLAVE_ADDRESS);
	yy_i2c_slave_interrupt_init(I2C_TWI1);
	
	/* GPIO Init */
	yy_gpio_init();
	
	

}
