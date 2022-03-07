//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "Led.h"
#include "Arduino.h"
#include "Ultrasuoni.h"
#include "Puls.h"
#include "LCD.h"
#include "RulloLCD.h"

extern EventGroupHandle_t xRullo;

void LCDInit(void){
	LCDInitialization();
	LCDDisplayString((uint8_t *)"B0 N0");
	
	xTaskCreate(LCDConteggioTask, /* Pointer to the function that implements the task.              */
	"vTaskConteggio",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void LCDConteggioTask(void * pvParameters){
	static int pacchiB=0;
	static int pacchiN=0;
	char conteggio[8];
	EventBits_t colore;
	const EventBits_t xBitsToWait = EVENT_SMISTASX | EVENT_SMISTADX;
	while(1){
		colore=xEventGroupWaitBits(xRullo, xBitsToWait, pdTRUE, pdFALSE, portMAX_DELAY);		//aspetto uno dei due bit 
		if(colore==EVENT_SMISTASX){									//se viene cliccato pulsante sinistro
			pacchiB++; 																//incremento variabile pacchi bianchi
			LedVerdeOn();															//e accendo led verde
			LedRossoOff();
		}
		if(colore==EVENT_SMISTADX){									//se viene cliccato pulsante destro
			pacchiN++;																//incremento variabile pacchi neri
			LedRossoOn();															//e accendo led rosso
			LedVerdeOff();
		}
		sprintf(conteggio,"B%dN%d",pacchiB,pacchiN);
		LCDClear();																			//stampo sul display il valore di entrambe le variabili
		LCDDisplayString((uint8_t *)conteggio);
	}
}


void LCDTestInit(void){
	xTaskCreate(LCDTestPulsTask, /* Pointer to the function that implements the task.              */
	"vTaskPuls",    /* Text name for the task.  This is to facilitate debugging only. */
	50,    /* Stack depth in words.                */
	NULL,  /* We are not using the task parameter. */
	1,     /* This task will run at priority 1.    */
	NULL); /* We are not using the task handle.    */
}

void LCDTestPulsTask(void * pvParameters){
	while(1){
		if(SwLeftClick()){															//se clicco pulsante sinistro
			xEventGroupSetBits(xRullo,EVENT_SMISTASX);		//setto il bit per i pacchi bianchi
		}
		if(SwRightClick())															//se clicco pulsante destro
			xEventGroupSetBits(xRullo,EVENT_SMISTADX);		//setto il bit per i pacchi neri
		}
}