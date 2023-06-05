#pragma once

#include <stdio.h>
#include "driver/i2c.h"
#include "sdkconfig.h"




// #define _I2C_NUMBER(num) I2C_NUM_0
// #define I2C_NUMBER(num) _I2C_NUMBER(num)

#define WRITE_BIT I2C_MASTER_WRITE              /*!< I2C master write */
#define READ_BIT I2C_MASTER_READ                /*!< I2C master read */
#define ACK_CHECK_EN 0x1                        /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS 0x0                       /*!< I2C master will not check ack from slave */
#define ACK_VAL 0x0                             /*!< I2C ack value */
#define NACK_VAL 0x1                            /*!< I2C nack value */

//#define I2C_MASTER_SCL_IO GPIO_NUM_21               /*!< gpio number for I2C master clock */
//#define I2C_MASTER_SDA_IO GPIO_NUM_22               /*!< gpio number for I2C master data  */
//#define I2C_MASTER_NUM I2C_NUMBER(CONFIG_I2C_MASTER_PORT_NUM) /*!< I2C port number for master dev */
//#define I2C_MASTER_FREQ_HZ 20000        /*!< I2C master clock frequency */
//#define I2C_MASTER_TX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
//#define I2C_MASTER_RX_BUF_DISABLE 0                           /*!< I2C master doesn't need buffer */
//
static i2c_port_t i2c_num_KURWA = I2C_NUM_0;


#define SCL_PIN GPIO_NUM_21
#define SDA_PIN GPIO_NUM_22

#define SUCCESS 0
#define FAIL -1
#define I2C_MASTER_ACK 0
#define I2C_MASTER_NACK 1

esp_err_t i2c_master_driver_initialize(void);
/**
 * @brief generic function for reading I2C data
 * 
 * @param reg_addr register adress to read from 
 * @param reg_data pointer to save the data read 
 * @param len length of data to be read
 * @param intf_ptr 
 * 
 * >init: dev->intf_ptr = &dev_addr;
 * 
 * @return ESP_OK if reading was successful
 */
int8_t main_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);  // *intf_ptr = dev->intf_ptr
/**
 * @brief generic function for writing data via I2C 
 *  
 * @param reg_addr register adress to write to 
 * @param reg_data register data to be written 
 * @param len length of data to be written
 * @param intf_ptr 
 * 
 * @return ESP_OK if writing was successful
 */
int8_t main_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
int8_t user_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt);
int8_t user_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt);

