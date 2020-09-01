
#include <FreeRTOS.h>
#include <task.h>
#include "HAL_GPIO.h"
#include "HAL_UART.h"


void prvSetupHardware(void);


void vBlinky (void *pvParameters)
{
	uint8_t array[5] = {1,3,5,7,9};
 	const TickType_t delay =  pdMS_TO_TICKS(1000);

	
 for(;;)
	{
		GPIO_PinWrite (PORTF,PIN1,TRUE);
		 //	vTaskDelay(delay);
		/*GPIO_PinWrite (PORTF,PIN1,FALSE);
		vTaskDelay(delay);*/
	}
}


void vBlinky1 (void *pvParameters)
{
	uint8_t array[5] = {2,4,6,8,10};
	
	const TickType_t delay =  pdMS_TO_TICKS(1000);

	
 for(;;)
	{
		GPIO_PinWrite (PORTF,PIN1,FALSE);
		vTaskDelay(delay);
		
	}
}
int main()
{
   SystemCoreClock = 12000000;
	prvSetupHardware();
	
   
	//1. Create a Task Blinky To Turn On LED .
  //xTaskCreate(vBlinky ,"Blinky!!" , configMINIMAL_STACK_SIZE,NULL,1,NULL);

	//2. Create a Task Blinky To Tunr Off LED .
//	xTaskCreate(vBlinky1 ,"Blinky!!" , configMINIMAL_STACK_SIZE,NULL,1,NULL);

	//2. After creating tunr on the scheduler
	//vTaskStartScheduler();
	   UART_CharWrite(UART0_t , 'H' );
	//UART_StringWrite (UART0_t ,"Hello");
 

	//for(;;);
	
}

void prvSetupHardware(void)
{
	//GPIO_InitPort(PORTF);
	//GPIO_EnableDO(PORTF,PIN1,DRIVE_2MA,PULL_DOWN);
 	UART_Init (UART0_t,PORTA,115200);
}

