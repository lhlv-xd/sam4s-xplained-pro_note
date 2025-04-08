/*
 * yy_systick_api.h
 *
 * Created: 2025/4/8 下午 04:19:16
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_SYSTICK_API_H_
#define YY_SYSTICK_API_H_

/* extern */
extern uint32_t SystemCoreClock; // core clock


/* Prototype */
void yy_systick_init(void);
uint32_t yy_get_systick(void);
void test_systick_api();


#endif /* YY_SYSTICK_API_H_ */