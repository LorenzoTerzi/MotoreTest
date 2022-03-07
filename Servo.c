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

extern EventGroupHandle_t xRullo;

void ServoMotoreInit(void){
	/*Inizializzazione pin servo(PE11) in alternate function 
	per generare un segnale PWM che piloterà il servomotore*/
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	GPIOE->MODER &= ~GPIO_MODER_MODE11_Msk;
	GPIOE->MODER |= GPIO_MODER_MODE11_1;
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL11_Msk;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL11_0;

	//Inizializzazione timer del pin PE11
	TIM1_CH2_PWM(1551);
	
	xTaskCreate(ServoSmistaDxTask, /* Pointer to the function that implements the task.              */
	"Task 4 (Smista destra)",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
	xTaskCreate(ServoSmistaSxTask, /* Pointer to the function that implements the task.              */
	"Task 5 (Smista sinistra)",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void ServoSmistaDxTask(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_SMISTADX;
	while(1){
		xEventGroupWaitBits(xRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);
		TIM1->CCR2 = 2000;	//Sposta a 0°
		vTaskDelay(380);
		TIM1->CCR2 = 1200;	//Sposta a 150°
		vTaskDelay(380);
		TIM1->CCR2 = 1600;	//Sposta a 0°
	}
}

void ServoSmistaSxTask(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_SMISTASX;
	while(1){
		xEventGroupWaitBits(xRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);
		TIM1->CCR2=1200;	//Sposta a 0°
		vTaskDelay(400);
		TIM1->CCR2 = 2000;	//Sposta a 150°
		vTaskDelay(400);
		TIM1->CCR2 = 1600;	//Sposta a 0°
	}
}


void ServoMotoreTestInit(void){
	xTaskCreate(ServoTestPA0Task, /* Pointer to the function that implements the task.              */
	"Task 10 (PA0 check)",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
	xTaskCreate(ServoTestPA1Task, /* Pointer to the function that implements the task.              */
	"Task 11 (PA1 check)",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void ServoTestPA0Task(void * pvParameters){
	while(1){
		//Lettura pulsante sinistro 
		while(!digitalRead(PA0));
		while(digitalRead(PA0)){;}
			//Modifica event group per richiamare task smista
			xEventGroupSetBits(xRullo, EVENT_SMISTASX);
	}	
}

void ServoTestPA1Task(void * pvParameters){
	while(1){
		//Lettura pulsante sinistro 
		while(!digitalRead(PA1));
		while(digitalRead(PA1)){;}
			xEventGroupSetBits(xRullo, EVENT_SMISTADX);
	}
}