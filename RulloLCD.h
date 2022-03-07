#define EVENT_SMISTASX  					 1 << 4 // zero shift for bit0
#define EVENT_SMISTADX  		 			 1 << 5 // zero shift for bit0

void LCDInit(void);
void LCDConteggioTask(void * pvParameters);

void LCDTestInit(void);
void LCDTestPulsTask(void * pvParameters);
