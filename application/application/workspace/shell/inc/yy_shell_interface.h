/*
 * yy_shell_interface.h
 *
 * Created: 2025/4/2 下午 04:17:39
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_SHELL_INTERFACE_H_
#define YY_SHELL_INTERFACE_H_

#include "yy_peripheral_init.h"
#include <stdarg.h>

/* Extern */


/* Defined */
#define SHELLBUF_SIZE 128
#define SHELL_PROMPT "\r\n> "
#define SHELL_PRINTF(format, ...) yy_show(format, ##__VA_ARGS__)


/* Prototype */
void yy_shell_init();
void yy_shell_deinit();





#endif /* YY_SHELL_INTERFACE_H_ */