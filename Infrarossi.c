//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Arduino.h"
#include "Infrarossi.h"
#include "Puls.h"

extern EventGroupHandle_t xRullo;

void InfrarossiInit(void){
	pinMode(PIN_INFRAROSSI,INPUT);					//inizializzo sensore infrarossi (PE10)
	
	xTaskCreate(InfrarossiTask, /* Pointer to the function that implements the task.      */
	"Rileva colore",    /* Text name for the task.  This is to facilitate debugging only. */
	50,   /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void InfrarossiTask(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_RILEVA_OGGETTO;
	static char colore=0;
	while(1){
		xEventGroupWaitBits(xRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);				//aspetto bit rileva oggetto
		for(int i=0;i<600;i++){													
			vTaskDelay(1);																//aspetto 10 secondi e controllo se rilevo almeno una volta un oggetto bianco
		  if(digitalRead(PIN_INFRAROSSI)==0)																//click pulsante su = oggetto bianco
				colore=1;																		//nessun click = oggetto nero
		}
		if(colore==1){																	//se ho rilevato oggetto bianco
			xEventGroupSetBits(xRullo,EVENT_SMISTASX);		//setto bit event group
			colore=0;
		}
		else{																						//non ho rilevato oggetto bianco = oggetto nero
			xEventGroupSetBits(xRullo,EVENT_SMISTADX);		//setto bit event group 
		}
	}
}


void InfrarossiTestInit(void){ 
	pinMode(PIN_INFRAROSSI,INPUT);					//inizializzo sensore infrarossi (PE10)
	
	xTaskCreate(InfrarossiTestPulsTask, /* Pointer to the function that implements the task.              */
	"vTaskPuls",    /* Text name for the task.  This is to facilitate debugging only. */
	50,   /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
	xTaskCreate(InfrarossiTestTask, /* Pointer to the function that implements the task.      */
	"Rileva colore",    /* Text name for the task.  This is to facilitate debugging only. */
	50,   /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void InfrarossiTestTask(void * pvParameters){
	const EventBits_t xBitsToWaitFor = EVENT_RILEVA_OGGETTO;
	static char colore=0;
	while(1){
		xEventGroupWaitBits(xRullo,xBitsToWaitFor,pdTRUE,pdTRUE,portMAX_DELAY);				//aspetto bit rileva oggetto
		for(int i=0;i<3000;i++){													
			vTaskDelay(10);																//aspetto 10 secondi e controllo se rilevo almeno una volta un oggetto bianco
		  if(SwUpClick())																//click pulsante su = oggetto bianco
				colore=1;																		//nessun click = oggetto nero
		}
		if(colore==1){																	//se ho rilevato oggetto bianco
			xEventGroupSetBits(xRullo,EVENT_SMISTASX);		//setto bit event group
			colore=0;
		}
		else{																						//non ho rilevato oggetto bianco = oggetto nero
			xEventGroupSetBits(xRullo,EVENT_SMISTADX);		//setto bit event group 
		}
	}
}

void InfrarossiTestPulsTask(void * pvParameters){
	while(1){
		if(SwRightClick())																			//se clicco pulsante sinistro
			xEventGroupSetBits(xRullo,EVENT_RILEVA_OGGETTO);		//setto il bit per simulare ultrasuoni
	}
}