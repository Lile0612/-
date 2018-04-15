/*! @file
********************************************************************************
<PRE>
ģ����       : 485ͨѶ��������ģ��
�ļ���       : taskRS232.h
����ļ�     :
�ļ�ʵ�ֹ��� : ͨѶ����
����         : < ��>
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         :
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2017/03/22   1.0    < ��>           ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/


#ifndef _TASKRS232_H
#define _TASKRS232_H


/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
#define ADDR_ALL                0xEE
#define ADDR_PC                 0xEF
#define RTU_ADDR_ALL            0xFA
#define RTU_ADDR_PC             0xFE
#define RX_SUBCOM_LEN           64
#define TX_SUBCOM_LEN           128

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/*------ У�� ------*/
typedef struct
{
    u8 Start1;               // ֡��ʼ��
    u8 Addr1;                // ���ͷ���ַ
    u8 Addr2;                // ���շ���ַ
    u8 Start2;               // ֡��ʼ��
    u8 CtrlCode;             // ������
    u16 Len;                 // ���ݳ���
    u8 Cmd;                  // ������
    u8 Data[TX_SUBCOM_LEN];  // ������
    u8 CS;                   // У��
}MSSendPackStruct;

// �������ݽṹ
typedef struct
{
    u8 Start1;               // ֡��ʼ��
    u8 Addr1;                // ���ͷ���ַ
    u8 Addr2;                // ���շ���ַ
    u8 Start2;               // ֡��ʼ��
    u8 CtrlCode;             // ������
    u16 Len;                 // ���ݳ���
    u8 Cmd;                  // ������
    u8 Data[RX_SUBCOM_LEN];  // ���ݵ�ַ
    u8 byCS;                 // У��
}MSRecvPackStruct;

/*------ rtu ------*/
typedef struct
{
    u8 RTU_Addr;                 // �Ǳ��ַ
    u8 RTU_Func;                 // ������
    u16 RTU_DsAddr;              // ��ʼ��ַ
    u16 RTU_DsData;               // �ֽڳ��� ����ֵ
    u16 RTU_DsNum;
    u8 RTU_DataNum;              //
    u8 RTU_DataLen;              //
    u8 RTU_Data;
    u8 Data[TX_SUBCOM_LEN];     // ������
    u16 RtuCRC;                 // У��
}RtuSendPackStruct;

// �������ݽṹ
typedef struct
{
    u8 RR_Addr;                 // �Ǳ��ַ
    u8 RR_Func;                 // ������
    u16 RR_DsAddr;              // ��ʼ��ַ
    u16 RR_DsNum;               // �ֽڳ��� ����ֵ
    u8 RR_DataNum;              //
    u8 RR_DataLen;              //
    u8 RR_Data;
    u8 Data[RX_SUBCOM_LEN];  // ���ݵ�ַ
    u16 RR_CRC;                 // У��
}RtuRecvPackStruct;

typedef struct
{
    u8 Cmd;
    u8 Phase;
    u8 Data[64];
}AdjustMsgStruct;


// �澯����
__packed struct  MSPTLALARM_BITS { // bit  description
	u8 OUA:1;			// 0	��ѹ�澯,0:����,1:Խ��
	u8 LIP:1;			// 1	Ƿ��Խ��,0:����,1:Խ��
	u8 OUP:1;			// 2	��ѹԽ��
	u8 LUP:1;			// 3    ǷѹԽ��

	u8 THDIP:1;			// 4    ����г��Խ��
	u8 TEMP:1;			// 5    �¶�Խ��
	u8 NUMP:1;			// 6	Ͷ�д����澯
	u8 LP:1;			// 7	ȱ��

	u8 AKGFAULT:1;		// 8    A�鿪�ظ澯
	u8 BKGFAULT:1;		// 8    B�鿪�ظ澯
	u8 CKGFAULT:1;		// 8    C�鿪�ظ澯
	u8 DKGFAULT:1;		// 8    D�鿪�ظ澯

	u8 rsvd:4;			// 15 - 12  ����
};


__packed union MSPTLALARM_REG
{
	u16					all;
	struct MSPTLALARM_BITS	bit;
};

// �ӻ�����(07H)
__packed typedef struct {
// 	u8 UpperPF;								// ������������	1�ֽ�	1.0-0.98C
	u8 LowerPF;								// ������������	1�ֽ�	0.80-0.99L
	u8 TempVal;								// �¶���ֵ	1�ֽ�	20~70
	u8 THDIVal;								// г����ֵ	1�ֽ�	20~60
	u16 WarnShield;							// �澯����	2�ֽ�	0~FFFH
	u16 OUAVal;								// ��ѹ�澯��ֵ	2�ֽ�	������4000~4200��Ӧ��ѹ400~420(V)Ĭ��406V
											//						�ֲ���2310~2410��Ӧ��ѹ231~241(V)Ĭ��236V
	u16 OUPVal;								// ���ع�ѹ��ֵ	2�ֽ�	������4200~4600��Ӧ��ѹ420~460(V) Ĭ��437V
											//						�ֲ���2420~2530��Ӧ��ѹ231~241(V)Ĭ��247V
	u16 LIPVal;								// Ƿ����������ֵ	2�ֽ�	20~100��Ӧ����0.2~1(A)
}MSPTL_SubParamUpStruct;

__packed typedef struct {
// 	u8 UpperPF;								// ������������	1�ֽ�	1.0-0.98C
	u8 LowerPF;								// ������������	1�ֽ�	0.80-0.99L
	u8 TempVal;								// �¶���ֵ	1�ֽ�	20~70
	u8 THDIVal;								// г����ֵ	1�ֽ�	20~60
	u16 OUAVal;								// ��ѹ�澯��ֵ	2�ֽ�	������4000~4200��Ӧ��ѹ400~420(V)Ĭ��406V
											//						�ֲ���2310~2410��Ӧ��ѹ231~241(V)Ĭ��236V
	u16 OUPVal;								// ���ع�ѹ��ֵ	2�ֽ�	������4200~4600��Ӧ��ѹ420~460(V) Ĭ��437V
											//						�ֲ���2420~2530��Ӧ��ѹ231~241(V)Ĭ��247V
	u16 LIPVal;								// Ƿ����������ֵ	2�ֽ�	20~100��Ӧ����0.2~1(A)
	u16 WarnShield;							// �澯����	2�ֽ�	0~FFFH
}MSPTL_SubParamDownStruct;

// ������Ϣ��08H��
__packed typedef struct {
	u16 U2;									// ������ѹ	2�ֽ�	/10֮��Ϊʵ�ʵ�ѹֵ(V)
	u32 rsvd1;								//
	u16 I2;									// ��������	2�ֽ�	/100֮��Ϊʵ�ʵ���ֵ(A)
	u32 rsvd2;								//
	u16 P2;									// �����й�	2�ֽ�	ʵ���й�ֵ(W)
	u32 rsvd3;								//
	u16 Q2;									// �����޹�	2�ֽ�	ʵ���޹�ֵ(Var)
	u32 rsvd4;								//
	u16 THDI;								// ����г��	2�ֽ�	г��ֵ������
	u32 rsvd5;								//
}MSPTL_SampleInfoStruct;

// �ӻ�����б���ȡ�ã���09H��

// ����汾�ţ�10H��


/* Exported functions ------------------------------------------------------- */
void Task_RS232_init(void);
void Task_RS232_Function(void);


#endif /* _TASKRS232_H */

//===========================================================================
// No more.
//===========================================================================


