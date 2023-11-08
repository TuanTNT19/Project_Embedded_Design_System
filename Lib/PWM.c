#include "PWM.h"
#include "stm32f1xx.h"
void TIM1_PWM_Init()
{
	RCC->APB2ENR |=(1<<11);
}
void TIM1_PWM_Config(uint8_t channel)
{
	RCC->APB2ENR |=(1<<2);//enable clock for GPIOA
	if (channel == 1)
	{
	GPIOA->CRH &=(0xFFFF0000);
	GPIOA->CRH |=(10<<0); //set gpioa pin 8 as output alternate function push pull for timer 1 channel 1
	TIM1->CCER |=(1<<0);
	TIM1->CCMR1 |=(6<<4);
	TIM1->CCR1=0;
	}
	else if (channel == 2)
	{
	GPIOA->CRH &=(0xFFFF0000);
	GPIOA->CRH |=(10<<4);//set gpioa pin 9 as output alternate function push pull for timer 1 channel 2
	TIM1->CCER |=(1<<4);
	TIM1->CCMR1 |=(6<<12);
	TIM1->CCR2=0;
	}
	else if (channel == 3)
	{
	GPIOA->CRH &=(0xFFFF0000);
	GPIOA->CRH |=(10<<8);//set gpioa pin 10 as output alternate function push pull for timer 1 channel 3
	TIM1->CCER |=(1<<8);
	TIM1->CCMR2 |=(6<<4);
	TIM1->CCR3=0;
	}
	else if (channel == 4)
	{
	GPIOA->CRH &=(0xFFFF0000);
	GPIOA->CRH |=(10<<12);//set gpioa pin 11 as output alternate function push pull for timer 1 channel 4
	TIM1->CCER |=(1<<12);
	TIM1->CCMR2 |=(6<<12);
	TIM1->CCR4=0;
	}
	TIM1->PSC = 7;
	TIM1->ARR = 999;
	TIM1->BDTR |= TIM_BDTR_MOE;// Enable the main output
	TIM1->CR1|=(1<<0);
	while(!(TIM1->SR & (1<<0)));
}
void TIM1_PWM_duty(uint8_t channel, uint16_t duty)
{
	if (channel == 1)
	{
		TIM1->CCR1 = duty;
	}
	else if (channel == 2)
	{
		TIM1->CCR2 = duty;
	}
	else if (channel == 3)
	{
		TIM1->CCR3 = duty;
	}
	else if (channel == 4)
	{
		TIM1->CCR4 = duty;
	}
	
}
void TIM1_PWM_Config_Multi(uint8_t number)
{
	      RCC->APB2ENR |=(1<<2);//enable clock for GPIOA
        GPIOA->CRH &=(0xFFFF0000);
	for (uint8_t i=number;i>0;i--)
{
        GPIOA->CRH |=(10<<((number-i)*4));
        TIM1->CCER |= (1<<((number - i)*4));
}
if (number == 2)
{
        TIM1->CCMR1 |=((6<<4) | (6<<12));//set mode for channel 1 vs 2
        TIM1->CCR1=0;
        TIM1->CCR2=0;
}
else if (number == 3)
{
        TIM1->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM1->CCMR2 |=(6<<4);//set mode for channel 3
        TIM1->CCR1=0;
        TIM1->CCR2=0;
        TIM1->CCR3=0;
}
else if (number == 4)
{
        TIM1->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM1->CCMR2 |=((6<<4)|(6<<12));//set mode for channal 3 vs 4
        TIM1->CCR1=0;
        TIM1->CCR2=0;
        TIM1->CCR3=0;
        TIM1->CCR4=0;
}
	TIM1->PSC = 7;
	TIM1->ARR = 999;
	TIM1->BDTR |= TIM_BDTR_MOE;// Enable the main output
	TIM1->CR1|=(1<<0);
	while(!(TIM1->SR & (1<<0)));
	
}


void TIM2_PWM_Init()
{
	RCC->APB1ENR |=(1<<0);
}
void TIM2_PWM_Config(uint8_t channel)
{
	RCC->APB2ENR |=(1<<2);//enable clock for GPIOA
	if (channel == 1)
	{
	GPIOA->CRL &=(0xFFFF0000);
	GPIOA->CRL |=(10<<0); //set gpioa pin 0 as output alternate function push pull for timer 2 channel 1
	TIM2->CCER |=(1<<0);
	TIM2->CCMR1 |=(6<<4);
	TIM2->CCR1=0;
	}
	else if (channel == 2)
	{
	GPIOA->CRL &=(0xFFFF0000);
	GPIOA->CRL |=(10<<4);//set gpioa pin 1 as output alternate function push pull for timer 2 channel 2
	TIM2->CCER |=(1<<4);
	TIM2->CCMR1 |=(6<<12);
	TIM2->CCR2=0;
	}
	else if (channel == 3)
	{
	GPIOA->CRL &=(0xFFFFF0FF);
	GPIOA->CRL |=(10<<8);//set gpioa pin 2 as output alternate function push pull for timer 2 channel 3
	TIM2->CCER |=(1<<8);
	TIM2->CCMR2 |=(6<<4);
	TIM2->CCR3=0;
	}
	else if (channel == 4)
	{
	GPIOA->CRL &=(0xFFFF0FFF);
	GPIOA->CRL |=(10<<12);//set gpioa pin 3 as output alternate function push pull for timer 2 channel 4
	TIM2->CCER |=(1<<12);
	TIM2->CCMR2 |=(6<<12);
	TIM2->CCR4=0;
	}
	TIM2->PSC = 7;
	TIM2->ARR = 999;
	TIM2->CR1|=(1<<0);
	while(!(TIM2->SR & (1<<0)));
}
void TIM2_PWM_duty(uint8_t channel, uint16_t duty)
{
	if (channel == 1)
	{
		TIM2->CCR1 = duty;
	}
	else if (channel == 2)
	{
		TIM2->CCR2 = duty;
	}
	else if (channel == 3)
	{
		TIM2->CCR3 = duty;
	}
	else if (channel == 4)
	{
		TIM2->CCR4 = duty;
	}
	
}


void TIM3_PWM_Init()
{
	RCC->APB1ENR |=(1<<1);
}
void TIM3_PWM_Config(uint8_t channel)
{
	RCC->APB2ENR |=(1<<2);//enable clock for GPIOA
	RCC->APB2ENR |=(1<<3);//enable clock for GPIOB
	if (channel == 1)
	{
	GPIOA->CRL &=(0xF0FFFFFF);
	GPIOA->CRL |=(10<<24); //set gpioa pin 6 as output alternate function push pull for timer 3 channel 1
	TIM3->CCER |=(1<<0);
	TIM3->CCMR1 |=(6<<4);
	TIM3->CCR1=0;
	}
else if (channel == 2)
	{
	GPIOA->CRL &=(0x0FFFFFFF);
	GPIOA->CRL |=(10<<28); //set gpioa pin 7 as output alternate function push pull for timer 3 channel 2
	TIM3->CCER |=(1<<4);
	TIM3->CCMR1 |=(6<<12);
	TIM3->CCR2=0;
	}
	else if (channel == 3)
	{
	GPIOB->CRL &=(0xFFFFFFF0);
	GPIOB->CRL |=(10<<0); //set gpiob pin 0 as output alternate function push pull for timer 3 channel 3
	TIM3->CCER |=(1<<8);
	TIM3->CCMR2 |=(6<<4);
	TIM3->CCR3=0;
	}
	else if (channel == 4)
	{
	GPIOB->CRL &=(0xFFFFFF0F);
	GPIOB->CRL |=(10<<4); //set gpiob pin 1 as output alternate function push pull for timer 3 channel 4
	TIM3->CCER |=(1<<12);
	TIM3->CCMR2 |=(6<<12);
	TIM3->CCR4=0;
	}
	TIM3->PSC = 7;
	TIM3->ARR = 999;
	TIM3->CR1|=(1<<0);
	while(!(TIM3->SR & (1<<0)));
}
void TIM3_PWM_duty(uint8_t channel, uint16_t duty)
{
	if (channel == 1)
	{
		TIM3->CCR1 = duty;
	}
	else if (channel == 2)
	{
		TIM3->CCR2 = duty;
	}
	else if (channel == 3)
	{
		TIM3->CCR3 = duty;
	}
	else if (channel == 4)
	{
		TIM3->CCR4 = duty;
	}
	
}
void TIM3_PWM_Config_Multi(uint8_t number)
{
	
	      RCC->APB2ENR |=(1<<2);//enable clock for GPIOA
	      RCC->APB2ENR |=(1<<3);
        GPIOA->CRL &=(0x00FFFFFF);
	      GPIOB->CRL &=(0xFFFFFF00);
	for (uint8_t i=number;i>0;i--)
{
        TIM3->CCER |= (1<<((number - i)*4));
}
if (number == 2)
{
	      GPIOA->CRL |=((10<<24) | (10<<28));
        TIM3->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM3->CCR1=0;
        TIM3->CCR2=0;
}
else if (number == 3)
{
	      GPIOA->CRL |=((10<<24) | (10<<28));
	      GPIOB->CRL |=(10<<0);
        TIM3->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM3->CCMR2 |=(6<<4);//set mode for channal 3 
        TIM3->CCR1=0;
        TIM3->CCR2=0;
        TIM3->CCR3=0;
}
else if (number == 4)
{
	      GPIOA->CRL |=((10<<24) | (10<<28));
	      GPIOB->CRL |=((10<<0) | (10<<4));
        TIM3->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM3->CCMR2 |=((6<<4)|(6<<12));//set mode for channal 3 vs 4
        TIM3->CCR1=0;
        TIM3->CCR2=0;
        TIM3->CCR3=0;
        TIM3->CCR4=0;
}
	TIM3->PSC = 7;
	TIM3->ARR = 999;
	//TIM3->BDTR |= TIM_BDTR_MOE;// Enable the main output
	TIM3->CR1|=(1<<0);
	while(!(TIM3->SR & (1<<0)));
	
	
}

void TIM4_PWM_Init()
{
	RCC->APB1ENR |=(1<<2);
}
void TIM4_PWM_Config(uint8_t channel)
{
	RCC->APB2ENR |=(1<<3);//enable clock for GPIOB
	if (channel == 1)
	{
		GPIOB->CRL &=(0xF0FFFFFF);
		GPIOB->CRL |=(10<<24);
		TIM4->CCER |=(1<<0);
		TIM4->CCMR1 |=(6<<4);
		TIM4->CCR1=0;
	}
	else if (channel == 2)
	{
		GPIOB->CRL &=(0x0FFFFFFF);
		GPIOB->CRL |=(10<<28);
		TIM4->CCER |=(1<<4);
		TIM4->CCMR1 |=(6<<12);
		TIM4->CCR2=0;
	}
		else if (channel == 3)
	{
		GPIOB->CRH &=(0xFFFFFFF0);
		GPIOB->CRH |=(10<<0);
		TIM4->CCER |=(1<<8);
		TIM4->CCMR2 |=(6<<4);
		TIM4->CCR3=0;
	}
			else if (channel == 4)
	{
		GPIOB->CRH &=(0xFFFFFF0F);
		GPIOB->CRH |=(10<<4);
		TIM4->CCER |=(1<<12);
		TIM4->CCMR2 |=(6<<12);
		TIM4->CCR4=0;
	}
	TIM4->PSC = 7;
	TIM4->ARR = 999;
	TIM4->CR1|=(1<<0);
	while(!(TIM4->SR & (1<<0)));
}

void TIM4_PWM_Config_Multi(uint8_t number)
{
	      RCC->APB2ENR |=(1<<3);
	      GPIOB->CRL &=(0x00FFFFFF);
	      GPIOB->CRH &= (0xFFFFFF00);
	for (uint8_t i=number;i>0;i--)
{
        TIM4->CCER |= (1<<((number - i)*4));
}
if (number == 2)
{
	      GPIOB->CRL |=((10<<24) | (10<<28));
        TIM4->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM4->CCR1=0;
        TIM4->CCR2=0;
}
else if (number == 3)
{
	      GPIOB->CRL |=((10<<24) | (10<<28));
	      GPIOB->CRH |=(10<<0);
        TIM4->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM4->CCMR2 |=(6<<4);//set mode for channal 3 
        TIM4->CCR1=0;
        TIM4->CCR2=0;
        TIM4->CCR3=0;
}
else if (number == 4)
{
	      GPIOB->CRL |=((10<<24) | (10<<28));
	      GPIOB->CRH |=((10<<0) | (10<<4));
        TIM4->CCMR1 |=((6<<4) | (6<<12));//set mode 1 for channel 1 vs 2
        TIM4->CCMR2 |=((6<<4)|(6<<12));//set mode for channal 3 vs 4
        TIM4->CCR1=0;
        TIM4->CCR2=0;
        TIM4->CCR3=0;
        TIM4->CCR4=0;
}
	TIM4->PSC = 7;
	TIM4->ARR = 999;
	//TIM4->BDTR |= TIM_BDTR_MOE;// Enable the main output
	TIM4->CR1|=(1<<0);
	while(!(TIM4->SR & (1<<0)));
	
	
}

void TIM4_PWM_duty(uint8_t channel, uint16_t duty)
{
	if (channel == 1)
	{
		TIM4->CCR1 = duty;
	}
	else if (channel == 2)
	{
		TIM4->CCR2 = duty;
	}
	else if (channel == 3)
	{
		TIM4->CCR3 = duty;
	}
	else if (channel == 4)
	{
		TIM4->CCR4 = duty;
	}
	
}
