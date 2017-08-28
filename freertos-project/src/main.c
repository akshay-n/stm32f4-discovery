//stm32f4
#include "stm32f4_discovery.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

//freeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

void ledToggle(void*);
void initGPIO();

int main(void){
  
  initGPIO();
    
  // Create task
  xTaskCreate(
		  ledToggle,                        // Function pointer
		  "Task1",                          // Task name
		  configMINIMAL_STACK_SIZE,         // Stack depth in words
		  (void*) NULL,                     // Pointer to tasks arguments
		  tskIDLE_PRIORITY + 2UL,           // Task priority
		  NULL                              // Task handle
  );
  
  
  // Start the RTOS Scheduler
  vTaskStartScheduler();
  
  while(1);
  
}

//Task to toggle LEDs
void ledToggle(void *pvParameters){
  
  while (1) {
    GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
    //1s delay
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_14);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
    vTaskDelay(1000 / portTICK_RATE_MS);
    GPIO_ToggleBits(GPIOD, GPIO_Pin_15);
    
  }
}

void initGPIO(){
  GPIO_InitTypeDef GPIO_InitStructure;    
  // Init LED
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}
