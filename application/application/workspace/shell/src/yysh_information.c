/*
 * yysh_information.c
 *
 * Created: 2025/4/9 下午 01:15:05
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yysh_information.h"
#include "yysh_customization_cmds.h"
#include "yy_i2c_slave_interrupt.h"

extern uint32_t _sfixed, _efixed, _etext, _srelocate, _erelocate, _sbss, _ebss, _sstack, _estack, __ram_end__, _end;

void yysh_show_linker_address(void *data)
{
	/* .text */
	SHELL_PRINTF(".text\r\n");
	SHELL_PRINTF("\t_sfixed: 0x%x\r\n", &_sfixed);
	SHELL_PRINTF("\t_efixed: 0x%x\r\n", &_efixed);
	
	/* .relocate */
	SHELL_PRINTF(".relocate\r\n");
	SHELL_PRINTF("\t_srelocate: 0x%x\r\n", &_srelocate);
	SHELL_PRINTF("\t_erelocate: 0x%x\r\n", &_erelocate);
	
	/* .bss */
	SHELL_PRINTF(".bss\r\n");
	SHELL_PRINTF("\t_sbss: 0x%x\r\n", &_sbss);
	SHELL_PRINTF("\t_ebss: 0x%x\r\n", &_ebss);
	
	/* .stack */
	SHELL_PRINTF(".stack\r\n");
	SHELL_PRINTF("\t_sstack: 0x%x\r\n", &_sstack);
	SHELL_PRINTF("\t_estack: 0x%x\r\n", &_estack);
	
	/* .heap */
	SHELL_PRINTF(".heap\r\n");
	SHELL_PRINTF("\t_end: 0x%x\r\n", &_end);
	SHELL_PRINTF("\t__ram_end__: 0x%x\r\n", &__ram_end__);
	
	/* other */
	SHELL_PRINTF("others\r\n");
	SHELL_PRINTF("\t_etext: 0x%x\r\n", &_etext);
}


/*
 * @brief clear screen
 */
void yysh_clear(void* data)
{
	SHELL_PRINTF("\x1B[2J\x1B[H");
}


void yysh_show_i2c_pages(void* data)
{

	
	uint8_t count = 0;
	SHELL_PRINTF("\r\nBasicPage: 0x%x\r\n", BasicPage);
	for (uint32_t i = 0; i < 128; i++) {
		SHELL_PRINTF("0x%02x, ", BasicPage[i]);
		count++;
		if (count % 16 == 0) {
			SHELL_PRINTF("\r\n");
			count = 0;
		}
	}
	
	count = 0;
	SHELL_PRINTF("\r\Page00h:0x%x\r\n", Page00h);
	for (uint32_t i = 0; i < 128; i++) {
		SHELL_PRINTF("0x%02x, ", Page00h[i]);
		count++;
		if (count % 16 == 0) {
			SHELL_PRINTF("\r\n");
			count = 0;
		}
		
	}
}