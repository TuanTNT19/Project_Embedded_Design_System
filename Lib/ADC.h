#ifndef ADC_H
#define ADC_H
#include <stdint.h>
void ADC1_Init();
void ADC1_Config_Channel(uint8_t channel);
uint16_t ADC1_Read();
void ADC1_Config_Multi(uint8_t number, uint8_t channels[]);
void DMA_Init();
void ADC1_Read_DMA(uint32_t srcAdd, uint32_t destAdd, uint16_t size);
void ADC2_Init();
void ADC2_Config_Channel(uint8_t channel);
uint16_t ADC2_Read();
	
#endif