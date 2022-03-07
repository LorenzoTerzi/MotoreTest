//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Led.h"
#include "Arduino.h"
#include "Puls.h"
#include "LCD.h"
#include "Ultrasuoni.h"

extern EventGroupHandle_t xRullo;

void UltrasuoniInit(void){
	//TriggerInit
	//configuro PB6 in alternate function
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= ~GPIO_MODER_MODE6_Msk;
	GPIOB->MODER |= GPIO_MODER_MODE6_1;
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFSEL6_Msk ;
	GPIOB->AFR[0] |= GPIO_AFRL_AFSEL6_1;

	//EchoInit
	//configuro PA5 in alternate function
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODE5_Msk;
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL5_Msk;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;
	
	TIM2_CH1_InCapt_SM();					//impulso del trigger per avviare misurazione, timer PB6
	TIM4_CH1_PWM();								//misurazione dell'impulso con l'echo, timer PA5
}

void TIM2_IRQHandler(void){ 
	char c[6];
	float durata;
	durata=TIM2->CCR1+1;											//misurazione in us
	durata=durata/58;													//converto in cm
	if(durata<5)																					//se la distanza e' minore di 5 cm
		xEventGroupSetBits(xRullo,EVENT_RILEVA_OGGETTO);		//setto bit dell'event group
}

	
void UltrasuoniTestInit(void){
	xTaskCreate(UltrasuoniTestLedTask,     /* Pointer to the function that implements the task.   */
	"vTaskLed",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void UltrasuoniTestLedTask(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_RILEVA_OGGETTO;				
	while(1){
		xEventGroupWaitBits(xRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY); 	//aspetto bit event group
		LedRossoToggle();
		vTaskDelay(100);									//lampeggio del led rosso
		LedRossoToggle();									//ad intervalli di 100 ms
		vTaskDelay(100);
	}
}
