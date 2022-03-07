#define EVENT_RILEVA_OGGETTO  					 1 << 1 // zero shift for bit0
#define EVENT_SMISTASX  					 			 1 << 4 // zero shift for bit0
#define EVENT_SMISTADX  		 			 			 1 << 5 // zero shift for bit0
#define PIN_INFRAROSSI PE10

void InfrarossiInit(void);
void InfrarossiTask(void * pvParameters);

void InfrarossiTestInit(void);
void InfrarossiTestTask(void * pvParameters);
void InfrarossiTestPulsTask(void * pvParameters);