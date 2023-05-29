#include "pms3003.h"

#define set_PIN  GPIO_NUM_0


const int uart_buffer_size = 1024;

#define TAGP "pms3003"

const uart_port_t uart_num = UART_NUM_2;

uart_config_t uart_config = {
    .baud_rate = 9600,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 122,
    .source_clk = UART_SCLK_DEFAULT,
};

int pm1;
int pm25;
int pm10;

void init_pms(void)
{
    ESP_LOGI(TAGP, "uart init");
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    ESP_LOGI(TAGP, "uart set pin");
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 17, 16, 18, 19));

    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, 0, 0, NULL, 0));

    gpio_set_direction(set_PIN, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(set_PIN, GPIO_PULLDOWN_ONLY);

    uart_write_bytes(uart_num, "\x42\x4d\x00\x1c\x00\x00\x01\x73", 8);
}

void read_pms3003(void * arg)
{
    uint8_t buff[32];

    int len = 0;
    int frame_count = 0;
  for(;;)
  {
    ESP_LOGI(TAGP, "\nuart data read\n");

    uart_get_buffered_data_len(uart_num, (size_t*)&len);
    len = uart_read_bytes(uart_num, buff, 32, 100);


    len = uart_read_bytes(uart_num, buff, 32, 100);
    //gpio_set_level(set_PIN, 1); //set button on
    printf("\n0: %02x \n1: %02x\nlen: %d \n", buff[0], buff[1], len);

        if(len >= 32 && buff[0]==0x42 && buff[1]==0x4d)
        {
            ESP_LOGI(TAGP, "got frame of %d bytes", len);

            pm25=((buff[10]<<8) + buff[11]);
            pm10=((buff[12]<<8) + buff[13]);
            pm1 =((buff[6]<<8) + buff[7]);
        

            ESP_LOGI(TAGP, "got PM1 equal: %d", pm1);
            ESP_LOGI(TAGP, "got PM10 equal: %d", pm10);
            ESP_LOGI(TAGP, "got PM25 equal: %d", pm25);
        }
        else
        {
            ESP_LOGI(TAGP, "Frame is invalid");
        }

  }
}

int rpm25()
{
    return pm25;
}

int rpm10()
{
    return pm10;
}

int rpm1()
{
    return pm1;
}
