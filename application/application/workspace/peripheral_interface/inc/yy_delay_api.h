/*
 * yy_delay_api.h
 *
 * Created: 2025/5/19 下午 02:51:10
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_DELAY_API_H_
#define YY_DELAY_API_H_

/* Macro */
// Loop Times (Corrected by clock)
#define DELAY_1S_TIMES 30000000
#define DELAY_1MS_TIMES 30000
#define DELAY_1US_TIMES 30


/* Prototype */
void yy_delay_1s_by_for();
void yy_delay_1s_by_while();


#endif /* YY_DELAY_API_H_ */