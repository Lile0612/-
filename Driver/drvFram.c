/*! @file
********************************************************************************
<PRE>
模 块 名     : 铁电读取写入程序（MB85RC16/04）
文 件 名     : drvFram.c
相关文件      :
文件实现功能 :
作者         : < 612 >
版本         : 1.0
--------------------------------------------------------------------------------
备注         : 数显表
--------------------------------------------------------------------------------
修改记录 :
  日 期        版本      修改人         修改内容
2018/05/22   1.0    < 612 >        创建

</PRE>
********************************************************************************

  * 版权所有(c) YYYY, <xxxx>, 保留所有权利

*******************************************************************************/


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

//配置SDA(PB11)推挽输出
void MyI2C_GPIO_Out_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   =  PIN_EE_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(PORT_EE_SDA, &GPIO_InitStructure);
}

//配置SDA(PB11)上拉输入
void  MyI2C_GPIO_IN_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   =  PIN_EE_SDA;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(PORT_EE_SDA, &GPIO_InitStructure);
}

//模拟起始信号
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

//模拟停止信号
void MyI2C_Stop(void)
{
  MyI2C_GPIO_Out_Config();
  SDA_0;                                       //I2CStop的条件是在SCL是低电平的情况下
  SCL_1;
  delay_us(50);
  SDA_1;
}

//I2C发送字节
u8 MyI2C_SendByte(u8 ByteData)              //I2C的基本传送方式是字节发送
{
  u8 ack;
  u8 i;
  MyI2C_GPIO_Out_Config();
  for (i = 0;  i < 8;  i++)                   //主器件通过SCL发出8个时钟脉冲将要发送的
  {                                           //数据通过SDA发出
    SCL_0;
    delay_us(50);
    if (ByteData&0x80)
      SDA_1;
    else
      SDA_0;
    delay_us(30);
    ByteData <<= 1;                           //数据建立时间200us
    SCL_1;
    delay_us(50);                            //数据保持时间没有要求
  }

  SCL_0;                                      //在第9个时钟时读取从件（ATC1024）发送的
                                              //ack应答信号，此时SDA应为输入状态，SD//为输入状态时，SDA是高电平
  delay_us(50);

  MyI2C_GPIO_IN_Config();                       //注意在设置SDA为输入时，一定要先使SCL

  SCL_1;                                      //是低电平，千万不能使SCL为高电平，因为在
  delay_us(50);                              //SCL是高电平的情况下，有可能出现SDA从低

  ack = SDA_read ;                            //到高的跳变（I2CStop状况）发送失败，
  SCL_0;

  return (ack);                               //返回ack信号，低电平表示有应答，高则没有
}


//I2C接收字节
u8 MyI2C_ReceiveByte(u8 last_char)
{
  u8 data=0, i;
  MyI2C_GPIO_IN_Config();                       //主器件通过8个时钟信号，接收从件发出的数据
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
  if (last_char)                              //如果接收是最后的一个字节时，主器件在第9个周期
    SDA_1;                                    //给从件一个高电平(NACK)，否则给一个低电平(ACK)
  else                                       //表示继续接收
    SDA_0;

  delay_us(30);
  SCL_1;
  delay_us(50);
  SCL_0;
  return data;
}
///////////////////////////////上半部分为驱动////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
// 以下为铁电读写操作

/* Private macro -------------------------------------------------------------*/
#define FRAM_SIZE 2048
#define FRAM_SECTOR_SIZE 32
#define FRAM_R 1
#define FRAM_W 0
#define FRAM_STARTADDR      (0x00000000) 
#define FRAM_DATA_SIZE	              32    // 最大参数长度
// Addr:11位地址
#define FRAM_MSBADDRESS(Addr, RW) (0xA0 | ((Addr & 0x0700) >> 7) | RW)
#define FRAM_LSBADDRESS(Addr) (Addr & 0xFF)
/********************************************************/

#define FRAM_RECORD_SIZE	             490    // 最大参数长度
#define FRAM_RECORD_ADDR      (0x00000030)      // DI 记录值地址

#define FRAM_DO_RECORD_ADDR      (0x00000220)      // DO 记录值地址

#define FRAM_Index_ADDR      (0x00000022)    // Di  标签
#define FRAM_INDEX_SIZE	              8    // 最大参数长度 标签页

#define FRAM_MaxDem_SIZE	             300    // 最大值参数长度
#define FRAM_MaxDem_ADDR      (0x00000410)      // 最大值记录地址

/********************************************************/

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

u16 FramRecord_Crc(u8 *pData)
{
	u16 Crc = 0;
	u16 Counter = 0;
	for (Counter = 0; Counter < FRAM_RECORD_SIZE-2; Counter++)
	{
		Crc += *(pData+Counter);
	}
    Crc = Crc & 0xff;
	return Crc;
}

u16 FramIndex_Crc(u8 *pData)
{
	u16 Crc = 0;
	u16 Counter = 0;
	for (Counter = 0; Counter < FRAM_INDEX_SIZE-2; Counter++)
	{
		Crc += *(pData+Counter);
	}
    Crc = Crc & 0xff;
	return Crc;
}

u16 FramMax_Crc(u8 *pData)
{
	u16 Crc = 0;
	u16 Counter = 0;
	for (Counter = 0; Counter < FRAM_MaxDem_SIZE-2; Counter++)
	{
		Crc += *(pData+Counter);
	}
    Crc = Crc & 0xff;
	return Crc;
}

/**
  * @brief  写数据
  * @param  -uint16_t phyAddr:物理地址
  			-uint8_t *pWriteData: 要写入的数据缓存
  			-uint16_t Length:数据长度
  * @retval : IIC_ERR_NO_ACK-没有应答
  				IIC_ERR_NONE-正确
  */
u8 FRAM_I2C_WriteData(u16 phyAddr, u8 *pWriteData, u16 Length)
{
	u8 Addr;
	u16 NumByteToWrite = Length;

    MyI2C_Start();

	// 发送器件地址 高3位地址
	Addr = FRAM_MSBADDRESS(phyAddr, FRAM_W);
    if(MyI2C_SendByte(Addr))//写芯片地址
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }

	// 发送低8位地址
	Addr = FRAM_LSBADDRESS(phyAddr);
    if(MyI2C_SendByte(Addr))//写芯片地址
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
  * @brief  读数据
  * @param  -uint16_t phyAddr:物理地址
  			-uint8_t *pWriteData: 要读取的数据缓存
  			-uint16_t Length:数据长度
  * @retval : IIC_ERR_NO_ACK-没有应答
  				IIC_ERR_NONE-正确
  */
u8 FRAM_I2C_ReadData(u16 phyAddr, u8 *pReadData, u16 Length)
{
	u8 Addr;
	u16 NumByteToRead = Length;
    u16 i;
    MyI2C_Start();

	// 发送器件地址 高3位地址
	Addr = FRAM_MSBADDRESS(phyAddr, FRAM_W);
    if(MyI2C_SendByte(Addr))//写芯片地址
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }

	// 发送低8位地址
	Addr = FRAM_LSBADDRESS(phyAddr);
    if(MyI2C_SendByte(Addr))//写芯片地址
    {
        MyI2C_Stop();
        return IIC_ERR_NO_ACK;
    }

    MyI2C_Start();

	// 发送器件地址 高3位地址
	Addr = FRAM_MSBADDRESS(phyAddr, FRAM_R);
    if(MyI2C_SendByte(Addr))//写芯片地址
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
	if (Crc == FLIPW(&FramReadData[FRAM_DATA_SIZE-2]))  //CRC验证 读取是否出错
    {
		Size = sizeof(Energy_Memory);
		memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);

	}
	else // 失败，把当前数据写入EEPROM
	{
		//Size = sizeof(Energy_Memory);
		//memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);
	}
}


void FRAM_RecordWrite(void)
{
	WRITE_UNPROTECT;
	u8 FramWriteData[FRAM_RECORD_SIZE];
	u16 Size = 0;
	u16 CrcSum = 0;
	u8 *pData;

	memset((u8 *)&FramWriteData, 0xFF, FRAM_RECORD_SIZE);
	Size = sizeof(SOE_DataStruct)*40;
	memcpy((u8 *)&FramWriteData, (u8 *)&DinRecord[0], Size);

	pData = (u8 *)&FramWriteData[0];
	CrcSum= FramRecord_Crc(pData);
	pData += (FRAM_RECORD_SIZE-2);
	memcpy(pData, (u8 *)&CrcSum, 2);
	FRAM_I2C_WriteData(FRAM_RECORD_ADDR, FramWriteData, FRAM_RECORD_SIZE);
	WRITE_PROTECT;
}
void FRAM_RecordRead(void)
{
    u8 FramReadData[FRAM_RECORD_SIZE];
    for(u16 i =0;i<FRAM_RECORD_SIZE;i++)
    {
        FramReadData[i] = 0;
    }
	u16 Size = 0;
	u16 Crc = 0;

	FRAM_I2C_ReadData(FRAM_RECORD_ADDR, FramReadData, FRAM_RECORD_SIZE);
	Crc = FramRecord_Crc(FramReadData);
	if (Crc == FLIPW(&FramReadData[FRAM_RECORD_SIZE-2]))  //CRC验证 读取是否出错
    {
		Size = sizeof(SOE_DataStruct)*40;
		memcpy((u8 *)&DinRecord[0], (u8 *)&FramReadData[0], Size);

	}
	else // 失败，把当前数据写入EEPROM
	{
		//Size = sizeof(Energy_Memory);
		//memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);
	}
}

//===================================================================
//序列号读写
void FRAM_IndexWrite(void)
{
	WRITE_UNPROTECT;
	u8 FramWriteIndex[FRAM_INDEX_SIZE];
	u16 Size = 0;
	u16 CrcSum = 0;
	u8 *pData;

	memset((u8 *)&FramWriteIndex, 0xFF, FRAM_INDEX_SIZE);
	Size = sizeof(SOE_IndexStruct);
	memcpy((u8 *)&FramWriteIndex, (u8 *)&SoeIndex, Size);

	pData = (u8 *)&FramWriteIndex[0];
	CrcSum= FramIndex_Crc(pData);
	pData += (FRAM_INDEX_SIZE-2);
	memcpy(pData, (u8 *)&CrcSum, 2);
	FRAM_I2C_WriteData(FRAM_Index_ADDR, FramWriteIndex, FRAM_INDEX_SIZE);
	WRITE_PROTECT;
}
void FRAM_IndexRead(void)
{
    u8 FramReadIndex[FRAM_INDEX_SIZE];
    for(u8 i =0;i<FRAM_INDEX_SIZE;i++)
    {
        FramReadIndex[i] = 0;
    }
	u16 Size = 0;
	u16 Crc = 0;

	FRAM_I2C_ReadData(FRAM_Index_ADDR, FramReadIndex, FRAM_INDEX_SIZE);
	Crc = FramIndex_Crc(FramReadIndex);
	if (Crc == FLIPW(&FramReadIndex[FRAM_INDEX_SIZE-2]))  //CRC验证 读取是否出错
    {
		Size = sizeof(SOE_IndexStruct);
		memcpy((u8 *)&SoeIndex, (u8 *)&FramReadIndex[0], Size);

	}
	else // 失败，把当前数据写入EEPROM
	{
		//Size = sizeof(Energy_Memory);
		//memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);
	}
}

//===================================================================
//DO 数据写入
void FRAM_DoRecordWrite(void)
{
	WRITE_UNPROTECT;
	u8 FramWriteDo[FRAM_RECORD_SIZE];
	u16 Size = 0;
	u16 CrcSum = 0;
	u8 *pData;

	memset((u8 *)&FramWriteDo, 0xFF, FRAM_RECORD_SIZE);
	Size = sizeof(SOE_DataStruct)*40;
	memcpy((u8 *)&FramWriteDo, (u8 *)&DoutRecord[0], Size);

	pData = (u8 *)&FramWriteDo[0];
	CrcSum= FramRecord_Crc(pData);
	pData += (FRAM_RECORD_SIZE-2);
	memcpy(pData, (u8 *)&CrcSum, 2);
	FRAM_I2C_WriteData(FRAM_DO_RECORD_ADDR, FramWriteDo, FRAM_RECORD_SIZE);
	WRITE_PROTECT;
}
void FRAM_DoRecordRead(void)
{
    u8 FramReadDo[FRAM_RECORD_SIZE];
    for(u16 i =0;i<FRAM_RECORD_SIZE;i++)
    {
        FramReadDo[i] = 0;
    }
	u16 Size = 0;
	u16 Crc = 0;

	FRAM_I2C_ReadData(FRAM_DO_RECORD_ADDR, FramReadDo, FRAM_RECORD_SIZE);
	Crc = FramRecord_Crc(FramReadDo);
	if (Crc == FLIPW(&FramReadDo[FRAM_RECORD_SIZE-2]))  //CRC验证 读取是否出错
    {
		Size = sizeof(SOE_DataStruct)*40;
		memcpy((u8 *)&DoutRecord[0], (u8 *)&FramReadDo[0], Size);

	}
	else // 失败，把当前数据写入EEPROM
	{
		//Size = sizeof(Energy_Memory);
		//memcpy((u8 *)&ElectricEnergy, (u8 *)&FramReadData[0], Size);
	}
}

//===================================================================
//Max 需量数据写入
void FRAM_MaxDemWrite(void)
{
	WRITE_UNPROTECT;
	u8 FramWriteMax[FRAM_MaxDem_SIZE];
	u16 Size = 0;
	u16 CrcSum = 0;
	u8 *pData;

	memset((u8 *)&FramWriteMax, 0xFF, FRAM_MaxDem_SIZE);
	Size = sizeof(DemMaxStructure)*4;                       // 每周记录一次 四周 
	memcpy((u8 *)&FramWriteMax, (u8 *)&vg_DemMax_Val[0], Size);

	pData = (u8 *)&FramWriteMax[0];
	CrcSum= FramMax_Crc(pData);
	pData += (FRAM_MaxDem_SIZE-2);
	memcpy(pData, (u8 *)&CrcSum, 2);
	FRAM_I2C_WriteData(FRAM_MaxDem_ADDR, FramWriteMax, FRAM_MaxDem_SIZE);
	WRITE_PROTECT;
}
void FRAM_MaxDemRead(void)
{
    u8 FramReadMax[FRAM_MaxDem_SIZE];
    for(u16 i =0;i<FRAM_MaxDem_SIZE;i++)
    {
        FramReadMax[i] = 0;
    }
	u16 Size = 0;
	u16 Crc = 0;

	FRAM_I2C_ReadData(FRAM_MaxDem_ADDR, FramReadMax, FRAM_MaxDem_SIZE);
	Crc = FramMax_Crc(FramReadMax);
	if (Crc == FLIPW(&FramReadMax[FRAM_MaxDem_SIZE-2]))  //CRC验证 读取是否出错
    {
		Size = sizeof(DemMaxStructure)*4;
		memcpy((u8 *)&vg_DemMax_Val[0], (u8 *)&FramReadMax[0], Size);
	}
	else // 失败，把当前数据写入EEPROM
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
// uint16_t Addr 起始地址
// uint16_t Num 删除的sector数量
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

