#ifndef __config_H
#define __config_H

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "delay.h"
#include "initIO.h"
#include "NRF24L01.h"
#include "Tim.h"
#include "sys_fun.h"
#include "SPI.h"
#include "control.h"
#include "stmflash.h"
#include "math.h"
#include "stdio.h"
#include "UART1.h"
#include "ConfigTable.h"
#include "adc.h"
#include "Key.h"
#include "CommUAV.h"
#endif


#define uart1baudSet 115200

#define AMERICAN_RC_MODE		//默认美国手（否则日本手）
#define VERSION_RC 100
//------------------End of File----------------------------
