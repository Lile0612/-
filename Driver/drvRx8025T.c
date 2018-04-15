
/* Includes--------------------------------------------------------------*/
#include "Include.h"

// ʱ��Ĵ�������
#define	RTC8025_Second        0  //��Ĵ���
#define	RTC8025_Minute        1  //�ּĴ���
#define	RTC8025_Hour          2  //ʱ�Ĵ���
#define	RTC8025_Week          3  //���ڼĴ���
#define	RTC8025_Day           4  //�ռĴ���
#define	RTC8025_Month         5  //�¼Ĵ���
#define	RTC8025_Year          6  //��Ĵ���

// ���ƼĴ�������(ʱ��оƬ�ͺŲ���ͬ����Ӧ������Ҳ�ǲ���ͬ��)
#define	RTC8025T_Control1     (0x0D)  //����1 �Ĵ��� ��R8025T��
#define	RTC8025_Control1      (0x0E)  //����1 �Ĵ���  (R8025AC)

#define	RTC8025_PON           (0x10)  // RTC��ԴʧЧ��־λ
#define	RTC8025_XST           (0x20)  // RTC�ڲ�����ʧЧ��־λ

// ����ģʽ����
#define	RTC8025_Standard_Read (0x00)  //��׼��ģʽ
#define	RTC8025_Simple_Read   (0x04)  //�򵥶�ģʽ

STDATETIME      stDateTime;
SPECIALFLAG     specialFlag;
DEVSTATE        devState;
u8              pubRam[32];

void Get8025( u8 addr, u8 *data, u8 counter);
void Set8025( u8 addr, u8 *data, u8 counter);
void Init8025(void);
void RtcSetDateTime(STDATETIME *pTime);
void RtcSetLocalTime(void);
void UpdateDateTime(void);


//BCD��ת��λʮ����
u8 BCD2DEC(u8 temp)
{
  temp = (temp >> 4) * 10 + (temp & 0x0f);
  return temp;
}

//��λʮ����תBCD��
u8 DEC2BCD(u8 temp)
{
  temp = (temp / 10) * 16 + (temp % 10);
  return temp;
}

void Get8025( u8 addr, u8 *data,u8 counter)
{
    u8 i;
    MyI2C_Start();
    MyI2C_SendByte(0x64);
    MyI2C_SendByte(addr);
    MyI2C_Start();
    MyI2C_SendByte(0x65);
    for (i = 0;  i < counter - 1 ;  i++)
      *data++ = MyI2C_ReceiveByte(0);
    *data++ = MyI2C_ReceiveByte(1);
    MyI2C_Stop();
}

void Set8025( u8 addr, u8 *data,u8 counter)
{
   u8 i;
   MyI2C_Start();
   MyI2C_SendByte(0x64);
   MyI2C_SendByte(addr);
   for(i = 0; i <counter; i++)
     MyI2C_SendByte(*data++);
   MyI2C_Stop();
}

void Init8025(void)
{
    u8 da[3];
    da[0]=0x00;
    da[1]=0x00;         // 24Сʱģʽ����,1Hz  Ƶ�����
    da[2]=0x60;
    Set8025(RTC8025T_Control1,da,3);
    memset(pubRam,0,3);
    Get8025(RTC8025T_Control1,pubRam,3);

    if(pubRam[2] != da[2])
    {
      specialFlag.I2C8025F = 1;
    }
    else
    {
      specialFlag.I2C8025F = 0;
    }
}

void TimerDataHandle(u8* pDate)
{
    stDateTime.second = BCD2DEC(pDate[0]);
    stDateTime.minute = BCD2DEC(pDate[1]);

    if(pDate[2]==0x24)
        pDate[2] = 0;
    stDateTime.hour = BCD2DEC(pDate[2]);

    if(pDate[3] == 0x01)
        stDateTime.week = 0;
    else if(pDate[3] == 0x02)
        stDateTime.week = 1;
    else if(pDate[3] == 0x04)
        stDateTime.week = 2;
    else if(pDate[3] == 0x08)
        stDateTime.week = 3;
    else if(pDate[3] == 0x10)
        stDateTime.week = 4;
    else if(pDate[3] == 0x20)
        stDateTime.week = 5;
    else if(pDate[3] == 0x40)
        stDateTime.week = 6;

    stDateTime.date  = BCD2DEC(pDate[4]);
    stDateTime.month = BCD2DEC(pDate[5]);
    stDateTime.year  = BCD2DEC(pDate[6]);
}

void RtcSetDateTime(STDATETIME *pTime)
{
   u8 Timebuf[7];

   Timebuf[0] = DEC2BCD(pTime->second);
   Timebuf[1] = DEC2BCD(pTime->minute);
   Timebuf[2] = DEC2BCD(pTime->hour);
   Timebuf[3] = (0x01)<<(pTime->week);
   Timebuf[4] = DEC2BCD(pTime->date);
   Timebuf[5] = DEC2BCD(pTime->month);
   Timebuf[6] = DEC2BCD(pTime->year);

   Set8025(0,Timebuf,7);   //Timebuf������ΪBCD��
   TimerDataHandle(Timebuf);
}
void Write8025TDateTime(SysTimeStruct WriteTime)
{
   u8 Timebuf[7];

   Timebuf[0] = WriteTime.Second;
   Timebuf[1] = WriteTime.Minute;
   Timebuf[2] = WriteTime.Hour;
   Timebuf[3] = (0x01)<<(WriteTime.Date.Week);
   Timebuf[4] = WriteTime.Date.Day;
   Timebuf[5] = WriteTime.Date.Month;
   Timebuf[6] = WriteTime.Date.Year;

   Set8025(0,Timebuf,7);   //Timebuf������ΪBCD��
}

void RtcSetLocalTime()
{
//  struct    tm *now_ptm;
//  time_t     timep;
//  STDATETIME set_time;                      //������ʱ���붼��BCD��

//  timep = time(NULL);                       //��ȡ��ǰRTCʱ���
//  timep += 8 * 3600;                        //RTCʱ���ת���ɱ���ʱ���ʱ���
//  now_ptm = gmtime(&timep);                 //ָ��ָ��ṹ��������Ϊʮ����
//  set_time.second  = now_ptm->tm_sec;       //ȡֵ����Ϊ[0,59]
//  set_time.minute  = now_ptm->tm_min;       //ȡֵ����Ϊ[0,59]
//  set_time.hour    = now_ptm->tm_hour;      //ȡֵ����Ϊ[0,23]
//  set_time.week    = now_ptm->tm_wday;      //ȡֵ����Ϊ[0,6]��0Ϊ������
//  set_time.date    = now_ptm->tm_mday;      //ȡֵ����Ϊ[1,31]
//  set_time.month   = now_ptm->tm_mon + 1;   //ȡֵ����Ϊ[0,11] ��0Ϊ1��
//  set_time.year    = now_ptm->tm_year - 100;//tm�����1900��ʼ����
//  set_time.reserve = 0;

//  RtcSetDateTime(&set_time);
}

void UpdateDateTime()
{
    u8 Timebuf[7];

    Get8025(RTC8025_Second, Timebuf, 7);   //Timebuf������ΪBCD��
    TimerDataHandle(Timebuf);
}

void Read8025TDateTime(SysTimeStruct *pSysTime)
{
    u8 Timebuf[7];
    Get8025(RTC8025_Second, Timebuf, 7);   //Timebuf������ΪBCD��
    //TimerDataHandle(Timebuf);

    pSysTime->Date.Year = Timebuf[6];
    pSysTime->Date.Week = Timebuf[3];
    pSysTime->Date.Month = Timebuf[5];
    pSysTime->Date.Day = Timebuf[4];
    pSysTime->Hour = Timebuf[2];
    pSysTime->Minute = Timebuf[1];
    pSysTime->Second = Timebuf[0];
//    Get8025(RTC8025_Second, (u8 *)&pSysTime, 7);   //Timebuf������ΪBCD��
}


