/*
 * yysh_memory_cmds.c
 *
 * Created: 2025/4/7 下午 03:00:20
 *  Author: Yuyi_Chen
 */ 

#include "yysh_memory_cmds.h"
#include "yysh_customization_cmds.h"

/*
 * @brief print value of memory address, max numbers is 1024.
 *        Usage: > memread <address> <size>
 */
void yysh_read_memory(void * data)
{
	/* format is incorrect */
	if (tokens[2][0] == '\0' || strncmp(tokens[1], "0x", 2) != 0) {
		return;
	}
		
	uint8_t recvBuf[1024];
	uint32_t addr, size;
	char* endptr;
	addr = strtol(tokens[1], &endptr, 16);
	size = strtol(tokens[2], &endptr, 10);
		
	uint32_t start = (addr ) & ~(0xf);
	uint32_t total_size = (((addr + size) + 0xf) & ~(0xf)) - start;
	total_size = (total_size > 1024) ? 1024 : total_size;
	uint32_t col_size = total_size / 16;
		
		
	memcpy(recvBuf, (const uint8_t *)start, total_size);
		
		
	/* SHELL_PRINTF Info */
	SHELL_PRINTF("            ");
	for (int i = 0; i < 16; i++ ) {
		char x_lable[2];
		sprintf(x_lable, "%x", i);
		SHELL_PRINTF("%2s ", x_lable);
	}
	SHELL_PRINTF("\r\n  ");

	for (int i = 0; i < col_size; i++) {
		char y_lable[10];
		sprintf(y_lable, "%08x:", start + i*16);
		SHELL_PRINTF("%9s ", y_lable);
		for (int j = 0; j < 16; j++) {
			// message
			char value[3];
			sprintf(value, "%02x", recvBuf[i*16+j]);
			SHELL_PRINTF("%2s ", value);
		}
		SHELL_PRINTF("\r\n  ");
	}
}

/*
 * @brief erase flash
 *        Usage: > flasherase <address> <mode>
 *        (mode can refer to the following : FLASH_ERADED_MODE_E)
 */
void yysh_erase_flash(void * data)
{
	/* format is incorrect */
	if (tokens[2][0] == '\0' || strncmp(tokens[1], "0x", 2) != 0) {
		return;
	}
	
	uint32_t addr, mode;
	char* endptr;
	addr = strtol(tokens[1], &endptr, 16);
	mode = strtol(tokens[2], &endptr, 10);
	
	uint32_t status;
	status = yy_flash_erase(addr, mode);
	SHELL_PRINTF("status: %d\r\n", status);
	
}

/*
 * @brief write data to flash
 *        Usage: > flashwrite <address> <value>
 */
void yysh_write_flash(void* data)
{
	/* format is incorrect */
	if (tokens[2][0] == '\0' || strncmp(tokens[1], "0x", 2) != 0) {
		return;
	}
	
	uint32_t addr;
	uint8_t value;
	char* endptr;
	addr = strtol(tokens[1], &endptr, 16);
	// Regardless of the input format, it is hexadecimal. 
	value =  (strncmp(tokens[1], "0x", 2) == 0) ? strtol(tokens[2], &endptr, 16) : strtol(tokens[2], &endptr, 10);
	
	uint32_t status;
	status = yy_flash_write(addr, &value, 1, ERASED_PAGES_8);
	SHELL_PRINTF("status: %d\r\n", status);
	
}