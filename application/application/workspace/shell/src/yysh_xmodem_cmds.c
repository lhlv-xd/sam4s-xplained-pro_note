/*
 * yysh_xmodem_cmds.c
 *
 * Created: 2025/4/14 下午 02:38:29
 *  Author: Yuyi_Chen
 */ 

#include "yysh_xmodem_cmds.h"


/* Extern */
volatile uint8_t is_xmodem = 0;
volatile uint8_t xmodembuf[131];
volatile uint32_t xmodembuf_index = 0;

volatile uint8_t is_xmodem_data = 0;
volatile XMODEM_MODE xmodem_mode = XMODEM_SEND_C;

/* Define */
#define XMODEM_C 0x43
#define XMODEM_ACK 0x06
#define XMODEM_NAK 0x15
#define XMODEM_CRC_MSB 131
#define XMODEM_CRC_LSB 132


/* Prototype */
uint16_t _yy_xmodem_crc16(const uint8_t *addr, uint32_t num);

/** 
 * @brief Update firmware by xmodem
 */
void yysh_xmodem_update(void *data)
{
	/* format is incorrect */
	if (tokens[1][0] == '\0' || strncmp(tokens[1], "0x", 2) != 0) {
		return;
	}
	
	SHELL_PRINTF("Wait to xmodem connect...\r\n");
	is_xmodem = 1;
	
	static uint16_t crc = 0;
	static uint16_t crc_calc = 0;
	
	uint32_t addr = yysh_getvalue32(tokens[1]);
	uint32_t addr_index = 0;
	
	/* Reset */
	xmodem_mode = XMODEM_SEND_C;
	xmodembuf_index = 0;
	
	/* Execution */
	while (is_xmodem) {
		switch (xmodem_mode) {
			case XMODEM_SEND_C:
				SHELL_PRINTF("%c\b \b", XMODEM_C);
				delay_ms(500);
				break;
			case XMODEM_RECV_OK:
				/* Calculate CRC */
				crc_calc = _yy_xmodem_crc16(&(xmodembuf[3]), 128);
				crc = xmodembuf[XMODEM_CRC_MSB] << 8 | xmodembuf[XMODEM_CRC_LSB];
				
				/* Check CRC */
				if (crc_calc == crc) {
					/* Write to flash */
					uint8_t status;
					status = yy_flash_write(addr + addr_index++ * 128, &(xmodembuf[3]), 128, ERASED_PAGES_8);
					
					
					/* Response ACK */
					SHELL_PRINTF("%c", XMODEM_ACK);
					xmodem_mode = XMODEM_RECV_DATA;
				} else {
					
					/* Response NAK */
					SHELL_PRINTF("%c", XMODEM_NAK);
					xmodem_mode = XMODEM_RECV_DATA;
				}
					
				break;
			case XMODEM_EOT:
				is_xmodem = 0;
				break;
		}
		
	}
	
	delay_ms(3000);
	SHELL_PRINTF("FINISH\r\n");
	
	
	/* End */
	is_xmodem = 0;
}



uint16_t _yy_xmodem_crc16(const uint8_t *addr, uint32_t num)
{
	uint16_t crc = 0;
	for( ; num > 0; num--)
	{
		crc = crc ^ (*addr++ << 8);
		for(int i=0; i < 8; i++)
		{
			if(crc & 0x8000)
			crc = (crc << 1) ^ 0x1021;
			else
			crc <<= 1;
		}
		crc &= 0xFFFF;
	}
	return crc;
}