/*
 * yy_gpio_api.c
 *
 * Created: 2025/5/16 下午 04:40:08
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yy_gpio_api.h"
#include "yy_peripheral_init.h"

/* Static */
static uint32_t pa24_count = 0;


void yy_gpio_init()
{
	/* Output */
	// PA25
	ioport_set_pin_dir(GPIO_PA25, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(GPIO_PA25, 0);
	
	
	/* Input */
	// PA24
	ioport_set_pin_dir(GPIO_PA24, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(GPIO_PA24, IOPORT_MODE_PULLDOWN);
	
	
	/* Configure GPIO Interrupts */
	// Clear Interrupt Status
	pio_get_interrupt_status(GPIOA_REGISTERS);
	
	// Set PA24 is actived by a high level rising edge and call yy_gpio_pa24_handler function.
	// If set high level active, pa24 init advised is pulldown.
	pio_handler_set_pin(GPIO_PA24, PIO_IT_RISE_EDGE, yy_gpio_pa24_handler);
	
	// Turn on PIOA Interrupt if need any pioa pin interrupt.
	NVIC_DisableIRQ(GPIOA_IRQ);
	NVIC_ClearPendingIRQ(GPIOA_IRQ);
	NVIC_SetPriority(GPIOA_IRQ, 0);
	NVIC_EnableIRQ(GPIOA_IRQ);
	pio_enable_interrupt(GPIOA_REGISTERS, PIO_IER_P24);
	
}



void yy_gpio_pa24_handler(uint32_t id, uint32_t mask)
{
	pa24_count++;
	//yy_show("gpio pa24 interrupt: %d\r\n", pa24_count++);
	//yy_show("id=0x%x, mask=0x%x\r\n", id, mask); // show: id=0xb (PIOA handler), mask=0x01000000 (PA24 Mask)
}


/** 
 * @Brief Simulate voltage changes caused by external triggers.
 * @Note Need to manually connect pa24 and pa25 pins, input and output respectively.
 */
void test_gpio_pa24_interrupt()
{
	int timeout = 1000;
	
	/* Initial Value */
	ioport_set_pin_level(GPIO_PA25, 0);

	/* Convert 10000 times */
	for (int i = 0; i < 50000; i++) {
		// Set PA25 to high
		timeout = 1000;
		ioport_set_pin_level(GPIO_PA25, 1);
		while (timeout--);
		if (timeout <= 0 && !PIOA->PIO_ODSR & (1<<24)) {
			yy_show("Setting PA25 to 1 is timeout[%d]\r\n", timeout);
			return;
		}
		
		// Set PA25 to LOW
		timeout = 1000;
		ioport_set_pin_level(GPIO_PA25, 0);
		while (timeout-- && PIOA->PIO_ODSR & (1<<24));
		if (timeout <= 0) {
			yy_show("Setting PA25 to 0 is timeout[%d]\r\n", timeout);
			return;
		}
	}
	
	/* Show Result: 50000 expected*/
	yy_show("pa24_count: %d\r\n", pa24_count);
}