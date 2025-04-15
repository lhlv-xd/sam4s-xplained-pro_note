/*
 * yy_rstc_api.h
 *
 * Created: 2025/4/15 上午 11:42:05
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_RSTC_API_H_
#define YY_RSTC_API_H_

/* Enum */
typedef enum {
	GENERAL_RST = 0,
	BACKUP_RST,
	WDT_RST,
	SOFT_RST,
	USER_RST,
	RESET_TYPE_MAX
}RESET_TYPE_E;

/* Prototype */
void yy_check_reset_reason();



#endif /* YY_RSTC_API_H_ */