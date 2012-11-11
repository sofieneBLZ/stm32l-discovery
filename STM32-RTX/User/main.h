#ifndef __MAIN_H__
#define __MAIN_H__

#include "function.h"
#include "stm32l_discovery_lcd.h"

#define enableInterrupts()   __set_PRIMASK(0);
#define disableInterrupts()  __set_PRIMASK(1);



#endif
