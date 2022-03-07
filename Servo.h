#define EVENT_SMISTASX  					 1 << 4 // zero shift for bit0
#define EVENT_SMISTADX  		 			 1 << 5 // zero shift for bit0

void ServoMotoreInit(void);
void ServoSmistaDxTask(void * pvParameters);
void ServoSmistaSxTask(void * pvParameters);

void ServoMotoreTestInit(void);
void ServoTestPA0Task(void * pvParameters);   
void ServoTestPA1Task(void * pvParameters);