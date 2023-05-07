#include "wifi.h"

double temp = 1.5;
double press = 1.5;
double hum = 1.5;




char html_page[] = "<!DOCTYPE HTML><html>\n"
                   "<head>\n"
                   "  <title>W12N STACJA SIECI BEZPRZEWODOWYCH</title>\n"
                   "  <meta http-equiv=\"refresh\" content=\"10\">\n"
                   "  <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
                   "  <link rel=\"stylesheet\" href=\"https://use.fontawesome.com/releases/v5.7.2/css/all.css\" integrity=\"sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr\" crossorigin=\"anonymous\">\n"
                   "  <link rel=\"icon\" href=\"data:,\">\n"
                   "  <style>\n"
                   "    html {font-family: Arial; display: inline-block; text-align: center;}\n"
                   "    p {  font-size: 1.2rem;}\n"
                   "    body {  margin: 0;}\n"
                   "    .topnav { overflow: hidden; background-color: #4B1D3F; color: white; font-size: 1.7rem; }\n"
                   "    .content { padding: 20px; }\n"
                   "    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }\n"
                   "    .cards { max-width: 700px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); }\n"
                   "    .reading { font-size: 2.8rem; }\n"
                   "    .card.pm25 { color: #0e7c7b; }\n"
                   "    .card.pm10 { color: #17bebb; }\n"
                   "    .card.pm1 { color: #3fca6b; }\n"
                   "    .card.gas { color: #d62246; }\n"
                   "  </style>\n"
                   "</head>\n"
                   "<body>\n"
                   "  <div class=\"topnav\">\n"
                   "    <h3>W12N STACJA SIECI BEZPRZEWODOWYCH</h3>\n"
                   "  </div>\n"
                   "  <div class=\"content\">\n"
                   "    <div class=\"cards\">\n"
                   "      <div class=\"card pm25\">\n"
                   "        <h4><i class=\"fas fa-globe-europe\"></i> PM25</h4><p><span class=\"reading\">%.2f ug/m3</span></p>\n"
                   "      </div>\n"
                   "      <div class=\"card pm10\">\n"
                   "        <h4><i class=\"fas fa-globe-europe\"></i> PM10</h4><p><span class=\"reading\">%.2f ug/m3</span></p>\n"
                   "      </div>\n"
                   "      <div class=\"card pm1\">\n"
                   "        <h4><i class=\"fas fa-globe-europe\"></i> PM1</h4><p><span class=\"reading\">%.2f ug/m3</span></p>\n"
                   "      </div>\n"
                   "    </div>\n"
                   "  </div>\n"
                   "</body>\n"
                   "</html>";

esp_err_t send_web_page(httpd_req_t *req)
{

    

    //read_pms3003();    

    temp =  rpm25();
    hum = rpm10();
    press = rpm1();

    int response;
    
    char response_data[sizeof(html_page) + 50];
    memset(response_data, 0, sizeof(response_data));
    sprintf(response_data, html_page, temp, hum, press);
    response = httpd_resp_send(req, response_data, HTTPD_RESP_USE_STRLEN);

        

    return response;
}

esp_err_t get_req_handler(httpd_req_t *req)
{
    return send_web_page(req);
}

httpd_uri_t uri_get = {
    .uri = "/",
    .method = HTTP_GET,
    .handler = get_req_handler,
    .user_ctx = NULL};

httpd_handle_t setup_server(void)
{
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    httpd_handle_t server = NULL;

    if (httpd_start(&server, &config) == ESP_OK)
    {
        httpd_register_uri_handler(server, &uri_get);
        init_pms(); //incjalizacja czujnika
    }

    return server;
}