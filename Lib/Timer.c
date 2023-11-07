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
void delay_us(uint16_t us)
{
	TIM2->CNT=0;
	while (TIM2->CNT < us);
}
void delay_ms(uint16_t ms)
{
	while (ms--)
	{
		delay_us(1000);
	}
}