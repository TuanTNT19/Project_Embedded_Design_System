#include "Timer.h"
#include "stm32f1xx.h"
void TIM2_config()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //Enable TIMEeR2 clock
	TIM2->PSC = 7;
	TIM2->ARR = 65535;
	TIM2->CR1 = (1<<0);//enable counter
	while (!(TIM2->SR & TIM_SR_UIF));
}
void delay_us2(uint16_t us)
{
	TIM2->CNT=0;
	while (TIM2->CNT < us);
}
void delay_ms2(uint16_t ms)
{
	while (ms--)
	{
		delay_us2(1000);
	}
}
void TIM1_config()
{
	RCC->APB2ENR |=(1<<11);
	TIM1->PSC = 7;
	TIM1->ARR = 65535;
	TIM1->CR1 = (1<<0);//enable counter
	while (!(TIM1->SR & TIM_SR_UIF));
}
void delay_us1(uint16_t us)
{
	TIM1->CNT=0;
	while (TIM1->CNT < us);
}
void delay_ms1(uint16_t ms)
{
	while (ms--)
	{
		delay_us1(1000);
	}
}