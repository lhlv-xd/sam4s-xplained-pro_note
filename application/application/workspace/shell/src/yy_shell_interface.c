/*
 * yy_shell_interface.c
 *
 * Created: 2025/4/2 下午 04:17:24
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include <string.h>
#include "yy_shell_interface.h"
#include "yy_uart_api.h"


/* Variable  */
volatile uint8_t shellbuf[SHELLBUF_SIZE];
static uint8_t shellbuf_index = 0;




/** 
 * @brief Init shell
 */
void yy_shell_init()
{
	/* Rx Interrupt */
	NVIC_DisableIRQ(UART1_IRQn);
	NVIC_ClearPendingIRQ(UART1_IRQn);
	NVIC_SetPriority(UART1_IRQn, 1);
	NVIC_EnableIRQ(UART1_IRQn);
	uart_enable_interrupt(USART_SERIAL1, UART_IER_RXRDY);
}

/** 
 * @brief Deinit shell
 */
void yy_shell_deinit()
{
	NVIC_DisableIRQ(UART1_IRQn);
	NVIC_ClearPendingIRQ(UART1_IRQn);
	uart_disable_interrupt(USART_SERIAL1, UART_IER_RXRDY);
}


void UART1_Handler()
{
	uint32_t status = uart_get_status(UART1);
	uint8_t received_data;
	//show("status: 0x%x\r\n", status);

	if (status & UART_IER_RXRDY) {
		received_data = (uint8_t) UART1->UART_RHR;
		uart_reset_status(UART1);

		
		if (received_data == '\r' || received_data == '\n') {
			/* No command, show prompt */
			if (shellbuf_index == 0) {
				SHELL_PRINTF(SHELL_PROMPT);
				return;
			}
			
			
			/* Deal with shellbuf */
			shellbuf[shellbuf_index] = '\0';
			
			/* Reset parameters */
			shellbuf_index = 0;
			
			/* Finish */
			SHELL_PRINTF("\r\nFinish: %s", shellbuf);
			SHELL_PRINTF("\r\nlen: %d\r\n", strlen(shellbuf));
			SHELL_PRINTF(SHELL_PROMPT);
			
			return;
		}
		
		/* Backspace  */
		if (received_data == 0x08) {
			if (shellbuf_index == 0) {
				return;
			}
			
			shellbuf[shellbuf_index--] = '\0';
			SHELL_PRINTF("\b \b");
			return;
		}
		
		/* Show Character */
		SHELL_PRINTF("%c", received_data);
		
		/* Add character to shellbuf */
		shellbuf[shellbuf_index++] = received_data;

	}


}