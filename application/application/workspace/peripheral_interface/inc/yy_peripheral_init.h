/*
 * yy_peripheral_init.h
 *
 * Created: 2025/4/2 下午 02:21:56
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_PERIPHERAL_INIT_H_
#define YY_PERIPHERAL_INIT_H_
/* include */
#include "yy_uart_api.h"
#include "yy_flash_api.h"
#include "yy_systick_api.h"
#include "yy_rstc_api.h"
#include "yy_i2c_api.h"
#include "yy_i2c_slave_interrupt.h"
#include "yy_gpio_api.h"
#include "yy_delay_api.h"

/* Prototype */
void yy_peripheral_init();

#endif /* YY_PERIPHERAL_INIT_H_ */