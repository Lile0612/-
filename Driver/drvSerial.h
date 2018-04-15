/*! @file
********************************************************************************
<PRE>
ģ����       : Ӳ������ģ��
�ļ���       : drvSerial.h
����ļ�     :
�ļ�ʵ�ֹ��� : ��������
����         : <---->
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2010/10/15   1.0    <---->         ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/

#ifndef _DRVSERIAL_H
#define _DRVSERIAL_H

/* Private typedef -----------------------------------------------------------*/
typedef enum { FAILED = 0, PASSED = !FAILED} STATUS;
typedef enum {COM_STATUS_LENERR = 0, COM_STATUS_OK}COM_STATUS;
/* Private define ------------------------------------------------------------*/
// ��������
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
#define USART_RX_BUF_MAX	128	/*������2����*/
#define USART_RX_BUF_MARK	(USART_RX_BUF_MAX-1)

#define USART_TX_BUF_MAX	128	/*������2����*/
#define USART_TX_BUF_MARK	(USART_TX_BUF_MAX-1)

extern volatile u8 vu8_sending;
extern unsigned char uart1_delay_ok;
extern unsigned char uart1_delay_number;
/* Public variables ---------------------------------------------------------*/

bool USART_IsDataInRxBuf(void);
u32 USART_GetRxBufLen(void);

COM_STATUS USART_GetRxString(u8 *pData, u16 len);
COM_STATUS USART_PutTxString(u8 *pData, u16 len);
void SERIAL_IRQHandler(void);

#endif/* _DRVSERIAL_H */

//===========================================================================
// No more.
//===========================================================================




