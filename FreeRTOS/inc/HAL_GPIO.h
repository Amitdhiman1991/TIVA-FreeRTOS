#ifndef __HAL_GPIO_H__
#define __HAL_GPIO_H__

#include "HAL.h"
#define TRUE  1
#define FALSE 0


void GPIO_InitPort(PortName_t port);
void GPIO_EnableDI(PortName_t port, uint8_t pinMap, DI_Pull_t pull);
void GPIO_EnableDO(PortName_t port, PinName_t pinMap, DO_Drive_t drive, DI_Pull_t pull);
void GPIO_PinWrite(PortName_t port, PinName_t pin, uint8_t value );

void GPIO_EnableAltDigital(PortName_t port, uint8_t pinMap, uint8_t ctl, bool openDrain);



#endif //HAL_GPIO_H
