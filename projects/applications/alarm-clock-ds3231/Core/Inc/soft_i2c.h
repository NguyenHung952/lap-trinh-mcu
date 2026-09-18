#ifndef SOFT_I2C_H_
#define SOFT_I2C_H_

#include <stdint.h>

void soft_i2c_init(void);
void soft_i2c_start(void);
void soft_i2c_stop(void);
uint8_t soft_i2c_write_byte(uint8_t data);
uint8_t soft_i2c_read_byte(uint8_t send_ack);

#endif /* SOFT_I2C_H_ */
