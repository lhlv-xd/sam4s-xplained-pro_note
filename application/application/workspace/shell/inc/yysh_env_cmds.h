/*
 * yysh_env_cmds.h
 *
 * Created: 2025/4/22 下午 03:09:28
 *  Author: Yuyi_Chen
 */ 


#ifndef YYSH_ENV_CMDS_H_
#define YYSH_ENV_CMDS_H_

#include "yysh_customization_cmds.h"

/* Definition */
#define ENV_ADDRESS 0x410000
#define ENV_SIZE 0x10000
#define ENV_KEY_SIZE 128
#define ENV_VALUE_SIZE 384
#define ENV_NUMS (ENV_SIZE / (ENV_KEY_SIZE + ENV_VALUE_SIZE)) // Integer
#define ENV_ERASE_SIZE (4 * 1024)  // 8 pages


/* Prototype */
void yysh_setenv(void* data);
void yysh_getenv(void* data);
void yysh_delenv(void* data);
uint32_t _find_env(const char* key);



#endif /* YYSH_ENV_CMDS_H_ */