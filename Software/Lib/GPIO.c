#include "GPIO.h"
#include "stm32f1xx.h"

void GPIOA_Init()
{
	RCC->APB2ENR |= (1<<2);
}
void GPIOB_Init()
{
	RCC->APB2ENR |= (1<<3);
}
void GPIOC_Init()
{
	RCC->APB2ENR |= (1<<4);
}

void GPIOA_Config_Pin(uint8_t Pinnum,char str)
{
 if (str =='O')
 {
	 if (Pinnum<=7)
	 {
		 GPIOA->CRL &=(0x00000000);
		 GPIOA->CRL |=(2<<(4*Pinnum));
	}
	 else if (Pinnum>7)
	 {
		 GPIOA->CRH &=(0x00000000);
		 GPIOA->CRH |=(2<<(4*(Pinnum-8)));
	 }
	}
 else if (str=='I')
 {
	 if (Pinnum <=7)
	 {
		GPIOA->CRL &=(0x00000000);
		GPIOA->CRL |=(0<<(4*Pinnum));
		}
	 else if (Pinnum >7)
	 {
		 GPIOA->CRH &=(0x00000000);
		 GPIOA->CRH |=(0<<(4*(Pinnum - 8)));
		}
	 }
}
void GPIOA_Pin_On(uint8_t Pinnum)
{
	GPIOA->ODR |=(1<<Pinnum);
}
void GPIOA_Pin_Off(uint8_t Pinnum)
{
	GPIOA->ODR &=(0<<Pinnum);
}





void GPIOB_Config_Pin(uint8_t Pinnum,char str)
{
 if (str =='O')
 {
	 if (Pinnum<=7)
	 {
		 GPIOB->CRL &=(0x00000000);
		 GPIOB->CRL |=(2<<(4*Pinnum));
	}
	 else if (Pinnum>7)
	 {
		 GPIOB->CRH &=(0x00000000);
		 GPIOB->CRH |=(2<<(4*(Pinnum-8)));
	 }
	}
 else if (str=='I')
 {
	 if (Pinnum <=7)
	 {
		GPIOB->CRL &=(0x00000000);
		GPIOB->CRL |=(0<<(4*Pinnum));
		}
	 else if (Pinnum >7)
	 {
		 GPIOB->CRH &=(0x00000000);
		 GPIOB->CRH |=(0<<(4*(Pinnum - 8)));
		}
	 }
}
void GPIOB_Pin_On(uint8_t Pinnum)
{
	GPIOB->ODR |=(1<<Pinnum);
}
void GPIOB_Pin_Off(uint8_t Pinnum)
{
	GPIOB->ODR &=(0<<Pinnum);
}




void GPIOC_Config_Pin(uint8_t Pinnum,char str)
{
 if (str =='O')
 {
	 if (Pinnum<=7)
	 {
		 GPIOC->CRL &=(0x00000000);
		 GPIOC->CRL |=(2<<(4*Pinnum));
	}
	 else if (Pinnum>7)
	 {
		 GPIOC->CRH &=(0x00000000);
		 GPIOC->CRH |=(2<<(4*(Pinnum-8)));
	 }
	}
 else if (str=='I')
 {
	 if (Pinnum <=7)
	 {
		GPIOC->CRL &=(0x00000000);
		GPIOC->CRL |=(0<<(4*Pinnum));
		}
	 else if (Pinnum >7)
	 {
		 GPIOC->CRH &=(0x00000000);
		 GPIOC->CRH |=(0<<(4*(Pinnum - 8)));
		}
	 }
}
void GPIOC_Pin_On(uint8_t Pinnum)
{
	GPIOC->ODR |=(1<<Pinnum);
}
void GPIOC_Pin_Off(uint8_t Pinnum)
{
	GPIOC->ODR &=(0<<Pinnum);
}

