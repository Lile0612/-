/*! @file
********************************************************************************
<PRE>
ģ����       : ����ģ��
�ļ���       : taskProtect.c
����ļ�     :
�ļ�ʵ�ֹ��� : �޹�����
����         : <--->
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2010/10/05   1.0    <xxxx>         ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Include.h"
/* Private typedef -----------------------------------------------------------*/

BOOL g_OverCurr[PH_TH] = {FALSE,FALSE,FALSE};

/*------------------------------------------------------------------------
* �ṹ���� : tagKGProtectStateStruct
* ��    �� : �����жϹ���״̬����
------------------------------------------------------------------------*/
typedef struct tagKGProtectStateStruct
{
    BOOL HappenDelayEnable;     // �Ƿ�������ʱ
    BOOL RtnDelayEnable;        // ���α�������,����������ʱ
    BOOL HappenSure;            // ȷ����������
    BOOL SwitchSure;            // ȷ���г�
    u32 DelayTickWhen;          // ��ʱʱ��
} KGProtectStateStruct;



enum emADProtect   //
{
    ADJUSTVOL_A_CUR = 0, // ��������

    ADJUSTVOL_B_CUR = 1, // ��������

    ADJUSTVOL_C_CUR = 2, // ��������

    ADJUSTVOL_MAX = 3,

};

// ����״̬����
KGProtectStateStruct g_KGProtectState[ADJUSTVOL_MAX];

// ---------------------- definitions ------------------------------

#define RATIO_ADJUST_I	10000 // ����������ֵ����

// ȡ���ж�
void KG_CancelJudge(KGProtectStateStruct *pKGProtectState)
{
    pKGProtectState->HappenDelayEnable = FALSE;
    pKGProtectState->RtnDelayEnable = FALSE;
    pKGProtectState->HappenSure = FALSE;
    pKGProtectState->SwitchSure = FALSE;
    pKGProtectState->DelayTickWhen = 0;
}

// �ж�
void KG_ProtectHappen(KGProtectStateStruct *pKGProtectState, u32 wActTime)
{
    if (pKGProtectState->HappenDelayEnable == FALSE)
    {
        pKGProtectState->HappenDelayEnable = TRUE;
        pKGProtectState->RtnDelayEnable = FALSE;
        pKGProtectState->SwitchSure = FALSE;
        pKGProtectState->DelayTickWhen = PT_TimerGet();
    }
    else
    {
        if (PT_TimerDiff(pKGProtectState->DelayTickWhen) > wActTime)
        {
            pKGProtectState->HappenDelayEnable = FALSE;
            pKGProtectState->RtnDelayEnable = FALSE;
            pKGProtectState->HappenSure = TRUE;
            pKGProtectState->SwitchSure = TRUE;
            pKGProtectState->DelayTickWhen = 0;
        }
    }
}

void KG_ProtectRtn(KGProtectStateStruct *pKGProtectState, u32 RtnTime)
{
    if (pKGProtectState->RtnDelayEnable == FALSE)   // û��ȷ��
    {
        pKGProtectState->HappenDelayEnable = FALSE;
        pKGProtectState->RtnDelayEnable = TRUE;
        pKGProtectState->SwitchSure = FALSE;
        pKGProtectState->DelayTickWhen = PT_TimerGet();
    }
    else
    {
        if (PT_TimerDiff(pKGProtectState->DelayTickWhen) > RtnTime)
        {
            KG_CancelJudge(pKGProtectState);
        }
    }
}

BOOL KG_JudgeOverHappen(u32 OverProteVal, u32 BackLashVal, u32 RealVal, enum emADProtect AdjustType, u32 HappenDlyTime, u32 CancelDlyTime)
{
    if (OverProteVal == 0)
    {
        KG_CancelJudge(&g_KGProtectState[AdjustType]);
        return FALSE;
    }
    if (OverProteVal <= RealVal)
    {
        KG_ProtectHappen(&g_KGProtectState[AdjustType], HappenDlyTime);
    }
    else
    {
        if ((OverProteVal - BackLashVal) >= RealVal)   // ����ȡ������
        {
            // �����Ѿ�ȷ������
            if (g_KGProtectState[AdjustType].HappenSure == TRUE)
            {
                KG_ProtectRtn(&g_KGProtectState[AdjustType], CancelDlyTime);
            }
            else
            {
                KG_CancelJudge(&g_KGProtectState[AdjustType]);
            }
        }
        else     // ���ڷ����ͷ���֮��,����������ʱ����
        {
            // �����Ѿ�ȷ������
            if (g_KGProtectState[AdjustType].HappenSure == TRUE)
            {
                KG_ProtectHappen(&g_KGProtectState[AdjustType], HappenDlyTime);
            }
        }
    }
    return g_KGProtectState[AdjustType].HappenSure;
}


void Protect_AutoProc(void)
{


    u32 BackCur = 0;
    u32 OverCur_Value1 = 0;
    //static union AdjustVolState_Reg s_OldAdjustVolState[PH_TH];
    float fCalcCur;

    // �жϹ���1
    fCalcCur = (float)g_tParam.CtrlParam.Alarm / 100* 5 * g_tParam.CtrlParam.CTNum; // ������β���� 120
    fCalcCur *= RATIO_ADJUST_I; // ת����mA
    OverCur_Value1 = (float)fCalcCur; // ���α�ʾ
    BackCur = (fCalcCur * 0.1); // ����ֵ������ֵ��0.9������  120A

    KG_JudgeOverHappen(OverCur_Value1, BackCur, vg_Power_Val.Real2_Val[PH_A].I, ADJUSTVOL_A_CUR, 10000, 10000);

    KG_JudgeOverHappen(OverCur_Value1, BackCur, vg_Power_Val.Real2_Val[PH_B].I, ADJUSTVOL_B_CUR, 10000, 10000); //60000 60S

    KG_JudgeOverHappen(OverCur_Value1, BackCur, vg_Power_Val.Real2_Val[PH_C].I, ADJUSTVOL_C_CUR, 10000, 10000);

    // ������׼ȷ��������״̬������
    if (vg_Power_Val.Real2_Val[PH_A].U < 1000 || vg_Power_Val.Real2_Val[PH_B].U < 1000 || vg_Power_Val.Real2_Val[PH_C].U < 1000)
    {
        return;
    }

    // ����
    if (g_KGProtectState[ADJUSTVOL_A_CUR].SwitchSure)
    {
        g_OverCurr[PH_A] = TRUE;
    }
    if (g_KGProtectState[ADJUSTVOL_B_CUR].SwitchSure)
    {
        g_OverCurr[PH_B] = TRUE;
    }
    if (g_KGProtectState[ADJUSTVOL_C_CUR].SwitchSure)
    {
        g_OverCurr[PH_C] = TRUE;
    }
    // ����
    if (!g_KGProtectState[ADJUSTVOL_A_CUR].HappenSure)
    {
        g_OverCurr[PH_A] = FALSE;
    }
    if (!g_KGProtectState[ADJUSTVOL_B_CUR].HappenSure)
    {
        g_OverCurr[PH_B] = FALSE;
    }
    if (!g_KGProtectState[ADJUSTVOL_C_CUR].HappenSure)
    {
        g_OverCurr[PH_C] = FALSE;
    }


/***********************************************************************************************************/
/***********************************************************************************************************/
}

void Task_Protect_Function(void)
{
    Protect_AutoProc();
}

