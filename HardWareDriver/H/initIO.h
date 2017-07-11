#ifndef _initIO_H_
#define _initIO_H_

#include "stm32f10x.h"

/*
LED灯对应引脚
PA12	---->	LED81
PB4		---->	LED82
PB5		---->	LED83
PB6		---->	LED84
PB7		---->	LED85
*/

/*
按钮对应引脚
PA8		---->	"-"
PB1		---->	"mode"
PB3		---->	"+"
*/

//LED配置
#define ON_LED0 GPIO_SetBits(GPIOA, GPIO_Pin_12)
#define ON_LED1 GPIO_SetBits(GPIOB, GPIO_Pin_4)
#define ON_LED2 GPIO_SetBits(GPIOB, GPIO_Pin_5)
#define ON_LED3 GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define ON_LED4 GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define OFF_LED0 GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define OFF_LED1 GPIO_ResetBits(GPIOB, GPIO_Pin_4)
#define OFF_LED2 GPIO_ResetBits(GPIOB, GPIO_Pin_5)
#define OFF_LED3 GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define OFF_LED4 GPIO_ResetBits(GPIOB, GPIO_Pin_7)

void initIO(void);
static void keyInit(void);
static void ledInit(void);

#endif
