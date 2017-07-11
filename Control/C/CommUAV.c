#include "CommUAV.h"
#include "stdio.h"
#include "config.h"
#include "control.h"

remoteMsg remoteData = {"$M<",8,0,1500,1500,1500,1000};

void sendF3Data()
{	
	memcpy(NRF24L01_RXDATA,&remoteData,sizeof(remoteData));
	NRF24L01_TxPacket(NRF24L01_RXDATA);
	
	if(remoteData.cmd & CALIBRATION)
	{
		static u8 count = 0;
		count++;
		if(count > 100)
		{
			remoteData.cmd &= (~CALIBRATION);		
			count = 0;
		}
	}
}

void cmdReduce()
{	
	if(remoteData.cmd & NEWADDRESS)
	{
		return;
	}
	else
	{
		OFF_LED1;
		LoadRCdata();
	}
	
	if(remoteData.cmd & ARM)
	{
		ON_LED3;
	}
	else
	{
		OFF_LED3;
	}
	
	if(remoteData.cmd & ALTHOLD)
	{
		ON_LED2;
	}
	else
	{
		OFF_LED2;
	}

}




