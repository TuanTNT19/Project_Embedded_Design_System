/*
 * TIM_Configure.c
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */

#include "TIM_Configure.h"
#include <stm32f1xx.h>

#define UP  1
#define DO  0
void TIM2_Configure(uint16_t PSC, uint32_t ARR){
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC = PSC;
	TIM2->ARR = ARR;
	TIM2->CR1 |= (1 << 0);
	while (!(TIM2->SR & TIM_SR_UIF));
}
void TIM1_Configure(uint16_t PSC, uint32_t ARR){
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	TIM1->PSC = PSC;
	TIM1->ARR = ARR;
	TIM1->CR1 |= (1 << 0);
	while (!(TIM1->SR & TIM_SR_UIF));
}
void TIM4_Configure(uint16_t PSC, uint32_t ARR){
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->PSC = PSC;
	TIM4->ARR = ARR;
	TIM4->DIER |= TIM_DIER_UIE;
	TIM4->CR1 |= TIM_CR1_ARPE | TIM_CR1_URS;
	TIM4->EGR |= TIM_EGR_UG;
	NVIC_EnableIRQ(TIM4_IRQn);
	TIM4->CR1 |= TIM_CR1_CEN;
}
void delay_us2(uint16_t us){
	TIM2->CNT = 0;
	while (TIM2->CNT < us);
}
void delay_us1(uint16_t us){
	TIM1->CNT = 0;
	while (TIM1->CNT < us);
}
void delay_ms2(uint16_t ms){
	while (ms--){
		delay_us2(1000);
	}
}
void delay_ms1(uint16_t ms){
	while (ms--){
		delay_us1(1000);
	}
}
