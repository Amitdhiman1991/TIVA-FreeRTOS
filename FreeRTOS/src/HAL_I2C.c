#include "TM4C123GH6PM.h"
#include "HAL_I2C.h"
#include "HAL_GPIO.h"





void Init_I2C(I2C_Module_t Module )
{
   //volatile I2C0_Type * I2C_t =  I2C_Module;
   uint32_t ModuleBit = (0x1 << (uint8_t) Module) 	;
    
   if (!(SYSCTL->PRI2C & ModuleBit ))
     { 
   SYSCTL->RCGCI2C |= ModuleBit;
   
   while (!(SYSCTL->PRI2C & ModuleBit )){}
     }
   
   switch(Module)
     {
        //I2C0//
       case I2C0_t:			
        GPIO_EnableAltDigital(PORTB, PIN2, 0x03 ,false);  //SCL	
        GPIO_EnableAltDigital(PORTB, PIN3, 0x03 ,true);   //SDA (open Drain)
        break;
        
        //I2C1//
       case I2C1_t:
        GPIO_EnableAltDigital(PORTA, PIN6, 0x03 ,false);  //SCL	
        GPIO_EnableAltDigital(PORTA, PIN7, 0x03 ,true);   //SDA (open Drain)
        break;
        
           //I2C2//
       case I2C2_t:
        GPIO_EnableAltDigital(PORTE, PIN4, 0x03 ,false);  //SCL	
        GPIO_EnableAltDigital(PORTE, PIN5, 0x03 ,true);   //SDA (open Drain)
        break;
        
        //I2C3//
       case I2C3_t:
        GPIO_EnableAltDigital(PORTD, PIN0, 0x03 ,false);  //SCL	
        GPIO_EnableAltDigital(PORTD, PIN1, 0x03 ,true);   //SDA (open Drain)
        break;
        
       default:
        break;
     }
 }

void I2C_EnableAsMaster(I2C_Module_t Module, uint32_t speed)
  {
  volatile I2C0_Type* i2c = (volatile I2C0_Type*)I2CBaseAddress[Module];
  
  //Enable Master Mode//
  i2c->MCR |=I2C_MCR_MASTER;
  
  //speed//
  uint32_t tpr = 
  i2c->MTPR =
  
  
  }