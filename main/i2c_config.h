#pragma once

#include <stdio.h>
#include "driver/i2c.h"
#include "sdkconfig.h"


#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */
#define I2C_MASTER_NUM I2C_NUMBER(CONFIG_I2C_MASTER_PORT_NUM) /*!< I2C port number for master dev */


#define SCL_PIN_B GPIO_NUM_21
#define SDA_PIN_B GPIO_NUM_22
#define SCL_PIN_S GPIO_NUM_18
#define SDA_PIN_S GPIO_NUM_19

#define SUCCESS 0
#define FAIL -1
#define I2C_MASTER_ACK 0
#define I2C_MASTER_NACK 1


static i2c_port_t i2c_num = 1;

esp_err_t i2c_master_driver_initialize_SGP(void);
esp_err_t i2c_master_driver_initialize_BME(void);

int8_t user_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt);
int8_t user_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt);

int8_t main_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
int8_t main_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
