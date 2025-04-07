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


/* Variable  */
volatile uint8_t shellbuf[SHELLBUF_SIZE];
static uint8_t shellbuf_index = 0;

volatile uint8_t exec_shell_command = 0;


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
			exec_shell_command = 1;
			SHELL_PRINTF("\r\n");
			SHELL_DEBUG(0, "\r\nFinish: %s", shellbuf);
			SHELL_DEBUG(0, "\r\nlen: %d\r\n", strlen(shellbuf));
			
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
		}
	}
	/* Show Prompt */
	SHELL_PRINTF(SHELL_PROMPT);
}



