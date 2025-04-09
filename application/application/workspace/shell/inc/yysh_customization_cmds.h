/*
 * yysh_customization_cmds.h
 *
 * Created: 2025/4/7 下午 02:02:04
 *  Author: Yuyi_Chen
 */ 


#ifndef YYSH_CUSTOMIZATION_CMDS_H_
#define YYSH_CUSTOMIZATION_CMDS_H_

#include <asf.h>
#include <stdint.h>
#include <string.h>
#include "yy_shell_interface.h"
/* Customized Include */
#include "yysh_memory_cmds.h"
#include "yysh_information.h"

/* Structure */
struct cmd {
	char *name;
	void (*func)(void* data);
};


/* Macro */


/* Extern */
extern struct cmd cmds[];


/* Prototype */
uint8_t yysh_getvalue8(const char* value);
uint32_t yysh_getvalue32(const char* value);
uint32_t yysh_cmds_size();
void yysh_help(void* data);
// Customized command






#endif /* YYSH_CUSTOMIZATION_CMDS_H_ */