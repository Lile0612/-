
/* Includes--------------------------------------------------------------*/
#include "Include.h"

#define SCL_1         PORT_EE_SCL->BSRR = PIN_EE_SCL
#define SCL_0         PORT_EE_SCL->BRR  = PIN_EE_SCL

#define SDA_1         PORT_EE_SDA->BSRR = PIN_EE_SDA
#define SDA_0         PORT_EE_SDA->BRR  = PIN_EE_SDA

#define SCL_read      PORT_EE_SDA->IDR & PIN_EE_SDA
#define SDA_read      PORT_EE_SDA->IDR & PIN_EE_SDA

void MyI2C_GPIO_OUT_Config(void);
void MyI2C_GPIO_IN_Config(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
u8   MyI2C_SendByte(u8 ByteData);
u8   MyI2C_ReceiveByte(u8 last_char);

//for 72mhz clk means t=12=>1us
void  delay_us(long t)
{
    long i;

    for(i=0;i<t;i++);
}

//����SDA(PB11)�������
void MyI2C_GPIO_Out_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   =  PIN_EE_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(PORT_EE_SDA, &GPIO_InitStructure);
}

//����SDA(PB11)��������
void  MyI2C_GPIO_IN_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   =  PIN_EE_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(PORT_EE_SDA, &GPIO_InitStructure);
}

//ģ����ʼ�ź�
void MyI2C_Start(void)
{
  MyI2C_GPIO_Out_Config();
  SDA_1;
  SCL_1;
  delay_us(50);
  SDA_0;
  delay_us(50);
  SCL_0;
}

//ģ��ֹͣ�ź�
void MyI2C_Stop(void)
{
  MyI2C_GPIO_Out_Config();
  SDA_0;                                       //I2CStop����������SCL�ǵ͵�ƽ�������
  SCL_1;
  delay_us(50);
  SDA_1;
}

//I2C�����ֽ�
u8 MyI2C_SendByte(u8 ByteData)              //I2C�Ļ������ͷ�ʽ���ֽڷ���
{
  u8 ack;
  u8 i;
  MyI2C_GPIO_Out_Config();
  for (i = 0;  i < 8;  i++)                   //������ͨ��SCL����8��ʱ�����彫Ҫ���͵�
  {                                           //����ͨ��SDA����
    SCL_0;
    delay_us(50);
    if (ByteData&0x80)
      SDA_1;
    else
      SDA_0;
    delay_us(30);
    ByteData <<= 1;                           //���ݽ���ʱ��200us
    SCL_1;
    delay_us(50);                            //���ݱ���ʱ��û��Ҫ��
  }

  SCL_0;                                      //�ڵ�9��ʱ��ʱ��ȡ�Ӽ���ATC1024�����͵�
                                              //ackӦ���źţ���ʱSDAӦΪ����״̬��SD//Ϊ����״̬ʱ��SDA�Ǹߵ�ƽ
  delay_us(50);

  MyI2C_GPIO_IN_Config();                       //ע��������SDAΪ����ʱ��һ��Ҫ��ʹSCL

  SCL_1;                                      //�ǵ͵�ƽ��ǧ����ʹSCLΪ�ߵ�ƽ����Ϊ��
  delay_us(50);                              //SCL�Ǹߵ�ƽ������£��п��ܳ���SDA�ӵ�

  ack = SDA_read ;                            //���ߵ����䣨I2CStop״��������ʧ�ܣ�
  SCL_0;

  return (ack);                               //����ack�źţ��͵�ƽ��ʾ��Ӧ�𣬸���û��
}


//I2C�����ֽ�
u8 MyI2C_ReceiveByte(u8 last_char)
{
  u8 data=0, i;
  MyI2C_GPIO_IN_Config();                       //������ͨ��8��ʱ���źţ����մӼ�����������
  for (i = 0;  i < 8;  i++)
  {
    SCL_0;
    delay_us(50);
    SCL_1;
    delay_us(50);
    data <<=1;
    if (SDA_read ) data++;
  }
  SCL_0;
  delay_us(50);

  MyI2C_GPIO_Out_Config();
  if (last_char)                              //�������������һ���ֽ�ʱ���������ڵ�9������
    SDA_1;                                    //���Ӽ�һ���ߵ�ƽ(NACK)�������һ���͵�ƽ(ACK)
  else                                       //��ʾ��������
    SDA_0;

  delay_us(30);
  SCL_1;
  delay_us(50);
  SCL_0;
  return data;
}
///////////////////////////////�ϰ벿��Ϊ����////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// ����Ϊ�����д����

/* Private macro -------------------------------------------------------------*/
#define FRAM_SIZE 2048
#define FRAM_SECTOR_SIZE 32
#define FRAM_R 1
#define FRAM_W 0
#define FRAM_STARTADDR      (0x00000000)   // ��30k
#define FRAM_DATA_SIZE	              32    // ����������
// Addr:11λ��ַ
#define FRAM_MSBADDRESS(Addr, RW) (0xA0 | ((Addr & 0x0700) >> 7) | RW)
#define FRAM_LSBADDRESS(Addr) (Addr & 0xFF)


u16 FramData_Crc(u8 *pData)
{
	u16 Crc = 0;
	u16 Counter = 0;
	for (Counter = 0; Counter < FRAM_DATA_SIZE-2; Counter++)
	{
		Crc += *(pData+Counter);
	}
    Crc = Crc & 0xff;
	return Crc;
}
/**
  * @brief  д����
  * @param  -uint16_t phyAddr:�����ַ
  			-uint8_t *pWriteData: Ҫд������ݻ���
  			-uint16_t Length:���ݳ���
  * @retval : IIC_ERR_NO_ACK-û��Ӧ��
  				IIC_ERR_NONE-��ȷ
  */
u8 FRAM_I2C_WriteData(u16 phyAddr, u8 *pWriteData, u16 Length)
{
	u8 Addr;
	u16 NumByteToWrite = Length;

    MyI2C_Start();

	// ����������ַ ��3λ��ַ
	Addr = FRAM_MSBADDRESS(phyAddr, FRAM_W);
    if(MyI2C_SendByte(Addr))//доƬ��ַ
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }

	// ���͵�8λ��ַ
	Addr = FRAM_LSBADDRESS(phyAddr);
    if(MyI2C_SendByte(Addr))//доƬ��ַ
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }

	while(NumByteToWrite--)
	{
		if(MyI2C_SendByte(*pWriteData))
			return IIC_ERR_NO_ACK;

		pWriteData++;
	}

    MyI2C_Stop();

    return IIC_ERR_NONE;
}

/**
  * @brief  ������
  * @param  -uint16_t phyAddr:�����ַ
  			-uint8_t *pWriteData: Ҫ��ȡ�����ݻ���
  			-uint16_t Length:���ݳ���
  * @retval : IIC_ERR_NO_ACK-û��Ӧ��
  				IIC_ERR_NONE-��ȷ
  */
u8 FRAM_I2C_ReadData(u16 phyAddr, u8 *pReadData, u16 Length)
{
	u8 Addr;
	u16 NumByteToRead = Length;
    u8 i;
    MyI2C_Start();

	// ����������ַ ��3λ��ַ
	Addr = FRAM_MSBADDRESS(phyAddr, FRAM_W);
    if(MyI2C_SendByte(Addr))//доƬ��ַ
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }

	// ���͵�8λ��ַ
	Addr = FRAM_LSBADDRESS(phyAddr);
    if(MyI2C_SendByte(Addr))//доƬ��ַ
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }

    MyI2C_Start();

	// ����������ַ ��3λ��ַ
	Addr = FRAM_MSBADDRESS(phyAddr, FRAM_R);
    if(MyI2C_SendByte(Addr))//доƬ��ַ
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }
	for (i = 0;  i < NumByteToRead - 1 ;  i++)
      *pReadData++ = MyI2C_ReceiveByte(0);
    *pReadData++ = MyI2C_ReceiveByte(1);
    MyI2C_Stop();
    return IIC_ERR_NONE;
}
void FRAM_WriteData(void)
{
	WRITE_UNPROTECT;
	u8 FramWriteData[FRAM_DATA_SIZE];
	u16 Size = 0;
	u16 CrcSum = 0;
	u8 *pData;

	memset((u8 *)&FramWriteData, 0xFF, FRAM_DATA_SIZE);
	Size = sizeof(Energy_Memory);
	memcpy((u8 *)&FramWriteData, (u8 *)&ElectricEnergy, Size);

	pData = (u8 *)&FramWriteData[0];
	CrcSum= FramData_Crc(pData);
	pData += (FRAM_DATA_SIZE-2);
	memcpy(pData, (u8 *)&CrcSum, 2);
	FRAM_I2C_WriteData(FRAM_STARTADDR, FramWriteData, FRAM_DATA_SIZE);
	WRITE_PROTECT;
}
void FRAM_ReadData(void)
{
    u8 FramReadData[FRAM_DATA_SIZE];
    for(u8 i =0;i<FRAM_DATA_SIZE;i++)
    {
        FramReadData[i] = 0;
    }
	u16 Size = 0;
	u16 Crc = 0;
	__nop();

	FRAM_I2C_ReadData(FRAM_STARTADDR, FramReadData, FRAM_DATA_SIZE);
	Crc = FramData_Crc(FramReadData);
	if (Crc == FLIPW(&FramReadData[FRAM_DATA_SIZE-2]))  //CRC��֤ ��ȡ�Ƿ����
    {
		Size = sizeof(Energy_Memory);
		memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);

	}
	else // ʧ�ܣ��ѵ�ǰ����д��EEPROM
	{
		//Size = sizeof(Energy_Memory);
		//memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);
	}
}

/*
void FRAM_Erase_Chip(void)
{
	uint16_t i = 0;
	uint8_t Data[FRAM_SECTOR_SIZE];

	memset(Data, 0xFF, FRAM_SECTOR_SIZE);
	for (i = 0; i < FRAM_SIZE; i+=FRAM_SECTOR_SIZE)
	{
		FRAM_WriteData(i, Data, FRAM_SECTOR_SIZE);
	}
}
// uint16_t Addr ��ʼ��ַ
// uint16_t Num ɾ����sector����
void FRAM_Erase_Sector(uint16_t Addr, uint16_t Num)
{
	uint16_t i = 0;
	uint8_t Data[FRAM_SECTOR_SIZE];
	uint16_t startAddr;
	uint16_t Sector = Addr/FRAM_SECTOR_SIZE;

	if (Addr >= FRAM_SIZE)
	{
		return;
	}

	if ((Addr+Num*FRAM_SECTOR_SIZE) >= FRAM_SIZE)
	{
		return;
	}

	startAddr = Sector * FRAM_SECTOR_SIZE;
	memset(Data, 0xFF, FRAM_SECTOR_SIZE);

	for (i = 0; i < Num; i++)
	{
		FRAM_WriteData(startAddr+i*FRAM_SECTOR_SIZE, Data, FRAM_SECTOR_SIZE);
	}
}*/

