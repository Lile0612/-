/*! @file
********************************************************************************
<PRE>
ģ����       : ������ʾ����ģ��
�ļ���       : taskGUI.c
����ļ�     :
�ļ�ʵ�ֹ��� : �˻�����,LED����,����ɨ��(�������ʾ)
����         : < ��>
�汾         : 1.0
--------------------------------------------------------------------------------
��ע         : ���Ա�(������)
--------------------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾   �޸���         �޸�����
2017/03/22   1.0    < ��>           ����
</PRE>
********************************************************************************

  * ��Ȩ����(c) YYYY, <xxx>, ��������Ȩ��

*******************************************************************************/
#ifdef _GUILED_
/* Includes ------------------------------------------------------------------*/
#include "Include.h"
/* Public variate ------------------------------------------------------------*/



/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
#define KEY_NUM					0x04 // ��������


#define KEY_UP_BUTTON			0x00
#define KEY_DOWN_BUTTON			0x01
#define KEY_MENU_BUTTON			0x02
#define KEY_OK_BUTTON			0x03

#define KEY_PRESSED				0x01
#define KEY_UNPRESSED			0x02
#define KEY_LONG_PRESSED		0x04

u8 g_Key_Status[KEY_NUM];


u16 Leve_1_DispNUM; // ��λ��Ƿ�

#define  NEG_NUM           '-' // ����ASCII
#define  POS_NUM           '+' // ����ASCII

/* Private variables ---------------------------------------------------------*/
#define TIMER_IDLE	SYSTICK

#define TIMER_DELAY_30M	    (1800000/TIMER_IDLE)// ��ʱ30*60s
#define TIMER_DELAY_300S	(300000/TIMER_IDLE) // ��ʱ300s
#define TIMER_DELAY_120S	(120000/TIMER_IDLE) // ��ʱ120s
#define TIMER_DELAY_60S		(60000/TIMER_IDLE)	// ��ʱ60s
#define TIMER_DELAY_50S		(50000/TIMER_IDLE)	// ��ʱ50s
#define TIMER_DELAY_30S		(30000/TIMER_IDLE)	// ��ʱ30s
#define TIMER_DELAY_15S		(15000/TIMER_IDLE)	// ��ʱ15s
#define TIMER_DELAY_7S		(9000/TIMER_IDLE)	// ��ʱ7s
#define TIMER_DELAY_5S		(5000/TIMER_IDLE)	// ��ʱ5s
#define TIMER_DELAY_2S		(2000/TIMER_IDLE)	// ��ʱ2s
#define TIMER_DELAY_1S		(1000/TIMER_IDLE)	// ��ʱ1s
#define TIMER_DELAY_10ms    (9/TIMER_IDLE)	    // ��ʱ10ms
#define TIMER_DELAY_100ms	(100/TIMER_IDLE)	// ��ʱ100ms
#define TIMER_DELAY_200ms	(200/TIMER_IDLE)	// ��ʱ200ms
#define TIMER_DELAY_300ms	(300/TIMER_IDLE)	// ��ʱ300ms
#define TIMER_DELAY_500ms	(500/TIMER_IDLE)	// ��ʱ500ms
#define TIMER_DELAY_750ms	(750/TIMER_IDLE)	// ��ʱ750ms

#define TIMER_DELAY_LONGSET (3000/TIMER_IDLE)   //����������ʱ3s

typedef enum
{
    UPDATA_ADD = 0,
    UPDATA_SUB = 1,

} UPDATA_DIR;

//ɸѡ���
typedef enum
{
	Select_Net = 0x00,
	Select_Baud = 0x01,
	Select_Data = 0x02,
	Select_Coms = 0x03,
	Select_Save = 0x04,
	Select_Disp_Default = 0x05,
	Select_Do_Mode = 0x06,
	Select_Ao_Mode = 0x07,
	Select_Do_item = 0x08,
	Select_Ao_item = 0x09,
	Select_Light = 0x0A,

}SELECT_CATE;

// ���˵�����
#ifdef _LEDHarm_
enum emMENU_MAIN_INDEX
{
    MENU_INDEX_U     = 0x00, // ��ѹ
	MENU_INDEX_MIN	 = MENU_INDEX_U,
	MENU_INDEX_LU    = 0x01, // �ߵ�ѹ
	MENU_INDEX_I	 = 0x02, // ����
	MENU_INDEX_P	 = 0x03, // �й�����
	MENU_INDEX_Q     = 0x04, // �޹�����
	MENU_INDEX_S     = 0x05, // ���ڹ���
	MENU_INDEX_PF    = 0x06, // �й�����
	MENU_INDEX_F     = 0x07,
	MENU_INDEX_PosEPT    = 0x08, // �����й�����
	MENU_INDEX_NegEPT    = 0x09, // �����й�����
	MENU_INDEX_PosEQT    = 0x0A, // �����޹�����
	MENU_INDEX_NegEQT    = 0x0B, // �����޹�����
	MENU_INDEX_Uimb      = 0x0C,
    MENU_INDEX_HarmU     = 0x0D,
    MENU_INDEX_HarmI     = 0x0E,
    MENU_INDEX_HarmU3    = 0x0F,
    MENU_INDEX_HarmU5    = 0x10,
    MENU_INDEX_HarmU7    = 0x11,
    MENU_INDEX_HarmU9    = 0x12,
    MENU_INDEX_HarmU11   = 0x13,
    MENU_INDEX_HarmU13   = 0x14,
    MENU_INDEX_HarmU15   = 0x15,
    MENU_INDEX_HarmU17   = 0x16,
    MENU_INDEX_HarmU19   = 0x17,
    MENU_INDEX_HarmU21   = 0x18,
    MENU_INDEX_HarmU23   = 0x19,
    MENU_INDEX_HarmU25   = 0x1A,
    MENU_INDEX_HarmU27   = 0x1B,
    MENU_INDEX_HarmU29   = 0x1C,
    MENU_INDEX_HarmU31   = 0x1D,
    MENU_INDEX_HarmI3    = 0x1E,
    MENU_INDEX_HarmI5    = 0x1F,
    MENU_INDEX_HarmI7    = 0x20,
    MENU_INDEX_HarmI9    = 0x21,
    MENU_INDEX_HarmI11   = 0x22,
    MENU_INDEX_HarmI13   = 0x23,
    MENU_INDEX_HarmI15   = 0x24,
    MENU_INDEX_HarmI17   = 0x25,
    MENU_INDEX_HarmI19   = 0x26,
    MENU_INDEX_HarmI21   = 0x27,
    MENU_INDEX_HarmI23   = 0x28,
    MENU_INDEX_HarmI25   = 0x29,
    MENU_INDEX_HarmI27   = 0x2A,
    MENU_INDEX_HarmI29   = 0x2B,
    MENU_INDEX_HarmI31   = 0x2C,

    MENU_INDEX_Uavr      = 0x40, // ��ѹ
	MENU_INDEX_LUavr     = 0x41, // �ߵ�ѹ
	MENU_INDEX_Iavr	     = 0x42, // ����
	MENU_INDEX_Pe	     = 0x43, // �й�����
	MENU_INDEX_Qe        = 0x44, // �޹�����
	MENU_INDEX_Se        = 0x45, // ���ڹ���
	MENU_INDEX_PFe       = 0x46, // �й�����
	MENU_INDEX_MAX	     = MENU_INDEX_HarmI31,
    MENU_INDEX_UAngle    = 0x30,
    MENU_INDEX_IAngle    = 0x31,
};
#else
enum emMENU_MAIN_INDEX
{
    MENU_INDEX_U     = 0x00, // ��ѹ
	MENU_INDEX_MIN	 = MENU_INDEX_U,
	MENU_INDEX_LU    = 0x01, // �ߵ�ѹ
	MENU_INDEX_I	 = 0x02, // ����
	MENU_INDEX_P	 = 0x03, // �й�����
	MENU_INDEX_Q     = 0x04, // �޹�����
	MENU_INDEX_S     = 0x05, // ���ڹ���
	MENU_INDEX_PF    = 0x06, // �й�����
	MENU_INDEX_F     = 0x07,
	MENU_INDEX_PosEPT    = 0x08, // �����й�����
	MENU_INDEX_NegEPT    = 0x09, // �����й�����
	MENU_INDEX_PosEQT    = 0x0A, // �����޹�����
	MENU_INDEX_NegEQT    = 0x0B, // �����޹�����
    MENU_INDEX_HarmU     = 0x0C,
    MENU_INDEX_HarmI     = 0x0D,
    MENU_INDEX_HarmU3    = 0x0E,
    MENU_INDEX_HarmU5    = 0x0F,
    MENU_INDEX_HarmU7    = 0x10,
    MENU_INDEX_HarmU9    = 0x11,
    MENU_INDEX_HarmU11   = 0x12,
    MENU_INDEX_HarmU13   = 0x13,
    MENU_INDEX_HarmU15   = 0x14,
    MENU_INDEX_HarmU17   = 0x15,
    MENU_INDEX_HarmU19   = 0x16,
    MENU_INDEX_HarmU21   = 0x17,
    MENU_INDEX_HarmU23   = 0x18,
    MENU_INDEX_HarmU25   = 0x19,
    MENU_INDEX_HarmU27   = 0x1A,
    MENU_INDEX_HarmU29   = 0x1B,
    MENU_INDEX_HarmU31   = 0x1C,
    MENU_INDEX_HarmI3    = 0x1D,
    MENU_INDEX_HarmI5    = 0x1E,
    MENU_INDEX_HarmI7    = 0x1F,
    MENU_INDEX_HarmI9    = 0x20,
    MENU_INDEX_HarmI11   = 0x21,
    MENU_INDEX_HarmI13   = 0x22,
    MENU_INDEX_HarmI15   = 0x23,
    MENU_INDEX_HarmI17   = 0x24,
    MENU_INDEX_HarmI19   = 0x25,
    MENU_INDEX_HarmI21   = 0x26,
    MENU_INDEX_HarmI23   = 0x27,
    MENU_INDEX_HarmI25   = 0x28,
    MENU_INDEX_HarmI27   = 0x29,
    MENU_INDEX_HarmI29   = 0x2A,
    MENU_INDEX_HarmI31   = 0x2B,
    MENU_INDEX_Uimb      = 0x2C,
    MENU_INDEX_Uavr      = 0x40, // ��ѹ
	MENU_INDEX_LUavr     = 0x41, // �ߵ�ѹ
	MENU_INDEX_Iavr	     = 0x42, // ����
	MENU_INDEX_Pe	     = 0x43, // �й�����
	MENU_INDEX_Qe        = 0x44, // �޹�����
	MENU_INDEX_Se        = 0x45, // ���ڹ���
	MENU_INDEX_PFe       = 0x46, // �й�����
	MENU_INDEX_MAX	     = MENU_INDEX_NegEQT,
    MENU_INDEX_UAngle    = 0x30,
    MENU_INDEX_IAngle    = 0x31,
};
#endif

enum emMENU_SUBMAIN_INDEX
{
	MENUSUB_INDEX_READ	= 0x00, // �鿴
	MENUSUB_INDEX_MIN	= MENUSUB_INDEX_READ,
	MENUSUB_INDEX_PROG	= 0x01, // ����
	MENUSUB_INDEX_MAX	= MENUSUB_INDEX_PROG,
};

// MENU1�˵�����
enum emMENU_SETMENU1_INDEX
{
	MENU1_INDEX_INPT	= 0x00, // ��������
	MENU1_INDEX_MIN	    = MENU1_INDEX_INPT,
	MENU1_INDEX_COM1	= 0x01, // ͨѶ
	MENU1_INDEX_SYS     = 0x02, // ϵͳ
	MENU1_INDEX_DO1     = 0x03, // ���1
	MENU1_INDEX_DO2     = 0x04, // ���2
	MENU1_INDEX_DO3     = 0x05, // ���3
	MENU1_INDEX_DO4     = 0x06, // ���4
	MENU1_INDEX_AO1     = 0x07, // ģ�����1
	MENU1_INDEX_AO2     = 0x08, // ģ�����2
    MENU1_INDEX_VER     = 0x09, // �汾
	MENU1_INDEX_MAX	    = MENU1_INDEX_AO2,
	MENU1_INDEX_RMAX    = MENU1_INDEX_VER,
};

// MENU2_1�˵�����
enum emMENU_SETMENU2_1_INDEX
{
    MENU2_1_INDEX_NET   = 0x00, // ���߷�ʽ
    MENU2_1_INDEX_MIN	= MENU2_1_INDEX_NET,
    MENU2_1_INDEX_PT	= 0x01, // PT
    MENU2_1_INDEX_CT    = 0x02, // CT
	MENU2_1_INDEX_MAX	= MENU2_1_INDEX_CT,
};

// MENU2_2�˵�����
enum emMENU_SETMENU2_2_INDEX
{
	MENU2_2_INDEX_ADD	= 0x00, // ͨѶ��ַ
	MENU2_2_INDEX_MIN	= MENU2_2_INDEX_ADD,
	MENU2_2_INDEX_BAUD	= 0x01, // ������
	MENU2_2_INDEX_DATA  = 0x02, // ���ݸ�ʽ
	MENU2_2_INDEX_COMS  = 0x03, // ���ݸ�ʽ
	MENU2_2_INDEX_MAX	= MENU2_2_INDEX_COMS,
};

// MENU2_3�˵�����
enum emMENU_SETMENU2_3_INDEX
{
	MENU2_3_INDEX_CYC	= 0x00, // ��ʾ�л�ʱ��
	MENU2_3_INDEX_MIN	= MENU2_3_INDEX_CYC,
	MENU2_3_INDEX_LIGH	= 0x01, // ���ȵȼ�
	MENU2_3_INDEX_T	= 0x02, // ʱ������
	MENU2_3_INDEX_DISP	= 0x03, // Ĭ����ʾ
	MENU2_3_INDEX_ALR	= 0x04, // ��˸����
	MENU2_3_INDEX_CLRE	= 0x05, // ��������
	MENU2_3_INDEX_CODE	= 0x06, // �������
	MENU2_3_INDEX_MAX	= MENU2_3_INDEX_CODE,
	MENU2_3_INDEX_RMAX  = MENU2_3_INDEX_ALR,
};

// MENU2_4�˵�����  D0-1
enum emMENU_SETMENU2_4_INDEX
{
	MENU2_4_INDEX_MODE	= 0x00, // ����ģʽ
	MENU2_4_INDEX_MIN	= MENU2_4_INDEX_MODE,
	MENU2_4_INDEX_TIME	= 0x01, // ����������
	MENU2_4_INDEX_ITEM  = 0x02, // ������Ŀ
	MENU2_4_INDEX_UAL   = 0x03, // ����ֵ
	MENU2_4_INDEX_HYS   = 0x04, // ����ֵ
	MENU2_4_INDEX_DELAY = 0x05, // ��ʱ
	MENU2_4_INDEX_MAX	= MENU2_4_INDEX_DELAY,
};

// MENU2_5�˵�����  D0-2
enum emMENU_SETMENU2_5_INDEX
{
	MENU2_5_INDEX_MODE	= 0x00, // ����ģʽ
	MENU2_5_INDEX_MIN	= MENU2_5_INDEX_MODE,
	MENU2_5_INDEX_TIME	= 0x01, // ����������
	MENU2_5_INDEX_ITEM  = 0x02, // ������Ŀ
	MENU2_5_INDEX_UAL   = 0x03, // ����ֵ
	MENU2_5_INDEX_HYS   = 0x04, // ����ֵ
	MENU2_5_INDEX_DELAY = 0x05, // ��ʱ
	MENU2_5_INDEX_MAX	= MENU2_5_INDEX_DELAY,
};

// MENU2_6�˵�����  DO-3
enum emMENU_SETMENU2_6_INDEX
{
	MENU2_6_INDEX_MODE	= 0x00, // ����ģʽ
	MENU2_6_INDEX_MIN	= MENU2_6_INDEX_MODE,
	MENU2_6_INDEX_TIME	= 0x01, // ����������
	MENU2_6_INDEX_ITEM  = 0x02, // ������Ŀ
	MENU2_6_INDEX_UAL   = 0x03, // ����ֵ
	MENU2_6_INDEX_HYS   = 0x04, // ����ֵ
	MENU2_6_INDEX_DELAY = 0x05, // ��ʱ
	MENU2_6_INDEX_MAX	= MENU2_6_INDEX_DELAY,
};

// MENU2_7�˵�����  DO-4
enum emMENU_SETMENU2_7_INDEX
{
	MENU2_7_INDEX_MODE	= 0x00, // ����ģʽ
	MENU2_7_INDEX_MIN	= MENU2_7_INDEX_MODE,
	MENU2_7_INDEX_TIME	= 0x01, // ����������
	MENU2_7_INDEX_ITEM  = 0x02, // ������Ŀ
	MENU2_7_INDEX_UAL   = 0x03, // ����ֵ
	MENU2_7_INDEX_HYS   = 0x04, // ����ֵ
	MENU2_7_INDEX_DELAY = 0x05, // ��ʱ
	MENU2_7_INDEX_MAX	= MENU2_7_INDEX_DELAY,
};

// MENU2_8�˵�����  AO-1
enum emMENU_SETMENU2_8_INDEX
{
	MENU2_8_INDEX_MODE	= 0x00, // ����ģʽ
	MENU2_8_INDEX_MIN	= MENU2_8_INDEX_MODE,
	MENU2_8_INDEX_ITEM  = 0x01, // ������Ŀ
	MENU2_8_INDEX_DS    = 0x02, // ����ֵ
	MENU2_8_INDEX_FS    = 0x03, // ����ֵ
	MENU2_8_INDEX_MAX	= MENU2_8_INDEX_FS,
};

// MENU2_8�˵�����  AO-2
enum emMENU_SETMENU2_9_INDEX
{
	MENU2_9_INDEX_MODE	= 0x00, // ����ģʽ
	MENU2_9_INDEX_MIN	= MENU2_9_INDEX_MODE,
	MENU2_9_INDEX_ITEM  = 0x01, // ������Ŀ
	MENU2_9_INDEX_DS    = 0x02, // ����ֵ
	MENU2_9_INDEX_FS    = 0x03, // ����ֵ
	MENU2_9_INDEX_MAX	= MENU2_9_INDEX_FS,
};

// ������ʾ�ڼ�λ
#define CURRENTFOCUS_NONE		0x00
#define CURRENTFOCUS_0			0x01
#define CURRENTFOCUS_1			0x02
#define CURRENTFOCUS_2			0x04
#define CURRENTFOCUS_3			0x08
#define CHARMODE_NC             0x00

// ����״̬
enum emKEYSTATUS
{
	KEYSTATUS_NONE = 0,
	KEYSTATUS_UP = 1,
	KEYSTATUS_DOWN = 2,
	KEYSTATUS_MENU = 3,
	KEYSTATUS_OK = 4,
	KEYSTATUS_MENULONG = 5,
};

void Disp_IO_Status(u8 InStatus,u8 OutSatus);
void DispMenu_Main(void);   // ������
void DispMenu_Menu1(void); // ģʽѡ��(�Ķ�/���)
void DispMenu_Menu2(void); // ������ѡ��˵�
void DispMenu_Menu3(void); // �����Ӳ˵�
void DispMenu_MenuValue(void);     // ������ֵ
void DispMenu_MenuCode(void);     // ������ʾ
void DispMenu_MenuCodeErr(void);  // ���������ʾ
void DispMenu_MenuSave(void);      // ģʽѡ�����

// �����Key_Tab�ж�Ӧ
#define KEYFUNC_MAIN        0 // ��ʾ���˵�
#define KEYFUNC_MENU1	    1 // ѡ��ģʽ
#define KEYFUNC_MENU2	    2 // ���ò˵�����
#define KEYFUNC_MENU3		3 // ���ò˵�����
#define KEYFUNC_MENUVALUE	4 // ���ò˵�ֵ
#define KEYFUNC_MENUCODE	5 // �����������
#define KEYFUNC_MENUCODEERR	6 // ��������������
#define KEYFUNC_MENUSAVE	7 // �˳��������

void (*KeyFuncPtr)();			// ��������ָ��

typedef struct{
	u8 KeyStateIndex;			// ��ǰ״̬������
	u8 KeyLeftState;			// ����"����"��ʱת���״̬������
	u8 KeyRightState;			// ����"����"��ʱת���״̬������
    u8 KeyUpState;              // ����"����"��ʱת���״̬������
    u8 KeyDnState;              // ����"����"��ʱת���״̬������
	void (*CurrentOperate)();	// ��ǰ״̬Ӧ��ִ�еĹ��ܲ���
} KbdTabStruct;

const KbdTabStruct Key_Tab[]={
//    |-----------> Index
//    |  Up
//    |  |  Down
//    |  |  |  Menu
//    |  |  |  |  Ok   --->���ܺ���
//    |  |  |  |  |       |
    { 0, 0, 0, 0, 0,(*DispMenu_Main)},  // �������� ��ʾ���˵�����
    { 1, 1, 1, 0, 2,(*DispMenu_Menu1)}, // ��ʾMENU����������ֵ
    { 2, 2, 2, 0, 3,(*DispMenu_Menu2)}, // ��ʾOK����ֵ
    { 3, 3, 3, 2, 4,(*DispMenu_Menu3)}, // ��ʾOK����ֵ
    { 4, 4, 4, 3, 4,(*DispMenu_MenuValue)}, // ��ʾOK����ֵ
    { 5, 5, 5, 1, 5,(*DispMenu_MenuCode)},  // ��ʾ�����������
    { 6, 6, 6, 6, 6,(*DispMenu_MenuCodeErr)}, // ��ʾ�����������
    { 7, 7, 7, 7, 7,(*DispMenu_MenuSave)}, // �������

};

static u8 DispValueUpDataFlag = FALSE;
u8 DispMode = ReadMode;
u8 LEDLEVEL = 0;

static u8 KeyFuncIndex = KEYFUNC_MAIN;
static u8 sg_DispMainMenuIndex = MENU_INDEX_MIN;              // Ҫ��ʾ�����˵�������
static u8 sg_DispSubMainMenuIndex = MENUSUB_INDEX_READ;     // Ҫ��ʾ�����˵�������
static u8 sg_DispSetMenu1Index = MENU1_INDEX_INPT;		    // Ҫ��ʾ������һ��������
static u8 sg_DispSetMenu2_1_Index = MENU2_1_INDEX_MIN;		// Ҫ��ʾ��2-1�˵�������
static u8 sg_DispSetMenu2_2_Index = MENU2_2_INDEX_ADD;		// Ҫ��ʾ��2-2�˵�������
static u8 sg_DispSetMenu2_3_Index = MENU2_3_INDEX_CYC;		// Ҫ��ʾ��2-3�˵�������
static u8 sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MODE;		// Ҫ��ʾ��2-4�˵�������
static u8 sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MODE;		// Ҫ��ʾ��2-5�˵�������
static u8 sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MODE;		// Ҫ��ʾ��2-6�˵�������
static u8 sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MODE;		// Ҫ��ʾ��2-7�˵�������
static u8 sg_DispSetMenu2_8_Index = MENU2_8_INDEX_MODE;		// Ҫ��ʾ��2-8�˵�������
static u8 sg_DispSetMenu2_9_Index = MENU2_9_INDEX_MODE;		// Ҫ��ʾ��2-9�˵�������

typedef struct
{
	u8 CurrentFocus;	// ��ǰ�Ľ���
	u8 DispWidth;		// ��ʾλ��
}Disp_FocusStruct;
Disp_FocusStruct Disp_Focus;

static u8 sg_CurrentDispChar[13];			// Ҫ��ʾ���ַ�
static s16 sg_CurrentDispNumber;			// Ҫ��ʾ������
static s32 sg_DispSetValue = 0;				// Ҫ��ʾ����������

static u8 key_scan[KEY_NUM];				// ����ɨ��״̬
static u8 key_scan_bak[KEY_NUM];			// �ϴμ�ɨ��״̬
static u8 key_status[KEY_NUM];				// ��ǰ����״̬
static u8 key_Surestatus[KEY_NUM];		    // ��ǰ����״̬
static u16 key_LongPress_Tick[KEY_NUM];	    // ����������ֵ

u8 KeyDiff(void); // ����״̬�ж�
void DispChar(u8 num,u8 ch1, u8 ch2, u8 ch3, u8 ch4);
u16 CharToNumber(void);	// ����ʾ���ò˵��е��ַ�����ת��Ϊʮ��������
void GetSetOldValue(void);
void UpdataSetValue(UPDATA_DIR Updata_dir);
void UpdataOrSetValue(SELECT_CATE Cate,UPDATA_DIR Updata_Dir);  //������ֵ

volatile u8 vg_Display_Value[16];   // ��ʾ���滺��

//static u8 UpDataFlagNum = 0;
static BOOL sg_bSetFlashEnable = TRUE;  // ��˸ʹ��
static BOOL sg_b2sFlashEnable = TRUE;  // ��˸ʹ��
static BOOL g_bInitDefault = FALSE;		// �ϵ����ʾĬ��
static BOOL g_bUpdataDefault = FALSE;	// ��ʾĬ��
static BOOL g_bBlackLightDefault = FALSE;  // ������
BOOL g_fftEnable = FALSE;        //
BOOL g_AoOutEnable = FALSE;        //

static BOOL g_bCycleDefault = FALSE;  // ������

static BOOL g_bRestoreDlyEnable = TRUE;
static BOOL g_b1DlyEnable = TRUE;
static BOOL g_b5DlyEnable = FALSE;
static BOOL g_bBlackLightEnble = FALSE;  // ������
BOOL g_LEDEnable = TRUE;
static BOOL g_bAlarmEnble = TRUE;  // ������

static u16 sg_ReFlashCount = 0;         // û�а��������ʱֵ
static u32 sg_RestoreDlyTick = 0;
static u32 sg_AlarmDlyTick = 0;
static u16 sg_ComFlashNum = 0;
static u8 sg_ComFlag = FALSE;           // ͨ�ű�־
static BOOL sg_AoOutDely = TRUE;        // ģ�������������ʱ

static u32 s_SysStartTick = 0;
static BOOL s_bSysStartEnable = FALSE;
static u16 g_fftTick = 0;
static u32 g_BlackTick = 0;
static u16 g_CycleTick = 0;
static u32 g_AoOutDelyTick = 0;

/*--------------------------���ʱ�� ����------------------------*/
static u16 g_Out_1_tick = 0;
static u16 g_Out_2_tick = 0;
static u16 g_Out_3_tick = 0;
static u16 g_Out_4_tick = 0;

static u16 g_Out_01_Time10ms = 0;
static u16 g_Out_02_Time10ms = 0;
static u16 g_Out_03_Time10ms = 0;
static u16 g_Out_04_Time10ms = 0;

static u16 g_Out_11_Time10ms = 0;
static u16 g_Out_12_Time10ms = 0;
static u16 g_Out_13_Time10ms = 0;
static u16 g_Out_14_Time10ms = 0;


static BOOL g_b1OutOverTurn = FALSE;
static BOOL g_b2OutOverTurn = FALSE;
static BOOL g_b3OutOverTurn = FALSE;
static BOOL g_b4OutOverTurn = FALSE;


/*---------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/**
  * @brief  GUI��ʼ��.
  * @note
  * @param  None
  * @retval None
  */
void Task_GUI_init(void)
{
    for(u8 i = 0;i < 16;i++)
    {
        vg_Display_Value[i] = 0xff;
    }
    Update_screen();
    PT_TimerDelay(2000);
	KeyDiff();
}

/**
  * @brief  �õ�ĳ��������״̬.
  * @note
  * @param  KeyNo:�������
  * @retval None
  */
void OneKeyStaus(u8 KeyNo)
{
    if(g_Key_Status[KeyNo])
    {
        key_scan[KeyNo] <<= 1;
        key_scan[KeyNo] += 1;
        if((key_scan[KeyNo] == 0xff)  && (key_scan_bak[KeyNo] != 0xff))
        {
            key_status[KeyNo] |= KEY_UNPRESSED;
            if (key_LongPress_Tick[KeyNo] != 0)
            {
                key_Surestatus[KeyNo] |= KEY_PRESSED;
            }
            key_LongPress_Tick[KeyNo] = 0;
        }
    }
    else
    {
        key_scan[KeyNo] <<= 1;
        if((key_scan[KeyNo] == 0x00) && (key_scan_bak[KeyNo] != 0x00))
        {
            key_status[KeyNo] |= KEY_PRESSED;
            key_LongPress_Tick[KeyNo] = TIMER_DELAY_LONGSET ;
        }
    }
    key_scan_bak[KeyNo] = key_scan[KeyNo];
    if(key_LongPress_Tick[KeyNo])
    {
        if(!--key_LongPress_Tick[KeyNo])
        {
            key_status[KeyNo] |= KEY_LONG_PRESSED;//0x04
        }
    }
}


/**
  * @brief  ͨ��IO�ڵõ�4��������״̬,Ȼ�����ת���õ�����İ���״̬.
  * @note
  * @param  None
  * @retval None
  */
void KeyStatus(void)
{
	g_Key_Status[0] = KEY_UP_STATUS;
	g_Key_Status[1] = KEY_DOWN_STATUS;
	g_Key_Status[2] = KEY_MENU_STATUS;
	g_Key_Status[3] = KEY_OK_STATUS;


	OneKeyStaus(KEY_UP_BUTTON);
	OneKeyStaus(KEY_DOWN_BUTTON);
	OneKeyStaus(KEY_MENU_BUTTON);
	OneKeyStaus(KEY_OK_BUTTON);
}




/**
  * @brief	�Ը��ְ�����Ͻ����ж�
  * @param	None
  * @retval ������
  */
u8 KeyDiff(void)
{
    u8 Key = KEYSTATUS_NONE;
    /*********************************************************/
    if(key_Surestatus[KEY_UP_BUTTON] & KEY_PRESSED)
    {
        key_Surestatus[KEY_UP_BUTTON] &= ~KEY_PRESSED;
        Key = KEYSTATUS_UP;
    }
    if(key_Surestatus[KEY_DOWN_BUTTON] & KEY_PRESSED)
    {
        key_Surestatus[KEY_DOWN_BUTTON] &= ~KEY_PRESSED;
        Key = KEYSTATUS_DOWN;
    }
    if(key_Surestatus[KEY_MENU_BUTTON] & KEY_PRESSED)
    {
        key_Surestatus[KEY_MENU_BUTTON] &= ~KEY_PRESSED;
        Key = KEYSTATUS_MENU;
    }
    if(key_Surestatus[KEY_OK_BUTTON] & KEY_PRESSED)
    {
        key_Surestatus[KEY_OK_BUTTON] &= ~KEY_PRESSED;
        Key = KEYSTATUS_OK;
    }
    if(key_status[KEY_MENU_BUTTON] & KEY_LONG_PRESSED)
    {
        key_status[KEY_MENU_BUTTON] &= ~KEY_LONG_PRESSED;
        Key = KEYSTATUS_MENULONG;           //ֱ���˵�������
    }
    return Key;
}

/**
  * @brief	ͨ��������յ���ȷ֡�����ñ�־,��GUI�����жϸñ�־������˸��ʾ����
  * @param	None
  * @retval None
  */
void GUI_SetComFlag(void)
{
	sg_ComFlag = TRUE;
	sg_ComFlashNum = 0;
}


void GUI_Timer_On(void)
{
	static u32 s_Dly1sTick = 0;
	static u32 s_Dly5sTick = 0;
	static u16 s_FlashNum = 0;
	static u32 s_2sFlashNum = 0;
	u32 TimerDlyNum = 0;

	sg_ReFlashCount++;
	if (!s_bSysStartEnable)
	{
		s_SysStartTick++;
		if (s_SysStartTick++ > TIMER_DELAY_7S)
		{
			s_bSysStartEnable = TRUE;
			s_SysStartTick = 0;
		}
	}
    /**************************OutPut*****************************/
    if(g_Out_Status[Dout_ONE])
    {
        if(g_tParam.CtrlParam.DO1_Time != 0x00)
        {
            if(g_Out_1_tick++ >= TIMER_DELAY_10ms)
            {
                g_Out_1_tick= 0;
                if(g_b1OutOverTurn == FALSE)
                {
                    if(g_Out_01_Time10ms++ >= g_tParam.CtrlParam.DO1_Time)
                    {
                        g_Out_01_Time10ms = 0;
                        g_b1OutOverTurn = TRUE;
                        CTRL1_DisEnble;
                    }
                }
                else
                {
                    if(g_Out_11_Time10ms++ >= (10000 - g_tParam.CtrlParam.DO1_Time))
                    {
                        g_Out_11_Time10ms = 0;
                        g_b1OutOverTurn = FALSE;
                        CTRL1_Enble;
                    }
                }
            }
        }
        else
        {
             CTRL1_Enble;
        }
    }
    else
    {
        CTRL1_DisEnble;
    }
    if(g_Out_Status[Dout_TWO])
    {
        if(g_tParam.CtrlParam.DO2_Time != 0x00)
        {
            if(g_Out_2_tick++ >= TIMER_DELAY_10ms)
            {
                g_Out_2_tick= 0;
                if(g_b2OutOverTurn == FALSE)
                {
                    if(g_Out_02_Time10ms++ >= g_tParam.CtrlParam.DO2_Time/100)
                    {
                        g_Out_02_Time10ms = 0;
                        g_b2OutOverTurn = TRUE;
                        CTRL2_DisEnble;
                    }
                }
                else
                {
                    if(g_Out_12_Time10ms++ >= (10000 - g_tParam.CtrlParam.DO2_Time))
                    {
                        g_Out_12_Time10ms = 0;
                        g_b2OutOverTurn = FALSE;
                        CTRL2_Enble;
                    }
                }
            }
        }
        else
        {
             CTRL2_Enble;
        }
    }
    else
    {
        CTRL2_DisEnble;
    }
    if(g_Out_Status[Dout_THREE])
    {
        if(g_tParam.CtrlParam.DO3_Time != 0x00)
        {
            if(g_Out_3_tick++ >= TIMER_DELAY_10ms)
            {
                g_Out_3_tick= 0;
                if(g_b3OutOverTurn == FALSE)
                {
                    if(g_Out_03_Time10ms++ >= g_tParam.CtrlParam.DO3_Time)
                    {
                        g_Out_03_Time10ms = 0;
                        g_b3OutOverTurn = TRUE;
                        CTRL3_DisEnble;
                    }
                }
                else
                {
                    if(g_Out_13_Time10ms++ >= (10000 - g_tParam.CtrlParam.DO3_Time))
                    {
                        g_Out_13_Time10ms = 0;
                        g_b3OutOverTurn = FALSE;
                        CTRL3_Enble;
                    }
                }
            }
        }
        else
        {
             CTRL3_Enble;
        }
    }
    else
    {
        CTRL3_DisEnble;
    }
    if(g_Out_Status[Dout_FOUR])
    {
        if(g_tParam.CtrlParam.DO4_Time != 0x00)
        {
            if(g_Out_4_tick++ >= TIMER_DELAY_10ms)
            {
                g_Out_4_tick= 0;
                if(g_b4OutOverTurn == FALSE)
                {
                    if(g_Out_04_Time10ms++ >= g_tParam.CtrlParam.DO4_Time)
                    {
                        g_Out_04_Time10ms = 0;
                        g_b4OutOverTurn = TRUE;
                        CTRL4_DisEnble;
                    }
                }
                else
                {
                    if(g_Out_14_Time10ms++ >= (10000 - g_tParam.CtrlParam.DO4_Time))
                    {
                        g_Out_14_Time10ms = 0;
                        g_b4OutOverTurn = FALSE;
                        CTRL4_Enble;
                    }
                }
            }
        }
        else
        {
             CTRL4_Enble;
        }
    }
    else
    {
        CTRL4_DisEnble;
    }
	/**************************δ����300S��ر���ʾ*****************
	if (g_bOffDispDlyEnable)
	{
		if (sg_OffDispDlyTick++ >= TIMER_DELAY_300S)// 300s��ر���ʾ
		{
			sg_OffDispDlyTick = 0;
			g_bOffDispDlyEnable = FALSE;  // �ر���ʾʱ�����
		}
	}
	else
	{
		sg_OffDispDlyTick = 0;
	}*/

    /**************************ѭ����ʾ*******************************/
    if(g_tParam.CtrlParam.Cycle == CYCYES)
    {
        g_bUpdataDefault = FALSE;    
    }
    if((g_tParam.CtrlParam.Cycle == CYCYES) && g_bCycleDefault)
    {
        if( g_CycleTick++ >= TIMER_DELAY_5S)
        {
            g_CycleTick = 0;
            g_bCycleDefault = FALSE;
            sg_DispMainMenuIndex++;
			if(sg_DispMainMenuIndex > MENU_INDEX_MAX)
			{
			    sg_DispMainMenuIndex = MENU_INDEX_MIN;
			}
        }
    }
    else
    {
        g_CycleTick = 0;
        g_bCycleDefault = TRUE;
    }

    /******************************����*******************************/
    if ( g_bBlackLightDefault )
    {
        if(g_BlackTick ++ >= TIMER_DELAY_1S * g_tParam.CtrlParam.BlackTime)
        {
            g_BlackTick = 0;
            //g_bBlackLightDefault = FALSE;
            g_bBlackLightEnble = FALSE;
        }
    }
    else
    {
        g_BlackTick = 0;
        g_bBlackLightEnble = TRUE;
    }

    /**************************FFT�����ʼ����ʱ**********************/
    if (g_fftEnable)
	{
		if (g_fftTick++ >= TIMER_DELAY_1S)// 300s��ر���ʾ
		{
			g_fftTick = 0;
			g_fftEnable = FALSE;  // �ر���ʾʱ�����
		}
	}
	else
	{
		g_fftTick = 0;
	}

    /**************************��������120S����ʾĬ�Ͻ���************/
	if (g_bRestoreDlyEnable && (g_tParam.CtrlParam.Cycle != CYCYES))
	{
		//TimerDlyNum = TIMER_DELAY_120S;         // ��ʱ120��
		TimerDlyNum = TIMER_DELAY_30M;
		if (sg_RestoreDlyTick++ > TimerDlyNum)  // ��ʾĬ�Ͻ���
		{
			sg_RestoreDlyTick = 0;
			g_bRestoreDlyEnable = FALSE;
			g_bUpdataDefault = TRUE;
		}
	}
	else
	{
		sg_RestoreDlyTick = 0;
	}
    /**************************����1S��ʱ****************************/
	if (g_b1DlyEnable)
	{
		if (s_Dly1sTick++ >= TIMER_DELAY_1S)
		{
			s_Dly1sTick = 0;
			g_bInitDefault = TRUE;
			g_b1DlyEnable = FALSE;
		}
	}
	/**************************����5S_Ao��ʱ****************************/
	if (sg_AoOutDely)
	{
		if (g_AoOutDelyTick ++ >= TIMER_DELAY_5S)
		{
			g_AoOutDelyTick = 0;
			g_AoOutEnable = TRUE;
			sg_AoOutDely = FALSE;
		}
	}
	/**************************���������淵��**********************/
	if (g_b5DlyEnable)
	{
		if (s_Dly5sTick++ >= TIMER_DELAY_5S)
		{
			s_Dly5sTick = 0;
			g_b5DlyEnable = FALSE;
			sg_DispSetValue = 0;
			KeyFuncIndex = KEYFUNC_MENUCODE;
			Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
			KeyFuncPtr=Key_Tab[KeyFuncIndex].CurrentOperate;
		}
	}
	/**************************��˸��ʶ******************************/
	s_FlashNum++;
	if (s_FlashNum >= TIMER_DELAY_750ms)
	{
		s_FlashNum = 0;
		sg_bSetFlashEnable = !sg_bSetFlashEnable;
	}
	/**************************��˸��ʶ******************************/
	s_2sFlashNum++;
	if (s_2sFlashNum >= TIMER_DELAY_2S)
	{
		s_2sFlashNum = 0;
		sg_b2sFlashEnable = !sg_b2sFlashEnable;
	}
    /**************************ͨѶ*****��****************************/
	if (sg_ComFlag)
	{
		sg_ComFlashNum++;
		if (sg_ComFlashNum >= TIMER_DELAY_500ms)
		{
			sg_ComFlashNum = 0;
			sg_ComFlag = FALSE;
		}
	}
	else
	{
		sg_ComFlashNum = 0;
	}
	/**************************����*****��ʱ**************************/
	if((g_OverCurr[PH_A] || g_OverCurr[PH_B] || g_OverCurr[PH_C]))
	{
        if (!g_bAlarmEnble)
        {
            sg_AlarmDlyTick++;
            if (sg_AlarmDlyTick >= TIMER_DELAY_60S)
            {
                sg_AlarmDlyTick = 0;
                g_bAlarmEnble = TRUE;
            }
        }
        else
        {
            sg_ComFlashNum = 0;
        }
     }
}

void Task_Timer_Function(void)
{
	GUI_Timer_On();
	KeyStatus();
}

void GUI_Key_Menu(void)     //�˵�������
{
	switch (KeyFuncIndex)
	{
    	case KEYFUNC_MAIN:
    	    g_bUpdataDefault = TRUE;  // �ָ���Ĭ�Ͻ���
    		break;
    	case KEYFUNC_MENU1:
    	    g_bUpdataDefault = TRUE;  // �ָ���Ĭ�Ͻ���
            break;
    	case KEYFUNC_MENU2:
    	    if(DispMode == ProgMode)
    	    {
                KeyFuncIndex = KEYFUNC_MENUSAVE;        //�����ö����˵��˻ص�������
    	    }
            else
            {
                KeyFuncIndex = KEYFUNC_MAIN;
                DispMode = ReadMode;
            }
            sg_DispSubMainMenuIndex = MENUSUB_INDEX_READ;
    		sg_DispSetMenu1Index = MENU1_INDEX_INPT;
    		sg_DispSetMenu2_1_Index = MENU2_1_INDEX_NET;
    		sg_DispSetMenu2_2_Index = MENU2_2_INDEX_ADD;
    		sg_DispSetMenu2_3_Index = MENU2_3_INDEX_CYC;
    		sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MODE;
            sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MODE;
    		sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MODE;
    		sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MODE;
    		sg_DispSetMenu2_8_Index = MENU2_8_INDEX_MODE;
    		sg_DispSetMenu2_9_Index = MENU2_9_INDEX_MODE;
    		sg_DispSetValue = SaveNO;
    		break;
    	case KEYFUNC_MENU3:
	  	    KeyFuncIndex = KEYFUNC_MENU2;
    		sg_DispSetMenu2_1_Index = MENU2_1_INDEX_NET;
    		sg_DispSetMenu2_2_Index = MENU2_2_INDEX_ADD;
    		sg_DispSetMenu2_3_Index = MENU2_3_INDEX_CYC;
    		sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MODE;
            sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MODE;
    		sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MODE;
    		sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MODE;
    		sg_DispSetMenu2_8_Index = MENU2_8_INDEX_MODE;
    		sg_DispSetMenu2_9_Index = MENU2_9_INDEX_MODE;
    		break;
    	case KEYFUNC_MENUVALUE:
    	  	KeyFuncIndex = KEYFUNC_MENU3;
    		break;
		case KEYFUNC_MENUCODE:
			KeyFuncIndex = KEYFUNC_MENU1;
			sg_DispSubMainMenuIndex = MENUSUB_INDEX_PROG;
			sg_DispSetMenu1Index = MENU1_INDEX_INPT;
    		sg_DispSetMenu2_1_Index = MENU2_1_INDEX_NET;
    		sg_DispSetMenu2_2_Index = MENU2_2_INDEX_ADD;
    		sg_DispSetMenu2_3_Index = MENU2_3_INDEX_CYC;
    		sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MODE;
            sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MODE;
    		sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MODE;
    		sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MODE;
    		sg_DispSetMenu2_8_Index = MENU2_8_INDEX_MODE;
    		sg_DispSetMenu2_9_Index = MENU2_9_INDEX_MODE;
    		break;
    	case KEYFUNC_MENUCODEERR:
    	    KeyFuncIndex = KEYFUNC_MENUCODE;
    		break;
    	case KEYFUNC_MENUSAVE:
    	    KeyFuncIndex = KEYFUNC_MENU2;
			sg_DispSetMenu1Index = MENU1_INDEX_INPT;  // ������ȷ �������ò˵�
    	    break;
        default:
            g_bUpdataDefault = TRUE;
            break;
    	}
	    KeyFuncPtr=Key_Tab[KeyFuncIndex].CurrentOperate;
}


void GUI_Key_Ok(void)
{
	switch (KeyFuncIndex)
	{
		case KEYFUNC_MAIN:
		    switch(sg_DispMainMenuIndex)
		    {
                case MENU_INDEX_U:
                    sg_DispMainMenuIndex = MENU_INDEX_Uavr;
                    break;
                case MENU_INDEX_Uavr:
                    sg_DispMainMenuIndex = MENU_INDEX_U;
                    break;
                case MENU_INDEX_LU:
                    sg_DispMainMenuIndex = MENU_INDEX_LUavr;
                    break;
                case MENU_INDEX_LUavr:
                    sg_DispMainMenuIndex = MENU_INDEX_LU;
                    break;
                case MENU_INDEX_I:
                    sg_DispMainMenuIndex = MENU_INDEX_Iavr;
                    break;
                case MENU_INDEX_Iavr:
                    sg_DispMainMenuIndex = MENU_INDEX_I;
                    break;
                case MENU_INDEX_P:
                    if(g_tParam.CtrlParam.NetMode == N34)
                    {
                        sg_DispMainMenuIndex = MENU_INDEX_Pe;
                    }
                    break;
                case MENU_INDEX_Pe:
                    sg_DispMainMenuIndex = MENU_INDEX_P;
                    break;
                case MENU_INDEX_Q:
                    sg_DispMainMenuIndex = MENU_INDEX_Qe;
                    break;
                case MENU_INDEX_Qe:
                    sg_DispMainMenuIndex = MENU_INDEX_Q;
                    break;
                case MENU_INDEX_S:
                    sg_DispMainMenuIndex = MENU_INDEX_Se;
                    break;
                case MENU_INDEX_Se:
                    sg_DispMainMenuIndex = MENU_INDEX_S;
                    break;
                case MENU_INDEX_PF:
                    if(g_tParam.CtrlParam.NetMode == N34)
                    {
                        sg_DispMainMenuIndex = MENU_INDEX_PFe;
                    }
                    break;
                case MENU_INDEX_PFe:
                    sg_DispMainMenuIndex = MENU_INDEX_PF;
                    break;
                default:
                    break;
		    }
			break;
		case KEYFUNC_MENU1:
		    DispCtrlParam = g_tParam.CtrlParam;
		    if( sg_DispSubMainMenuIndex == MENUSUB_INDEX_PROG)
		    {
                DispMode = ProgMode;  // ��ʾģʽ��־λ
                KeyFuncIndex = KEYFUNC_MENUCODE;
                Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                LEDLEVEL = DispCtrlParam.BlackTime;
			    sg_DispSetValue = 0x00;
		    }
		    else if( sg_DispSubMainMenuIndex == MENUSUB_INDEX_READ)
		    {
		        DispMode = ReadMode;  // ��ʾģʽ��־λ
                KeyFuncIndex = KEYFUNC_MENU2;
		    }
			break;
		case KEYFUNC_MENU2:
		    if(DispMode == ReadMode)
		    {
                GetSetOldValue();
		    }
            KeyFuncIndex = KEYFUNC_MENU3;
			break;
		case KEYFUNC_MENU3:
		    if(DispMode == ProgMode)
		    {
		        GetSetOldValue();
    			KeyFuncIndex = KEYFUNC_MENUVALUE;
    			if(sg_DispSetMenu1Index == MENU1_INDEX_VER)
    				KeyFuncIndex = KEYFUNC_MENU3;
    	    }
			break;
		case KEYFUNC_MENUVALUE:
		    if(DispMode == ProgMode)
		    {
		        if((sg_DispSetValue == SaveYes) && (sg_DispSetMenu2_3_Index == MENU2_3_INDEX_CLRE))
		        {
                    ElectricEnergy.PosEPT = 0;
                    ElectricEnergy.PosEQT = 0;
                    ElectricEnergy.NegEPT = 0;
                    ElectricEnergy.NegEQT = 0;
                    KeyFuncIndex = KEYFUNC_MENU3;
		        }
		        else
		        {
    		        KeyFuncIndex = KEYFUNC_MENU3;
    		        GetSetNewValue();
		        }
		    }
			break;
		case KEYFUNC_MENUCODE:
			if(sg_DispSetValue == g_tParam.CtrlParam.Code)
			{
				KeyFuncIndex = KEYFUNC_MENU2;
				sg_DispSetMenu1Index = MENU1_INDEX_INPT;  //������ȷ �������ò˵�
			}
			else
			{
				KeyFuncIndex = KEYFUNC_MENUCODEERR;
				g_b5DlyEnable = TRUE;
			}
			break;
		case KEYFUNC_MENUCODEERR:
		    break;
		case KEYFUNC_MENUSAVE: //���ݱ������
            if((sg_DispSetValue == SaveYes)&&(DispValueUpDataFlag == TRUE))
            {
                if((g_tParam.CtrlParam.Baud485 != DispCtrlParam.Baud485) || (g_tParam.CtrlParam.DataFormat != DispCtrlParam.DataFormat))
                {
                    g_tParam.CtrlParam.Baud485 = DispCtrlParam.Baud485;
                    g_tParam.CtrlParam.DataFormat = DispCtrlParam.DataFormat;
                    USART_Configuration();
                    PT_TimerDelay(10);
                }
                if(g_tParam.CtrlParam.NetMode != DispCtrlParam.NetMode)
                {
                    g_tParam.CtrlParam = DispCtrlParam;
                    SaveParam();
                    DispValueUpDataFlag = FALSE;
                    g_bUpdataDefault = TRUE;
                    DispMode = ReadMode;
                    NVIC_SystemReset();
                }
                g_tParam.CtrlParam = DispCtrlParam;
                SaveParam();
                DispValueUpDataFlag = FALSE;
            }
            g_bUpdataDefault = TRUE;
            DispMode = ReadMode;
		    break;
		default:
            g_bUpdataDefault = TRUE;
		    break;
		}
	KeyFuncPtr=Key_Tab[KeyFuncIndex].CurrentOperate;
}


void GUI_Key_MenuLong(void)  //�˵������� ֻ�������˵�ģʽ������ ����ģʽѡ��
{
	if (KeyFuncIndex == KEYFUNC_MAIN)
	{
			KeyFuncIndex = KEYFUNC_MENU1;
	}
	KeyFuncPtr=Key_Tab[KeyFuncIndex].CurrentOperate;
}


void GUI_Key_Up(void)       //�󰴼� ʵ��:��ȥ
{
    switch (KeyFuncIndex)
	{
		case KEYFUNC_MAIN:      //�����˵�
            if(g_tParam.CtrlParam.NetMode == N34)
			{
                if(sg_DispMainMenuIndex >= 0x40)
                {
                    sg_DispMainMenuIndex = sg_DispMainMenuIndex - 0x40;
                }
                sg_DispMainMenuIndex--;
			}
			else
			{
                if(sg_DispMainMenuIndex == MENU_INDEX_LU | sg_DispMainMenuIndex == MENU_INDEX_LUavr)
                {
                    sg_DispMainMenuIndex = MENU_INDEX_MAX;
                }
                else if(sg_DispMainMenuIndex == MENU_INDEX_PF)
                {
                    sg_DispMainMenuIndex = MENU_INDEX_P;
                }
                else
                {
                    if(sg_DispMainMenuIndex >= 0x40)
                    {
                        sg_DispMainMenuIndex = sg_DispMainMenuIndex - 0x40;
                    }
                    sg_DispMainMenuIndex--;
                }
			}
			if(sg_DispMainMenuIndex > MENU_INDEX_MAX)
			{
			    sg_DispMainMenuIndex = MENU_INDEX_MAX;
			}
			break;
		case KEYFUNC_MENU1:      //�Ӳ˵�  �鿴/���
			sg_DispSubMainMenuIndex--;
			if(sg_DispSubMainMenuIndex > MENUSUB_INDEX_MAX)
			{
			    sg_DispSubMainMenuIndex = MENUSUB_INDEX_MAX;
            }
			break;
		case KEYFUNC_MENU2:
            sg_DispSetMenu1Index--;
			if(DispMode == ReadMode)
			{
                if(sg_DispSetMenu1Index > MENU1_INDEX_RMAX)
			    {
			        sg_DispSetMenu1Index = MENU1_INDEX_RMAX;
                }
			}
			else
			{
                if(sg_DispSetMenu1Index > MENU1_INDEX_MAX)
			    {
			        sg_DispSetMenu1Index = MENU1_INDEX_MAX;
                }
			}
			break;
		case KEYFUNC_MENU3:
            if(sg_DispSetMenu1Index == MENU1_INDEX_INPT)
			{
				sg_DispSetMenu2_1_Index--;
				if(sg_DispSetMenu2_1_Index > MENU2_1_INDEX_MAX)
				{
				    sg_DispSetMenu2_1_Index = MENU2_1_INDEX_MAX;
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_COM1)
			{
				sg_DispSetMenu2_2_Index--;
				if(sg_DispSetMenu2_2_Index > MENU2_2_INDEX_MAX)
				{
				    sg_DispSetMenu2_2_Index = MENU2_2_INDEX_MAX;
				}
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_SYS)
			{
                sg_DispSetMenu2_3_Index--;
                if(DispMode == ReadMode)
                {
                    if(sg_DispSetMenu2_3_Index > MENU2_3_INDEX_RMAX)
                    {
                        sg_DispSetMenu2_3_Index = MENU2_3_INDEX_RMAX;
                    }
                }
                else
                {
                    if(sg_DispSetMenu2_3_Index > MENU2_3_INDEX_MAX)
                    {
                        sg_DispSetMenu2_3_Index = MENU2_3_INDEX_MAX;
                    }
                }
			}
            else if(sg_DispSetMenu1Index == MENU1_INDEX_DO1)
			{
                if(DispCtrlParam.DO1_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MODE;
                }
                else if(DispCtrlParam.DO1_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_4_Index--;
    				if(sg_DispSetMenu2_4_Index > MENU2_4_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_TIME;
                    }
                }
                else
                {
                    if((DispCtrlParam.DO1_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO1_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_4_Index--;
        				if(sg_DispSetMenu2_4_Index > MENU2_4_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_ITEM;
                        }
                    }
                    else
                    {
                        sg_DispSetMenu2_4_Index--;
        				if(sg_DispSetMenu2_4_Index > MENU2_4_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MAX;
                        }
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_DO2)
			{
				if(DispCtrlParam.DO2_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MODE;
                }
                else if(DispCtrlParam.DO2_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_5_Index--;
    				if(sg_DispSetMenu2_5_Index > MENU2_5_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_TIME;
                    }
                }
                else
                {
                    if((DispCtrlParam.DO2_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO2_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_5_Index--;
        				if(sg_DispSetMenu2_5_Index > MENU2_5_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_ITEM;
                        }
                    }
                    else
                    {
                        sg_DispSetMenu2_5_Index--;
        				if(sg_DispSetMenu2_5_Index > MENU2_5_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MAX;
                        }
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_DO3)
			{
				if(DispCtrlParam.DO3_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MODE;
                }
                else if(DispCtrlParam.DO3_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_6_Index--;
    				if(sg_DispSetMenu2_6_Index > MENU2_6_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_TIME;
                    }
                }
                else
                {
                    if((DispCtrlParam.DO3_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO3_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_6_Index--;
        				if(sg_DispSetMenu2_6_Index > MENU2_6_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_ITEM;
                        }
                    }
                    else
                    {
                        sg_DispSetMenu2_6_Index--;
        				if(sg_DispSetMenu2_6_Index > MENU2_6_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MAX;
                        }
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_DO4)
			{
				if(DispCtrlParam.DO4_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MODE;
                }
                else if(DispCtrlParam.DO4_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_7_Index--;
    				if(sg_DispSetMenu2_7_Index > MENU2_7_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_TIME;
                    }
                }
                else
                {
                    if((DispCtrlParam.DO4_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO4_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_7_Index--;
        				if(sg_DispSetMenu2_7_Index > MENU2_7_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_ITEM;
                        }
                    }
                    else
                    {
                        sg_DispSetMenu2_7_Index--;
        				if(sg_DispSetMenu2_7_Index > MENU2_7_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MAX;
                        }
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_AO1)
			{
			    if(DispCtrlParam.AO1_Mode == AO_MODE_OFF)
			    {
                    sg_DispSetMenu2_8_Index = AO_MODE_OFF;
			    }
			    else
			    {
                    sg_DispSetMenu2_8_Index--;
    				if(sg_DispSetMenu2_8_Index > MENU2_8_INDEX_MAX)
    				{
    				    sg_DispSetMenu2_8_Index = MENU2_8_INDEX_MAX;
                    }
			    }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_AO2)
			{
			    if(DispCtrlParam.AO2_Mode == AO_MODE_OFF)
			    {
                    sg_DispSetMenu2_9_Index = AO_MODE_OFF;
			    }
			    else
			    {
                    sg_DispSetMenu2_9_Index--;
    				if(sg_DispSetMenu2_9_Index > MENU2_9_INDEX_MAX)
    				{
    				    sg_DispSetMenu2_9_Index = MENU2_9_INDEX_MAX;
                    }
			    }
			}
			if(DispMode == ReadMode)
			{
                GetSetOldValue();
			}
			break;
		case KEYFUNC_MENUVALUE://����ֵ
		    if(DispMode == ProgMode)
		    {
		        switch(sg_DispSetMenu1Index)
		        {
                    case MENU1_INDEX_INPT:
                        if(sg_DispSetMenu2_1_Index == MENU2_1_INDEX_NET)
        		        {
                            UpdataOrSetValue(Select_Net,UPDATA_ADD);
        		        }
                        else
                        {
                            if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                            {
                                Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                            }
                    		else
                            {
                                Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                            }
                        }
                        break;
                    case MENU1_INDEX_COM1:
                        if(sg_DispSetMenu2_2_Index == MENU2_2_INDEX_BAUD)
                        {
                            UpdataOrSetValue(Select_Baud,UPDATA_SUB);
                        }
                        else if(sg_DispSetMenu2_2_Index == MENU2_2_INDEX_DATA)
                        {
                            UpdataOrSetValue(Select_Data,UPDATA_SUB);
                        }
                        else if(sg_DispSetMenu2_2_Index == MENU2_2_INDEX_COMS)
                        {
                            UpdataOrSetValue(Select_Coms,UPDATA_SUB);
                        }
                        else
                        {
                            if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                            {
                                Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                            }
                    		else
                            {
                                Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                            }
                        }
                        break;

                    case MENU1_INDEX_SYS:
        		        switch(sg_DispSetMenu2_3_Index)
        		        {
                            case MENU2_3_INDEX_CYC:
                                UpdataOrSetValue(Select_Save,UPDATA_SUB);
                                break;
                            case MENU2_3_INDEX_LIGH:
                                UpdataOrSetValue(Select_Light,UPDATA_SUB);
                                break;
                            case MENU2_3_INDEX_DISP:
                                UpdataOrSetValue(Select_Disp_Default,UPDATA_SUB);
                                break;
                            case MENU2_3_INDEX_CLRE:
                                UpdataOrSetValue(Select_Save,UPDATA_SUB);
                                break;
                            default:
                                if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                                {
                                    Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                                }
                        		else
                                {
                                    Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                                }
                                break;
        		        }
        		        break;
        		    case MENU1_INDEX_DO1:
        		        switch(sg_DispSetMenu2_4_Index)
        		        {
                            case MENU2_4_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_SUB);
                                break;
                            case MENU2_4_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_SUB);
                                break;
                            default:
                                if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                                {
                                    Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                                }
                        		else
                                {
                                    Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                                }
                                break;
        		        }
        		        break;
        		    case MENU1_INDEX_DO2:
        		        switch(sg_DispSetMenu2_5_Index)
        		        {
                            case MENU2_5_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_SUB);
                                break;
                            case MENU2_5_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_SUB);
                                break;
                            default:
                                if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                                {
                                    Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                                }
                        		else
                                {
                                    Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                                }
                                break;
        		        }
        		        break;
        		    case MENU1_INDEX_DO3:
        		        switch(sg_DispSetMenu2_6_Index)
        		        {
                            case MENU2_6_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_SUB);
                                break;
                            case MENU2_6_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_SUB);
                                break;
                            default:
                                if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                                {
                                    Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                                }
                        		else
                                {
                                    Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                                }
                                break;
        		        }
        		        break;
        		    case MENU1_INDEX_DO4:
        		        switch(sg_DispSetMenu2_7_Index)
        		        {
                            case MENU2_7_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_SUB);
                                break;
                            case MENU2_7_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_SUB);
                                break;
                            default:
                                if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                                {
                                    Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                                }
                        		else
                                {
                                    Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                                }
                                break;
        		        }
        		        break;
        		    case MENU1_INDEX_AO1:
        		        switch(sg_DispSetMenu2_8_Index)
        		        {
                            case MENU2_8_INDEX_MODE:
                                UpdataOrSetValue(Select_Ao_Mode,UPDATA_SUB);
                                break;
                            case MENU2_8_INDEX_ITEM:
                                UpdataOrSetValue(Select_Ao_item,UPDATA_SUB);
                                break;
                            default:
                                if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                                {
                                    Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                                }
                        		else
                                {
                                    Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                                }
                                break;
        		        }
        		        break;
        		    case MENU1_INDEX_AO2:
        		        switch(sg_DispSetMenu2_9_Index)
        		        {
                            case MENU2_9_INDEX_MODE:
                                UpdataOrSetValue(Select_Ao_Mode,UPDATA_SUB);
                                break;
                            case MENU2_9_INDEX_ITEM:
                                UpdataOrSetValue(Select_Ao_item,UPDATA_SUB);
                                break;
                            default:
                                if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
                                {
                                    Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
                                }
                        		else
                                {
                                    Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
                                }
                                break;
        		        }
        		    default:
        		        break;
                }
    		}
            break;
		case KEYFUNC_MENUCODE:
			if(Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
            {
                Disp_Focus.CurrentFocus = CURRENTFOCUS_3;
            }
    		else
            {
                Disp_Focus.CurrentFocus = Disp_Focus.CurrentFocus >> 1;
            }
			break;
		case KEYFUNC_MENUCODEERR:
		    break;
    	case KEYFUNC_MENUSAVE:
    	    UpdataOrSetValue(Select_Save,UPDATA_ADD);
    	    break;
	    default: //��������Ĵ���
            g_bUpdataDefault = TRUE;
    		break;
		}
	KeyFuncPtr=Key_Tab[KeyFuncIndex].CurrentOperate;
}

void GUI_Key_Down(void)  //�Ұ���
{
    switch (KeyFuncIndex)
	{
		case KEYFUNC_MAIN:      //�����˵� ����/Ƶ��
			if(g_tParam.CtrlParam.NetMode == N34)
			{
			    if(sg_DispMainMenuIndex >= 0x40)
                {
                    sg_DispMainMenuIndex = sg_DispMainMenuIndex - 0x40;
                }
			    sg_DispMainMenuIndex++;
            }
			else
			{
                if(sg_DispMainMenuIndex == MENU_INDEX_MAX)
                {
                    sg_DispMainMenuIndex = MENU_INDEX_LU;
                }
                else if(sg_DispMainMenuIndex == MENU_INDEX_P)
                {
                    sg_DispMainMenuIndex = MENU_INDEX_PF;
                }
                else
                {
                    if(sg_DispMainMenuIndex >= 0x40)
                    {
                        sg_DispMainMenuIndex = sg_DispMainMenuIndex - 0x40;
                    }
                    sg_DispMainMenuIndex++;
                }
			}
			if(sg_DispMainMenuIndex > MENU_INDEX_MAX)
			{
			    sg_DispMainMenuIndex = MENU_INDEX_MIN;
			}
			break;
	    case KEYFUNC_MENU1:
			sg_DispSubMainMenuIndex++;
			if(sg_DispSubMainMenuIndex > MENUSUB_INDEX_MAX)
			{
			    sg_DispSubMainMenuIndex = MENUSUB_INDEX_MIN;
			}
			break;
		case KEYFUNC_MENU2:
			sg_DispSetMenu1Index++;
			if(DispMode == ReadMode)
			{
                if(sg_DispSetMenu1Index > MENU1_INDEX_RMAX)
			    {
			        sg_DispSetMenu1Index = MENU1_INDEX_MIN;
                }
			}
			else
			{
                if(sg_DispSetMenu1Index > MENU1_INDEX_MAX)
			    {
			        sg_DispSetMenu1Index = MENU1_INDEX_MIN;
                }
			}
			break;
		case KEYFUNC_MENU3:
			if(sg_DispSetMenu1Index == MENU1_INDEX_INPT)
			{
				sg_DispSetMenu2_1_Index++;
				if(sg_DispSetMenu2_1_Index > MENU2_1_INDEX_MAX)
				{
				    sg_DispSetMenu2_1_Index = MENU2_1_INDEX_MIN;
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_COM1)
			{
				sg_DispSetMenu2_2_Index++;
				if(sg_DispSetMenu2_2_Index > MENU2_2_INDEX_MAX)
				{
				    sg_DispSetMenu2_2_Index = MENU2_2_INDEX_MIN;
				}
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_SYS)
			{
                sg_DispSetMenu2_3_Index++;
                if(DispMode == ReadMode)
                {
                    if(sg_DispSetMenu2_3_Index > MENU2_3_INDEX_RMAX)
                    {
                        sg_DispSetMenu2_3_Index = MENU2_3_INDEX_MIN;
                    }
                }
                else
                {
                    if(sg_DispSetMenu2_3_Index > MENU2_3_INDEX_MAX)
                    {
                        sg_DispSetMenu2_3_Index = MENU2_3_INDEX_MIN;
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_DO1)
			{
                if(DispCtrlParam.DO1_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MODE;
                }
                else if(DispCtrlParam.DO1_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_4_Index++;
    				if(sg_DispSetMenu2_4_Index > MENU2_4_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MIN;
                    }
                }
                else
                {
    				if((DispCtrlParam.DO1_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO1_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_4_Index++;
        				if(sg_DispSetMenu2_4_Index > MENU2_4_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MIN;
        				}
                    }
                    else
                    {
                        sg_DispSetMenu2_4_Index++;
        				if(sg_DispSetMenu2_4_Index > MENU2_4_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MIN;
        				}
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_DO2)
			{
				if(DispCtrlParam.DO2_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MODE;
                }
                else if(DispCtrlParam.DO2_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_5_Index++;
    				if(sg_DispSetMenu2_5_Index > MENU2_5_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MIN;
                    }
                }
                else
                {
                    if((DispCtrlParam.DO2_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO2_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_5_Index++;
        				if(sg_DispSetMenu2_5_Index > MENU2_5_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MIN;
        				}
                    }
                    else
                    {
                        sg_DispSetMenu2_5_Index++;
        				if(sg_DispSetMenu2_5_Index > MENU2_5_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MIN;
        				}
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_DO3)
			{
				if(DispCtrlParam.DO3_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MODE;
                }
                else if(DispCtrlParam.DO3_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_6_Index++;
    				if(sg_DispSetMenu2_6_Index > MENU2_6_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MIN;
                    }
                }
                else
                {
                    if((DispCtrlParam.DO3_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO3_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_6_Index++;
        				if(sg_DispSetMenu2_6_Index > MENU2_6_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MIN;
        				}
                    }
                    else
                    {
                        sg_DispSetMenu2_6_Index++;
        				if(sg_DispSetMenu2_6_Index > MENU2_6_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MIN;
        				}
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_DO4)
			{
				if(DispCtrlParam.DO4_Mode == DO_MODE_OFF)
                {
                    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MODE;
                }
                else if(DispCtrlParam.DO4_Mode == DO_MODE_REM)
                {
                    sg_DispSetMenu2_7_Index++;
    				if(sg_DispSetMenu2_7_Index > MENU2_7_INDEX_TIME)
    				{
    				    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MIN;
                    }
                }
                else
                {
                    if((DispCtrlParam.DO4_Item >= DO_ITEM_DI1_H) && (DispCtrlParam.DO4_Item <= DO_ITEM_DI4_L))
                    {
                        sg_DispSetMenu2_7_Index++;
        				if(sg_DispSetMenu2_7_Index > MENU2_7_INDEX_ITEM)
        				{
        				    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MIN;
        				}
                    }
                    else
                    {
                        sg_DispSetMenu2_7_Index++;
        				if(sg_DispSetMenu2_7_Index > MENU2_7_INDEX_MAX)
        				{
        				    sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MIN;
        				}
                    }
                }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_AO1)
			{
			    if(DispCtrlParam.AO1_Mode == AO_MODE_OFF)
			    {
                    sg_DispSetMenu2_8_Index = AO_MODE_OFF;
			    }
			    else
			    {
                    sg_DispSetMenu2_8_Index++;
    				if(sg_DispSetMenu2_8_Index > MENU2_8_INDEX_MAX)
    				{
    				    sg_DispSetMenu2_8_Index = MENU2_8_INDEX_MIN;
    				}
			    }
			}
			else if(sg_DispSetMenu1Index == MENU1_INDEX_AO2)
			{
				if(DispCtrlParam.AO2_Mode == AO_MODE_OFF)
			    {
                    sg_DispSetMenu2_9_Index = AO_MODE_OFF;
			    }
			    else
			    {
                    sg_DispSetMenu2_9_Index++;
    				if(sg_DispSetMenu2_9_Index > MENU2_9_INDEX_MAX)
    				{
    				    sg_DispSetMenu2_9_Index = MENU2_9_INDEX_MIN;
    				}
			    }
			}
			if(DispMode == ReadMode)
			{
                GetSetOldValue();
			}
			break;
		case KEYFUNC_MENUVALUE://����ֵ
		    if(DispMode == ProgMode)
		    {
		        switch(sg_DispSetMenu1Index)
		        {
                    case MENU1_INDEX_INPT:
                        switch(sg_DispSetMenu2_1_Index)
                        {
                            case MENU2_1_INDEX_NET:
                                UpdataOrSetValue(Select_Net,UPDATA_ADD);
                                break;
                            case MENU2_1_INDEX_PT:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_1_INDEX_CT:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                        		break;
                        }
                        break;
                    case MENU1_INDEX_COM1:
                        switch(sg_DispSetMenu2_2_Index)
                        {
                            case MENU2_2_INDEX_ADD:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_2_INDEX_BAUD:
                                UpdataOrSetValue(Select_Baud,UPDATA_ADD);
                                break;
                            case MENU2_2_INDEX_DATA:
                                UpdataOrSetValue(Select_Data,UPDATA_ADD);
                                break;
                            case MENU2_2_INDEX_COMS:
                                UpdataOrSetValue(Select_Coms,UPDATA_ADD);
                                break;
                            default:
                        		break;
                        }
                        break;
                    case MENU1_INDEX_SYS:
                        switch(sg_DispSetMenu2_3_Index)
                        {
                            case MENU2_3_INDEX_CYC:
                                UpdataOrSetValue(Select_Save,UPDATA_ADD);
                                break;
                            case MENU2_3_INDEX_LIGH:
                                UpdataOrSetValue(Select_Light,UPDATA_ADD);
                                break;
                            case MENU2_3_INDEX_DISP:
                                UpdataOrSetValue(Select_Disp_Default,UPDATA_ADD);
                                break;
                            case MENU2_3_INDEX_ALR:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_3_INDEX_CLRE:
                                UpdataOrSetValue(Select_Save,UPDATA_ADD);
                                break;
                            case MENU2_3_INDEX_CODE:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                        		break;
                        }
                        break;
                    case MENU1_INDEX_DO1:
                        switch(sg_DispSetMenu2_4_Index)
                        {
                            case MENU2_4_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_ADD);
                                break;
                            case MENU2_4_INDEX_TIME:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_4_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_ADD);
                                break;
                            case MENU2_4_INDEX_UAL:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_4_INDEX_HYS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_4_INDEX_DELAY:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                                break;
                        }
                        break;
                    case MENU1_INDEX_DO2:
                        switch(sg_DispSetMenu2_5_Index)
                        {
                            case MENU2_5_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_ADD);
                                break;
                            case MENU2_5_INDEX_TIME:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_5_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_ADD);
                                break;
                            case MENU2_5_INDEX_UAL:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_5_INDEX_HYS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_5_INDEX_DELAY:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                                break;
                        }
                        break;
                    case MENU1_INDEX_DO3:
                        switch(sg_DispSetMenu2_6_Index)
                        {
                            case MENU2_6_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_ADD);
                                break;
                            case MENU2_6_INDEX_TIME:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_6_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_ADD);
                                break;
                            case MENU2_6_INDEX_UAL:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_6_INDEX_HYS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_6_INDEX_DELAY:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                                break;
                        }
                        break;
                    case MENU1_INDEX_DO4:
                        switch(sg_DispSetMenu2_7_Index)
                        {
                            case MENU2_7_INDEX_MODE:
                                UpdataOrSetValue(Select_Do_Mode,UPDATA_ADD);
                                break;
                            case MENU2_7_INDEX_TIME:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_7_INDEX_ITEM:
                                UpdataOrSetValue(Select_Do_item,UPDATA_ADD);
                                break;
                            case MENU2_7_INDEX_UAL:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_7_INDEX_HYS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_7_INDEX_DELAY:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                                break;
                        }
                        break;
                    case MENU1_INDEX_AO1:
                        switch(sg_DispSetMenu2_8_Index)
                        {
                            case MENU2_8_INDEX_MODE:
                                UpdataOrSetValue(Select_Ao_Mode,UPDATA_ADD);
                                break;
                            case MENU2_8_INDEX_ITEM:
                                UpdataOrSetValue(Select_Ao_item,UPDATA_ADD);
                                break;
                            case MENU2_8_INDEX_DS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_8_INDEX_FS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                                break;
                        }
                        break;
                    case MENU1_INDEX_AO2:
                        switch(sg_DispSetMenu2_9_Index)
                        {
                            case MENU2_9_INDEX_MODE:
                                UpdataOrSetValue(Select_Ao_Mode,UPDATA_ADD);
                                break;
                            case MENU2_9_INDEX_ITEM:
                                UpdataOrSetValue(Select_Ao_item,UPDATA_ADD);
                                break;
                            case MENU2_9_INDEX_DS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            case MENU2_9_INDEX_FS:
                                UpdataSetValue(UPDATA_ADD);
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
		        }
    		}
            break;
		case KEYFUNC_MENUCODE:
			UpdataSetValue(UPDATA_ADD);
			break;
		case KEYFUNC_MENUCODEERR:
		    break;
    	case KEYFUNC_MENUSAVE:
    	    UpdataOrSetValue(Select_Save,UPDATA_SUB);
            break;
        default: //��������Ĵ���
            g_bUpdataDefault = TRUE;
    		break;
		}
	KeyFuncPtr=Key_Tab[KeyFuncIndex].CurrentOperate;
}


void GUI_Key_Default(u8 Key)
{
    // Ĭ�ϵ�������
	if ((Key == KEYSTATUS_NONE && g_bInitDefault) || g_bUpdataDefault)
	{
		g_bInitDefault = FALSE;
        KeyFuncIndex = KEYFUNC_MAIN;
        switch(g_tParam.CtrlParam.DefaultDisp)
        {
            case DISP_UINT_U:
                if(g_tParam.CtrlParam.NetMode == N34)
                {
                    sg_DispMainMenuIndex = MENU_INDEX_U;
                }
                else if(g_tParam.CtrlParam.NetMode == N33)
                {
                    sg_DispMainMenuIndex = MENU_INDEX_LU;
                }
                break;
            case DISP_UINT_I:
                sg_DispMainMenuIndex = MENU_INDEX_I;
                break;
            case DISP_UINT_P:
                sg_DispMainMenuIndex = MENU_INDEX_P;
                break;
            case DISP_UINT_PF:
                sg_DispMainMenuIndex = MENU_INDEX_PF;
                break;
            case DISP_UINT_EP:
                sg_DispMainMenuIndex = MENU_INDEX_PosEPT;
                break;
            case DISP_UINT_THD:
                sg_DispMainMenuIndex = MENU_INDEX_HarmU;
                break;
            //case DISP_UINT_DEM:
                //sg_DispMainMenuIndex = MENU_INDEX_;
                //break;
            default:
                sg_DispMainMenuIndex = MENU_INDEX_U;
                break;
        }
		sg_DispSetMenu1Index = MENU1_INDEX_INPT;
		sg_DispSetMenu2_1_Index = MENU2_1_INDEX_MIN;
		sg_DispSetMenu2_2_Index = MENU2_2_INDEX_ADD;
		sg_DispSetMenu2_3_Index = MENU2_3_INDEX_CYC;
		sg_DispSetMenu2_4_Index = MENU2_4_INDEX_MODE;
		sg_DispSetMenu2_5_Index = MENU2_5_INDEX_MODE;
		sg_DispSetMenu2_6_Index = MENU2_6_INDEX_MODE;
		sg_DispSetMenu2_7_Index = MENU2_7_INDEX_MODE;
		KeyFuncPtr=Key_Tab[KeyFuncIndex].CurrentOperate;
	}

}


void GUI_Main(void)
{
    u8 Key = KeyDiff();

    switch(Key)
	{
    	case KEYSTATUS_UP:      // ���ϼ�
    	{
    	    g_bRestoreDlyEnable = FALSE;
    	    g_bUpdataDefault = FALSE;
    	    g_bBlackLightDefault = FALSE;
    	    GUI_Key_Up();
    		break;
    	}
    	case KEYSTATUS_DOWN:    // ���¼�
    	{
    	    g_bRestoreDlyEnable = FALSE;
    	    g_bUpdataDefault = FALSE;
    	    g_bBlackLightDefault = FALSE;
    	    GUI_Key_Down();
    		break;
    	}
    	case KEYSTATUS_MENU:    // ����� MENU
    	{
    	    g_bRestoreDlyEnable = FALSE;
    	    g_bUpdataDefault = FALSE;
    	    g_bBlackLightDefault = FALSE;

    	    GUI_Key_Menu();
    		break;
        }
    	case KEYSTATUS_OK:      // ���Ҽ� ȷ����
    	{
    	    g_bRestoreDlyEnable = FALSE;
    	    g_bUpdataDefault = FALSE;
    	    g_bBlackLightDefault = FALSE;
    	    GUI_Key_Ok();
    		break;
        }
    	case KEYSTATUS_MENULONG: //MENU ������
    	{
    	    g_bRestoreDlyEnable = FALSE;
            g_bUpdataDefault = FALSE;
            g_bBlackLightDefault = FALSE;
    	    GUI_Key_MenuLong();
    		break;
        }
    	//---------------------------------------------------------------------------
    	//---------------------------------------------------------------------------
    	default: //��������Ĵ���
    	    g_bRestoreDlyEnable = TRUE;
    	    g_bBlackLightDefault = TRUE;
    		break;
    }
    GUI_Key_Default(Key);

	if (KeyFuncPtr != NULL)
	{
		(*KeyFuncPtr)();//ִ�е�ǰ�����Ĳ���
	}

}

void Task_GUI_Function(void)
{
	GUI_Main();
    Update_screen();
}

void Disp_Set_FU(u8 Index, u8 *pFuData)
{
    *pFuData = CHARMODE_FU;
    sg_CurrentDispChar[Index] = NEG_NUM;
}

/**
  * @brief	��ʾ��ѹֵ
  * @param	s16 DispNum-Ҫ��ʾ������
			u8 Decimal-С����λ��
			u8 DispWidth-��ʾ���(��λ��)
			BOOL bFlash-�Ƿ���˸
			u8 FlashDec-��˸��λ��
			BOOL bEnableDisp-ǿ����ʾȫ��λ
  * @retval None
  * ���ӷ�����ʾ
  */

void DispValueVoltage(u8 num,s32 DispNum, u8 Decimal, u8 DispWidth, BOOL bFlash, u8 FlashDec, BOOL bEnableDisp, u8 NumLeve)
{
    if(DispNum < 10000)
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 2;
        }
#if(FUNCTION_VOLTAGE == 1)
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 0;
        }
#else
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 3;
        }
#endif
        else if( NumLeve & 0x01 )
        {
            DispNum = DispNum;
            Decimal = 1;
        }
    }
    else if((DispNum >= 10000) && (DispNum < 100000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 2;
        }
#if(FUNCTION_VOLTAGE == 1)
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 0;
        }
#else
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 3;
        }
#endif
    }
    else if((DispNum >= 100000) && (DispNum < 1000000))  //����ѹ��Χ
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 2;
        }
    }
    else if((DispNum >= 1000000) && (DispNum < 10000000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
    }
    else if((DispNum >= 10000000) && (DispNum < 100000000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
    }
    else if((DispNum >= 100000000) && (DispNum < 1000000000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
    }
    DispValue(num,DispNum,Decimal, 4, FALSE,0, TRUE, FALSE);
}



/**
  * @brief	��ʾ����ֵ
  * @param	s16 DispNum-Ҫ��ʾ������
			u8 Decimal-С����λ��
			u8 DispWidth-��ʾ���(��λ��)
			BOOL bFlash-�Ƿ���˸
			u8 FlashDec-��˸��λ��
			BOOL bEnableDisp-ǿ����ʾȫ��λ
  * @retval None
  * ���ӷ�����ʾ
  */

void DispValueCurrent(u8 num,s32 DispNum, u8 Decimal, u8 DispWidth, BOOL bFlash, u8 FlashDec, BOOL bEnableDisp, u8 NumLeve)
{
    if(DispNum < 10000)
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 1;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 2;
        }
#if(FUNCTION_CURRENT == 1)
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 0;
        }
#else
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 3;
        }
#endif
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 1;
        }
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 2;
        }
        else if( NumLeve & 0x01 )
        {
            DispNum = DispNum;
            Decimal = 3;
        }
    }
    else if((DispNum >= 10000) && (DispNum < 100000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 1;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 2;
        }
#if(FUNCTION_CURRENT == 1)
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 0;
        }
#else
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 3;
        }
#endif
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 1;
        }
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 2;
        }
    }
    else if((DispNum >= 100000) && (DispNum < 1000000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 1;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 2;
        }
#if(FUNCTION_CURRENT == 1)
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 0;
        }
#else
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 3;
        }
#endif
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 1;
        }
    }
    else if((DispNum >= 1000000) && (DispNum < 10000000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 1;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 2;
        }
#if(FUNCTION_CURRENT == 1)
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 0;
        }
#else
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 3;
        }
#endif
    }
    else if((DispNum >= 10000000) && (DispNum < 100000000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 1;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 2;
        }
    }
    else if((DispNum >= 100000000) && (DispNum < 1000000000))
    {
        if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 1;
        }
    }
    DispValue(num,DispNum,Decimal, 4, FALSE,0, TRUE, FALSE);
}


/**
  * @brief	��ʾ����ֵ
  * @param	s16 DispNum-Ҫ��ʾ������
			u8 Decimal-С����λ��
			u8 DispWidth-��ʾ���(��λ��)
			BOOL bFlash-�Ƿ���˸
			u8 FlashDec-��˸��λ��
			BOOL bEnableDisp-ǿ����ʾȫ��λ
  * @retval None
  * ���ӷ�����ʾ
  */

void DispValuePower(u8 num,s64 DispNum, u8 Decimal, u8 DispWidth, BOOL bFlash, u8 FlashDec, BOOL bEnableDisp, u16 NumLeve)
{
    if(DispNum < 10000)  // 123.4w
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if( NumLeve & 0x80)
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
        else if(NumLeve & 0x40 )
        {
            DispNum = DispNum * 0.000001;
            Decimal = 1;
        }
        else if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 2;
        }
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 3;
        }
        else if( NumLeve & 0x01 )
        {
            DispNum = (DispNum * 0.1);
            Decimal = 0;
        }

    }
    else if((DispNum >= 10000) && (DispNum < 100000)) // 1.234 KW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if( NumLeve & 0x80)
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
        else if(NumLeve & 0x40 )
        {
            DispNum = DispNum * 0.000001;
            Decimal = 1;
        }
        else if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 2;
        }
        else if(NumLeve & 0x02)
        {
            DispNum = DispNum * 0.1;
            Decimal = 3;
        }
    }
    else if((DispNum >= 100000) && (DispNum < 1000000)) // 12.34 KW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if( NumLeve & 0x80)
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
        else if(NumLeve & 0x40 )
        {
            DispNum = DispNum * 0.000001;
            Decimal = 1;
        }
        else if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
        else if(NumLeve & 0x04)
        {
            DispNum = DispNum * 0.01;
            Decimal = 2;
        }

    }
    else if((DispNum >= 1000000) && (DispNum < 10000000))   // 123.4 KW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if( NumLeve & 0x80)
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
        else if(NumLeve & 0x40 )
        {
            DispNum = DispNum * 0.000001;
            Decimal = 1;
        }
        else if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
        else if(NumLeve & 0x08 )
        {
            DispNum = DispNum * 0.001;
            Decimal = 1;
        }
    }
    else if((DispNum >= 10000000) && (DispNum < 100000000))  //1234 KW = 1.234MW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if( NumLeve & 0x80)
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
        else if(NumLeve & 0x40 )
        {
            DispNum = DispNum * 0.000001;
            Decimal = 1;
        }
        else if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
        else if(NumLeve & 0x10 )
        {
            DispNum = DispNum * 0.0001;
            Decimal = 3;
        }
    }
    else if((DispNum >= 100000000) && (DispNum < 1000000000))  // 12.34 MW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if( NumLeve & 0x80)
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
        else if(NumLeve & 0x40 )
        {
            DispNum = DispNum * 0.000001;
            Decimal = 1;
        }
        else if(NumLeve & 0x20 )
        {
            DispNum = DispNum * 0.00001;
            Decimal = 2;
        }
    }
    else if((DispNum >= 1000000000) && (DispNum < 10000000000))  // 123.4 MW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if( NumLeve & 0x80)
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
        else if(NumLeve & 0x40 )
        {
            DispNum = DispNum * 0.000001;
            Decimal = 1;
        }
    }
    else if((DispNum >= 10000000000) && (DispNum < 100000000000))  // 1234 MW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if( NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
        else if(NumLeve & 0x80 )
        {
            DispNum = DispNum * 0.0000001;
            Decimal = 0;
        }
    }
    else if((DispNum >= 100000000000) && (DispNum < 1000000000000))  // 12.34 KMW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
        else if(NumLeve & 0x0100)
        {
            DispNum = DispNum * 0.00000001;
            Decimal = 2;
        }
    }
    else if((DispNum >= 1000000000000) && (DispNum < 10000000000000))  // 123.4 KMW
    {
        if(NumLeve & 0x0200)
        {
            DispNum = DispNum * 0.000000001;
            Decimal = 1;
        }
    }

    DispValue(num,(s32)DispNum,Decimal, 4, FALSE,0, TRUE, FALSE);
}

/**
  * @brief	��ʾ����
  * @param	s16 DispNum-Ҫ��ʾ������
			u8 Decimal-С����λ��
			u8 DispWidth-��ʾ���(��λ��)
			BOOL bFlash-�Ƿ���˸
			u8 FlashDec-��˸��λ��
			BOOL bEnableDisp-ǿ����ʾȫ��λ
  * @retval None
  */
void DispValue(u8 num,s32 DispNum, u8 Decimal, u8 DispWidth, BOOL bFlash, u8 FlashDec, BOOL bEnableDisp, BOOL bSet)
{
	u8 temp8[4] = {0, 0, 0, 0};
	u8 BitChar[4] = {0, 0, 0, 0};
	u8 i = 0;

    if(DispNum >= 10000)
    {
        DispNum = DispNum * 0.1;
    }

	BitChar[0] = kabs(DispNum)/1000;
	BitChar[1] = (kabs(DispNum)%1000)/100;
	BitChar[2] = (kabs(DispNum)%100)/10;
	BitChar[3] = kabs(DispNum)%10;
	// ����Ҫ��ʾ���ַ�
	for (i = 0 ; i < 4; i++)
	{
    	if (sg_CurrentDispChar[i] != POS_NUM && sg_CurrentDispChar[i] != NEG_NUM)
    	{
    		sg_CurrentDispChar[i] = BitChar[i];
    	}
    	temp8[i] =HT_Data_Index( BitChar[i]);
	}

	if (Decimal == 3)  //С����
	{

		if (DispNum < 0)
		{
		    Disp_Set_FU(0, &temp8[0]);
		}
		temp8[0] |= CHARMODE_DOT;
	}
	else if (Decimal == 2)
	{
		if (DispNum < 0)
		{
		    Disp_Set_FU(0, &temp8[0]);
		}
		else
		{
			if (BitChar[0] == 0)
			{
				temp8[0] = CHARMODE_NC;
			}
		}
		temp8[1] |= CHARMODE_DOT;
	}
	else if (Decimal == 1)
	{

		if (DispNum < 0)
		{
			if (BitChar[0] == 0)
			{
				if (BitChar[1] > 0)
				{
		            Disp_Set_FU(0, &temp8[0]);
				}
				else
				{
		            Disp_Set_FU(1, &temp8[1]);
                    temp8[0] = CHARMODE_NC;
				}
				temp8[2] |= CHARMODE_DOT;
			}
			else
			{
                temp8[3] = temp8[2];
			    temp8[2] = temp8[1];
			    temp8[1] = temp8[0];
				temp8[0] = CHARMODE_FU;
				//temp8[2] |= CHARMODE_DOT;
			}
		}
		else
		{
			if (BitChar[0] == 0)
			{
				temp8[0] = CHARMODE_NC;
				if (BitChar[1] == 0)
				{
					temp8[1] = CHARMODE_NC;
				}
			}
			temp8[2] |= CHARMODE_DOT;
		}

	}
	else if (Decimal == 0)
	{
        if (DispNum < 0 && DispNum > -10)
 		{
		    Disp_Set_FU(2, &temp8[2]);
 		}
 		else if (DispNum <= -10 && DispNum > -100)
 		{
		    Disp_Set_FU(1, &temp8[1]);
 		}
 		else if (DispNum <= -100 && DispNum > -1000)
 		{
		    Disp_Set_FU(0, &temp8[0]);
 		}
	}
	else
	{
		return;
	}
	switch (DispWidth)
	{
    	case 1:
    		temp8[0] = CHARMODE_NC;
    		temp8[1] = CHARMODE_NC;
    		temp8[2] = CHARMODE_NC;
    	    break;
    	case 2:
    		temp8[0] = CHARMODE_NC;
    		temp8[1] = CHARMODE_NC;
    	    break;
    	case 3:
    		temp8[0] = CHARMODE_NC;
    	    break;
	}

	if (bEnableDisp)
	{
		if (temp8[0] == CHARMODE_NC)
		{
			temp8[0] = CHARMODE_0;
		}
		if (temp8[1] == CHARMODE_NC)
		{
			temp8[1] = CHARMODE_0;
		}
		if (temp8[2] == CHARMODE_NC)
		{
			temp8[2] = CHARMODE_0;
		}
		if (temp8[3] == CHARMODE_NC)
		{
			temp8[3] = CHARMODE_0;
		}
	}

	if (bSet) // ��������״̬0
	{
		for (i = 0; i < 4; i++)
		{
			if (sg_CurrentDispChar[i] == POS_NUM)
			{
				temp8[i] = CHARMODE_ZHENG;
			}
			else if (sg_CurrentDispChar[i] == NEG_NUM)
			{
				temp8[i] = CHARMODE_FU;
			}
		}
	}
	if (bFlash)
	{
		for (i = 0; i < 4; i++)
		{
    		if (Get_Bit(FlashDec, i) == 1)
    		{
    			temp8[i] = CHARMODE_NC;
    		}
		}
	}
	DispChar(num,temp8[0], temp8[1], temp8[2], temp8[3]);

}

/**
  * @brief	��ʾ�ַ�
  * @param	u8 ch1-��1λ�ַ� ��emInderMode
			u8 ch2-��2λ�ַ� ��emInderMode
			u8 ch3-��3λ�ַ� ��emInderMode
			u8 ch4-��4λ�ַ� ��emInderMode
  * @retval None
  */

void DispChar(u8 num,u8 ch1, u8 ch2, u8 ch3, u8 ch4)    //����ʾ����
{
	switch(num)
	{
		case 0:
            vg_Display_Value[0] = ch1;
            vg_Display_Value[1] = ch2;
            vg_Display_Value[2] = ch3;
            vg_Display_Value[3] = ch4;
		    break;
		case 1:
            vg_Display_Value[4] = ch1;
            vg_Display_Value[5] = ch2;
            vg_Display_Value[6] = ch3;
            vg_Display_Value[7] = ch4;
		    break;
		case 2:
            vg_Display_Value[8] = ch1;
            vg_Display_Value[9] = ch2;
            vg_Display_Value[10] = ch3;
            vg_Display_Value[11] = ch4;
            break;
        case 3:
            vg_Display_Value[15] = ch2;    //��λ
            break;
        case 4:
            vg_Display_Value[14] = ch2;    //��λ
            break;
        case 5:
            vg_Display_Value[13] = ch2;    //��λ
            break;
		default:
		    break;
	}
}

void DispHarmonicContent(u8 Select_VA,u8 Index)
{
    u32 DispValTmp[3];
    if(Select_VA == TRUE)
    {
        if(g_tParam.CtrlParam.NetMode == N34)
        {
            DispValTmp[0] = (u32)(HarmonicData.HarmonicpercentU[0][Index-1]/100);
            DispValTmp[1] = (u32)(HarmonicData.HarmonicpercentU[1][Index-1]/100);
            DispValTmp[2] = (u32)(HarmonicData.HarmonicpercentU[2][Index-1]/100);
            DispValue(0,DispValTmp[0], 2, 4, FALSE,0, TRUE, FALSE);
            DispValue(1,DispValTmp[1], 2, 4, FALSE,0, TRUE, FALSE);
            DispValue(2,DispValTmp[2], 2, 4, FALSE,0, TRUE, FALSE);
        }
        else
        {
            DispValTmp[0] = (u32)(HarmonicData.HarmonicpercentU[0][Index-1]/100);
            DispValTmp[2] = (u32)(HarmonicData.HarmonicpercentU[2][Index-1]/100);
            DispValue(0,DispValTmp[0], 2, 4, FALSE,0, TRUE, FALSE);
            DispValue(1,DispValTmp[2], 2, 4, FALSE,0, TRUE, FALSE);
            DispChar(2,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU);
        }

    }
    else
    {
        DispValTmp[0] = (u32)(HarmonicData.HarmonicpercentI[0][Index-1]/100);
        DispValTmp[1] = (u32)(HarmonicData.HarmonicpercentI[1][Index-1]/100);
        DispValTmp[2] = (u32)(HarmonicData.HarmonicpercentI[2][Index-1]/100);
        DispValue(0,DispValTmp[0], 2, 4, FALSE,0, TRUE, FALSE);
        DispValue(1,DispValTmp[1], 2, 4, FALSE,0, TRUE, FALSE);
        DispValue(2,DispValTmp[2], 2, 4, FALSE,0, TRUE, FALSE);
    }
}



/**
  * @brief	��ʾ�ַ�
  * @param	u8 Index-��1-4λ  ��DIG1 DIG2 DIG3 DIG4
			u8 ch-�ַ�  ��emInderMode
  * @retval None
  */
void DispBitChar(u8 Index, u8 ch)
{
    if (Index < 4) // ��4λ
    {
        vg_Display_Value[Index] = ch;
    }
}

/**
  * @brief	��ʾ����
  * @param	s16 DispNum-Ҫ��ʾ������
			u8 Decimal-С����λ��
			u8 DispWidth-��ʾ���(��λ��)
			BOOL bFlash-�Ƿ���˸
			u8 FlashDec-��˸��λ��
			BOOL bEnableDisp-ǿ����ʾȫ��λ
  * @retval None
  */
void DispMenu_Main(void)
{
    u8 UintFlag;
    s16 TmpPf;
    u8 tmpInCharmode[4];
    u8 tmpOutCharmode[4];
    u32 DispValTmp[3];
    s64 DispValTmpPQS[4];
    Leve_1_DispNUM = 0x00;
    if(g_OverCurr[PH_A] || g_OverCurr[PH_B] || g_OverCurr[PH_C])
    {
        sg_DispMainMenuIndex = MENU_INDEX_I;
        g_bUpdataDefault = FALSE;
        g_bAlarmEnble = FALSE;
    }
    switch (sg_DispMainMenuIndex)
    {
        case MENU_INDEX_U: // ��λV 1λС���� �����ѹ
		    for(u8 i = 0; i<3; i++)
    		    {
    		        DispValTmp[i] = vg_Power_Val.Real2_Val[i].U;
    		        if(vg_Power_Val.Real2_Val[i].U < 100000)     //123.4
                    {
                        Leve_1_DispNUM |= 0x01;
                    }                                           //6                                   //7
                    if((vg_Power_Val.Real2_Val[i].U >= 100000) && (vg_Power_Val.Real2_Val[i].U < 1000000)) //1.234 K
                    {
                        Leve_1_DispNUM |= 0x02;
                    }                                           //7                                    //8
                    else if((vg_Power_Val.Real2_Val[i].U >= 1000000) && (vg_Power_Val.Real2_Val[i].U < 10000000))//12.34 K
                    {
                        Leve_1_DispNUM |= 0x04;
                    }                                           //8                                    //9
                    else if((vg_Power_Val.Real2_Val[i].U >= 10000000) && (vg_Power_Val.Real2_Val[i].U < 100000000))//123.4 K
                    {
                        Leve_1_DispNUM |= 0x08;
                    }                                           //9                                    //10
                    else if((vg_Power_Val.Real2_Val[i].U >= 100000000) && (vg_Power_Val.Real2_Val[i].U < 1000000000))//1.234 M
                    {
                        Leve_1_DispNUM |= 0x10;
                    }
    		    }
    		    for(u8 j = 0; j<3; j++)
    		    {
                    DispValueVoltage(j,DispValTmp[j]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
    		    }
                if(Leve_1_DispNUM == 0x01)
                {
                    DispChar(3,CHARMODE_ALL,CHARMODE_Dv,CHARMODE_NC,CHARMODE_NC);
                }
    		    if((Leve_1_DispNUM > 0x01) && Leve_1_DispNUM < 0x10)
    		    {
                    UintFlag = 0;
                    UintFlag |= CHARMODE_Dv + CHARMODE_DK;
    		        DispChar(3,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
    		    }
                else if(Leve_1_DispNUM & 0x10)
    		    {
                    UintFlag = 0;
                    UintFlag |= CHARMODE_Dv + CHARMODE_DM;
    		        DispChar(3,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
    		    }
    			break;
        case MENU_INDEX_Uavr:// ��λV 1λС���� ƽ�����ѹ
		        DispValTmp[0] = vg_Power_Val.Uavr;
		        if(DispValTmp[0] < 100000)     //123.4
                {
                    Leve_1_DispNUM |= 0x01;
                }                                           //6                                   //7
                if((DispValTmp[0] >= 100000) && (DispValTmp[0] < 1000000)) //1.234 K
                {
                    Leve_1_DispNUM |= 0x02;
                }                                           //7                                    //8
                else if((DispValTmp[0] >= 1000000) && (DispValTmp[0] < 10000000))//12.34 K
                {
                    Leve_1_DispNUM |= 0x04;
                }                                           //8                                    //9
                else if((DispValTmp[0] >= 10000000) && (DispValTmp[0] < 100000000))//123.4 K
                {
                    Leve_1_DispNUM |= 0x08;
                }                                           //9                                    //10
                else if((DispValTmp[0] >= 100000000) && (DispValTmp[0] < 1000000000))//1.234 M
                {
                    Leve_1_DispNUM |= 0x10;
                }
                DispChar(0,CHARMODE_U,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                DispValueVoltage(1,DispValTmp[0]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
                if(Leve_1_DispNUM == 0x01)
                {
                    DispChar(3,CHARMODE_ALL,CHARMODE_Dv + CHARMODE_Davr,CHARMODE_NC,CHARMODE_NC);
                }
    		    if((Leve_1_DispNUM > 0x01) && Leve_1_DispNUM < 0x10)
    		    {
                    UintFlag = 0;
                    UintFlag |= CHARMODE_Dv + CHARMODE_DK + CHARMODE_Davr;
    		        DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
    		    }
                else if(Leve_1_DispNUM & 0x10)
    		    {
                    UintFlag = 0;
                    UintFlag |= CHARMODE_Dv + CHARMODE_DM + CHARMODE_Davr;
    		        DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
    		    }
    			break;
	    case MENU_INDEX_LU:// ��λV 1λС����
	        for(u8 i = 0; i<3; i++)
    		    {
    		        DispValTmp[i] = vg_Power_Val.Real2_Val[i].LineU;
    		        if(vg_Power_Val.Real2_Val[i].LineU < 100000)     //123.4
                    {
                        Leve_1_DispNUM |= 0x01;
                    }                                           //6                                   //7
                    if((vg_Power_Val.Real2_Val[i].LineU >= 100000) && (vg_Power_Val.Real2_Val[i].LineU < 1000000)) //1.234 K
                    {
                        Leve_1_DispNUM |= 0x02;
                    }                                           //7                                    //8
                    else if((vg_Power_Val.Real2_Val[i].LineU >= 1000000) && (vg_Power_Val.Real2_Val[i].LineU < 10000000))//12.34 K
                    {
                        Leve_1_DispNUM |= 0x04;
                    }                                           //8                                    //9
                    else if((vg_Power_Val.Real2_Val[i].LineU >= 10000000) && (vg_Power_Val.Real2_Val[i].LineU < 100000000))//123.4 K
                    {
                        Leve_1_DispNUM |= 0x08;
                    }                                           //9                                    //10
                    else if((vg_Power_Val.Real2_Val[i].LineU >= 100000000) && (vg_Power_Val.Real2_Val[i].LineU < 1000000000))//1.234 M
                    {
                        Leve_1_DispNUM |= 0x10;
                    }
    		    }
    		    for(u8 j = 0; j<3; j++)
    		    {
                    DispValueVoltage(j,DispValTmp[j]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
    		    }
                if(Leve_1_DispNUM == 0x01)
                {
                    if(!sg_bSetFlashEnable)
                    {
                        DispChar(3,CHARMODE_NC,CHARMODE_Dv,CHARMODE_NC,CHARMODE_NC);
                    }
                    else
                    {
                        DispChar(3,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                    }
                }
    		    if((Leve_1_DispNUM > 0x01) && Leve_1_DispNUM < 0x10)
    		    {
                    UintFlag = 0;
    		        if(!sg_bSetFlashEnable)
                    {
                        UintFlag |=CHARMODE_Dv + CHARMODE_DK;
    		            DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
                    else
                    {
                        UintFlag |= CHARMODE_DK;
    		            DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
    		    }
                else if(Leve_1_DispNUM & 0x10)
    		    {
                    UintFlag = 0;
    		        if(!sg_bSetFlashEnable)
                    {
                        UintFlag |=CHARMODE_Dv + CHARMODE_DM;
    		            DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
                    else
                    {
                        UintFlag |= CHARMODE_DM;
    		            DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
    		    }
    			break;
        case MENU_INDEX_LUavr:// ��λV 1λС���� ƽ�����ѹ
		        DispValTmp[0] = vg_Power_Val.ULavr;
		        if(DispValTmp[0] < 100000)     //123.4
                {
                    Leve_1_DispNUM |= 0x01;
                }                                           //6                                   //7
                if((DispValTmp[0] >= 100000) && (DispValTmp[0] < 1000000)) //1.234 K
                {
                    Leve_1_DispNUM |= 0x02;
                }                                           //7                                    //8
                else if((DispValTmp[0] >= 1000000) && (DispValTmp[0] < 10000000))//12.34 K
                {
                    Leve_1_DispNUM |= 0x04;
                }                                           //8                                    //9
                else if((DispValTmp[0] >= 10000000) && (DispValTmp[0] < 100000000))//123.4 K
                {
                    Leve_1_DispNUM |= 0x08;
                }                                           //9                                    //10
                else if((DispValTmp[0] >= 100000000) && (DispValTmp[0] < 1000000000))//1.234 M
                {
                    Leve_1_DispNUM |= 0x10;
                }
                DispChar(0,CHARMODE_L,CHARMODE_U,CHARMODE_NC,CHARMODE_NC);
                DispValueVoltage(1,DispValTmp[0]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
                if(Leve_1_DispNUM == 0x01)
                {
                    if(!sg_bSetFlashEnable)
                    {
                        DispChar(3,CHARMODE_NC,CHARMODE_Dv + CHARMODE_Davr,CHARMODE_NC,CHARMODE_NC);
                    }
                    else
                    {
                        DispChar(3,CHARMODE_NC,CHARMODE_NC + CHARMODE_Davr,CHARMODE_NC,CHARMODE_NC);
                    }
                }
    		    if((Leve_1_DispNUM > 0x01) && Leve_1_DispNUM < 0x10)
    		    {
                    UintFlag = 0;
    		        if(!sg_bSetFlashEnable)
                    {
                        UintFlag |=CHARMODE_Dv + CHARMODE_DK  + CHARMODE_Davr;
    		        DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
                    else
                    {
                        UintFlag |= CHARMODE_DK + CHARMODE_Davr;
    		        DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
    		    }
                else if(Leve_1_DispNUM & 0x10)
    		    {
                    UintFlag = 0;
    		        if(!sg_bSetFlashEnable)
                    {
                        UintFlag |=CHARMODE_Dv + CHARMODE_DM + CHARMODE_Davr;
    		            DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
                    else
                    {
                        UintFlag |= CHARMODE_DM + CHARMODE_Davr;
    		            DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
                    }
    		    }
    			break;
		case MENU_INDEX_I://��λA 3λС����
            for(u8 i = 0; i<3; i++)
            {
                DispValTmp[i] = vg_Power_Val.Real2_Val[i].I;
                if(vg_Power_Val.Real2_Val[i].I < 100000)     //1.234
                {
                    Leve_1_DispNUM |= 0x01;
                }                                           //6                                   //7
                if((vg_Power_Val.Real2_Val[i].I >= 100000) && (vg_Power_Val.Real2_Val[i].I < 1000000)) //12.34
                {
                    Leve_1_DispNUM |= 0x02;
                }                                           //7                                    //8
                else if((vg_Power_Val.Real2_Val[i].I >= 1000000) && (vg_Power_Val.Real2_Val[i].I < 10000000))//123.4
                {
                    Leve_1_DispNUM |= 0x04;
                }                                           //8                                    //9
                else if((vg_Power_Val.Real2_Val[i].I >= 10000000) && (vg_Power_Val.Real2_Val[i].I < 100000000))//1.234 K
                {
                    Leve_1_DispNUM |= 0x08;
                }                                           //9                                    //10
                else if((vg_Power_Val.Real2_Val[i].I >= 100000000) && (vg_Power_Val.Real2_Val[i].I < 1000000000))//12.34 K
                {
                    Leve_1_DispNUM |= 0x10;
                }
            }
            for(u8 j = 0; j<3; j++)
            {
                DispValueCurrent(j,DispValTmp[j]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
            }
            if(g_OverCurr[PH_A] && (g_tParam.CtrlParam.Alarm !=0))
		    {
                if(sg_bSetFlashEnable)
                {
                    DispChar(PH_A,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                }
		    }
		    if(g_OverCurr[PH_B] && (g_tParam.CtrlParam.Alarm !=0))
		    {
                if(sg_bSetFlashEnable)
                {
                    DispChar(PH_B,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                }
		    }
		    if(g_OverCurr[PH_C] && (g_tParam.CtrlParam.Alarm !=0))
		    {
                if(sg_bSetFlashEnable)
                {
                    DispChar(PH_C,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                }
		    }
            if( Leve_1_DispNUM & 0x20 || Leve_1_DispNUM & 0x10 || Leve_1_DispNUM & 0x08)
            {
                DispChar(3,CHARMODE_NC,CHARMODE_DK,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_NC,CHARMODE_Di,CHARMODE_NC,CHARMODE_NC);
            }
            else
            {
                DispChar(4,CHARMODE_NC,CHARMODE_Di,CHARMODE_NC,CHARMODE_NC);
            }
            break;
        case MENU_INDEX_Iavr://��λA 3λС����
            DispValTmp[0] = vg_Power_Val.Iavr;
            if(DispValTmp[0] < 100000)     //1.234
            {
                Leve_1_DispNUM |= 0x01;
            }                                           //6                                   //7
            if((DispValTmp[0] >= 100000) && (DispValTmp[0] < 1000000)) //12.34
            {
                Leve_1_DispNUM |= 0x02;
            }                                           //7                                    //8
            else if((DispValTmp[0] >= 1000000) && (DispValTmp[0] < 10000000))//123.4
            {
                Leve_1_DispNUM |= 0x04;
            }                                           //8                                    //9
            else if((DispValTmp[0] >= 10000000) && (DispValTmp[0] < 100000000))//1.234 K
            {
                Leve_1_DispNUM |= 0x08;
            }                                           //9                                    //10
            else if((DispValTmp[0] >= 100000000) && (DispValTmp[0] < 1000000000))//12.34 K
            {
                Leve_1_DispNUM |= 0x10;
            }
            DispChar(0,CHARMODE_I,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
            DispValueCurrent(1,DispValTmp[0]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
            if( Leve_1_DispNUM & 0x20 || Leve_1_DispNUM & 0x10 || Leve_1_DispNUM & 0x08)
            {
                DispChar(3,CHARMODE_NC,CHARMODE_DK + CHARMODE_Davr,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_NC,CHARMODE_Di,CHARMODE_NC,CHARMODE_NC);
            }
            else
            {
                DispChar(3,CHARMODE_NC,CHARMODE_Davr,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_NC,CHARMODE_Di,CHARMODE_NC,CHARMODE_NC);
            }
            break;
       	case MENU_INDEX_P://�й�
            UintFlag = 0x00;
            for(u8 i = 0; i<3; i++)
            {
                if(g_tParam.CtrlParam.NetMode == N34)
		        {
                    DispValTmpPQS[i] = kabs(vg_Power_Val.Real2_Val[i].P);
                }
                else
                {
                    if(i == 0)
                    {
                        DispValTmpPQS[i] = kabs(vg_Power_Val.Pt);
                    }
                    else if(i == 1)
                    {
                        DispValTmpPQS[i] = kabs(vg_Power_Val.Qt);
                    }
                    else if(i == 2)
                    {
                        DispValTmpPQS[i] = vg_Power_Val.St;
                    }
                }

                if(DispValTmpPQS[i] < 100000)
                {
                    Leve_1_DispNUM |= 0x01;
                }                                                                               //7
                if((DispValTmpPQS[i] >= 100000) && (DispValTmpPQS[i]< 1000000))  //
                {
                    Leve_1_DispNUM |= 0x02;
                }                                           //7                                        //8
                else if((DispValTmpPQS[i] >= 1000000) && (DispValTmpPQS[i] < 10000000)) //
                {
                    Leve_1_DispNUM |= 0x04;
                }                                           //8                                        //9
                else if((DispValTmpPQS[i] >= 10000000) && (DispValTmpPQS[i] < 100000000))  //
                {
                    Leve_1_DispNUM |= 0x08;
                }                                           //9                                        //10
                else if((DispValTmpPQS[i] >= 100000000) && (DispValTmpPQS[i] < 1000000000)) //
                {
                    Leve_1_DispNUM |= 0x10;
                }                                           //10                                       //11
                else if((DispValTmpPQS[i] >= 1000000000) && (DispValTmpPQS[i] < 10000000000)) //
                {
                    Leve_1_DispNUM |= 0x20;
                }                                           //11                                       //12
                else if((DispValTmpPQS[i] >= 10000000000) && (DispValTmpPQS[i] < 100000000000)) //
                {
                    Leve_1_DispNUM |= 0x40;
                }                                           //12                                       //13
                else if((DispValTmpPQS[i] >= 100000000000) && (DispValTmpPQS[i] < 1000000000000)) //
                {
                    Leve_1_DispNUM |= 0x80;
                }                                          //13                                       //14
                else if((DispValTmpPQS[i] >= 1000000000000) && (DispValTmpPQS[i] < 10000000000000)) //
                {
                    Leve_1_DispNUM |= 0x0100;
                }                                          //14                                      //15
                else if((DispValTmpPQS[i] >= 10000000000000) && (DispValTmpPQS[i] < 100000000000000)) //
                {
                    Leve_1_DispNUM |= 0x0200;
                }

            }
            for(u8 j = 0; j<3; j++)
            {
                DispValuePower(j,DispValTmpPQS[j]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
            }

            if( Leve_1_DispNUM == 0x01)
            {
                UintFlag = 0x00;
                UintFlag |= CHARMODE_Dw;
                DispChar(3,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM < 0x10 )
            {
                UintFlag = 0x00;
                UintFlag |= CHARMODE_Dw + CHARMODE_DK;
                DispChar(3,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM <0x0100)
            {
                UintFlag = 0x00;
                UintFlag |= CHARMODE_Dw + CHARMODE_DM;
                DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM & 0x0100 || Leve_1_DispNUM & 0x0200)
            {
                UintFlag = 0x00;
                UintFlag |= CHARMODE_Dw + CHARMODE_DM + CHARMODE_DK;
                DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
            }
            if(g_tParam.CtrlParam.NetMode == N33)
            {
                DispChar(3,CHARMODE_NC,UintFlag + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_NC,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_NC,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            break;
        case MENU_INDEX_Pe://�й�
            UintFlag = 0x00;
            DispValTmpPQS[0] = kabs(vg_Power_Val.Pt);

            if(DispValTmpPQS[0] < 100000)
            {
                Leve_1_DispNUM |= 0x01;
            }                                                                               //7
            if((DispValTmpPQS[0] >= 100000) && (DispValTmpPQS[0]< 1000000))  //
            {
                Leve_1_DispNUM |= 0x02;
            }                                           //7                                        //8
            else if((DispValTmpPQS[0] >= 1000000) && (DispValTmpPQS[0] < 10000000)) //
            {
                Leve_1_DispNUM |= 0x04;
            }                                           //8                                        //9
            else if((DispValTmpPQS[0] >= 10000000) && (DispValTmpPQS[0] < 100000000))  //
            {
                Leve_1_DispNUM |= 0x08;
            }                                           //9                                        //10
            else if((DispValTmpPQS[0] >= 100000000) && (DispValTmpPQS[0] < 1000000000)) //
            {
                Leve_1_DispNUM |= 0x10;
            }                                           //10                                       //11
            else if((DispValTmpPQS[0] >= 1000000000) && (DispValTmpPQS[0] < 10000000000)) //
            {
                Leve_1_DispNUM |= 0x20;
            }                                           //11                                       //12
            else if((DispValTmpPQS[0] >= 10000000000) && (DispValTmpPQS[0] < 100000000000)) //
            {
                Leve_1_DispNUM |= 0x40;
            }                                           //12                                       //13
            else if((DispValTmpPQS[0] >= 100000000000) && (DispValTmpPQS[0] < 1000000000000)) //
            {
                Leve_1_DispNUM |= 0x80;
            }                                          //13                                       //14
            else if((DispValTmpPQS[0] >= 1000000000000) && (DispValTmpPQS[0] < 10000000000000)) //
            {
                Leve_1_DispNUM |= 0x0100;
            }                                          //14                                      //15
            else if((DispValTmpPQS[0] >= 10000000000000) && (DispValTmpPQS[0] < 100000000000000)) //
            {
                Leve_1_DispNUM |= 0x0200;
            }
            DispChar(0,CHARMODE_P,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
            DispValuePower(1,DispValTmpPQS[0]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);

            if( Leve_1_DispNUM == 0x01)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_Dw + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM < 0x10 )
            {
                UintFlag |= CHARMODE_Dw + CHARMODE_DK + CHARMODE_De;
                DispChar(3,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM <0x0100)
            {
                UintFlag = 0x00;
                UintFlag |= CHARMODE_Dw + CHARMODE_DM + CHARMODE_De;
                DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM & 0x0100 || Leve_1_DispNUM & 0x0200)
            {
                UintFlag = 0x00;
                UintFlag |= CHARMODE_Dw + CHARMODE_DM + CHARMODE_DK + CHARMODE_De;
                DispChar(3,CHARMODE_NC,UintFlag,CHARMODE_NC,CHARMODE_NC);
            }
            break;
        case MENU_INDEX_Q:// �޹�
            for(u8 i = 0; i<3; i++)
            {
                DispValTmpPQS[i] = kabs(vg_Power_Val.Real2_Val[i].Q);
                if(DispValTmpPQS[i] < 100000)
                {
                    Leve_1_DispNUM |= 0x01;
                }                                                                               //7
                if((DispValTmpPQS[i] >= 100000) && (DispValTmpPQS[i]< 1000000))  //
                {
                    Leve_1_DispNUM |= 0x02;
                }                                           //7                                        //8
                else if((DispValTmpPQS[i] >= 1000000) && (DispValTmpPQS[i] < 10000000)) //
                {
                    Leve_1_DispNUM |= 0x04;
                }                                           //8                                        //9
                else if((DispValTmpPQS[i] >= 10000000) && (DispValTmpPQS[i] < 100000000))  //
                {
                    Leve_1_DispNUM |= 0x08;
                }                                           //9                                        //10
                else if((DispValTmpPQS[i] >= 100000000) && (DispValTmpPQS[i] < 1000000000)) //
                {
                    Leve_1_DispNUM |= 0x10;
                }                                           //10                                       //11
                else if((DispValTmpPQS[i] >= 1000000000) && (DispValTmpPQS[i] < 10000000000)) //
                {
                    Leve_1_DispNUM |= 0x20;
                }                                           //11                                       //12
                else if((DispValTmpPQS[i] >= 10000000000) && (DispValTmpPQS[i] < 100000000000)) //
                {
                    Leve_1_DispNUM |= 0x40;
                }                                           //12                                       //13
                else if((DispValTmpPQS[i] >= 100000000000) && (DispValTmpPQS[i] < 1000000000000)) //
                {
                    Leve_1_DispNUM |= 0x80;
                }                                          //13                                       //14
                else if((DispValTmpPQS[i] >= 1000000000000) && (DispValTmpPQS[i] < 10000000000000)) //
                {
                    Leve_1_DispNUM |= 0x0100;
                }                                          //14                                      //15
                else if((DispValTmpPQS[i] >= 10000000000000) && (DispValTmpPQS[i] < 100000000000000)) //
                {
                    Leve_1_DispNUM |= 0x0200;
                }

            }
            for(u8 j = 0; j<3; j++)
            {
                DispValuePower(j,DispValTmpPQS[j]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
            }

            if( Leve_1_DispNUM == 0x01)
            {
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM < 0x10 )
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DK,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM <0x0100)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM & 0x0100 || Leve_1_DispNUM & 0x0200)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM + CHARMODE_DK,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            break;
        case MENU_INDEX_Qe://�й�
            UintFlag = 0x00;
            DispValTmpPQS[0] = kabs(vg_Power_Val.Qt);

            if(DispValTmpPQS[0] < 100000)
            {
                Leve_1_DispNUM |= 0x01;
            }                                                                               //7
            if((DispValTmpPQS[0] >= 100000) && (DispValTmpPQS[0]< 1000000))  //
            {
                Leve_1_DispNUM |= 0x02;
            }                                           //7                                        //8
            else if((DispValTmpPQS[0] >= 1000000) && (DispValTmpPQS[0] < 10000000)) //
            {
                Leve_1_DispNUM |= 0x04;
            }                                           //8                                        //9
            else if((DispValTmpPQS[0] >= 10000000) && (DispValTmpPQS[0] < 100000000))  //
            {
                Leve_1_DispNUM |= 0x08;
            }                                           //9                                        //10
            else if((DispValTmpPQS[0] >= 100000000) && (DispValTmpPQS[0] < 1000000000)) //
            {
                Leve_1_DispNUM |= 0x10;
            }                                           //10                                       //11
            else if((DispValTmpPQS[0] >= 1000000000) && (DispValTmpPQS[0] < 10000000000)) //
            {
                Leve_1_DispNUM |= 0x20;
            }                                           //11                                       //12
            else if((DispValTmpPQS[0] >= 10000000000) && (DispValTmpPQS[0] < 100000000000)) //
            {
                Leve_1_DispNUM |= 0x40;
            }                                           //12                                       //13
            else if((DispValTmpPQS[0] >= 100000000000) && (DispValTmpPQS[0] < 1000000000000)) //
            {
                Leve_1_DispNUM |= 0x80;
            }                                          //13                                       //14
            else if((DispValTmpPQS[0] >= 1000000000000) && (DispValTmpPQS[0] < 10000000000000)) //
            {
                Leve_1_DispNUM |= 0x0100;
            }                                          //14                                      //15
            else if((DispValTmpPQS[0] >= 10000000000000) && (DispValTmpPQS[0] < 100000000000000)) //
            {
                Leve_1_DispNUM |= 0x0200;
            }
            DispChar(0,CHARMODE_Q,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
            DispValuePower(1,DispValTmpPQS[0]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);

            if( Leve_1_DispNUM == 0x01)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM < 0x10 )
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DK + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM <0x0100)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM & 0x0100 || Leve_1_DispNUM & 0x0200)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM + CHARMODE_DK + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(4,CHARMODE_ALL,CHARMODE_Dvar,CHARMODE_NC,CHARMODE_NC);
            }
            break;
        case MENU_INDEX_S://�й�
            for(u8 i = 0; i<3; i++)
            {
                DispValTmpPQS[i] = vg_Power_Val.Real2_Val[i].S;
                if(DispValTmpPQS[i] < 100000)
                {
                    Leve_1_DispNUM |= 0x01;
                }                                                                               //7
                if((DispValTmpPQS[i] >= 100000) && (DispValTmpPQS[i]< 1000000))  //
                {
                    Leve_1_DispNUM |= 0x02;
                }                                           //7                                        //8
                else if((DispValTmpPQS[i] >= 1000000) && (DispValTmpPQS[i] < 10000000)) //
                {
                    Leve_1_DispNUM |= 0x04;
                }                                           //8                                        //9
                else if((DispValTmpPQS[i] >= 10000000) && (DispValTmpPQS[i] < 100000000))  //
                {
                    Leve_1_DispNUM |= 0x08;
                }                                           //9                                        //10
                else if((DispValTmpPQS[i] >= 100000000) && (DispValTmpPQS[i] < 1000000000)) //
                {
                    Leve_1_DispNUM |= 0x10;
                }                                           //10                                       //11
                else if((DispValTmpPQS[i] >= 1000000000) && (DispValTmpPQS[i] < 10000000000)) //
                {
                    Leve_1_DispNUM |= 0x20;
                }                                           //11                                       //12
                else if((DispValTmpPQS[i] >= 10000000000) && (DispValTmpPQS[i] < 100000000000)) //
                {
                    Leve_1_DispNUM |= 0x40;
                }                                           //12                                       //13
                else if((DispValTmpPQS[i] >= 100000000000) && (DispValTmpPQS[i] < 1000000000000)) //
                {
                    Leve_1_DispNUM |= 0x80;
                }                                          //13                                       //14
                else if((DispValTmpPQS[i] >= 1000000000000) && (DispValTmpPQS[i] < 10000000000000)) //
                {
                    Leve_1_DispNUM |= 0x0100;
                }                                          //14                                      //15
                else if((DispValTmpPQS[i] >= 10000000000000) && (DispValTmpPQS[i] < 100000000000000)) //
                {
                    Leve_1_DispNUM |= 0x0200;
                }

            }
            for(u8 j = 0; j<3; j++)
            {
                DispValuePower(j,DispValTmpPQS[j]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);
            }

            if( Leve_1_DispNUM == 0x01)
            {
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM < 0x10 )
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DK,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM <0x0100)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM & 0x0100 || Leve_1_DispNUM & 0x0200)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM + CHARMODE_DK,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            break;
        case MENU_INDEX_Se://�й�
            UintFlag = 0x00;
            DispValTmpPQS[0] = vg_Power_Val.St;

            if(DispValTmpPQS[0] < 100000)
            {
                Leve_1_DispNUM |= 0x01;
            }                                                                               //7
            if((DispValTmpPQS[0] >= 100000) && (DispValTmpPQS[0]< 1000000))  //
            {
                Leve_1_DispNUM |= 0x02;
            }                                           //7                                        //8
            else if((DispValTmpPQS[0] >= 1000000) && (DispValTmpPQS[0] < 10000000)) //
            {
                Leve_1_DispNUM |= 0x04;
            }                                           //8                                        //9
            else if((DispValTmpPQS[0] >= 10000000) && (DispValTmpPQS[0] < 100000000))  //
            {
                Leve_1_DispNUM |= 0x08;
            }                                           //9                                        //10
            else if((DispValTmpPQS[0] >= 100000000) && (DispValTmpPQS[0] < 1000000000)) //
            {
                Leve_1_DispNUM |= 0x10;
            }                                           //10                                       //11
            else if((DispValTmpPQS[0] >= 1000000000) && (DispValTmpPQS[0] < 10000000000)) //
            {
                Leve_1_DispNUM |= 0x20;
            }                                           //11                                       //12
            else if((DispValTmpPQS[0] >= 10000000000) && (DispValTmpPQS[0] < 100000000000)) //
            {
                Leve_1_DispNUM |= 0x40;
            }                                           //12                                       //13
            else if((DispValTmpPQS[0] >= 100000000000) && (DispValTmpPQS[0] < 1000000000000)) //
            {
                Leve_1_DispNUM |= 0x80;
            }                                          //13                                       //14
            else if((DispValTmpPQS[0] >= 1000000000000) && (DispValTmpPQS[0] < 10000000000000)) //
            {
                Leve_1_DispNUM |= 0x0100;
            }                                          //14                                      //15
            else if((DispValTmpPQS[0] >= 10000000000000) && (DispValTmpPQS[0] < 100000000000000)) //
            {
                Leve_1_DispNUM |= 0x0200;
            }
            DispChar(0,CHARMODE_S,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
            DispValuePower(1,DispValTmpPQS[0]*0.1, 0, 4, FALSE,0, TRUE, Leve_1_DispNUM);

            if( Leve_1_DispNUM == 0x01)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM < 0x10 )
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DK + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM <0x0100)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            else if( Leve_1_DispNUM & 0x0100 || Leve_1_DispNUM & 0x0200)
            {
                DispChar(3,CHARMODE_ALL,CHARMODE_DM + CHARMODE_DK + CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
                DispChar(5,CHARMODE_ALL,CHARMODE_Dva,CHARMODE_NC,CHARMODE_NC);
            }
            break;
		case MENU_INDEX_PF:
		    if(g_tParam.CtrlParam.NetMode == N34)
		    {
                for(u8 i = 0; i<3; i++)
                {
                    DispValTmpPQS[i] = kabs(vg_Power_Val.Real2_Val[i].PF);
                    DispValue(i,DispValTmpPQS[i],3,4,FALSE,0,FALSE,FALSE);
                }

		    }
		    else
		    {
                DispValTmpPQS[0] = kabs(vg_Power_Val.PFTA);
                DispChar(0,CHARMODE_P,CHARMODE_F,CHARMODE_NC,CHARMODE_NC);

                if(DispValTmpPQS[0] != 0)
                {
                    DispValue(1,DispValTmpPQS[0],3,4,FALSE,0,FALSE,FALSE);
                }
                else
                {
                    DispChar(1,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU);
                }
		    }
		    DispChar(4,CHARMODE_NC,CHARMODE_Dpf,CHARMODE_NC,CHARMODE_NC);
            break;
        case MENU_INDEX_PFe:
            DispChar(0,CHARMODE_P,CHARMODE_F,CHARMODE_NC,CHARMODE_NC);
            DispValTmpPQS[0] = kabs(vg_Power_Val.PFTA);
            DispValue(1,DispValTmpPQS[0],3,4,FALSE,0,FALSE,FALSE);
            DispChar(3,CHARMODE_NC,CHARMODE_De,CHARMODE_NC,CHARMODE_NC);
            DispChar(4,CHARMODE_NC,CHARMODE_Dpf,CHARMODE_NC,CHARMODE_NC);
            break;
        case MENU_INDEX_F:
            UintFlag = 0x00;
            for(u8 j = 0;j<DIN_NUM;j++)
            {
                if(g_Din_Status[j])
                    tmpInCharmode[j] = CHARMODE_0;
                else
                    tmpInCharmode[j] = CHARMODE_1;
            }
            for(u8 k = 0;k<OUT_NUM;k++)
            {
                if(g_Out_Status[k])
                    tmpOutCharmode[k] = CHARMODE_1;
                else
                    tmpOutCharmode[k] = CHARMODE_0;
            }
            DispChar(0,tmpInCharmode[3],tmpInCharmode[2],tmpInCharmode[1],tmpInCharmode[0]);
            DispChar(1,tmpOutCharmode[3],tmpOutCharmode[2],tmpOutCharmode[1],tmpOutCharmode[0]);
            if(vg_Power_Val.Freq == 0)
            {
                DispChar(2,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU);
            }
            else
            {
                DispValue(2,vg_Power_Val.Freq, 2, 4, FALSE, 0, FALSE, FALSE);
            }
            UintFlag |= CHARMODE_Dhz;
            DispChar(5,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
            break;
        /*=================================================================================================*/
        /*=================================================================================================*/
        case MENU_INDEX_PosEPT://��λk
            UintFlag = 0x00;
            if(ElectricEnergy.PosEPT > 999999)
            {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.PosEPT * 10);
                DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
                DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
                DispValue(2,DispValTmpPQS[2],1,4, FALSE, 0, TRUE, FALSE);
            }
            else
            {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.PosEPT * 100);
                DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
                DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
                DispValue(2,DispValTmpPQS[2],2,4, FALSE, 0, TRUE, FALSE);
            }
            DispChar(0,CHARMODE_E,CHARMODE_P,CHARMODE_NC,CHARMODE_NC);
            DispValue(1,DispValTmpPQS[1],0,4, FALSE, 0, TRUE, FALSE);

            UintFlag |= CHARMODE_Dkwh;
            DispChar(4,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
            break;
        case MENU_INDEX_NegEPT://��λk
            UintFlag = 0x00;
            if(ElectricEnergy.NegEPT > 999999)
            {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.NegEPT * 10);
                DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
                DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
                DispValue(2,DispValTmpPQS[2],1,4, FALSE, 0, TRUE, FALSE);
            }
            else
            {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.NegEPT * 100);
                DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
                DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
                DispValue(2,DispValTmpPQS[2],2,4, FALSE, 0, TRUE, FALSE);
            }
            DispChar(0,CHARMODE_E,CHARMODE_P,CHARMODE_FU,CHARMODE_NC);
            DispValue(1,DispValTmpPQS[1],0,4, FALSE, 0, TRUE, FALSE);

            UintFlag |= CHARMODE_Dkwh;
            DispChar(4,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);
            break;
	    case MENU_INDEX_PosEQT://��λk
	        UintFlag = 0x00;
	        if(ElectricEnergy.PosEQT > 999999)
	        {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.PosEQT * 10);
		        DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
		        DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
		        DispValue(2,DispValTmpPQS[2],1,4, FALSE, 0, TRUE, FALSE);
	        }
	        else
	        {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.PosEQT * 100);
		        DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
		        DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
		        DispValue(2,DispValTmpPQS[2],2,4, FALSE, 0, TRUE, FALSE);
	        }

	        DispChar(0,CHARMODE_E,CHARMODE_Q,CHARMODE_NC,CHARMODE_NC);
            DispValue(1,DispValTmpPQS[1],0,4, FALSE, 0, TRUE, FALSE);

            UintFlag |= CHARMODE_Dkvarh;
            DispChar(5,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);

			break;
	    case MENU_INDEX_NegEQT://��λk
	        UintFlag = 0x00;
	        if(ElectricEnergy.NegEQT > 999999)
	        {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.NegEQT * 10);
		        DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
		        DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
		        DispValue(2,DispValTmpPQS[2],1,4, FALSE, 0, TRUE, FALSE);
	        }
	        else
	        {
                DispValTmpPQS[0] = (s32)(ElectricEnergy.NegEQT * 100);
		        DispValTmpPQS[1] = DispValTmpPQS[0]/10000;
		        DispValTmpPQS[2] = DispValTmpPQS[0]%10000;
		        DispValue(2,DispValTmpPQS[2],2,4, FALSE, 0, TRUE, FALSE);
	        }

	        DispChar(0,CHARMODE_E,CHARMODE_Q,CHARMODE_FU,CHARMODE_NC);
            DispValue(1,DispValTmpPQS[1],0,4, FALSE, 0, TRUE, FALSE);

            UintFlag |= CHARMODE_Dkvarh;
            DispChar(5,CHARMODE_ALL,UintFlag,CHARMODE_NC,CHARMODE_NC);

			break;
        case MENU_INDEX_HarmU: // ��ѹ��г��
            if(sg_b2sFlashEnable == FALSE)
            {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_NC);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_FU,CHARMODE_U);
            }
            else
            {
                if(g_tParam.CtrlParam.NetMode == N34)
                {
                    DispValue(0,vg_Power_Val.Real2_Val[0].THDU, 2, 4, FALSE,0, TRUE, FALSE);
                	DispValue(1,vg_Power_Val.Real2_Val[1].THDU, 2, 4, FALSE,0, TRUE, FALSE);
                	DispValue(2,vg_Power_Val.Real2_Val[2].THDU, 2, 4, FALSE,0, TRUE, FALSE);
                }
                else
                {
                    DispValue(0,vg_Power_Val.Real2_Val[0].THDU, 2, 4, FALSE,0, TRUE, FALSE);
        			DispValue(1,vg_Power_Val.Real2_Val[2].THDU, 2, 4, FALSE,0, TRUE, FALSE);
        			DispChar(2,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU,CHARMODE_FU);
                }
            }
            break;
        case MENU_INDEX_HarmI:  // ������г��
            if(sg_b2sFlashEnable == FALSE)
            {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_NC);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_FU,CHARMODE_I);
            }
            else
            {
                DispValue(0,vg_Power_Val.Real2_Val[0].THDI, 2, 4, FALSE,0, TRUE, FALSE);
                DispValue(1,vg_Power_Val.Real2_Val[1].THDI, 2, 4, FALSE,0, TRUE, FALSE);
                DispValue(2,vg_Power_Val.Real2_Val[2].THDI, 2, 4, FALSE,0, TRUE, FALSE);
            }
            break;
	    case MENU_INDEX_HarmU3:
            if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_3);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,3);
	        }
            break;
        case MENU_INDEX_HarmU5:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_5);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,5);
	        }
            break;
        case MENU_INDEX_HarmU7:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_7);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,7);
	        }
            break;
        case MENU_INDEX_HarmU9:
	       if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_9);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,9);
	        }
            break;
        case MENU_INDEX_HarmU11:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_1);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,11);
	        }
            break;
        case MENU_INDEX_HarmU13:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_3);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,13);
	        }
            break;
        case MENU_INDEX_HarmU15:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_5);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,15);
	        }
            break;
        case MENU_INDEX_HarmU17:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_7);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,17);
	        }
            break;
        case MENU_INDEX_HarmU19:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_9);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,19);
	        }
            break;
        case MENU_INDEX_HarmU21:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_1);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,21);
	        }
            break;
        case MENU_INDEX_HarmU23:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_3);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,23);
	        }
            break;
        case MENU_INDEX_HarmU25:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_5);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,5);
	        }
            break;
        case MENU_INDEX_HarmU27:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_7);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,27);
	        }
            break;
        case MENU_INDEX_HarmU29:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_9);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,29);
	        }
            break;
        case MENU_INDEX_HarmU31:
            if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_U);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_3,CHARMODE_1);
	        }
	        else
	        {
                DispHarmonicContent(TRUE,31);
	        }
            break;
        case MENU_INDEX_HarmI3:
            if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_3);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,3);
	        }
            break;
        case MENU_INDEX_HarmI5:
	       if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_5);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,5);
	        }
            break;
        case MENU_INDEX_HarmI7:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_7);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,7);
	        }
            break;
        case MENU_INDEX_HarmI9:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_9);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,9);
	        }
            break;
        case MENU_INDEX_HarmI11:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_1);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,11);
	        }
            break;
        case MENU_INDEX_HarmI13:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_3);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,13);
	        }
            break;
        case MENU_INDEX_HarmI15:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_5);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,15);
	        }
            break;
        case MENU_INDEX_HarmI17:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_7);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,17);
	        }
            break;
        case MENU_INDEX_HarmI19:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_1,CHARMODE_9);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,19);
	        }
            break;
        case MENU_INDEX_HarmI21:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_1);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,21);
	        }
            break;
        case MENU_INDEX_HarmI23:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_3);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,23);
	        }
            break;
        case MENU_INDEX_HarmI25:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_5);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,25);
	        }
            break;
        case MENU_INDEX_HarmI27:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_7);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,27);
	        }
            break;
        case MENU_INDEX_HarmI29:
	        if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_2,CHARMODE_9);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,29);
	        }
            break;
        case MENU_INDEX_HarmI31:
            if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_T,CHARMODE_h,CHARMODE_D,CHARMODE_I);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_3,CHARMODE_1);
	        }
	        else
	        {
                DispHarmonicContent(FALSE,31);
	        }
            break;
        case MENU_INDEX_Uimb:
            DispChar(0,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_NC);
		    DispValue(1,vg_Power2_Val.U_Imb, 2, 4, FALSE,0, TRUE, FALSE);
		    DispValue(2,vg_Power2_Val.I_Imb, 2, 4, FALSE,0, TRUE, FALSE);
            break;
        case MENU_INDEX_UAngle:
            if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_D,CHARMODE_E,CHARMODE_G,CHARMODE_NC);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_U);
	        }
	        else
	        {
                DispValue(0,Phase_U[0], 1, 4, FALSE,0, FALSE, FALSE);
			    DispValue(1,Phase_U[1], 1, 4, FALSE,0, FALSE, FALSE);
			    DispValue(2,Phase_U[2], 1, 4, FALSE,0, FALSE, FALSE);
	        }
            break;
        case MENU_INDEX_IAngle:
            if(sg_b2sFlashEnable == FALSE)
	        {
                DispChar(0,CHARMODE_D,CHARMODE_E,CHARMODE_G,CHARMODE_NC);
                DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_I);
	        }
	        else
	        {
                DispValue(0,Phase_I[0], 1, 4, FALSE,0, FALSE, FALSE);
			    DispValue(1,Phase_I[1], 1, 4, FALSE,0, FALSE, FALSE);
			    DispValue(2,Phase_I[2], 1, 4, FALSE,0, FALSE, FALSE);
	        }
            break;
		default :
			break;
	}
}


void DispMenu_Menu1(void) //һ������(����)
{
    switch (sg_DispSubMainMenuIndex)
	{
		case MENUSUB_INDEX_READ:
			DispChar(0,CHARMODE_R,CHARMODE_E,CHARMODE_A,CHARMODE_D);
			break;
		case MENUSUB_INDEX_PROG:
		    DispChar(0,CHARMODE_P,CHARMODE_R,CHARMODE_O,CHARMODE_G);
            break;
		default :
			break;
	}
}


void DispMenu_Menu2(void) //�������� ����ѡ��(4)
{
	switch(sg_DispSetMenu1Index)
	{
		case MENU1_INDEX_INPT:
			DispChar(0,CHARMODE_I, CHARMODE_N,CHARMODE_P,CHARMODE_T);
		    break;
		case MENU1_INDEX_COM1:
			DispChar(0,CHARMODE_NC,CHARMODE_C,CHARMODE_O,CHARMODE_M);
		    break;
		case MENU1_INDEX_SYS:
			DispChar(0,CHARMODE_NC,CHARMODE_S,CHARMODE_Y,CHARMODE_S);
		    break;
		case MENU1_INDEX_DO1:
			DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
		    break;
		case MENU1_INDEX_DO2:
			DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
		    break;
		case MENU1_INDEX_DO3:
			DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_3);
		    break;
		case MENU1_INDEX_DO4:
			DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_4);
		    break;
		case MENU1_INDEX_AO1:
			DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
		    break;
		case MENU1_INDEX_AO2:
			DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
		    break;
		case MENU1_INDEX_VER:
			DispChar(0,CHARMODE_NC,CHARMODE_U,CHARMODE_E,CHARMODE_R);
			DispChar(2,CHARMODE_1,CHARMODE_7,CHARMODE_1,CHARMODE_2);
		    break;
		default:
		    break;
	}
}


void DispMenu_Menu3(void) //��������
{
    if(DispMode == ProgMode)
    {
    	switch(sg_DispSetMenu1Index)
    	{
    		case MENU1_INDEX_INPT:
    			DispChar(0,CHARMODE_I,CHARMODE_N,CHARMODE_P,CHARMODE_T);
    			switch(sg_DispSetMenu2_1_Index)
    			{
    			    case MENU2_1_INDEX_NET:
                        DispChar(1,CHARMODE_NC,CHARMODE_N,CHARMODE_E,CHARMODE_T);
                        break;
    				case MENU2_1_INDEX_PT:
    					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_P,CHARMODE_T);
    				    break;
    				case MENU2_1_INDEX_CT:
    					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_C,CHARMODE_T);
    				    break;
    				default:
    				    break;
    			}
    		    break;
            case MENU1_INDEX_COM1:
                DispChar(0,CHARMODE_NC,CHARMODE_C,CHARMODE_O,CHARMODE_M);
    			switch(sg_DispSetMenu2_2_Index)
    			{
    				case MENU2_2_INDEX_ADD:
                        DispChar(1,CHARMODE_NC,CHARMODE_A,CHARMODE_D,CHARMODE_D);
    				    break;
    				case MENU2_2_INDEX_BAUD:
    					DispChar(1,CHARMODE_B,CHARMODE_A,CHARMODE_U,CHARMODE_D);
    			    	break;
    				case MENU2_2_INDEX_DATA:
    					DispChar(1,CHARMODE_D,CHARMODE_A,CHARMODE_T,CHARMODE_A);
    				    break;
    				case MENU2_2_INDEX_COMS:
    					DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_M,CHARMODE_S);
    				    break;
    				default:
    				    break;
    			}
    		    break;
            case MENU1_INDEX_SYS:
                DispChar(0,CHARMODE_NC,CHARMODE_S,CHARMODE_Y,CHARMODE_S);
    			switch(sg_DispSetMenu2_3_Index)
    			{
    				case MENU2_3_INDEX_CYC:
    					DispChar(1,CHARMODE_NC,CHARMODE_C,CHARMODE_Y,CHARMODE_C);
    				    break;
    				case MENU2_3_INDEX_LIGH:
    					DispChar(1,CHARMODE_L,CHARMODE_I,CHARMODE_G,CHARMODE_H);
    				    break;
    				case MENU2_3_INDEX_T:
    					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_G,CHARMODE_H);
    				    break;
    				case MENU2_3_INDEX_DISP:
    					DispChar(1,CHARMODE_D,CHARMODE_I,CHARMODE_S,CHARMODE_P);
    				    break;
    				case MENU2_3_INDEX_ALR:
    					DispChar(1,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
    				    break;
    				case MENU2_3_INDEX_CLRE:
    					DispChar(1,CHARMODE_C,CHARMODE_L,CHARMODE_R + CHARMODE_DOT,CHARMODE_E);
    				    break;
    				case MENU2_3_INDEX_CODE:
    					DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_D,CHARMODE_E);
    				    break;
    				default:
    				    break;
    			}
    		    break;
    		case MENU1_INDEX_DO1:
                DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
    			switch(sg_DispSetMenu2_4_Index)
    			{
    				case MENU2_4_INDEX_MODE:
                        DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
    				    break;
    				case MENU2_4_INDEX_TIME:
    					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);
    			    	break;
    				case MENU2_4_INDEX_ITEM:
    					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
    			    	break;
    				case MENU2_4_INDEX_UAL:
    					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);
    				    break;
    				case MENU2_4_INDEX_HYS:
    					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
    				    break;
    				case MENU2_4_INDEX_DELAY:
    					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
    				    break;
    				default:
    				    break;
    			}
    		    break;
    		case MENU1_INDEX_DO2:
                DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
    			switch(sg_DispSetMenu2_5_Index)
    			{
    				case MENU2_5_INDEX_MODE:
                        DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
    				    break;
    				case MENU2_5_INDEX_TIME:
    					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);
    			    	break;
    				case MENU2_5_INDEX_ITEM:
    					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
    			    	break;
    				case MENU2_5_INDEX_UAL:
    					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);
    				    break;
    				case MENU2_5_INDEX_HYS:
    					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
    				    break;
    				case MENU2_5_INDEX_DELAY:
    					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
    				    break;
    				default:
    				    break;
    			}
    		    break;
    		case MENU1_INDEX_DO3:
                DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_3);
    			switch(sg_DispSetMenu2_6_Index)
    			{
    				case MENU2_6_INDEX_MODE:
                        DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
    				    break;
    				case MENU2_6_INDEX_TIME:
    					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);
    			    	break;
    				case MENU2_6_INDEX_ITEM:
    					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
    			    	break;
    				case MENU2_6_INDEX_UAL:
    					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);
    				    break;
    				case MENU2_6_INDEX_HYS:
    					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
    				    break;
    				case MENU2_6_INDEX_DELAY:
    					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
    				    break;
    				default:
    				    break;
    			}
    		    break;
    		case MENU1_INDEX_DO4:
                DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_4);
    			switch(sg_DispSetMenu2_7_Index)
    			{
    				case MENU2_7_INDEX_MODE:
                        DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
    				    break;
    				case MENU2_7_INDEX_TIME:
    					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);
    			    	break;
    				case MENU2_7_INDEX_ITEM:
    					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
    			    	break;
    				case MENU2_7_INDEX_UAL:
    					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);
    				    break;
    				case MENU2_7_INDEX_HYS:
    					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
    				    break;
    				case MENU2_7_INDEX_DELAY:
    					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
    				    break;
    				default:
    				    break;
    			}
    		    break;
    		case MENU1_INDEX_AO1:
                DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
    			switch(sg_DispSetMenu2_8_Index)
    			{
    				case MENU2_8_INDEX_MODE:
                        DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
    				    break;
    				case MENU2_8_INDEX_ITEM:
    					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
    			    	break;
    				case MENU2_8_INDEX_DS:
    					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_D,CHARMODE_S);
    				    break;
    				case MENU2_8_INDEX_FS:
    					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_F,CHARMODE_S);
    				    break;
    				default:
    				    break;
    			}
    		    break;
    		case MENU1_INDEX_AO2:
                DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
    			switch(sg_DispSetMenu2_9_Index)
    			{
    				case MENU2_9_INDEX_MODE:
                        DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
    				    break;
    				case MENU2_9_INDEX_ITEM:
    					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
    			    	break;
    				case MENU2_9_INDEX_DS:
    					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_D,CHARMODE_S);
    				    break;
    				case MENU2_9_INDEX_FS:
    					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_F,CHARMODE_S);
    				    break;
    				default:
    				    break;
    			}
    		    break;
    		default:
    		    break;
    	}
    }
    else if(DispMode == ReadMode)
    {
        u8 Decimal = 0;
        sg_bSetFlashEnable = FALSE;
        switch(sg_DispSetMenu1Index)
    	{
    		case MENU1_INDEX_INPT:
			DispChar(0,CHARMODE_I,CHARMODE_N,CHARMODE_P,CHARMODE_T);
			switch(sg_DispSetMenu2_1_Index)
			{
                case MENU2_1_INDEX_NET:
                    DispChar(1,CHARMODE_NC,CHARMODE_N,CHARMODE_E,CHARMODE_T);
                    if( sg_DispSetValue == N34)
                    {
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_3,CHARMODE_4);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                    }
                    else if( sg_DispSetValue == N33)
                    {
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_3,CHARMODE_3);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                    }
                    break;
				case MENU2_1_INDEX_PT:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_P,CHARMODE_T);

					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal, Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_1_INDEX_CT:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_C,CHARMODE_T);

					Decimal = 0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
		    break;
	    case MENU1_INDEX_COM1:
	        DispChar(0,CHARMODE_NC,CHARMODE_C,CHARMODE_O,CHARMODE_M);
			switch(sg_DispSetMenu2_2_Index)
			{
				case MENU2_2_INDEX_ADD:
					DispChar(1,CHARMODE_NC,CHARMODE_A,CHARMODE_D,CHARMODE_D);
					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, FALSE, TRUE);
					CharToNumber();
				    break;
				case MENU2_2_INDEX_BAUD:
					DispChar(1,CHARMODE_B,CHARMODE_A,CHARMODE_U,CHARMODE_D);
					if(sg_bSetFlashEnable)
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else
					{
                        switch(sg_DispSetValue)
    					{
                            case Baud12:
                                DispChar(2,CHARMODE_1,CHARMODE_2,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud24:
                                DispChar(2,CHARMODE_2,CHARMODE_4,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud48:
                                DispChar(2,CHARMODE_4,CHARMODE_8,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud96:
                                DispChar(2,CHARMODE_9,CHARMODE_6,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud192:
                                DispChar(2,CHARMODE_1,CHARMODE_9+CHARMODE_DOT,CHARMODE_2,CHARMODE_0);
                                break;
                            default:
                                break;
    					}
					}
			    	break;
				case MENU2_2_INDEX_DATA:
					DispChar(1,CHARMODE_D,CHARMODE_A,CHARMODE_T,CHARMODE_A);
				    if(sg_bSetFlashEnable)
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else
					{
                        switch(sg_DispSetValue)
    					{
                            case n81:
                                DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_8,CHARMODE_1);
                                break;
                            case o81:
                                DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_8,CHARMODE_1);
                                break;
                            case e81:
                                DispChar(2,CHARMODE_NC,CHARMODE_E,CHARMODE_8,CHARMODE_1);
                                break;
                            case n82:
                                DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_8,CHARMODE_2);
                                break;
                            default:
                                break;
    					}
					}
			    	break;
				case MENU2_2_INDEX_COMS:
					DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_M,CHARMODE_S);
					if(sg_DispSetValue == rtu485)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_T,CHARMODE_U);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else if( sg_DispSetValue == calib)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_C,CHARMODE_A,CHARMODE_L);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				default:
				    break;
			}
		    break;
        case MENU1_INDEX_SYS:
            DispChar(0,CHARMODE_NC,CHARMODE_S,CHARMODE_Y,CHARMODE_S);
            switch(sg_DispSetMenu2_3_Index)
			{
                case MENU2_3_INDEX_CYC:
					DispChar(1,CHARMODE_NC,CHARMODE_C,CHARMODE_Y,CHARMODE_C);

					if(sg_DispSetValue == SaveYes)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_Y,CHARMODE_E,CHARMODE_S);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else if( sg_DispSetValue == SaveNO)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_N,CHARMODE_O);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_3_INDEX_LIGH:        // ���ȵȼ�
					DispChar(1,CHARMODE_L,CHARMODE_I,CHARMODE_G,CHARMODE_H);
					if(!sg_bSetFlashEnable)
					{
                        switch(sg_DispSetValue)
                        {
                            case BrightLevel_1:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_L,CHARMODE_1);
                                break;
                            case BrightLevel_2:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_L,CHARMODE_2);
                                break;
                            case BrightLevel_3:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_L,CHARMODE_3);
                                break;
                            default:
                                break;
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_3_INDEX_DISP:
					DispChar(1,CHARMODE_D,CHARMODE_I,CHARMODE_S,CHARMODE_P);
					if(!sg_bSetFlashEnable)
					{
                        switch(sg_DispSetValue)
                        {
                            case DISP_UINT_U:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_U);
                                break;
                            case DISP_UINT_I:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_I);
                                break;
                            case DISP_UINT_P:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_P);
                                break;
                            case DISP_UINT_PF:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_F);
                                break;
                            case DISP_UINT_EP:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_E,CHARMODE_P);
                                break;
                            case DISP_UINT_THD:
                                DispChar(2,CHARMODE_NC,CHARMODE_T,CHARMODE_H,CHARMODE_D);
                                break;
                            default:
                                break;
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
			    case MENU2_3_INDEX_ALR:
					DispChar(1,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal, Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_3_INDEX_CLRE:
					DispChar(1,CHARMODE_C,CHARMODE_L,CHARMODE_R + CHARMODE_DOT,CHARMODE_E);

                    if(sg_DispSetValue == SaveYes)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_Y,CHARMODE_E,CHARMODE_S);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else if( sg_DispSetValue == SaveNO)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_N,CHARMODE_O);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_3_INDEX_CODE:
					DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_D,CHARMODE_E);

					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal, Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, FALSE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
		    break;
		case MENU1_INDEX_DO1:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
            switch(sg_DispSetMenu2_4_Index)
			{
                case MENU2_4_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_4_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_4_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_L);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
				case MENU2_4_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO1_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_4_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO1_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_4_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
            break;
        case MENU1_INDEX_DO2:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
            switch(sg_DispSetMenu2_5_Index)
			{
                case MENU2_5_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_5_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_5_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //    case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_L);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
			    case MENU2_5_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO2_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_5_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO2_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_5_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
			break;
        case MENU1_INDEX_DO3:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_3);
            switch(sg_DispSetMenu2_6_Index)
			{
                case MENU2_6_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_6_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_6_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_L);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
			    case MENU2_6_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO3_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_6_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO3_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_6_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
			break;
        case MENU1_INDEX_DO4:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_4);
            switch(sg_DispSetMenu2_7_Index)
			{
                case MENU2_7_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_7_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_7_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_L);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_H);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_L);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
			    case MENU2_7_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO4_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_7_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO4_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_7_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
			break;
        case MENU1_INDEX_AO1:
            DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
            switch(sg_DispSetMenu2_8_Index)
			{
                case MENU2_8_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
					    if(sg_DispSetValue == AO_MODE_OFF)
					        DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == AO_MODE_420)
                            DispChar(2,CHARMODE_NC,CHARMODE_4,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_020)
                            DispChar(2,CHARMODE_NC,CHARMODE_0,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_1220)
                        {
                            DispChar(2,CHARMODE_1,CHARMODE_2,CHARMODE_2,CHARMODE_0);
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_8_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
                            case AO_ITEM_UA:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UB:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UC:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UAB:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_UBC:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_UCA:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_IA:
                                DispChar(2,CHARMODE_I,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IB:
                                DispChar(2,CHARMODE_I,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IC:
                                DispChar(2,CHARMODE_I,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PA:
                                DispChar(2,CHARMODE_P,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PB:
                                DispChar(2,CHARMODE_P,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PC:
                                DispChar(2,CHARMODE_P,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_P:
                                DispChar(2,CHARMODE_P,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QA:
                                DispChar(2,CHARMODE_Q,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QB:
                                DispChar(2,CHARMODE_Q,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QC:
                                DispChar(2,CHARMODE_Q,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_Q:
                                DispChar(2,CHARMODE_Q,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SA:
                                DispChar(2,CHARMODE_S,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SB:
                                DispChar(2,CHARMODE_S,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SC:
                                DispChar(2,CHARMODE_S,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_S:
                                DispChar(2,CHARMODE_S,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFA:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFB:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFC:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_PF:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_F:
                                DispChar(2,CHARMODE_F,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
				case MENU2_8_INDEX_DS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_D,CHARMODE_S);
					switch(DispCtrlParam.AO1_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_8_INDEX_FS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_F,CHARMODE_S);
					switch(DispCtrlParam.AO1_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
            break;
        case MENU1_INDEX_AO2:
            DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
            switch(sg_DispSetMenu2_9_Index)
			{
                case MENU2_9_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
					    if(sg_DispSetValue == AO_MODE_OFF)
					        DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == AO_MODE_420)
                            DispChar(2,CHARMODE_NC,CHARMODE_4,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_020)
                            DispChar(2,CHARMODE_NC,CHARMODE_0,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_1220)
                        {
                            DispChar(2,CHARMODE_1,CHARMODE_2,CHARMODE_2,CHARMODE_0);
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_9_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
                            case AO_ITEM_UA:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UB:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UC:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UAB:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_UBC:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_UCA:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_IA:
                                DispChar(2,CHARMODE_I,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IB:
                                DispChar(2,CHARMODE_I,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IC:
                                DispChar(2,CHARMODE_I,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PA:
                                DispChar(2,CHARMODE_P,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PB:
                                DispChar(2,CHARMODE_P,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PC:
                                DispChar(2,CHARMODE_P,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_P:
                                DispChar(2,CHARMODE_P,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QA:
                                DispChar(2,CHARMODE_Q,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QB:
                                DispChar(2,CHARMODE_Q,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QC:
                                DispChar(2,CHARMODE_Q,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_Q:
                                DispChar(2,CHARMODE_Q,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SA:
                                DispChar(2,CHARMODE_S,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SB:
                                DispChar(2,CHARMODE_S,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SC:
                                DispChar(2,CHARMODE_S,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_S:
                                DispChar(2,CHARMODE_S,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFA:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFB:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFC:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_PF:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_F:
                                DispChar(2,CHARMODE_F,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
				case MENU2_9_INDEX_DS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_D,CHARMODE_S);
					switch(DispCtrlParam.AO2_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_9_INDEX_FS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_F,CHARMODE_S);
					switch(DispCtrlParam.AO2_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
            break;
		default:
		    break;
    	}
    }
}


void DispMenu_MenuValue(void) //4���˵�
{
	u8 Decimal = 0;
	if(DispMode == ReadMode)
	{
        sg_bSetFlashEnable = FALSE; //�鿴ѡ�����˸
	}
	switch(sg_DispSetMenu1Index)
	{
		case MENU1_INDEX_INPT:
			DispChar(0,CHARMODE_I,CHARMODE_N,CHARMODE_P,CHARMODE_T);
			switch(sg_DispSetMenu2_1_Index)
			{
                case MENU2_1_INDEX_NET:
                    DispChar(1,CHARMODE_NC,CHARMODE_N,CHARMODE_E,CHARMODE_T);
                    if( sg_DispSetValue == N34)
                    {
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_3,CHARMODE_4);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                    }
                    else if( sg_DispSetValue == N33)
                    {
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_3,CHARMODE_3);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                    }
                    break;
				case MENU2_1_INDEX_PT:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_P,CHARMODE_T);

					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal, Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_1_INDEX_CT:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_C,CHARMODE_T);

					Decimal = 0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
		    break;
	    case MENU1_INDEX_COM1:
	        DispChar(0,CHARMODE_NC,CHARMODE_C,CHARMODE_O,CHARMODE_M);
			switch(sg_DispSetMenu2_2_Index)
			{
				case MENU2_2_INDEX_ADD:
					DispChar(1,CHARMODE_NC,CHARMODE_A,CHARMODE_D,CHARMODE_D);
					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, FALSE, TRUE);
					CharToNumber();
				    break;
				case MENU2_2_INDEX_BAUD:
					DispChar(1,CHARMODE_B,CHARMODE_A,CHARMODE_U,CHARMODE_D);
					if(sg_bSetFlashEnable)
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else
					{
                        switch(sg_DispSetValue)
    					{
                            case Baud12:
                                DispChar(2,CHARMODE_1,CHARMODE_2,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud24:
                                DispChar(2,CHARMODE_2,CHARMODE_4,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud48:
                                DispChar(2,CHARMODE_4,CHARMODE_8,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud96:
                                DispChar(2,CHARMODE_9,CHARMODE_6,CHARMODE_0,CHARMODE_0);
                                break;
                            case Baud192:
                                DispChar(2,CHARMODE_1,CHARMODE_9+CHARMODE_DOT,CHARMODE_2,CHARMODE_0);
                                break;
                            default:
                                break;
    					}
					}
			    	break;
				case MENU2_2_INDEX_DATA:
					DispChar(1,CHARMODE_D,CHARMODE_A,CHARMODE_T,CHARMODE_A);
				    if(sg_bSetFlashEnable)
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else
					{
                        switch(sg_DispSetValue)
    					{
                            case n81:
                                DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_8,CHARMODE_1);
                                break;
                            case o81:
                                DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_8,CHARMODE_1);
                                break;
                            case e81:
                                DispChar(2,CHARMODE_NC,CHARMODE_E,CHARMODE_8,CHARMODE_1);
                                break;
                            case n82:
                                DispChar(2,CHARMODE_NC,CHARMODE_N,CHARMODE_8,CHARMODE_2);
                                break;
                            default:
                                break;
    					}
					}
			    	break;
				case MENU2_2_INDEX_COMS:
					DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_M,CHARMODE_S);
					if(sg_DispSetValue == rtu485)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_T,CHARMODE_U);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else if( sg_DispSetValue == calib)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_C,CHARMODE_A,CHARMODE_L);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				default:
				    break;
			}
		    break;
        case MENU1_INDEX_SYS:
            DispChar(0,CHARMODE_NC,CHARMODE_S,CHARMODE_Y,CHARMODE_S);
            switch(sg_DispSetMenu2_3_Index)
			{
                case MENU2_3_INDEX_CYC:
					DispChar(1,CHARMODE_NC,CHARMODE_C,CHARMODE_Y,CHARMODE_C);

					if(sg_DispSetValue == SaveYes)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_Y,CHARMODE_E,CHARMODE_S);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else if( sg_DispSetValue == SaveNO)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_N,CHARMODE_O);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_3_INDEX_LIGH:        // ���ȵȼ�
					DispChar(1,CHARMODE_L,CHARMODE_I,CHARMODE_G,CHARMODE_H);
					if(!sg_bSetFlashEnable)
					{
                        switch(sg_DispSetValue)
                        {
                            case BrightLevel_1:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_L,CHARMODE_1);
                                break;
                            case BrightLevel_2:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_L,CHARMODE_2);
                                break;
                            case BrightLevel_3:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_L,CHARMODE_3);
                                break;
                            default:
                                break;
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_3_INDEX_DISP:
					DispChar(1,CHARMODE_D,CHARMODE_I,CHARMODE_S,CHARMODE_P);
					if(!sg_bSetFlashEnable)
					{
                        switch(sg_DispSetValue)
                        {
                            case DISP_UINT_U:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_U);
                                break;
                            case DISP_UINT_I:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_I);
                                break;
                            case DISP_UINT_P:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_P);
                                break;
                            case DISP_UINT_PF:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_F);
                                break;
                            case DISP_UINT_EP:
                                DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_E,CHARMODE_P);
                                break;
                            case DISP_UINT_THD:
                                DispChar(2,CHARMODE_NC,CHARMODE_T,CHARMODE_H,CHARMODE_D);
                                break;
                            default:
                                break;
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
			    case MENU2_3_INDEX_ALR:
					DispChar(1,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal, Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_3_INDEX_CLRE:
					DispChar(1,CHARMODE_C,CHARMODE_L,CHARMODE_R + CHARMODE_DOT,CHARMODE_E);

                    if(sg_DispSetValue == SaveYes)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_Y,CHARMODE_E,CHARMODE_S);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
					else if( sg_DispSetValue == SaveNO)
					{
                        if(!sg_bSetFlashEnable)
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_N,CHARMODE_O);
                		else
                			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_3_INDEX_CODE:
					DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_D,CHARMODE_E);

					Decimal =  0;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal, Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, FALSE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
		    break;
		case MENU1_INDEX_DO1:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
            switch(sg_DispSetMenu2_4_Index)
			{
                case MENU2_4_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_4_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_4_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_0);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
				case MENU2_4_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO1_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_4_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO1_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_4_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
            break;
        case MENU1_INDEX_DO2:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
            switch(sg_DispSetMenu2_5_Index)
			{
                case MENU2_5_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_5_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_5_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //    case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_0);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
			    case MENU2_5_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO2_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_5_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO2_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_5_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
			break;
        case MENU1_INDEX_DO3:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_3);
            switch(sg_DispSetMenu2_6_Index)
			{
                case MENU2_6_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_6_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_6_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_0);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
			    case MENU2_6_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO3_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_6_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO3_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_6_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
			break;
        case MENU1_INDEX_DO4:
            DispChar(0,CHARMODE_D,CHARMODE_O,CHARMODE_FU,CHARMODE_4);
            switch(sg_DispSetMenu2_7_Index)
			{
                case MENU2_7_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
                        if(sg_DispSetValue == DO_MODE_OFF)
                            DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == DO_MODE_ALR)
                            DispChar(2,CHARMODE_NC,CHARMODE_A,CHARMODE_L,CHARMODE_R);
                        else if(sg_DispSetValue == DO_MODE_REM)
                            DispChar(2,CHARMODE_NC,CHARMODE_R,CHARMODE_E,CHARMODE_M);
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_7_INDEX_TIME:
					DispChar(1,CHARMODE_T,CHARMODE_I,CHARMODE_M,CHARMODE_E);

                    Decimal =  2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
			    	break;
				case MENU2_7_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);

					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
							case DO_ITEM_Ua_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ua_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ub_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ub_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Uavg_H:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Uavg_L:
                                DispChar(2,CHARMODE_U + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
							case DO_ITEM_Uab_H:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uab_L:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Ubc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Ubc_L:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_Uca_H:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_Uca_L:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_ULavg_H:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_ULavg_L:
                                DispChar(2,CHARMODE_U,CHARMODE_L + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-------------------------------------------------------*/
                            case DO_ITEM_Ia_H:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ia_L:
                                DispChar(2,CHARMODE_I,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ib_H:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ib_L:
                                DispChar(2,CHARMODE_I,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Ic_H:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Ic_L:
                                DispChar(2,CHARMODE_I,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Iavg_H:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Iavg_L:
                                DispChar(2,CHARMODE_I + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Pa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Pc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Pc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_P_H:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_P_L:
                                DispChar(2,CHARMODE_P + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_Qa_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qa_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qb_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qb_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Qc_H:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Qc_L:
                                DispChar(2,CHARMODE_Q,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Q_H:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Q_L:
                                DispChar(2,CHARMODE_Q + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_Sa_H:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sa_L:
                                DispChar(2,CHARMODE_S,CHARMODE_A + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sb_H:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sb_L:
                                DispChar(2,CHARMODE_S,CHARMODE_B + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_Sc_H:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_Sc_L:
                                DispChar(2,CHARMODE_S,CHARMODE_C + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            case DO_ITEM_S_H:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_S_L:
                                DispChar(2,CHARMODE_S + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*------------------------------------------------------*/
                            case DO_ITEM_PFa_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFa_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFb_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFb_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PFc_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_H);
                                break;
                            case DO_ITEM_PFc_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C + CHARMODE_DOT,CHARMODE_L);
                                break;
                            case DO_ITEM_PF_H:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_PF_L:
                                DispChar(2,CHARMODE_P,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_F_H:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_H);
                                break;
                            case DO_ITEM_F_L:
                                DispChar(2,CHARMODE_F + CHARMODE_DOT,CHARMODE_NC,CHARMODE_NC,CHARMODE_L);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_UTHa_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_UTHb_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_UTHc_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_UTH_H:
                                DispChar(2,CHARMODE_U,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            case DO_ITEM_ITHa_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_A);
                                break;
                            case DO_ITEM_ITHb_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_B);
                                break;
                            case DO_ITEM_ITHc_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H + CHARMODE_DOT,CHARMODE_C);
                                break;
                            case DO_ITEM_ITH_H:
                                DispChar(2,CHARMODE_I,CHARMODE_T,CHARMODE_H,CHARMODE_NC);
                                break;
                            /*-----------------------------------------------------*/
                            case DO_ITEM_IMBU_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_U);
                                break;
                            case DO_ITEM_IMBI_H:
                                DispChar(2,CHARMODE_I,CHARMODE_M,CHARMODE_B,CHARMODE_I);
                                break;
                            //case DO_ITEM_Io_H:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_H);
                            //    break;
                            //case DO_ITEM_Io_L:
                            //    DispChar(2,CHARMODE_I,CHARMODE_O + CHARMODE_DOT,CHARMODE_NC,CHARMODE_L);
                            //    break;
                            /*-----------------------------------------------------*/

                            case DO_ITEM_DI1_H:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI1_L:
                                DispChar(2,CHARMODE_D,CHARMODE_1,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI2_H:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI2_L:
                                DispChar(2,CHARMODE_D,CHARMODE_2,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI3_H:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI3_L:
                                DispChar(2,CHARMODE_D,CHARMODE_3,CHARMODE_FU,CHARMODE_0);
                                break;
                            case DO_ITEM_DI4_H:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_1);
                                break;
                            case DO_ITEM_DI4_L:
                                DispChar(2,CHARMODE_D,CHARMODE_4,CHARMODE_FU,CHARMODE_0);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
			    case MENU2_7_INDEX_UAL:
					DispChar(1,CHARMODE_NC,CHARMODE_U,CHARMODE_A,CHARMODE_L);

                    switch(DispCtrlParam.DO4_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_7_INDEX_HYS:
					DispChar(1,CHARMODE_NC,CHARMODE_H,CHARMODE_Y,CHARMODE_S);
					switch(DispCtrlParam.DO4_Item)
				    {
						case DO_ITEM_Ua_H:
                        case DO_ITEM_Ua_L:
                        case DO_ITEM_Ub_H:
                        case DO_ITEM_Ub_L:
                        case DO_ITEM_Uc_H:
                        case DO_ITEM_Uc_L:
                        case DO_ITEM_Uavg_H:
                        case DO_ITEM_Uavg_L:
                        /*-------------------------------------------------------*/
						case DO_ITEM_Uab_H:
                        case DO_ITEM_Uab_L:
                        case DO_ITEM_Ubc_H:
                        case DO_ITEM_Ubc_L:
                        case DO_ITEM_Uca_H:
                        case DO_ITEM_Uca_L:
                        case DO_ITEM_ULavg_H:
                        case DO_ITEM_ULavg_L:
                            Decimal = 1;
                            break;
                        /*-------------------------------------------------------*/
                        case DO_ITEM_Ia_H:
                        case DO_ITEM_Ia_L:
                        case DO_ITEM_Ib_H:
                        case DO_ITEM_Ib_L:
                        case DO_ITEM_Ic_H:
                        case DO_ITEM_Ic_L:
                        case DO_ITEM_Iavg_H:
                        case DO_ITEM_Iavg_L:
                            Decimal = 3;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Pa_H:
                        case DO_ITEM_Pa_L:
                        case DO_ITEM_Pb_H:
                        case DO_ITEM_Pb_L:
                        case DO_ITEM_Pc_H:
                        case DO_ITEM_Pc_L:
                        case DO_ITEM_P_H:
                        case DO_ITEM_P_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_Qa_H:
                        case DO_ITEM_Qa_L:
                        case DO_ITEM_Qb_H:
                        case DO_ITEM_Qb_L:
                        case DO_ITEM_Qc_H:
                        case DO_ITEM_Qc_L:
                        case DO_ITEM_Q_H:
                        case DO_ITEM_Q_L:
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_Sa_H:
                        case DO_ITEM_Sa_L:
                        case DO_ITEM_Sb_H:
                        case DO_ITEM_Sb_L:
                        case DO_ITEM_Sc_H:
                        case DO_ITEM_Sc_L:
                        case DO_ITEM_S_H:
                        case DO_ITEM_S_L:
                            Decimal = 0;
                            break;
                        /*------------------------------------------------------*/
                        case DO_ITEM_PFa_H:
                        case DO_ITEM_PFa_L:
                        case DO_ITEM_PFb_H:
                        case DO_ITEM_PFb_L:
                        case DO_ITEM_PFc_H:
                        case DO_ITEM_PFc_L:
                        case DO_ITEM_PF_H:
                        case DO_ITEM_PF_L:
                            Decimal = 3;
                            break;
                        /*-----------------------------------------------------*/
                        case DO_ITEM_F_H:
                        case DO_ITEM_F_L:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_UTHa_H:
                        case DO_ITEM_UTHb_H:
                        case DO_ITEM_UTHc_H:
                        case DO_ITEM_UTH_H:
                        case DO_ITEM_ITHa_H:
                        case DO_ITEM_ITHb_H:
                        case DO_ITEM_ITHc_H:
                        case DO_ITEM_ITH_H:
                        /*-----------------------------------------------------*/
                        case DO_ITEM_IMBU_H:
                        case DO_ITEM_IMBI_H:
                            Decimal = 2;
                            break;
                        //case DO_ITEM_Io_H:
                        //case DO_ITEM_Io_L:
                        //    Decimal = 3;
                        //    break;
                        /*-----------------------------------------------------*/
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_7_INDEX_DELAY:
					DispChar(1,CHARMODE_D,CHARMODE_E,CHARMODE_L,CHARMODE_Y);
                    Decimal = 2;
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
			}
			break;
        case MENU1_INDEX_AO1:
            DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_1);
            switch(sg_DispSetMenu2_8_Index)
			{
                case MENU2_8_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
					    if(sg_DispSetValue == AO_MODE_OFF)
					        DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == AO_MODE_420)
                            DispChar(2,CHARMODE_NC,CHARMODE_4,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_020)
                            DispChar(2,CHARMODE_NC,CHARMODE_0,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_1220)
                        {
                            DispChar(2,CHARMODE_1,CHARMODE_2,CHARMODE_2,CHARMODE_0);
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_8_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
                            case AO_ITEM_UA:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UB:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UC:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UAB:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_UBC:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_UCA:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_IA:
                                DispChar(2,CHARMODE_I,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IB:
                                DispChar(2,CHARMODE_I,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IC:
                                DispChar(2,CHARMODE_I,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PA:
                                DispChar(2,CHARMODE_P,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PB:
                                DispChar(2,CHARMODE_P,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PC:
                                DispChar(2,CHARMODE_P,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_P:
                                DispChar(2,CHARMODE_P,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QA:
                                DispChar(2,CHARMODE_Q,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QB:
                                DispChar(2,CHARMODE_Q,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QC:
                                DispChar(2,CHARMODE_Q,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_Q:
                                DispChar(2,CHARMODE_Q,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SA:
                                DispChar(2,CHARMODE_S,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SB:
                                DispChar(2,CHARMODE_S,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SC:
                                DispChar(2,CHARMODE_S,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_S:
                                DispChar(2,CHARMODE_S,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFA:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFB:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFC:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_PF:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_F:
                                DispChar(2,CHARMODE_F,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
				case MENU2_8_INDEX_DS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_D,CHARMODE_S);
					switch(DispCtrlParam.AO1_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_8_INDEX_FS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_F,CHARMODE_S);
					switch(DispCtrlParam.AO1_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
            break;
        case MENU1_INDEX_AO2:
            DispChar(0,CHARMODE_A,CHARMODE_O,CHARMODE_FU,CHARMODE_2);
            switch(sg_DispSetMenu2_9_Index)
			{
                case MENU2_9_INDEX_MODE:
                    DispChar(1,CHARMODE_M,CHARMODE_O,CHARMODE_D,CHARMODE_E);
                    if(!sg_bSetFlashEnable)
					{
					    if(sg_DispSetValue == AO_MODE_OFF)
					        DispChar(2,CHARMODE_NC,CHARMODE_O,CHARMODE_F,CHARMODE_F);
                        else if(sg_DispSetValue == AO_MODE_420)
                            DispChar(2,CHARMODE_NC,CHARMODE_4,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_020)
                            DispChar(2,CHARMODE_NC,CHARMODE_0,CHARMODE_2,CHARMODE_0);
                        else if(sg_DispSetValue == AO_MODE_1220)
                        {
                            DispChar(2,CHARMODE_1,CHARMODE_2,CHARMODE_2,CHARMODE_0);
                        }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
				    break;
				case MENU2_9_INDEX_ITEM:
					DispChar(1,CHARMODE_I,CHARMODE_T,CHARMODE_E,CHARMODE_M);
					if(!sg_bSetFlashEnable)
					{
					    switch(sg_DispSetValue)
					    {
                            case AO_ITEM_UA:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UB:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UC:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_UAB:
                                DispChar(2,CHARMODE_U,CHARMODE_A,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_UBC:
                                DispChar(2,CHARMODE_U,CHARMODE_B,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_UCA:
                                DispChar(2,CHARMODE_U,CHARMODE_C,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_IA:
                                DispChar(2,CHARMODE_I,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IB:
                                DispChar(2,CHARMODE_I,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_IC:
                                DispChar(2,CHARMODE_I,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PA:
                                DispChar(2,CHARMODE_P,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PB:
                                DispChar(2,CHARMODE_P,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PC:
                                DispChar(2,CHARMODE_P,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_P:
                                DispChar(2,CHARMODE_P,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QA:
                                DispChar(2,CHARMODE_Q,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QB:
                                DispChar(2,CHARMODE_Q,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_QC:
                                DispChar(2,CHARMODE_Q,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_Q:
                                DispChar(2,CHARMODE_Q,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SA:
                                DispChar(2,CHARMODE_S,CHARMODE_A,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SB:
                                DispChar(2,CHARMODE_S,CHARMODE_B,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_SC:
                                DispChar(2,CHARMODE_S,CHARMODE_C,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_S:
                                DispChar(2,CHARMODE_S,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFA:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_A,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFB:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_B,CHARMODE_NC);
                                break;
                            case AO_ITEM_PFC:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_C,CHARMODE_NC);
                                break;
                            case AO_ITEM_PF:
                                DispChar(2,CHARMODE_P,CHARMODE_F,CHARMODE_NC,CHARMODE_NC);
                                break;
                            case AO_ITEM_F:
                                DispChar(2,CHARMODE_F,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
                                break;
                            default:
                                break;
					    }
					}
					else
					{
                        DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
					}
			    	break;
				case MENU2_9_INDEX_DS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_D,CHARMODE_S);
					switch(DispCtrlParam.AO2_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				case MENU2_9_INDEX_FS:
					DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_F,CHARMODE_S);
					switch(DispCtrlParam.AO2_Item)
				    {
                        case AO_ITEM_UA:
                        case AO_ITEM_UB:
                        case AO_ITEM_UC:
                        case AO_ITEM_UAB:
                        case AO_ITEM_UBC:
                        case AO_ITEM_UCA:
                            Decimal = 1;
                            break;
                        case AO_ITEM_IA:
                        case AO_ITEM_IB:
                        case AO_ITEM_IC:
                            Decimal = 3;
                            break;
                        case AO_ITEM_PA:
                        case AO_ITEM_PB:
                        case AO_ITEM_PC:
                        case AO_ITEM_P:
                        case AO_ITEM_QA:
                        case AO_ITEM_QB:
                        case AO_ITEM_QC:
                        case AO_ITEM_Q:
                        case AO_ITEM_SA:
                        case AO_ITEM_SB:
                        case AO_ITEM_SC:
                        case AO_ITEM_S:
                            Decimal = 0;
                            break;
                        case AO_ITEM_PFA:
                        case AO_ITEM_PFB:
                        case AO_ITEM_PFC:
                        case AO_ITEM_PF:
                            Decimal = 3;
                            break;
                        case AO_ITEM_F:
                            Decimal = 2;
                            break;
                        default:
                            break;
				    }
					Disp_Focus.DispWidth = 4;
					DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
					CharToNumber();
				    break;
				default:
				    break;
            }
            break;
		default:
		    break;
	}
}


void DispMenu_MenuCode(void)    //��ʾ�������
{
	u8 Decimal = 0;
	DispChar(0,CHARMODE_P,CHARMODE_R,CHARMODE_O,CHARMODE_G);
	DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_D,CHARMODE_E);
	Decimal =  0;
	DispValue(2,sg_DispSetValue, Decimal,  Disp_Focus.DispWidth, sg_bSetFlashEnable, Disp_Focus.CurrentFocus, TRUE, TRUE);
	CharToNumber();
}

void DispMenu_MenuCodeErr(void)
{
	DispChar(0,CHARMODE_P,CHARMODE_R,CHARMODE_O,CHARMODE_G);
	DispChar(1,CHARMODE_C,CHARMODE_O,CHARMODE_D,CHARMODE_E);
	if(sg_bSetFlashEnable)
		DispChar(2,CHARMODE_NC,CHARMODE_E,CHARMODE_R,CHARMODE_R);
	else
		DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
}

void DispMenu_MenuSave(void)
{
		DispChar(0,CHARMODE_S,CHARMODE_A,CHARMODE_U,CHARMODE_E);
	    DispChar(1,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
        if( sg_DispSetValue == SaveYes)
		{
            if(sg_bSetFlashEnable)
    			DispChar(2,CHARMODE_NC,CHARMODE_Y,CHARMODE_E,CHARMODE_S);
    		else
    			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
		}
		else if( sg_DispSetValue == SaveNO)
		{
            if(sg_bSetFlashEnable)
    			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_N,CHARMODE_O);
    		else
    			DispChar(2,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC,CHARMODE_NC);
		}
}

const u16 cg_CharToNum[4] = {1000, 100, 10, 1};

/****************************************************************************************
** ��������: CharToNumber
** ��������: ����ʾ���ò˵��е��ַ�����ת��Ϊʮ��������
** ��    ��: void
** �� �� ֵ: void
** ����  ��:
** ��  ����: 2011��11��13��
**---------------------------------------------------------------------------------------
** �� �� ��:
** �ա�  ��:
**--------------------------------------------------------------------------------------
****************************************************************************************/
u16 CharToNumber(void)
{
	u8 i;
	u16 TotalData = 0;

	for (i = 0; i < 4; i++)
	{
		if (sg_CurrentDispChar[i] != NEG_NUM && sg_CurrentDispChar[i] != POS_NUM)
		{
			TotalData += sg_CurrentDispChar[i] * cg_CharToNum[i];
		}
	}
	sg_CurrentDispNumber = TotalData;

	return TotalData;
}


/****************************************************************************************
** ��������: GetSetOldValue
** ��������: ��ʾ���ò˵���Ҫ��ʾ������
** ��    ��: BOOL bUpdata-�Ƿ�Ҫ��˸����
** �� �� ֵ: void
** ����  ��:
** ��  ����: 2011��11��13��
**---------------------------------------------------------------------------------------
** �� �� ��:
** �ա�  ��:
**--------------------------------------------------------------------------------------
****************************************************************************************/
void GetSetOldValue(void)
{
	u8 i = 0;
	for (i = 0; i < 4; i++)
	{
		sg_CurrentDispChar[i] = 0x00;
	}
	Disp_Focus.DispWidth = 4;
	Disp_Focus.CurrentFocus = CURRENTFOCUS_3; //�˳�����¾۵�
	switch(sg_DispSetMenu1Index)
	{
		case MENU1_INDEX_INPT:
			switch(sg_DispSetMenu2_1_Index)
			{
                case MENU2_1_INDEX_NET:
                    sg_DispSetValue = DispCtrlParam.NetMode;
                    break;
				case MENU2_1_INDEX_PT:
					sg_DispSetValue = DispCtrlParam.PTNum;
				    break;
				case MENU2_1_INDEX_CT:
					sg_DispSetValue = DispCtrlParam.CTNum;
				    break;
				default:
				    break;
			}
		    break;
        case MENU1_INDEX_COM1:
			switch(sg_DispSetMenu2_2_Index)
			{
				case MENU2_2_INDEX_ADD:
					sg_DispSetValue = DispCtrlParam.Addr485;
				    break;
				case MENU2_2_INDEX_BAUD:
					sg_DispSetValue = DispCtrlParam.Baud485;
			    	break;
				case MENU2_2_INDEX_DATA:
					sg_DispSetValue = DispCtrlParam.DataFormat;
				    break;
				case MENU2_2_INDEX_COMS:
					sg_DispSetValue = DispCtrlParam.DataProtocol;
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_SYS:
			switch(sg_DispSetMenu2_3_Index)
			{
				case MENU2_3_INDEX_CYC:
					sg_DispSetValue = DispCtrlParam.Cycle;
				    break;
				case MENU2_3_INDEX_LIGH:
					sg_DispSetValue = DispCtrlParam.BlackTime;
				    break;
				case MENU2_3_INDEX_DISP:
					sg_DispSetValue = DispCtrlParam.DefaultDisp;
				    break;
				case MENU2_3_INDEX_ALR:
					sg_DispSetValue = DispCtrlParam.Alarm;
				    break;
				case MENU2_3_INDEX_CODE:
					sg_DispSetValue = DispCtrlParam.Code;
				    break;
				case MENU2_3_INDEX_CLRE:
					sg_DispSetValue = SaveNO;
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_DO1:
			switch(sg_DispSetMenu2_4_Index)
			{
				case MENU2_4_INDEX_MODE:
					sg_DispSetValue = DispCtrlParam.DO1_Mode;
				    break;
				case MENU2_4_INDEX_TIME:
					sg_DispSetValue = DispCtrlParam.DO1_Time;
				    break;
				case MENU2_4_INDEX_ITEM:
					if((g_tParam.CtrlParam.NetMode == N33) && (DispCtrlParam.DO1_Item < DO_ITEM_Uab_H))
				    {
                        sg_DispSetValue = DO_ITEM_Uab_H;
				    }
				    else
				    {
                        sg_DispSetValue = DispCtrlParam.DO1_Item;
				    }
				    break;
				case MENU2_4_INDEX_UAL:
					sg_DispSetValue = DispCtrlParam.DO1_UAL;
				    break;
				case MENU2_4_INDEX_HYS:
					sg_DispSetValue = DispCtrlParam.DO1_HYS;
				    break;
				case MENU2_4_INDEX_DELAY:
					sg_DispSetValue = DispCtrlParam.DO1_Delay;
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_DO2:
			switch(sg_DispSetMenu2_5_Index)
			{
				case MENU2_5_INDEX_MODE:
					sg_DispSetValue = DispCtrlParam.DO2_Mode;
				    break;
				case MENU2_5_INDEX_TIME:
					sg_DispSetValue = DispCtrlParam.DO2_Time;
				    break;
				case MENU2_5_INDEX_ITEM:
					if((g_tParam.CtrlParam.NetMode == N33) && (DispCtrlParam.DO2_Item < DO_ITEM_Uab_H))
				    {
                        sg_DispSetValue = DO_ITEM_Uab_H;
				    }
				    else
				    {
                        sg_DispSetValue = DispCtrlParam.DO2_Item;
				    }
				    break;
				case MENU2_5_INDEX_UAL:
					sg_DispSetValue = DispCtrlParam.DO2_UAL;
				    break;
				case MENU2_5_INDEX_HYS:
					sg_DispSetValue = DispCtrlParam.DO2_HYS;
				    break;
				case MENU2_5_INDEX_DELAY:
					sg_DispSetValue = DispCtrlParam.DO2_Delay;
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_DO3:
			switch(sg_DispSetMenu2_6_Index)
			{
				case MENU2_6_INDEX_MODE:
					sg_DispSetValue = DispCtrlParam.DO3_Mode;
				    break;
				case MENU2_6_INDEX_TIME:
					sg_DispSetValue = DispCtrlParam.DO3_Time;
				    break;
				case MENU2_6_INDEX_ITEM:
					if((g_tParam.CtrlParam.NetMode == N33) && (DispCtrlParam.DO3_Item < DO_ITEM_Uab_H))
				    {
                        sg_DispSetValue = DO_ITEM_Uab_H;
				    }
				    else
				    {
                        sg_DispSetValue = DispCtrlParam.DO3_Item;
				    }
				    break;
				case MENU2_6_INDEX_UAL:
					sg_DispSetValue = DispCtrlParam.DO3_UAL;
				    break;
				case MENU2_6_INDEX_HYS:
					sg_DispSetValue = DispCtrlParam.DO3_HYS;
				    break;
				case MENU2_6_INDEX_DELAY:
					sg_DispSetValue = DispCtrlParam.DO3_Delay;
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_DO4:
			switch(sg_DispSetMenu2_7_Index)
			{
				case MENU2_7_INDEX_MODE:
					sg_DispSetValue = DispCtrlParam.DO4_Mode;
				    break;
				case MENU2_7_INDEX_TIME:
					sg_DispSetValue = DispCtrlParam.DO4_Time;
				    break;
				case MENU2_7_INDEX_ITEM:
				    if((g_tParam.CtrlParam.NetMode == N33) && (DispCtrlParam.DO4_Item < DO_ITEM_Uab_H))
				    {
                        sg_DispSetValue = DO_ITEM_Uab_H;
				    }
				    else
				    {
                        sg_DispSetValue = DispCtrlParam.DO4_Item;
				    }
				    break;
				case MENU2_7_INDEX_UAL:
					sg_DispSetValue = DispCtrlParam.DO4_UAL;
				    break;
				case MENU2_7_INDEX_HYS:
					sg_DispSetValue = DispCtrlParam.DO4_HYS;
				    break;
				case MENU2_7_INDEX_DELAY:
					sg_DispSetValue = DispCtrlParam.DO4_Delay;
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_AO1:
			switch(sg_DispSetMenu2_8_Index)
			{
				case MENU2_8_INDEX_MODE:
					sg_DispSetValue = DispCtrlParam.AO1_Mode;
				    break;
				case MENU2_8_INDEX_ITEM:
				    if((g_tParam.CtrlParam.NetMode == N33) && ( DispCtrlParam.AO1_Item < AO_ITEM_UAB))
				    {
                        sg_DispSetValue = AO_ITEM_UAB;
				    }
				    else
				    {
                        sg_DispSetValue = DispCtrlParam.AO1_Item;
				    }
				    break;
				case MENU2_8_INDEX_DS:
					sg_DispSetValue = DispCtrlParam.AO1_DS;
				    break;
				case MENU2_8_INDEX_FS:
					sg_DispSetValue = DispCtrlParam.AO1_FS;
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_AO2:
			switch(sg_DispSetMenu2_9_Index)
			{
				case MENU2_9_INDEX_MODE:
					sg_DispSetValue = DispCtrlParam.AO2_Mode;
				    break;
				case MENU2_9_INDEX_ITEM:
					if((g_tParam.CtrlParam.NetMode == N33) && ( DispCtrlParam.AO2_Item < AO_ITEM_UAB))
				    {
                        sg_DispSetValue = AO_ITEM_UAB;
				    }
				    else
				    {
                        sg_DispSetValue = DispCtrlParam.AO2_Item;
				    }
				    break;
				case MENU2_9_INDEX_DS:
					sg_DispSetValue = DispCtrlParam.AO2_DS;
				    break;
				case MENU2_9_INDEX_FS:
					sg_DispSetValue = DispCtrlParam.AO2_FS;
				    break;
				default:
				    break;
			}
		    break;
		default:
		    break;
	}
}


/*-----------------------------------------------------------------------------------------------------------------*/
s32 JudgeSetNewValue(BOOL *pUpdataFlag, s32 OldValue, s32 *pNewValue, s32 MinValue, s32 MaxValue)
{
	if (*pNewValue >= MinValue && *pNewValue <= MaxValue)
	{
		if (OldValue != *pNewValue)
		{
		    *pUpdataFlag = TRUE;
			return *pNewValue;
		}
	}
	*pUpdataFlag = FALSE;
	*pNewValue = OldValue;
		return OldValue;
}

/*----------------------------------------------------------------------------------------------------------------*/
BOOL JudgeNewParam(BOOL *pUpdataFlag, s32 *pNewValue,s32 MinValue, s32 MaxValue)
{
    if (*pNewValue >= MinValue && *pNewValue <= MaxValue)
	{
		*pUpdataFlag = TRUE;
	}
	else
	{
        *pUpdataFlag = FALSE;
	}
	return *pUpdataFlag;
}
/*-----------------------------------------------------------------------------------------------------------------*/
/****************************************************************************************
** ��������: GetSetNewValue
** ��������: �������úõĲ˵�������,ֻ�����ݲ�һ��ʱ�Ÿ��±��浽FLASH��
** ��    ��: void
** �� �� ֵ: void
** ����  ��:
** ��  ����: 2011��11��11��
**---------------------------------------------------------------------------------------
** �� �� ��:
** �ա�  ��:
**--------------------------------------------------------------------------------------
****************************************************************************************/

void GetSetNewValue(void)
{
    BOOL UpData = FALSE;
    switch(sg_DispSetMenu1Index)
	{
		case MENU1_INDEX_INPT:
			switch(sg_DispSetMenu2_1_Index)
			{
                case MENU2_1_INDEX_NET:
                    DispCtrlParam.NetMode =
                        (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.NetMode,(s32*)&sg_DispSetValue,MIN_NetMode,MAX_NetMode);
                    break;
				case MENU2_1_INDEX_PT:
					DispCtrlParam.PTNum =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.PTNum,(s32*)&sg_DispSetValue,MIN_PT,MAX_PT);
				    break;
				case MENU2_1_INDEX_CT:
					DispCtrlParam.CTNum =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.CTNum,(s32*)&sg_DispSetValue,MIN_CT,MAX_CT);
				    break;
				default:
				    break;
			}
		    break;
        case MENU1_INDEX_COM1:
			switch(sg_DispSetMenu2_2_Index)
			{
				case MENU2_2_INDEX_ADD:
					DispCtrlParam.Addr485 =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.Addr485,(s32*)&sg_DispSetValue,MIN_Addr,MAX_Addr);
				    break;
				case MENU2_2_INDEX_BAUD:
                    DispCtrlParam.Baud485=
                        (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.Baud485,(s32*)&sg_DispSetValue,MIN_Baud,MAX_Baud);
			    	break;
				case MENU2_2_INDEX_DATA:
					DispCtrlParam.DataFormat=
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DataFormat,(s32*)&sg_DispSetValue,MIN_DataFormat,MAX_DataFormat);
                    break;
                case MENU2_2_INDEX_COMS:
					DispCtrlParam.DataProtocol=
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DataProtocol,(s32*)&sg_DispSetValue,MIN_DataProt,MAX_DataProt);
                    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_SYS:
			switch(sg_DispSetMenu2_3_Index)
			{
				case MENU2_3_INDEX_CYC:
					DispCtrlParam.Cycle =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.Cycle,(s32*)&sg_DispSetValue,MIN_Cycle,MAX_Cycle);
				    break;
				case MENU2_3_INDEX_LIGH:
					DispCtrlParam.BlackTime =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.BlackTime,(s32*)&sg_DispSetValue,MIN_BlackTime,MAX_BlackTime);
				    break;
				case MENU2_3_INDEX_DISP:
					DispCtrlParam.DefaultDisp=
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DefaultDisp,(s32*)&sg_DispSetValue,MIN_Disp,MAX_Disp);
				    break;
				case MENU2_3_INDEX_ALR:
					DispCtrlParam.Alarm =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.Alarm,(s32*)&sg_DispSetValue,MIN_Alarm,MAX_Alarm);
				    break;
				case MENU2_3_INDEX_CODE:
					DispCtrlParam.Code =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.Code,(s32*)&sg_DispSetValue,MIN_Code,MAX_Code);
				    break;
				default:
				    break;
			}
		    break;

		case MENU1_INDEX_DO1:
			switch(sg_DispSetMenu2_4_Index)
			{
				case MENU2_4_INDEX_MODE:
					DispCtrlParam.DO1_Mode =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO1_Mode,(s32*)&sg_DispSetValue,MIN_DO_Mode,MAX_DO_Mode);
				    break;
				case MENU2_4_INDEX_TIME:
					DispCtrlParam.DO1_Time =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO1_Time,(s32*)&sg_DispSetValue,MIN_DO_Time,MAX_DO_Time);
				    break;
				case MENU2_4_INDEX_ITEM:
					DispCtrlParam.DO1_Item =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO1_Item,(s32*)&sg_DispSetValue,MIN_DO_Item,MAX_DO_Item);
				    break;
				case MENU2_4_INDEX_UAL:
					DispCtrlParam.DO1_UAL =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO1_UAL,(s32*)&sg_DispSetValue,MIN_DO_Ual,MAX_DO_Ual);
				    break;
				case MENU2_4_INDEX_HYS:
					DispCtrlParam.DO1_HYS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO1_HYS,(s32*)&sg_DispSetValue,MIN_DO_Hys,MAX_DO_Hys);
				    break;
				case MENU2_4_INDEX_DELAY:
					DispCtrlParam.DO1_Delay=
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO1_Delay,(s32*)&sg_DispSetValue,MIN_DO_Dely,MAX_DO_Dely);
				    break;
				default:
				    break;
			}
		    break;

		case MENU1_INDEX_DO2:
			switch(sg_DispSetMenu2_5_Index)
			{
				case MENU2_5_INDEX_MODE:
					DispCtrlParam.DO2_Mode =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO2_Mode,(s32*)&sg_DispSetValue,MIN_DO_Mode,MAX_DO_Mode);
				    break;
				case MENU2_5_INDEX_TIME:
					DispCtrlParam.DO2_Time =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO2_Time,(s32*)&sg_DispSetValue,MIN_DO_Time,MAX_DO_Time);
				    break;
				case MENU2_5_INDEX_ITEM:
					DispCtrlParam.DO2_Item =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO2_Item,(s32*)&sg_DispSetValue,MIN_DO_Item,MAX_DO_Item);
				    break;
				case MENU2_5_INDEX_UAL:
					DispCtrlParam.DO2_UAL =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO2_UAL,(s32*)&sg_DispSetValue,MIN_DO_Ual,MAX_DO_Ual);
				    break;
				case MENU2_5_INDEX_HYS:
					DispCtrlParam.DO2_HYS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO2_HYS,(s32*)&sg_DispSetValue,MIN_DO_Hys,MAX_DO_Hys);
				    break;
				case MENU2_5_INDEX_DELAY:
					DispCtrlParam.DO2_Delay=
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO2_Delay,(s32*)&sg_DispSetValue,MIN_DO_Dely,MAX_DO_Dely);
				    break;
				default:
				    break;
			}
		    break;

		case MENU1_INDEX_DO3:
			switch(sg_DispSetMenu2_6_Index)
			{
				case MENU2_6_INDEX_MODE:
					DispCtrlParam.DO3_Mode =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO3_Mode,(s32*)&sg_DispSetValue,MIN_DO_Mode,MAX_DO_Mode);
				    break;
				case MENU2_6_INDEX_TIME:
					DispCtrlParam.DO3_Time =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO3_Time,(s32*)&sg_DispSetValue,MIN_DO_Time,MAX_DO_Time);
				    break;
				case MENU2_6_INDEX_ITEM:
					DispCtrlParam.DO3_Item =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO3_Item,(s32*)&sg_DispSetValue,MIN_DO_Item,MAX_DO_Item);
				    break;
				case MENU2_6_INDEX_UAL:
					DispCtrlParam.DO3_UAL =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO3_UAL,(s32*)&sg_DispSetValue,MIN_DO_Ual,MAX_DO_Ual);
				    break;
				case MENU2_6_INDEX_HYS:
					DispCtrlParam.DO3_HYS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO3_HYS,(s32*)&sg_DispSetValue,MIN_DO_Hys,MAX_DO_Hys);
				    break;
				case MENU2_6_INDEX_DELAY:
					DispCtrlParam.DO3_Delay=
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO3_Delay,(s32*)&sg_DispSetValue,MIN_DO_Dely,MAX_DO_Dely);
				    break;
				default:
				    break;
			}
		    break;

		case MENU1_INDEX_DO4:
			switch(sg_DispSetMenu2_7_Index)
			{
				case MENU2_7_INDEX_MODE:
					DispCtrlParam.DO4_Mode =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO4_Mode,(s32*)&sg_DispSetValue,MIN_DO_Mode,MAX_DO_Mode);
				    break;
				case MENU2_7_INDEX_TIME:
					DispCtrlParam.DO4_Time =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO4_Time,(s32*)&sg_DispSetValue,MIN_DO_Time,MAX_DO_Time);
				    break;
				case MENU2_7_INDEX_ITEM:
					DispCtrlParam.DO4_Item =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO4_Item,(s32*)&sg_DispSetValue,MIN_DO_Item,MAX_DO_Item);
				    break;
				case MENU2_7_INDEX_UAL:
					DispCtrlParam.DO4_UAL =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO4_UAL,(s32*)&sg_DispSetValue,MIN_DO_Ual,MAX_DO_Ual);
				    break;
				case MENU2_7_INDEX_HYS:
					DispCtrlParam.DO4_HYS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO4_HYS,(s32*)&sg_DispSetValue,MIN_DO_Hys,MAX_DO_Hys);
				    break;
				case MENU2_7_INDEX_DELAY:
					DispCtrlParam.DO4_Delay=
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.DO4_Delay,(s32*)&sg_DispSetValue,MIN_DO_Dely,MAX_DO_Dely);
				    break;
				default:
				    break;
			}
		    break;

        case MENU1_INDEX_AO1:
			switch(sg_DispSetMenu2_8_Index)
			{
				case MENU2_8_INDEX_MODE:
					DispCtrlParam.AO1_Mode =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO1_Mode,(s32*)&sg_DispSetValue,MIN_AO_Mode,MAX_AO_Mode);
				    break;
				case MENU2_8_INDEX_ITEM:
					DispCtrlParam.AO1_Item =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO1_Item,(s32*)&sg_DispSetValue,MIN_AO_Item,MAX_AO_Item);
				    break;
				case MENU2_8_INDEX_DS:
					DispCtrlParam.AO1_DS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO1_DS,(s32*)&sg_DispSetValue,MIN_AO_DS,MAX_AO_DS);
				    break;
				case MENU2_8_INDEX_FS:
					DispCtrlParam.AO1_FS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO1_FS,(s32*)&sg_DispSetValue,MIN_AO_FS,MAX_AO_FS);
				    break;
				default:
				    break;
			}
		    break;

		case MENU1_INDEX_AO2:
			switch(sg_DispSetMenu2_9_Index)
			{
				case MENU2_9_INDEX_MODE:
					DispCtrlParam.AO2_Mode =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO2_Mode,(s32*)&sg_DispSetValue,MIN_AO_Mode,MAX_AO_Mode);
				    break;
				case MENU2_9_INDEX_ITEM:
					DispCtrlParam.AO2_Item =
					    (u8)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO2_Item,(s32*)&sg_DispSetValue,MIN_AO_Item,MAX_AO_Item);
				    break;
				case MENU2_9_INDEX_DS:
					DispCtrlParam.AO2_DS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO2_DS,(s32*)&sg_DispSetValue,MIN_AO_DS,MAX_AO_DS);
				    break;
				case MENU2_9_INDEX_FS:
					DispCtrlParam.AO2_FS =
					    (u16)JudgeSetNewValue(&UpData,(s32)DispCtrlParam.AO2_FS,(s32*)&sg_DispSetValue,MIN_AO_FS,MAX_AO_FS);
				    break;
				default:
				    break;
			}
		    break;
		case MENU1_INDEX_VER: //ֻ��
		    break;
		default:
		    break;
	}
	if(UpData)   //�жϿ��Ʋ����Ƿ񱣴浽flash
	{
        DispValueUpDataFlag = TRUE;
	}
	else if(DispValueUpDataFlag != TRUE)
	{
        DispValueUpDataFlag = FALSE;
	}
}

void UpdataSetValue(UPDATA_DIR Updata_Dir)  //������ֵ
{
	u16 tmpData[4] = {0};
	u8 bit = 0;

	if (Disp_Focus.CurrentFocus == CURRENTFOCUS_NONE)
	{
		return;
	}
	else if (Disp_Focus.CurrentFocus == CURRENTFOCUS_0)
	{
		bit = 0;
	}
	else if (Disp_Focus.CurrentFocus == CURRENTFOCUS_1)
	{
		bit = 1;
	}
	else if (Disp_Focus.CurrentFocus == CURRENTFOCUS_2)
	{
		bit = 2;
	}
	else if (Disp_Focus.CurrentFocus == CURRENTFOCUS_3)
	{
		bit = 3;
	}

	tmpData[0] = sg_CurrentDispNumber/1000;
	tmpData[1] = sg_CurrentDispNumber%1000/100;
	tmpData[2] = sg_CurrentDispNumber%100/10;
	tmpData[3] = sg_CurrentDispNumber%10;

	if (sg_CurrentDispChar[bit] == NEG_NUM)
	{
		sg_CurrentDispChar[bit] = POS_NUM;
	}
	else if (sg_CurrentDispChar[bit] == POS_NUM)
	{
		sg_CurrentDispChar[bit] = NEG_NUM;
	}
	else
	{
    	if (Updata_Dir == UPDATA_ADD)
    	{
    		tmpData[bit] += 1;
    		if (tmpData[bit] == 10)
    		{
    			tmpData[bit] = 0;
    		}
    	}
    	else
    	{
    		tmpData[bit] -= 1;
    		if (tmpData[bit] > 9)
    		{
    			tmpData[bit] = 9;
    		}
    	}
	}
	sg_DispSetValue = (tmpData[0]*1000 + tmpData[1]*100 + tmpData[2]*10 + tmpData[3]);
	//��-�ž���Ϊ�Ǹ���
	/*if (sg_CurrentDispChar[0] == NEG_NUM || sg_CurrentDispChar[1] == NEG_NUM
	|| sg_CurrentDispChar[2] == NEG_NUM || sg_CurrentDispChar[3] == NEG_NUM)
	{
		sg_DispSetValue = -sg_DispSetValue;
	}*/
}


void UpdataOrSetValue(SELECT_CATE Cate,UPDATA_DIR Updata_Dir)//������ֵ or
{
    switch(Cate)
    {
        case Select_Net:
            if(sg_DispSetValue == N34)
            {
                sg_DispSetValue = N33;
            }
            else
            {
                sg_DispSetValue = N34;
            }
            break;
        case Select_Baud:
            if(Updata_Dir == UPDATA_ADD)
            {
                sg_DispSetValue++;
                if(sg_DispSetValue > Baud192)
                {
                    sg_DispSetValue = Baud12;
                }
            }
            else
            {
                sg_DispSetValue--;
                if(sg_DispSetValue < Baud12)
                {
                    sg_DispSetValue = Baud192;
                }
            }
            break;
        case Select_Data:
            if(Updata_Dir == UPDATA_ADD)
            {
                sg_DispSetValue++;
                if(sg_DispSetValue > n82)
                {
                    sg_DispSetValue = n81;
                }
            }
            else
            {
                sg_DispSetValue--;
                if(sg_DispSetValue < n81)
                {
                    sg_DispSetValue = n82;
                }
            }
            break;
        case Select_Coms:
            if(sg_DispSetValue == rtu485)
            {
                sg_DispSetValue = calib;
            }
            else
            {
                sg_DispSetValue = rtu485;
            }
            break;
        case Select_Save:
            if(sg_DispSetValue == SaveYes)
            {
                sg_DispSetValue = SaveNO;
            }
            else
            {
                sg_DispSetValue = SaveYes;
            }
            break;
        case Select_Disp_Default:
#ifdef _LEDHarm_
            if(Updata_Dir == UPDATA_ADD)
            {
                sg_DispSetValue++;
                if(sg_DispSetValue > DISP_UINT_THD)
                {
                    sg_DispSetValue = DISP_UINT_U;
                }
            }
            else
            {
                sg_DispSetValue--;
                if(sg_DispSetValue < DISP_UINT_U)
                {
                    sg_DispSetValue = DISP_UINT_THD;
                }
            }
#else
            if(Updata_Dir == UPDATA_ADD)
            {
                sg_DispSetValue++;
                if(sg_DispSetValue > DISP_UINT_EP)
                {
                    sg_DispSetValue = DISP_UINT_U;
                }
            }
            else
            {
                sg_DispSetValue--;
                if(sg_DispSetValue < DISP_UINT_U)
                {
                    sg_DispSetValue = DISP_UINT_EP;
                }
            }
#endif
            break;
        case Select_Do_Mode:
            if(Updata_Dir == UPDATA_ADD)
            {
                sg_DispSetValue++;
                if(sg_DispSetValue > DO_MODE_REM)
                {
                    sg_DispSetValue = DO_MODE_OFF;
                }
            }
            else
            {
                sg_DispSetValue--;
                if(sg_DispSetValue < DO_MODE_OFF)
                {
                    sg_DispSetValue = DO_MODE_REM;
                }
            }
            break;
        case Select_Do_item:
            if(g_tParam.CtrlParam.NetMode == N33)
            {
                if(Updata_Dir == UPDATA_ADD)
                {
                    sg_DispSetValue++;
                    if(sg_DispSetValue > DO_ITEM_DI4_L)
                    {
                        sg_DispSetValue = DO_ITEM_Uab_H;
                    }
                }
                else
                {
                    sg_DispSetValue--;
                    if(sg_DispSetValue < DO_ITEM_Uab_H)
                    {
                        sg_DispSetValue = DO_ITEM_DI4_L;
                    }
                }
            }
            else
            {
                if(Updata_Dir == UPDATA_ADD)
                {
                    sg_DispSetValue++;
                    if(sg_DispSetValue > DO_ITEM_DI4_L)
                    {
                        sg_DispSetValue = DO_ITEM_Ua_H;
                    }
                }
                else
                {
                    sg_DispSetValue--;
                    if(sg_DispSetValue < DO_ITEM_Ua_H)
                    {
                        sg_DispSetValue = DO_ITEM_DI4_L;
                    }
                }
            }
            break;
        case Select_Ao_Mode:
            if(Updata_Dir == UPDATA_ADD)
            {
                sg_DispSetValue++;
                if(sg_DispSetValue > AO_MODE_1220)
                {
                    sg_DispSetValue = AO_MODE_OFF;
                }
            }
            else
            {
                sg_DispSetValue--;
                if(sg_DispSetValue < AO_MODE_OFF)
                {
                    sg_DispSetValue = AO_MODE_1220;
                }
            }
            break;
        case Select_Ao_item:
            if(g_tParam.CtrlParam.NetMode == N33)
            {
                if(Updata_Dir == UPDATA_ADD)
                {
                    sg_DispSetValue++;
                    if(sg_DispSetValue > AO_ITEM_F)
                    {
                        sg_DispSetValue = AO_ITEM_UAB;
                    }
                }
                else
                {
                    sg_DispSetValue--;
                    if(sg_DispSetValue < AO_ITEM_UAB)
                    {
                        sg_DispSetValue = AO_ITEM_F;
                    }
                }
            }
            else
            {
                if(Updata_Dir == UPDATA_ADD)
                {
                    sg_DispSetValue++;
                    if(sg_DispSetValue > AO_ITEM_F)
                    {
                        sg_DispSetValue = AO_ITEM_UA;
                    }
                }
                else
                {
                    sg_DispSetValue--;
                    if(sg_DispSetValue < AO_ITEM_UA)
                    {
                        sg_DispSetValue = AO_ITEM_F;
                    }
                }
            }

            break;
        case Select_Light:
            if(Updata_Dir == UPDATA_ADD)
            {
                sg_DispSetValue++;
                if(sg_DispSetValue > BrightLevel_3)
                {
                    sg_DispSetValue = BrightLevel_1;
                }
                LEDLEVEL= sg_DispSetValue;
            }
            else
            {
                sg_DispSetValue--;
                if(sg_DispSetValue == BrightLevel_Off)
                {
                    sg_DispSetValue = BrightLevel_3;
                }
                LEDLEVEL = sg_DispSetValue;
            }
            break;
        default:
            break;
    }
}

#endif // #ifdef _GUILED_

//===========================================================================
//  End.
//===========================================================================


