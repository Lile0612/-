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

/* Private macro -------------------------------------------------------------*/
#define FRAM_SIZE 2048
#define FRAM_SECTOR_SIZE 32
#define FRAM_R 1
#define FRAM_W 0

// Addr:8λ�豸�� 16λ��ַ��
#define FRAM_MSBADDRESS(Addr) ((Addr & 0xFF00) >> 8)
#define FRAM_LSBADDRESS(Addr) (Addr & 0xFF)
/********************************************************/
// ��ַ����
#define FRAM_STARTADDR       (0x00000000) 
#define FRAM_DATA_SIZE	              32     // ����������

#define FRAM_Index_ADDR      (0x00000020)    // Di  ��ǩ
#define FRAM_INDEX_SIZE	              10     // ���������� ��ǩҳ

#define FRAM_RECORD_SIZE	               484     // ����������       0x01E4  
#define FRAM_RECORD_ADDR         (0x00000030)      // DI ��¼ֵ��ַ SP:0x0000 0214
#define FRAM_DO_RECORD_ADDR      (0x00000216)      // DO ��¼ֵ��ַ SP:     0x0000 03FA

#define FRAM_MaxDem_SIZE                  292      // ���ֵ�������� 0x0124
#define FRAM_MaxDem_ADDR         (0x00000400)      // ���ֵ��¼��ַ SP:0x0000 0524

/* Exported macro ------------------------------------------------------------*/
// ���ܼ�¼���·���
#define FRAM_Energy_SIZE	            624    // ���ֵ�������� 31*20+2��У��λ��

#define FRAM_FebrEnergy_sADDR      (0x0000052A)      // 2�¼�¼��ַ
#define FRAM_MarcEnergy_sADDR      (0x0000079A)      // 3�¼�¼��ַ
#define FRAM_ApriEnergy_sADDR      (0x00000A0A)      // 4�¼�¼��ַ
#define FRAM_MayyEnergy_sADDR      (0x00000C7A)      // 5�¼�¼��ַ
#define FRAM_JuneEnergy_sADDR      (0x00000EEA)      // 6�¼�¼��ַ
#define FRAM_JulyEnergy_sADDR      (0x0000115A)      // 7�¼�¼��ַ
#define FRAM_AuguEnergy_sADDR      (0x000013CA)      // 8�¼�¼��ַ
#define FRAM_SeptEnergy_sADDR      (0x0000163A)      // 9�¼�¼��ַ
#define FRAM_OctoEnergy_sADDR      (0x000018AA)      // 10�¼�¼��ַ
#define FRAM_NoveEnergy_sADDR      (0x00001B1A)      // 11�¼�¼��ַ
#define FRAM_DeceEnergy_sADDR      (0x00001D8A)      // 12�¼�¼��ַ



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

