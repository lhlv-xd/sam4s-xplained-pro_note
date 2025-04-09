/*
 * yysh_information.c
 *
 * Created: 2025/4/9 下午 01:15:05
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yysh_information.h"
#include "yysh_customization_cmds.h"

extern uint32_t _sfixed, _efixed, _etext, _srelocate, _erelocate, _sbss, _ebss, _sstack, _estack;

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
	
	/* other */
	SHELL_PRINTF("others\r\n");
	SHELL_PRINTF("\t_etext: 0x%x\r\n", &_etext);
}