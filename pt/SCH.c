/*! @file
********************************************************************************
<PRE>
ģ����       : �������ں˺���
�ļ���       : SCH.c
����ļ�     :
�ļ�ʵ�ֹ��� : �������
����         : <l��>
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         : ������
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2017/03/22   1.0    <l��>           ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Include.h"

/*----------------------------------------------------------------------------*/

sTask SCH_tasks_G[SCH_MAX_TASKS];   //�������������

void SCH_Init_T(void)
{
	u8 i;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	for (i = 0; i < SCH_MAX_TASKS; i++)
    {
        SCH_Delete_Task(i);				//ɾ������Ҫ������
    }
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = 3999;       //��ʱ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 11;       //ʱ�ӷ�Ƶ�� ��ʱ1ms
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;    //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

void SCH_Start(void)
{
	/* TIM enable counter */
	TIM_Cmd(TIM3, ENABLE);

	/* TIM IT enable */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

u16 g_IWDGCount = 0; //ι������
void SIGNAL_IRQHandler(void)
{
    u8 Index;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		for ( Index = 0;  Index < SCH_MAX_TASKS;  Index++ )
		{
			if (SCH_tasks_G[Index].pTask)
			{
				if (SCH_tasks_G[Index].Delay == 0)
				{
					SCH_tasks_G[Index].RunMe += 1;

					if (SCH_tasks_G[Index].Period)
					{
						SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
					}
				}
				else
				{
					SCH_tasks_G[Index].Delay -= 1;
				}
			}
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update );
		g_IWDGCount++;
		if (g_IWDGCount>=120)
		{
			//IWDG_ReloadCounter(); //�ֶ�ι��
			g_IWDGCount = 0;
		}
	}
}

void SCH_RUN_Tasks(void)  //����ִ��
 {
   u8 Index;

   for (Index = 0; Index < SCH_MAX_TASKS; Index++)
   {
      if (SCH_tasks_G[Index].RunMe > 0)
      {
         (*SCH_tasks_G[Index].pTask)();

         SCH_tasks_G[Index].RunMe -= 1;

         if (SCH_tasks_G[Index].Period == 0)
         {
            SCH_Delete_Task(Index);
         }
      }
   }
}

u8 SCH_Add_Task(void (*pFunction)(void),  //���1�
                    u16 DELAY,
                    u16 PERIOD)
{
   u8 Index = 0;

   while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
   {
      Index++;
   }

   if (Index == SCH_MAX_TASKS)
   {
      return SCH_MAX_TASKS;
    }

   SCH_tasks_G[Index].pTask  = pFunction;
   SCH_tasks_G[Index].Delay  = DELAY;
   SCH_tasks_G[Index].Period = PERIOD;
   SCH_tasks_G[Index].RunMe  = 0;

   return Index;
}

u8 SCH_Delete_Task( u8 TASK_INDEX)        //ɾ��
{
   SCH_tasks_G[TASK_INDEX].pTask   = 0x0000;
   SCH_tasks_G[TASK_INDEX].Delay   = 0;
   SCH_tasks_G[TASK_INDEX].Period  = 0;
   SCH_tasks_G[TASK_INDEX].RunMe   = 0;

   return 0;
}

