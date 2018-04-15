#ifndef _SCH_H_
#define _SCH_H_

#include "Macro.h"

#define RETURN_NORMAL             0
#define RETURN_ERROR              1

#define TASK_IDLE_GUI           40  //��ʾ
#define TASK_IDLE_EXTRA         100 //���ӹ���
#define TASK_IDLE_PROTOCOL      20  //�жϴ��ڽ��ս���
#define TASK_IDLE_RNUpData      200 //��ȡ����
#define TASK_IDLE_Handle        500 //У��
#define TASK_IDLE_SVC           100 //����

// ������֧�ֵ��������,�û��ڵ��õ�������ʱ���������
#define SCH_MAX_TASKS             6
typedef struct data
{
   void (*pTask)(void);
   s16 Delay;
   u16 Period;
   u8 RunMe;
} sTask;

// �������ں�
// ���ļ����к���
//*****************************************************
void SCH_Init_T(void);
void SCH_Start(void);
// ���������ⲿ�ӿ�
void SIGNAL_IRQHandler(void);
void SCH_RUN_Tasks(void);
u8 SCH_Add_Task(void (*pFunction)(void), u16 DELAY, u16 PERIOD);
u8 SCH_Delete_Task(u8 TASK_INDEX);

#endif /* _SCH_H */

//===========================================================================
// No more.
//===========================================================================



