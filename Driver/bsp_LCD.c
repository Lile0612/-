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
#ifdef _GUILCD_

/* Includes ------------------------------------------------------------------*/
//#include "drvI2C.h"
//#include "drvLCD.h"
#include "Include.h"


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define BIAS	0x30  // �ڲ�RCʱ��
#define SYSEN	0x02
#define LCDON	0x06
#define LCDOFF	0x04
#define TONE4K 0x80
#define TONE2K 0xA0

#define DISPNUM	92

enum emLCD_DISP_ADDR
{
	LCD_DISP_ADDR_COS = 0x0001,
	LCD_DISP_ADDR_COM = 0x0002,
	LCD_DISP_ADDR_DLY = 0x0004,
	LCD_DISP_ADDR_ONPF = 0x0008,
	LCD_DISP_ADDR_Q = 0x0101,
	LCD_DISP_ADDR_P = 0x0102,
	LCD_DISP_ADDR_I = 0x0104,
	LCD_DISP_ADDR_U = 0x0108,

};



// ��0������ 16��  le
// 0 1 2 3 4 5 6 7 8 9
const unsigned char LCD_COM_Row0_Value[][4] =
            {{0xA0,0x30,0x90,0x30},{0x00,0x00,0x10,0x20},{0x90,0x30,0x90,0x90},{0x90,0x10,0x90,0xB0},// 0 1 2 3
            {0x30,0x00,0x10,0xA0},{0xB0,0x10,0x80,0xB0},{0xB0,0x30,0x80,0xB0},{0x80,0x00,0x90,0x20}, // 4 5 6 7
            {0xB0,0x30,0x90,0xB0},{0xB0,0x10,0x90,0xB0},{0xB0,0x20,0x90,0xA0},{0x30,0x30,0x00,0xB0}, // 8 9 a b
            {0xA0,0x30,0x80,0x10},{0x10,0x30,0x10,0xB0},{0xB0,0x30,0x80,0x90},{0xB0,0x20,0x80,0x80}, // c d e f
            {0xA0,0x30,0x80,0x30},{0x30,0x20,0x10,0xA0},{0x00,0x80,0x40,0x00},{0x00,0x10,0x90,0x30}, // g h i j
            {0x00,0x80,0x60,0x40},{0x20,0x30,0x00,0x10},{0x60,0x20,0x30,0x20},{0x10,0x20,0x00,0xA0}, // k l m n
            {0x10,0x30,0x00,0xB0},{0xB0,0x20,0x90,0x80},{0xB0,0x00,0x90,0xA0},{0x10,0x20,0x00,0x80}, // o p q r
            {0xB0,0x10,0x80,0xB0},{0x80,0x80,0xC0,0x00},{0x20,0x30,0x10,0x30},{0x30,0x10,0x10,0xB0}, // s t u y
            {0x80,0x50,0xA0,0x10},{0x10,0x80,0x40,0x80},{0x10,0x00,0x00,0x80},{0x00,0x00,0x00,0x00},
            {0xF0,0xF0,0xF0,0xF0},}; // NC

// ��1��2������  le
// 0 1 2 3 4 5 6 7 8 9
const unsigned char LCD_COM_Row12_Value[][2] =
					{{0x50,0xF0},{0x50,0x00},{0x30,0xD0},{0x70,0x90},{0x70,0x20}, // 0 1 2 3 4
					{0x60,0xB0},{0x60,0xF0},{0x50,0x10},{0x70,0xF0},{0x70,0xB0},  // 5 6 7 8 9
					{0x70,0x70},{0x60,0xE0},{0x00,0xF0},{0x70,0xC0},{0x20,0xF0},  // a b c d e
					{0x20,0x70},{0x40,0xF0},{0x70,0x60},{0x00,0x60},{0x00,0xE0},  // f g h i l
					{0x60,0x50},{0x60,0x40},{0x60,0xC0},{0x30,0x70},{0x70,0x30},  //m n o p q
					{0x20,0x40},{0x60,0xB0},{0x20,0xE0},{0x50,0xE0},{0x70,0xA0},  //r s t u y
					{0x20,0x00},{0x00,0x00},}; // - NC

// ��3������  le
// 0 1 2 3 4 5 6 7 8 9
const unsigned char LCD_COM_Row3_Value[][2] =
					{{0x70,0x70},{0x20,0x40},{0x50,0xD0},{0x60,0xD0},{0x20,0xE0},  //0 1 2 3 4
					{0x60,0xB0},{0x70,0xB0},{0x20,0x50},{0x70,0xF0},{0x60,0xF0},   //5 6 7 8 9
					{0x50,0x30},{0x70,0xC0},{0x10,0xB0},{0x30,0xE0},{0x10,0xF0},   //C d F h P
					{0x20,0xF0},{0x60,0xB0},{0x50,0xA0},{0x00,0x80},{0x70,0x60},   //q s t - U
					{0x70,0x80},{0x50,0x20},{0x70,0x00},{0x10,0x80},}; //o l u r

// С����  le
const unsigned char LCD_COM_Row0_DotValue[] = {0x10,0x20,0x10};
const unsigned char LCD_COM_Row1_DotValue[] = {0x80,0x80,0x80};
const unsigned char LCD_COM_Row2_DotValue[] = {0x80,0x80,0x80};
const unsigned char LCD_COM_Row3_DotValue[] = {0x80,0x80,0x80};  //P15 P17 P18

// ð��
const unsigned char LCD_COM_Row_ColonValue[] = {0x20,0x10};   //P13 P16

// ���� le
const unsigned char LCD_COM_NegaSign[] = {0x80,0x20,0x20,0x80};
const unsigned char LCD_PIN_NegaSign[] = {13,57,56,73};

// ��3�� ��ͷ��š�
const unsigned char LCD_COM_Sum[] = {0x10,0x10,0x10,0x80};
const unsigned char LCD_PIN_Sum[] = {12,57,56,80};

// A�� B�� C�� le
const unsigned char LCD_COM_Phase[] = {0x20,0x40,0x40};
const unsigned char LCD_PIN_Phase[] = {13,57,56};

// AB�� BC�� CA�� le
const unsigned char LCD_COM_PhaseD[] = {0x60,0xC0,0xC0};
const unsigned char LCD_PIN_PhaseD[] = {13,57,56};

const unsigned char LCD_COM_ClearLeft[] = {0xE0,0xF0,0xF0,0xF0};
const unsigned char LCD_PIN_ClearLeft[] = {13,57,56,80};

// ��ʾ��λ w kw mw kmw var kvar mvar kmvar va kva mva kmva oxff v kv mv A kA mA
const unsigned char LCD_COM_UNIT0[][4] =
                    {{0x00,0x00,0x10,0x00},{0x10,0x00,0x10,0x00},{0x00,0x80,0x10,0x00},{0x10,0x80,0x10,0x00},
                    {0x00,0x00,0x00,0x40},{0x00,0x40,0x00,0x40},{0x00,0x20,0x00,0x40},{0x00,0x60,0x00,0x40},
                    {0x00,0x00,0x60,0x00},{0x20,0x00,0x60,0x00},{0x40,0x00,0x60,0x00},{0x60,0x00,0x60,0x00},
                    {0x00,0x00,0x20,0x00},{0x20,0x00,0x20,0x00},{0x40,0x00,0x20,0x00},
                    {0x00,0x00,0x40,0x00},{0x20,0x00,0x40,0x00},{0x40,0x00,0x40,0x00},
                    {0x00,0x00,0x20,0x80},{0x00,0x00,0x40,0x80},{0x70,0xE0,0x70,0xC0},};
const unsigned char LCD_PIN_UNIT0[] = {30,31,32,33};

// ��ʾ��λ w kw mw kmw var kvar mvar kmvar va kva mva kmva oxff v kv mv A kA mA
const unsigned char LCD_COM_UNIT1[][4] =
                    {{0x00,0x40,0x00,0x00},{0x00,0x40,0x40,0x00},{0x00,0x40,0x20,0x00},{0x00,0x40,0x60,0x00},
                    {0x00,0x80,0x00,0x00},{0x00,0x80,0x80,0x00},{0x00,0x80,0x00,0x80},{0x00,0x80,0x80,0x80},
                    {0x60,0x00,0x00,0x00},{0x60,0x20,0x00,0x00},{0x60,0x00,0x10,0x00},{0x60,0x20,0x10,0x00},
                    {0x20,0x00,0x00,0x00},{0x20,0x20,0x00,0x00},{0x20,0x00,0x10,0x00},
                    {0x40,0x00,0x00,0x00},{0x40,0x20,0x00,0x00},{0x40,0x00,0x10,0x00},
                    {0xA0,0x00,0x00,0x00},{0xC0,0x00,0x00,0x00},{0xE0,0xE0,0xF0,0x80},};
const unsigned char LCD_PIN_UNIT1[] = {35,37,39,41};

// ��ʾ��λ w kw mw kmw var kvar mvar kmvar va kva mva kmva oxff v kv mv A kA mA
const unsigned char LCD_COM_UNIT2[][4] =
                    {{0x00,0x40,0x00,0x00},{0x00,0x40,0x40,0x00},{0x00,0x40,0x20,0x00},{0x00,0x40,0x60,0x00},
                    {0x00,0x80,0x00,0x00},{0x00,0x80,0x80,0x00},{0x00,0x80,0x00,0x80},{0x00,0x80,0x80,0x80},
                    {0x10,0x20,0x00,0x00},{0x10,0x30,0x00,0x00},{0x10,0x20,0x10,0x00},{0x10,0x30,0x10,0x00},
                    {0x00,0x20,0x00,0x00},{0x00,0x30,0x00,0x00},{0x00,0x20,0x10,0x00},
                    {0x10,0x00,0x00,0x00},{0x10,0x10,0x00,0x00},{0x10,0x00,0x10,0x00},
                    {0x20,0x20,0x00,0x00},{0x30,0x00,0x00,0x00},{0x30,0xF0,0xF0,0x80},};
const unsigned char LCD_PIN_UNIT2[] = {34,36,38,40};

// ��ʾ��λ kwh kvar
const unsigned char LCD_COM_UNIT3[][3] =
                    {{0x60,0x20,0x00},{0x80,0xC0,0x00},{0xE0,0xF0,0x80}};
const unsigned char LCD_PIN_UNIT3[] = {58,60,62};

// ���������1
const unsigned char LCD_COM_INS[] = {0x40,0x20,0x80,0x10,0x40,0x20,0x80,0x80};
const unsigned char LCD_PIN_INS[] = {89,88,86,87,91,90,90,87};

// ���������2
const unsigned char LCD_COM_OUTS[] = {0X80,0X80,0X80,0X80};
const unsigned char LCD_PIN_OUTS[] = {84,83,82,85};

// ������״̬1
const unsigned char LCD_COM_IN_On[] =   {0x20,0x10,0x80,0x20,0x20,0x10,0x40,0x10}; //�պ�
const unsigned char LCD_COM_IN_Off[] =  {0x10,0x80,0x40,0x40,0x10,0x80,0x40,0x20}; //����
const unsigned char LCD_PIN_IN_On[] =   {89,88,88,87,91,90,86,86};
const unsigned char LCD_PIN_IN_Off[] =  {89,89,88,87,91,91,90,86};

// ������״̬2
const unsigned char LCD_COM_OUT_On[] =  {0X40,0X40,0X40,0X40};//�պ�
const unsigned char LCD_COM_OUT_Off[] = {0X20,0X10,0X20,0X10};//����
const unsigned char LCD_PIN_OUT_On[] =  {84,83,82,85};
const unsigned char LCD_PIN_OUT_Off[] = {84,82,82,84};

// ��������ʾ
const unsigned char LCD_COM_FourQ[] = {0X20,0X20,0X10,0X10};
const unsigned char LCD_PIN_FourQ[] = {81,83,81,85};

// ʱ���
const unsigned char LCD_COM_TimeDot[PH_TH][2] = {{0x10,0x80},{0x80,0x20},{0x20,0x80}};
const unsigned char LCD_PIN_TimeDot[PH_TH][2] = {{18,9},{8,18},{66,78}};

// �ֲ�Ͷ��ָʾ
const unsigned char LCD_COM_StarAON[] = {0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x10,0x40,0x10};
const unsigned char LCD_COM_StarBCON[] = {0x20,0x80,0x20,0x80,0x20,0x80,0x20,0x10,0x40,0x10};
const unsigned char LCD_PIN_StarAON[] = {25,25,24,24,34,35,35,37,37,36};
const unsigned char LCD_PIN_StarBON[] = {27,27,26,26,32,33,33,39,39,38};


const unsigned char LCD_PIN_Delta12_1_17_ONOFF[] = {75,73,71,69,67,65,63,61,59,57,55,53,51,49,47,45,43};
const unsigned char LCD_PIN_Delta12_18_20_ON0FF[] = {42,44,46};

// S1 COS U(V) I(A) P(kW) Q(kvar) S(kVA) Freq(Hz) HU(%) IU(%), t
const unsigned char LCD_COM_Norm[] = {0x20,0x10,0x80,0x40,0x20,0x10,0x10,0x20,0x10,0x20, 0x10};
const unsigned char LCD_PIN_Norm[] = {0,0,1,1,1,1,19,19,21,21,83};
// CT PT Ͷ����ʱ Ͷ������ �г�����  ��ѹ���� �������� г������ �¶ȱ���
const unsigned char LCD_COM_Set[] = {0x20,0x40,0x40,0x80,0x40,0x80,0x40,0x20,0x10};
const unsigned char LCD_PIN_Set[] = {83,83,0,0,82,80,80,80,80};
// S3 S4 ��ƽ�� Ͷ�� �г�  ����ѹ  Ƿ��ѹ ������ Ƿ���� г��Խ�� ȱ��
const unsigned char LCD_COM_Prt[] = {0x40,0x20,0x80,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10};
const unsigned char LCD_PIN_Prt[] = {21,23,21,20,20,20,20,50,50,50,50};
// S15 S16 S17 S18 S19 S20
const unsigned char LCD_COM_UIHL12[] = {0x80,0x40,0x20,0x20,0x40,0x80};
const unsigned char LCD_PIN_UIHL12[] = {81,81,81,79,79,77};

// ����״ָ̬ʾ
const unsigned char LCD_COM_CapStatus = 0x10;
const unsigned char LCD_PIN_CapStatus = 23;
// ����״ָ̬ʾ�ֲ���λ A�� B�� C��
const unsigned char LCD_COM_LedPhase[] = {0x10,0x10,0x10};
const unsigned char LCD_PIN_LedPhase[] = {25,27,29};
// ����״ָ̬ʾ��� 1-30
const unsigned char LCD_COM_LedAddr[] = {0x40,0x80,0x10,0x20,0x40,0x80,0x80,0x40,0x20,0x10,0x40,
											0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x20,0x80,0x40,0x80,0x40,0x80,0x40};
const unsigned char LCD_PIN_LedAddr[] = {23,23,22,22,22,22,48,48,48,48,77,74,72,70,68,66,64,62,60,58,56,54,52,52,36,36,38,38,40,40};
// ���� �ֶ� �Զ� ���� ����
const unsigned char LCD_COM_Ctrl[] = {0x10,0x20,0x20,0x20,0x20};
const unsigned char LCD_PIN_Ctrl[] = {76,76,70,64,58};
// ���� ����
const unsigned char LCD_COM_Sys[PH_TH][2] = {{0x40,0x80},{0x40,0x80},{0x80,0x40}};
const unsigned char LCD_PIN_Sys[PH_TH][2] = {{19,19},{18,18},{52,52}};
// ���� ��� ������ ����
const unsigned char LCD_COM_CapType[] = {0x10,0x20,0x40,0x80};
const unsigned char LCD_PIN_CapType[] = {82,78,78,79};

// �Դ�
unsigned char g_Display_Data[DISPNUM];
unsigned char sg_Display_Data_Back[DISPNUM];

const u8 cg_Disp[] = {	CHAR_0,/*0*/
						CHAR_1,/*1*/
						CHAR_2,/*2*/
						CHAR_3,/*3*/
						CHAR_4,/*4*/
						CHAR_5,/*5*/
						CHAR_6,/*6*/
						CHAR_7,/*7*/
						CHAR_8,/*8*/
						CHAR_9 /*9*/
			           };

void HT_I2C_delay(void)
{
#ifndef _DEBUG
	int i = 60; //��������Ż��ٶ�
#else
	int i = 30; //��������Ż��ٶ�
#endif
   while(i)
   {
     i--;
   }
}

void HT_Send_Delay(void)
{
#ifndef _DEBUG
	int i = 12; //��������Ż��ٶ�
#else
	int i = 6; //��������Ż��ٶ�
#endif
   while(i)
   {
     i--;
   }
}

// дһ���ֽ�����
void HT_SendBit(unsigned char data, unsigned char cnt)
{
    unsigned char i;
    for(i = 0; i < cnt; i++)  // ���8λ����
    {
        if(data&0x80)
        {
        	LCD_SDA_H;
        }
        else
        {
        	LCD_SDA_L;
        }
        LCD_SCL_L;
        data<<=1;
		    nus_delay(5);
        LCD_SCL_H;
    }
}

void HT_SendCmd(unsigned char Command)
{

	nus_delay(5);
	LCD_CS_L;
	HT_SendBit(0x80, 4);
	HT_SendBit(Command, 8);
	nus_delay(5);
    LCD_CS_H;

}

void HT_WriteData(unsigned char addr,unsigned char data)
{
	LCD_CS_L;
	HT_SendBit(0xa0, 3);
	HT_SendBit(addr, 7);
	HT_SendBit(data, 4);
	LCD_CS_H;
}

// Һ������
void HT_LedStatus(BOOL bStatus)
{
	if (bStatus)
	{
		LCD_BG_H;
	}
	else
	{
		LCD_BG_L;
	}
}

u8 HT_Data_Index(unsigned char data)
{
    return cg_Disp[data];
}

void HT_Init(void)      //Һ����Ļ��ʼ��
{
	int i = 0;
	LCD_CS_H;
	LCD_SCL_H;
	LCD_SDA_H;
	LCD_CS_L;
	HT_LedStatus(TRUE);

	HT_SendCmd(BIAS);
	HT_SendCmd(SYSEN);
	HT_SendCmd(LCDON);
    HT_SendCmd(TONE4K);
	LCD_CS_H;
    HT_I2C_delay();
	for (i = 0; i < DISPNUM; i++)
	{
		g_Display_Data[i] = 0x00;
		sg_Display_Data_Back[i] = 0xff;
	}
	Lcd_Update_screen();
}

/**
  * @brief  д��������
  * @param  unsigned char row:��(0-2)
  *			unsigned char col:��(0-4)
  *			unsigned char Value:��ֵ(0-3λΪֵ����С����ʱ����4λ��1)
  * @retval None
  */
void HT_WriteValue(unsigned char row,unsigned char col,unsigned char Value)
{
	if (row == 0)
	{
		if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[14+4*col], LCD_COM_Row0_Value[36][0]);
			MODIFY_BIT(g_Display_Data[15+4*col], LCD_COM_Row0_Value[36][1]);
			MODIFY_BIT(g_Display_Data[16+4*col], LCD_COM_Row0_Value[36][2]);
			MODIFY_BIT(g_Display_Data[17+4*col], LCD_COM_Row0_Value[36][3]);
		}
		else
		{
			if (Value <= DISP1_ALL)
			{
				MODIFY_BIT(g_Display_Data[14+4*col], LCD_COM_Row0_Value[36][0]);
			    MODIFY_BIT(g_Display_Data[15+4*col], LCD_COM_Row0_Value[36][1]);
			    MODIFY_BIT(g_Display_Data[16+4*col], LCD_COM_Row0_Value[36][2]);
			    MODIFY_BIT(g_Display_Data[17+4*col], LCD_COM_Row0_Value[36][3]);
				g_Display_Data[14+4*col] |= LCD_COM_Row0_Value[Value][0];
				g_Display_Data[15+4*col] |= LCD_COM_Row0_Value[Value][1];
				g_Display_Data[16+4*col] |= LCD_COM_Row0_Value[Value][2];
				g_Display_Data[17+4*col] |= LCD_COM_Row0_Value[Value][3];
			}
		}
	}
	else if (row == 1)
	{
		if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[53-4*col], LCD_COM_Row12_Value[8][0]);
			MODIFY_BIT(g_Display_Data[55-4*col], LCD_COM_Row12_Value[8][1]);
		}
		else
		{
			if (Value <= DISP_ALL)
			{
				MODIFY_BIT(g_Display_Data[53-4*col], LCD_COM_Row12_Value[8][0]);
			    MODIFY_BIT(g_Display_Data[55-4*col], LCD_COM_Row12_Value[8][1]);
				g_Display_Data[53-4*col] |= LCD_COM_Row12_Value[Value][0];
				g_Display_Data[55-4*col] |= LCD_COM_Row12_Value[Value][1];
			}
		}
	}
	else if (row == 2)
	{
		if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[52-4*col], LCD_COM_Row12_Value[8][0]);
			MODIFY_BIT(g_Display_Data[54-4*col], LCD_COM_Row12_Value[8][1]);
		}
		else
		{
			if (Value <= DISP_ALL)
			{
				MODIFY_BIT(g_Display_Data[52-4*col], LCD_COM_Row12_Value[8][0]);
			    MODIFY_BIT(g_Display_Data[54-4*col], LCD_COM_Row12_Value[8][1]);
				g_Display_Data[52-4*col] |= LCD_COM_Row12_Value[Value][0];
				g_Display_Data[54-4*col] |= LCD_COM_Row12_Value[Value][1];
			}
		}
	}
	else if (row == 3)
	{
        if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[78-2*col], LCD_COM_Row3_Value[8][0]);
			MODIFY_BIT(g_Display_Data[79-2*col], LCD_COM_Row3_Value[8][1]);
		}
		else
		{
			if (Value <= CHAR_NUM)
			{
				MODIFY_BIT(g_Display_Data[78-2*col], LCD_COM_Row3_Value[8][0]);
			    MODIFY_BIT(g_Display_Data[79-2*col], LCD_COM_Row3_Value[8][1]);
				g_Display_Data[78-2*col] |= LCD_COM_Row3_Value[Value][0];
				g_Display_Data[79-2*col] |= LCD_COM_Row3_Value[Value][1];
			}
		}
	}
	else if (row == 4)
	{
        if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[68-2*col], LCD_COM_Row3_Value[8][0]);
			MODIFY_BIT(g_Display_Data[69-2*col], LCD_COM_Row3_Value[8][1]);
		}
		else
		{
			if (Value <= CHAR_NUM)
			{
				MODIFY_BIT(g_Display_Data[68-2*col], LCD_COM_Row3_Value[8][0]);
			    MODIFY_BIT(g_Display_Data[69-2*col], LCD_COM_Row3_Value[8][1]);
				g_Display_Data[68-2*col] |= LCD_COM_Row3_Value[Value][0];
				g_Display_Data[69-2*col] |= LCD_COM_Row3_Value[Value][1];
			}
		}
	}
	else if (row == 5)
	{
		if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[0+4*col], LCD_COM_Row0_Value[36][0]);
			MODIFY_BIT(g_Display_Data[1+4*col], LCD_COM_Row0_Value[36][1]);
			MODIFY_BIT(g_Display_Data[2+4*col], LCD_COM_Row0_Value[36][2]);
			MODIFY_BIT(g_Display_Data[3+4*col], LCD_COM_Row0_Value[36][3]);
		}
		else
		{
			if (Value <= DISP1_ALL)
			{
				MODIFY_BIT(g_Display_Data[0+4*col], LCD_COM_Row0_Value[36][0]);
			    MODIFY_BIT(g_Display_Data[1+4*col], LCD_COM_Row0_Value[36][1]);
			    MODIFY_BIT(g_Display_Data[2+4*col], LCD_COM_Row0_Value[36][2]);
			    MODIFY_BIT(g_Display_Data[3+4*col], LCD_COM_Row0_Value[36][3]);
				g_Display_Data[0+4*col] |= LCD_COM_Row0_Value[Value][0];
				g_Display_Data[1+4*col] |= LCD_COM_Row0_Value[Value][1];
				g_Display_Data[2+4*col] |= LCD_COM_Row0_Value[Value][2];
				g_Display_Data[3+4*col] |= LCD_COM_Row0_Value[Value][3];
			}
		}
	}

}


/**
  * @brief  дһ���� 4��
  * @param  unsigned char row:��(0-2)
  *		    u8 1 2 3 4
  * @retval None
  */
void HT_Write4Value(u8 row,u8 tmp1,u8 tmp2,u8 tmp3,u8 tmp4)
{
    HT_WriteValue(row,0,tmp1);
    HT_WriteValue(row,1,tmp2);
    HT_WriteValue(row,2,tmp3);
    HT_WriteValue(row,3,tmp4);
}

/**
  * @brief  д����С����
  * @param  unsigned char row:��(0-2)
  *			unsigned char col:��(0-4)
  * @retval None
  */
void HT_WriteDot(unsigned char row,unsigned char col,unsigned char Value)
{
	if (row == 0)
	{
		if (Value == CHAR_NONE)
		{
			if (col == 0)
			{
				MODIFY_BIT(g_Display_Data[33], LCD_COM_Row0_DotValue[col]);
			}
			else if(col == 1)
			{
				MODIFY_BIT(g_Display_Data[33], LCD_COM_Row0_DotValue[col]);
			}
			else if(col == 2)
			{
                MODIFY_BIT(g_Display_Data[31], LCD_COM_Row0_DotValue[col]);
			}
		}
		else
		{
			if (col == 0)
			{
				g_Display_Data[33] |= LCD_COM_Row0_DotValue[col];
			}
			else if(col == 1)
			{
				g_Display_Data[33] |= LCD_COM_Row0_DotValue[col];
			}
			else if(col == 2)
			{
				g_Display_Data[31] |= LCD_COM_Row0_DotValue[col];
			}
		}
	}
	else if (row == 1)
	{
		if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[53-4*col], LCD_COM_Row1_DotValue[col]);
		}
		else
		{
			g_Display_Data[53-4*col] |= LCD_COM_Row1_DotValue[col];
		}
	}
	else if (row == 2)
	{
		if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[52-4*col], LCD_COM_Row2_DotValue[col]);
		}
		else
		{
			g_Display_Data[52-4*col] |= LCD_COM_Row2_DotValue[col];
		}
	}
	else if (row == 4)
	{
		if (Value == CHAR_NONE)
		{
			MODIFY_BIT(g_Display_Data[68-2*col], LCD_COM_Row3_DotValue[col]);
		}
		else
		{
			g_Display_Data[68-2*col] |= LCD_COM_Row3_DotValue[col];
		}
	}
}

/**
  * @brief  д����
  * @param  unsigned char row:��(0-2)
  *
  * @retval None
  */
void HT_WriteColon(unsigned char index,unsigned char Value)
{
    if (Value == CHAR_NONE)
	{
		if (index == 0)
		{
			MODIFY_BIT(g_Display_Data[70], LCD_COM_Row_ColonValue[index]);
		}
		else if(index == 1)
		{
			MODIFY_BIT(g_Display_Data[70], LCD_COM_Row_ColonValue[index]);
		}
	}
	else
	{
		if (index == 0)
		{
			g_Display_Data[70] |= LCD_COM_Row_ColonValue[index];
		}
		else if(index == 1)
		{
			g_Display_Data[70] |= LCD_COM_Row_ColonValue[index];
		}
	}

}
/**
  * @brief  д����
  * @param  unsigned char row:��(0-2)
  *
  * @retval None
  */
void HT_WriteNegative(unsigned char row,unsigned char Value)
{
	if (Value == CHAR_NONE)
	{
	    MODIFY_BIT(g_Display_Data[LCD_PIN_NegaSign[row]], LCD_COM_NegaSign[row]);
	}
	else
	{
		g_Display_Data[LCD_PIN_NegaSign[row]] |= LCD_COM_NegaSign[row];
	}
}

/**
  * @brief  д��
  * @param  unsigned char row:��(3)
  *
  * @retval None
  */
void HT_WriteSum(unsigned char row,unsigned char Value)
{
	if (Value == CHAR_NONE)
	{
	    MODIFY_BIT(g_Display_Data[LCD_PIN_Sum[row]], LCD_COM_Sum[row]);
	}
	else
	{
		g_Display_Data[LCD_PIN_Sum[row]] |= LCD_COM_Sum[row];
	}
}

/**
  * @brief  д ʱ�� :
  * @param  unsigned char Row_Value:�ڼ���(0-2)
  * @retval None
  */
void HT_WriteTimeDot(BOOL bDisp, unsigned char Row_Value)
{
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_TimeDot[Row_Value][0]] |= LCD_COM_TimeDot[Row_Value][0];
		g_Display_Data[LCD_PIN_TimeDot[Row_Value][1]] |= LCD_COM_TimeDot[Row_Value][1];
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_TimeDot[Row_Value][0]], LCD_COM_TimeDot[Row_Value][0]);
		MODIFY_BIT(g_Display_Data[LCD_PIN_TimeDot[Row_Value][1]], LCD_COM_TimeDot[Row_Value][1]);
	}
}


/**
  * @brief  дS1 COS U(V) I(A) P(kW) Q(kvar) S(kVA) Freq(Hz) HU(%) IU(%) t
  * @param  unsigned char Norm_Value:0-9
  * @retval None
  */
void HT_WriteNorm(BOOL bDisp, unsigned char Norm_Value)
{
	u8 Index = 0;
	if (bDisp)
	{
		if (Norm_Value != DISP_NORM_S1) // ����ͨ�ű�־ ����ֻ����ͬʱ����һ��
		{
			for (Index = DISP_NORM_COS; Index <= DISP_NORM_T; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Index]], LCD_COM_Norm[Index]);
			}
		}
		g_Display_Data[LCD_PIN_Norm[Norm_Value]] |= LCD_COM_Norm[Norm_Value];
	}
	else
	{
		if (Norm_Value == DISP_NORM_NULL)
		{
			for (Index = DISP_NORM_COS; Index <= DISP_NORM_T; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Index]], LCD_COM_Norm[Index]);
			}
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Norm_Value]], LCD_COM_Norm[Norm_Value]);
		}
	}
	if (bDisp)
	{
		if (Norm_Value != DISP_NORM_S1) // ����ͨ�ű�־ ����ֻ����ͬʱ����һ��
		{
			for (Index = DISP_NORM_COS; Index <= DISP_NORM_T; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Index]], LCD_COM_Norm[Index]);
			}
		}
		g_Display_Data[LCD_PIN_Norm[Norm_Value]] |= LCD_COM_Norm[Norm_Value];
	}
	else
	{
		if (Norm_Value == DISP_NORM_NULL)
		{
			for (Index = DISP_NORM_COS; Index <= DISP_NORM_T; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Index]], LCD_COM_Norm[Index]);
			}
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Norm_Value]], LCD_COM_Norm[Norm_Value]);
		}
	}
}

void HT_WriteNorm_Delta(BOOL bDisp, unsigned char Norm_Value1, unsigned char Norm_Value2, unsigned char Norm_Value3)
{
	u8 Index = 0;
	if (bDisp)
	{
		if (Norm_Value1 != DISP_NORM_S1 && Norm_Value2 != DISP_NORM_S1 && Norm_Value3 != DISP_NORM_S1) // ����ͨ�ű�־ ����ֻ����ͬʱ����3��
		{
			for (Index = DISP_NORM_COS; Index <= DISP_NORM_T; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Index]], LCD_COM_Norm[Index]);
			}
		}
		if (Norm_Value1 != DISP_NORM_NULL)
		{
			g_Display_Data[LCD_PIN_Norm[Norm_Value1]] |= LCD_COM_Norm[Norm_Value1];
		}
		if (Norm_Value2 != DISP_NORM_NULL)
		{
			g_Display_Data[LCD_PIN_Norm[Norm_Value2]] |= LCD_COM_Norm[Norm_Value2];
		}
		if (Norm_Value3 != DISP_NORM_NULL)
		{
			g_Display_Data[LCD_PIN_Norm[Norm_Value3]] |= LCD_COM_Norm[Norm_Value3];
		}
	}
	else
	{
		if (Norm_Value1 == DISP_NORM_NULL && Norm_Value2 == DISP_NORM_NULL && Norm_Value3 == DISP_NORM_NULL)
		{
			for (Index = DISP_NORM_COS; Index <= DISP_NORM_T; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Index]], LCD_COM_Norm[Index]);
			}
		}
		else
		{
			if (Norm_Value1 != DISP_NORM_NULL)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Norm_Value1]], LCD_COM_Norm[Norm_Value1]);
			}
			if (Norm_Value2 != DISP_NORM_NULL)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Norm_Value2]], LCD_COM_Norm[Norm_Value2]);
			}
			if (Norm_Value3 != DISP_NORM_NULL)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Norm[Norm_Value3]], LCD_COM_Norm[Norm_Value3]);
			}
		}
	}
}

/**
  * @brief  дCT PT Ͷ����ʱ Ͷ������ �г�����  ��ѹ���� �������� г������ �¶ȱ���
  * @param  unsigned char Set_Value:0-8
  * @retval None
  */
void HT_WriteSet(BOOL bDisp, BOOL bOnlyOne, unsigned char Set_Value)
{
	u8 Index = 0;

	if (Set_Value == DISP_SET_ALL)
	{
		if (bDisp)
		{
			for (Index = DISP_SET_CT; Index < DISP_SET_ALL; Index++)
			{
				g_Display_Data[LCD_PIN_Set[Set_Value]] |= LCD_COM_Set[Set_Value];
			}
		}
		else
		{
			for (Index = DISP_SET_CT; Index < DISP_SET_ALL; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Set[Index]], LCD_COM_Set[Index]);
			}
		}
		return;
	}
	if (bDisp)
	{
		if (bOnlyOne)
		{
			for (Index = DISP_SET_CT; Index <= DISP_SET_TP; Index++)
			{
				if (Set_Value != Index)
				{
					MODIFY_BIT(g_Display_Data[LCD_PIN_Set[Index]], LCD_PIN_Set[Index]);

				}
				else
				{
					g_Display_Data[LCD_PIN_Set[Set_Value]] |= LCD_COM_Set[Set_Value];
				}
			}
		}
		else
		{
			g_Display_Data[LCD_PIN_Set[Set_Value]] |= LCD_COM_Set[Set_Value];
		}
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_Set[Set_Value]], LCD_COM_Set[Set_Value]);
	}
}

/**
  * @brief  дS3 S4 ��ƽ�� Ͷ�� �г�  ����ѹ  Ƿ��ѹ ������ Ƿ���� г��Խ�� ȱ��
  * @param  unsigned char Prt_Value:0-8
  * @retval None
  */
void HT_WritePrt(BOOL bDisp, unsigned char Prt_Value)
{
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_Prt[Prt_Value]] |= LCD_COM_Prt[Prt_Value];
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_Prt[Prt_Value]], LCD_COM_Prt[Prt_Value]);
	}
}

/**
  * @brief  дS15 S16 S17 S18 S19 S20
  * @param  unsigned char UIHL12_Value:0-8
  * @retval None
  */
void HT_WriteUIHL12(BOOL bDisp, BOOL Flag_U, BOOL Flag_I,
				BOOL Flag_H, BOOL Flag_L, BOOL Flag_1, BOOL Flag_2)
{
	if (bDisp)
	{
		if (Flag_U)
		{
			g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_U]] |= LCD_COM_UIHL12[DISP_UIHL12_U];
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_U]], LCD_COM_UIHL12[DISP_UIHL12_U]);
		}
		if (Flag_I)
		{
			g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_I]] |= LCD_COM_UIHL12[DISP_UIHL12_I];
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_I]], LCD_COM_UIHL12[DISP_UIHL12_I]);
		}
		if (Flag_H)
		{
			g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_H]] |= LCD_COM_UIHL12[DISP_UIHL12_H];
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_H]], LCD_COM_UIHL12[DISP_UIHL12_H]);
		}
		if (Flag_L)
		{
			g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_L]] |= LCD_COM_UIHL12[DISP_UIHL12_L];
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_L]], LCD_COM_UIHL12[DISP_UIHL12_L]);
		}
		if (Flag_1)
		{
			g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_1]] |= LCD_COM_UIHL12[DISP_UIHL12_1];
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_1]], LCD_COM_UIHL12[DISP_UIHL12_1]);
		}
		if (Flag_2)
		{
			g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_2]] |= LCD_COM_UIHL12[DISP_UIHL12_2];
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_2]], LCD_COM_UIHL12[DISP_UIHL12_2]);
		}
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_U]], LCD_COM_UIHL12[DISP_UIHL12_U]);
		MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_I]], LCD_COM_UIHL12[DISP_UIHL12_I]);
		MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_H]], LCD_COM_UIHL12[DISP_UIHL12_H]);
		MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_L]], LCD_COM_UIHL12[DISP_UIHL12_L]);
		MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_1]], LCD_COM_UIHL12[DISP_UIHL12_1]);
		MODIFY_BIT(g_Display_Data[LCD_PIN_UIHL12[DISP_UIHL12_2]], LCD_COM_UIHL12[DISP_UIHL12_2]);
	}
}

/**
  * @brief  дA�� B�� C��
  * @param  unsigned char Phase_Value:0-2
  * @retval None
  */
void HT_WritePhase(BOOL bDisp, unsigned char Phase_Value)       //��ʾA��B��C��
{
	u8 Index = 0;
	if (bDisp)
	{
        if (Phase_Value == PH_TH)       //��ʾ����
		{
			for (Index = PH_A; Index < PH_TH; Index++)
			{
				g_Display_Data[LCD_PIN_Phase[Index]] |= LCD_COM_Phase[Index];
			}
		}
		else                            //��ʾ��Ӧ����
		{
			g_Display_Data[LCD_PIN_Phase[Phase_Value]] |= LCD_COM_Phase[Phase_Value];
		}
	}
	else
	{
		if (Phase_Value == PH_TH)       //��ʾ����
		{
			for (Index = PH_A; Index < PH_TH; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_Phase[Index]], LCD_COM_Phase[Index]);
			}
		}
		else                            //��ʾ��Ӧ����
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_Phase[Phase_Value]], LCD_COM_Phase[Phase_Value]);
		}
	}
}

/**
  * @brief  дA�� B�� C��
  * @param  unsigned char Phase_Value:0-2
  * @retval None
  */
void HT_WritePhaseDouble(BOOL bDisp, unsigned char Phase_Value)       //��ʾA��B��C��
{
	u8 Index = 0;
	if (bDisp)
	{
		if (Phase_Value == PH_TH)       //��ʾ����
		{
			for (Index = PH_A; Index < PH_TH; Index++)
			{
				g_Display_Data[LCD_PIN_PhaseD[Index]] |= LCD_COM_PhaseD[Index];
			}
		}
		else                            //��ʾ��Ӧ����
		{
			g_Display_Data[LCD_PIN_PhaseD[Phase_Value]] |= LCD_COM_PhaseD[Phase_Value];
		}
	}
	else
	{
		if (Phase_Value == PH_TH)       //��ʾ����
		{
			for (Index = PH_A; Index < PH_TH; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_PhaseD[Index]], LCD_COM_PhaseD[Index]);
			}
		}
		else                            //��ʾ��Ӧ����
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_PhaseD[Phase_Value]], LCD_COM_PhaseD[Phase_Value]);
		}
	}
}

/**
  * @brief  д�Ҳ൥λ����
  * @param  unsigned char Phase_Value:0-2
  * @retval None
  */
void HT_WriteUnit(BOOL bDisp, u8 Phase_Value, u8 Disp_Unit)
{
	u8 Index = 0;
	if (bDisp)
	{
        if(Phase_Value > PH_TH)
        {
            for (Index = PH_A; Index < PH_TH; Index++)
			{
				g_Display_Data[LCD_PIN_UNIT3[Index]] |=  LCD_COM_UNIT3[Disp_Unit][Index];
			}
        }
		if (Phase_Value == PH_TH)       //��ʾ����
		{
			for (Index = PH_A; Index < PH_ALL; Index++)
			{
				g_Display_Data[LCD_PIN_UNIT0[Index]] |=  LCD_COM_UNIT0[Disp_Unit][Index];
				g_Display_Data[LCD_PIN_UNIT1[Index]] |=  LCD_COM_UNIT1[Disp_Unit][Index];
				g_Display_Data[LCD_PIN_UNIT2[Index]] |=  LCD_COM_UNIT2[Disp_Unit][Index];

			}
		}
		else                            //��ʾ��Ӧ����
		{
			switch(Phase_Value)
		    {
                case PH_A:
                    for (Index = PH_A; Index < PH_ALL; Index++)
        			{
        				g_Display_Data[LCD_PIN_UNIT0[Index]] |=  LCD_COM_UNIT0[Disp_Unit][Index];
        			}
                    break;
                case PH_B:
                    for (Index = PH_A; Index < PH_ALL; Index++)
        			{
        				g_Display_Data[LCD_PIN_UNIT1[Index]] |=  LCD_COM_UNIT1[Disp_Unit][Index];
        			}
                    break;
                case PH_C:
                    for (Index = PH_A; Index < PH_ALL; Index++)
        			{
        				g_Display_Data[LCD_PIN_UNIT2[Index]] |=  LCD_COM_UNIT2[Disp_Unit][Index];
        			}
        			break;
        	    default:
        	        break;
		    }
		}
	}
	else
	{
	    if(Phase_Value > PH_TH)
        {
            for (Index = PH_A; Index < PH_TH; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT3[Index]], LCD_COM_UNIT3[2][Index]);
			}
        }
		if (Phase_Value == PH_TH)       //!��ʾ����
		{
			for (Index = PH_A; Index < PH_ALL; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT0[Index]], LCD_COM_UNIT0[DISP_UNIT_NONE][Index]);
				MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT1[Index]], LCD_COM_UNIT1[DISP_UNIT_NONE][Index]);
				MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT2[Index]], LCD_COM_UNIT2[DISP_UNIT_NONE][Index]);
			}
		}
		else                            //!��ʾ��Ӧ����
		{
		    switch(Phase_Value)
		    {
                case PH_A:
                    for (Index = PH_A; Index < PH_ALL; Index++)
        			{
        				MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT0[Phase_Value]], LCD_COM_UNIT0[DISP_UNIT_NONE][Index]);
        			}
                    break;
                case PH_B:
                    for (Index = PH_A; Index < PH_ALL; Index++)
        			{
        				MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT1[Phase_Value]], LCD_COM_UNIT1[DISP_UNIT_NONE][Index]);
        			}
                    break;
                case PH_C:
                    for (Index = PH_A; Index < PH_ALL; Index++)
        			{
        				MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT2[Phase_Value]], LCD_COM_UNIT2[DISP_UNIT_NONE][Index]);
        			}
        			break;
        	    default:
        	        break;
		    }
		}
	}
}

/**
  * @brief  д���������
  * @param  unsigned char Phase_Value:0-2
  * @retval None
  */
void HT_Write_IO_Frame(BOOL bDisp)
{
    u8 i,j;
    g_Display_Data[13] |= 0x10;
    g_Display_Data[85] |= 0x20;
	if (bDisp)
	{
		for (i = 0; i < DIN_NUM; i++)
		{
			g_Display_Data[LCD_PIN_INS[i]] |= LCD_COM_INS[i];
		}
		for (j = 0; j < OUT_NUM; j++)
		{
			g_Display_Data[LCD_PIN_OUTS[j]] |= LCD_COM_OUTS[j];
		}
	}
	else
	{
		for (i = 0; i < DIN_NUM; i++)
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_INS[i]],LCD_COM_INS[i]);
		}
		for (j = 0; j < OUT_NUM; j++)
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_OUTS[j]],LCD_COM_OUTS[j]);
		}
	}
}

/**
  * @brief  д�����޿��
  * @param  unsigned char Phase_Value:0-2
  * @retval None
  */
void HT_Write_Four_Quadrant(BOOL bDisp)
{
    u8 i;
    g_Display_Data[83] |= 0x10;
	if (bDisp)
	{
        for (i = 0; i < 4; i++)
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_FourQ[i]],LCD_COM_FourQ[i]);
		}
		switch(FourQuadtand)
		{
            case 0:
                g_Display_Data[LCD_PIN_FourQ[1]] |= LCD_COM_FourQ[1];  // 1���� ����
                break;
            case 1:
                g_Display_Data[LCD_PIN_FourQ[0]] |= LCD_COM_FourQ[0];  // 2���� ����
                break;
            case 2:
                g_Display_Data[LCD_PIN_FourQ[3]] |= LCD_COM_FourQ[3];  // 3���� ����
                break;
            case 3:
                g_Display_Data[LCD_PIN_FourQ[2]] |= LCD_COM_FourQ[2];  // 4���� ����
                break;
            default:
                break;
		}
	}
	else
	{
		for (i = 0; i < 4; i++)
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_FourQ[i]],LCD_COM_FourQ[i]);
		}
	}
}


/**
  * @brief  д������״̬
  * @param  unsigned char Phase_Value:0-
  * @retval None
  * TRUE �պ�  FALSE ����
  */
void HT_Write_IO_Status(BOOL bDisp,u8 Kind,u8 Index)
{
	if (bDisp)
	{
	    if(Kind == 0x00)
	    {
	        MODIFY_BIT(g_Display_Data[LCD_PIN_IN_Off[Index]],LCD_COM_IN_Off[Index]);
    		g_Display_Data[LCD_PIN_IN_On[Index]] |= LCD_COM_IN_On[Index];
	    }
		else if(Kind == 0x01)
		{
		    MODIFY_BIT(g_Display_Data[LCD_PIN_OUT_Off[Index]],LCD_COM_OUT_Off[Index]);
    		g_Display_Data[LCD_PIN_OUT_On[Index]] |= LCD_COM_OUT_On[Index];
		}
	}
	else
	{
		if(Kind == 0x00)
	    {
	        MODIFY_BIT(g_Display_Data[LCD_PIN_IN_On[Index]],LCD_COM_IN_On[Index]);
    		g_Display_Data[LCD_PIN_IN_Off[Index]] |= LCD_COM_IN_Off[Index];
	    }
		else if(Kind == 0x01)
		{
		    MODIFY_BIT(g_Display_Data[LCD_PIN_OUT_On[Index]],LCD_COM_OUT_On[Index]);
    		g_Display_Data[LCD_PIN_OUT_Off[Index]] |= LCD_COM_OUT_Off[Index];
		}
	}
}

/**
  * @brief  ��������λ
  * @param  unsigned char Phase_Value:0-2
  * @retval None
  */
void HT_ClearLeftSign(BOOL bClear)
{
	u8 Index = 0;
	if (!bClear)
	{
		return;
	}
	else
	{
		for (Index = PH_A; Index < PH_ALL; Index++)
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_ClearLeft[Index]], LCD_COM_ClearLeft[Index]);
		}
	}
}

/**
  * @brief  ����Ҳ���λ
  * @param  unsigned char Phase_Value:0-2
  * @retval None
  */
void HT_ClearRightSign(BOOL bClear)
{
	u8 Index = 0;
	if (!bClear)
	{
		return;
	}
	else
	{
		for (Index = PH_A; Index < PH_ALL; Index++)
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT0[Index]], LCD_COM_UNIT0[DISP_UNIT_NONE][Index]);
			MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT1[Index]], LCD_COM_UNIT1[DISP_UNIT_NONE][Index]);
			MODIFY_BIT(g_Display_Data[LCD_PIN_UNIT2[Index]], LCD_COM_UNIT2[DISP_UNIT_NONE][Index]);
		}
	}
}

/*test*/
void HT_TEST(void)
{
   g_Display_Data[33] |= 0x80;
}
/**
  * @brief  дA�� B�� C��
  * @param  unsigned char LedPhase_Value:0-2
  * @retval None
  */
void HT_WriteLedPhase(BOOL bDisp, unsigned char LedPhase_Value)
{
	u8 Index = 0;
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_LedPhase[LedPhase_Value]] |= LCD_COM_LedPhase[LedPhase_Value];
	}
	else
	{
		if (LedPhase_Value == PH_TH)
		{
			for (Index = PH_A; Index < PH_TH; Index++)
			{
				MODIFY_BIT(g_Display_Data[LCD_PIN_LedPhase[Index]], LCD_COM_LedPhase[Index]);
			}
		}
		else
		{
			MODIFY_BIT(g_Display_Data[LCD_PIN_LedPhase[LedPhase_Value]], LCD_COM_LedPhase[LedPhase_Value]);
		}
	}
}

/**
  * @brief  д1-30�����
  * @param  unsigned char LedAddr_Value:0-29
  * @retval None
  */
void HT_WriteLedAddr(BOOL bDisp, unsigned char LedAddr_Value)
{
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_LedAddr[LedAddr_Value]] |= LCD_COM_LedAddr[LedAddr_Value];
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_LedAddr[LedAddr_Value]], LCD_COM_LedAddr[LedAddr_Value]);
	}
}

/**
  * @brief  д ���� �ֶ� �Զ� ���� ����
  * @param  unsigned char Ctrl_Value:0-4
  * @retval None
  */
void HT_WriteCtrl(BOOL bDisp, unsigned char Ctrl_Value)
{
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_Ctrl[Ctrl_Value]] |= LCD_COM_Ctrl[Ctrl_Value];
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_Ctrl[Ctrl_Value]], LCD_COM_Ctrl[Ctrl_Value]);
	}
}

/**
  * @brief  д ���� ����
  * @param  unsigned char Sys_Value:0-29
  * @retval None
  */
void HT_WriteSys(BOOL bDisp, unsigned char Phase_Value, unsigned char Sys_Value)
{
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_Sys[Phase_Value][Sys_Value]] |= LCD_COM_Sys[Phase_Value][Sys_Value];
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_Sys[Phase_Value][Sys_Value]], LCD_COM_Sys[Phase_Value][Sys_Value]);
	}
}

/**
  * @brief  д ����״ָ̬ʾ
  * @param  None
  * @retval None
  */
void HT_WriteCapStatus(BOOL bDisp)
{
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_CapStatus] |= LCD_COM_CapStatus;
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_CapStatus], LCD_COM_CapStatus);
	}
}

/**
  * @brief  д ���� ��� ������ ����
  * @param  unsigned char CapType_Value:0-4
  * @retval None
  */
void HT_WriteCapType(BOOL bDisp, unsigned char CapType_Value)
{
	if (bDisp)
	{
		g_Display_Data[LCD_PIN_CapType[CapType_Value]] |= LCD_COM_CapType[CapType_Value];
	}
	else
	{
		MODIFY_BIT(g_Display_Data[LCD_PIN_CapType[CapType_Value]], LCD_COM_CapType[CapType_Value]);
	}
}

/**
  * @brief  ÿ�������ʾ
  * @param  unsigned char Com_Value:0x10,0x20,0x40,0x80,
  *			unsigned char Pin_Value:0-83
  * @retval None
  */
void HT_WriteEveryComPin(BOOL bDisp, unsigned char Com_Value, unsigned char Pin_Value)
{
	if (bDisp)
	{
		g_Display_Data[Pin_Value] |= Com_Value;
	}
	else
	{
		MODIFY_BIT(g_Display_Data[Pin_Value], Com_Value);
	}
}

/**
  * @brief  ����Ļ ����ʾ�κ���Ϣ
  * @param  None
  * @retval None
  */
/**********************************************************************
 * �� �� ��: Clear_Screen
 * ��������: ȫ�Բ�����û�л��ֶ�
 * ��    ��: ��
 * ��    ��: ��
 ***********************************************************************/
void Clear_Screen(void)
{
	int i = 0;
	for (i = 0; i < DISPNUM; i++)
	{
		g_Display_Data[i] = 0xff;
		sg_Display_Data_Back[i] = 0x00;
	}
}

/**
  * @brief  ������Ļ��ʾ��Ϣ
  * @param  None
  * @retval None
  */
void Lcd_Update_screen(void)
{
	int i = 0;
	nus_delay(10);
	LCD_CS_L;
	nus_delay(10);

	for (i = 0; i < DISPNUM>>1; i++)
	{
		if (sg_Display_Data_Back[2*i] != g_Display_Data[2*i])
		{
			HT_WriteData(i*4,g_Display_Data[2*i]);
		}
		if (sg_Display_Data_Back[2*i+1] != g_Display_Data[2*i+1])
		{
			HT_WriteData(i*4+2,g_Display_Data[2*i+1]);
		}
		sg_Display_Data_Back[2*i] = g_Display_Data[2*i];
		sg_Display_Data_Back[2*i+1] = g_Display_Data[2*i+1];
	}
	LCD_CS_H;
	LCD_CS_H;
}

/**
  * @brief  ������Ļ��ʾ��Ϣ(ȫ�� or ȫ��)
  * @param  None
  * @retval None
  */
void LCD_Update_screen_T(BOOL Flag)
{
	int i = 0;

	if (Flag)
	{
		for (i = 0; i < DISPNUM>>1; i++)
		{
			HT_WriteData(i*4,0xff);
			HT_WriteData(i*4+2,0xff);
		}
	}
	else
	{
		for (i = 0; i < DISPNUM>>1; i++)
		{
			HT_WriteData(i*4,0);
			HT_WriteData(i*4+2,0);
		}
	}
//	PT_TimerDelay(10);
}

/**
  * @brief  ����Ļ ����ʾ�κ���Ϣ
  * @param  None
  * @retval None
  */
/**********************************************************************
 * �� �� ��: Clear_Screen
 * ��������: ȫ�Բ�����û�л��ֶ�
 * ��    ��: ��
 * ��    ��: ��
 ***********************************************************************/
void Reset_Screen(void)
{
	int i = 0;
	for (i = 0; i < DISPNUM; i++)
	{
		g_Display_Data[i] = 0x00;
		sg_Display_Data_Back[i] = 0xff;
	}
}
/*
void Test_LCDValue(void)
{
	int i = 0;
	int j = 0;
	HT_WriteValue(0, 0, 0);
	Update_screen();
	HT_WriteValue(0, 0, 1);
	Update_screen();
	HT_WriteValue(0, 0, 2);
	Update_screen();
	HT_WriteValue(0, 0, 3);
	Update_screen();
	HT_WriteValue(0, 0, 4);
	Update_screen();
	HT_WriteValue(0, 0, 5);
	Update_screen();
	HT_WriteValue(0, 0, 6);
	Update_screen();
	HT_WriteValue(0, 0, 7);
	Update_screen();
	HT_WriteValue(0, 0, 8);
	Update_screen();
	HT_WriteValue(0, 0, 9);
	Update_screen();
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 4; j++)

		{
			HT_WriteValue(0, j, i);
			Update_screen();
			HT_WriteDot(0, j, CHAR_NONE);
			Update_screen();
			HT_WriteDot(0, j, CHAR_DOT);
			Update_screen();
			HT_WriteValue(1, j, i);
			Update_screen();
			HT_WriteDot(1, j, CHAR_NONE);
			Update_screen();
			HT_WriteDot(1, j, CHAR_DOT);
			Update_screen();
			HT_WriteValue(2, j, i);
			Update_screen();
			HT_WriteDot(2, j, CHAR_NONE);
			Update_screen();
			HT_WriteDot(2, j, CHAR_DOT);
			Update_screen();
		}
	}
//		for (i = 0; i < 380; i++)
//		{
//			HT_WriteData(i,0);
//		}
//		for (i = 0; i < 48; i++)
//		{
//			HT_WriteData(i*4,0x00);
//			HT_WriteData(i*4+2,0x00);
//		}
//		for (i = 0; i < 48; i++)
//		{
//
//			HT_WriteData(i*4,0x10);
//			HT_WriteData(i*4,0x20);
//			HT_WriteData(i*4,0x40);
//			HT_WriteData(i*4,0x80);
//			HT_WriteData(i*4,0x00);
//			HT_WriteData(i*4+2,0x10);
//			HT_WriteData(i*4+2,0x20);
//			HT_WriteData(i*4+2,0x40);
//			HT_WriteData(i*4+2,0x80);
//			HT_WriteData(i*4+2,0x00);
//		}
}

void Test_LCDLED(void)
{
	int i = 0;
	for (i = 0; i < MAX_STAR_CAP_NUM; i++)
	{
		HT_WriteCapLED(CAPTYPE_STAR, i, PH_A, FHKG_OFFTOON);
		Update_screen();
		HT_WriteCapLED(CAPTYPE_STAR, i, PH_A, FHKG_ONTOOFF);
		Update_screen();
	}
	for (i = 0; i < MAX_STAR_CAP_NUM; i++)
	{
		HT_WriteCapLED(CAPTYPE_STAR, i, PH_B, FHKG_OFFTOON);
		Update_screen();
		HT_WriteCapLED(CAPTYPE_STAR, i, PH_B, FHKG_ONTOOFF);
		Update_screen();
	}
	for (i = 0; i < MAX_STAR_CAP_NUM; i++)
	{
		HT_WriteCapLED(CAPTYPE_STAR, i, PH_C, FHKG_OFFTOON);
		Update_screen();
		HT_WriteCapLED(CAPTYPE_STAR, i, PH_C, FHKG_ONTOOFF);
		Update_screen();
	}
	for (i = 0; i < MAX_DELTA_CAP_NUM-10; i++)
	{
		HT_WriteCapLED(CAPTYPE_DELTA, i, PH_A, FHKG_OFFTOON);
		Update_screen();
		HT_WriteCapLED(CAPTYPE_DELTA, i, PH_A, FHKG_ONTOOFF);
		Update_screen();
	}
	for (i = 0; i < MAX_DELTA_CAP_NUM-10; i++)
	{
		HT_WriteCapLED(CAPTYPE_DELTA, i, PH_C, FHKG_OFFTOON);
		Update_screen();
		HT_WriteCapLED(CAPTYPE_DELTA, i, PH_C, FHKG_ONTOOFF);
		Update_screen();
	}
}

void Test_LCDNorm(void)
{
	int i = 0;
	for (i = DISP_NORM_S1; i <= DISP_NORM_T; i++)
	{
		HT_WriteNorm(TRUE, i);
		Update_screen();
		HT_WriteNorm(FALSE, i);
		Update_screen();
	}
}

void Test_LCDSet(void)
{
	int i = 0;
	for (i = DISP_SET_CT; i <= DISP_SET_TP; i++)
	{
		HT_WriteSet(TRUE, TRUE, i);
		Update_screen();
		HT_WriteSet(FALSE, TRUE, i);
		Update_screen();
	}
}

void Test_LCDPrt(void)
{
	int i = 0;
	for (i = DISP_PRT_TEMP; i <= DISP_PRT_LP; i++)
	{
		HT_WritePrt(TRUE, i);
		Update_screen();
		HT_WritePrt(FALSE, i);
		Update_screen();
	}
}

void Test_LCDUIHL12(void)
{
//		int i = 0;
//		for (i = DISP_UIHL12_U; i <= DISP_UIHL12_2; i++)
//		{
//			HT_WriteUIHL12(TRUE, i);
//			Update_screen();
//			HT_WriteUIHL12(FALSE, i);
//			Update_screen();
//		}
}

void Test_LCDPhase(void)
{
	int i = 0;
	for (i = PH_A; i <= PH_C; i++)
	{
		HT_WritePhase(TRUE, i);
		Update_screen();
		HT_WritePhase(FALSE, i);
		Update_screen();
	}
}

void Test_LCDLedPhase(void)
{
	int i = 0;
	for (i = PH_A; i <= PH_C; i++)
	{
		HT_WriteLedPhase(TRUE, i);
		Update_screen();
		HT_WriteLedPhase(FALSE, i);
		Update_screen();
	}
}

void Test_LCDLedAddr(void)
{
	int i = 0;
	for (i = 0; i < MAX_DELTA_CAP_NUM; i++)
	{
		HT_WriteLedAddr(TRUE, i);
		Update_screen();
		HT_WriteLedAddr(FALSE, i);
		Update_screen();
	}
}

void Test_LCDCtrl(void)
{
	int i = 0;
	for (i = DISP_CTRL_SET; i <= DISP_CTRL_TEST; i++)
	{
		HT_WriteCtrl(TRUE, i);
		Update_screen();
		HT_WriteCtrl(FALSE, i);
		Update_screen();
	}
}

void Test_LCDSys(void)
{
	int i = 0;
	for (i = DISP_SYS_INDUCTOR; i <= DISP_SYS_CAP; i++)
	{
		HT_WriteSys(TRUE, PH_A, i);
		Update_screen();
		HT_WriteSys(FALSE, PH_A, i);
		Update_screen();
		HT_WriteSys(TRUE, PH_B, i);
		Update_screen();
		HT_WriteSys(FALSE, PH_B, i);
		Update_screen();
		HT_WriteSys(TRUE, PH_C, i);
		Update_screen();
		HT_WriteSys(FALSE, PH_C, i);
		Update_screen();
	}
}

void Test_LCDCapStatus(void)
{
	HT_WriteCapStatus(TRUE);
	Update_screen();
	HT_WriteCapStatus(FALSE);
	Update_screen();
}

void Test_LCDTimeDot(void)
{
	HT_WriteTimeDot(TRUE, 0);
	Update_screen();
	HT_WriteTimeDot(FALSE, 0);
	Update_screen();
	HT_WriteTimeDot(TRUE, 1);
	Update_screen();
	HT_WriteTimeDot(FALSE, 1);
	Update_screen();
	HT_WriteTimeDot(TRUE, 2);
	Update_screen();
	HT_WriteTimeDot(FALSE, 2);
	Update_screen();
}

void Test_LCDCapType(void)
{
	int i = 0;
	for (i = DISP_CAPTYPE_ID; i <= DISP_CAPTYPE_STAR; i++)
	{
		HT_WriteCapType(TRUE, i);
		Update_screen();
		HT_WriteCapType(FALSE, i);
		Update_screen();
	}
}

void Test_LCDEveryComPin(void)
{
	int com_Value = 0;
	int pin_Value = 0;
	unsigned char Value[] = {0x10,0x20,0x40,0x80};

	for (com_Value = 0; com_Value <= 3; com_Value++)
	{
		for (pin_Value = 0; pin_Value <= 83; pin_Value++)
		{
			HT_WriteEveryComPin(TRUE, Value[com_Value],pin_Value);
			Update_screen();
			HT_WriteEveryComPin(FALSE, Value[com_Value],pin_Value);
			Update_screen();
		}
	}
}
*/
#endif // #ifdef _GUILCD_



