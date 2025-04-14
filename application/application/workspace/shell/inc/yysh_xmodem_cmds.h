/*
 * yysh_xmodem_cmds.h
 *
 * Created: 2025/4/14 下午 02:38:50
 *  Author: Yuyi_Chen
 */ 


#ifndef YYSH_XMODEM_CMDS_H_
#define YYSH_XMODEM_CMDS_H_

#include "yysh_customization_cmds.h"

/* Enumerate */
typedef enum {
	XMODEM_SEND_C,
	XMODEM_RECV_DATA,
	XMODEM_RECV_OK,
	XMODEM_EOT
}XMODEM_MODE;

/* Extern */
extern volatile uint8_t is_xmodem;
extern volatile uint8_t xmodembuf[131];
extern volatile uint32_t xmodembuf_index;

extern volatile uint8_t is_xmodem_data;
extern volatile XMODEM_MODE xmodem_mode;

/* Prototype */
void yysh_xmodem_update(void *data);


#endif /* YYSH_XMODEM_CMDS_H_ */