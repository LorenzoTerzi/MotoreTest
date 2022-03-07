//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"                     	// ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Servo.h"
#include "Led.h"
#include "Arduino.h"
#include "Motore.h"
#include "Puls.h"

extern EventGroupHandle_t xRullo;

void MotoreInit(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE1_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE1_1;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL1_Msk;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL1_1;
	
	xTaskCreate(MotoreStartTask, /* Pointer to the function that implements the task.              */
	"Task start motore",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
		xTaskCreate(MotoreStopTask, /* Pointer to the function that implements the task.              */
	"Task stop motore",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void MotoreStartTask(void * pvParameters){
	while(1){
		if(SwUpClick())
			TIM5_CH2_PWM(250,1000);
	}	
}

void MotoreStopTask(void * pvParameters){
	while(1){
		if(SwRightClick())
			TIM5_CH2_PWM(1,1000);
	}	
}











