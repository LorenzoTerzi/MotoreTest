//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Arduino.h"
#include "Buzzer.h"
#include "Puls.h"

extern EventGroupHandle_t xRullo;

void BuzzerInit(void){
	pinMode(PIN_BUZZER,OUTPUT);								//inizializzo il buzzer (PE15)
	
	xTaskCreate(BuzzerTask, /* Pointer to the function that implements the task.              */
	"vTaskBuzzer",      /* Text name for the task.  This is to facilitate debugging only. */
	50,   /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void BuzzerTask(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_RILEVA_OGGETTO; 
	while(1){
		xEventGroupWaitBits(xRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY); 		//aspetto bit event group
		digitalWrite(PIN_BUZZER, HIGH);																							//buzzer on 
		vTaskDelay(300);
		digitalWrite(PIN_BUZZER, LOW);																							//buzzer off
	}
}


void BuzzerTestInit(void){ 
	xTaskCreate(BuzzerTestPulsTask, /* Pointer to the function that implements the task.              */
	"vTaskPuls",    /* Text name for the task.  This is to facilitate debugging only. */
	50,   /* Stack depth in words.                 */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void BuzzerTestPulsTask(void * pvParameters){
	while(1){
		if(SwUpClick()) 																									  //verifico click pulsante sinistro
			xEventGroupSetBits(xRullo,EVENT_RILEVA_OGGETTO);									//setto bit event group
	}
}

