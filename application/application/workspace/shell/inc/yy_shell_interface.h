/*
 * yy_shell_interface.h
 *
 * Created: 2025/4/2 下午 04:17:39
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_SHELL_INTERFACE_H_
#define YY_SHELL_INTERFACE_H_

#include "yy_peripheral_init.h"
#include "yysh_customization_cmds.h"
#include <stdarg.h>

/* Flag */


/* Defined */
#define SHELLBUF_SIZE 128
#define SHELL_SIGN   ">"
#define SHELL_PROMPT "\r\n"SHELL_SIGN" "

#define SHELL_INTERFACE USART_SERIAL1
#define SHELL_IRQ UART1_IRQn
#define SHELL_HANDLER UART1_Handler

#define SHELL_PRINTF(format, ...) yy_show(format, ##__VA_ARGS__)
#define SHELL_DEBUG(debug, format, ...) { \
	if (debug > 0) { \
		yy_show(format, ##__VA_ARGS__); \
	}}

#define TOKEN_NUMS 8
#define TOKEN_CMD_SIZE 20

#define HISTORY_NUMS 4

/* Extern */
extern volatile uint8_t tokens[TOKEN_NUMS][TOKEN_CMD_SIZE];
extern volatile uint8_t exec_shell_command;
extern volatile uint8_t shellbuf[SHELLBUF_SIZE];

/* Enumerate */
typedef enum {
	PgUp,
	PgDn	
}ARROW_KEYS_E;


/* Prototype */
// Init
void yy_shell_init();
void yy_shell_deinit();

// history
void set_history(uint8_t* content);
void get_history(uint8_t* recvbuf, ARROW_KEYS_E mode);
void clear_shell_message();

// Execution
uint8_t** yysh_split_line(uint8_t* command_line);
void yysh_clear_tokens();
void yysh_exec(uint8_t* command_line);





#endif /* YY_SHELL_INTERFACE_H_ */