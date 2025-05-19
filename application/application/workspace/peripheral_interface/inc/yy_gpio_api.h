/*
 * yy_gpio_api.h
 *
 * Created: 2025/5/16 下午 04:40:25
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_GPIO_API_H_
#define YY_GPIO_API_H_


/* Macro */
#define SET_PIN(pin) (PIO_##pin##_IDX)

// All GPIO Register
#define GPIOA_REGISTERS PIOA
#define GPIOB_REGISTERS PIOB
#define GPIOC_REGISTERS PIOC

// GPIO Interrupt
#define GPIOA_IRQ PIOA_IRQn
#define GPIOB_IRQ PIOB_IRQn
#define GPIOC_IRQ PIOC_IRQn

// Interrupt Handler
#define GPIOA_HANDLER PIOA_Handler
#define GPIOB_HANDLER PIOB_Handler
#define GPIOC_HANDLER PIOC_Handler


/* GPIO */
#define GPIO_PA24 SET_PIN(PA24)
#define GPIO_PA25 SET_PIN(PA25)


/* Prototype */
void yy_gpio_init();
void yy_gpio_pa24_handler(uint32_t a, uint32_t b);
void test_gpio_pa24_interrupt();

#endif /* YY_GPIO_API_H_ */