/*
 * yy_rstc_api.c
 *
 * Created: 2025/4/15 上午 11:41:53
 *  Author: Yuyi_Chen
 */ 

/* RSTC (Reset Controller) */
#include <asf.h>
#include "yy_rstc_api.h"
#include "yy_peripheral_init.h"

/** 
 * @brief Display the reason for this reboot.
 */
void yy_check_reset_reason() 
{
	uint32_t reset_status = RSTC->RSTC_SR;
	reset_status = (reset_status & RSTC_SR_RSTTYP_Msk) >> RSTC_SR_RSTTYP_Pos;
	yy_show("\r\nReason for last reset (0x%08x):", RSTC->RSTC_SR);
	
	switch (reset_status) {
		case GENERAL_RST:
			yy_show("First power-up reset\r\n");
			break;
		case BACKUP_RST:
			yy_show("Return from Backup Mode\r\n");
			break;
		case WDT_RST:
			yy_show("Watchdog fault occurred\r\n");
			break;
		case SOFT_RST:
			yy_show("Processor reset required by the software\r\n");
			break;
		case USER_RST:
			yy_show("NRST pin detected low\r\n");
			break;
		default:
			yy_show("other reason\r\n");
			break;
	};
}