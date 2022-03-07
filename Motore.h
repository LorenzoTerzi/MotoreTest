#define ON 250
#define OFF 1
#define EVENT_MOTORE 		 1 << 6 // zero shift for bit0

void MotoreInit(void);

void MotoreStartTask(void * pvParameters);
void MotoreStopTask(void * pvParameters);