/*
*********************************************************************************************************
*
*	ģ������ : Ӧ�ó������ģ��
*	�ļ����� : param.c
*	��     �� : V1.0
*	˵     �� : ��ȡ�ͱ���Ӧ�ó���Ĳ���
*	�޸ļ�¼ :
*	            �汾��      ����            ����        ˵��
*	            V1.0    2017-10-27       l��     ��ʽ����
*
*	Copyright (C), 2015-2020   www.yidek.com
*
*********************************************************************************************************
*/

/* Includes ------------------------------------------------------------------*/

#include "Include.h"

/* Public variables ---------------------------------------------------------*/

float RtuPrimaryData[36];       // һ�β�����
u16 RtuPrimaryDataTmp[72];      // һ�β�����ת��
s16 RtuSecondaryData[192];      // ���β�����
s16 RtuTHDData[102];            // г������
s16 RtuCTRLData[64];            // ���ò���
s16 RtuCTRLDataTemp[64];        // ���ò���
s16 RtuOUTData[4];              // �̵���״̬
s16 RtuINData[4];               // ������״̬

Energy_Memory ElectricEnergy;
PARAM_T g_tParam;
SX_PARAM DispCtrlParam;
u8 FourQuadtand;
u8 IbEnbleFlag = FALSE;
/* Private functions ---------------------------------------------------------*/

/*
*********************************************************************************************************
*	�� �� ��: InitCtrlParam
*	����˵��: ���Ʋ�����ʼ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void InitCtrlParam(void)
{
    g_tParam.CtrlParam.INIT = 0x55; //��ʼ����ʶλ
    g_tParam.CtrlParam.Code = 1;
    g_tParam.CtrlParam.NetMode = N34;
    g_tParam.CtrlParam.PTNum = 1;
    g_tParam.CtrlParam.CTNum = 1;
    g_tParam.CtrlParam.Addr485 = 0x01;
    g_tParam.CtrlParam.Baud485 = Baud48;
    g_tParam.CtrlParam.DataFormat = n81;
    g_tParam.CtrlParam.DataProtocol = calib;
    g_tParam.CtrlParam.Cycle = SaveNO;
#ifdef _GUILCD_
    g_tParam.CtrlParam.BlackTime = 60;
#else
    g_tParam.CtrlParam.BlackTime = BrightLevel_1;
#endif
    g_tParam.CtrlParam.Alarm = 120;
    g_tParam.CtrlParam.DefaultDisp = DISP_UINT_U;

    g_tParam.CtrlParam.DO1_Mode = DO_MODE_OFF;
    g_tParam.CtrlParam.DO1_Item = DO_ITEM_Ua_H;
    g_tParam.CtrlParam.DO1_Time = 0;
    g_tParam.CtrlParam.DO1_UAL = 0;
    g_tParam.CtrlParam.DO1_HYS = 0;
    g_tParam.CtrlParam.DO1_Delay = 0;

    g_tParam.CtrlParam.DO2_Mode = DO_MODE_OFF;
    g_tParam.CtrlParam.DO2_Item = DO_ITEM_Ua_H;
    g_tParam.CtrlParam.DO2_Time = 0;
    g_tParam.CtrlParam.DO2_UAL = 0;
    g_tParam.CtrlParam.DO2_HYS = 0;
    g_tParam.CtrlParam.DO2_Delay = 0;

    g_tParam.CtrlParam.DO3_Mode = DO_MODE_OFF;
    g_tParam.CtrlParam.DO3_Item = DO_ITEM_Ua_H;
    g_tParam.CtrlParam.DO3_Time = 0;
    g_tParam.CtrlParam.DO3_UAL = 0;
    g_tParam.CtrlParam.DO3_HYS = 0;
    g_tParam.CtrlParam.DO3_Delay = 0;

    g_tParam.CtrlParam.DO4_Mode = DO_MODE_OFF;
    g_tParam.CtrlParam.DO4_Item = DO_ITEM_Ua_H;
    g_tParam.CtrlParam.DO4_Time = 0;
    g_tParam.CtrlParam.DO4_UAL = 0;
    g_tParam.CtrlParam.DO4_HYS = 0;
    g_tParam.CtrlParam.DO4_Delay = 0;

    g_tParam.CtrlParam.AO1_Mode = AO_MODE_OFF;
    g_tParam.CtrlParam.AO1_Item = AO_ITEM_UA;
    g_tParam.CtrlParam.AO1_DS = 0;
    g_tParam.CtrlParam.AO1_FS = 0;

    g_tParam.CtrlParam.AO2_Mode = AO_MODE_OFF;
    g_tParam.CtrlParam.AO2_Item = AO_ITEM_UA;
    g_tParam.CtrlParam.AO2_DS = 0;
    g_tParam.CtrlParam.AO2_FS = 0;

    g_tParam.CtrlParam.AdjustFinishFlag = FALSE;
    g_tParam.CtrlParam.AnaCalibFlag = FALSE;
}

void InitRNParam_Phase(u8 Phase) //�����ʼ��
{
    g_tParam.RN_Coefficients.HFConst1 = RNPARAM_HFCONST1;

    if (Phase < 3)
    {
        g_tParam.RN_Coefficients.GSU[Phase] = 0x2000;// 10210;
        g_tParam.RN_Coefficients.GSI[Phase] = 0xC000;// 49152;
        g_tParam.RN_Coefficients.PHSI[Phase] = 0x808080;// 65505;
        g_tParam.RN_Coefficients.P_PHSL[Phase] = 0x00;
        g_tParam.RN_Coefficients.P_PHSM[Phase] = 0x00;
        g_tParam.RN_Coefficients.P_PHSH[Phase] = 0x00;
    }
}

void InitRNParam_PhaseToZero(u8 Phase)
{
    g_tParam.RN_Coefficients.HFConst1 = 0x1000;

    if (Phase < 3)
    {
        g_tParam.RN_Coefficients.GSU[Phase] = 0;// 10210;
        g_tParam.RN_Coefficients.GSI[Phase] = 0;// 59652;
        g_tParam.RN_Coefficients.PHSI[Phase] = 0x808080;// 65505;  //����Ĭ��ֵ
        g_tParam.RN_Coefficients.P_PHSL[Phase] = 0x00;
        g_tParam.RN_Coefficients.P_PHSM[Phase] = 0x00;
        g_tParam.RN_Coefficients.P_PHSH[Phase] = 0x00;
    }
}

void InitRNParam(void) //�����ʼ��
{
    int ph;

    for (ph = 0; ph < 3; ph++)
    {
        InitRNParam_Phase(ph);
    }
}

void InitRNParamToZero(void)
{
    int ph;
    for (ph = 0; ph < 3; ph++)
    {
        InitRNParam_PhaseToZero(ph);
    }
}
void WriteRNParam(u8 *pWriteData) //У׼������ʽת��
{
    g_tParam.RN_Coefficients.HFConst1 = FLIPDW(pWriteData);

    g_tParam.RN_Coefficients.GSU[0] = FLIPDW(pWriteData+4);
    g_tParam.RN_Coefficients.GSI[0] = FLIPDW(pWriteData+8);
    g_tParam.RN_Coefficients.PHSI[0] = FLIPDW(pWriteData+12);

    g_tParam.RN_Coefficients.GSU[1] = FLIPDW(pWriteData+16);
    g_tParam.RN_Coefficients.GSI[1] = FLIPDW(pWriteData+20);
    g_tParam.RN_Coefficients.PHSI[1] = FLIPDW(pWriteData+24);

    g_tParam.RN_Coefficients.GSU[2] = FLIPDW(pWriteData+28);
    g_tParam.RN_Coefficients.GSI[2] = FLIPDW(pWriteData+32);
    g_tParam.RN_Coefficients.PHSI[2] = FLIPDW(pWriteData+36);
}



/*
*********************************************************************************************************
*	�� �� ��: LoadParam
*	����˵��: ��Flash��������g_tParam
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void LoadParam(void)
{

#ifdef PARAM_SAVE_TO_FLASH
	/* ��ȡCPU Flash�еĲ��� */
    MemData_ReadParam();
#endif

#ifdef PARAM_SAVE_TO_EEPROM
	/* ��ȡEEPROM�еĲ��� */
	ee_ReadBytes((uint8_t *)&g_tParam, PARAM_ADDR, sizeof(PARAM_T));
#endif

}

/*
*********************************************************************************************************
*	�� �� ��: SaveParam
*	����˵��: ��ȫ�ֱ���g_tParam д�뵽CPU�ڲ�Flash
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void SaveParam(void)
{
#ifdef PARAM_SAVE_TO_FLASH
	/* ��ȫ�ֵĲ����������浽 CPU Flash */
	MemData_WriteParam();
#endif

#ifdef PARAM_SAVE_TO_EEPROM
	/* ��ȫ�ֵĲ����������浽EEPROM */
	ee_WriteBytes((uint8_t *)&g_tParam, PARAM_ADDR, sizeof(PARAM_T));
#endif
}


