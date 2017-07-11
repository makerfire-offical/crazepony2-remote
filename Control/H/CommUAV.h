#ifndef COMM_UAV
#define COMM_UAV

#include <string.h>
#include "NRF24L01.h"

//---------UAV control cmd


typedef enum _CMD
{
	ARM = 1 << 0,
	FREEHEAD = 1 << 1,
	ALTHOLD = 1 << 2,
	CALIBRATION = 1 << 3,
	NEWADDRESS = 1 << 4,
}CMD;

enum
{	
	ROLL,
	PITCH,
	YAW,
	THROTTLE,
};

typedef struct _remoteMsg
{
	u8 checkCode[4];
	u8 length;
	u16 cmd;
	u16 motor[4];
}remoteMsg;

extern remoteMsg remoteData;
void sendF3Data(void);
void cmdReduce(void);
	

#endif
