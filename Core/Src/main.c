

#include "stdio.h"
#include "main.h"
#include "cmsis_os.h"
#include "PWM.h"
#include "Timer.h"
#include "LiquidCrystal_I2C.h"
#include "ADC.h"
#include "UART.h"
#include "GPIO.h"

I2C_HandleTypeDef hi2c1;
//TaskHandle_t ReadDHT22Handle;
TaskHandle_t defaultTaskHandle;
TaskHandle_t AboveNormalHandle;
TaskHandle_t HighHandle;
//TaskHandle_t SendUartHandle;
QueueHandle_t QueuexHandle;
QueueHandle_t QueueyHandle;
//QueueHandle_t QueuetHandle;
static void MX_I2C1_Init(void);
//void ReadDHT22(void *para);
void StartDefaultTask(void  *argument);
void AboveNormalTask (void *parameter);
void HighTask(void *para2);
//void SendUartTask(void *para3);
int i=0;
int j=0;
uint8_t sta=0;
LiquidCrystal_I2C hlcd;
uint8_t channel[2]={3,4};
uint16_t adc_value[2];
uint16_t data_receive[2];
uint8_t temp=0;
uint8_t humi =0;
uint8_t data_trans[2]={0};
char str[10];
int main(void)
{
  lcd_init(&hlcd, &hi2c1, LCD_ADDR_DEFAULT);
//  xTaskCreate(ReadDHT22,"Task 0",128,NULL,4,&ReadDHT22Handle);
  xTaskCreate(StartDefaultTask, "Task00", 128, NULL, 1, &defaultTaskHandle);
  xTaskCreate(AboveNormalTask, "Task01", 128, NULL, 2, &AboveNormalHandle);
	xTaskCreate(HighTask, "Task01", 128, NULL, 3, &HighHandle);
//  xTaskCreate(SendUartTask,"Task1",128,NULL,0,&SendUartHandle);
	QueuexHandle = xQueueCreate(1,2);
	QueueyHandle = xQueueCreate(1,2);
//  QueuetHandle = xQueueCreate(2,1);
  ADC1_Config_Multi(2,channel);
	DMA_Init();
	TIM2_PWM_Init();
	TIM2_PWM_Config(3);
	TIM2_PWM_Config(2);
	USART1_Init();
	USART1_Config(9600);
	RCC->APB2ENR |= (1<<2);
	GPIOA->CRH &=(0xFFF0FFFF);
	GPIOA->CRH |=(8<<16);
	GPIOA->ODR |=(1<<12);
  osKernelStart();


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
//void ReadDHT22(void *para)
//{
//  
//   lcd_set_cursor(&hlcd, 0,0);
//	 lcd_printf(&hlcd, "Temp: %2d  Lumi: %2d",temp,humi);
//   xQueueSend(QueuetHandle,&temp,NULL);
//   xQueueSend(QueuetHandle,&humi,NULL);

//}
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
		   uint16_t duty = data_receive[0]*999/4095;
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
		   uint16_t duty = data_receive[1]*999/4095;
       TIM2_PWM_duty(3, duty);
	
}
  /* USER CODE END 5 */
}
//void SendUartTask(void *para3){
//  while (1)
//  {
//     
//      xQueueReceive(QueuetHandle,&data_trans[0],osWaitForever);// get Temper from Queuet
//      xQueueReceive(QueuetHandle,&data_trans[1],osWaitForever);//get Humi from Queuet
//		  if (!(GPIOA->IDR &(1<<12)))
//{
//  while (!(GPIOA->IDR &(1<<12)));
//   if (sta ==0)
//	 {
//		 sta=1;
//	 }
//	 else if (sta ==1)
//	 {
//		
//		 sta =0;
//	 }
//   
//}
//      
//      if (sta == 1)
//{
//       		 int len=sprintf(str,"%3d %3d\n",data_trans[0],data_trans[1]);
//		 USART1_Send_String((char *)str);
//              vTaskDelay(500);
//}
//else {
//        USART1_Send_String(NULL);
//        vTaskDelay(500);
//}
//      
//  
//}
//}


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