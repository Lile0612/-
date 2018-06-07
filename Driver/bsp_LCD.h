/*! @file
********************************************************************************
<PRE>
ģ����       : ����ģ��
�ļ���       : drvLED.h
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

#ifndef _DRVLCD_H
#define _DRVLCD_H

/* Includes ------------------------------------------------------------------*/
#include "Macro.h"

/* Exported types ------------------------------------------------------------*/

#define LCD_DIS_STAR_NUM        10
#define LCD_DIS_DELTA_NUM       30
#define IN_STATUS_NUM           6
#define OUT_STATUS_NUM          3
/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

// ��3��
#define CHAR_0		0x00
#define CHAR_1		0x01
#define CHAR_2		0x02
#define CHAR_3		0x03
#define CHAR_4		0x04
#define CHAR_5		0x05
#define CHAR_6		0x06
#define CHAR_7		0x07
#define CHAR_8		0x08
#define CHAR_9		0x09
#define CHAR_C	    0x0A
#define CHAR_d	    0x0B
#define CHAR_E		0x0C
#define CHAR_F		0x0D
#define CHAR_H		0x0E
#define CHAR_n		0x0F
#define CHAR_P		0x10
#define CHAR_q		0x11
#define CHAR_S		0x12
#define CHAR_t		0x13
#define CHAR_FU     0x14
#define CHAR_V      0x15
#define CHAR_O		0x16
#define CHAR_L		0x17
#define CHAR_U		0x18
#define CHAR_R		0x19
#define CHAR_NUM	CHAR_R//��������ֵ
#define CHAR_DOT	0x10
#define CHAR_NONE	0xFF

enum emLCD_DISP_8_VALUE
{
	DISP_0 = 0x00,
	DISP_1 = 0x01,
	DISP_2 = 0x02,
	DISP_3 = 0x03,
	DISP_4 = 0x04,
	DISP_5 = 0x05,
	DISP_6 = 0x06,
	DISP_7 = 0x07,
	DISP_8 = 0x08,
	DISP_9 = 0x09,
	DISP_a = 0x0A,
	DISP_b = 0x0B,
	DISP_C = 0x0C,
	DISP_d = 0x0D,
	DISP_E = 0x0E,
	DISP_F = 0x0F,
	DISP_G = 0x10,
	DISP_H = 0x11,
	DISP_I = 0x12,
	DISP_L = 0x13,
    DISP_m = 0x14,
	DISP_n = 0x15,
	DISP_o = 0x16,
	DISP_p = 0x17,
	DISP_q = 0x18,
	DISP_r = 0x19,
	DISP_s = 0x1A,
	DISP_t = 0x1B,
	DISP_U = 0x1C,
	DISP_Y = 0x1D,
	DISP_FU = 0x1E,
	DISP_NC = 0x1F,
	DISP_ALL = 0x20,
};

enum emLCD_DISP_16_VALUE
{
	DISP1_0 = 0x00,
	DISP1_1 = 0x01,
	DISP1_2 = 0x02,
	DISP1_3 = 0x03,
	DISP1_4 = 0x04,
	DISP1_5 = 0x05,
	DISP1_6 = 0x06,
	DISP1_7 = 0x07,
	DISP1_8 = 0x08,
	DISP1_9 = 0x09,
	DISP1_A = 0x0A,
	DISP1_b = 0x0B,
	DISP1_C = 0x0C,
	DISP1_d = 0x0D,
	DISP1_E = 0x0E,
	DISP1_F = 0x0F,
	DISP1_G = 0x10,
	DISP1_H = 0x11,
	DISP1_I = 0x12,
	DISP1_J = 0x13,
	DISP1_K = 0x14,
	DISP1_L = 0x15,
	DISP1_M = 0x16,
	DISP1_n = 0x17,
	DISP1_o = 0x18,
	DISP1_p = 0x19,
	DISP1_q = 0x1A,
	DISP1_r = 0x1B,
	DISP1_s = 0x1C,
	DISP1_T = 0x1D,
	DISP1_U = 0x1E,
	DISP1_Y = 0x1F,
	DISP1_Z = 0x20,
	DISP1_ZHENG = 0x21,
	DISP1_FU = 0x22,
	DISP1_NC = 0x23,
	DISP1_ALL = 0x24,
};

// ��ʾ��λ
// w kw mw kmw var kvar mvar kmvar va kva mva kmva v kv mv A kA mA oxff
enum EMLCD_DISP_UNIT
{
    DISP_UNIT_w     = 0,
    DISP_UNIT_kw    = 1,
    DISP_UNIT_mw    = 2,
    DISP_UNIT_kmw   = 3,
    DISP_UNIT_var   = 4,
    DISP_UNIT_kvar  = 5,
    DISP_UNIT_mvar  = 6,
    DISP_UNIT_kmvar = 7,
    DISP_UNIT_VA    = 8,
    DISP_UNIT_kVA   = 9,
    DISP_UNIT_mVA   = 10,
    DISP_UNIT_kmVA  = 11,
    DISP_UNIT_V     = 12,
    DISP_UNIT_kV    = 13,
    DISP_UNIT_mV    = 14,
    DISP_UNIT_A     = 15,
    DISP_UNIT_kA    = 16,
    DISP_UNIT_mA    = 17,
    DISP_UNIT_PerV  = 18,
    DISP_UNIT_PerA  = 19,
    DISP_UNIT_NONE  = 20,
};

// S1 COS U(V) I(A) P(kW) Q(kvar) S(kVA) Freq(Hz) HU(%) IU(%) t
enum EMLCD_DISP_NORM
{
	DISP_NORM_S1 = 0,
	DISP_NORM_COS = 1,
	DISP_NORM_UV = 2,
	DISP_NORM_IA = 3,
	DISP_NORM_PKW = 4,
	DISP_NORM_QKVAR = 5,
	DISP_NORM_SKVA = 6,
	DISP_NORM_FREQ = 7,
	DISP_NORM_HU = 8,
	DISP_NORM_IU = 9,
	DISP_NORM_T = 10,
	DISP_NORM_NULL = 11,
};
// CT PT Ͷ����ʱ Ͷ������ �г�����  ��ѹ���� �������� г������ �¶ȱ���
enum EMLCD_DISP_SET
{
	DISP_SET_CT = 0,
	DISP_SET_PT = 1,
	DISP_SET_DLY = 2,
	DISP_SET_ONPF = 3,
	DISP_SET_OFFPF = 4,
	DISP_SET_UP = 5,
	DISP_SET_IP = 6,
	DISP_SET_HP = 7,
	DISP_SET_TP = 8,
	DISP_SET_ALL = 9,
};
// S3 S4 ��ƽ�� Ͷ�� �г�  ����ѹ  Ƿ��ѹ ������ Ƿ���� г��Խ�� ȱ��
enum EMLCD_DISP_PRT
{
	DISP_PRT_TEMP = 0,
	DISP_PRT_S4 = 1,
	DISP_PRT_IMB = 2,
	DISP_PRT_ON = 3,
	DISP_PRT_OFF = 4,
	DISP_PRT_OU = 5,
	DISP_PRT_LU = 6,
	DISP_PRT_OI = 7,
	DISP_PRT_LI = 8,
	DISP_PRT_OH = 9,
	DISP_PRT_LP = 10,
};
// S15 S16 S17 S18 S19 S20
enum EMLCD_DISP_UIHL12
{
	DISP_UIHL12_U = 0,
	DISP_UIHL12_I = 1,
	DISP_UIHL12_H = 2,
	DISP_UIHL12_L = 3,
	DISP_UIHL12_1 = 4,
	DISP_UIHL12_2 = 5,
};
// ���� �ֶ� �Զ� ���� ����
enum EMLCD_DISP_CTRL
{
	DISP_CTRL_SET = 0,
	DISP_CTRL_MANUAL = 1,
	DISP_CTRL_AUTO = 2,
	DISP_CTRL_LOCK = 3,
	DISP_CTRL_TEST = 4,
};
// ���� ����
enum EMLCD_DISP_SYS
{
	DISP_SYS_INDUCTOR = 0,
	DISP_SYS_CAP = 1,
};
// ���� ��� ������ ����
enum EMLCD_DISP_CAPTYPE
{
	DISP_CAPTYPE_ID = 0,
	DISP_CAPTYPE_INDEX = 1,
	DISP_CAPTYPE_DELTA = 2,
	DISP_CAPTYPE_STAR = 3,
};

enum emLCD_DISP_Max
{
	IndexMax = 0x00,
	IndexMin = 0x01,
	IndexAvg = 0x02,
	IndexCom = 0x03,
	IndexWarm = 0x04,
};

enum emLCD_DISP_Rexord
{
	IndexS_jian = 0x00,
	IndexS_feng = 0x01,
	IndexS_ping = 0x02,
	IndexS_gu1 = 0x03,
	IndexS_ji = 0x04,
	IndexS_gu2 = 0x05,
	IndexS_shang1 = 0x06,
	IndexS_shang2 = 0x07,
	IndexS_yue = 0x08,
};


/* Exported functions ------------------------------------------------------- */
u8 HT_Data_Index(unsigned char data);
void HT_LedStatus(BOOL bStatus);
void HT_TouchStatus(BOOL bStatus);
void HT_Init(void);
void HT_WriteValue(unsigned char row,unsigned char col,unsigned char Value);
void HT_Write4Value(u8 row,u8 tmp1,u8 tmp2,u8 tmp3,u8 tmp4);
void HT_WriteDot(unsigned char row,unsigned char col,unsigned char Value);
void HT_WriteColon(unsigned char index,unsigned char Value);
void HT_WriteMax(unsigned char index,unsigned char Value);
void HT_TEST(void);
void HT_WriteNegative(unsigned char row,unsigned char Value);
void HT_WriteTimeDot(BOOL bDisp, unsigned char Row_Value);
void HT_WriteCapLED(unsigned char CapType,unsigned char Addr,unsigned char Phase,unsigned char SwitchType);
void HT_WriteNorm(BOOL bDisp, unsigned char Norm_Value);
void HT_WriteNorm_Delta(BOOL bDisp, unsigned char Norm_Value1, unsigned char Norm_Value2, unsigned char Norm_Value3);
void HT_WriteSet(BOOL bDisp, BOOL bOnlyOne, unsigned char Set_Value);
void HT_WritePrt(BOOL bDisp, unsigned char Prt_Value);
//void HT_WriteUIHL12(BOOL bDisp, unsigned char UIHL12_Value);
void HT_WriteUIHL12(BOOL bDisp, BOOL Flag_U, BOOL Flag_I,
				BOOL Flag_H, BOOL Flag_L, BOOL Flag_1, BOOL Flag_2);
void HT_WritePhase(BOOL bDisp, unsigned char Phase_Value);
void HT_WritePhaseDouble(BOOL bDisp, unsigned char Phase_Value);       //��ʾA��B��C��
void HT_WriteUnit(BOOL bDisp, u8 Phase_Value, u8 Disp_Unit);
void HT_WriteSum(unsigned char row,unsigned char Value);
void HT_Write_IO_Frame(BOOL bDisp);
void HT_Write_IO_Status(BOOL bDisp,u8 Kind,u8 Index);
void HT_Write_Four_Quadrant(BOOL bDisp);
void HT_ClearLeftSign(BOOL bClear);
void HT_ClearRightSign(BOOL bClear);
void HT_WriteRecordSign(unsigned char index,unsigned char Value);


void HT_WriteEveryComPin(BOOL bDisp, unsigned char Com_Value, unsigned char Pin_Value);
void Lcd_Update_screen(void);
void LCD_Update_screen_T(BOOL Flag);
void Clear_Screen(void);
void Reset_Screen(void);


#endif /* _DRVLCD_H */

#endif /* _GUILCD_ */

//===========================================================================
// No more.
//===========================================================================


