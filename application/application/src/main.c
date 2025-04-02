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

int main (void)
{
	/* Initialize */
	board_init();
	yy_peripheral_init();
	
	/* Start */
	printf("------- Start -------\r\n");

	/* SHELL*/
	printf("> ");
	while (1) {
		uint8_t data;

		/* block */
		data = getchar();
		printf("%c", data);
		
		if (data == '\n' || data == '\r') {
			printf("\r\n");
			printf("> ");
		}
	}
}
