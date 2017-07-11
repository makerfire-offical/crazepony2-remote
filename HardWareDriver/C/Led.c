/*
      ____                      _____                  +---+
     / ___\                     / __ \                 | R |
    / /                        / /_/ /                 +---+
   / /   ________  ____  ___  / ____/___  ____  __   __
  / /  / ___/ __ `/_  / / _ \/ /   / __ \/ _  \/ /  / /
 / /__/ /  / /_/ / / /_/  __/ /   / /_/ / / / / /__/ /
 \___/_/   \__,_/ /___/\___/_/    \___ /_/ /_/____  /
                                                 / /
                                            ____/ /
                                           /_____/
main.c file
编写者：
作者E-mail：
编译环境：MDK-Lite  Version: 1.0
初版时间: 2017-2-27
功能：
------------------------------------
*/

#include "Led.h"
#include "UART1.h"
#include "config.h"

void LedSet(u8 ch,char sta)
{
    switch(ch)
    {
    case signalLED:
        if(sta == 1) GPIO_SetBits(GPIOA, GPIO_Pin_12);
        else  GPIO_ResetBits(GPIOA, GPIO_Pin_12);
        break;

    case led2:
        if(sta == 1) GPIO_SetBits(GPIOB, GPIO_Pin_4);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_4);
        break;

    case led3:
        if(sta == 1) GPIO_SetBits(GPIOB, GPIO_Pin_5);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_5);
        break;

    case led4:
        if(sta == 1) GPIO_SetBits(GPIOB, GPIO_Pin_6);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_6);
        break;

    case led5:
        if(sta) GPIO_SetBits(GPIOB, GPIO_Pin_7);
        else  GPIO_ResetBits(GPIOB, GPIO_Pin_7);
        break;
    }

}

