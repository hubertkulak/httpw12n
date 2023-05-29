#include "adc.h"

esp_adc_cal_characteristics_t adc_chars;

#define ADC1_EXAMPLE_CHAN0          ADC1_CHANNEL_0

//ADC Attenuation
#define ADC_EXAMPLE_ATTEN           ADC_ATTEN_DB_11

#define ADC_EXAMPLE_CALI_SCHEME     ESP_ADC_CAL_VAL_EFUSE_VREF

uint32_t voltage = 0;

void adc_calibration_init(void)
{
    esp_err_t ret;


    ret = esp_adc_cal_check_efuse(ADC_EXAMPLE_CALI_SCHEME);
    if (ret == ESP_ERR_NOT_SUPPORTED) {
        printf("\nCalibration scheme not supported, skip software calibration\n");
    } else if (ret == ESP_ERR_INVALID_VERSION) {
        printf("eFuse not burnt, skip software calibration");
    } else if (ret == ESP_OK) {

        esp_adc_cal_characterize(ADC_UNIT_1, ADC_EXAMPLE_ATTEN, ADC_WIDTH_BIT_DEFAULT, 0, &adc_chars);
    } else {
        printf("Invalid arg");
    }

}

void init_adc(void){
  adc_calibration_init();

  //ADC1 config
  ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
  ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_EXAMPLE_CHAN0, ADC_EXAMPLE_ATTEN));
}

void water(void *arg)
{



   for(;;){
    uint32_t reading = adc1_get_raw(ADC1_EXAMPLE_CHAN0);
    voltage = esp_adc_cal_raw_to_voltage(reading, &adc_chars);
    printf("\ncali data: %ld mV\n", voltage);
    vTaskDelay(pdMS_TO_TICKS(2000));
   }

}

float rvoltage()
{
  return voltage;
}
