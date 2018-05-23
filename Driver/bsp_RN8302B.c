/* Includes ------------------------------------------------------------------*/

#include "Include.h"

//RN8302

static u8 Rn8302_RX_Buf[10];
static u8 Rn8302_TX_Buf[10];
static ErrorStatus RN8302_TX_Frame(u8 num);
static ErrorStatus RN8302_RX_Frame(u8 num);
static u8 RN8302WR(RegStructure *dat);
static u8 RN8302RD(RegStructure *dat);
static void RN8302Init(void);
u32 CheckSum;
BOOL MaxFramWriteEnble = FALSE;
POWER2_ValStruct vg_Power_Val;
POWER22_ValStruct vg_Power2_Val;
POWER2_Read_ValStruct vg_Read_Val;
DemMaxStructure vg_DemMax_Val[4];        // ���� ���ֵ


//struct RN_AnalogData g_AnalogData;
/******************************************************************************

                         RN8302ȫ�������������弰��ʼ��

  ****************************************************************************/

Full_wave_data Fullwave_data =
{
    .Ua_wave = {bank0, 0x00, 3, RO, 0},
    .Ub_wave = {bank0, 0x01, 3, RO, 0},
    .Uc_wave = {bank0, 0x02, 3, RO, 0},
    .Ia_wave = {bank0, 0x03, 3, RO, 0},
    .Ib_wave = {bank0, 0x04, 3, RO, 0},
    .Ic_wave = {bank0, 0x05, 3, RO, 0},
    .In_wave = {bank0, 0x06, 3, RO, 0},
    .U[0] = {bank0, 0x07, 4, RO, 0},
    .U[1] = {bank0, 0x08, 4, RO, 0},
    .U[2] = {bank0, 0x09, 4, RO, 0},
    .USum_vector = {bank0, 0x0A, 4, RO, 0},
    .I[0] = {bank0, 0x0B, 4, RO, 0},
    .I[1] = {bank0, 0x0C, 4, RO, 0},
    .I[2] = {bank0, 0x0D, 4, RO, 0},
    .In = {bank0, 0x0E, 4, RO, 0},
    .Reserved1 = {bank0, 0x0F, 4, RO, 0},
    .ISum_vector = {bank0, 0x10, 4, RO, 0},
//    .Ia_NVM1 = {bank0, 0x11, 3, RO, 0},
//    .Ib_NVM1 = {bank0, 0x12, 3, RO, 0},
//    .Ic_NVM1 = {bank0, 0x13, 3, RO, 0},
    .P[0] = {bank0, 0x14, 4, RO, 0},
    .P[1] = {bank0, 0x15, 4, RO, 0},
    .P[2] = {bank0, 0x16, 4, RO, 0},
    .Pt = {bank0, 0x17, 4, RO, 0},
    .Q[0] = {bank0, 0x18, 4, RO, 0},
    .Q[1] = {bank0, 0x19, 4, RO, 0},
    .Q[2] = {bank0, 0x1A, 4, RO, 0},
    .Qt = {bank0, 0x1B, 4, RO, 0},
    .S[0] = {bank0, 0x1C, 4, RO, 0},
    .S[1] = {bank0, 0x1D, 4, RO, 0},
    .S[2] = {bank0, 0x1E, 4, RO, 0},
    .St = {bank0, 0x1F, 4, RO, 0},
    .Pf[0] = {bank0, 0x20, 3, RO, 0},
    .Pf[1] = {bank0, 0x21, 3, RO, 0},
    .Pf[2] = {bank0, 0x22, 3, RO, 0},////
    .Pft = {bank0, 0x23, 3, RO, 0},
    .EPt = {bank0, 0x33, 3, RO, 0},
    .PosEPt = {bank0, 0x37, 3, RO, 0},
    .NegEPt = {bank0, 0x3B, 3, RO, 0},
    .EQt = {bank0, 0x3F, 3, RO, 0},
    .PosEQt = {bank0, 0x43, 3, RO, 0},
    .NegEQt = {bank0, 0x47, 3, RO, 0},
    .ESt = {bank0, 0x4B, 3, RO, 0},
};
/******************************************************************************

                         RN8302����г�������������弰��ʼ��

*******************************************************************************/
Fundamental_wave_data Fundwave_data =
{
    .YU[0] = {bank0, 0x50, 3, RO, 0},
    .YU[1] = {bank0, 0x51, 3, RO, 0},
    .YU[2] = {bank0, 0x52, 3, RO, 0},
    .YI[0] = {bank0, 0x53, 3, RO, 0},
    .YI[1] = {bank0, 0x54, 3, RO, 0},
    .YI[2] = {bank0, 0x55, 3, RO, 0},
    .YIn = {bank0, 0x56, 3, RO, 0},
    .UFrequence = {bank0, 0x57, 3, RO, 0},
    .FU[0] = {bank0, 0x58, 4, RO, 0},
    .FU[1] = {bank0, 0x59, 4, RO, 0},
    .FU[2] = {bank0, 0x5A, 4, RO, 0},
    .FI[0] = {bank0, 0x5B, 4, RO, 0},
    .FI[1] = {bank0, 0x5C, 4, RO, 0},
    .FI[2] = {bank0, 0x5D, 4, RO, 0},
    .FPa = {bank0, 0x5E, 4, RO, 0},
    .FPb = {bank0, 0x5F, 4, RO, 0},
    .FPc = {bank0, 0x60, 4, RO, 0},
    .FPt = {bank0, 0x61, 4, RO, 0},
    .FQa = {bank0, 0x62, 4, RO, 0},
    .FQb = {bank0, 0x63, 4, RO, 0},
    .FQc = {bank0, 0x64, 4, RO, 0},
    .FQt = {bank0, 0x65, 4, RO, 0},
    .FSa = {bank0, 0x66, 4, RO, 0},
    .FSb = {bank0, 0x67, 4, RO, 0},
    .FSc = {bank0, 0x68, 4, RO, 0},
    .FSt = {bank0, 0x69, 4, RO, 0},
    .FPfa = {bank0, 0x6A, 3, RO, 0},
    .FPfb = {bank0, 0x6B, 3, RO, 0},
    .FPfc = {bank0, 0x6C, 3, RO, 0},
    .FPft = {bank0, 0x6D, 3, RO, 0},
    .HU[0] = {bank0, 0x96, 4, RO, 0},
    .HU[1] = {bank0, 0x97, 4, RO, 0},
    .HU[2] = {bank0, 0x98, 4, RO, 0},
    .HI[0] = {bank0, 0x99, 4, RO, 0},
    .HI[1] = {bank0, 0x9A, 4, RO, 0},
    .HI[2] = {bank0, 0x9B, 4, RO, 0},

};
/******************************************************************************

                   RN8302���ü�״̬�������弰��ʼ��

*******************************************************************************/
Config_Stutas_REG CFG_StatusREG =
{
    //EMMУ��Ĵ��� I
    .HFConst1 = {bank1, 0x00, 2, RW, 15261},
    .HFConst2 = {bank1, 0x01, 2, RW, 4096},
    .IStart_PS = {bank1, 0x02, 2, RW, 592},
    .IStart_Q = {bank1, 0x03, 2, RW, 592},
    .LostVoltT = {bank1, 0x04, 2, RW, 1024},
    .ZXOT = {bank1, 0x05, 2, RW, 115},
    .PRTH1L = {bank1, 0x06, 2, RW, 500},      //�ֶ�У��
    .PRTH1H = {bank1, 0x07, 2, RW, 1000},
    .PRTH2L = {bank1, 0x08, 2, RW, 2000},
    .PRTH2H = {bank1, 0x09, 2, RW, 3000},
//    .IRegion3L = {bank1, 0x0A, 2, RW, 0},
//    .IRegion3H = {bank1, 0x0B, 2, RW, 0},
    .PHSU[0] = {bank1, 0x0C, 1, RW, 128},
    .PHSU[1] = {bank1, 0x0D, 1, RW, 128},
    .PHSU[2] = {bank1, 0x0E, 1, RW, 128},
    .PHSI[0] = {bank1, 0x0F, 3, RW, 8421504},
    .PHSI[1] = {bank1, 0x10, 3, RW, 8421504},
    .PHSI[2] = {bank1, 0x11, 3, RW, 8421504},
    .PHSIN = {bank1, 0x12, 1, RW, 128},
    .GSU[0] = {bank1, 0x13, 2, RW, 10210},
    .GSU[1] = {bank1, 0x14, 2, RW, 10210},
    .GSU[2] = {bank1, 0x15, 2, RW, 10210},
    .GSI[0] = {bank1, 0x16, 2, RW, 59568},
    .GSI[1] = {bank1, 0x17, 2, RW, 59568},
    .GSI[2] = {bank1, 0x18, 2, RW, 59568},
    .GSIN = {bank1, 0x19, 2, RW, 0},
    .P_PHSL[0] ={bank1, 0x31,2, RW, 0},
    .P_PHSL[1] ={bank1, 0x32,2, RW, 0},
    .P_PHSL[2] ={bank1, 0x33,2, RW, 0},
    .Q_PHSL[0] ={bank1, 0x34,2, RW, 0},
    .Q_PHSL[1] ={bank1, 0x35,2, RW, 0},
    .Q_PHSL[2] ={bank1, 0x36,2, RW, 0},
    .PA_PHSM ={bank1, 0xB0,3, RW, 0},
    .PA_PHSH ={bank1, 0xB1,3, RW, 0},
    .PB_PHSM ={bank1, 0xB2,3, RW, 0},
    .PB_PHSH ={bank1, 0xB3,3, RW, 0},
    .PC_PHSM ={bank1, 0xB4,3, RW, 0},
    .PC_PHSH ={bank1, 0xB5,3, RW, 0},
    .QA_PHSM ={bank1, 0xB6,3, RW, 0},
    .QA_PHSH ={bank1, 0xB7,3, RW, 0},
    .QB_PHSM ={bank1, 0xB8,3, RW, 0},
    .QB_PHSH ={bank1, 0xB9,3, RW, 0},
    .QC_PHSM ={bank1, 0xBA,3, RW, 0},
    .QC_PHSH ={bank1, 0xBB,3, RW, 0},
//    .DCOS_UA = {bank1, 0x1A, 2, RW, 0},
//    .DCOS_UB = {bank1, 0x1B, 2, RW, 0},
//    .DCOS_UC = {bank1, 0x1C, 2, RW, 0},
//    .DCOS_IA = {bank1, 0x1D, 2, RW, 0},
//    .DCOS_IB = {bank1, 0x1E, 2, RW, 0},
//    .DCOS_IC = {bank1, 0x1F, 2, RW, 0},
//    .DCOS_IN = {bank1, 0x20, 2, RW, 0},
//    .UA_OS = {bank1, 0x21, 2, RW, 0},
//    .UB_OS = {bank1, 0x22, 2, RW, 0},
//    .UC_OS = {bank1, 0x23, 2, RW, 0},
    .I_OS[0] = {bank1, 0x24, 2, RW, 0},
    .I_OS[1] = {bank1, 0x25, 2, RW, 0},
    .I_OS[2] = {bank1, 0x26, 2, RW, 0},

    //EMM���ú�״̬�Ĵ���
    .CFCFG = {bank1, 0x60, 3, RW, 274960},
    .EMUCFG = {bank1, 0x61, 3, RW, 4718592},
    .EMUCON = {bank1, 0x62, 3, RW, 7829367},
    .WSAVECON = {bank1, 0x63, 1, RW, 0},
    .EMMIE = {bank1, 0x64, 2, RW, 0},
    .EMMIF = {bank1, 0x65, 2, RO, 0},
    .PQSign = {bank1, 0x66, 2, RO, 0},
    .Noload = {bank1, 0x67, 2, RO, 0},
    .IRegionS = {bank1, 0x68, 2, RO, 0},
    .PHASES = {bank1, 0x69, 2, RO, 0},
    .CheckSum1 = {bank1, 0x6A, 3, RO, 0},
    //NVM1���ú�״̬�Ĵ���
//    .NVM1CFG = {bank1, 0x70, 1, RW, 0},
//    .NVM1IF = {bank1, 0x71, 1, RO, 0},
    //NVM2���ú�״̬�Ĵ���
//    .NVM2CFG = {bank1, 0x72, 2, RW, 3873},
//    .NVM2CMPA = {bank1, 0x73, 2, RW, 598},
//    .NVM2CMPB = {bank1, 0x74, 2, RW, 598},
//    .NVM2CMPC = {bank1, 0x75, 2, RW, 598},
//    .NVM2IF = {bank1, 0x76, 1, RO, 0},
    //ϵͳ���üĴ���
    .WREN = {bank1, 0x80, 1, RW, 220},
    .WMSW = {bank1, 0x81, 1, RW, 1},
    .SOFT_RST = {bank1, 0x82, 1, RW, 250},
    .ADCREG = {bank1, 0x83, 2, RW, 0},
    .MODSEL = {bank1, 0x86, 1, RW, 0},
    //ϵͳ״̬�Ĵ���
    .SYSSR = {bank1, 0x8A, 2, RO, 0},
    .CheckSum2  = {bank1, 0x8B, 2, RO, 0},
    .RData = {bank1, 0x8C, 4, RO, 0},
    .WData = {bank1, 0x8D, 3, RO, 0},
    .LRBufAddr = {bank1, 0x8E, 2, RO, 0},
    .DeciceID = {bank1, 0x8F, 3, RO, 0},
};
/******************************************************************************
  * *   ��������: sqrt_64fixed(u64 a)

  * *   ����˵��: ������ƽ����

  * *   �������: a ��ֵ

  * *   �������: ��

  * *   ����ֵ:  ��
  ****************************************************************************/
u32 sqrt_64fixed(u64 a)
{
    u64 i, c;
    u64 b = 0;
    for(i = 0x4000000000000000; i != 0; i >>= 2)
    {
        c = i + b;
        b >>= 1;
        if(c <= a)
        {
            a -= c;
            b += i;
        }
    }
    return (u32)b;
}
/******************************************************************************
  * *   ��������: LineCalcFunc(u8 Phase,int Angle)

  * *   ����˵��: �����ߵ�ѹֵ

  * *   �������: u8 Phase �࣬int Angle ������֮��нǶ���

  * *   �������: ��

  * *   ����ֵ:  ��
  ****************************************************************************/
u32 LineCalcFunc(u8 Phase,int Angle)
{
    u64 a,b,c;
    u32 d;
    double Radian;
    Radian = Angle * 3.1415926 / 1800;  //���ȼ���
    switch(Phase)
    {
        case 0:     //AB
            a = vg_Power_Val.Real2_Val[0].U*vg_Power_Val.Real2_Val[0].U;
            b = vg_Power_Val.Real2_Val[1].U*vg_Power_Val.Real2_Val[1].U;
            c = a+b-2*vg_Power_Val.Real2_Val[1].U*vg_Power_Val.Real2_Val[0].U*cos(Radian);
            d = sqrt_64fixed(c);
            break;
        case 1:     //BC
            a = vg_Power_Val.Real2_Val[1].U*vg_Power_Val.Real2_Val[1].U;
            b = vg_Power_Val.Real2_Val[2].U*vg_Power_Val.Real2_Val[2].U;
            c = a+b-2*vg_Power_Val.Real2_Val[2].U*vg_Power_Val.Real2_Val[1].U*cos(Radian);
            d = sqrt_64fixed(c);
            break;
        case 2:     //AC
            a = vg_Power_Val.Real2_Val[2].U*vg_Power_Val.Real2_Val[2].U;
            b = vg_Power_Val.Real2_Val[0].U*vg_Power_Val.Real2_Val[0].U;
            c = a+b-2*vg_Power_Val.Real2_Val[2].U*vg_Power_Val.Real2_Val[0].U*cos(Radian);
            d = sqrt_64fixed(c);
            break;
        case 3:     //IB
            a = vg_Power_Val.Real2_Val[2].I*vg_Power_Val.Real2_Val[2].I;
            b = vg_Power_Val.Real2_Val[0].I*vg_Power_Val.Real2_Val[0].I;
            c = a+b+2*vg_Power_Val.Real2_Val[2].I*vg_Power_Val.Real2_Val[0].I*cos(Radian);
            d = sqrt_64fixed(c);
            break;
        default:
            break;
    }
    return d;
}
void bsp_InitRN8023(void)
{
    RN8302Init();
}

/******************************************************************************
  * *   ��������: RN8302WR(RegStructure* dat)

  * *   ����˵��: ��RN8302ָ���ļĴ�����д����

  * *   �������: RegStructure* dat��ָ���ļĴ����ṹָ��

  * *   �������: ��

  * *   ����ֵ:  ��
  ****************************************************************************/
static u8 RN8302WR(RegStructure *dat)
{
    u8 data1, data2, data3;
    u8 check;

    if(dat->rw == RO)return ERROR;
    switch(dat->bytenum)
    {
    case 1:
        data1 = dat->data & 0xff;
        Rn8302_TX_Buf[0] = dat->addr;
        Rn8302_TX_Buf[1] = 0x80 | (dat->bank << 4);
        Rn8302_TX_Buf[2] = data1;
        check = RN8302_TX_Frame(3);
        break;
    case 2:
        data1 = (dat->data >> 8) & 0xff;
        data2 = dat->data & 0xff;
        Rn8302_TX_Buf[0] = dat->addr;
        Rn8302_TX_Buf[1] = 0x80 | (dat->bank << 4);

        Rn8302_TX_Buf[2] = data1;
        Rn8302_TX_Buf[3] = data2;
        check = RN8302_TX_Frame(4);
        break;
    case 3:
        data1 = (dat->data >> 16) & 0xff;
        data2 = (dat->data >> 8) & 0xff;
        data3 = dat->data & 0xff;
        Rn8302_TX_Buf[0] = dat->addr;
        Rn8302_TX_Buf[1] = 0x80 | (dat->bank << 4);
        Rn8302_TX_Buf[2] = data1;
        Rn8302_TX_Buf[3] = data2;
        Rn8302_TX_Buf[4] = data3;
        check = RN8302_TX_Frame(5);
        break;
    default:
        break;
    }
    return check;
}

/******************************************************************************

  * *   ��������: RN8302RD(RegStructure* dat)

  * *   ����˵��: ��RN8302ָ���ļĴ����ж�ȡ����

  * *   �������: RegStructure* dat��ָ���ļĴ����ṹָ��

  * *   �������: ��

  * *   ����ֵ:   У��������ȷ����1�����󷵻�0

  ****************************************************************************/
static u8 RN8302RD(RegStructure *dat)
{
    u8 check = 0;
    if(dat->rw != RO && dat->rw != RW)return 0;
    switch(dat->bytenum)
    {
    case 1:
        Rn8302_TX_Buf[0] = dat->addr;
        Rn8302_TX_Buf[1] = 0x00 | (dat->bank << 4);
        check = RN8302_RX_Frame(1);
        if(check) dat->data = Rn8302_RX_Buf[0];
        break;
    case 2:
        Rn8302_TX_Buf[0] = dat->addr;
        Rn8302_TX_Buf[1] = 0x00 | (dat->bank << 4);
        check = RN8302_RX_Frame(2);
        if(check) dat->data = Rn8302_RX_Buf[0] << 8 | Rn8302_RX_Buf[1];
        break;
    case 3:
        Rn8302_TX_Buf[0] = dat->addr;
        Rn8302_TX_Buf[1] = 0x00 | (dat->bank << 4);
        check = RN8302_RX_Frame(3);
        if(check) dat->data = Rn8302_RX_Buf[0] << 16 | Rn8302_RX_Buf[1] << 8 | Rn8302_RX_Buf[2];
        break;
    case 4:
        Rn8302_TX_Buf[0] = dat->addr;
        Rn8302_TX_Buf[1] = 0x00 | (dat->bank << 4);
        check = RN8302_RX_Frame(4);
        if(check) dat->data = Rn8302_RX_Buf[0] << 24 | Rn8302_RX_Buf[1] << 16 | Rn8302_RX_Buf[2] << 8 | Rn8302_RX_Buf[3];
        break;
    default:
        break;
    }
    return check;
}



void spi_nop(void)
{
    u8 i = 100; //��������Ż��ٶ�
    while(i)
    {
        i--;
    }
}

/****************************************************************************************
** ��������: Spi_RN8302_SendByte
** ��������: ��RN8302B����һ���ֽ�
** ��    ��: u8 byData---�����ֽ�
** �� �� ֵ: TRUE---�ɹ�, FALSE---ʧ��
** ����  ��:
** ��  ����: 2010��10��8��
**---------------------------------------------------------------------------------------
** �� �� ��:
** �ա�  ��:
**--------------------------------------------------------------------------------------
****************************************************************************************/
u8 Spi_RN8302_SendByte(u8 byData)
{
    u8 i;
    for (i = 0; i < 8; i++)     // Setup byte circulation bits
    {
        if (byData & 0x80)              // Put DATA_BUF.7 on data line
            RN_SPI_MOSI_H;
        else
            RN_SPI_MOSI_L;
        RN_SPI_SCK_H;                   // Set clock line high
        byData <<= 1;                       // Shift DATA_BUF
        spi_nop();
        RN_SPI_SCK_L;                   // Set clock line low
        spi_nop();
    }
    return TRUE;
}

/****************************************************************************************
** ��������: Spi_RN8302_ReadByte
** ��������: ��RN8302B����һ���ֽ�
** ��    ��:
** �� �� ֵ: ��ȡ��һ���ֽ�ֵ, 0xffΪ��Чֵ
** ����  ��:
** ��  ����: 2010��10��8��
**---------------------------------------------------------------------------------------
** �� �� ��:
** �ա�  ��:
**--------------------------------------------------------------------------------------
****************************************************************************************/
u8 Spi_RN8302_ReadByte(void)
{
    u8 i;
    u8 byte;
    byte = 0;
    for (i = 0; i < 8; i++)     // Setup byte circulation bits
    {
        byte <<= 1; // Right shift DATA_BUF
        RN_SPI_SCK_H;                   // Set clock line high
        if (RN_SPI_MISO_IN)
            byte |= 0x01;           // Read data
        spi_nop();

        RN_SPI_SCK_L;                   // Set clock line low
        spi_nop();
    }
    return byte;            // Return function parameter
}

/******************************************************************************

  * *   ��������: RN8302_TX_Frame(uchar num)

  * *   ����˵��: ��8302�з���һ֡���ݣ�Rn8302_TX_Buf���ͻ�����

  * *   �������: num ֡�ֽ���

  * *   �������: ��

  * *   ����ֵ:   ��

  ****************************************************************************/
static ErrorStatus RN8302_TX_Frame(u8 num)
{
    u8 i, Repeat, temp;
    u8 checksum = 0;
    u8 *p;
    ErrorStatus        err = SUCCESS;

    RN_SPI_CSN_L;
    for(Repeat = 3; Repeat > 0; Repeat--)
    {
        p = Rn8302_TX_Buf;
        for(i = 0; i < num; i++)
        {
            Spi_RN8302_SendByte(*p);
            checksum += *p;
            p++;
        }
        checksum = ~checksum;
        Spi_RN8302_SendByte(checksum);
        //��WData�Ĵ������-----------------------
        Spi_RN8302_SendByte( 0x8D);
        checksum = 0x8D;
        temp = 0x10;
        Spi_RN8302_SendByte(temp);
        checksum += temp;
        for(i = 3 ; i > 0 ; i--)
        {
            temp = Spi_RN8302_ReadByte();
            if((num - 2) >= i)
            {
                if(temp != Rn8302_TX_Buf[num - i])
                {
                    err = ERROR;
                    break;
                }
            }
            checksum += temp;
        }
        if(err == SUCCESS)
        {
            checksum = ~checksum;
            temp = Spi_RN8302_ReadByte();
            if(temp != checksum)  err = ERROR;
        }
        if(err == SUCCESS)
        {
            if(num - 2 == 3)CFG_StatusREG.WData.data =  Rn8302_TX_Buf[2] << 16 | Rn8302_TX_Buf[3] << 8 | Rn8302_TX_Buf[4];
            else if(num - 2 == 2)CFG_StatusREG.WData.data =  Rn8302_TX_Buf[2] << 8 | Rn8302_TX_Buf[3];
            else if(num - 2 == 1)CFG_StatusREG.WData.data =  Rn8302_TX_Buf[2];
            break;
        }
    }
    RN_SPI_CSN_H;
    return(err);
}

/******************************************************************************

  * *   ��������: RN8302_RX_Frame(uchar num)

  * *   ����˵��: ��8302�ж�ȡһ֡���ݣ�Rn8302_RX_Buf���ջ�����

  * *   �������: num ֡�ֽ���

  * *   �������: ��

  * *   ����ֵ:   У��������ȷ����1�����󷵻�0

  ****************************************************************************/
static ErrorStatus RN8302_RX_Frame(u8 num)
{
    u8 i, Repeat, temp;
    u8 checksum = 0;
    u8 *p;
    ErrorStatus err = SUCCESS;

    RN_SPI_CSN_L;
    for(Repeat = 3; Repeat > 0; Repeat--)
    {
        p = Rn8302_RX_Buf;
        Spi_RN8302_SendByte(Rn8302_TX_Buf[0]);
        checksum = Rn8302_TX_Buf[0];
        Spi_RN8302_SendByte(Rn8302_TX_Buf[1]);
        checksum += Rn8302_TX_Buf[1];
        for(i = 0; i < num; i++)
        {
            *p = Spi_RN8302_ReadByte();
            checksum += *p;
            p++;
        }
        checksum = ~checksum;
        if(checksum != Spi_RN8302_ReadByte())err = ERROR;
        if(err != SUCCESS)continue;
        //---��RData�Ĵ������------------------------------------
        Spi_RN8302_SendByte( 0x8C);
        checksum = 0x8C;
        temp = 0x10;
        Spi_RN8302_SendByte( temp );
        checksum += temp;
        for(i = 4 ; i > 0 ; i--)
        {
            temp = Spi_RN8302_ReadByte();
            if(num >= i)
            {
                if(temp != Rn8302_RX_Buf[num - i])
                {
                    err = ERROR;
                    break;
                }
            }
            checksum += temp;
        }
        if(err == SUCCESS)
        {
            checksum = ~checksum;
            temp = Spi_RN8302_ReadByte();
            if(temp != checksum)  err = ERROR;
        }
        if(err == SUCCESS)
        {
            if(num == 4)CFG_StatusREG.RData.data =  Rn8302_RX_Buf[0] << 24 | Rn8302_RX_Buf[1] << 16 | Rn8302_RX_Buf[2] << 8 | Rn8302_RX_Buf[3];
            else if(num == 3)CFG_StatusREG.RData.data =  Rn8302_RX_Buf[0] << 16 | Rn8302_RX_Buf[1] << 8 | Rn8302_RX_Buf[2];
            else if(num == 2)CFG_StatusREG.RData.data =  Rn8302_RX_Buf[0] << 8 | Rn8302_RX_Buf[1];
            else if(num == 1)CFG_StatusREG.RData.data =  Rn8302_RX_Buf[0];
            break;
        }

    }
    RN_SPI_CSN_H;
    return(err);
}

/******************************************************************************

  * *   ��������: RN8302RDBUFF(RegStructure* dat)

  * *   ����˵��: ��RN8302ָ���ļĴ����ж�ȡ���λ�������

  * *   �������: RegStructure* dat��ָ���ļĴ����ṹָ��

  * *   �������: ��

  * *   ����ֵ:   У��������ȷ����1�����󷵻�0

  ****************************************************************************/
u8 RN8302RDBUFF(u16 addr, u8 *pReadWaveData)
{
    u8 i,temp,Repeat,addtmp;
    u8 checksum = 0;
    ErrorStatus err = SUCCESS;

    Rn8302_TX_Buf[0] = (u8)(addr & 0x00ff);
    addtmp = (u8)(addr >>4)&0xf0;
    Rn8302_TX_Buf[1] = 0x00 | addtmp | 0x0c;

    RN_SPI_CSN_L;
    for(Repeat = 3; Repeat > 0; Repeat--)
    {
        //pReadWaveData = Rn8302_RX_Buf;
        Spi_RN8302_SendByte(Rn8302_TX_Buf[0]);
        checksum = Rn8302_TX_Buf[0];
        Spi_RN8302_SendByte(Rn8302_TX_Buf[1]);
        checksum += Rn8302_TX_Buf[1];
        for(i = 0; i < 48; i++)
        {
            *pReadWaveData = Spi_RN8302_ReadByte();
            checksum += *pReadWaveData;
            pReadWaveData ++;
        }
        checksum = ~checksum;
        if(checksum != Spi_RN8302_ReadByte())err = ERROR;
        if(err != SUCCESS)continue;
        //---��RData�Ĵ������------------------------------------
        Spi_RN8302_SendByte( 0x8C);
        checksum = 0x8C;
        temp = 0x10;
        Spi_RN8302_SendByte( temp );
        checksum += temp;
        for(i = 4 ; i > 0 ; i--)
        {
            temp = Spi_RN8302_ReadByte();
            if(48 >= i)
            {
                if(temp != pReadWaveData[48 - i])
                {
                    err = ERROR;
                    break;
                }
            }
            checksum += temp;
        }
        if(err == SUCCESS)
        {
            checksum = ~checksum;
            temp = Spi_RN8302_ReadByte();
            if(temp != checksum)  err = ERROR;
        }
    }
    RN_SPI_CSN_H;
    return(err);
}


/******************************************************************************

  * *   ��������: RN8302Init(void)

  * *   ����˵��: RN8302��ʼ���������ָ����桢��λУ��ϵ����������

  * *   �������: ��

  * *   �������: ��

  * *   ����ֵ:   ��

  ****************************************************************************/
void RN8302Init(void)
{
    int i;
    int ph;
    // ��оƬID
    RN8302RD(&CFG_StatusREG.DeciceID);
    if (CFG_StatusREG.DeciceID.data != 0x830200)
    {
        return;
    }


    // дʹ��
    CFG_StatusREG.WREN.data = WRENABLE;
    RN8302WR(&CFG_StatusREG.WREN);

    // �л���emmģʽ
    CFG_StatusREG.WMSW.data = EMMOD;
    RN8302WR(&CFG_StatusREG.WMSW);

    // �����λ�������дʹ��
    CFG_StatusREG.SOFT_RST.data = SOFTRST;
    RN8302WR(&CFG_StatusREG.SOFT_RST);

    for (i = 0; i < 50000; i++)
    {
        __ASM volatile ("nop");
    }
    // дʹ��
    CFG_StatusREG.WREN.data = WRENABLE;
    RN8302WR(&CFG_StatusREG.WREN);

    // �л���emmģʽ
    CFG_StatusREG.WMSW.data = EMMOD;
    RN8302WR(&CFG_StatusREG.WMSW);


    // ϵ���ָ�
    CFG_StatusREG.HFConst1.data = g_tParam.RN_Coefficients.HFConst1;
    RN8302WR(&CFG_StatusREG.HFConst1);

    // ϵ���ָ�
    CFG_StatusREG.HFConst2.data = g_tParam.RN_Coefficients.HFConst1;
    RN8302WR(&CFG_StatusREG.HFConst2);

    // GAIN_1/GAIN_2/GAIN_4/GAIN_8

    // ADCͨ����������-----------------IN-----------IC----------IB---------IA---------UC---------UB--------UA---
    CFG_StatusREG.ADCREG.data = GAIN_1 << 12 | GAIN_1 << 10 | GAIN_1 << 8 | GAIN_1 << 6 | GAIN_1 << 4 | GAIN_1 << 2 | GAIN_1;
    RN8302WR(&CFG_StatusREG.ADCREG);

    if(g_tParam.CtrlParam.NetMode == N34)
    {
        CFG_StatusREG.PRTH1L.data = g_tParam.RN_Coefficients.PRTH1L;
        RN8302WR(&CFG_StatusREG.PRTH1L);
        CFG_StatusREG.PRTH1H.data = g_tParam.RN_Coefficients.PRTH1H;
        RN8302WR(&CFG_StatusREG.PRTH1H);
        CFG_StatusREG.PRTH2L.data = g_tParam.RN_Coefficients.PRTH2L;
        RN8302WR(&CFG_StatusREG.PRTH2L);
        CFG_StatusREG.PRTH2H.data = g_tParam.RN_Coefficients.PRTH2H;
        RN8302WR(&CFG_StatusREG.PRTH2H);

        for (ph = 0; ph < 3; ph++)
        {
            // ����У׼��ѹ�������
            CFG_StatusREG.GSU[ph].data = g_tParam.RN_Coefficients.GSU[ph];
            RN8302WR(&CFG_StatusREG.GSU[ph]);
            // ����У׼�����������
            CFG_StatusREG.GSI[ph].data = g_tParam.RN_Coefficients.GSI[ph];
            RN8302WR(&CFG_StatusREG.GSI[ph]);
            // ������λУ����
            CFG_StatusREG.PHSI[ph].data = g_tParam.RN_Coefficients.PHSI[ph];
            RN8302WR(&CFG_StatusREG.PHSI[ph]);   //ͨ����λ
        }
        // ���������
        CFG_StatusREG.CFCFG.data = 0x043210;
        RN8302WR(&CFG_StatusREG.CFCFG);

        // ��������
        CFG_StatusREG.MODSEL.data = 0x00;
        RN8302WR(&CFG_StatusREG.MODSEL);
    }
    else if(g_tParam.CtrlParam.NetMode == N33)
    {
        for (ph = 0; ph < 3; ph++)
        {
            // ����У׼��ѹ�������
            CFG_StatusREG.GSU[ph].data = g_tParam.RN_Coefficients.GSU[ph];
            RN8302WR(&CFG_StatusREG.GSU[ph]);
            // ����У׼�����������
            CFG_StatusREG.GSI[ph].data = g_tParam.RN_Coefficients.GSI[ph];
            RN8302WR(&CFG_StatusREG.GSI[ph]);
        }
        CFG_StatusREG.P_PHSL[PH_A].data = g_tParam.RN_Coefficients.P_PHSL[PH_A];
        RN8302WR(&CFG_StatusREG.P_PHSL[PH_A]);   //ͨ����λ

        CFG_StatusREG.P_PHSL[PH_C].data = g_tParam.RN_Coefficients.P_PHSL[PH_C];
        RN8302WR(&CFG_StatusREG.P_PHSL[PH_C]);   //ͨ����λ

        CFG_StatusREG.Q_PHSL[PH_A].data = g_tParam.RN_Coefficients.P_PHSL[PH_A];
        RN8302WR(&CFG_StatusREG.Q_PHSL[PH_A]);   //ͨ����λ

        CFG_StatusREG.Q_PHSL[PH_C].data = g_tParam.RN_Coefficients.P_PHSL[PH_C];
        RN8302WR(&CFG_StatusREG.Q_PHSL[PH_C]);

        // ���������
        CFG_StatusREG.CFCFG.data = 0x043210;
        RN8302WR(&CFG_StatusREG.CFCFG);

        // ��������
        CFG_StatusREG.MODSEL.data = 0x33;
        RN8302WR(&CFG_StatusREG.MODSEL);
    }
    //�����Ĵ�����������
    CFG_StatusREG.EMUCFG.data = 0x400000;
    //�����Ĵ��������ۼ�
    //CFG_StatusREG.EMUCFG.data = 0x480000;
    RN8302WR(&CFG_StatusREG.EMUCFG);

    //�������ƼĴ���������ʹ�ܸ����й����޹���������г�����ܼ���
    CFG_StatusREG.EMUCON.data = 0x777777;
    RN8302WR(&CFG_StatusREG.EMUCON);

    // У��ͼĴ���1
    RN8302RD(&CFG_StatusREG.CheckSum1);

    //д����
    CFG_StatusREG.WREN.data = WRDISABLE;
    RN8302WR(&CFG_StatusREG.WREN);
}

/******************************************************************************

  * *   ��������: RN8302InitAdjust(void)

  * *   ����˵��: RN8302��ʼ���������ָ����桢��λУ��ϵ����������

  * *   �������: ��

  * *   �������: ��

  * *   ����ֵ:   ��

  ****************************************************************************/
void RN8302InitAdjust(void)
{
    int i;

    //��оƬID
    RN8302RD(&CFG_StatusREG.DeciceID);
    if (CFG_StatusREG.DeciceID.data != 0x830200)
    {
        return;
    }
    //дʹ��
    CFG_StatusREG.WREN.data = WRENABLE;
    RN8302WR(&CFG_StatusREG.WREN);

    //�л���emmģʽ
    CFG_StatusREG.WMSW.data = EMMOD;
    RN8302WR(&CFG_StatusREG.WMSW);

    //�����λ�������дʹ��
    CFG_StatusREG.SOFT_RST.data = SOFTRST;
    RN8302WR(&CFG_StatusREG.SOFT_RST);

    for (i = 0; i < 4000; i++)
    {
        __ASM volatile ("nop");
    }
    //дʹ��
    CFG_StatusREG.WREN.data = WRENABLE;
    RN8302WR(&CFG_StatusREG.WREN);

    //�л���emmģʽ
    CFG_StatusREG.WMSW.data = EMMOD;
    RN8302WR(&CFG_StatusREG.WMSW);

    if(g_tParam.CtrlParam.NetMode == N34)
    {
        // ��������
        CFG_StatusREG.MODSEL.data = 0x00;
        RN8302WR(&CFG_StatusREG.MODSEL);
    }
    else if(g_tParam.CtrlParam.NetMode == N33)
    {
        // ��������
        CFG_StatusREG.MODSEL.data = 0x33;
        RN8302WR(&CFG_StatusREG.MODSEL);
    }

    //�����Ĵ�����������
    CFG_StatusREG.EMUCFG.data = 0x400000;
    RN8302WR(&CFG_StatusREG.EMUCFG);

    //�������ƼĴ���������ʹ�ܸ����й����޹���������г�����ܼ���
    CFG_StatusREG.EMUCON.data = 0x777777;
    RN8302WR(&CFG_StatusREG.EMUCON);

    // У��ͼĴ���1
    RN8302RD(&CFG_StatusREG.CheckSum1);

    //д����
    CFG_StatusREG.WREN.data = WRDISABLE;
    RN8302WR(&CFG_StatusREG.WREN);
}

#define RATIED_VAL_U  22000     /* ���ѹ 0.01*/
#define RATIED_VAL_I  50000     /* ����� 0.0001*/
#define RATIED_VAL_P  (220*5*100)     /* 1.0ʱ��й� 0.01*/
#define RATIED_VAL_HALFP  (0.5*220*5*10)     /* 0.5Lʱ��й� 0.1*/
#define STANDARD_VAL_U  20000000     /* ���ѹ��׼�Ĵ���ֵ */
//#define STANDARD_VAL_I  70000000     /* �������׼�Ĵ���ֵ */
#define STANDARD_VAL_I  8000000     /* �������׼�Ĵ���ֵ */
//#define STANDARD_VAL_P  166893005     /* 1.0Lʱ��й���׼�Ĵ���ֵ 20000000*70000000 /2^23*/
#define STANDARD_VAL_P  19073486     /* 1.0Lʱ��й���׼�Ĵ���ֵ 20000000*8000000 /2^23*/
#define STANDARD_VAL_HALFP  (STANDARD_VAL_P/2)     /* 0.5Lʱ��й���׼�Ĵ���ֵ */
#define POWER15 32768 /* 2^15 */
#define POWER16 65536 /* 2^16 */
#define POWER23 8388608 /* 2^23 */
#define POWER24 16777216 /* 2^24 */


/******************************************************************************

  * *   ��������: Refresh_AnalogData()

  * *   ����˵��: ��ȡRN8302�е����ݣ�ˢ������

  * *   �������: ��

  * *   �������: ��

  * *   ����ֵ:   ��

  ****************************************************************************/
int Phase_U[3];
int Phase_I[3];
int IbAngletmp;
float Umax,Umin,Imax,Imin;
void RN8032_Updata(void)
{
    u64 u64_temp;
    float ftemp,ftemp2;
    int ph;
    int ntemp;

    u16 Direct;
    int ba_Angle,cb_Angle,ac_Angle;

    float Hutemp,Futemp;

    /*--------------------��������--------------------*/
    if(RN8302RD(&CFG_StatusREG.SYSSR))
    {
        __NOP();
    }
    for (ph = 0; ph < 3; ph++)
    {
        /*------ ��ѹ��� ------*/
        if(RN8302RD(&Fundwave_data.YU[ph]))
        {
            ftemp = (float)Fundwave_data.YU[ph].data;
            ntemp =  (int)(ftemp / POWER24 * 3600);
            Phase_U[ph] = ntemp;
            vg_Power2_Val.Real22_Val[ph].U_Phase = ntemp/10;
        }
        /*------ ������� ------*/
        if(RN8302RD(&Fundwave_data.YI[ph]))
        {
            ftemp = (float)Fundwave_data.YI[ph].data;
            ntemp =  (int)(ftemp / POWER24 * 3600);
            Phase_I[ph] = ntemp;
            vg_Power2_Val.Real22_Val[ph].I_Phase = ntemp/10;
        }
        /*------ ���ѹ ------*/
        if(RN8302RD(&Fullwave_data.U[ph]))
        {
            ftemp = Fullwave_data.U[ph].data;
            //ftemp = 20000000;
            ftemp2 = ftemp * RATIED_VAL_U / STANDARD_VAL_U;       // ABC���ѹ��Чֵ
            vg_Power_Val.Real2_Val[ph].U = ftemp2;
            vg_Power2_Val.Real22_Val[ph].U = (int)(ftemp2/10);
            vg_Read_Val.Real_Read_Val[ph].U = (int)ftemp2;
            if (vg_Power_Val.Real2_Val[ph].U < 100) // 1V    22000 = 220V
            {
                vg_Power_Val.Real2_Val[ph].U = 0;
                vg_Power2_Val.Real22_Val[ph].U = 0;
                vg_Read_Val.Real_Read_Val[ph].U = 0;
            }
            vg_Power_Val.Real2_Val[ph].U = vg_Power_Val.Real2_Val[ph].U * g_tParam.CtrlParam.PTNum;

            RtuPrimaryData[Index_1_Ua + ph] = vg_Power_Val.Real2_Val[ph].U/100;
            RtuSecondaryData[Index_2_Ua + ph] = vg_Power2_Val.Real22_Val[ph].U;
            // Max
            if((vg_Power2_Val.Real22_Val[ph].U > vg_DemMax_Val[SoeIndex.MaxIndex].Max_U) && (g_MaxDemEnable == TRUE))
            {
                vg_DemMax_Val[SoeIndex.MaxIndex].Max_U = vg_Power2_Val.Real22_Val[ph].U;
                vg_DemMax_Val[SoeIndex.MaxIndex].mUTime = g_SOETime;
                MaxFramWriteEnble = TRUE;
            }
        }
        /*------ ����� ------*/
        if(RN8302RD(&Fullwave_data.I[ph]))
        {
            ftemp = Fullwave_data.I[ph].data;
            ftemp2 = ftemp * RATIED_VAL_I / STANDARD_VAL_I;         // ABC�������Чֵ
            vg_Power_Val.Real2_Val[ph].I = ftemp2;
            vg_Power2_Val.Real22_Val[ph].I = (int)(ftemp2/10);
            vg_Read_Val.Real_Read_Val[ph].I = (u32)ftemp2;
            if (vg_Power_Val.Real2_Val[ph].I < 50)  //5ma
            {
                vg_Power_Val.Real2_Val[ph].I = 0;
                vg_Power2_Val.Real22_Val[ph].I = 0;
                vg_Read_Val.Real_Read_Val[ph].I = 0;
            }
            vg_Power_Val.Real2_Val[ph].I = vg_Power_Val.Real2_Val[ph].I * g_tParam.CtrlParam.CTNum;

            RtuPrimaryData[Index_1_Ia + ph] = vg_Power_Val.Real2_Val[ph].I/10000;
            RtuSecondaryData[Index_2_Ia + ph] = vg_Power2_Val.Real22_Val[ph].I;
            // Max
            if((vg_Power2_Val.Real22_Val[ph].I > vg_DemMax_Val[SoeIndex.MaxIndex].Max_I) && (g_MaxDemEnable == TRUE))
            {
                vg_DemMax_Val[SoeIndex.MaxIndex].Max_I = vg_Power2_Val.Real22_Val[ph].I;
                vg_DemMax_Val[SoeIndex.MaxIndex].mITime = g_SOETime;
                MaxFramWriteEnble = TRUE;
            }
        }
        /*------ �������� ------*/
        if(RN8302RD(&Fullwave_data.Pf[ph]))  //���λΪ�й����ʷ���λ
        {
            if(Fullwave_data.Pf[ph].data & 0x800000)
            {
                u64_temp = (Fullwave_data.Pf[ph].data ^ 0xffffff) + 1;
                ftemp = (float)u64_temp / POWER23;
                ftemp2 = ftemp * 10000 +5;                                // ABC�๦������
                vg_Power_Val.Real2_Val[ph].PF = ftemp2/10;
                vg_Power2_Val.Real22_Val[ph].PF = (int)(ftemp2/10);
                vg_Read_Val.Real_Read_Val[ph].PF = (u16)(ftemp2/10);
            }
            else
            {
                u64_temp = Fullwave_data.Pf[ph].data;
                ftemp = (float)u64_temp / POWER23;
                ftemp2 = ftemp * 10000 +5;                                // ABC�๦������
                vg_Power_Val.Real2_Val[ph].PF = ftemp2/10;
                vg_Power2_Val.Real22_Val[ph].PF = (int)(ftemp2/10);
                vg_Read_Val.Real_Read_Val[ph].PF = (u16)(ftemp2/10);
            }
        }
        /*------ �й����� ------*/
        if(RN8302RD(&Fullwave_data.P[ph]))
        {
            if(Fullwave_data.P[ph].data & 0x80000000)
            {
                ntemp = (((Fullwave_data.P[ph].data ^ 0xffffffff) + 1) & 0x7fffffff);            // A���й�����
                ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
                if(ftemp < 0.05)
                {
                    ftemp = 0;
                }
                vg_Read_Val.Real_Read_Val[ph].P = (s32)ftemp;
                vg_Power_Val.Real2_Val[ph].P = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
                vg_Power2_Val.Real22_Val[ph].P = (int)(ftemp/10);
            }
            else
            {
                ntemp = Fullwave_data.P[ph].data;
                ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
                if(ftemp < 0.05)
                {
                    ftemp = 0;
                }
                vg_Read_Val.Real_Read_Val[ph].P = (s32)ftemp;
                vg_Power_Val.Real2_Val[ph].P = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
                vg_Power2_Val.Real22_Val[ph].P = (int)(ftemp/10);
            }
        }
        /*------ �޹����� ------*/
        if(RN8302RD(&Fullwave_data.Q[ph]))
        {
            if(Fullwave_data.Q[ph].data & 0x80000000)
            {
                ntemp = (((Fullwave_data.Q[ph].data ^ 0xffffffff) + 1) & 0x7fffffff);            // A���޹�����  ��
                ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
                if(ftemp < 0.05)
                {
                    ftemp = 0;
                }
                vg_Read_Val.Real_Read_Val[ph].Q = (s32)ftemp;
                vg_Power_Val.Real2_Val[ph].Q = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
                vg_Power2_Val.Real22_Val[ph].Q = (int)(ftemp/10);
            }
            else
            {
                ntemp = Fullwave_data.Q[ph].data;
                ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
                if(ftemp < 0.05)
                {
                    ftemp = 0;
                }
                vg_Read_Val.Real_Read_Val[ph].Q = (s32)ftemp;
                vg_Power_Val.Real2_Val[ph].Q = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
                vg_Power2_Val.Real22_Val[ph].Q = (int)(ftemp/10);
            }
        }
        /*------ ���ڹ��� ------*/
        if(RN8302RD(&Fullwave_data.S[ph]))
        {
            ntemp = Fullwave_data.S[ph].data;                      // A�����ڹ���
            ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
            if(ftemp < 0.05)
            {
                ftemp = 0;
            }
            vg_Read_Val.Real_Read_Val[ph].S = (s32)ftemp;
            vg_Power_Val.Real2_Val[ph].S = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
            vg_Power2_Val.Real22_Val[ph].S = (int)(ftemp/10);
        }

        /*------ ���ʷ��� ------*/
        if(RN8302RD(&CFG_StatusREG.PQSign))
        {
            Direct = CFG_StatusREG.PQSign.data;
            if(Direct & (0x0001 << ph))  // �й�Ϊ��
            {
                vg_Power_Val.Real2_Val[ph].P = -vg_Power_Val.Real2_Val[ph].P;
                vg_Read_Val.Real_Read_Val[ph].P = -vg_Read_Val.Real_Read_Val[ph].P;
                vg_Power2_Val.Real22_Val[ph].P = -vg_Power2_Val.Real22_Val[ph].P;
            }
            if(Direct & (0x0001 << (ph+4))) // �޹�Ϊ��
            {
                vg_Power_Val.Real2_Val[ph].Q = -vg_Power_Val.Real2_Val[ph].Q;
                vg_Power2_Val.Real22_Val[ph].Q = -vg_Power2_Val.Real22_Val[ph].Q;
                vg_Read_Val.Real_Read_Val[ph].Q = -vg_Read_Val.Real_Read_Val[ph].Q;
            }
            if(((!(Direct & (0x0001 << ph))) && (Direct & (0x0001 << (ph+4)))) ||\
            ((Direct & (0x0001 << ph)) && (!(Direct & (0x0001 << (ph+4))))))
            {
                vg_Power_Val.Real2_Val[ph].PF = -vg_Power_Val.Real2_Val[ph].PF;
                vg_Power2_Val.Real22_Val[ph].PF = -vg_Power2_Val.Real22_Val[ph].PF;
                vg_Read_Val.Real_Read_Val[ph].PF = -vg_Read_Val.Real_Read_Val[ph].PF;
            }
        }

        if (vg_Power_Val.Real2_Val[ph].PF <= -1000)
        {
            vg_Power_Val.Real2_Val[ph].PF = 1000;
            vg_Power2_Val.Real22_Val[ph].PF = 1000;
            vg_Read_Val.Real_Read_Val[ph].PF = 1000;
        }
        if (vg_Power_Val.Real2_Val[ph].U < 100)
        {
            vg_Power_Val.Real2_Val[ph].PF = 0;
            vg_Power2_Val.Real22_Val[ph].PF = 0;
            vg_Read_Val.Real_Read_Val[ph].PF = 0;
        }
        if (vg_Power_Val.Real2_Val[ph].I < 20)
        {
            vg_Power_Val.Real2_Val[ph].PF = 0;
            vg_Power2_Val.Real22_Val[ph].PF = 0;
            vg_Read_Val.Real_Read_Val[ph].PF = 0;
        }
        if (vg_Power_Val.Real2_Val[ph].PF == 1000)
        {
            vg_Power_Val.Real2_Val[ph].Q = 0;
            vg_Power2_Val.Real22_Val[ph].Q = 0;
            vg_Read_Val.Real_Read_Val[ph].Q = 0;
        }

        RtuPrimaryData[Index_1_Pa + ph] = vg_Power_Val.Real2_Val[ph].P/100000;
        RtuSecondaryData[Index_2_Pa + ph] = vg_Power2_Val.Real22_Val[ph].P/10;

        RtuPrimaryData[Index_1_Qa + ph] = vg_Power_Val.Real2_Val[ph].Q/100000;
        RtuSecondaryData[Index_2_Qa + ph] = vg_Power2_Val.Real22_Val[ph].Q/10;

        RtuPrimaryData[Index_1_Sa + ph] = vg_Power_Val.Real2_Val[ph].S/100000;
        RtuSecondaryData[Index_2_Sa + ph] = vg_Power2_Val.Real22_Val[ph].S/10;

        RtuSecondaryData[Index_2_PFa + ph] = vg_Power2_Val.Real22_Val[ph].PF;
#ifdef _LEDHarm_
        /*------ ��г������ ------*/
        if (vg_Power_Val.Real2_Val[ph].U < 100)
        {
            vg_Power_Val.Real2_Val[ph].THDU = 0;
            vg_Power2_Val.Real22_Val[ph].THDU = 0;
        }
        else
        {
            if(RN8302RD(&Fundwave_data.HU[ph]))  //г����ѹ��Чֵ
            {
                ftemp = Fundwave_data.HU[ph].data;
                ftemp2 = ftemp * RATIED_VAL_U / STANDARD_VAL_U;       // ABC���ѹ��Чֵ
                vg_Power_Val.Real2_Val[ph].UH = ftemp2 * g_tParam.CtrlParam.PTNum;
                vg_Power2_Val.Real22_Val[ph].UH = (int)(ftemp2/10);
                if(RN8302RD(&Fundwave_data.FU[ph]))  // ������ѹ��Чֵ
                {
                    vg_Power_Val.Real2_Val[ph].THDU = (float)Fundwave_data.HU[ph].data * 10000 / (float)Fundwave_data.FU[ph].data;
                    vg_Power2_Val.Real22_Val[ph].THDU = (int)vg_Power_Val.Real2_Val[ph].THDU;
                }
                else
                {
                    vg_Power_Val.Real2_Val[ph].THDU = 0;
                    vg_Power2_Val.Real22_Val[ph].THDU = 0;
                }
            }
            else
            {
                vg_Power_Val.Real2_Val[ph].THDU = 0;
                vg_Power2_Val.Real22_Val[ph].THDU = 0;
            }
        }

        if (vg_Power_Val.Real2_Val[ph].I < 20)
        {
            vg_Power_Val.Real2_Val[ph].THDI = 0;
            vg_Power2_Val.Real22_Val[ph].THDI = 0;
        }
        else
        {
            if(RN8302RD(&Fundwave_data.HI[ph]))
            {
                ftemp = Fundwave_data.HI[ph].data;
                ftemp2 = ftemp * RATIED_VAL_I / STANDARD_VAL_I;         // ABC�������Чֵ
                vg_Power_Val.Real2_Val[ph].IH = ftemp2 * g_tParam.CtrlParam.CTNum;
                vg_Power2_Val.Real22_Val[ph].IH = (int)(ftemp2/10);
                if(RN8302RD(&Fundwave_data.FI[ph]))
                {
                    vg_Power_Val.Real2_Val[ph].THDI = (float)Fundwave_data.HI[ph].data * 10000 / (float)Fundwave_data.FI[ph].data;
                    vg_Power2_Val.Real22_Val[ph].THDI = (int)vg_Power_Val.Real2_Val[ph].THDI;
                }
                else
                {
                    vg_Power_Val.Real2_Val[ph].THDI = 0;
                    vg_Power2_Val.Real22_Val[ph].THDI = 0;
                }
            }
            else
            {
                vg_Power_Val.Real2_Val[ph].THDI = 0;
                vg_Power2_Val.Real22_Val[ph].THDI = 0;
            }
        }
#endif
    }

    /*------ �ߵ�ѹ ------*/
    ba_Angle = Phase_U[1] - Phase_U[0];
    cb_Angle = Phase_U[2] - Phase_U[1];
    ac_Angle = 3600 - Phase_U[2];

    vg_Power_Val.Real2_Val[0].LineU = (float)LineCalcFunc(0,ba_Angle);
    vg_Power_Val.Real2_Val[1].LineU = (float)LineCalcFunc(1,cb_Angle);
    vg_Power_Val.Real2_Val[2].LineU = (float)LineCalcFunc(2,ac_Angle);

    vg_Power2_Val.Real22_Val[0].LineU = (int)(vg_Power_Val.Real2_Val[0].LineU/10);
    vg_Power2_Val.Real22_Val[1].LineU = (int)(vg_Power_Val.Real2_Val[1].LineU/10);
    vg_Power2_Val.Real22_Val[2].LineU = (int)(vg_Power_Val.Real2_Val[2].LineU/10);

	vg_Power2_Val.Real22_Val[0].LineU = (int)(vg_Power2_Val.Real22_Val[0].LineU /g_tParam.CtrlParam.PTNum);
    vg_Power2_Val.Real22_Val[1].LineU = (int)(vg_Power2_Val.Real22_Val[1].LineU /g_tParam.CtrlParam.PTNum);
    vg_Power2_Val.Real22_Val[2].LineU = (int)(vg_Power2_Val.Real22_Val[2].LineU /g_tParam.CtrlParam.PTNum);

    for(u8 jIndex=0; jIndex<3; jIndex++)
    {
        RtuPrimaryData[Index_1_Uab + jIndex] = vg_Power_Val.Real2_Val[jIndex].LineU/100;
        RtuSecondaryData[Index_2_Uab + jIndex] = vg_Power2_Val.Real22_Val[jIndex].LineU;

        // Max
        if((vg_Power2_Val.Real22_Val[jIndex].LineU > vg_DemMax_Val[SoeIndex.MaxIndex].Max_UL) && (g_MaxDemEnable == TRUE))
        {
            vg_DemMax_Val[SoeIndex.MaxIndex].Max_UL = vg_Power2_Val.Real22_Val[jIndex].LineU;
            vg_DemMax_Val[SoeIndex.MaxIndex].mULTime = g_SOETime;
            MaxFramWriteEnble = TRUE;
        }
    }

    /*if(vg_Power_Val.Real2_Val[PH_B].I < 50)
    {
        IbEnbleFlag = FALSE;
    }
    else
    {
        IbEnbleFlag = TRUE;
    }*/

    /*------ N33����B����� --*/
    if((g_tParam.CtrlParam.NetMode == N33) && (vg_Power_Val.Real2_Val[PH_B].I < 50))
    {
        IbAngletmp = abs(Phase_I[PH_C] - Phase_I[PH_A]);
        if(IbAngletmp > 1800)
            IbAngletmp = 3600 - IbAngletmp;
		//IbAngletmp = 1200;
        vg_Power_Val.Real2_Val[PH_B].I = (float)LineCalcFunc(3,IbAngletmp);
        vg_Read_Val.Real_Read_Val[PH_B].I = (u32)(vg_Power_Val.Real2_Val[PH_B].I/g_tParam.CtrlParam.CTNum);
        vg_Power2_Val.Real22_Val[PH_B].I = (int)(vg_Power_Val.Real2_Val[PH_B].I/10);
        vg_Power2_Val.Real22_Val[PH_B].I = (int)(vg_Power2_Val.Real22_Val[PH_B].I/g_tParam.CtrlParam.CTNum);
    }

    /*------ ƽ�����ѹ ------*/
    vg_Power_Val.Uavr = (vg_Power_Val.Real2_Val[0].U + vg_Power_Val.Real2_Val[1].U + vg_Power_Val.Real2_Val[2].U)/3;
    vg_Power2_Val.Uavr = (vg_Power2_Val.Real22_Val[0].U + vg_Power2_Val.Real22_Val[1].U + vg_Power2_Val.Real22_Val[2].U)/3;
    /*------ ƽ���ߵ�ѹ ------*/
    vg_Power_Val.ULavr = (vg_Power_Val.Real2_Val[0].LineU + vg_Power_Val.Real2_Val[1].LineU+ vg_Power_Val.Real2_Val[2].LineU)/3;
    vg_Power2_Val.ULavr = (vg_Power2_Val.Real22_Val[0].LineU + vg_Power2_Val.Real22_Val[1].LineU + vg_Power2_Val.Real22_Val[2].LineU)/3;
    /*------ ƽ������� ------*/
    vg_Power_Val.Iavr = (vg_Power_Val.Real2_Val[0].I + vg_Power_Val.Real2_Val[1].I + vg_Power_Val.Real2_Val[2].I)/3;
    vg_Power2_Val.Iavr = (vg_Power2_Val.Real22_Val[0].I + vg_Power2_Val.Real22_Val[1].I + vg_Power2_Val.Real22_Val[2].I)/3;

    RtuPrimaryData[Index_1_Uavr] = vg_Power_Val.Uavr/100;
    RtuSecondaryData[Index_2_Uavr] = vg_Power2_Val.Uavr;

    RtuPrimaryData[Index_1_ULavr] = vg_Power_Val.ULavr/100;
    RtuSecondaryData[Index_2_ULavr] = vg_Power2_Val.ULavr;

    RtuPrimaryData[Index_1_Iavr] = vg_Power_Val.Iavr/10000;
    RtuSecondaryData[Index_2_Iavr] = vg_Power2_Val.Iavr;

    /*------ ��ƽ��ȼ��� ------*/
    if(g_tParam.CtrlParam.NetMode == N33)
    {
        Umax = (vg_Power_Val.Real2_Val[0].LineU > vg_Power_Val.Real2_Val[1].LineU)?vg_Power_Val.Real2_Val[0].LineU:vg_Power_Val.Real2_Val[1].LineU;
        Umax = (Umax > vg_Power_Val.Real2_Val[2].LineU)? Umax:vg_Power_Val.Real2_Val[2].LineU;

        Umin = (vg_Power_Val.Real2_Val[0].LineU< vg_Power_Val.Real2_Val[1].LineU)?vg_Power_Val.Real2_Val[0].LineU:vg_Power_Val.Real2_Val[1].LineU;
        Umin = (Umin < vg_Power_Val.Real2_Val[2].LineU)? Umin:vg_Power_Val.Real2_Val[2].LineU;

        vg_Power2_Val.U_Imb = (int)((Umax - Umin)*10000/Umax);  //0.1%
        RtuSecondaryData[Index_2_Uimb] = vg_Power2_Val.U_Imb;
    }
    else
    {
        Umax = (vg_Power_Val.Real2_Val[0].U > vg_Power_Val.Real2_Val[1].U)?vg_Power_Val.Real2_Val[0].U:vg_Power_Val.Real2_Val[1].U;
        Umax = (Umax > vg_Power_Val.Real2_Val[2].U)? Umax:vg_Power_Val.Real2_Val[2].U;

        Umin = (vg_Power_Val.Real2_Val[0].U < vg_Power_Val.Real2_Val[1].U)?vg_Power_Val.Real2_Val[0].U:vg_Power_Val.Real2_Val[1].U;
        Umin = (Umin < vg_Power_Val.Real2_Val[2].U)? Umin:vg_Power_Val.Real2_Val[2].U;

        vg_Power2_Val.U_Imb = (int)((Umax - Umin)*10000/Umax);  //0.1%
        RtuSecondaryData[Index_2_Uimb] = vg_Power2_Val.U_Imb;
    }

    Imax = (vg_Power_Val.Real2_Val[0].I > vg_Power_Val.Real2_Val[1].I)?vg_Power_Val.Real2_Val[0].I:vg_Power_Val.Real2_Val[1].I;
    Imax = (Imax > vg_Power_Val.Real2_Val[2].I)? Imax:vg_Power_Val.Real2_Val[2].I;

    Imin = (vg_Power_Val.Real2_Val[0].I < vg_Power_Val.Real2_Val[1].I)?vg_Power_Val.Real2_Val[0].I:vg_Power_Val.Real2_Val[1].I;
    Imin = (Imin < vg_Power_Val.Real2_Val[2].I)? Imin:vg_Power_Val.Real2_Val[2].I;

    vg_Power2_Val.I_Imb = (int)((Imax - Imin)*10000/Imax);  //0.01%
    RtuSecondaryData[Index_2_Iimb] = vg_Power2_Val.I_Imb;

    /*------ ƽ��г������ ------*/
    Hutemp = (float)(Fundwave_data.HU[PH_A].data + Fundwave_data.HU[PH_B].data + Fundwave_data.HU[PH_C].data)/3;
    Futemp = (float)(Fundwave_data.FU[PH_A].data + Fundwave_data.FU[PH_B].data + Fundwave_data.FU[PH_C].data)/3;
    vg_Power2_Val.UTHavr = (int)(Hutemp*10000/Futemp);

    Hutemp = (float)(Fundwave_data.HI[PH_A].data + Fundwave_data.HI[PH_B].data + Fundwave_data.HI[PH_C].data)/3;
    Futemp = (float)(Fundwave_data.FI[PH_A].data + Fundwave_data.FI[PH_B].data + Fundwave_data.FI[PH_C].data)/3;
    vg_Power2_Val.ITHavr = (int)(Hutemp*10000/Futemp);

    /*------ ���й����� ------*/
    if(RN8302RD(&Fullwave_data.Pt))
    {
        if(Fullwave_data.Pt.data & 0x80000000)
        {
            ntemp = (((Fullwave_data.Pt.data ^ 0xffffffff) + 1) & 0x7fffffff);            // A���й�����
            ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
            if(ftemp < 0.1)
            {
                ftemp = 0;
            }
            vg_Power_Val.Pt = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
            vg_Power2_Val.Pt = (int)(ftemp/10);
        }
        else
        {
            ntemp = Fullwave_data.Pt.data;
            ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
            if(ftemp < 0.1)
            {
                ftemp = 0;
            }
            vg_Power_Val.Pt = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
            vg_Power2_Val.Pt = (int)(ftemp/10);
        }
    }
    /*------ ���޹����� ------*/
    if(RN8302RD(&Fullwave_data.Qt))
    {
        if(Fullwave_data.Qt.data & 0x80000000)
        {
            ntemp = (((Fullwave_data.Qt.data ^ 0xffffffff) + 1) & 0x7fffffff);            // A���޹�����  ��
            ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
            if(ftemp < 0.1)
            {
                ftemp = 0;
            }
            vg_Power_Val.Qt = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
            vg_Power2_Val.Qt = (int)(ftemp/10);
        }
        else
        {
            ntemp = Fullwave_data.Qt.data;
            ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
            if(ftemp < 0.1)
            {
                ftemp = 0;
            }
            vg_Power_Val.Qt = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
            vg_Power2_Val.Qt = (int)(ftemp/10);
        }
    }
    /*------ �����ڹ��� ------*/
    if(RN8302RD(&Fullwave_data.St))
    {
        if(Fullwave_data.St.data & 0x80000000)
        {
            ntemp = (((Fullwave_data.St.data ^ 0xffffffff) + 1) & 0x7fffffff);            // A���޹�����  ��
            ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
            if(ftemp < 0.1)
            {
                ftemp = 0;
            }
            vg_Power_Val.St = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
            vg_Power2_Val.St = (int)(ftemp/10);
        }
        else
        {
            ntemp = Fullwave_data.St.data;
            ftemp = (float)ntemp * RATIED_VAL_P / STANDARD_VAL_P;
            if(ftemp < 0.1)
            {
                ftemp = 0;
            }
            vg_Power_Val.St = ftemp * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
            vg_Power2_Val.St = (int)(ftemp/10);
        }
        // Max
        if((vg_Power2_Val.St > vg_DemMax_Val[SoeIndex.MaxIndex].Max_S) && (g_MaxDemEnable == TRUE))
        {
            vg_DemMax_Val[SoeIndex.MaxIndex].Max_S = vg_Power2_Val.St;
            vg_DemMax_Val[SoeIndex.MaxIndex].mSTime = g_SOETime;
            MaxFramWriteEnble = TRUE;
        }
    }
    /*------ �ܹ������� ------*/
    if(RN8302RD(&Fullwave_data.Pft))
    {
        if(Fullwave_data.Pft.data & 0x800000)
        {
            u64_temp = (Fullwave_data.Pft.data ^ 0xffffff) + 1;
            ftemp = (float)u64_temp / POWER23;
            ftemp2 = ftemp * 10000 +5;                                // ABC�๦������
            vg_Power_Val.PFTA = ftemp2/10;
            vg_Power2_Val.PFTA = (int)ftemp2/10;
        }
        else
        {
            u64_temp = Fullwave_data.Pft.data;
            ftemp = (float)u64_temp / POWER23;
            ftemp2 = ftemp * 10000 +5;                                // ABC�๦������
            vg_Power_Val.PFTA = ftemp2/10;
            vg_Power2_Val.PFTA = (int)ftemp2/10;
        }
    }
    /*------ ���ʷ����ж� ------*/
    if(RN8302RD(&CFG_StatusREG.PQSign))
    {
        Direct = CFG_StatusREG.PQSign.data;
        if(Direct & (0x0001 << 3))  // �й�Ϊ��
        {
            vg_Power_Val.Pt = -vg_Power_Val.Pt;
            vg_Power2_Val.Pt = -vg_Power2_Val.Pt;
        }
		// Max
		if((vg_Power2_Val.Pt > vg_DemMax_Val[SoeIndex.MaxIndex].Max_P) && (g_MaxDemEnable == TRUE))
		{
			vg_DemMax_Val[SoeIndex.MaxIndex].Max_P = vg_Power2_Val.Pt;
			vg_DemMax_Val[SoeIndex.MaxIndex].mPTime = g_SOETime;
			MaxFramWriteEnble = TRUE;
		}
        if(Direct & (0x0001 << 7)) // �޹�Ϊ��
        {
            vg_Power_Val.Qt = -vg_Power_Val.Qt;
            vg_Power2_Val.Qt = -vg_Power2_Val.Qt;
        }
		// Max
		if((vg_Power2_Val.Qt > vg_DemMax_Val[SoeIndex.MaxIndex].Max_Q) && (g_MaxDemEnable == TRUE))
		{
			vg_DemMax_Val[SoeIndex.MaxIndex].Max_Q = vg_Power2_Val.Qt;
			vg_DemMax_Val[SoeIndex.MaxIndex].mQTime = g_SOETime;
			MaxFramWriteEnble = TRUE;
		}
        /*==========================N33 ����================================*/
        if(g_tParam.CtrlParam.NetMode == N33)
        {
            vg_Power_Val.St = sqrt(vg_Power_Val.Pt * vg_Power_Val.Pt + vg_Power_Val.Qt * vg_Power_Val.Qt);
            vg_Power2_Val.St = vg_Power_Val.St/g_tParam.CtrlParam.CTNum / g_tParam.CtrlParam.PTNum /10;
            vg_Power_Val.PFTA = vg_Power_Val.Pt/vg_Power_Val.St * 1000;
            vg_Power2_Val.PFTA = vg_Power_Val.PFTA;
            if(vg_Power_Val.PFTA >1000)
            {
                vg_Power_Val.PFTA = 1000;
                vg_Power2_Val.PFTA = 1000;
            }
        }
        if(vg_Power_Val.PFTA != 1000)
        {
            if(((!(Direct & (0x0001 << 3))) && (Direct & (0x0001 << (3+4)))) ||\
            ((Direct & (0x0001 << 3)) && (!(Direct & (0x0001 << (3+4))))))
            {
                vg_Power_Val.PFTA = -vg_Power_Val.PFTA;  // 1.�й�Ϊ+ �޹�Ϊ-  2.�й�Ϊ- �޹�Ϊ+
                vg_Power2_Val.PFTA = -vg_Power2_Val.PFTA;  // 1.�й�Ϊ+ �޹�Ϊ-  2.�й�Ϊ- �޹�Ϊ+
            }
        }
		if((vg_Power_Val.PFTA >= 1000) || (vg_Power_Val.PFTA <= -1000))
		{
            FourQuadtand &=~0x01;
            FourQuadtand &=~0x02;
		}
		else
		{
            if(Direct & (0x0001 << 3))
            {
                FourQuadtand |= 0x01;
            }
            else
            {
                FourQuadtand &=~0x01;
            }
            if(Direct & (0x0001 << 7))
            {
                FourQuadtand |= 0x02;
            }
            else
            {
                FourQuadtand &=~0x02;
            }
		}
    }
    /*------ �ܹ��������ж� ------*/
    if (vg_Power_Val.PFTA <= -1000)
    {
        vg_Power_Val.PFTA = 1000;
        vg_Power2_Val.PFTA = 1000;
    }
    if ((vg_Power_Val.Real2_Val[0].U < 100) && (vg_Power_Val.Real2_Val[1].U < 100) && (vg_Power_Val.Real2_Val[2].U < 100))
    {
        vg_Power_Val.PFTA = 0;
        vg_Power2_Val.PFTA = 0;
    }
    if ((vg_Power_Val.Real2_Val[0].I < 100) && (vg_Power_Val.Real2_Val[1].I < 100) && (vg_Power_Val.Real2_Val[2].I < 100))
    {
        vg_Power_Val.PFTA = 0;
        vg_Power2_Val.PFTA = 0;
    }
    if (vg_Power_Val.PFTA == 1000)
    {
        vg_Power_Val.Qt = 0;
        vg_Power2_Val.Qt = 0;
        vg_Power_Val.Real2_Val[PH_A].Q = 0;
        vg_Power2_Val.Real22_Val[PH_A].Q = 0;
        vg_Power_Val.Real2_Val[PH_B].Q = 0;
        vg_Power2_Val.Real22_Val[PH_B].Q = 0;
        vg_Power_Val.Real2_Val[PH_C].Q = 0;
        vg_Power2_Val.Real22_Val[PH_C].Q = 0;
    }

    RtuPrimaryData[Index_1_P] = vg_Power_Val.Pt;
    RtuSecondaryData[Index_2_P] = vg_Power2_Val.Pt;
    RtuPrimaryData[Index_1_Q] = vg_Power_Val.Qt;
    RtuSecondaryData[Index_2_Q] = vg_Power2_Val.Qt;
    RtuPrimaryData[Index_1_S] = vg_Power_Val.St;
    RtuSecondaryData[Index_2_S] = vg_Power2_Val.St;

    RtuPrimaryData[Index_1_PF] = vg_Power_Val.PFTA/1000;
    RtuSecondaryData[Index_2_PF] = vg_Power2_Val.PFTA;

    RtuSecondaryData[Index_2_Pavr] = vg_Power2_Val.Pt/30;
    RtuSecondaryData[Index_2_Qavr] = vg_Power2_Val.Qt/30;
    RtuSecondaryData[Index_2_Savr] = vg_Power2_Val.St/30;


    /*------ Ƶ�� ------*/
    if(RN8302RD(&Fundwave_data.UFrequence)) // fosc*8/reg,������λС��,(8.192*10^6)*8
    {
        vg_Power_Val.Freq = (65536000000 / Fundwave_data.UFrequence.data +8 )/10 ;  // ��ѹ��Ƶ��
        vg_Power2_Val.Freq = (int)vg_Power_Val.Freq;
        if ((vg_Power_Val.Real2_Val[0].U < 500) && (vg_Power_Val.Real2_Val[1].U < 500) && (vg_Power_Val.Real2_Val[2].U < 500))
        {
            vg_Power_Val.Freq = 0;
            vg_Power2_Val.Freq = 0;
        }
    }

    RtuPrimaryData[Index_1_Hz] = vg_Power_Val.Freq/100;
    RtuSecondaryData[Index_2_Hz] = vg_Power2_Val.Freq;

    if(RN8302RD(&Fullwave_data.PosEPt))   // �����й�����
    {
        ElectricEnergy.PosEPT += ((float)Fullwave_data.PosEPt.data)/3200 * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
        vg_Power2_Val.PosEPT = (u32)(ElectricEnergy.PosEPT*1000/g_tParam.CtrlParam.CTNum / g_tParam.CtrlParam.PTNum);
    }
    if(RN8302RD(&Fullwave_data.PosEQt))   // �����޹�����
    {
        ElectricEnergy.PosEQT += ((float)Fullwave_data.PosEQt.data)/3200 * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
        vg_Power2_Val.PosEQT = (u32)(ElectricEnergy.PosEQT*1000/g_tParam.CtrlParam.CTNum / g_tParam.CtrlParam.PTNum);
    }
    if(RN8302RD(&Fullwave_data.NegEPt))   // �����й�����
    {
        ElectricEnergy.NegEPT += ((float)Fullwave_data.NegEPt.data/3200) * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
        vg_Power2_Val.EPT = (u32)(ElectricEnergy.NegEPT * 1000/g_tParam.CtrlParam.CTNum / g_tParam.CtrlParam.PTNum);
    }
    if(RN8302RD(&Fullwave_data.NegEQt))   // �����޹�����
    {
        ElectricEnergy.NegEQT += ((float)Fullwave_data.NegEQt.data/3200) * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
        vg_Power2_Val.EQT = (u32)(ElectricEnergy.NegEQT * 1000/g_tParam.CtrlParam.CTNum / g_tParam.CtrlParam.PTNum);
    }

    if(RN8302RD(&Fullwave_data.ESt))   // S����
    {
        ElectricEnergy.EST += ((float)Fullwave_data.ESt.data)/3200 * g_tParam.CtrlParam.CTNum * g_tParam.CtrlParam.PTNum;
        vg_Power2_Val.EST = (u32)(ElectricEnergy.EST*1000/g_tParam.CtrlParam.CTNum / g_tParam.CtrlParam.PTNum);
    }

    RtuPrimaryData[Index_1_PEPT] = ElectricEnergy.PosEPT;
    RtuPrimaryData[Index_1_PEQT] = ElectricEnergy.PosEQT;
    RtuPrimaryData[Index_1_NEPT] = ElectricEnergy.NegEPT;
    RtuPrimaryData[Index_1_NEQT] = ElectricEnergy.NegEQT;

    RtuSecondaryData[Index_2_PEPT] = DWORD_HI(vg_Power2_Val.PosEPT);
    RtuSecondaryData[Index_2_PEPT + 1] = DWORD_LO(vg_Power2_Val.PosEPT);

    RtuSecondaryData[Index_2_PEQT] = DWORD_HI(vg_Power2_Val.PosEQT);
    RtuSecondaryData[Index_2_PEQT + 1] = DWORD_LO(vg_Power2_Val.PosEQT);

    RtuSecondaryData[Index_2_NEPT] = DWORD_HI(vg_Power2_Val.EPT);
    RtuSecondaryData[Index_2_NEPT + 1] = DWORD_LO(vg_Power2_Val.EPT);

    RtuSecondaryData[Index_2_NEQT] = DWORD_HI(vg_Power2_Val.EQT);
    RtuSecondaryData[Index_2_NEQT + 1] = DWORD_LO(vg_Power2_Val.EQT);

    RtuSecondaryData[Index_2_EST] = DWORD_HI(vg_Power2_Val.EST);
    RtuSecondaryData[Index_2_EST + 1] = DWORD_LO(vg_Power2_Val.EST);

    if(MaxFramWriteEnble == TRUE)
    {
        FRAM_MaxDemWrite();
        MaxFramWriteEnble = FALSE;
    }

    if(g_tParam.CtrlParam.AdjustFinishFlag == TRUE)
    {
        if(RN8302RD(&CFG_StatusREG.CheckSum1))
        {
            CheckSum = CFG_StatusREG.CheckSum1.data;
            if(CheckSum != g_tParam.RN_Coefficients.CheckSum1)
            {
                g_tParam.CtrlParam.AdjustFinishFlag = FALSE;
                SaveParam();
                NVIC_SystemReset();
            }
        }
    }
    __nop();
}

void Task_Power_Function(void)
{
    RN8032_Updata();
    FRAM_WriteData();
#ifdef _LEDHarm_
    fnDl645Fft_Harmonic_Exec();
#endif
}

//===========================================================================
//===========================================================================

void RN8032_Adjust_U(unsigned int Phase, unsigned int Voltage)
{
    unsigned int ph = Phase;
    float ftemp;
    float fErr;
    float fGain;
    unsigned int GSData;
    unsigned int Vol_StandardVal; // ��ǰ��ѹ��Ӧ�ı�׼ֵ

    if(RN8302RD(&Fullwave_data.U[ph]))
    {
        ftemp = (float)Voltage;
        Vol_StandardVal = (unsigned int)(ftemp * STANDARD_VAL_U / RATIED_VAL_U);
        ftemp = (float)Fullwave_data.U[ph].data - (float)Vol_StandardVal;
        fErr = ftemp / Vol_StandardVal;
        fGain = (-fErr) / (1 + fErr);
        if (fGain >= 0)
        {
            GSData = (unsigned int)(fGain * POWER15);
        }
        else
        {
            GSData = (unsigned int)(POWER16 + fGain * POWER15);
        }
        g_tParam.RN_Coefficients.GSU[ph] = GSData;
        CFG_StatusREG.GSU[ph].data = g_tParam.RN_Coefficients.GSU[ph];
    }
}

void RN8032_Adjust_I(unsigned int Phase, unsigned int Current)
{
    unsigned int ph = Phase;
    float ftemp;
    float fErr;
    float fGain;
    unsigned int GSData;
    unsigned int Cur_StandardVal; // ��ǰ������Ӧ�ı�׼ֵ

    if(RN8302RD(&Fullwave_data.I[ph]))
    {
        ftemp = (float)Current;   // У׼ֵ 5A
        Cur_StandardVal = (unsigned int)(ftemp * STANDARD_VAL_I / RATIED_VAL_I);
        ftemp = (float)Fullwave_data.I[ph].data - (float)Cur_StandardVal;
        fErr = ftemp / Cur_StandardVal;
        fGain = (-fErr) / (1 + fErr);

        if (fGain >= 0)
        {
            GSData = (unsigned int)(fGain * POWER15);
        }
        else
        {
            GSData = (unsigned int)(POWER16 + fGain * POWER15);
        }

        g_tParam.RN_Coefficients.GSI[ph] = GSData;
        CFG_StatusREG.GSI[ph].data = g_tParam.RN_Coefficients.GSI[ph];
    }
}
/*
void RN8302_Adjust_Offset(unsigned int Phase)
{
    unsigned int ph = Phase;
    u32 Iavebuff[11];
    u64 Iave = 0;
    u16 IaveTmp;
    u8 max = 1;
    u8 min = 1;
    for(int i = 0; i<11;i++)
    {
        if(RN8302RD(&Fullwave_data.I[ph]))
        {
            Iavebuff[i] = Fullwave_data.I[ph].data;
        }
        PT_TimerDelay(300);
    }
    for(int j =1;j<11;j++)
    {
        Iave += Iavebuff[j];
        if (Iavebuff[j]>Iavebuff[max])  max=j;     //�����ֵ
        if (Iavebuff[j]<Iavebuff[min])  min=j;     //����Сֵ
    }
    Iave -= Iavebuff[max];
    Iave -= Iavebuff[min];
    Iave = Iave>>3;
    Iave = Iave * Iave;
    Iave = Iave & 0x000000003FFFC000;//)>>14;
    Iave = Iave >> 14;
    Iave = Iave ^ 0xFFFF;
    IaveTmp = (u16)(Iave | 0x8000);
    g_tParam.RN_Coefficients.I_OS[ph] = IaveTmp;
    CFG_StatusREG.I_OS[ph].data = g_tParam.RN_Coefficients.I_OS[ph];

}*/

void RN8032_Adjust_Section_I(unsigned char seg)
{
    if(seg == 0x00) // �Ͷ�
    {
        if(RN8302RD(&Fullwave_data.I[PH_A]))
        {
            g_tParam.RN_Coefficients.PRTH1L = Fullwave_data.I[PH_A].data >> 12;
            CFG_StatusREG.PRTH1L.data = g_tParam.RN_Coefficients.PRTH1L;
            g_tParam.RN_Coefficients.PRTH1H = g_tParam.RN_Coefficients.PRTH1L + 300;
            CFG_StatusREG.PRTH1H.data = g_tParam.RN_Coefficients.PRTH1H;  // �����ֶ�
        }
    }
    else if(seg == 0x01) // �߶�
    {
        // дʹ��
        CFG_StatusREG.WREN.data = WRENABLE;
        RN8302WR(&CFG_StatusREG.WREN);

        if(RN8302RD(&Fullwave_data.I[PH_A]))
        {
            g_tParam.RN_Coefficients.PRTH2L = Fullwave_data.I[PH_A].data >> 12;
            CFG_StatusREG.PRTH2L.data = g_tParam.RN_Coefficients.PRTH2L;
            g_tParam.RN_Coefficients.PRTH2H = g_tParam.RN_Coefficients.PRTH2L + 300;
            CFG_StatusREG.PRTH2H.data = g_tParam.RN_Coefficients.PRTH2H;  // �����ֶ�

            CFG_StatusREG.PRTH1L.data = g_tParam.RN_Coefficients.PRTH1L;
            RN8302WR(&CFG_StatusREG.PRTH1L);
            CFG_StatusREG.PRTH1H.data = g_tParam.RN_Coefficients.PRTH1H;
            RN8302WR(&CFG_StatusREG.PRTH1H);
            CFG_StatusREG.PRTH2L.data = g_tParam.RN_Coefficients.PRTH2L;
            RN8302WR(&CFG_StatusREG.PRTH2L);
            CFG_StatusREG.PRTH2H.data = g_tParam.RN_Coefficients.PRTH2H;
            RN8302WR(&CFG_StatusREG.PRTH2H);
        }


        //д����
        CFG_StatusREG.WREN.data = WRDISABLE;
        RN8302WR(&CFG_StatusREG.WREN);
    }
}


/*
//��������У������PH=1��
//active:��������Ĵ�����ַ :GPA
//err:�й����
void RN8032_Adjust_Power(unsigned int Phase, unsigned int ActivePower)
{
    unsigned int ph = Phase;
    unsigned int Gain;
    float err;
    unsigned int Power_StandardVal; // ��ǰ��ѹ��Ӧ�ı�׼ֵ

    if(RN8302RD(&Fullwave_data.P[ph]))
    {
        Power_StandardVal = (unsigned int)((float)ActivePower * STANDARD_VAL_P / (RATIED_VAL_P));
        err = ((float)Fullwave_data.P[ph].data - (float)Power_StandardVal) / (float)Power_StandardVal;
    }

    err = (-err) / (1 + err);

    if(err >= 0)
    {
        Gain = (unsigned int)(err * POWER15);
    }
    else
    {
        Gain = (unsigned int)(POWER16 + err * POWER15);
    }
    g_tParam.RN_Coefficient.GP[ph] = Gain;
    CFG_StatusREG.GP[ph].data = g_tParam.RN_Coefficient.GP[ph];
    g_tParam.RN_Coefficient.GQ[ph] = Gain;
    CFG_StatusREG.GQ[ph].data = g_tParam.RN_Coefficient.GQ[ph];
    g_tParam.RN_Coefficient.GS[ph] = Gain;
    CFG_StatusREG.GS[ph].data = g_tParam.RN_Coefficient.GS[ph];
}*/

//��������У������PH=0.5��
void RN8032_Adjust_Angle(unsigned int Phase,unsigned int Section, unsigned int ActivePower)
{
    unsigned int ph = Phase;
    unsigned int Gain;
    float err;
    unsigned int Power_StandardVal; // ��ǰ��ѹ��Ӧ�ı�׼ֵ
    float Angle;
    int lsb;
    if(g_tParam.CtrlParam.NetMode == N34)
    {
        if(Section == 0x00) // �Ͷ�
        {
            if(RN8302RD(&Fullwave_data.P[ph]))
            {
                Power_StandardVal = ActivePower;
                err = ((float)vg_Power_Val.Real2_Val[ph].P - (float)Power_StandardVal) / (float)Power_StandardVal;
            }

            err =  -err / (float)1.73205;
            Angle = asin(err) * 180/PI;             //���ȼ��㵽�Ƕ�
            lsb = (int)(Angle / (float)0.017578);  //����У׼
            Gain = (unsigned char)(0x80 - lsb);

            g_tParam.RN_Coefficients.PHSI[ph] = g_tParam.RN_Coefficients.PHSI[ph]&0xFFFF00;
            g_tParam.RN_Coefficients.PHSI[ph] |= Gain;
            CFG_StatusREG.PHSI[ph].data = g_tParam.RN_Coefficients.PHSI[ph];
        }
        else if(Section == 0x01) // �ж�
        {
            if(RN8302RD(&Fullwave_data.P[ph]))
            {
                Power_StandardVal = ActivePower;
                err = ((float)vg_Power_Val.Real2_Val[ph].P - (float)Power_StandardVal) / (float)Power_StandardVal;
            }

            err =  -err / (float)1.73205;
            Angle = asin(err) * 180/PI;             //���ȼ��㵽�Ƕ�
            lsb = (int)(Angle / (float)0.017578);  //����У׼
            Gain = (unsigned char)(0x80 - lsb);

            g_tParam.RN_Coefficients.PHSI[ph] = g_tParam.RN_Coefficients.PHSI[ph]&0xFF00FF;
            g_tParam.RN_Coefficients.PHSI[ph] |= Gain << 8;
            CFG_StatusREG.PHSI[ph].data = g_tParam.RN_Coefficients.PHSI[ph];
        }
        else if(Section == 0x02) // �߶�
        {
            if(RN8302RD(&Fullwave_data.P[ph]))
            {
                Power_StandardVal = ActivePower;
                err = ((float)vg_Power_Val.Real2_Val[ph].P - (float)Power_StandardVal) / (float)Power_StandardVal;
            }

            err =  -err / (float)1.73205;
            Angle = asin(err) * 180/PI;             //���ȼ��㵽�Ƕ�
            lsb = (int)(Angle / (float)0.017578);  //����У׼
            Gain = (unsigned char)(0x80 - lsb);

            g_tParam.RN_Coefficients.PHSI[ph] = g_tParam.RN_Coefficients.PHSI[ph]&0x00FFFF;
            g_tParam.RN_Coefficients.PHSI[ph] |= Gain << 16;
            CFG_StatusREG.PHSI[ph].data = g_tParam.RN_Coefficients.PHSI[ph];
        }
    }
    else if(g_tParam.CtrlParam.NetMode == N33)
    {
        if(RN8302RD(&Fullwave_data.P[ph]))
    	{
    		Power_StandardVal = ActivePower;
    		err = ((float)vg_Power_Val.Real2_Val[ph].P - (float)Power_StandardVal) / (float)Power_StandardVal;
    	}
    	err = err * (float)1.73205;
    	/*if(err >= 0)
        	{
                g_tParam.RN_Coefficients.P_PHSL[ph] = err * POWER15;
        	    CFG_StatusREG.P_PHSL[ph].data = g_tParam.RN_Coefficients.P_PHSL[ph];
        	}
        	else
        	{
                g_tParam.RN_Coefficients.P_PHSL[ph] = err * POWER15 + POWER16;
        	    CFG_StatusREG.P_PHSL[ph].data = g_tParam.RN_Coefficients.P_PHSL[ph];
        	}*/
        if(Phase == PH_A)
        {
            g_tParam.RN_Coefficients.P_PHSL[ph] = -err * POWER15 + POWER16;
            CFG_StatusREG.P_PHSL[ph].data = g_tParam.RN_Coefficients.P_PHSL[ph];
            //g_tParam.RN_Coefficients.Q_PHSL[ph] = g_tParam.RN_Coefficients.P_PHSL[ph];
            //CFG_StatusREG.Q_PHSL[ph].data = g_tParam.RN_Coefficients.Q_PHSL[ph];
        }
        else if(Phase == PH_C)
        {
            g_tParam.RN_Coefficients.P_PHSL[ph] = err * POWER15; //+ POWER16;
            CFG_StatusREG.P_PHSL[ph].data = g_tParam.RN_Coefficients.P_PHSL[ph];
            //g_tParam.RN_Coefficients.Q_PHSL[ph] = g_tParam.RN_Coefficients.P_PHSL[ph];
            //CFG_StatusREG.Q_PHSL[ph].data = g_tParam.RN_Coefficients.Q_PHSL[ph];
        }
    }
}


//��������У������PH=0.5��
void RN8032_Adjust_Angle34(unsigned int Phase,unsigned int Section, unsigned int ActivePower)
{
    unsigned int ph = Phase;
    unsigned int Gain;
    float err;
    unsigned int Power_StandardVal; // ��ǰ��ѹ��Ӧ�ı�׼ֵ
    float Angle;
    int lsb;

    if(Section == 0x00) // �Ͷ�
    {
        if(RN8302RD(&Fullwave_data.P[ph]))
        {
            Power_StandardVal = ActivePower;
            err = ((float)vg_Power_Val.Real2_Val[ph].P - (float)Power_StandardVal) / (float)Power_StandardVal;
        }

        err =  -err / (float)1.73205;
        Angle = asin(err) * 180/PI;             //���ȼ��㵽�Ƕ�
        lsb = (int)(Angle / (float)0.017578);  //����У׼
        Gain = (unsigned char)(0x80 - lsb);

        g_tParam.RN_Coefficients.PHSI[ph] = g_tParam.RN_Coefficients.PHSI[ph]&0xFFFF00;
        g_tParam.RN_Coefficients.PHSI[ph] |= Gain;
        CFG_StatusREG.PHSI[ph].data = g_tParam.RN_Coefficients.PHSI[ph];
    }
    else if(Section == 0x01) // �ж�
    {
        if(RN8302RD(&Fullwave_data.P[ph]))
        {
            Power_StandardVal = ActivePower;
            err = ((float)vg_Power_Val.Real2_Val[ph].P - (float)Power_StandardVal) / (float)Power_StandardVal;
        }

        err =  -err / (float)1.73205;
        Angle = asin(err) * 180/PI;             //���ȼ��㵽�Ƕ�
        lsb = (int)(Angle / (float)0.017578);  //����У׼
        Gain = (unsigned char)(0x80 - lsb);

        g_tParam.RN_Coefficients.PHSI[ph] = g_tParam.RN_Coefficients.PHSI[ph]&0xFF00FF;
        g_tParam.RN_Coefficients.PHSI[ph] |= Gain << 8;
        CFG_StatusREG.PHSI[ph].data = g_tParam.RN_Coefficients.PHSI[ph];
    }
    else if(Section == 0x02) // �߶�
    {
        if(RN8302RD(&Fullwave_data.P[ph]))
        {
            Power_StandardVal = ActivePower;
            err = ((float)vg_Power_Val.Real2_Val[ph].P - (float)Power_StandardVal) / (float)Power_StandardVal;
        }

        err =  -err / (float)1.73205;
        Angle = asin(err) * 180/PI;             //���ȼ��㵽�Ƕ�
        lsb = (int)(Angle / (float)0.017578);  //����У׼
        Gain = (unsigned char)(0x80 - lsb);

        g_tParam.RN_Coefficients.PHSI[ph] = g_tParam.RN_Coefficients.PHSI[ph]&0x00FFFF;
        g_tParam.RN_Coefficients.PHSI[ph] |= Gain << 16;
        CFG_StatusREG.PHSI[ph].data = g_tParam.RN_Coefficients.PHSI[ph];
    }
}


/*-------------------------У׼ģʽ----��λ---------Buf*/
void RN8032_Adjust(u8 Cmd, u8 Phase, u8 *pAdjustData) //У׼����
{
    u8 PhaseLow4;
    u8 PhaseHigh4;
    u8 ph;
    u16 UData[PH_TH];
    u16 IData[PH_TH];
    u16 AoData[4];
    #if 0
    u8 AngleData[PH_TH];
    #else
    u32 PData[PH_TH];   // ��������
    #endif
    u8 Size;

//  RN8302InitAdjust();

    switch (Cmd)
    {
        case CALIB_UIE: // ��ѹ��������У׼
            g_tParam.CtrlParam.AdjustFinishFlag = FALSE;
            Size = sizeof(UData);
            memcpy((u8 *)&UData[0], pAdjustData, Size);
            memcpy((u8 *)&IData[0], pAdjustData+Size, Size);
            if (Phase == PH_TH)
            {
            	InitRNParamToZero();                       /* ��ʼ�����Ʋ��� */
                RN8302InitAdjust();
                PT_TimerDelay(2000);
                RN8032_Updata();
                PT_TimerDelay(500);
                RN8032_Updata();
                for (ph = 0; ph < 3; ph++)
                {
                    RN8032_Adjust_U(ph, UData[ph]);
                    PT_TimerDelay(400);
                    RN8032_Adjust_I(ph, IData[ph]);
                    PT_TimerDelay(400);
                }
            }
            else if (Phase < PH_TH)
            {
                ph = Phase;
            	InitRNParam_PhaseToZero(ph);                 /* ��ʼ�����Ʋ��� */
                RN8302InitAdjust();
                PT_TimerDelay(2000);
                RN8032_Updata();
                PT_TimerDelay(500);
                RN8032_Updata();
                RN8032_Adjust_U(ph, UData[ph]);
                PT_TimerDelay(400);
                RN8032_Adjust_I(ph, IData[ph]);
                PT_TimerDelay(400);
            }
            g_tParam.CtrlParam.AdjustFinishFlag = TRUE;
            break;
        case CALIB_SECTION_I:
            RN8032_Adjust_Section_I(*pAdjustData);
            break;
        case CALIB_AnoPwm:
            Size = sizeof(AoData);
            memcpy((u8 *)&AoData[0], pAdjustData, Size);
            g_tParam.RN_Coefficients.Ana_Pwm1_5h = (float)AoData[0]/10000;
            g_tParam.RN_Coefficients.Ana_Pwm1_2k = (float)AoData[1]/1000;
            g_tParam.RN_Coefficients.Ana_Pwm1_ki = (g_tParam.RN_Coefficients.Ana_Pwm1_2k - g_tParam.RN_Coefficients.Ana_Pwm1_5h)/3000;

            g_tParam.RN_Coefficients.Ana_Pwm2_5h = (float)AoData[2]/10000;
            g_tParam.RN_Coefficients.Ana_Pwm2_2k = (float)AoData[3]/1000;
            g_tParam.RN_Coefficients.Ana_Pwm2_ki = (g_tParam.RN_Coefficients.Ana_Pwm2_2k - g_tParam.RN_Coefficients.Ana_Pwm2_5h)/3000;
            g_tParam.CtrlParam.AnaCalibFlag = TRUE;
            break;
        case CALIB_ANGLE: // ����У׼
            g_tParam.CtrlParam.AdjustFinishFlag = FALSE;
           /* ���ü������ */
            PData[0] = FLIPDW(pAdjustData+0);
            PData[1] = FLIPDW(pAdjustData+4);
            PData[2] = FLIPDW(pAdjustData+8);
            PhaseLow4 = Phase & 0x0F;
            PhaseHigh4 = (Phase & 0xF0)>>4;
            if (PhaseLow4 == PH_TH)
            {
                for (ph = 0; ph < 3; ph++)
                {
                    RN8032_Adjust_Angle(ph,PhaseHigh4, PData[ph]);
                    PT_TimerDelay(400);
                }
            }
            else if (PhaseLow4 < PH_TH)
            {
                ph = PhaseLow4;
                RN8032_Adjust_Angle(ph, PhaseHigh4, PData[ph]);
                PT_TimerDelay(400);
            }
            g_tParam.CtrlParam.AdjustFinishFlag = TRUE;
            break;
        case CALIB_SET_DEFAULT: //
            if (Phase == PH_TH)
            {
            	InitRNParam();                            /* ��ʼ�����Ʋ��� */
            }
            else if (Phase < PH_TH)
            {
                ph = Phase;
            	InitRNParam_Phase(ph);                     /* ��ʼ�����Ʋ��� */
            }
            break;
        case CALIB_SET_ZERO: //
            if (Phase == PH_TH)
            {
            	InitRNParamToZero();                       /* ��ʼ�����Ʋ��� */
            }
            else if (Phase < PH_TH)
            {
                ph = Phase;
            	InitRNParam_PhaseToZero(ph);               /* ��ʼ�����Ʋ��� */
            }
            break;
        case CALIB_WRITEDATA: //��ʽת�� RN_Coefficients �ṹ
            WriteRNParam(pAdjustData);
            break;
        /*case CALIB_IOFFSET:
            for (ph = 0; ph < 3; ph++)
            {
                RN8302_Adjust_Offset(ph);
                PT_TimerDelay(400);
            }
            break;*/
        default:
            break;
    }
    g_tParam.RN_Coefficients.HFConst1 = RNPARAM_HFCONST1;
    RN8302Init();
    PT_TimerDelay(2000);
    if(g_tParam.CtrlParam.AdjustFinishFlag == TRUE)
    {
        if(RN8302RD(&CFG_StatusREG.CheckSum1))
        {
            g_tParam.RN_Coefficients.CheckSum1 = CFG_StatusREG.CheckSum1.data;

        }
    }
    SaveParam();
}

/*********************FFT*****************************************/
sADE_Instantaneous_TypeDef Harmonictemp;
sDl645FftHarmonicData_TypeDef HarmonicData;

BOOL FFTEnble = FALSE;
float sin_tab[NUM_FFT];
float cos_tab[NUM_FFT];
/* Private functions ---------------------------------------------------------*/

const float Fftcoefficient[50]=					// г������ʱ����ϵ��
{
	1.0005,
	1.0027,
	1.0054,
	1.0087,
	1.0129,
	1.0175,
	1.0229,
	1.029,
	1.0362,
	1.0438,
	1.0524,
	1.0618,
	1.0718,
	1.0827,
	1.0944,
	1.1075,
	1.121,
	1.136,
	1.1517,
	1.1685,
	1.1862,
	1.2051,
	1.2255,
	1.2475,
	1.27,
	1.2942,
	1.3199,
	1.3468,
	1.3758,
	1.407,
	1.4421,
	1.4714,
	1.5107,
	1.5483,
	1.5873,
	1.6312,
	1.6727,
	1.7199,
	1.77,
	1.8231,
	1.8797,
	1.9448,
	2.0074,
	2.074,
	2.1534,
	2.2126,
	2.2919,
	2.3762,
	2.467,
	2.5639,
};

u32	fnHexToBcd_u32(u32 Dat)
{
	u32 result = 0;

	Dat = Dat % 100000000;
	result += (Dat / 10000000) * 0x10000000;
	Dat = Dat % 10000000;
	result += (Dat / 1000000) * 0x1000000;
	Dat = Dat % 1000000;
	result += (Dat / 100000) * 0x100000;
	Dat = Dat % 100000;
	result += (Dat / 10000) * 0x10000;
	Dat = Dat % 10000;
	result += (Dat / 1000) * 0x1000;
	Dat = Dat % 1000;
	result += (Dat / 100) * 0x100;
	Dat = Dat % 100;
	result += (Dat / 10) * 0x10;
	Dat = Dat % 10;
	result += Dat;

	return(result);
}

void fnDl645Fft_init(void)
{
	Harmonictemp.Channel=0x00;
	Harmonictemp.DataCount=0;
    Harmonictemp.StarFlag=0;
    Harmonictemp.ADSPIBusy = 0;
    memset(&Harmonictemp,0,sizeof(sADE_Instantaneous_TypeDef));
    memset(&HarmonicData,0,sizeof(sDl645FftHarmonicData_TypeDef));
}

void SampleDataModifyF(float *piRetValue)
{
	u8 i;
	u32	Temp;
   	for(i=0; i<NUM_FFT; i++)
   	{
	   	piRetValue[i] = 0;
	   	Temp = 0;
	   	//memcpy((u8 *)&Temp , &(Harmonictemp.InstantaneousData[i*3]) , 3);
	   	//Rn8302_RX_Buf[0] << 16 | Rn8302_RX_Buf[1] << 8 | Rn8302_RX_Buf[2];
	   	Temp = Harmonictemp.InstantaneousData[i*3] <<16 | Harmonictemp.InstantaneousData[i*3+1] <<8 | Harmonictemp.InstantaneousData[i*3+2] <<8;
   		if(Temp &0x800000)
   		{
   			Temp = (0xffffff - Temp) + 1;
   			piRetValue[i] = -(float)Temp/8388608;
   		}
   		else piRetValue[i] = (float)Temp/8388608;
   	}
}

void FFT(float dataR[NUM_FFT],float dataI[NUM_FFT])
{
	int x0,x1,x2,x3,x4,x5,x6,xx;
	int i,j,k,b,p,L;
	float TR,TI,temp;

	/********** following code invert sequence ************/
	for ( i=0;i<NUM_FFT;i++ )
	{
		x0=x1=x2=x3=x4=x5=x6=0;
		x0=i&0x01; x1=(i/2)&0x01; x2=(i/4)&0x01; x3=(i/8)&0x01;x4=(i/16)&0x01; x5=(i/32)&0x01; x6=(i/64)&0x01;
		xx=x0*64+x1*32+x2*16+x3*8+x4*4+x5*2+x6;
		dataI[xx]=dataR[i];
	}
	for ( i=0;i<NUM_FFT;i++ )
	{
		dataR[i]=dataI[i]; dataI[i]=0;
	}

	/************** following code FFT *******************/
	for ( L=1;L<=7;L++ )
	{ /* for(1) */
		b=1; i=L-1;
		while ( i>0 )
		{
			b=b*2; i--;
		} /* b= 2^(L-1) */
		for ( j=0;j<=b-1;j++ ) /* for (2) */
		{
			p=1; i=7-L;
			while ( i>0 ) /* p=pow(2,7-L)*j; */
			{
				p=p*2; i--;
			}
			p=p*j;
			for ( k=j;k<128;k=k+2*b ) /* for (3) */
			{
				TR=dataR[k]; TI=dataI[k]; temp=dataR[k+b];
				dataR[k]=dataR[k]+dataR[k+b]*cos_tab[p]+dataI[k+b]*sin_tab[p];
				dataI[k]=dataI[k]-dataR[k+b]*sin_tab[p]+dataI[k+b]*cos_tab[p];
				dataR[k+b]=TR-dataR[k+b]*cos_tab[p]-dataI[k+b]*sin_tab[p];
				dataI[k+b]=TI+temp*sin_tab[p]-dataI[k+b]*cos_tab[p];
			} /* END for (3) */
		} /* END for (2) */
	} /* END for (1) */
} /* END FFT */

void InitForFFT()
{
	int i;

	for ( i=0;i<NUM_FFT;i++ )
	{
		sin_tab[i]=sin(PI*2*i/NUM_FFT);
		cos_tab[i]=cos(PI*2*i/NUM_FFT);
	}
}

// �Ƚϸ�ͨ����ѹ����������Ƿ����һ��ֵ����С�ڲ����д�ͨ����г������
u8 fnDl645Fft_DataCmp(u8 Channel)
{
	u8 Btemp=1;
	u8 i;
	if(vg_Power_Val.Real2_Val[0].U < 100)
	{
	    for(i = 0;i<51;i++)
	    {
            HarmonicData.HarmonicpercentU[0][i] = 0;
        }
	}
	switch(Channel)
	{
		case 0x00:
			if(vg_Power_Val.Real2_Val[0].U < 100)
			{
                Btemp=0;
			}
			break;
		case 0x01:
			if(vg_Power_Val.Real2_Val[1].U < 100)
			{
                Btemp=0;
                for(i = 0;i<51;i++)
			    {
                    HarmonicData.HarmonicpercentU[1][i] = 0;
                }

			}
			break;
		case 0x02:
			if(vg_Power_Val.Real2_Val[2].U< 100)
			{ 
			    Btemp=0;
			    for(i = 0;i<51;i++)
			    {
                    HarmonicData.HarmonicpercentU[2][i] = 0x00;
                }
            }
			break;
		case 0x03:
			if(vg_Power_Val.Real2_Val[0].I < 0x0070) Btemp=0;
			break;
		case 0x04:
			if(vg_Power_Val.Real2_Val[1].I < 0x0070) Btemp=0;
			break;
		case 0x05:
			if(vg_Power_Val.Real2_Val[2].I < 0x0070) Btemp=0;
			break;
	    default:
	        break;
	}
	return(Btemp);
}

void fnDl645Fft_Harmonic_Exec(void)
{

	float ftemp_N,ftemp_P;
	float fBase;  //������ƽ��
	s16 i;

	if(Harmonictemp.StarFlag==0)
	{
		Harmonictemp.StarFlag =1;
		g_fftEnable = TRUE;
		//memset(&HarmonicData,0,sizeof(sDl645FftHarmonicData_TypeDef));
		//Harmonictemp.TimeOutStamp=SysStamp?SysStamp:(SysStamp-1);

		CFG_StatusREG.WREN.data = WRENABLE;
        RN8302WR(&CFG_StatusREG.WREN);      //дʹ��

        CFG_StatusREG.WSAVECON.rw = RW;
		CFG_StatusREG.WSAVECON.data = 0xA0;
        RN8302WR(&CFG_StatusREG.WSAVECON);  //��������ֵд����

		CFG_StatusREG.WREN.data = WRDISABLE;
        RN8302WR(&CFG_StatusREG.WREN);      //д����

		Harmonictemp.Channel=0x00;
		Harmonictemp.ReadAdress = 0x0200;
		InitForFFT();
		return;
	}
	if(Harmonictemp.StarFlag == 0x01)
	{
		if(g_fftEnable)	return;
		Harmonictemp.StarFlag = 0x02;
		CFG_StatusREG.WSAVECON.rw = RO;
		if(RN8302RD(&CFG_StatusREG.WSAVECON))
		{
            if(CFG_StatusREG.WSAVECON.data & 0x30) return;
		}/*
		for(i=0;i<6;i++)
		{
			Dl645FrontTmp.UI[i] = 0 ;
	    	fnRN8302_Read( 0x0058+i , (u8 *)&Dl645FrontTmp.UI[i] , 4 ) ; //����
		}
		for(i=0;i<3;i++)
		{
			HarmonicData.FU[i] = ((s16)(Dl645FrontTmp.UI[i]/(10*(Dl645FirmPara.VRmsConst))));
		}
		for(i=0;i<3;i++)
		{
			HarmonicData.FI[i] = (s32)(Dl645FrontTmp.UI[i+3]/(Dl645FirmPara.IRmsConst));
		}*/
		return;
	}
	if(Harmonictemp.StarFlag == 0x02)
	{
		for(i=0;i<8;i++)
		{
			RN8302RDBUFF(((Harmonictemp.ReadAdress)+i*16),(u8 *)&Harmonictemp.InstantaneousData[i*48]);
		}

		// ������ɺ����г������
		SampleDataModifyF(&HarmonicData.iRealArray[0]);	//������������
		for(i=0;i<NUM_FFT;i++)  HarmonicData.iMageArray[i]=0;
		FFT(HarmonicData.iRealArray, HarmonicData.iMageArray);

		ftemp_N = (float)(((float)HarmonicData.iRealArray[1] *(float)HarmonicData.iRealArray[1]) + ((float)HarmonicData.iMageArray[1] * (float)HarmonicData.iMageArray[1]));
		ftemp_N = sqrt(ftemp_N);
		fBase	= ftemp_N;
		ftemp_P = 0;
		for(i=0;i<32;i++)
	    {
	    	ftemp_N = (float)(((float)HarmonicData.iRealArray[i+2] *(float)HarmonicData.iRealArray[i+2]) + ((float)HarmonicData.iMageArray[i+2] * (float)HarmonicData.iMageArray[i+2]));
	    	ftemp_N = sqrt(ftemp_N);
	    	if(Harmonictemp.Channel<0x03)
	    	{
	    		HarmonicData.HarmonicpercentU[Harmonictemp.Channel][i+1] = ftemp_N * 1000000*Fftcoefficient[i] /fBase;//(fnHexToBcd_u32((u32)(( ftemp_N * 1000000*Fftcoefficient[i]) /fBase))) ;
	    		//ftemp_P += (((float)HarmonicData.HarmonicpercentU[Harmonictemp.Channel][i+1]) * ((float)HarmonicData.HarmonicpercentU[Harmonictemp.Channel][i+1]));
	    	}
	    	else
	    	{
		    	HarmonicData.HarmonicpercentI[Harmonictemp.Channel-3][i+1] = ftemp_N * 1000000*Fftcoefficient[i] /fBase ;
	    	}
	    }
		/*if(Harmonictemp.Channel<0x03)
		{
			ftemp_P = sqrt(ftemp_P);
			HarmonicData.HarmonicpercentU[Harmonictemp.Channel][0] = (u16)(ftemp_P);
		}*/
		//HarmonicData.HarmonicpercentI[Harmonictemp.Channel-3][0] = 0x999999;
		//HarmonicData.HarmonicpercentU[Harmonictemp.Channel][0] = 0x999999;
		Harmonictemp.Channel++;  //�ӻ�ȥ
		Harmonictemp.ReadAdress+=128;//�ӻ�ȥ
		for(i=Harmonictemp.Channel;i<6;i++)
		{
			if(fnDl645Fft_DataCmp(Harmonictemp.Channel)) break;
			Harmonictemp.Channel++;
			Harmonictemp.ReadAdress+=128;
		}
		if(Harmonictemp.Channel > 5 )
		{
			Harmonictemp.StarFlag = 0;
			return;
		}

	}
	/*if(fnStamp_Through(Harmonictemp.TimeOutStamp)>8000)
	{
		Harmonictemp.StarFlag = 0;
	}*/
}

