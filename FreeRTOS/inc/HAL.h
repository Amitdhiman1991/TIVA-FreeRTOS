/* File HAL.h
 * Hardware Abstraction layer 
 * TM4C123 Tiva 
 */

#ifndef __HAL_H__
#define __HAL_H__

    
#include "TM4C123GH6PM.h"  
#include <stdbool.h>
    
// Hardware Ports//


 

typedef enum
  {
    PORTA =0,
    PORTB =1,
    PORTC =2,
    PORTD =3,
    PORTE =4,
    PORTF
 }PortName_t;
 

//Port PIN Numers//
typedef enum {
   PIN0 = 0x01,
   PIN1 = 0x02,
   PIN2 = 0x04,
   PIN3 = 0x08,
   PIN4 = 0x10,
   PIN5 = 0x20,
   PIN6 = 0x40,
   PIN7 = 0X80
} PinName_t;


typedef struct {
   PortName_t port;
   PinName_t  pin;
} PinDef_t;

//..Digital Input Pull UP/DOWN/NONE Definition

typedef enum DI_Pull{
   PULL_NONE,
   PULL_UP,
   PULL_DOWN
}DI_Pull_t;

typedef enum DO_Drive {
   DRIVE_2MA,
   DRIVE_4MA,
   DRIVE_8MA 
} DO_Drive_t;

 
 

#endif
      

