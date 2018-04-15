/*! @file
********************************************************************************
<PRE>
ģ����       : Ӳ������
�ļ���       : stm32f10x_target.h
����ļ�     :
�ļ�ʵ�ֹ��� : Ӳ����ʼ��
����         : <xxx>
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2009/09/15   1.0    <xxx>         ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __bsp_H
#define __bsp_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

void Bsp_Init (void);
//void TIM3_Configuration(void);
void EXTI_Configuration(void);
void RCC_Configuration(void);
void USART_Configuration(void);
void ADC_Configuration(void);
void SysTick_Configuration(void);
void NVIC_Configuration(void);
void USART_DMAReConfig(u8* pDataBuf, u16 BufSize);
void TIM14_Configuration(FunctionalState State);
void TIM_PWM_Configuration(void);

#ifdef __cplusplus
}
#endif

#endif /* __bsp */


//===========================================================================
// No more.
//===========================================================================


