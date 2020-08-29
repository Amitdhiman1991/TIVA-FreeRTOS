/* I2C Drivers
 * Amit Dhiman
 *08/05/2020
*/

#ifndef HAL_I2C_H
#define HAL_I2C_H

#include <stdint.h>
#include <stdbool.h>


#define I2C_MCR_MASTER             0x00000010  // I2C Master Function Enable
#define I2C_MAX_MODULES             4
typedef enum
  {
    I2C0_t =0,
    I2C1_t =1,
    I2C2_t =2,
    I2C3_t =3
  } I2C_Module_t;
 
const volatile uint32_t I2CBaseAddress[] = {
   I2C0_BASE,
   I2C1_BASE,
   I2C2_BASE,
   I2C3_BASE
};

void Init_I2C(I2C_Module_t Module);
void I2C_EnableAsMaster(I2C_Module_t Module, uint32_t speed)



#endif  //HAL_I2C_H


