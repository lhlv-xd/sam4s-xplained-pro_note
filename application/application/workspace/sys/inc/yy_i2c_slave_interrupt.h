/*
 * yy_i2c_slave_interrupt.h
 *
 * Created: 2025/4/16 下午 06:26:45
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_I2C_SLAVE_INTERRUPT_H_
#define YY_I2C_SLAVE_INTERRUPT_H_

#include <asf.h>
#include "yy_i2c_slave_interrupt.h"
#include "yy_peripheral_init.h"

/* User Config */
#define I2C_SLAVE_HANDLER TWI1_Handler
#define I2C_SLAVE_INTERFACE TWI1

/* Extern */
// Page
extern volatile uint8_t BasicPage[128];
extern volatile uint8_t Page00h[128];
extern volatile uint8_t Page01h[128];





#endif /* YY_I2C_SLAVE_INTERRUPT_H_ */