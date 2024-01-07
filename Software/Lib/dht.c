#include "dht.h"
#include "cmsis_os.h"
void DHT_Init(DHT* dht, GPIO_TypeDef*GPIOx, uint8_t Pin){
  if(Pin > 7){
		GPIOx->CRH &= ~(15<<(Pin * 4 - 32));
		GPIOx->CRH |= 7 << (Pin * 4 - 32);
	}else{
		GPIOx->CRL &= ~(15<<(Pin * 4));
		GPIOx->CRL |= 7 << (Pin * 4);
	}
  dht->pin = Pin;
}

void DHT22_Start(DHT* dht){
	GPIOA->BSRR |= (1 << (dht->pin + 16));
	osDelay(20);
	DISABLE_IRQ();
	GPIOA->BSRR |= (1 << dht->pin);
	TIM1->CNT = 0;
	while(TIM1->CNT < 55){
		if(!(GPIOA->IDR & (1<<dht->pin)))
			break;
	}
	ENABLE_IRQ();
}

uint8_t DHT22_checkResponse(DHT* dht){
	uint8_t res = 0;
	TIM1->CNT = 0;
	while(TIM1->CNT < 90){
		if((GPIOA->IDR & (1<<dht->pin)) && (TIM1->CNT > 70)){
			res++;
			break;
		}
	}

	TIM1->CNT = 0;
	while(TIM1->CNT <95){
		if(!(GPIOA->IDR & (1<<dht->pin)) && (TIM1->CNT > 70)){
			res++;
			break;
		}
	}
	return res;
}

void DHT22_readData(DHT* dht){
	uint8_t data[5];
	DHT22_Start(dht);
	DISABLE_IRQ();
	uint8_t check = DHT22_checkResponse(dht);
	if(check == 2){
		for(int i = 0; i < 4; i++){
			for(int j = 7; j >= 0; j--){
				TIM1->CNT = 0;
		while(TIM1->CNT < 60){
		  if((GPIOA->IDR & (1<<dht->pin)) && (TIM1->CNT > 40)){
			break;
		  }
		}
		TIM1->CNT = 0;
		while(TIM1->CNT < 80){
		  if(!(GPIOA->IDR & (1<<dht->pin))){
			break;
		  }
		}
		if(TIM1->CNT > 50){
		  data[i] |= (1<<j);
		}
		else
		  data[i] &= ~(1<<j);
			}
		}
	}
	dht->temperature = ((uint16_t)(data[2]&0x7F)*256 + (uint16_t)data[3])/10.0;
	dht->humility = ((uint16_t)data[0]*256 + (uint16_t)data[1])/10.0;
	ENABLE_IRQ();
}
