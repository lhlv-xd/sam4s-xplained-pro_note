/*
 * yy_i2c_slave_interrupt.c
 *
 * Created: 2025/4/16 下午 06:25:37
 *  Author: Yuyi_Chen
 */ 
#include <asf.h>
#include "yy_i2c_slave_interrupt.h"

/* Page */
volatile uint8_t BasicPage[128];
volatile uint8_t Page00h[128];
volatile uint8_t Page01h[128];

/* static */
static uint8_t is_register_address = 1;
static uint8_t *rptr = (uint8_t *) &BasicPage;
static uint8_t table_end_address = 0x7f;

static uint8_t data_address = 0x00;
static uint8_t address_data = 0x00;


void I2C_SLAVE_HANDLER(void)
{
	uint32_t status;

	status = twi_get_interrupt_status(I2C_SLAVE_INTERFACE);
	
	if ((status & TWI_SR_SVACC) == TWI_SR_SVACC) {
		twi_disable_interrupt(I2C_SLAVE_INTERFACE, TWI_IDR_SVACC);
		twi_enable_interrupt(I2C_SLAVE_INTERFACE, TWI_IER_RXRDY | TWI_IER_GACC
		| TWI_IER_NACK | TWI_IER_EOSACC | TWI_IER_SCL_WS);
	}
	
	/* First if (slave Rx)*/
	if (((status & TWI_SR_GACC) == 0)
	&& ((status & TWI_SR_RXRDY) == TWI_SR_RXRDY)) {
		/* Read 1 Byte */
		uint8_t received_data = twi_read_byte(I2C_SLAVE_INTERFACE);
		
		//yy_show("recv: 0x%x (%d)\r\n", received_data, is_register_address);
		/* Deal with register address */
		if (is_register_address) {
			/* Reset */
			data_address = received_data;
			is_register_address = 0;
			
			/* Choose Page (Basic Page) */
			if (data_address < 0x80) {
				rptr = ((uint8_t *) &BasicPage) + data_address;
				table_end_address = 0x7f;
			}
			/* Choose Page (Upper Page) */
			else {
				switch (BasicPage[0x7f]) {
					case 0x00:
						rptr = ((uint8_t *)&Page00h) + (data_address - 128);
						break;
					case 0x01:
						rptr = ((uint8_t *)&Page01h) + (data_address - 128);
						break;
					default :
						break;
				}
				table_end_address = 0xff;
			}
		}
		/* !is_registeraddress (process data) */
		else {
			address_data = received_data;
			
			/* Receive data by register address (Basic Page) */
			if (table_end_address == 0x7f) {
				*rptr = received_data;
			}
			/* Receive data by register address (Upper Page) */
			else {
				switch (BasicPage[0x7f]) {
					case 0x00:
						*rptr = received_data;
						break;
					case 0x01:
						*rptr = received_data;
						break;
					default :
						break;
				}
			}
			
			/* Process the next data */
			if (data_address < table_end_address) {
				data_address++;
				rptr++;
			}
			/* Process overflow */
			else {
				data_address -= 0x7f;
				rptr -= 0x7f;
			}
			
		}
		
	}
	/* First else (slave Tx) */
	else {
		/* Second if */
		if (((status & TWI_SR_TXRDY) == TWI_SR_TXRDY)
		&& ((status & TWI_SR_TXCOMP) == TWI_SR_TXCOMP)
		&& ((status & TWI_SR_EOSACC) == TWI_SR_EOSACC)) {
			/* End of slave transfer, end of slave access */
			twi_enable_interrupt(I2C_SLAVE_INTERFACE, TWI_SR_SVACC);
			twi_disable_interrupt(I2C_SLAVE_INTERFACE,
								  TWI_IDR_RXRDY | TWI_IDR_GACC |
								  TWI_IDR_NACK | TWI_IDR_EOSACC | TWI_IDR_SCL_WS);
			//yy_show("this\r\n");
		}
		/* Second if */
		else {
			/* Third if */
			if (((status & TWI_SR_SVACC) == TWI_SR_SVACC)
			&& ((status & TWI_SR_GACC) == 0)
			&& ((status & TWI_SR_SVREAD) == TWI_SR_SVREAD)
			&& ((status & TWI_SR_TXRDY) == TWI_SR_TXRDY)
			&& ((status & TWI_SR_NACK) == 0)) {
				
				/* Send data through register address (Basic Page) */
				if (table_end_address == 0x7F) {
					TWI1->TWI_THR = *rptr;
				}
				/* Send data through register address (Upper Page) */
				else {
					switch (BasicPage[0x7f]) {
						case 0x00:
							TWI1->TWI_THR = *rptr;
							break;
						case 0x01:
							TWI1->TWI_THR = *rptr;
							break;
						default :
							break;
					}
				}
					
				/* Process the next data */
				if (data_address < table_end_address) {
					data_address++;
					rptr++;
				}
				/* Process overflow */
				else {

					data_address -= 0x7f;
					rptr -= 0x7f;
				}
			}
		}
		
	}
	
	
	/* END */
	if (status & TWI_SR_EOSACC) {
		is_register_address = 1;
		
	}
}