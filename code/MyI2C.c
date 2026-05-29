#include "main.h"                  // 换成 HAL 库的头文件
#include "MyI2C.h"

// ==========================================
// 🛠️ 引脚物理绑定配置
// 假设你把 MPU6050 的 SCL 接在 PB10，SDA 接在 PB11
// 如果你接在其他引脚，直接修改下面的端口和引脚号即可
// ==========================================
#define I2C_SCL_PORT  GPIOB
#define I2C_SCL_PIN   GPIO_PIN_10

#define I2C_SDA_PORT  GPIOB
#define I2C_SDA_PIN   GPIO_PIN_11

/**
  * 函    数：微秒级延时（因为 HAL 库只有毫秒延时，模拟 I2C 必须用这个短延时）
  */
static void MyI2C_Delay_us(uint32_t us)
{
    // 在 72MHz 主频下，利用简单循环实现大约 1us 的延时
    uint32_t delay = us * 5;
    while(delay--);
}

/**
  * 函    数：I2C写SCL引脚电平
  */
void MyI2C_W_SCL(uint8_t BitValue)
{
    HAL_GPIO_WritePin(I2C_SCL_PORT, I2C_SCL_PIN, (GPIO_PinState)BitValue);
    MyI2C_Delay_us(10); // 延时保证时序稳定
}

/**
  * 函    数：I2C写SDA引脚电平
  */
void MyI2C_W_SDA(uint8_t BitValue)
{
    HAL_GPIO_WritePin(I2C_SDA_PORT, I2C_SDA_PIN, (GPIO_PinState)BitValue);
    MyI2C_Delay_us(10);
}

/**
  * 函    数：I2C读SDA引脚电平
  */
uint8_t MyI2C_R_SDA(void)
{
    return (uint8_t)HAL_GPIO_ReadPin(I2C_SDA_PORT, I2C_SDA_PIN);
}

/**
  * 函    数：I2C初始化
  * 注    意：由于你已经在 CubeMX 里配置过 GPIO 了，这里只需要确保引脚默认拉高即可
  */
void MyI2C_Init(void)
{
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

/* ================================================================= */
/* 协议层函数（Start, Stop, SendByte, ReceiveByte 等）完全不需要修改 */
/* 直接保留江科大原本的逻辑即可 */
/* ================================================================= */

void MyI2C_Start(void)
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i ++)
	{
		MyI2C_W_SDA(!!(Byte & (0x80 >> i)));
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void)
{
	uint8_t i, Byte = 0x00;
	MyI2C_W_SDA(1);
	for (i = 0; i < 8; i ++)
	{
		MyI2C_W_SCL(1);
		if (MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t AckBit)
{
	MyI2C_W_SDA(AckBit);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void)
{
	uint8_t AckBit;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	AckBit = MyI2C_R_SDA();
	MyI2C_W_SCL(0);
	return AckBit;
}
