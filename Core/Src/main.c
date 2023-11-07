#include "stdio.h"
#include "main.h"
#include "cmsis_os.h"
#include "PWM.h"
#include "Timer.h"
#include "ADC.h"
TaskHandle_t defaultTaskHandle;
TaskHandle_t AboveNormalHandle;
void StartDefaultTask(void  *argument);
void AboveNormalTask (void *parameter);
int i=0;
int j=0;
uint8_t channel[1]={3};
uint16_t value;
int main(void)
{
 
  xTaskCreate(StartDefaultTask, "Task00", 128, NULL, osPriorityAboveNormal, &defaultTaskHandle);
  xTaskCreate(AboveNormalTask, "Task01", 128, NULL, osPriorityAboveNormal+3, &AboveNormalHandle);

  osKernelStart();


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void AboveNormalTask (void *parameter){
	
	ADC1_Init();
	DMA_Init();
	ADC1_Config_Multi(1,channel);
	ADC1_Read_DMA((uint32_t)&ADC1->DR, (uint32_t)value, 1);
	while(1)
	{
		
   vTaskDelay(200);
		
	}
}

void StartDefaultTask(void  *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
   
while(1)
{
	
	
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