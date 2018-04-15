/*! @file
********************************************************************************
<PRE>
ģ����       : ���ӹ���
�ļ���       : taskExtra.h
����ļ�     :
�ļ�ʵ�ֹ��� : DI DO AO
����         : <--->
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2017/10/28   1.0    <lile>           ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/

#include "Macro.h"

#ifndef _TASKEXTRA_H
#define _TASKEXTRA_H

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#define DIN_NUM					0x04 // ��������������
#define OUT_NUM					0x04 // �������������
//////////////////////////////////////////////////////////////////////////
// ����Ϊ����
__packed struct  AdjustVolState_Bit {   // bit  description
    // ����״̬
    u32 Un_H:1;         // 0    ���ѹ����
    u32 Un_L:1;         // 1    ���ѹ����
    u32 UL_H:1;         // 2    �ߵ�ѹ����
    u32 UL_L:1;         // 3    �ߵ�ѹ����
    u32 I_H:1;          // 4    ��������
    u32 I_L:1;          // 5    ��������
    u32 I0_H:1;         // 6    ���ߵ�������
    u32 I0_L:1;         // 7    ���ߵ�������
    u32 P_H:1;          // 8    �й�����
    u32 P_L:1;          // 9    �й�����
    u32 Q_H:1;          // 10   �޹�����
    u32 Q_L:1;          // 11   �޹�����
    u32 S_H:1;          // 12   ��������
    u32 S_L:1;          // 13   ��������
    u32 PF_H:1;         // 14   ������������
    u32 PF_L:1;         // 15   ������������
    u32 F_H:1;          // 16   Ƶ������
    u32 F_L:1;          // 17   Ƶ������
    u32 UTH_H:1;        // 18   ��ѹг������
    u32 UTH_L:1;        // 19   ��ѹг������
    u32 ITH_H:1;        // 20   ����г������
    u32 ITH_L:1;        // 21   ����г������
    u32 Align32:10;      // ������

};

__packed union AdjustVolState_Reg
{
    u32               all;
    struct  AdjustVolState_Bit  Bit;
};

// ���ܵ���������
__packed typedef struct {
    u8 SVC_ActStatus[3];               // 3Cap
    u8 Signal_Status;                   // �ź�״̬
    union AdjustVolState_Reg AdjustVolState;
}Device_DataStruct;

typedef enum
{
	Dout_ONE = 0,
	Dout_TWO = 1,
	Dout_THREE = 2,
	Dout_FOUR = 3,
}emDoutNum;


extern u8 Out_Rem_Enble[3];
extern u8 DinStatus_Disp;
extern u8 OutStatus_Disp;
extern BOOL g_Out_Status[OUT_NUM];
extern u8 RemOutCtrl;
extern u8 g_Din_Status[DIN_NUM];
extern u8 g_Din_BIT[DIN_NUM];




void Task_Extra_Function(void);







#endif /* _TASKEXTRA_H */

//===========================================================================
// No more.
//===========================================================================

