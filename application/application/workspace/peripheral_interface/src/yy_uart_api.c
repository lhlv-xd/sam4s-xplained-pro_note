/*
 * yy_uart_api.c
 *
 * Created: 2025/4/2 下午 02:00:40
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include <stdarg.h>
#include <string.h>
#include "yy_uart_api.h"

/** 
 * @brief UART Init 
 */
void yy_uart_init()
{
	static usart_serial_options_t usart_options = {
		.baudrate = USART_SERIAL_BAUDRATE,
		.charlength = USART_SERIAL_CHAR_LENGTH,
		.paritytype = USART_SERIAL_PARITY,
		.stopbits = USART_SERIAL_STOP_BIT
	};
	
#if ENABLE_UART0
	gpio_configure_group(PINS_UART0_PIO, PINS_UART0, PINS_UART0_FLAGS);
	usart_serial_init(USART_SERIAL0, &usart_options);
#endif // ENABLE_UART0

#if ENABLE_UART1
	gpio_configure_group(PINS_UART1_PIO, PINS_UART1, PINS_UART1_FLAGS);
	usart_serial_init(USART_SERIAL1, &usart_options);
#endif // ENABLE_UART1
}



/** 
 * @brief show debug message by uart 
 */
void yy_show(const char* format, ...)
{
	char buf[1024];
	
	va_list args;
	va_start(args, format);
	vsnprintf(buf, sizeof(buf), format, args);
	va_end(args);

#if ENABLE_UART1
	usart_serial_write_packet(USART_SERIAL1, buf, strlen(buf));
#else
	usart_serial_write_packet(USART_SERIAL0, buf, strlen(buf));
#endif
}