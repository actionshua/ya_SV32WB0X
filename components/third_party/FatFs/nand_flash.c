
#include "nand_flash.h"
#include "pinmux/hal_pinmux.h"
#include "pinmux/drv_pinmux.h"


#define CS_CTL_PIN	GPIO_11		//don't use GPIO_13
#define NAND_CLOCK	20			//uint:Mbit/s
void SPI_FLASH_Init(void)
{
	//cs
	drv_gpio_set_mode(CS_CTL_PIN, PIN_MODE_GPIO);
	drv_gpio_set_dir(CS_CTL_PIN, GPIO_DIR_OUT);

	SPI_FLASH_CS_HIGH(); 
	drv_pinmux_manual_function_select_enable(SEL_SPI_MST);
	drv_spi_mst_init(NAND_CLOCK * 1000 * 1000, 0, 0);
}

void SPI_FLASH_WriteEnable(void)
{
  SPI_FLASH_CS_LOW();
  SPI_FLASH_SendByte(WriteEnable);
  SPI_FLASH_CS_HIGH();
}

void SPI_FLASH_WriteDisable(void)
{
  SPI_FLASH_CS_LOW();
  SPI_FLASH_SendByte(WriteDisable);
  SPI_FLASH_CS_HIGH();
}

static uint8_t SPI_Flash_ReadRegister(uint8_t address)
{
  uint8_t StatusRegister = 0;
 
  SPI_FLASH_SendByte(ReadStatusRegister);
  SPI_FLASH_SendByte(address);
  StatusRegister = SPI_FLASH_ReceiveByte();

  return StatusRegister;
}

uint8_t SPI_Flash_ReadStatusRegister()
{
	return SPI_Flash_ReadRegister(0xC0);
}

uint8_t SPI_Flash_ReadOtpRegister()
{
	return SPI_Flash_ReadRegister(0xB0);
}

uint8_t SPI_Flash_ReadBlockLockRegister()
{
	return SPI_Flash_ReadRegister(0xA0);
}

void SPI_Flash_WriteRegister(uint8_t address,uint8_t Byte)
{
  SPI_FLASH_CS_LOW();
  SPI_FLASH_SendByte(WriteStatusRegister);
  SPI_FLASH_SendByte(address);
  SPI_FLASH_SendByte(Byte);
  SPI_FLASH_CS_HIGH();
}

void SPI_Flash_WriteStatusRegister(uint8_t Byte)
{
	SPI_Flash_WriteRegister(0xC0,Byte);
}

void SPI_Flash_WriteOtpRegister(uint8_t Byte)
{
	SPI_Flash_WriteRegister(0xB0,Byte);
}

void SPI_Flash_WriteBlockLockRegister(uint8_t Byte)
{
	SPI_Flash_WriteRegister(0xA0,Byte);
}

uint8_t SPI_FLASH_SendByte(uint8_t byte)
{
	unsigned char ret_value;
	hal_spi_mst_transfer(&byte, &ret_value, sizeof(char), GPIO_13);

	return ret_value;
}


uint8_t SPI_FLASH_ReceiveByte(void)
{
  return (SPI_FLASH_SendByte(Dummy_Byte));
}


uint32_t SPI_FLASH_SET_RA(uint8_t cmd, uint32_t add)
{
	int ret_status_reg;
	SPI_FLASH_CS_LOW();
	SPI_FLASH_SendByte(cmd);
	
	SPI_FLASH_SendByte((add & 0xFF0000) >> 16);
	SPI_FLASH_SendByte((add & 0xFF00) >> 8);
	SPI_FLASH_SendByte(add & 0xFF);

	ret_status_reg = SPI_FLASH_WaitForFlag(STATUS_ST_OIP, 0);//wait for read end

	SPI_FLASH_CS_HIGH();

	return ret_status_reg;
}
uint32_t SPI_FLASH_PageRead(uint8_t *pBuffer, uint32_t ReadAddr)
{
	uint16_t ca = 0x04;//read/write 2048 one page.ref datasheet table 5-2
	uint32_t NumByteToRead= 2048;
	uint8_t ret_status_reg;

	ret_status_reg = SPI_FLASH_SET_RA(PageToCache, ReadAddr);

	if(((ret_status_reg & STATUS_ST_ECCS1) == 1) && \
		((ret_status_reg & STATUS_ST_ECCS0) == 0))
	{
		printf("read [%x] ecc error\n",ReadAddr);
		return -1;
	}
	SPI_FLASH_CS_LOW();

//read data from cache
	SPI_FLASH_SendByte(CacheOutput);
	SPI_FLASH_SendByte((ca & 0xFF00) >> 8);  
	SPI_FLASH_SendByte(ca & 0xFF);
	SPI_FLASH_SendByte(Dummy_Byte);

	while(NumByteToRead--)
	{
		*pBuffer = SPI_FLASH_ReceiveByte();
		pBuffer++; 
	}
	SPI_FLASH_CS_HIGH();
	return NumByteToRead;
}


uint8_t SPI_FLASH_BulkErase(uint32_t BlockAddr)
{
	uint8_t ret;
	uint8_t ret_status_reg;
	
	SPI_FLASH_WriteEnable();
	ret_status_reg = SPI_FLASH_SET_RA(BlockErace, BlockAddr);

	if(ret_status_reg & STATUS_ST_E_FAIL){
		printf("Block Erase Error [%x]\n",BlockAddr);
		return -1;
	}
	else{ 
		return 0;
	}
}



uint8_t SPI_FLASH_ReadDeviceID(void)
{
  uint8_t DeviceID = 0;
  SPI_FLASH_CS_LOW();
  SPI_FLASH_SendByte(ReadDeviceID);
  SPI_FLASH_SendByte(0x01); 
  DeviceID = SPI_FLASH_ReceiveByte();
  SPI_FLASH_CS_HIGH();      
  return DeviceID;
}

uint8_t SPI_FLASH_ReadManuID(void)
{
  uint8_t DeviceID = 0;
  SPI_FLASH_CS_LOW();
  SPI_FLASH_SendByte(ReadDeviceID);
  SPI_FLASH_SendByte(0x00);
  DeviceID = SPI_FLASH_ReceiveByte();
  SPI_FLASH_CS_HIGH();      
  return DeviceID;
}

#if 0
void SPI_FLASH_ByteWrite(uint8_t Byte, uint32_t WriteAddr)
{
  SPI_FLASH_WriteEnable(); 
  SPI_FLASH_CS_LOW();
  SPI_FLASH_SendByte(Page_Program);
  SPI_FLASH_SendByte((WriteAddr & 0xFF0000) >> 16);
  SPI_FLASH_SendByte((WriteAddr & 0xFF00) >> 8);  
  SPI_FLASH_SendByte(WriteAddr & 0xFF);
  
  SPI_FLASH_SendByte(Byte); 
  SPI_FLASH_CS_HIGH();
  SPI_FLASH_WaitForWriteEnd();
}
#endif

uint8_t SPI_FLASH_PageWrite(uint8_t* pBuffer, uint32_t WriteAddr)
{
	uint16_t ca = 0x04;//read/write 2048 one page.ref datasheet table 5-2
	uint16_t NumByteToWrite = 2048;
	uint8_t ret_status_reg;
	
	SPI_FLASH_WriteEnable(); 
	SPI_FLASH_CS_LOW();
	SPI_FLASH_SendByte(Page_Program);

	//16 bit column address
	SPI_FLASH_SendByte((ca & 0xFF00) >> 8);  
	SPI_FLASH_SendByte(ca & 0xFF);

	while(NumByteToWrite--)
	{
		SPI_FLASH_SendByte(*pBuffer);
		pBuffer++; 
	}
	SPI_FLASH_CS_HIGH();

	ret_status_reg = SPI_FLASH_SET_RA(Page_Program_Exe, WriteAddr);
	
	if(ret_status_reg & STATUS_ST_P_FAIL){
		printf("page write Error [%x]\n",WriteAddr);
		return -1;
	}
	else{ 
		return 0;
	}
}

#if 0
void SPI_FLASH_BufferWrite(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
  uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

  Addr = WriteAddr % SPI_FLASH_PageSize;
  count = SPI_FLASH_PageSize - Addr;
  NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
  NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
  
  if(Addr == 0) /* WriteAddr is SPI_FLASH_PageSize aligned  */
  {
    if(NumOfPage == 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */ 
    {
      while(NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;  
      }    
     
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
   }
  }
  else /* WriteAddr is not SPI_FLASH_PageSize aligned  */
  {
    if(NumOfPage== 0) /* NumByteToWrite < SPI_FLASH_PageSize */
    {
      if(NumOfSingle > count) /* (NumByteToWrite + WriteAddr) > SPI_FLASH_PageSize */
      {
        temp = NumOfSingle - count;
      
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
        WriteAddr +=  count;
        pBuffer += count; 
        
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, temp);
      }
      else
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
      }
    }
    else /* NumByteToWrite > SPI_FLASH_PageSize */
    {
      NumByteToWrite -= count;
      NumOfPage =  NumByteToWrite / SPI_FLASH_PageSize;
      NumOfSingle = NumByteToWrite % SPI_FLASH_PageSize;
      
      SPI_FLASH_PageWrite(pBuffer, WriteAddr, count);
      WriteAddr +=  count;
      pBuffer += count;  
     
      while(NumOfPage--)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, SPI_FLASH_PageSize);
        WriteAddr +=  SPI_FLASH_PageSize;
        pBuffer += SPI_FLASH_PageSize;
      }
      
      if(NumOfSingle != 0)
      {
        SPI_FLASH_PageWrite(pBuffer, WriteAddr, NumOfSingle);
      }
    }
  }
}
#endif

uint8_t SPI_FLASH_WaitForFlag(uint8_t flag,uint8_t expect_flag)
{
	int ret;
	int timeout = 100;
	ret = SPI_Flash_ReadStatusRegister();
	while((ret & flag) !=  expect_flag)
	{
		ret = SPI_Flash_ReadStatusRegister();
		if(--timeout== 0)
		{
			printf("nand flash wait idel timeout\n");
			printf("status reg = %d\n",ret);
			return -1;
		}
		OS_UsDelay(500);
	}
	return ret;
	//while(SPI_FLASH_StatusCheck(flag) != expect_flag);	
}

void SPI_FLASH_Rest()
{
	SPI_FLASH_SendByte(0xFF);
	SPI_Flash_WriteBlockLockRegister(0x0);//enable erase and write op
}
