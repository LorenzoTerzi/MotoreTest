//=== INCLUDES =============================================================================
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config
#include "FreeRTOS.h"   
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timer.h"                     // ARM.FreeRTOS::RTOS:Timers
#include "event_groups.h"               // ARM.FreeRTOS::RTOS:Event Groups
#include <stdio.h>
#include "clock.h"
#include "Arduino.h"
#include "LCD.h"
#include "Puls.h"
#include "Led.h"
#include "Infrarossi.h"
#include "Ultrasuoni.h"
#include "Servo.h"
#include "RulloLCD.h"
#include "Buzzer.h"
#include "Motore.h"

EventGroupHandle_t xRullo;

int main(void){ 
	pllInit(0,10,0);
	MotoreInit();
	SwInit();
	
	
	xRullo=xEventGroupCreate();								//creazione eventGroup
	vTaskStartScheduler();
}

