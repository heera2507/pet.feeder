#include "stm32f4xx.h"                 // Device header
#include "stdio.h"
#include "stdint.h"
#include "ff.h"  // FATFS
#include "diskio.h"
#include <string.h>

#define SUCCESS_LED_PIN GPIO_PIN_8
#define ERROR_LED_PIN GPIO_PIN_9

void setup_GPIO(void);
void set_LED(uint32_t Pin, uint32_t State);
void USART2_Init(void);
void readDHT11(float *TEMP, float *HUM);
void USART2_write(uint8_t* charString, uint16_t len);
void delayMicroseconds(uint32_t microseconds);

FATFS fs;
FIL fil;
FRESULT fresult;

int main(void) {
    uint8_t DHT11_DATA[5] = {0, 0, 0, 0, 0};
    uint8_t i, j;
    float TEMP, HUM;
    char buffer[64];

    setup_GPIO();
    // Initialise SD card and mount filesystem
    f_mount(&fs, "", 0);
    while (1) {
        int Response = 1;

        if (Response == 1) {
            TEMP = (float)DHT11_DATA[2];
            HUM = (float)DHT11_DATA[0];
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
}

void setup_GPIO(void) {
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
    GPIOA->MODER |= (GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0);
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_8 | GPIO_OTYPER_OT_9);
    GPIOA->OSPEEDER |= (GPIO_OSPEEDER_OSPEEDER8 | GPIO_OSPEEDER_OSPEEDER9);
    GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR8 | GPIO_PUPDR_PUPDR9);
}

void set_LED(uint32_t Pin, uint32_t State) {
    if (State) {
        GPIOA->BSRR = Pin;
    } else {
        GPIOA->BSRR = (Pin << 16);
    }
}

void delayMicroseconds(uint32_t microseconds) {
    RCC->APB1ENR |= 0x1; // Enable TIM2 clock
    TIM2->PSC = 16 - 1;  // Prescaler value
    TIM2->ARR = microseconds;
    TIM2->CNT = 0;
    TIM2->CR1 = 1; // Starts the timer

    while (!(TIM2->SR & 1)) {};

    TIM2->SR &= ~1;
}
