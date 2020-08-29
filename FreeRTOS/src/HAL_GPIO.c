#include <stdint.h>
#include "HAL_GPIO.h"
#include <stdbool.h>
#include "TM4C123GH6PM.h"



#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register

const volatile uint32_t * GPIOBaseAddress[] = {
   (volatile uint32_t*)GPIOA_BASE,
   (volatile uint32_t*)GPIOB_BASE,
   (volatile uint32_t*)GPIOC_BASE,
   (volatile uint32_t*)GPIOD_BASE,
   (volatile uint32_t*)GPIOE_BASE,
   (volatile uint32_t*)GPIOF_BASE
};

/********************************************************************
  @Name    :  GPIO_EnableDI
  @purpose :  Digital Enable the GPIO PORTS
  @param   : 
*********************************************************************/

void GPIO_EnableDI(PortName_t port, uint8_t pinMap, DI_Pull_t pull)
  {
     GPIO_InitPort(port);
      volatile GPIOA_Type * gpio = (volatile GPIOA_Type *)GPIOBaseAddress[port];
     
     if (port == PORTF && pinMap & 0x01)
       {
          /*PORTF PIN 0 is normally Locked ,need to write passcode to unlock..*/
          gpio->LOCK = GPIO_LOCK_KEY;
          gpio->CR   = 0x01;
       }
     
     /*...Clear pins for input*/
     gpio->DIR &= ~pinMap;
     
     /*...Disable alternate functions...*/
     gpio->AFSEL &= ~pinMap;
     
     /*...Set the pull up/down mode..*/
     switch(pull) 
       {
         case PULL_NONE:
	gpio->PUR &= ~pinMap;
	gpio->PDR &= ~pinMap;
	break;
	
         case PULL_UP:
          /*...Enable weak pull resistors..*/
          	gpio->PUR |= pinMap;
	break;
	
         case PULL_DOWN:
          /*...Enable weak down resistors...*/
          	gpio->PDR |= pinMap;
	break;
	
       };
     
     /*.....Enable pins for digital I/O and clear for analog I/O....*/
     	gpio->DEN |= pinMap;
	gpio->AMSEL &= ~pinMap;
	
  }
	
/******************************************************
  @Name    :  GPIO_EnableDO
  @Purpose :  Digital Enable the GPIO PORTS
  @param   : 
*******************************************************/
  
void GPIO_EnableDO(PortName_t port, PinName_t pinMap, DO_Drive_t drive, DI_Pull_t pull)
  {
   
  
  volatile GPIOA_Type * gpio = (volatile GPIOA_Type *)GPIOBaseAddress[port];
     
  if (port == PORTF && pinMap & 0x01)
    {
    /*PORTF PIN 0 is normally Locked ,need to write passcode to unlock..*/
          gpio->LOCK = GPIO_LOCK_KEY;
          gpio->CR   = 0x01;
    }
  
   gpio->DIR  |= pinMap;
  
   gpio->AFSEL &= ~pinMap;
   
   /*...Set the output drive strenght...*/
   switch (drive)
     {
       case DRIVE_2MA:
        gpio->DR2R |= pinMap;
        break;
        
       case DRIVE_4MA:
        gpio->DR4R |= pinMap;
        break;
        
       case DRIVE_8MA:
        gpio->DR8R |= pinMap;
        break;
     };
   
   /*.. Set the pull up/down mode.>*/
   switch (pull) {
     case PULL_NONE:
      gpio->PUR &= ~pinMap;	
      gpio->PDR &= ~pinMap;	
      break;
      
     case PULL_UP:
      // Enable weak pull resistors.
      gpio->PUR |= pinMap;	
      break;
      
     case PULL_DOWN:
      // Enable weak down resistors.
      gpio->PDR |= pinMap;	
      break;
   };
   
   /*... Enable pins for digital I/O and clear for analog I/O...*/
       gpio->DEN |= pinMap;
       gpio->AMSEL &= ~pinMap;
  }
	
     
void GPIO_InitPort(PortName_t port)
  {
  uint32_t portBit = (0x1 << (uint8_t)port);
  
  if(!(SYSCTL->RCGCGPIO & portBit))
    {
    SYSCTL->RCGCGPIO |= portBit;
    
    while(!(SYSCTL->RCGCGPIO & portBit)){}
    }
   }
	
	 
 /************************************************************************************************************
	 
	 @Name         : GPIO_EnableAltDigital
	 @param        : port,pinMAp-pinNumber,ctl-PCTL value tonbe stored in PCTL register,OpenDrain TURE OR FAlSE
	 @Discription  : Enabling A;ternate Functionality of pins
 *************************************************************************************************************/

void GPIO_EnableAltDigital(PortName_t port, uint8_t pinMap, uint8_t ctl, bool openDrain)
  {
  uint8_t i=0;
  uint32_t PCTLValue = 0;
  
  GPIO_InitPort(port);
  volatile GPIOA_Type* gpio = (volatile GPIOA_Type*)GPIOBaseAddress[port]; 
  
  
  // Enable pins for alternate function.
  gpio->AFSEL |= pinMap;
  
  //Enabling Open Drain for PIn
  if (openDrain)
    {
       gpio->ODR |= pinMap;
    }
  else
     gpio->ODR &= ~pinMap;

  
  for (i=0; i<7; i++)
  {
  if(pinMap & 0x01 <<i)
    {
     PCTLValue |= (ctl<<(4*i));
    }
  }
  
   gpio->PCTL |= PCTLValue;
  }
	
	
	
/***********************************************************************************
 	@Name     :  GPIO_PinWrite
   @Purpose :  Writing Value 
   @param   : 
	
	*********************************************************************************/

	void GPIO_PinWrite(PortName_t port, PinName_t pin, uint8_t value )
{
  volatile GPIOA_Type * gpio = (volatile GPIOA_Type *) GPIOBaseAddress[port];

	if (value)
	{
 gpio->DATA |=    pin;
	}
else 
	gpio->DATA &=  ~ ( pin);
	
}
