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
	addr = yysh_getvalue32(tokens[1]);
	size = yysh_getvalue32(tokens[2]);
	
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
 * @brief write data to memory
 *        Usage: > memwrite <address> <value>
 */
void yysh_write_memory(void* data)
{
	/* format is incorrect */
	if (tokens[2][0] == '\0' || strncmp(tokens[1], "0x", 2) != 0) {
		return;
	}
	
	uint32_t addr;
	uint8_t value;
	addr = yysh_getvalue32(tokens[1]);
	value = yysh_getvalue8(tokens[2]);
	
	uint8_t *ptr = (uint8_t *) addr;
	*ptr = value;
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
	
	uint32_t addr;
	uint8_t mode;
	addr = yysh_getvalue32(tokens[1]);
	mode = yysh_getvalue8(tokens[2]);
	
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
	addr = yysh_getvalue32(tokens[1]);
	value = yysh_getvalue8(tokens[2]);
	
	uint32_t status;
	status = yy_flash_write(addr, &value, 1, ERASED_PAGES_8);
	SHELL_PRINTF("status: %d\r\n", status);
	
}


/* 
 * @brief Unlock specific flash region.
 * @note The minimum lock size is 8k and need to be aligned to 8K
 */
void yysh_unlock_flash(void* data)
{
	/* format is incorrect */
	if (tokens[2][0] == '\0' || strncmp(tokens[1], "0x", 2) != 0) {
		return;
	}
	
	uint32_t addr, total_size;
	addr = yysh_getvalue32(tokens[1]);
	total_size = yysh_getvalue32(tokens[2]);
	
	
	/* Declare */
	uint32_t status;
	uint32_t pul_actual_start, pul_actual_end;
	
	/* Flash Init */
	status = flash_init(FLASH_ACCESS_MODE_128, 6);
	SHELL_DEBUG(1, "flash_init status: %d\r\n", status);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	/* Flash Unlock */
	status = flash_unlock(addr, addr + total_size - 1, &pul_actual_start, &pul_actual_end);
	SHELL_DEBUG(1, "flash_unlock status: %d\r\n", status);
	if (status != FLASH_RC_OK) {	
		return;
	}
	
	SHELL_PRINTF("unlock address: 0x%x to 0x%x\r\n", pul_actual_start, pul_actual_end);
}

/* 
 * @brief Lock specific flash region.
 * @note The minimum lock size is 8k and need to be aligned to 8K
 */
void yysh_lock_flash(void* data)
{
	/* format is incorrect */
	if (tokens[2][0] == '\0' || strncmp(tokens[1], "0x", 2) != 0) {
		return;
	}
	
	uint32_t addr, total_size;
	addr = yysh_getvalue32(tokens[1]);
	total_size = yysh_getvalue32(tokens[2]);
	
	/* Declare */
	uint32_t status;
	uint32_t pul_actual_start, pul_actual_end;
	
	/* Flash Init */
	status = flash_init(FLASH_ACCESS_MODE_128, 6);
	SHELL_DEBUG(1, "flash_init status: %d\r\n", status);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	/* Flash lock */
	status = flash_lock(addr, addr + total_size - 1, &pul_actual_start, &pul_actual_end);
	SHELL_DEBUG(1, "status: %d\r\n", status);
	if (status != FLASH_RC_OK) {
		return;
	}
	
	SHELL_PRINTF("lock address: 0x%x to 0x%x\r\n", pul_actual_start, pul_actual_end);
}