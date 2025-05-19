/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "yy_peripheral_init.h"
#include "yy_shell_interface.h"
#include "yy_relocate.h"

int main (void)
{
	/* Initialize */
	board_init();
	yy_peripheral_init();
	yy_shell_init();
	
	/* Test */
	//test_flash_api();
	//test_systick_api();
	test_gpio_pa24_interrupt();

	/* Start */
	yy_check_reset_reason();
	yy_show("\r\n------- Start -------\r\n");

	while(1) {
		if (exec_shell_command) {
			exec_shell_command = 0;
			yysh_exec(shellbuf);
		}
	}
}
