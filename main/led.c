#include "led.h"



void configled(int pin){
    gpio_reset_pin(pin);
    gpio_set_direction(pin, GPIO_MODE_OUTPUT);
}

void ledstateon(int pin){
   gpio_set_level(pin, 1);
}

void ledstateoff(int pin){
   gpio_set_level(pin, 0);
}
