/*
 * yy_i2c_api.h
 *
 * Created: 2025/4/16 下午 05:56:39
 *  Author: Yuyi_Chen
 */ 


#ifndef YY_I2C_API_H_
#define YY_I2C_API_H_

/* User Config */
#define SLAVE_ADDRESS 0x50

/* Define */
#define SET_PIN(pin) (PIO_##pin##_IDX)
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#define TWI0_SDA           SET_PIN(PA3)
#define TWI0_SCL           SET_PIN(PA4)
#define TWI1_SDA          SET_PIN(PB4)
#define TWI1_SCL          SET_PIN(PB5)

/* Enum */
typedef enum {
	I2C_TWI0,
	I2C_TWI1
}I2C_INTERFACE_E;

/* Prototype */
void yy_i2c_slave_init(I2C_INTERFACE_E interface, uint32_t slave_address);
void yy_i2c_slave_interrupt_init(I2C_INTERFACE_E interface);


#endif /* YY_I2C_API_H_ */