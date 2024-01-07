/*
 * TIM_Configure.h
 *
 *  Created on: Jun 5, 2023
 *      Author: nguye
 */

#ifndef TIM_TIM_CONFIGURE_H_
#define TIM_TIM_CONFIGURE_H_

#include "stdint.h"

void TIM1_Configure(uint16_t PSC, uint32_t ARR);
void TIM2_Configure(uint16_t PSC, uint32_t ARR);
void TIM4_Configure(uint16_t PSC, uint32_t ARR);
void delay_us2(uint16_t us);
void delay_ms2(uint16_t ms);
void delay_us1(uint16_t us);
void delay_ms1(uint16_t ms);

#endif /* TIM_TIM_CONFIGURE_H_ */
