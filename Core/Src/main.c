#include "stdio.h"
#include "main.h"
#include "cmsis_os.h"
#include "PWM.h"
#include "Timer.h"
#include "ADC.h"
TaskHandle_t defaultTaskHandle;
TaskHandle_t AboveNormalHandle;
TaskHandle_t HighHandle;
QueueHandle_t QueuexHandle;
QueueHandle_t QueueyHandle;
void StartDefaultTask(void  *argument);
void AboveNormalTask (void *parameter);
void HighTask(void *para2);
int i=0;
int j=0;
uint8_t channel[2]={3,4};
uint16_t adc_value[2];
uint16_t data_receive[2];
int main(void)
{
 
  xTaskCreate(StartDefaultTask, "Task00", 128, NULL, osPriorityAboveNormal, &defaultTaskHandle);
  xTaskCreate(AboveNormalTask, "Task01", 128, NULL, osPriorityAboveNormal+1, &AboveNormalHandle);
	xTaskCreate(HighTask, "Task01", 128, NULL, osPriorityAboveNormal+2, &HighHandle);
	QueuexHandle = xQueueCreate(1,2);
	QueueyHandle = xQueueCreate(1,2);
  ADC1_Config_Multi(2,channel);
	DMA_Init();
	TIM2_PWM_Init();
	TIM2_PWM_Config(1);
	TIM2_PWM_Config(2);
  osKernelStart();


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

void HighTask(void *para2)
{

  ADC1_Read_DMA((uint32_t)&ADC1->DR, (uint32_t)adc_value, 2);
	while(1)
	{
		xQueueSend(QueuexHandle,&adc_value[0],NULL);
		xQueueSend(QueueyHandle,&adc_value[1],NULL);
    vTaskDelay(50);
	}
}
void AboveNormalTask (void *parameter){
	

	while(1)
	{
		
   		 xQueueReceive(QueuexHandle,&data_receive[0],osWaitForever);
		   uint8_t duty = data_receive[0]*999/4095;
       TIM2_PWM_duty(2, duty);
		
	}
}

void StartDefaultTask(void  *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
   
while(1)
{
			 xQueueReceive(QueueyHandle,&data_receive[1],osWaitForever);
		   uint8_t duty = data_receive[1]*999/4095;
       TIM2_PWM_duty(1, duty);
	
}
  /* USER CODE END 5 */
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}