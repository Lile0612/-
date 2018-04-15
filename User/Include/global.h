#ifndef __GLOBAL_H__
#define __GLOBAL_H__

// �汾�궨��
// 2016.04.19
#define VER_SOFT    1001
#define VER_HARD    1001


#define LOSTPOWER_ENABLE    1	// ����ʹ�� ��������ʹ�øú�
////////////////////////////////////////////////////////////

#define SYSTICK	1	// ϵͳʱ��

#define TIMER_DELAY_POWERON	(60000/SYSTICK)	// ��ʱ60s �ϵ�ʱ��


////////////////////////////////////////////////////////////

#define MS_FLAG    1   // 0: 1:������λ����ѯ����

#define MAX_QUERY_NUM     63         // ��ѯ����ַ


#define CAPTYPE_MIN  CAPTYPE_DOUBLE
#define CAPTYPE_MAX  CAPTYPE_SINGLE
/*------------------------------------------------------------------------
 * ö������ : enDEVFLAG
 * ��    �� : ����������
 * ʱ    �� : 2012��12��4��
------------------------------------------------------------------------*/

#define DEV_TYPE        1	// 0: ������(���DEV_TYPEFLAG=6,7) 1:������(DEV_TYPEFLAG=0,1,2,3,4,5)

#ifdef _DEV_STAR		// Preprocessor Symbols
	#define DEV_FLAG    1   // 0:���� 1:����
#else
	#define DEV_FLAG    0   // 0:���� 1:����
#endif

#define DEV_FLASH        0 // 0:��FLASH  1:��FLASH
#define DEV_INDICATOR    1 // 0: ��״ָ̬ʾ�� 1:����(�������ɵ�ַ)

#ifdef _ZERO_TEST
#define ZERO_TEST    1   // 0:������ʱ 1:1s��Ͷ��
#else
#define ZERO_TEST    0   //
#endif

#ifdef _DEV_PHASE_CMP		// ��䲹��
#define DEV_PHASE_CMP    1
#else
#define DEV_PHASE_CMP    0
#endif

#ifdef _FACTORY_TEST
#define FACTORY_TEST    1   // 0:���� 1:�����ϻ���� ����䲹��Ϊģ��
#else
#define FACTORY_TEST    0   //
#endif


//=======================���Ա���==========================//
///////////////////////////////////////////////////////////////

#ifdef _FUNCTION_CURRENT
#define FUNCTION_CURRENT  1    //������
#else
#define FUNCTION_CURRENT  0    //
#endif

#ifdef _FUNCTION_VOLTAGE
#define FUNCTION_VOLTAGE  1    //��ѹ��
#else
#define FUNCTION_VOLTAGE  0    //
#endif

#ifdef _FUNCTION_POWER
#define FUNCTION_POWER    1    //���ʱ�
#else
#define FUNCTION_POWER    0    //
#endif

#ifdef _FUNCTION_MULTI_UI      //��ѹ������
#define FUNCTION_MULTI_UI 1
#else
#define FUNCTION_MULTI_UI 0
#endif

#ifdef _FUNCTION_MULTI
#define FUNCTION_MULTI    1    //�๦�ܱ�
#else
#define FUNCTION_MULTI    0    //
#endif

#ifdef _FUNCTION_MULTI_F
#define FUNCTION_MULTI_F    1    //�๦�ܱ�
#else
#define FUNCTION_MULTI_F    0    //
#endif

#ifdef _GUI_LCD_
#define GUI_LCD    1    //�๦�ܱ�
#else
#define GUI_LCD    0    //
#endif


// ��ʾ������ֵ���ڴ�ֵ֮��ı���
#define RATIO_SET_U 10 //
#define RATIO_SET_I 1 // 100->1000
#define RATIO_SET_HARM 10 // 1->10
// ���������ͱ����ı���
#define RATIO_PROVAL_U	100 // ��ѹ������ֵ����
#define RATIO_PROVAL_I	1 // ����������ֵ����
#define RATIO_PROVAL_HARM	10 // г��������ֵ����
//-��Χ �������ò�����С����
#ifdef CALC_60HZ
    #if (DEV_FLAG == 1)
        #define MIN_UH1    288
        #define MAX_UH1    336
        #define MIN_UH2    264
        #define MAX_UH2    312
        #define MIN_UL    204
        #define MAX_UL    264
    #else
        #define MIN_UH1    480
        #define MAX_UH1    576
        #define MIN_UH2    456
        #define MAX_UH2    552
        #define MIN_UL    336
        #define MAX_UL    432
    #endif
#else
    #if (DEV_FLAG == 1)
        #define MIN_UH1    240
        #define MAX_UH1    280
        #define MIN_UH2    220
        #define MAX_UH2    260
        #define MIN_UL    170
        #define MAX_UL    220
    #else
        #define MIN_UH1    400
        #define MAX_UH1    480
        #define MIN_UH2    380
        #define MAX_UH2    460
        #define MIN_UL    280
        #define MAX_UL    360
    #endif
#endif
#define MIN_HARM    2 // 2%
#define MAX_HARM    60 // 60%
#define MIN_IL    50 // mA
#define MAX_IL    900 // mA
#define MIN_TP    20
#define MAX_TP    80
#define MIN_IH    90 // 100%
#define MAX_IH    140

#define MAX_CT_RATIO 	5000	  // CT�����
#define MAX_PF_HIGH 	-80		  // ���������������ֵ
#define MIN_PF_HIGH 	90		  // ��������������Сֵ
#define MAX_PF_LOW 	96		  // ���������������ֵ
#define MIN_PF_LOW 	80		  // ��������������Сֵ
#define MAX_YS 		250		  // ��ʱ���ֵ
#define MAX_JG 		250		  // ��ʱ���ֵ
#if (ZERO_TEST == 1)
    #define MIN_YS 		0		  // ��ʱ��Сֵ
    #define MIN_JG 		0		  // ��ʱ��Сֵ
#else
    #define MIN_YS 		5		  // ��ʱ��Сֵ
    #define MIN_JG 		5		  // ��ʱ��Сֵ
#endif
#define MAX_CAP 		50		  // �������������ֵ
#define MIN_CAP 		1		  // ������������Сֵ
//-Ĭ��ֵ
#define DEVCAP_RATED_U    450 // ���������ѹ
#define DEVCAP_RATED_PHASE_U    259 // ���������ѹ 450/sqrt(3)
#define DEFVAL_RATED_I    5	// �����
#ifdef CALC_60HZ
    #if (DEV_TYPE == 1)
    	#if (DEV_FLAG == 1)
    	    #define DEFVAL_UH1    (2600*1.2)
    	    #define DEFVAL_UH2    (2450*1.2)
    	    #define DEFVAL_UL1    (1730*1.2)
    	    #define DEFVAL_UL2    (1960*1.2)

    	    #define DEFVAL_RATED_U    (220*1.2)

    	#else
    	    #define DEFVAL_UH1    (4500*1.2)
    	    #define DEFVAL_UH2    (4250*1.2)
    	    #define DEFVAL_UL1    (3200*1.2)
    	    #define DEFVAL_UL2    (3500*1.2)

    	    #define DEFVAL_RATED_U    (380*1.2) // ���ѹ

    	#endif
    #else
    	#if (DEV_FLAG == 1)
    	    #define DEFVAL_UH1    (2600*1.2)
    	    #define DEFVAL_UH2    (2450*1.2)
    	    #define DEFVAL_UL1    (1730*1.2)
    	    #define DEFVAL_UL2    (1960*1.2)

    	    #define DEFVAL_RATED_U    (220*1.2)

    	#else
    	    #define DEFVAL_UH1    (4500*1.2)
    	    #define DEFVAL_UH2    (4250*1.2)
    	    #define DEFVAL_UL1    (3000*1.2)
    	    #define DEFVAL_UL2    (3400*1.2)

    	    #define DEFVAL_RATED_U    (380*1.2)

    	#endif
    #endif
#else
    #if (DEV_TYPE == 1)
    	#if (DEV_FLAG == 1)
    	    #define DEFVAL_UH1    2600
    	    #define DEFVAL_UH2    2450
    	    #define DEFVAL_UL1    1730
    	    #define DEFVAL_UL2    1960

    	    #define DEFVAL_RATED_U    220

    	#else
    	    #define DEFVAL_UH1    4500
    	    #define DEFVAL_UH2    4250
    	    #define DEFVAL_UL1    3200
    	    #define DEFVAL_UL2    3500

    	    #define DEFVAL_RATED_U    380 // ���ѹ

    	#endif
    #else
    	#if (DEV_FLAG == 1)
    	    #define DEFVAL_UH1    2600
    	    #define DEFVAL_UH2    2450
    	    #define DEFVAL_UL1    1730
    	    #define DEFVAL_UL2    1960

    	    #define DEFVAL_RATED_U    220

    	#else
    	    #define DEFVAL_UH1    4500
    	    #define DEFVAL_UH2    4250
    	    #define DEFVAL_UL1    3000
    	    #define DEFVAL_UL2    3400

    	    #define DEFVAL_RATED_U    380

    	#endif
    #endif
#endif

#define DEFVAL_PF  1       // �����������Ʒ�ʽ CT���Ϊ1
#define DEFVAL_IL    100	// 100mA
#define DEFVAL_IL_NODISP    50	// 50mAʱ����ʾ����
#define DEFVAL_IH    130 // 130%
#define DEFVAL_HARM    50 // 10%������
#define DEFVAL_YS    15	// 15s
#define DEFVAL_JG    30	// 30s
#define DEFVAL_PF_LOW    95	// 0.95
#define DEFVAL_PF_HIGH    99 // 0.99
#define DEFVAL_PF_HIGH_NEG    -95 // -0.95
#define DEFVAL_TEMP    55	// 55��
#define DEFVAL_CAP    20	// 20kvar


#endif //__GLOBAL_H__


