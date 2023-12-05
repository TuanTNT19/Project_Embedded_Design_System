#ifndef PWM_H
#define PWM_H
#include <stdint.h>
void TIM1_PWM_Init();
void TIM1_PWM_Config(uint8_t channel);
void TIM1_PWM_duty(uint8_t channel, uint16_t duty);
void TIM1_PWM_Config_Multi(uint8_t number);
void TIM2_PWM_Init();
void TIM2_PWM_Config(uint8_t channel);
void TIM2_PWM_duty(uint8_t channel, uint16_t duty);
void TIM3_PWM_Init();
void TIM3_PWM_Config(uint8_t channel);
void TIM3_PWM_Config_Multi(uint8_t number);
void TIM3_PWM_duty(uint8_t channel, uint16_t duty);
void TIM4_PWM_Init();
void TIM4_PWM_Config(uint8_t channel);
void TIM4_PWM_Config_Multi(uint8_t number);
void TIM4_PWM_duty(uint8_t channel, uint16_t duty);


#endif