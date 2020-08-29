/* File : HAL_PLL.c
   Purpose : CLock Setting 
   Author : Amit Dhiman
   Hardware :TM4C123GH6PM

*/

#include "TM4C123GH6PM.h"

#define DEFAULT_FREQ  16000000

uint32_t PLL_BusClockFreq  = DEFAULT_FREQ;

Static void SetBusClockFreq(uint32 freq)
  {
  
  PLL_BusClockFreq  = freq;
    
  
  }

void PLL_Init(SysClockFreq_t frequency)
  {
  SYSCTL->RCC
  
  
  }