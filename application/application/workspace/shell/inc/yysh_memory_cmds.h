/*
 * yysh_memory_cmds.h
 *
 * Created: 2025/4/7 下午 03:00:43
 *  Author: Yuyi_Chen
 */ 


#ifndef YYSH_MEMORY_CMDS_H_
#define YYSH_MEMORY_CMDS_H_

/* Prototype */
void yysh_read_memory(void * data);
void yysh_write_memory(void* data);
void yysh_erase_flash(void * data);
void yysh_write_flash(void* data);




#endif /* YYSH_MEMORY_CMDS_H_ */