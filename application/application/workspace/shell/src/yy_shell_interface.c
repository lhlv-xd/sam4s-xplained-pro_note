/*
 * yy_shell_interface.c
 *
 * Created: 2025/4/2 下午 04:17:24
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include <string.h>
#include <stdlib.h>
#include "yy_shell_interface.h"
#include "yysh_customization_cmds.h"
#include "yy_uart_api.h"

/* Extern Variable */
volatile uint8_t tokens[TOKEN_NUMS][TOKEN_CMD_SIZE];
volatile uint8_t shellbuf[SHELLBUF_SIZE];
volatile uint8_t exec_shell_command = 0;

/* Variable  */
uint8_t historybuf[HISTORY_NUMS][SHELLBUF_SIZE];
static uint8_t history_index = 0;

static uint8_t shellbuf_index = 0;



/* static */
static uint8_t is_esc = 0;
static int8_t hist_get_index = -1;

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

/** 
 * @brief Set history command to historybuf
 */
void set_history(uint8_t* content)
{
	strcpy(historybuf[history_index++], content);
	if (history_index >= HISTORY_NUMS) {
		history_index = 0;
	}
}

/** 
 * @brief Get history command
 */
void get_history(uint8_t* recvbuf, ARROW_KEYS_E mode)
{
	if (hist_get_index == -1) {
		hist_get_index = history_index;
	}
	
	int8_t _hist_index;
	if (mode == PgUp) {
		_hist_index = (hist_get_index == 0) ? (HISTORY_NUMS - 1) : (hist_get_index - 1);
		
	}
	else {
		_hist_index = (hist_get_index == HISTORY_NUMS) ? (0) : (hist_get_index + 1);
	}
	
	// if around
	if (_hist_index != history_index) {
		hist_get_index = _hist_index;
	}
	
	strcpy(recvbuf, historybuf[hist_get_index]);
}

/** 
 * @brief Clear shell output message
 */
void clear_shell_message()
{
	SHELL_PRINTF("\r");
	uint32_t size = strlen(shellbuf) + strlen(SHELL_PROMPT);
	size = (size > SHELLBUF_SIZE) ? SHELLBUF_SIZE : size;
	for (uint32_t i = 0; i < size; i++) {
		SHELL_PRINTF(" ");
	}
	SHELL_PRINTF("\r"SHELL_SIGN" ");
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
			hist_get_index = -1;
			
			/* Finish */
			exec_shell_command = 1;
			SHELL_PRINTF("\r\n");
			SHELL_DEBUG(0, "\r\nFinish: %s", shellbuf);
			SHELL_DEBUG(0, "\r\nlen: %d\r\n", strlen(shellbuf));
			
			/* Record History */
			set_history(shellbuf);
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
		
		/* ESC */
		if (received_data == 0x1b || is_esc) {
			is_esc = 1;	
			if (received_data != 0x1b) {
				is_esc = 0;
			}
			
			switch (received_data) {
				case 0x5b: // ASCII: [
					is_esc = 1;
					break;
				/* PgUp */
				case 0x41:
					SHELL_DEBUG(0, "Up,");
					clear_shell_message();
					
					get_history(shellbuf, PgUp);
					shellbuf_index = strlen(shellbuf);
					shellbuf[shellbuf_index] = '\0';
					
					SHELL_PRINTF("%s", shellbuf);
					break;
				/* PgDn */
				case 0x42:
					SHELL_DEBUG(0, "Down,");
					clear_shell_message();
					
					get_history(shellbuf, PgDn);
					shellbuf_index = strlen(shellbuf);
					shellbuf[shellbuf_index] = '\0';
					
					SHELL_PRINTF("%s", shellbuf);
					break;	
				/* Left */
				case 0x44:
					SHELL_DEBUG(0, "Left,");
					break;
				/* Right */
				case 0x43:
					SHELL_DEBUG(0, "Right,");
					break;	
				default:
					break;
			}

			return;
		}
		
		/* Tab */
		if (received_data == 0x09) {
			for (uint32_t i = 0; i < yysh_cmds_size(); i++) {
				if (strncmp(cmds[i].name, shellbuf, shellbuf_index) == 0) {
					strcpy(shellbuf, cmds[i].name);
					shellbuf_index = strlen(cmds[i].name);
					
					//show
					clear_shell_message();
					SHELL_PRINTF("%s", shellbuf);
				}
			}
			return;
		}
		
		
		/* Show Character */
		SHELL_PRINTF("%c", received_data);
		/* Add character to shellbuf */
		shellbuf[shellbuf_index++] = received_data;

	}


}


/** 
 * @brief split commands to tokens 
 * @param[in] command_line This is input from shell.
 */
uint8_t** yysh_split_line(uint8_t* command_line)
{
	/* Declare */
	uint8_t cmd_buf[SHELLBUF_SIZE];
	const char* delimiter = " \t\r\n";
	char* substr;
	uint8_t tokens_index = 0;
	
	/* Split */
	strcpy(cmd_buf, command_line);
	substr = strtok(cmd_buf, delimiter);
	
	do {
		strcpy(tokens[tokens_index++], substr);
		substr = strtok(NULL, delimiter);
	} while(substr);
	

	return tokens;
}

/** 
 * @brief Clear tokens to '\0'
 */
void yysh_clear_tokens()
{
	for(uint8_t i = 0; i < TOKEN_NUMS; i++)
	{
		for(uint8_t j = 0; j < TOKEN_CMD_SIZE; j++)
		{
			tokens[i][j] = '\0';
		}
	}
	
}


/** 
 * @brief Processing shell commands
 * @param[in] command_line This is input from shell.
 */
void yysh_exec(uint8_t* command_line)
{
	SHELL_DEBUG(0, "[in %s function] \r\n", __FUNCTION__);
	
	/* split command line to tokens  */
	yysh_split_line(command_line);
	
	/* Execution tokens */
	for (uint32_t i = 0; i < yysh_cmds_size(); i++) {
		if (strcmp(tokens[0], cmds[i].name) == 0) {
			cmds[i].func(NULL);
			
			/* Clear tokens */
			yysh_clear_tokens();
			
			/* Show Prompt */
			SHELL_PRINTF(SHELL_PROMPT);
			return;
		}
	}
	/* Show Prompt */
	SHELL_PRINTF("\r"SHELL_SIGN" ");
}



