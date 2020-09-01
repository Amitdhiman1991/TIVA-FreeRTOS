/*  Name      :Amit Dhiman
*   Purpose   :UART Driver
*   Board     :TIVA C TM4C1236GHPM
*/

#include <math.h>
#include "HAL_UART.h"
#include "HAL_GPIO.h"


	
	const volatile uint32_t *UART_BaseAddress[] = {
		
   (volatile uint32_t *)UART0_BASE,
	 (volatile uint32_t *)UART1_BASE,
	 (volatile uint32_t *)UART2_BASE,
	 (volatile uint32_t *)UART3_BASE,
	 (volatile uint32_t *)UART4_BASE,
	 (volatile uint32_t *)UART5_BASE,
	 (volatile uint32_t *)UART6_BASE,
	 (volatile uint32_t *)UART7_BASE,
	 };
	
/**************************************************************************************************
	 
	 @Function    : UART_Init
   @params      :	UART_Id_t Module ,
	 @return      : None
	 @purpose     : Uart Initialization
	 
 **************************************************************************************************/	 
	 void UART_Init(UART_Id_t Module, PortName_t port , uint32_t baud)
	 {
		  uint32_t Baud_uartdivisor;
			float frac,integer;
		 //Setting Specific UART Bit in RCGCUART register
		 
		 SYSCTL->RCGCUART |= (0x1 << Module);
		 
		 switch (Module)
		 {
				 case UART0_t :
					 if(port == PORTA )
						 {
						 GPIO_InitPort(PORTA);
						 GPIO_EnableAltDigital(PORTA,PIN0|PIN1 ,0x01,FALSE);
						 }
						  
						 break;
			 
			 case UART1_t :
						if(port == PORTB)
						{				
						GPIO_InitPort(PORTB);
						GPIO_EnableAltDigital(PORTB,PIN0|PIN1 ,0x01,true);
						}
						if(port == PORTC)
						{
						GPIO_InitPort(PORTC);
						GPIO_EnableAltDigital(PORTC,PIN4|PIN5 ,0x02,true);
						}
					 	break;
			 
			 case UART2_t :
				   GPIO_InitPort(PORTD);
			     break;
			 
			 case  UART3_t  :
				   GPIO_InitPort(PORTC);
			     break;
			 
			  case   UART4_t  :
				   GPIO_InitPort(PORTC);
			     break;
			 
			 case UART5_t :
				   GPIO_InitPort(PORTE);
			     break;
			 
			 case UART6_t :
				   GPIO_InitPort(PORTD);
			     break;
			 
			 case UART7_t :
				   GPIO_InitPort(PORTE);
			     break;
			 
			 default:
				 break;
		 }
	 
	 volatile UART0_Type * uart_t = (volatile UART0_Type *)UART_BaseAddress[Module];
	 
	 //1. Disable the UART by clearing the UARTEN bit in the UARTCTL register
	 uart_t->CTL = 0;
	 
	 //2. Write the integer portion of the BRD to the UARTIBRD register.

	 /*BRD = 20,000,000 / (16 * 115,200) = 10.8507
		which means that the DIVINT field of the UARTIBRD register (see page 914) should be set to 10
		decimal or 0xA. The value to be loaded into the UARTFBRD register (see page 915) is calculated
			by the equation:
			UARTFBRD[DIVFRAC] = integer(0.8507 * 64 + 0.5) = 54*/
			
	   Baud_uartdivisor = (16 * baud);
		 
		uint32_t divisor = (SystemCoreClock /Baud_uartdivisor) ;
		 
		  
		 uart_t ->IBRD = divisor ;
		 uart_t ->FBRD = (((SystemCoreClock % Baud_uartdivisor) * 64) / Baud_uartdivisor) + 0.5;
		 
		 uart_t->LCRH  = 0x00000060;                           //setting 8 bit 
		 
		 uart_t->CC = 0; 		 																		//using system clock
	 
	   uart_t->CTL = 0x00000301;                              // Enabling uart setting rx and tx  
	 }
	 
	 
	 void UART_CharWrite(UART_Id_t Module , char a )
	 {
	 
	 volatile UART0_Type * uart_t  =  (volatile UART0_Type *)UART_BaseAddress[Module];
	 
	 while(uart_t->FR & 0x20){}
		 
		 uart_t->DR = a ;
	 
	 
	 }
	 
	 
	 void UART_StringWrite(UART_Id_t Module ,char * s)
	 {
		 
	  while (*s != '\0' )
		{
		UART_CharWrite(Module , *s);
			s++;
		}
	 
	}		 