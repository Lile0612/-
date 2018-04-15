
#define __PT_TIMER_C__
#include "Include.h"

__IO u32 TTimer_ticks=0;

void PT_TimerIncrement(void)
{
    TTimer_ticks++;
}

u32 PT_TimerGet()
{
	u32 temp = TTimer_ticks;
	return temp;
}

u8 PT_TimerExpired(TTimer *this)
{
	return ((u32)(PT_TimerGet() -(u32) this->start) >= (u32)this->interval);
}

void PT_TimerSet(TTimer *this,u32 interval)
{
	this->interval = interval; this->start = PT_TimerGet();
}

// �ж�����ϵͳʱ��
u32 PT_TimerDiff(u32 TimeWhen)
{
	u32 TimeCur = PT_TimerGet();
	if (TimeCur >= TimeWhen)
	{
		return (TimeCur - TimeWhen);
	}
	else
	{
		return (U32_MAX - TimeCur + TimeWhen);
	}
}

void nus_delay(unsigned int num)
{
	u32 i,j;
#ifndef IWDG_DEBUG
	u32 k;
#endif
	for (i=0;i<num;i++)
	{
#ifdef  IWDG_DEBUG
		for (j=0;j<2;j++);
#else
		for (j=0;j<8;j++) {k++;};
#endif
	}
}

//��ȷ��ʱ���� ms��ʱ����,1msΪһ����λ
void PT_TimerDelay(u32 Timer_Count)
{
    u32 TimeCur = PT_TimerGet();
    while(PT_TimerDiff(TimeCur) < Timer_Count)	//��ʱ
    {
		__nop();
    }
}


