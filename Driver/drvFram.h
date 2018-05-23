/*! @file
********************************************************************************
<PRE>
ģ �� ��     : �����ȡд�����MB85RC16/04��
�� �� ��     : drvFram.h
����ļ�      :
�ļ�ʵ�ֹ��� :
����         : < 612 >
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         : ���Ա�
--------------------------------------------------------------------------------
�޸ļ�¼ :
  �� ��        �汾      �޸���         �޸�����
2018/05/22   1.0    < 612 >        ����

</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxxx>, ��������Ȩ��

*******************************************************************************/

#ifndef _DRVFRAM_H
#define _DRVFRAM_H

/* Includes ------------------------------------------------------------------*/
//#include "TimerDef.h"

/* Exported types ------------------------------------------------------------*/
#define IIC_ERR_NONE			0
#define IIC_ERR_NO_ACK			1
/* Exported constants --------------------------------------------------------*/
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
/* Exported macro ------------------------------------------------------------*/

void FRAM_WriteData(void);
void FRAM_ReadData(void);
void FRAM_RecordWrite(void);
void FRAM_RecordRead(void);
void FRAM_IndexWrite(void);
void FRAM_IndexRead(void);
void FRAM_DoRecordWrite(void);
void FRAM_DoRecordRead(void);
void FRAM_MaxDemWrite(void);
void FRAM_MaxDemRead(void);

void MyI2C_Start(void);
void MyI2C_Stop(void);
u8   MyI2C_SendByte(u8 ByteData);
u8   MyI2C_ReceiveByte(u8 last_char);

//void FRAM_Erase_Sector(u16 Addr, u16 Num);
//void FRAM_Erase_Chip(void);

#endif /* _DRVFRAM_H */

//===========================================================================
// No more.
//===========================================================================

