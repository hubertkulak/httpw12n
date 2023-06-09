#include "sgpbme.h"
#include "i2c_config.h"
#include "SGP30.h"
#include "bme280.h"
#include <math.h>

struct bme280_dev bme280;
struct bme280_data sensdata;
sgp30_dev_t main_sgp30_sensor;


void user_delay_ms(uint32_t ms)
{
  vTaskDelay(ms/portTICK_PERIOD_MS);
}

int my_bme280_init(void)
{
	
  i2c_master_driver_initialize_BME();
  int8_t rslt = BME280_OK;
  uint8_t settings_sel;
  
  bme280.dev_id = BME280_I2C_ADDR_PRIM;
  bme280.intf = BME280_I2C_INTF;
  bme280.read = (void *)user_i2c_read;
  bme280.write = (void *)user_i2c_write;
  bme280.delay_ms = (void *)user_delay_ms;
  printf("calling bme280_init\r\n");
  rslt = bme280_init(&bme280);
  printf("bme280 init result %d\r\n", rslt);

  bme280.settings.osr_h = BME280_OVERSAMPLING_4X;
  bme280.settings.osr_p = BME280_OVERSAMPLING_8X;
  bme280.settings.osr_t = BME280_OVERSAMPLING_4X;
  bme280.settings.filter = BME280_FILTER_COEFF_OFF;
  settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;
  rslt = bme280_set_sensor_settings(settings_sel, &bme280);
  printf("bme280 settings config result %d\r\n", rslt);
	return rslt;
}
void task_bme280_normal_mode() {

//	com_rslt += bme280_set_oversamp_pressure(BME280_OVERSAMPLING_16X);
//	com_rslt += bme280_set_oversamp_temperature(BME280_OVERSAMPLING_2X);
//	com_rslt += bme280_set_oversamp_humidity(BME280_OVERSAMPLING_1X);

//	com_rslt += bme280_set_standby_durn(BME280_STANDBY_TIME_1_MS);
//	com_rslt += bme280_set_filter(BME280_FILTER_COEFF_16);
	
//	com_rslt += bme280_set_sensor_settings(BME280_NO_OVERSAMPLING,
	int com_rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, &bme280);
	if (com_rslt == SUCCESS) {
    while (true) {
      vTaskDelay(1000 / portTICK_PERIOD_MS);

      com_rslt = bme280_get_sensor_data(BME280_ALL, &sensdata ,&bme280);
      if (com_rslt == SUCCESS) {
   			//long int p = sensdata.pressure - 10000000 + 1000000;
			//long int pi = p / 1000;
			//long int pd = p - pi * 100;
			
			float altitude = pow(1013.25f / getPressure(), 0.190234f) - 1;
			altitude *= ((15.0f + 273.15f) / 0.0065f);

			printf("odczyt: %.2f degC / %.2f hPa / %.2f wilgotnosc \n", getTemp(), getPressure(), getHumid());
		//	printf("pressure wartosci: z czujnika %ld p %ld pi %ld pd %ld\n", sensdata.pressure, p, pi, pd);
			
			printf("alti %.5f\n", altitude);
		 } else {
			printf("measure error. code: %d", com_rslt);
      }
    }
  } else {
    printf("init or setting error. code: %d", com_rslt);
  }

  vTaskDelete(NULL);
}

void init_sgp(){
	i2c_master_driver_initialize_SGP();
    printf("SGP30 main task initializing...");

    sgp30_init(&main_sgp30_sensor, (sgp30_read_fptr_t)main_i2c_read, (sgp30_write_fptr_t)main_i2c_write);

    // SGP30 needs to be read every 1s and sends TVOC = 400 14 times when initializing
    for (int i = 0; i < 14; i++) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        sgp30_IAQ_measure(&main_sgp30_sensor);
        printf("SGP30 Calibrating... TVOC: %d,  eCO2: %d\n",  main_sgp30_sensor.TVOC, main_sgp30_sensor.eCO2);
    }

    // Read initial baselines 
    uint16_t eco2_baseline, tvoc_baseline;
    sgp30_get_IAQ_baseline(&main_sgp30_sensor, &eco2_baseline, &tvoc_baseline);
    printf("BASELINES - TVOC: %d,  eCO2: %d\n",  tvoc_baseline, eco2_baseline);

}

void read_sgp(){

   printf("SGP30 main task is running...");
    while(1) {
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        sgp30_IAQ_measure(&main_sgp30_sensor);

        printf("TVOC: %d,  eCO2: %d\n",  main_sgp30_sensor.TVOC, main_sgp30_sensor.eCO2);
    }
}

float getTemp(){
	return (float) sensdata.temperature / 100.0f;
}
float getHumid(){
  	int hi = sensdata.humidity / 1024;
	int hd = sensdata.humidity * 100 / 1024 - hi * 100;

	return (float) hi + (float) hd / 100.0f;
}
float getPressure(){
	//long int p = sensdata.pressure - 10000000 + 1000000;
	//return (float) p / 1000.0f;
	return (float) sensdata.pressure / 10000.0f;
}
int getTvoc(){
	return main_sgp30_sensor.TVOC;
}
int getCO2(){
	return main_sgp30_sensor.eCO2;	
}

