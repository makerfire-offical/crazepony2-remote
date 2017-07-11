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
#include "config.h"             //包含所有的驱动头文件
#include "stm32f10x.h"

int main(void)
{
    /***********************************/
    SystemClock_HSI(9);           //系统时钟初始化，时钟源内部HSI
    cycleCounterInit();				    // Init cycle counter
    SysTick_Config(SystemCoreClock / 1000);	//SysTick开启系统tick定时器并初始化其中断，1ms
    UART1_init(SysClock,uart1baudSet); //串口1初始化
    NVIC_INIT();	                //中断初始化
    STMFLASH_Unlock();            //内部flash解锁
    LoadParamsFromEEPROM();				//加载系统参数配置表
	initIO();							//初始化IO
    Adc_Init();										//摇杆AD初始化
    NRF24L01_INIT();              //NRF24L01初始化
    SetTX_Mode();                 //设无线模块模式

    TIM4_Init(SysClock,TIME4_Preiod);	  //定时器4初始化，定时时间单位：(TIME4_Preiod)微秒

    while (1)
    {
		//10Hz loop
        if(flag10Hz == 1)  
        {

            flag10Hz = 0;
            checkKey();
			printf("%d %d %d %d\r\n",TX_ADDRESS[0],TX_ADDRESS[1],TX_ADDRESS[2],TX_ADDRESS[3]);
        }

        //50Hz loop
        if(flag50Hz == 1)
        {
            cmdReduce();
            flag50Hz = 0;
        }

        // 83Hz 12ms
        if(flag80Hz)
        {
            flag80Hz = 0;
        }
        if(flag100Hz)
        {
            if(remoteData.cmd & NEWADDRESS)
            {
                modifyAddress();
            }
            sendF3Data();
        }
    }
}

