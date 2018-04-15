/*! @file
********************************************************************************
<PRE>
ģ����       : Ӳ������ģ��
�ļ���       : _DRVTIMER_H.h
����ļ�     :
�ļ�ʵ�ֹ��� : TIMER����
����         : <--->
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
</PRE>
*******************************************************************************/

#ifndef _DRVTIMER_H
#define _DRVTIMER_H

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx.h"
#include "Macro.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
typedef struct
{
  u8 second;
  u8 minute;
  u8 hour;  
  u8 week;
  u8 date;   
  u8 month;
  u8 year;
  u8 reserve;
}STDATETIME;

typedef struct                   
{ 
  u16 DataMinuteValid:   1;
  u16 MinuteForSampleAve:1;
  
  u16 I2C32F:1;           //AT24C32��?���?�¡�??��1��??
  u16 I2C8025F:1;         //8563����?����??��1��??
  u16 FSMCNANDF:1;        //NAND��??��1��??
  u16 SPI3180F:1;         //MAX3180
  u16 USB376F:1;          //USBD???��??��1��??
  u16 NetChip:1;
  u16 GPRScom_finish:1;
  u16 GPRSTxf:1;
  u16 GPRSLoginStart:1;
  u16 GPRSLoginEnd:1;
  u16 ReadFromGprs:1;
  u16 SendTxforGpsr:1;
  u16 SendLoginTxt:2;      //1-��???2-D?��?
  u16 FirstSet:1;
  u16 SavePowDDU:1;
  u16 InitYX:1;
  u16 HasEventFlag:1;
  u16 doOneKeyConfirm:1;
  u16 YK_Recordf:2;          //��D����???��??
  u16 SendSMS:2;
  u16 CalledNum:3;           //2|o?��?��y
  u16 cycle_Dis:4;
  u16 cycle_time:3;
  u16 MonthInitNeed:1;
  u16 IfEsamCheckOn:1;
  u16 IfEthernetON:1;
  u16 IfEthHasInited:1;
  u16 EthernetInit:1;
  u16 Shellmode :1;
  u16 LocalShell:1;
  u16 WifiFrom:1;
  u16 LocalFrom:1;
  u16 pt104mode:1;
  u16 Hasaddr:1;
  u16 res:2;
  
}SPECIALFLAG;

typedef struct   
{ 
  u16 stop_cleardg:1;        //����?1?��??1�� 
  
  u16 NowTimePeriod:2;
  u16 HasPower:1;
  
  u16 KeyDownFlag:1;
  u16 SecondFlag:1;        //??����??
  u16 MinuteFlag:1;
  
  u16 DataRx:1;
  u16 DataTx:1;
  
  u16 n10ms_Flag:1;
  u16 n50msFlag:1;
  u16 AutoUp:1;
  u16 EventUp:1;
  u8 wirelessMode;
  u8 ShowERC1;
  u8 ShowERC2;
 
}DEVSTATE;

/* Exported macro ------------------------------------------------------------*/
#pragma pack(1)
//ʱ��ṹ����
typedef struct{
    u8 byDay;
    u8 byMonth:5;
    u8 byWeek:3;        //�����գ�7
    u8 byYear;
}CTimeDMWY, CDate;

typedef struct {
    u8 bySecond;
    u8 byMinute;
    u8 byHour;
    CDate date;
}CSystemTime;

//
typedef struct
{
	u8 Day;
	u8 Month;
	u8 Week;		//�����գ�7
	u8 Year;
} DateStruct;

typedef struct
{
	u8 Day;
	u8 Month;
	u8 Year;
} TimeDMYStruct;

typedef struct {
	BYTE Year;
	BYTE Month;
	BYTE Day;
	BYTE Hour;
	BYTE Minute;
}TimeYMDHMStruct;

__packed typedef struct {
	BYTE Year;
	BYTE Month;
	BYTE Day;
	BYTE Hour;
	BYTE Minute;
	BYTE Second;
}TimeYMDHMSStruct;

typedef struct
{
	u8 Second;
	u8 Minute;
	u8 Hour;
	DateStruct Date;
} SysTimeStruct;

typedef struct
{
	u8 Month;
	u8 Year;
} DateMYStruct;

typedef struct
{
	u8 Year;
	u8 Month;
	u8 Day;
} TimeYMDStruct;

typedef struct
{
	u8 Year;
	u8 Month;
	u8 Day;
	u8 Hour;
} DateYMDHStruct;



//���ݡ�ʱ����Ͻṹ��
typedef  struct
{
	union
	{
		u8	byV;
		u16	wV;
		u32	dwV;
		s32	lV;
	}val;
	SysTimeStruct SysTime; //occurrent time
}DateTimeStruct;

#pragma pack()

#endif /* _DRVTIMER_H */

//===========================================================================
// No more.
//===========================================================================

