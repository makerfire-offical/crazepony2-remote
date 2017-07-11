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
*/

#include "config.h"

#define PRESSED_KEY(key) (GPIO_ReadInputDataBit(GPIOB,key)==0)


const uint16_t ARM_KEY = GPIO_Pin_3;
const uint16_t ALT_KEY = GPIO_Pin_8;
const uint16_t CAL_KEY = GPIO_Pin_11;
const uint16_t ONLINE_KEY = GPIO_Pin_1;

u8 armKeyFlag = 0;
u8 calibrationKeyFlag = 0;
//定高模式按钮和对频模式按钮通用
u8 modeKeyFlag = 0;


//arm按键，控制电机是否待机转动
void EXTI3_IRQHandler(void) {
    if(EXTI_GetITStatus(EXTI_Line3) != RESET) //确保是否产生了EXTI Line中断
    {
        armKeyFlag = 1;
        EXTI_ClearITPendingBit(EXTI_Line3);     //清除中断标志位
    }
}

void EXTI9_5_IRQHandler(void) {
    //calibration按键，控制IMU校准
    if(EXTI_GetITStatus(EXTI_Line8) != RESET) //确保是否产生了EXTI Line中断
    {
        calibrationKeyFlag = 1;
        EXTI_ClearITPendingBit(EXTI_Line8);     //清除中断标志位
    }
}

void checkKey(void)
{
    //中断计数
    static uint8_t keyCount = 0;
	
	if(PRESSED_KEY(ONLINE_KEY))
	{
		modeKeyFlag = 1;
	}
	else
	{
		if(modeKeyFlag)
		{
			modeKeyFlag = 0;
#ifdef AMERICAN_RC_MODE
			if(remoteData.motor[PITCH] > 1600 && remoteData.motor[ROLL] > 1600)
			{
				remoteData.cmd |= NEWADDRESS;
			}
#else
			if(remoteData.motor[THROTTLE] > 1600 && remoteData.motor[ROLL] > 1600)
			{
				remoteData.cmd |= NEWADDRESS;
			}
#endif
			else
			{
				//如果在对频模式下，则退出对频
				
				if(remoteData.cmd & NEWADDRESS)
				{
					modifyOnceFlag = 1;
					remoteData.cmd &= (~NEWADDRESS);
					//根据新发送地址重新配置
					SetTX_Mode();
					OFF_LED0;
				}
				else
				{
					//如果不在对频模式，则开启/关闭定高模式
					if(remoteData.cmd & ALTHOLD)
					{
						remoteData.cmd &= (~ALTHOLD);
					}
					else
					{
						remoteData.cmd |= ALTHOLD;
					}
				}
			}
		}
	}


    //对频模式，忽略其他按键
    if(remoteData.cmd & NEWADDRESS)
    {
        armKeyFlag = 0;
        calibrationKeyFlag = 0;
		remoteData.cmd &= (~ARM);
		remoteData.cmd &= (~ALTHOLD);
        return;
    }

    //中断判断（定高和解锁）
    if(armKeyFlag || calibrationKeyFlag)
    {
        keyCount++;
        if(keyCount<3)
        {
            return;
        }
        else
        {
            keyCount = 0;
        }
    }
    //上/解锁
    if(armKeyFlag)
    {
        armKeyFlag = 0;
        if(remoteData.cmd & ARM)
        {

            remoteData.cmd &= (~ARM);
			//上锁时关定高
			remoteData.cmd &= (~ALTHOLD);
        }
        else
        {
            if(remoteData.motor[THROTTLE] < 1150)
            {
                remoteData.cmd |= ARM;
            }
        }
    }
	
	//校准按键，发送后清除校准标志位
    if(calibrationKeyFlag)
    {
        calibrationKeyFlag = 0;
        remoteData.cmd |= CALIBRATION;       
    }
}



