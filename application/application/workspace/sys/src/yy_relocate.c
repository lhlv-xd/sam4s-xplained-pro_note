/*
 * yy_relocate.c
 *
 * Created: 2025/4/8 上午 10:04:30
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include "yy_relocate.h"

/** 
 * @brief Jump to Application from bootloader.
 * @param vStart The first address of Application
 */
void yy_jump_to_exe(uint32_t vStart)
{
	// -- Disable interrupts
	// Disable IRQ
	__disable_irq();
	// Disable IRQs
	int i;
	for (i = 0; i < 8; i ++) NVIC->ICER[i] = 0xFFFFFFFF;
	// Clear pending IRQs
	for (i = 0; i < 8; i ++) NVIC->ICPR[i] = 0xFFFFFFFF;
	// -- Modify vector table location
	// Barriars
	__DSB();
	__ISB();
	// Change the vector table
	SCB->VTOR = ((uint32_t)vStart);
	// Barriars
	__DSB();
	__ISB();
	// -- Enable interrupts
	__enable_irq();
	// -- Execute application
	__asm ("mov r1, r0 \n"
	"ldr r0, [r1, #4] \n"
	"ldr sp, [r1] \n"
	"blx r0"
	);
}