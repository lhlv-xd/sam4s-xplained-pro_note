/*
 * yysh_customization_cmds.c
 *
 * Created: 2025/4/7 下午 02:01:36
 *  Author: Yuyi_Chen
 */ 
#include "yysh_customization_cmds.h"



/* Customization */
void yysh_help(void* data)
{
	const char help_msg[] =
	"yysh  Yuyi's Shell. \r\n"
	"  help                                           Print this help message.\r\n";
	
	SHELL_PRINTF(help_msg);
}

struct cmd cmds[] = {
	{"help",           yysh_help       }
};

uint32_t yysh_cmds_size()
{
	return sizeof(cmds) / sizeof(struct cmd);
}


