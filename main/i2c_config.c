#include <stdio.h>
#include "i2c_config.h"

esp_err_t i2c_master_driver_initialize(void) {
//    int i2c_master_port = I2C_MASTER_NUM; 
//    int i2c_master_port = I2C_MASTER_NUM;
	i2c_config_t conf;

    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = SDA_PIN;
    conf.scl_io_num = SCL_PIN;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 50000;//I2C_MASTER_FREQ_HZ;
	conf.clk_flags = 0;

    i2c_param_config(I2C_NUM_0, &conf);
   // i2c_param_config(i2c_master_port, &conf);
    return i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);
}

int8_t main_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) { // *intf_ptr = dev->intf_ptr
    int8_t ret = 0; /* Return 0 for Success, non-zero for failure */

    if (len == 0) {
        return ESP_OK;
    }

    uint8_t chip_addr = *(uint8_t*)intf_ptr;
    
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    
    if (reg_addr != 0xff) {
        i2c_master_write_byte(cmd, (chip_addr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
        i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
        i2c_master_start(cmd);
    }
    
    i2c_master_write_byte(cmd, (chip_addr << 1) | I2C_MASTER_READ, ACK_CHECK_EN);

    if (len > 1) {
        i2c_master_read(cmd, reg_data, len - 1, ACK_VAL);
    }
    i2c_master_read_byte(cmd, reg_data + len - 1, NACK_VAL);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(i2c_num_KURWA, cmd, 1000 / portTICK_PERIOD_MS);
    
    i2c_cmd_link_delete(cmd);
    
    return ret;
}

int8_t main_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    int8_t ret = 0; /* Return 0 for Success, non-zero for failure */

    uint8_t chip_addr = *(uint8_t*)intf_ptr;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (chip_addr << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    
    if (reg_addr != 0xFF) {
        i2c_master_write_byte(cmd, reg_addr, ACK_CHECK_EN);
    }

    i2c_master_write(cmd, reg_data, len, ACK_CHECK_EN);
    i2c_master_stop(cmd);

    ret = i2c_master_cmd_begin(i2c_num_KURWA, cmd, 1000 / portTICK_PERIOD_MS);
    
    i2c_cmd_link_delete(cmd);
    
    return ret;
}
int8_t user_i2c_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt)
{
  int32_t iError = 0;

  esp_err_t espRc;
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();

  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);

  i2c_master_write_byte(cmd, reg_addr, true);
  i2c_master_write(cmd, reg_data, cnt, true);
  i2c_master_stop(cmd);

  espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 200/portTICK_PERIOD_MS);
  //  printf("in user_i2c_read, i2c_master_cmd_begin returns %d\r\n", espRc);
  if (espRc == ESP_OK) {
    iError = SUCCESS;
  } else {
    iError = FAIL;
  }
  i2c_cmd_link_delete(cmd);

  return (int8_t)iError;
}

int8_t user_i2c_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *reg_data, uint8_t cnt)
{
  int32_t iError = 0;
  esp_err_t espRc;

  i2c_cmd_handle_t cmd = i2c_cmd_link_create();

  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
  i2c_master_write_byte(cmd, reg_addr, true);

  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);

  if (cnt > 1) {
    i2c_master_read(cmd, reg_data, cnt-1, I2C_MASTER_ACK);
  }
  i2c_master_read_byte(cmd, reg_data+cnt-1, I2C_MASTER_NACK);
  i2c_master_stop(cmd);

  espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 200/portTICK_PERIOD_MS);
  if (espRc == ESP_OK) {
    iError = SUCCESS;
  } else {
    iError = FAIL;
  }

  i2c_cmd_link_delete(cmd);

  return (int8_t)iError;
}

