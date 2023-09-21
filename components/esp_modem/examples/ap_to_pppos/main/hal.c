#include "hal.h"


void hal_init(){
    // gpio_config_t cfg = {
    //     .intr_type = GPIO_INTR_DISABLE,
    //     .mode = GPIO_MODE_OUTPUT,
    //     .pin_bit_mask = (1ULL << OUTPUTS_SHIFT_DOUT) | (1ULL << OUTPUTS_SHIFT_CLK) | (1ULL << OUTPUTS_SHIFT_LD) | (1ULL << SENSORS_ON),
    //     .pull_down_en = GPIO_PULLDOWN_DISABLE,
    //     .pull_up_en = GPIO_PULLUP_DISABLE
    // };
    // gpio_config(&cfg);
    gpio_set_level(SENSORS_ON, 1);
    gpio_set_level(OUTPUTS_SHIFT_DOUT, 0);
    gpio_set_level(OUTPUTS_SHIFT_CLK, 0);
    gpio_set_level(OUTPUTS_SHIFT_LD, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
}

void hal_write(uint32_t val){
    for(int32_t i=0;i<32;i++){
    if (val & 0x80000000)
        gpio_set_level(OUTPUTS_SHIFT_DOUT, 1); // Data -> 1
    else
        gpio_set_level(OUTPUTS_SHIFT_DOUT, 0);// Data -> 0
    vTaskDelay(pdMS_TO_TICKS(10));
    val = val << 1; //shift data
    gpio_set_level(OUTPUTS_SHIFT_CLK, 1); // Clock 0 -> 1
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(OUTPUTS_SHIFT_CLK, 0); // Clock 1 -> 0
    }
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(OUTPUTS_SHIFT_LD, 1); // LD 0 -> 1
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(OUTPUTS_SHIFT_LD, 0); // LD 1 -> 0
}