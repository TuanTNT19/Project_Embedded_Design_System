

#include "stm32f1xx.h"
#include "Timer.h"
#define DISABLE_IRQ()             do{__asm volatile("MOV R0, #0x1"); __asm volatile("MSR PRIMASK,R0");} while(0)
#define ENABLE_IRQ()              do{__asm volatile("MOV R0, #0x0"); __asm volatile("MSR PRIMASK,R0");} while(0)
typedef struct{
	uint8_t pin;
	float temperature;
	float humility;
}DHT;

void DHT_Init(DHT* dht, GPIO_TypeDef*GPIOx, uint8_t Pin);
void DHT22_readData(DHT* dht);


