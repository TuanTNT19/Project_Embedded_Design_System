#ifndef TIMER_H
#define TIMER_H
#include <stdint.h>

void TIM2_config();
void delay_us1(uint16_t us);
void delay_ms1(uint16_t ms);
void TIM1_config();
void delay_us2(uint16_t us);
void delay_ms2(uint16_t ms);
#endif