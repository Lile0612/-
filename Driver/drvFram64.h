/*! @file
********************************************************************************
<PRE>
ģ �� ��     : �����ȡд�����MB85RC64��
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
// ���ܼ�¼���·���
#define FRAM_Energy_SIZE	            591    // ���ֵ�������� 31*19+2��У��λ��

#define FRAM_JanuEnergy_sADDR      (0x00000436)      // 1�¼�¼��ַ
#define FRAM_FebrEnergy_sADDR      (0x00000686)      // 2�¼�¼��ַ
#define FRAM_MarcEnergy_sADDR      (0x000008D6)      // 3�¼�¼��ַ
#define FRAM_ApriEnergy_sADDR      (0x00000B26)      // 4�¼�¼��ַ
#define FRAM_MayyEnergy_sADDR      (0x00000D76)      // 5�¼�¼��ַ
#define FRAM_JuneEnergy_sADDR      (0x0FC6)      // 6�¼�¼��ַ
#define FRAM_JulyEnergy_sADDR      (0x00001216)      // 7�¼�¼��ַ
#define FRAM_AuguEnergy_sADDR      (0x00001466)      // 8�¼�¼��ַ
#define FRAM_SeptEnergy_sADDR      (0x000016B6)      // 9�¼�¼��ַ
#define FRAM_OctoEnergy_sADDR      (0x00001906)      // 10�¼�¼��ַ
#define FRAM_NoveEnergy_sADDR      (0x00001B56)      // 11�¼�¼��ַ
#define FRAM_DeceEnergy_sADDR      (0x00001DA6)      // 12�¼�¼��ַ



void MyI2C_Start(void);
void MyI2C_Stop(void);
u8   MyI2C_SendByte(u8 ByteData);
u8   MyI2C_ReceiveByte(u8 last_char);

void FRAM_WriteData(void);
void FRAM_RecordWrite(void);
void FRAM_IndexWrite(void);
void FRAM_DoRecordWrite(void);
void FRAM_MaxDemWrite(void);
void FRAM_EnergyRecordWrite(void);
void FRAM_EnergyRecordSeek(u8 RefKind,u8 RefMonth);
u8 FRAM_I2C_ReadData(u16 phyAddr, u8 *pReadData, u16 Length);
u16 FramEnergy_Crc(u8 *pData);


void FramInit(void);

//void FRAM_Erase_Sector(u16 Addr, u16 Num);
//void FRAM_Erase_Chip(void);

#endif /* _DRVFRAM_H */

//===========================================================================
// No more.
//===========================================================================

