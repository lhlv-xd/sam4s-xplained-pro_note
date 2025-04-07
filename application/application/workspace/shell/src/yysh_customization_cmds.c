/*
 * yysh_customization_cmds.c
 *
 * Created: 2025/4/7 下午 02:01:36
 *  Author: Yuyi_Chen
 */ 
#include "yysh_customization_cmds.h"



/* Customization */
/*
 * @brief show all commands help message
 * @details You can add your customized command help to this.
 */
void yysh_help(void* data)
{
	const char help_msg[] =
	"yysh  Yuyi's Shell. \r\n"
	"  help                                           Print this help message.\r\n"
	"  memread <address> <size>                       Read MCU register.\r\n";
	
	SHELL_PRINTF(help_msg);
}

/* Add your customized callback function to this */
struct cmd cmds[] = {
	{"help",           yysh_help       },
	{"memread",        yysh_read_memory}
};

/*
 * @brief show cmds size
 */
uint32_t yysh_cmds_size()
{
	return sizeof(cmds) / sizeof(struct cmd);
}


