

#ifndef __HAL_UART__
#define __HAL_UART__

#include <stdint.h>
#include "TM4C123GH6PM.h"
#include "HAL.h"



typedef enum
{
  UART0_t = 0,
	UART1_t = 1,
	UART2_t = 2,
	UART3_t = 3,
	UART4_t = 4,
	UART5_t = 5,
	UART6_t = 6,
	UART7_t = 7
}	UART_Id_t; 

void UART_Init(UART_Id_t Module, PortName_t port ,uint32_t baud );


#endif
