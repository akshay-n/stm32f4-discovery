//stm32f4
#include "stm32f4_discovery.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

//freeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

#define MAXPOW 300
#define PWMDELAY 3

void timerTask1(void*);
void timerTask2(void*);
void timerTask3(void*);
void timerTask4(void*);

void initGPIO(void);
void initTimer(void);
void initPWM(void);

SemaphoreHandle_t xSemaphore;

int main(void){
      
    initGPIO();
    initTimer();
    initPWM();
      
    xSemaphore = xSemaphoreCreateBinary();
    if(!xSemaphore){
        //Insufficient FreeRTOS heap available, hang
        while(1);
    }
    xSemaphoreGive(xSemaphore);
    // Create tasks
    xTaskCreate(
        timerTask1,                       // Function pointer
        "Task_Green_led",                          // Task name
        configMINIMAL_STACK_SIZE,         // Stack depth in words
        (void*) NULL,                     // Pointer to tasks arguments
        tskIDLE_PRIORITY + 2UL,           // Task priority
        NULL                              // Task handle
    );
    
    xTaskCreate(
        timerTask2,                       // Function pointer
        "Task_Orange_led",                          // Task name
        configMINIMAL_STACK_SIZE,         // Stack depth in words
        (void*) NULL,                     // Pointer to tasks arguments
        tskIDLE_PRIORITY + 2UL,           // Task priority
        NULL                              // Task handle
    );
    
    xTaskCreate(
        timerTask3,                       // Function pointer
        "Task_Red_led",                          // Task name
        configMINIMAL_STACK_SIZE,         // Stack depth in words
        (void*) NULL,                     // Pointer to tasks arguments
        tskIDLE_PRIORITY + 2UL,           // Task priority
        NULL                              // Task handle
    );
    
    xTaskCreate(
        timerTask4,                       // Function pointer
        "Task_Blue_led",                          // Task name
        configMINIMAL_STACK_SIZE,         // Stack depth in words
        (void*) NULL,                     // Pointer to tasks arguments
        tskIDLE_PRIORITY + 2UL,           // Task priority
        NULL                              // Task handle
    );
    
    // Start the RTOS Scheduler
    vTaskStartScheduler();
      
    while(1);
}

//Task for timer
void timerTask1(void *pvParameters){  

uint16_t power = 0;
while(1){  //Loop forever
    if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE){
        while(power < MAXPOW){
            TIM4->CCR1 = power++;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
	    xSemaphoreGive(xSemaphore);
	    taskYIELD();  
        while(power > 0){
            TIM4->CCR1 = power--;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
        vTaskDelay(1000/portTICK_PERIOD_MS);
        }
    //xSemaphoreGive(xSemaphore);
    //taskYIELD();
    }
}

void timerTask2(void *pvParameters){  

uint16_t power = 0;
while(1){  //Loop forever
    if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE){
        while(power < MAXPOW){
            TIM4->CCR2 = power++;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
	    xSemaphoreGive(xSemaphore);
	    taskYIELD();  
        while(power > 0){
            TIM4->CCR2 = power--;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
        vTaskDelay(1000/portTICK_PERIOD_MS);
        }
    //xSemaphoreGive(xSemaphore);
    //taskYIELD();
    }
}

void timerTask3(void *pvParameters){  

uint16_t power = 0;
while(1){  //Loop forever
    if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE){
        while(power < MAXPOW){
            TIM4->CCR3 = power++;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
	    xSemaphoreGive(xSemaphore);
	    taskYIELD();  
        while(power > 0){
            TIM4->CCR3 = power--;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
        vTaskDelay(1000/portTICK_PERIOD_MS);
        }
    //xSemaphoreGive(xSemaphore);
    //taskYIELD();
    }
}

void timerTask4(void *pvParameters){  

uint16_t power = 0;
while(1){  //Loop forever
    if(xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE){
        while(power < MAXPOW){
            TIM4->CCR4 = power++;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
	    xSemaphoreGive(xSemaphore);
	    taskYIELD();  
        while(power > 0){
            TIM4->CCR4 = power--;
	        vTaskDelay(PWMDELAY/portTICK_PERIOD_MS);
	      }
        vTaskDelay(1000/portTICK_PERIOD_MS);
        }
    //xSemaphoreGive(xSemaphore);
    //taskYIELD();
    }
}

void initGPIO(){

    GPIO_InitTypeDef GPIO_InitStructure;
    // Enable clock for GPIOD
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

void initTimer(void){
    TIM_TimeBaseInitTypeDef  TIM_BaseStruct;

    // Enable clock for TIM4
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_BaseStruct.TIM_Prescaler = 0;
    TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_BaseStruct.TIM_Period = 665;
    TIM_BaseStruct.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM4, &TIM_BaseStruct);
    TIM_ARRPreloadConfig(TIM4, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
}

void initPWM(void){
    TIM_OCInitTypeDef TIM_OCStruct;

    TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCStruct.TIM_Pulse = 0;

    //PWM channel 1
    TIM_OC1Init(TIM4, &TIM_OCStruct);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

    //PWM channel 2
    TIM_OC2Init(TIM4, &TIM_OCStruct);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

    //PWM channel 3
    TIM_OC3Init(TIM4, &TIM_OCStruct);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

    //PWM channel 4
    TIM_OC4Init(TIM4, &TIM_OCStruct);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
}
