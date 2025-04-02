/*
 * yy_uart_api.h
 *
 * Created: 2025/4/2 下午 02:00:55
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_UART_API_H_
#define YY_UART_API_H_

/* Flags */
#define ENABLE_UART0 0
#define ENABLE_UART1 1

/* Alias */ 
#define USART_SERIAL1 UART1
#define USART_SERIAL0 UART0

/* Defined  */
// UART0
#ifndef PINS_UART0
#define PINS_UART0                (PIO_PA9A_URXD0 | PIO_PA10A_UTXD0)
#define PINS_UART0_FLAGS          (PIO_PERIPH_A | PIO_DEFAULT)
#define PINS_UART0_PIO            PIOA
#endif // PINS_UART0

// UART1 (default for Sam4s Xplained Pro)
#ifndef PINS_UART1
#define PINS_UART1                (PIO_PB2A_URXD1 | PIO_PB3A_UTXD1)
#define PINS_UART1_FLAGS          (PIO_PERIPH_A | PIO_DEFAULT)
#define PINS_UART1_PIO            PIOB
#endif // PINS_UART1

// Uart Parameters
#define USART_SERIAL_BAUDRATE 115200
#define USART_SERIAL_CHAR_LENGTH US_MR_CHRL_8_BIT
#define USART_SERIAL_PARITY US_MR_PAR_NO
#define USART_SERIAL_STOP_BIT false


/* Prototype */
#include <stdarg.h>
void yy_uart_init();
void yy_show(const char* format, ...);



#endif /* YY_UART_API_H_ */