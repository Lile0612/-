/* Includes ------------------------------------------------------------------*/
#include "Include.h"

/* Public variables ---------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

volatile BOOL vg_sysInitFlag = FALSE; // ϵͳ������־

/* Private functions ---------------------------------------------------------*/

BOOL MemData_Write_To_Flash(u32 Addr, u8 *pInData, u16 Count)  //Flash д��
{
    u16 Counter = 0;
    u32 dwRegRealAddress = Addr;
    BOOL MemoryProgramStatus = TRUE;

    if (Count <= FLASH_PARAM_SIZE)
    {
        FLASH_Unlock();

        FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR );

        FLASH_ErasePage(dwRegRealAddress);

        for (Counter = 0; Counter < FLASH_PARAM_SIZE / 4; Counter++)
        {
            if (FLASH_ProgramWord(dwRegRealAddress, *(vu32*) (pInData+Counter*4)) == FLASH_COMPLETE) // д���
            {
                if((*(vu32*) dwRegRealAddress) != *(vu32*)(pInData+Counter*4)) // ���ݼ��
                {
                    MemoryProgramStatus = FALSE;
                    break;
                }
                dwRegRealAddress += 4;
            }
            else
            {
                MemoryProgramStatus = FALSE;
                break;
            }
        }
        FLASH_Lock();

        return MemoryProgramStatus;
    }
    else
    {
        return FALSE;
    }
}

BOOL MemEnergy_Write_To_Flash(u32 Addr, u8 *pInData, u16 Count)  //Flash д��
{
    u16 Counter = 0;
    u32 dwRegRealAddress = Addr;
    BOOL MemoryProgramStatus = TRUE;

    if (Count <= MEM_Energy_SIZE)
    {
        FLASH_Unlock();

        FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR );

        FLASH_ErasePage(dwRegRealAddress);

        for (Counter = 0; Counter < MEM_Energy_SIZE / 4; Counter++)
        {
            if (FLASH_ProgramWord(dwRegRealAddress, *(vu32*) (pInData+Counter*4)) == FLASH_COMPLETE) // д���
            {
                if((*(vu32*) dwRegRealAddress) != *(vu32*)(pInData+Counter*4)) // ���ݼ��
                {
                    MemoryProgramStatus = FALSE;
                    break;
                }
                dwRegRealAddress += 4;
            }
            else
            {
                MemoryProgramStatus = FALSE;
                break;
            }
        }
        FLASH_Lock();

        return MemoryProgramStatus;
    }
    else
    {
        return FALSE;
    }
}


void MemData_WriteCalib(u8 *pScrData, u16 Count)
{
	MemData_Write_To_Flash(CALIB_STARTADDR, pScrData, Count);
}

void MemData_ReadCalib(u8 *pDstData, u16 Count)
{
	memcpy(pDstData, (u8 *)CALIB_STARTADDR, Count);
}

bool MemData_CmpParamType(PARAM_T *pSettingParam)
{
    if( pSettingParam->CtrlParam.NetMode > MAX_NetMode)
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.Addr485 > MAX_Addr )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DataFormat > MAX_DataFormat )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DataProtocol > MAX_DataProt || pSettingParam->CtrlParam.DataProtocol < MIN_DataProt )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.Cycle > MAX_Cycle || pSettingParam->CtrlParam.Cycle < MIN_Cycle )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.BlackTime > MAX_BlackTime  || pSettingParam->CtrlParam.BlackTime  < MIN_BlackTime  )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DefaultDisp > MAX_Disp )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.PTNum > MAX_PT || pSettingParam->CtrlParam.PTNum < MIN_PT )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.CTNum > MAX_CT || pSettingParam->CtrlParam.CTNum < MIN_CT )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.Baud485 > MAX_Baud )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.Alarm > MAX_Alarm)
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.Code > MAX_Code || pSettingParam->CtrlParam.Code < MIN_Code )
    {
        return FALSE;
    }

    /*********************************DO-1*******************************************************************/
    if( pSettingParam->CtrlParam.DO1_Mode > MAX_DO_Mode )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO1_Item > MAX_DO_Item )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO1_Time > MAX_DO_Time )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO1_UAL > MAX_DO_Ual )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO1_HYS > MAX_DO_Hys )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO1_Delay > MAX_DO_Dely )
    {
        return FALSE;
    }

    /*********************************DO-2*******************************************************************/
    if( pSettingParam->CtrlParam.DO2_Mode > MAX_DO_Mode )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO2_Item > MAX_DO_Item )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO2_Time > MAX_DO_Time )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO2_UAL > MAX_DO_Ual )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO2_HYS > MAX_DO_Hys )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO2_Delay > MAX_DO_Dely )
    {
        return FALSE;
    }

    /*********************************DO-3*******************************************************************/
    if( pSettingParam->CtrlParam.DO3_Mode > MAX_DO_Mode )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO3_Item > MAX_DO_Item )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO3_Time > MAX_DO_Time )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO3_UAL > MAX_DO_Ual )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO3_HYS > MAX_DO_Hys )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO3_Delay > MAX_DO_Dely )
    {
        return FALSE;
    }

    /*********************************DO-4*******************************************************************/
    if( pSettingParam->CtrlParam.DO4_Mode > MAX_DO_Mode )//|| pSettingParam->CtrlParam.DO3_Mode < MIN_DO_Mode )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO4_Item > MAX_DO_Item )//|| pSettingParam->CtrlParam.DO3_Item < MIN_DO_Item )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO4_Time > MAX_DO_Time )//|| pSettingParam->CtrlParam.DO3_Time < MIN_DO_Time )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO4_UAL > MAX_DO_Ual )//|| pSettingParam->CtrlParam.DO3_UAL < MIN_DO_Ual )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO4_HYS > MAX_DO_Hys )//|| pSettingParam->CtrlParam.DO3_HYS < MIN_DO_Hys )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.DO4_Delay > MAX_DO_Dely )//|| pSettingParam->CtrlParam.DO3_Delay < MIN_DO_Dely )
    {
        return FALSE;
    }

    /*********************************AO-1*******************************************************************/
    if( pSettingParam->CtrlParam.AO1_Mode > MAX_AO_Mode )//|| pSettingParam->CtrlParam.AO1_Mode < MIN_AO_Mode )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.AO1_Item > MAX_DO_Item )//|| pSettingParam->CtrlParam.DO1_Item < MIN_DO_Item )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.AO1_DS > MAX_AO_DS )//|| pSettingParam->CtrlParam.AO1_DS< MIN_AO_DS)
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.AO1_FS > MAX_AO_FS )//|| pSettingParam->CtrlParam.AO1_FS < MIN_AO_FS)
    {
        return FALSE;
    }

    /*********************************AO-2*******************************************************************/
    if( pSettingParam->CtrlParam.AO2_Mode > MAX_AO_Mode )//|| pSettingParam->CtrlParam.AO1_Mode < MIN_AO_Mode )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.AO2_Item > MAX_DO_Item )//|| pSettingParam->CtrlParam.DO1_Item < MIN_DO_Item )
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.AO2_DS > MAX_AO_DS )//|| pSettingParam->CtrlParam.AO1_DS< MIN_AO_DS)
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.AO2_FS > MAX_AO_FS )//|| pSettingParam->CtrlParam.AO1_FS < MIN_AO_FS)
    {
        return FALSE;
    }
    /*********************************������ʼ�����λ********************************************************************/
    if( pSettingParam->CtrlParam.AnaCalibFlag > 0x01 )  // ϵͳ��һ�γ�ʼ����
    {
        return FALSE;
    }
    if( pSettingParam->CtrlParam.INIT != 0x55 )  // ϵͳ��һ�γ�ʼ����
    {
        return FALSE;
    }
    return TRUE;
}

void MemData_CmpParam(PARAM_T *pSettingParam)
{
    bool aa = TRUE;
    aa = MemData_CmpParamType(pSettingParam);
    //if (!MemData_CmpParamType(pSettingParam))
    if(!aa)
    {
        InitCtrlParam();                     /* ��ʼ�����Ʋ��� */
        InitRNParam();                       /* ��ʼ�����Ʋ��� */
        MemData_WriteParam();
    }
}
// ����Ĭ�ϲ���
// �ָ�Ĭ������ֵ ����PT CT ��ַ
void MemData_SetDefaultParam(PARAM_T *pSettingParam, BOOL bInit)
{
        //�ָ���������
}

u16 MemData_Crc(u8 *pData)
{
	u16 Crc = 0;
	u16 Counter = 0;
	for (Counter = 0; Counter < FLASH_PARAM_SIZE-2; Counter++)
	{
		Crc += *(pData+Counter);
	}
	return Crc;
}

u16 MEMEnergy_Crc(u8 *pData)
{
	u32 Crc = 0;
	u16 Counter = 0;
	for (Counter = 0; Counter < MEM_Energy_SIZE-2; Counter++)
	{
		Crc += *(pData+Counter);
	}
    Crc = Crc & 0xff;
	return Crc;
}


// �������
void MemData_CalcParam(void)
{
    //���²���
}

/*------------------------------------------------------------------------
 * �� �� �� : MemData_WriteParam
 * �������� : ���������FLASH
 * ʱ    �� : 2012��2��20��
 * �� �� ֵ : BOOL --- TRUE �޴���
                        FALSE �޻�Ӧ
 * ����˵�� : u8 Addr---оƬ�ڲ����ݴ洢��ַ
              u8 *pOutData---д�����ݴ������
              u8 Count---Ҫд������ݳ��� Ϊ0 ������д
 * �޸���ʷ :
------------------------------------------------------------------------*/
void MemData_WriteParam(void)
{
	u8 FlashData[FLASH_PARAM_SIZE];
	u16 Size = 0;
	u16 Crc = 0;
	u8 *pData;

	memset((u8 *)&FlashData, 0xFF, FLASH_PARAM_SIZE);
	Size = sizeof(PARAM_T);;
	memcpy((u8 *)&FlashData, (u8 *)&g_tParam, Size);

	pData = (u8 *)&FlashData[0];
	Crc = MemData_Crc(pData);
	pData += (FLASH_PARAM_SIZE-2);
	memcpy(pData, (u8 *)&Crc, 2);
	MemData_Write_To_Flash(CONFIG_STARTADDR, FlashData, FLASH_PARAM_SIZE);

	//MemData_CalcParam(); // ÿдһ�ξͼ��� ���ݸ���
	__nop();

}

/*------------------------------------------------------------------------
 * �� �� �� : MemData_ReadParam
 * �������� : ��FLASH������
 * ʱ    �� : 2006��6��23��
 * ʱ    �� : 2012��2��20��
 * �� �� ֵ : BOOL --- TRUE �޴���
                        FALSE �޻�Ӧ
 * ����˵�� : u8 Addr---оƬ�ڲ����ݴ洢��ַ
              u8 *pInData---��ȡ���ݴ������
              u8 Count---Ҫ��ȡ�����ݳ��� Ϊ0 ������д
 * �޸���ʷ :
------------------------------------------------------------------------*/
void MemData_ReadParam(void)
{
	u8 FlashData[FLASH_PARAM_SIZE];
	u16 Size = 0;
	u16 Crc = 0;

	memcpy(FlashData, (u8 *)CONFIG_STARTADDR, FLASH_PARAM_SIZE);
	Crc = MemData_Crc(FlashData);
	if (Crc == FLIPW(&FlashData[FLASH_PARAM_SIZE-2]))  //CRC��֤ ��ȡ�Ƿ����
	{
		Size = sizeof(PARAM_T);;
		memcpy((u8 *)&g_tParam, (u8 *)&FlashData[0], Size);
		MemData_CmpParam(&g_tParam);
	}
	else // ʧ�ܣ��ѵ�ǰ����д��EEPROM
	{
		MemData_WriteParam();
	}
}

// ���ݳ�ʼ��
void MemData_InitSettingParam(void)
{
    MemData_SetDefaultParam(&g_tParam, TRUE);
    MemData_ReadParam();
}


void MemData_InitPowerVal(void) //��������ʼ��
{
    u8 ph = PH_A;
    for (ph = PH_A; ph < PH_TH; ph++)
    {
        vg_Power_Val.Real2_Val[ph].U = 22000;//���β��ѹ AC
        vg_Power_Val.Real2_Val[ph].I= 50000;//���β���� B
        vg_Power_Val.Real2_Val[ph].P = 31350;//���β��й�����
        vg_Power_Val.Real2_Val[ph].Q = 10304;//���β��޹�����
        vg_Power_Val.Real2_Val[ph].S = 33000;//���β����ڹ���
        vg_Power_Val.Real2_Val[ph].PF = 950;//��������ֵ
    }
    vg_Power_Val.Freq = 5000;
}

//////////////////////////////////////////////////////////////////////////////////////////////
// ���ܲ���
//===================================================================
// ���ܼ�¼д��
void MEM_EnergyRecordWrite(void)
{
	u8 FramWriteEnergy[MEM_Energy_SIZE];
	u16 CrcSum = 0;
	u8 *pData;
	u16 EnergySize = 0;
	u32 TempAddr;
	
	memset((u8 *)&FramWriteEnergy, 0xFF, MEM_Energy_SIZE);
	EnergySize = sizeof(EnergyRecordStructure)*31;
	memcpy((u8 *)&FramWriteEnergy, (u8 *)&NowEnergyRecord[0], EnergySize);

	pData = (u8 *)&FramWriteEnergy[0];
	CrcSum= MEMEnergy_Crc(pData);
	pData += (MEM_Energy_SIZE-2);
	memcpy(pData, (u8 *)&CrcSum, 2);
	
    switch (SoeIndex.BackMonth)
    {
        case 0x01:
            MemEnergy_Write_To_Flash(MEM_JanEn_sADDR, FramWriteEnergy, MEM_Energy_SIZE);
            break;
        default:
            break;
    }
    __nop();
}
void MEM_EnergyRecordRead(void)
{
    u8 FramReadEnergy[MEM_Energy_SIZE];
    for(u16 i =0; i<MEM_Energy_SIZE; i++)
    {
        FramReadEnergy[i] = 0;
    }
	u16 Size = 0;
	u16 Crc = 0;
	
    memcpy(FramReadEnergy, (u8 *)MEM_JanEn_sADDR, MEM_Energy_SIZE);
    
	Crc = MEMEnergy_Crc(FramReadEnergy);
	if (Crc == FLIPW(&FramReadEnergy[MEM_Energy_SIZE-2]))  //CRC��֤ ��ȡ�Ƿ����
    {
		Size = sizeof(EnergyRecordStructure)*31;
		memcpy((u8 *)&NowEnergyRecord[0], (u8 *)&FramReadEnergy[0], Size);
	}
	else // ʧ�ܣ��ѵ�ǰ����д��EEPROM
	{
		//Size = sizeof(Energy_Memory);
		//memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);
	}
	__nop();
}

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

// ���ݳ�ʼ��
void MemData_Init(void)
{
    MemData_InitSettingParam();

    MemData_InitPowerVal();

	MemData_CalcParam(); // ��ʼ������

    MemData_WriteParam();

}



