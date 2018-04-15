/*! @file
********************************************************************************
<PRE>
ģ �� ��     : ������ PD354-L9S
�� �� ��     : sysMain.c
����ļ�      :
�ļ�ʵ�ֹ��� :
����         : < 612 >
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         : ���Ա�
--------------------------------------------------------------------------------
�޸ļ�¼ :
  �� ��        �汾      �޸���         �޸�����
2018/02/01   1.0    < 612 >        ����
2018/03/17   1.1    < 612 >      LED��ʾ���������������
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxxx>, ��������Ȩ��

*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "Include.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

void App_Init(void)
{

}

/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
	debug();
#endif

  	Bsp_Init();
    PT_TimerDelay(50);
	Task_GUI_init();
	PT_TimerDelay(500);
	LoadParam();//��Flash ϵͳ��ʼ����־λ.
    FRAM_ReadData();
	bsp_InitRN8023();
    USART_Configuration();
#ifdef _GUILCD_
    LCD_BG_H;
#endif
    SCH_Init_T();

    // ��������
	SCH_Add_Task(Task_RS232_Function, 0, TASK_IDLE_PROTOCOL);		// 485����
	SCH_Add_Task(Task_Power_Function, 500, TASK_IDLE_RNUpData);	// ����ˢ��
	SCH_Add_Task(Task_Protect_Function, 1000, TASK_IDLE_SVC);	// �����澯
	SCH_Add_Task(Task_Extra_Function, 200,TASK_IDLE_EXTRA);
	SCH_Add_Task(Task_GUI_Function, 500, TASK_IDLE_GUI);		// GUI

	// ��ʼ����
	SCH_Start();
	while(1)
	{
		SCH_RUN_Tasks();
	}
}

