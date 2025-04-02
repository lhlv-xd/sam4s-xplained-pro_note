/*
 * yy_redirection.c
 *
 * Created: 2025/4/2 下午 02:49:27
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yy_peripheral_init.h"


int _write(int file, char *data, int len)
{
#if ENABLE_UART1
	usart_serial_write_packet(USART_SERIAL1, data, len);
#else
	usart_serial_write_packet(USART_SERIAL0, data, len);
#endif
	return 0;
}

int _read(int file, char *data, int len) {
	uint32_t status;

#if ENABLE_UART1
	while (status = uart_read(UART1, data));
#else
	while (status = uart_read(UART0, data));
#endif

	return 1; // date length
}