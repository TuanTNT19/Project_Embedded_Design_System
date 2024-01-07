#include "ADC.h"
#include "stm32f1xx.h"

uint8_t id1 = 0;
uint8_t id2 = 0;
void ADC1_Init()
{
		RCC->APB2ENR|=(1<<9);//enable clock fof ADC1
}
void ADC1_Config_Channel(uint8_t channel)
{
	if (channel <= 7)
	{
		RCC->APB2ENR|=(1<<2);//enable clock for GPIOA
		GPIOA->CRL &=(0x00000000);
		GPIOA->CRL |=(0<<(4*channel));
	}
	else if (channel ==8)
	{
		RCC->APB2ENR|=(1<<3);//enable clock for GPIOB
		GPIOB->CRL &=(0x00000000);
		GPIOB->CRL |=(0<<0);
	}
	else if (channel == 9)
	{
		RCC->APB2ENR|=(1<<3);//enable clock for GPIOB
		GPIOA->CRL &=(0x00000000);
		GPIOA->CRL |=(0<<4);
	}
	  ADC1->CR2 |=(1<<0); //enable A/D converter
		ADC1->CR2 |=(1<<1);//Turn on continuous mode 
		ADC1->SMPR2 |=(7<<(3*channel));//sample time =  239.5 cycles
		ADC1->SQR1 &=(0<<20); //only one channel
		ADC1->SQR3 |=(channel<<0);
	  ADC1->CR2 |= (1 << 2); // turn calibrate on 
	  while(!(ADC1->CR2 & (1 << 2)));//check calibrate
		ADC1->CR2 |=(1<<0);//enable ADC1
		ADC1->CR2 |=(1<<22);//Perform an initial conversion (discarded)
	
}

uint16_t ADC1_Read()
	{
		//ADC1->CR2 |= ADC_CR2_SWSTART;
		while(!(ADC1->SR &(1<<1)));
		uint16_t value=ADC1->DR;
		return value;
		
	}

void ADC1_Config_Multi(uint8_t number, uint8_t channels[])
{
	RCC->APB2ENR |= 1<<9;  // enable ADC1 clock
	RCC->APB2ENR |= (1<<2);  // enable GPIOA clock
	RCC->APB2ENR |=(1<<3);
	GPIOA->CRL &=(0x00000000);
  GPIOB->CRL &=(0xFFFFFF00);
	ADC1->CR1 |=(1<<8);//enable scan mode
	ADC1->CR2|=(1<<1);//enable continous mode
	ADC1->CR2|=(1<<8);//enble DMA
	ADC1->CR2 &=~(1<<11); //right alignment
	ADC1->CR2 |=(7<<17);//SWSTART in EXTSEL bit
	ADC1->CR2|=(1<<20);//Conversion on external event enabled
	//ADC1->SMPR2 |=((7<<3) | (7<<12));  // Sampling time of 1.5 cycles for channel 1 and channel 4
	for (uint8_t i=0;i<number;i++)
	{
		ADC1->SMPR2 |=((7<<(3*channels[i])));
	}
	ADC1->SQR1|=((number-1)<<20);
	for (uint8_t j=0;j<number;j++)
	{
		if (j<6)
		{
		  ADC1->SQR3 |=(channels[j]<<id1);
		  id1+=5;
		}
		else if(j>=6){
			ADC1->SQR2 |=(channels[j]<<id2);
			id2+=5;
		}
	}
	ADC1->CR2 |= (1 << 2); // turn calibrate on 
	while(!(ADC1->CR2 & (1 << 2)));//check calibrate
	ADC1->CR2|=(1<<0);//enable ADC1
	ADC1->CR2 |=(1<<22);//enable conversion
}
void DMA_Init()
{
	RCC->AHBENR |= 1<<0;//enable clock for DMA1
	DMA1_Channel1->CCR &=~ (1<<4);//read from peripheral
	DMA1_Channel1->CCR |=(1<<5);//enable circular mode
	DMA1_Channel1->CCR |=(1<<7);//enable memory increment
	DMA1_Channel1->CCR|=(1<<8);//peripheral size : 16 bit
	DMA1_Channel1->CCR|=(1<<10);//memory size : 16 bit
	
}
void ADC1_Read_DMA(uint32_t srcAdd, uint32_t destAdd, uint16_t size)
{
	DMA1_Channel1->CNDTR = size;
	DMA1_Channel1->CPAR = srcAdd;
	DMA1_Channel1->CMAR=destAdd;
	DMA1_Channel1->CCR |=(1<<0);//enable channel DMA
}
void ADC2_Init()
{
		RCC->APB2ENR|=(1<<10);//enable clock fof ADC2
}
void ADC2_Config_Channel(uint8_t channel)
{
	if (channel <= 7)
	{
		RCC->APB2ENR|=(1<<2);//enable clock for GPIOA
		GPIOA->CRL &=(0x00000000);
		GPIOA->CRL |=(0<<(4*channel));
	}
	else if (channel ==8)
	{
		RCC->APB2ENR|=(1<<3);//enable clock for GPIOB
		GPIOB->CRL &=(0x00000000);
		GPIOB->CRL |=(0<<0);
	}
	else if (channel == 9)
	{
		RCC->APB2ENR|=(1<<3);//enable clock for GPIOB
		GPIOA->CRL &=(0x00000000);
		GPIOA->CRL |=(0<<4);
	}
	  ADC2->CR2 |=(1<<0); //enable A/D converter
		ADC2->CR2 |=(1<<1);//Turn on continuous mode 
		ADC2->SMPR2 |=(7<<(3*channel));//sample time =  239.5 cycles
		ADC2->SQR1 &=(0<<20); //only one channel
		ADC2->SQR3 |=(channel<<0);
	  ADC2->CR2 |= (1 << 2); // turn calibrate on 
	  while(!(ADC2->CR2 & (1 << 2)));//check calibrate
		ADC2->CR2 |=(1<<0);//enable ADC1
		ADC2->CR2 |=(1<<22);//Perform an initial conversion (discarded)
	
}

uint16_t ADC2_Read()
	{
		//ADC1->CR2 |= ADC_CR2_SWSTART;
		while(!(ADC2->SR &(1<<1)));
		uint16_t value=ADC2->DR;
		return value;
		
	}
	