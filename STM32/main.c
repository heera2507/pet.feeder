/**
 * Smart Pet Feeder - STM32 Subsystem
 * ----------------------------------
 * Logs temperature and humidity data (DHT11)
 * to an SD card via FATFS, with LED indicators
 * for success/error.
 */

#include "stm32f4xx.h"
#include "ff.h"
#include "diskio.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define SUCCESS_LED_PIN GPIO_PIN_8
#define ERROR_LED_PIN GPIO_PIN_9

void setup_GPIO(void);
void set_LED(uint32_t Pin, uint32_t State);
void delayMicroseconds(uint32_t microseconds);

FATFS fs;
FIL fil;
FRESULT fresult;

int main(void) {
    float TEMP = 0.0f, HUM = 0.0f;
    char buffer[64];

    setup_GPIO();
    f_mount(&fs, "", 0);

    while (1) {
        sprintf(buffer, "Temperature: %.2f C, Humidity: %.2f%%\r\n", TEMP, HUM);

        fresult = f_open(&fil, "DHT11DATA.txt", FA_OPEN_APPEND | FA_WRITE);
        if (fresult == FR_OK) {
            f_puts(buffer, &fil);
            f_close(&fil);
            set_LED(SUCCESS_LED_PIN, 1);
            set_LED(ERROR_LED_PIN, 0);
        } else {
            set_LED(ERROR_LED_PIN, 1);
            set_LED(SUCCESS_LED_PIN, 0);
        }

        delayMicroseconds(3000000);
    }
}
