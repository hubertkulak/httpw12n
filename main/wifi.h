#include <stdio.h>
#include <stdlib.h>
#include <string.h> //Requires by memset
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include <esp_http_server.h>

#include "esp_event.h"
#include "freertos/event_groups.h"
#include "esp_log.h"

#include <lwip/sockets.h>
#include <lwip/sys.h>
#include <lwip/api.h>
#include <lwip/netdb.h>

#include "pms3003.h"
#include "adc.h"
#include "i2c_config.h"
#include "sgpbme.h"

httpd_handle_t setup_server(void);
esp_err_t get_req_handler(httpd_req_t *req);
esp_err_t send_web_page(httpd_req_t *req);
