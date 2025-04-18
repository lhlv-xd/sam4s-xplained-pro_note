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
	"  reset                                          Reset MCU.\r\n"
	"  clear                                          Clear screen.\r\n"
	"  memread <address> <size>                       Read MCU register.\r\n"
	"  memwrite <address> <value>                     Write MCU register.\r\n"
	"  flasherase <address> <mode>                    Erase mcu flash.\r\n"
	"  flashwrite <address> <value>                   Write mcu flash.\r\n"
	"  flashunlock <address> <total_size>             Unlock flash.\r\n"
	"  flashlock <address> <total_size>               Lock flash.\r\n"
	"  show_linker                                    Show linker address.\r\n"
	"  xmodem <address>                               FW update by xmodem.\r\n"
	"  jumpto <address>                               Relocate to new Entry point.\r\n";
	
	SHELL_PRINTF(help_msg);
}

/* Add your customized callback function to this */
struct cmd cmds[] = {
	{"help",             yysh_help               },
	{"clear",            yysh_clear              },
	{"memread",          yysh_read_memory        },
	{"memwrite",         yysh_write_memory       },
	{"flasherase",       yysh_erase_flash        },
	{"flashwrite",       yysh_write_flash        },
	{"flashunlock",      yysh_unlock_flash       },
	{"flashlock",        yysh_lock_flash         },
	{"show_linker",      yysh_show_linker_address},
	{"xmodem",           yysh_xmodem_update      },
	{"jumpto",           yysh_relocate           },
};

/*
 * @brief show cmds size
 */
uint32_t yysh_cmds_size()
{
	return sizeof(cmds) / sizeof(struct cmd);
}

/*
 * @brief convert string to uint8_t
 * @note if string include 0x, the result of uint8_t is hexadecimal, or it is decimal.
 */
uint8_t yysh_getvalue8(const char* value)
{
	uint8_t ret_value;
	char* endptr;
	ret_value =(strncmp(value, "0x", 2) == 0) ?  strtol(value, &endptr, 16) : strtol(value, &endptr, 10);
	
	SHELL_DEBUG(0, "yysh_getvalue8: %d\r\n", ret_value);
	return ret_value;
}

/*
 * @brief convert string to uint32_t
 * @note if string include 0x, the result of uint8_t is hexadecimal, or it is decimal.
 */
uint32_t yysh_getvalue32(const char* value)
{
	uint32_t ret_value;
	char* endptr; 
	ret_value =(strncmp(value, "0x", 2) == 0) ?  strtol(value, &endptr, 16) : strtol(value, &endptr, 10);
	
	SHELL_DEBUG(0, "yysh_getvalue32: 0x%x\r\n", ret_value);
	return ret_value;
}