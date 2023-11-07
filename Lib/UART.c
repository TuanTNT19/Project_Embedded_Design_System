#include "UART.h"
#include "stm32f1xx.h"

uint16_t Cal_BRR(uint32_t baudrate)
{
    double b = (double)8000000/(16*baudrate);
    uint32_t man = (uint32_t )b;
    uint32_t frac = (b - (double)man)*16;
    uint16_t r = (frac<<0) | (man <<4);
    return r;
}
void USART2_Init()
{
	RCC->APB1ENR |= (1<<17);//enable clock for USART2
}
void USART2_Config(uint32_t baudr)
{
	RCC->APB2ENR |= (1<<2);//enable clock for gpioa
	// config gpioa pin 2 as alternative function TX
	GPIOA->CRL &= (0xFFFFF0FF);
	GPIOA-> CRL |= (10<<8);
		// config gpioa pin 3 as alternative function RX
	GPIOA->CRL &= (0xFFFF0FFF);
	GPIOA->CRL |= (8<<12);//in push pull up/down
	GPIOA->ODR |= (1<<3);// pull up
	USART2->BRR = Cal_BRR(baudr);
	USART2->CR1 |= (1<<13);
	USART2->CR1 |= (1<<2); // RE=1.. Enable the Receiver
  USART2->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
}

void USART2_Send_char(char str)
{
	while (!(USART2->SR & (1<<7)));
	USART2->DR=str;
}
void USART2_Send_String(char *ch)
{
	while (*ch)
	{
		 USART2_Send_char(*ch++);
	}
}

uint8_t USART2_Getchar(void)
{
	
	uint8_t Temp;
	while (!(USART2->SR & USART_SR_RXNE));
	Temp = USART2->DR;
	return Temp;
}


void USART3_Init()
{
	RCC->APB1ENR |= (1<<18);//enable clock for USART3
}
void USART3_Config(uint32_t baudr)
{
	RCC->APB2ENR |= (1<<3);//enable clock for gpiob
	// config gpiob pin 10 as alternative function TX
	GPIOB->CRH &= (0xFFFFF0FF);
	GPIOB-> CRH |= (10<<8);
		// config gpiob pin 11 as alternative function RX
	GPIOB->CRL &= (0xFFFF0FFF);
	GPIOB->CRL |= (8<<12);//in push pull up/down
	GPIOB->ODR |= (1<<11);// pull up
	USART3->BRR = Cal_BRR(baudr);
	USART3->CR1 |= (1<<13);
	USART3->CR1 |= (1<<2); // RE=1.. Enable the Receiver
  USART3->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
}

void USART3_Send_char(char str)
{
	while (!(USART3->SR & (1<<7)));
	USART3->DR=str;
}
void USART3_Send_String(char *ch)
{
	while (*ch)
	{
		 USART3_Send_char(*ch++);
	}
}

uint8_t USART3_Getchar(void)
{
	
	uint8_t Temp;
	while (!(USART3->SR & USART_SR_RXNE));
	Temp = USART3->DR;
	return Temp;
}


void USART1_Init()
{
	RCC->APB2ENR |= (1<<14);//enable clock for USART1
}
void USART1_Config(uint32_t baudr)
{
	RCC->APB2ENR |= (1<<2);//enable clock for gpioa
	// config gpioa pin 9 as alternative function TX
	GPIOA->CRH &= (0xFFFFFF0F);
	GPIOA-> CRH |= (10<<4);
		// config gpioa pin 10 as alternative function RX
	GPIOA->CRL &= (0xFFFFF0FF);
	GPIOA->CRL |= (8<<8);//in push pull up/down
	GPIOA->ODR |= (1<<10);// pull up
	USART1->BRR = Cal_BRR(baudr);
	USART1->CR1 |= (1<<13);
	USART1->CR1 |= (1<<2); // RE=1.. Enable the Receiver
  USART1->CR1 |= (1<<3);  // TE=1.. Enable Transmitter
}

void USART1_Send_char(char str)
{
	while (!(USART1->SR & (1<<7)));
	USART1->DR=str;
}
void USART1_Send_String(char *ch)
{
	while (*ch)
	{
		 USART1_Send_char(*ch++);
	}
}

uint8_t USART1_Getchar(void)
{
	
	uint8_t Temp;
	while (!(USART1->SR & USART_SR_RXNE));
	Temp = USART1->DR;
	return Temp;
}
