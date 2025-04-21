/*
 * yy_i2c_api.c
 *
 * Created: 2025/4/16 下午 05:56:20
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yy_i2c_api.h"


void yy_i2c_slave_init(I2C_INTERFACE_E interface, uint32_t slave_address)
{
	
	switch (interface) {
		case I2C_TWI0:
			/* Enable clock */
			pmc_enable_periph_clk(ID_PIOA);
			pmc_enable_periph_clk(ID_TWI0);
			
			/* Set Pin peripheral mode */
			ioport_set_pin_mode(TWI0_SCL, IOPORT_MODE_MUX_A);
			ioport_disable_pin(TWI0_SCL);
			
			ioport_set_pin_mode(TWI0_SDA, IOPORT_MODE_MUX_A);
			ioport_disable_pin(TWI0_SDA);
			
			/* TWI1 init */
			twi_slave_setup(TWI0, slave_address);
			break;
		case I2C_TWI1:
			/* Enable clock */
			pmc_enable_periph_clk(ID_PIOB);
			pmc_enable_periph_clk(ID_TWI1);
			
			/* Disale system function */
			uint32_t CCFG_SYSIO_CONF = matrix_get_system_io();
			matrix_set_system_io(CCFG_SYSIO_CONF | CCFG_SYSIO_SYSIO4 | CCFG_SYSIO_SYSIO5);

			/* Set Pin peripheral mode */
			ioport_set_pin_mode(TWI1_SCL, IOPORT_MODE_MUX_A);
			ioport_disable_pin(TWI1_SCL);
			
			ioport_set_pin_mode(TWI1_SDA, IOPORT_MODE_MUX_A);
			ioport_disable_pin(TWI1_SDA);
			
			/* TWI1 init */
			twi_slave_setup(TWI1, slave_address);
			break;
	}
}

void yy_i2c_slave_interrupt_init(I2C_INTERFACE_E interface)
{
	switch (interface) {
		case I2C_TWI0:
			/* Clear receipt buffer */
			twi_read_byte(TWI0);
			
			/* Configure TWI interrupts */
			NVIC_DisableIRQ(TWI0_IRQn);
			NVIC_ClearPendingIRQ(TWI0_IRQn);
			NVIC_SetPriority(TWI0_IRQn, 0);
			NVIC_EnableIRQ(TWI0_IRQn);
			twi_enable_interrupt(TWI0, TWI_SR_SVACC);
			break;
		case I2C_TWI1:
			/* Clear receipt buffer */
			twi_read_byte(TWI1);
			
			/* Configure TWI interrupts */
			NVIC_DisableIRQ(TWI1_IRQn);
			NVIC_ClearPendingIRQ(TWI1_IRQn);
			NVIC_SetPriority(TWI1_IRQn, 0);
			NVIC_EnableIRQ(TWI1_IRQn);
			twi_enable_interrupt(TWI1, TWI_SR_SVACC);
			break;
	}
}