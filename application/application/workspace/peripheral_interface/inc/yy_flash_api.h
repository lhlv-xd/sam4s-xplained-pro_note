/*
 * yy_flash_api.h
 *
 * Created: 2025/4/7 下午 04:46:21
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_FLASH_API_H_
#define YY_FLASH_API_H_

typedef enum {
	/* 4 of pages to be erased with EPA command*/
	ERASED_PAGES_4=0,
	/* 8 of pages to be erased with EPA command*/
	ERASED_PAGES_8,
	/* 16 of pages to be erased with EPA command*/
	ERASED_PAGES_16,
	/* 32 of pages to be erased with EPA command*/
	ERASED_PAGES_32,
	/* a sector to be erased */
	ERASED_SECTOR,
	/* a bank to be erased */
	ERASED_BANK,
	/* skip erase */
	ERADED_SKIP,
	/* Parameter is not support */
	ERASDE_PAGES_INVALID,
}FLASH_ERADED_MODE_E;


/* Prototype */
uint32_t yy_flash_erase(uint32_t addr, FLASH_ERADED_MODE_E mode);
uint32_t yy_flash_write(uint32_t addr, uint8_t* data_ptr, uint32_t data_size, FLASH_ERADED_MODE_E mode);
uint32_t yy_flash_read(uint32_t addr, uint8_t* data_ptr, uint32_t data_size);
void test_flash_api();

#endif /* YY_FLASH_API_H_ */