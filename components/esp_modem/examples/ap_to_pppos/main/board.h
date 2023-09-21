#pragma once
#ifndef __HAL__
#define __HAL__

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define OUTPUTS_SHIFT_DOUT GPIO_NUM_2
#define OUTPUTS_SHIFT_CLK  GPIO_NUM_3
#define OUTPUTS_SHIFT_LD   GPIO_NUM_21

#define SENSORS_ON         GPIO_NUM_6

#define GSM_PWR_KEY       (1<<7)
#define GSM_PWR_ON        (1<<14)

void board_init();
void board_write(uint32_t val);

#ifdef __cplusplus
}
#endif

#endif
