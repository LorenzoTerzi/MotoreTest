#define PIN_BUZZER PE15
#define EVENT_RILEVA_OGGETTO  		 				 1 << 1 // zero shift for bit0

void BuzzerInit(void);
void BuzzerTask(void * pvParameters);

void BuzzerTestInit(void);
void BuzzerTestPulsTask(void * pvParameters);
