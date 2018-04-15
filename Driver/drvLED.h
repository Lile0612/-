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

#ifndef _DRVLED_H
#define _DRVLED_H

/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
#define LED_BYTES       5

/* Exported constants --------------------------------------------------------*/
/*      a          b g d e a h f c
     f     b
        g
     e     c
        d    h                        */
/* Exported macro ------------------------------------------------------------*/
enum emCHARMODE_INDEX
{
	CHARMODE_0	= 0xbb,/*0*/
	CHARMODE_1  = 0x81,/*1*/
	CHARMODE_2	= 0xf8,/*2*/
	CHARMODE_3	= 0xd9,/*3*/
	CHARMODE_4	= 0xc3,/*4*/
	CHARMODE_5	= 0x5b,/*5*/
	CHARMODE_6  = 0x7b,/*6*/
	CHARMODE_7	= 0x89,/*7*/
	CHARMODE_8	= 0xfb,/*8*/
	CHARMODE_9	= 0xdb,/*9*/
	CHARMODE_A	= 0xeb,/*A*/
	CHARMODE_B  = 0x73,/*b*/
	CHARMODE_C	= 0x3a,/*C*/
	CHARMODE_D	= 0xf1,/*d*/
	CHARMODE_E	= 0x7a,/*E*/
	CHARMODE_F	= 0x6a,/*F*/
	CHARMODE_G  = CHARMODE_6, //
	CHARMODE_H	= 0xe3,/*H*/
	CHARMODE_h	= 0x63,/*H*/
	CHARMODE_I	= CHARMODE_1,/*I*/
	CHARMODE_J  = 0x91,/*J*/
	CHARMODE_L	= 0x32,/*L*/
	CHARMODE_N	= 0x61,/*n*/
	CHARMODE_M	= 0x69,/*m*/
	CHARMODE_O	= 0x71,/*O*/
	CHARMODE_P  = 0xea,/*P*/
	CHARMODE_Q	= 0xcb,/*q*/
	CHARMODE_R  = 0x60,/*r*/
	CHARMODE_S	= CHARMODE_5,/*S*/
	CHARMODE_T	= 0x72,/*T*/
	CHARMODE_U  = 0xb3,/*U*/
	CHARMODE_Y  = 0xd3,/*Y*/
	CHARMODE_FU = 0x40,/*-*/
	CHARMODE_DOT   = 0x04,
	CHARMODE_ZHENG = CHARMODE_0,
	CHARMODE_ALL   = 0xFF,
	CHARMODE_NC    = 0x00,

	CHARMODE_Dv    = 0x10,
    CHARMODE_Dw    = 0x04,
    CHARMODE_De    = 0x01,
    CHARMODE_Davr  = 0x40,

    CHARMODE_Di    = 0x10,
    CHARMODE_Dvar  = 0x04,
    CHARMODE_Dpf   = 0x01,
    CHARMODE_Dkwh  = 0x40,

    CHARMODE_Dhz    = 0x10,
    CHARMODE_Dva    = 0x04,
    CHARMODE_Dalm   = 0x01,
    CHARMODE_Dkvarh = 0x40,

    CHARMODE_DK    = 0x02,
    CHARMODE_DM    = 0x08,

    CHARMODE_F1    = 0x40,
    CHARMODE_F2    = 0x40,
    CHARMODE_F3    = 0x40,
};

extern const u8 cg_DispCharacter[];
typedef union Union_ByteDef
{
    struct
    {
        unsigned char b0:1;
        unsigned char b1:1;
        unsigned char b2:1;
        unsigned char b3:1;
        unsigned char b4:1;
        unsigned char b5:1;
        unsigned char b6:1;
        unsigned char b7:1;
    }BIT;
    unsigned char BYTE;
}UNION_BYTE;
/* Exported functions ------------------------------------------------------- */

void Update_screen(void);
void Clear_Screen(void);
void TM1640_delay(void);
u8 HT_Data_Index(unsigned char data);


#endif /* _DRVLED_H */

//===========================================================================
// No more.
//===========================================================================


