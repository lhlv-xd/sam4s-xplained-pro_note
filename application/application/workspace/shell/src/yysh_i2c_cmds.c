/*
 * yysh_i2c_cmds.c
 *
 * Created: 2025/5/23 下午 01:20:01
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yysh_i2c_cmds.h"
#include "yysh_customization_cmds.h"

/** 
 * @Brief Disable I2C slave
 */
void yysh_i2c_slave_disable(void *data)
{
	yy_i2c_slave_interrupt_deinit(I2C_TWI1);
}


/** 
 * @Brief Enable I2C slave
 */
void yysh_i2c_slave_enable(void *data)
{
	yy_i2c_slave_interrupt_init(I2C_TWI1);
}


