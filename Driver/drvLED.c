/*! @file
********************************************************************************
<PRE>
ģ����       : ����ģ��
�ļ���       : drvLED.c
����ļ�     :
�ļ�ʵ�ֹ��� : LED��������
����         : <--->
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2012/11/12   1.0    <xxxx>         ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/
#ifdef _GUILED_
/* Includes ------------------------------------------------------------------*/
#include "Include.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

const u8 cg_DispCharacter[] = {	CHARMODE_0,/*0*/
								CHARMODE_1,/*1*/
								CHARMODE_2,/*2*/
								CHARMODE_3,/*3*/
								CHARMODE_4,/*4*/
								CHARMODE_5,/*5*/
								CHARMODE_6,/*6*/
								CHARMODE_7,/*7*/
								CHARMODE_8,/*8*/
								CHARMODE_9 /*9*/
					           };
/****************************************************************************************
** ��������: TM1640_delay
** ��������: ��ʱ
** ��    ��: None
** �� �� ֵ: None
** ����  ��:
** ��  ����: 2009��10��14��
**---------------------------------------------------------------------------------------
** �� �� ��:
** �ա�  ��:
**--------------------------------------------------------------------------------------
****************************************************************************************/
void TM1640_delay(void)
{
   u8 i = 30; //��������Ż��ٶ�
   while(i)
   {
     i--;
   }
}


u8 HT_Data_Index(unsigned char data)
{
    return cg_DispCharacter[data];
}
// TM1640��ʼ
void TM1640_Start(void)
{
	TM_DIN_H;
	TM_CLK_H;
	TM1640_delay();
	TM_DIN_L;
	TM1640_delay();
	TM_CLK_L;
	TM1640_delay();
}
// TM1640����
void TM1640_End(void)
{
	TM_DIN_L;
	TM_CLK_L;
	TM1640_delay();
	TM_CLK_H;
	TM1640_delay();
	TM_DIN_H;
	TM1640_delay();
}
// дһ���ֽ�����
void TM1640_I2C_WrByte(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
        TM_CLK_L;
	    TM1640_delay();
		if(dat&0x01)
		    TM_DIN_H;
		else
		    TM_DIN_L;
		TM1640_delay();
		TM_CLK_H;
		dat>>=1;//����һλ����λ�Ƚ�������ͨѶģʽ
		TM1640_delay();
	}
}

/***********************************
��ָ����ַд��һ���ֽڵ�����
�ȷ�����ٷ�����
************************************/
void TM1640_Write(unsigned char dat)
{

	TM1640_I2C_WrByte(dat);
}

void Update_screen(void)
{
		u8 i;
		TM1640_Start();
		TM1640_I2C_WrByte(0x40); // �����Զ���ַ
		TM1640_End();

		TM1640_Start();
		TM1640_I2C_WrByte(0xc0); // ������ʼ��ַ

		for(i=0;i<16;i++)
		{
			TM1640_Write(vg_Display_Value[i]);     // LED�� LED    pDisplay_Data[i]
		}

		TM1640_End();
		TM1640_Start();
        if(DispMode == ProgMode)
        {
            switch(LEDLEVEL)
            {
                case 0x01:
                    TM1640_I2C_WrByte(0X89);
                    break;
                case 0x02:
                    TM1640_I2C_WrByte(0X8A);
                    break;
                case 0x03:
                    TM1640_I2C_WrByte(0X8B);
                    break;
                default:
                    TM1640_I2C_WrByte(0X8A);
                    break;
            }
        }
        else //if(DispMode == ReadMode)
        {
            switch(g_tParam.CtrlParam.BlackTime)
            {
                case 0x01:
                    TM1640_I2C_WrByte(0X89);
                    break;
                case 0x02:
                    TM1640_I2C_WrByte(0X8A);
                    break;
                case 0x03:
                    TM1640_I2C_WrByte(0X8B);
                    break;
                default:
                    TM1640_I2C_WrByte(0X8A);
                    break;
            }
        }

		TM1640_End();

		for(i=0;i<16;i++)
		{
			vg_Display_Value[i] = 0;     // LED�� LED    pDisplay_Data[i]
		}
}

#endif // #ifdef _GUILED_

