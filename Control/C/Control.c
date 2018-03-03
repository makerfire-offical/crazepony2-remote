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
/* Control.c file
编写者：小马  (Camel)
作者E-mail：375836945@qq.com
编译环境：MDK-Lite  Version: 4.23
初版时间: 2014-01-28
功能：
------------------------------------
*/

#include "config.h"
#include "adc.h"
#include "control.h"
#include "math.h"

#define CONTAIN(a,b) ((a)<(b)?(a):(b))

/*
摇杆数据采集
输入参数为美国手和日本手
*/
#ifdef AMERICAN_RC_MODE
	#define THROTTLE_CHANNEL 3
	#define PITCH_CHANNEL 1
#else
	#define THROTTLE_CHANNEL 1
	#define PITCH_CHANNEL 3
#endif
#define ROLL_CHANNEL 0
#define YAW_CHANNEL 2

void LoadRCdata(void)
{
	//获取AD转换值
	remoteData.motor[YAW]=1000+(uint16_t)(Get_Adc_Average(YAW_CHANNEL,5)*1000>>12);
	remoteData.motor[ROLL]=1000+(uint16_t)(Get_Adc_Average(ROLL_CHANNEL,5)*1000>>12);	
	remoteData.motor[THROTTLE]=2000-(uint16_t)(Get_Adc_Average(THROTTLE_CHANNEL,5)*1000>>12);	
	remoteData.motor[PITCH]=1000+(uint16_t)(Get_Adc_Average(PITCH_CHANNEL,5)*1000>>12);	
	
	//给摇杆中间增加死区（不是归中油门杆可以去掉油门的）
	remoteData.motor[YAW]=(fabs(remoteData.motor[YAW]-1500)>30)?remoteData.motor[YAW]:1500;
	remoteData.motor[ROLL]=(fabs(remoteData.motor[ROLL]-1500)>30)?remoteData.motor[ROLL]:1500;
	remoteData.motor[THROTTLE]=(fabs(remoteData.motor[THROTTLE]-1500)>30)?remoteData.motor[THROTTLE]:1500;
	remoteData.motor[PITCH]=(fabs(remoteData.motor[PITCH]-1500)>30)?remoteData.motor[PITCH]:1500;
	
	//给各个值限幅[1000,2000]
	remoteData.motor[YAW]=CONTAIN(2000,remoteData.motor[YAW]);
	remoteData.motor[YAW]=-CONTAIN(-remoteData.motor[YAW],-1000);
	remoteData.motor[ROLL]=CONTAIN(2000,remoteData.motor[ROLL]);
	remoteData.motor[ROLL]=-CONTAIN(-remoteData.motor[ROLL],-1000);
	remoteData.motor[THROTTLE]=CONTAIN(2000,remoteData.motor[THROTTLE]);
	remoteData.motor[THROTTLE]=-CONTAIN(-remoteData.motor[THROTTLE],-1000);
	remoteData.motor[PITCH]=CONTAIN(2000,remoteData.motor[PITCH]);
	remoteData.motor[PITCH]=-CONTAIN(-remoteData.motor[PITCH],-1000);
	
	//摇杆值灵敏度（ROLL\PITCH）
	const float Q = 0.5;
	remoteData.motor[ROLL] = 1500 + Q*(remoteData.motor[ROLL]-1500);
	remoteData.motor[PITCH] = 1500 + Q*(remoteData.motor[PITCH]-1500);
	
	
}


