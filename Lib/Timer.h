#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

void TIM2_config();
void delay_us(uint16_t us);
void delay_ms(uint16_t ms);
#endif