/*
 * yy_flash_api.c
 *
 * Created: 2025/4/7 下午 04:46:05
 *  Author: Yuyi_Chen
 */ 

#include <asf.h>
#include <string.h>
#include "yy_flash_api.h"

/** 
 * @brief Erase flash between 0x400000 and 0x600000
 * @param[in] addr The start of address be erased.
 * @param[in] mode Clear flash of a specific size.
 * @reval 0 if successful; otherwise returns an error code.
 */
uint32_t yy_flash_erase(uint32_t addr, FLASH_ERADED_MODE_E mode)
{
	uint32_t status;
	/* Flash Init */
	status = flash_init(FLASH_ACCESS_MODE_128, 6);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	uint32_t page_size = 512;
	uint32_t total_size = (mode < ERASED_SECTOR) ? ((2 << (mode+2)) * 512) : (64 * 1024);
	if (mode == ERASED_BANK) {
		total_size = 1024 * 1024; // 1024 kBytes	
	}
	
	/* Unlock */
	status = flash_unlock(addr, addr + total_size - 1, 0, 0);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	/* Erase */
	switch (mode) {
		case ERASED_PAGES_4:
		case ERASED_PAGES_8:
		case ERASED_PAGES_16:
		case ERASED_PAGES_32:			
			status = flash_erase_page(addr, mode);
			break;
		case ERASED_SECTOR:
			status = flash_erase_sector(addr);
			break;
		case ERASED_BANK:
			status = flash_erase_all(addr);
			break;
		default:
			return FLASH_RC_INVALID;
			break;
		
	}
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	/* Lock */
	status = flash_lock(addr, addr + total_size - 1, 0, 0);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	return FLASH_RC_OK;
}

/** 
 * @brief Write a data buffer on flash.
 * @param[in] addr The start of address be erased.
 * @param[in] data_ptr data buffer
 * @param[in] data_size size of data buffer in bytes
 * @param[in] mode Clear flash of a specific size.
 * @reval 0 if successful; otherwise returns an error code.
 */
uint32_t yy_flash_write(uint32_t addr, uint8_t* data_ptr, uint32_t data_size, FLASH_ERADED_MODE_E mode)
{
	uint32_t status;
	/* Flash Init */
	status = flash_init(FLASH_ACCESS_MODE_128, 6);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	uint32_t page_size = 512;
	uint32_t total_size = (mode < ERASED_SECTOR) ? ((2 << (mode+2)) * 512) : (64 * 1024);
	if (mode == ERASED_BANK) {
		total_size = 1024 * 1024; // 1024 kBytes
	}
	
	/* Unlock */
	status = flash_unlock(addr, addr + total_size - 1, 0, 0);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	/* Erase */
	switch (mode) {
		case ERASED_PAGES_4:
		case ERASED_PAGES_8:
		case ERASED_PAGES_16:
		case ERASED_PAGES_32:
			status = flash_erase_page(addr, mode);
			break;
		case ERASED_SECTOR:
			status = flash_erase_sector(addr);
			break;
		case ERASED_BANK:
			if (addr < 0x500000) {
				return FLASH_RC_INVALID;
			}
			status = flash_erase_all(addr);
			break;
		default:
			return FLASH_RC_INVALID;
		break;
		
	}
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	/* Write */
	status = flash_write(addr, data_ptr, data_size, 0);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	/* Lock */
	status = flash_lock(addr, addr + total_size - 1, 0, 0);
	if (status != FLASH_RC_OK) {
		return status;
	}
	
	return FLASH_RC_OK;
}

/** 
 * @brief read flash to data buffer.
 * @param[in] addr The start of address be erased.
 * @param[out] data_ptr data buffer
 * @param[in] data_size size of data buffer be read in bytes
 * @reval actually read size
 */
uint32_t yy_flash_read(uint32_t addr, uint8_t* data_ptr, uint32_t data_size)
{
	if (addr < 0x400000 || addr > 0x5fffff) {
		return 0; // return size: 0
	}
	
	data_size = (addr + data_size <0x600000) ? (data_size) : (0x600000 - addr);
	memcpy(data_ptr, (uint8_t *)addr, data_size);
	
	return data_size;
}

/** 
 * @brief test all flash api in this file.
 */
void test_flash_api()
{
	uint32_t addr = 0x420000;
	uint8_t buf[256];
	uint32_t status;
	for(uint32_t i = 0; i < 256; i++) {
		buf[i] = i;
	}
	
	/* test flash write */
	status = yy_flash_write(addr, buf, 256, ERASED_PAGES_8);
	printf("yy_flash_wrtie status: %d\r\n", status);
	
	
	/* test flash erase */
	//status = yy_flash_erase(addr, ERASED_SECTOR);
	//printf("yy_flash_erase status: %d\r\n", status);
	
	/* test flash read */
	uint8_t rbuf[256];
	status = yy_flash_read(addr, rbuf, 256);
	printf("yy_flash_read status: %d\r\n", status);
	
	for (uint32_t i = 0; i < 256; i++) {
		printf("%x, ",rbuf[i]);
	}
}