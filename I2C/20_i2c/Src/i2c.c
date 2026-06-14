#include <stm32f446xx.h>
#include <stdint.h>


#define GPIOB_EN		(1U<<1)

#define I2C1_EN			(1U<<21)
#define I2C_16MHz		(0x10)
#define CCR_100KHz		(80)
#define TRISE_100KHz	(17)
#define I2C_PE			(1U<<0)

#define SR2_BUSY		(1U<<1)
#define CR1_SWRST		(1U<<15)
#define CR1_START		(1U<<8)
#define SR1_SB			(1U<<0)
#define SR1_ADDR		(1U<<1)
#define SR1_TXE			(1U<<7)
#define CR1_ACK			(1U<<10)
#define CR1_STOP		(1U<<9)
#define SR1_RxNE		(1U<<6)
#define SR1_RxNE		(1U<<6)
#define SR1_BTF			(1U<<2)


/*Ports:
 * PB8 ----i2c scl
 * PB9 ----i2c sda
 * */


void i2c_Init(void)
{
	/*Figure out the two pins for scl,sda for i2c1... */


	/*Enable Clk access to the GPIOB since we are using this for scl,sda for i2c... */
	RCC->AHB1ENR |= GPIOB_EN;

	/*Set the PB8,PB9 in Alternate function mode... = 10 */
	GPIOB->MODER |= (1U<<17);
	GPIOB->MODER &= ~(1U<<16);

	GPIOB->MODER |= (1U<<19);
	GPIOB->MODER &= ~(1U<<18);

	/*Set the AF Values in respective register... = AF4 */
	GPIOB->AFR[1] &= ~(1U<<0);
	GPIOB->AFR[1] &= ~(1U<<1);
	GPIOB->AFR[1] |=  (1U<<2);
	GPIOB->AFR[1] &= ~(1U<<3);

	GPIOB->AFR[1] &= ~(1U<<4);
	GPIOB->AFR[1] &= ~(1U<<5);
	GPIOB->AFR[1] |=  (1U<<6);
	GPIOB->AFR[1] &= ~(1U<<7);

	/*Set the output mode to Open Drain mode... */
	GPIOB->OTYPER |= (1U<<8);
	GPIOB->OTYPER |= (1U<<9);

	/*Set the two pins in Pull Up mode... = 01 */
	GPIOB->PUPDR &= ~(1U<<17);
	GPIOB->PUPDR |=  (1U<<16);

	GPIOB->PUPDR &= ~(1U<<19);
	GPIOB->PUPDR |=  (1U<<18);

	/*Enable the Clk access to i2c1... */
	RCC->APB1ENR |= I2C1_EN;

	/*Set the Clk Frequency of the i2c to system freq 16MHz... */
	I2C1->CR2  = I2C_16MHz;		//Hex : 0001 0000 = 0x10

	/*Set the i2c1 in standard mode*/
	I2C1->CCR  = CCR_100KHz;

	/*Set the TRISE to 1000ns for 100KHz*/
	I2C1->TRISE  = TRISE_100KHz;

	/*Enable PE in CR1... */
	I2C1->CR1 |= I2C_PE;




}


void i2c_Read(uint8_t slave_addr,uint8_t mem_addr,char *data)
{

	volatile uint32_t temp;			//For holding the temp value which we use for clearing the flags...
	/*Ensure that the I2C Bus is Not BUSY... */
	while((I2C1->SR2 & SR2_BUSY)){}

	/*RESET the i2c... */
	I2C1->CR1 |= CR1_SWRST;

	/*Release the Reset... */
	I2C1->CR1 &= ~CR1_SWRST;

	/*Send the Start Bit: Enable the Start Bit... */
	I2C1->CR1 |= CR1_START;

	/*Ensure that the Start Bit is transfer by checking the start flag in SR... */
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Send the Slave addr... + write */
	I2C1->DR = slave_addr<<1;

	/*Ensure the Adrress has been successfully sent by status flag... */
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear the Addr Flag by reading the SR2... */
	temp = I2C1->SR2;

	/*After sending the slave addr start send the memory addr of the slave where we are going to read the data from... */
	I2C1->DR = mem_addr;

	/*Ensure that the mem_addr has been successfully sent by status Txe flag... */
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Resend The START CONDITION inorder to notify master ready for next transaction instead of a STOP */
	/*Send the Start Bit: Enable the Start Bit... */
	I2C1->CR1 |= CR1_START;

	/*Ensure that the Start Bit is transfer by checking the start flag in SR... */
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Send the Slave addr... + read */
	I2C1->DR = (slave_addr<<1 | 1);

	/*Ensure the Adrress has been successfully sent by status flag... */
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Disable the ACK inorder to notify that this is the last byte the master reading from you... */
	I2C1->CR1 &= ~CR1_ACK;

	/*Clear the Addr Flag by reading the SR2... */
	temp = I2C1->SR2;

	/*Send STOP CONDITION to notify the slave that this is last byte accessing by the master... */
	I2C1->CR1 |= CR1_STOP;

	/*Wait until the RxNE flag to set for start to read from the DR... */
	while(!(I2C1->SR1 & SR1_RxNE)){}

	/*READ Data from DR and Store it to the pointer location... */
	*data = I2C1->DR;



}

void i2c_Burst_Read(uint8_t slave_addr,uint8_t mem_addr,char *data,uint32_t n)
{

	volatile uint32_t temp;			//For holding the temp value which we use for clearing the flags...
	/*Ensure that the I2C Bus is Not BUSY... */
	while((I2C1->SR2 & SR2_BUSY)){}

	/*RESET the i2c... */
	I2C1->CR1 |= CR1_SWRST;

	/*Release the Reset... */
	I2C1->CR1 &= ~CR1_SWRST;

	/*Send the Start Bit: Enable the Start Bit... */
	I2C1->CR1 |= CR1_START;

	/*Ensure that the Start Bit is transfer by checking the start flag in SR... */
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Send the Slave addr... + write */
	I2C1->DR = slave_addr<<1;

	/*Ensure the Adrress has been successfully sent by status flag... */
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear the Addr Flag by reading the SR2... */
	temp = I2C1->SR2;

	/*After sending the slave addr start send the memory addr of the slave where we are going to read the data from... */
	I2C1->DR = mem_addr;

	/*Ensure that the mem_addr has been successfully sent by status Txe flag... */
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*Resend The START CONDITION inorder to notify master ready for next transaction instead of a STOP */
	/*Send the Start Bit: Enable the Start Bit... */
	I2C1->CR1 |= CR1_START;

	/*Ensure that the Start Bit is transfer by checking the start flag in SR... */
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Send the Slave addr... + read */
	I2C1->DR = (slave_addr<<1 | 1);

	/*Ensure the Adrress has been successfully sent by status flag... */
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear the Addr Flag by reading the SR2... */
	temp = I2C1->SR2;

	/*Enable the ACK inorder to notify that this master reading multiple bytes from you... */
	I2C1->CR1 |= CR1_ACK;

	while(n > 0U)
	{

		if(n == 1U)
		{

			/*Disable the ACK inorder to notify that this is the last byte the master reading from you... */
			I2C1->CR1 &= ~CR1_ACK;

			/*Send STOP CONDITION to notify the slave that this is last byte accessing by the master... */
			I2C1->CR1 |= CR1_STOP;

			/*Wait until the RxNE flag to set for start to read from the DR... */
			while(!(I2C1->SR1 & SR1_RxNE)){}

			/*READ Data from DR and Store it to the pointer location... */
			*data = I2C1->DR;

			break;
		}

		else
		{
				/*Wait until the RxNE flag to set for start to read from the DR... */
				while(!(I2C1->SR1 & SR1_RxNE)){}

				/*READ Data from DR and Store it to the pointer location... */
				(*data++) = I2C1->DR;

				n--;
		}
	}

}


void i2c_Burst_Write(uint8_t slave_addr,uint8_t mem_addr,char *data,uint32_t n)
{

	volatile uint32_t temp;			//For holding the temp value which we use for clearing the flags...
	/*Ensure that the I2C Bus is Not BUSY... */
	while((I2C1->SR2 & SR2_BUSY)){}

//	/*RESET the i2c... */
//	I2C1->CR1 |= CR1_SWRST;
//
//	/*Release the Reset... */
//	I2C1->CR1 &= ~CR1_SWRST;

	/*Send the Start Bit: Enable the Start Bit... */
	I2C1->CR1 |= CR1_START;

	/*Ensure that the Start Bit is transfer by checking the start flag in SR... */
	while(!(I2C1->SR1 & SR1_SB)){}

	/*Send the Slave addr... + write */
	I2C1->DR = slave_addr<<1;

	/*Ensure the Adrress has been successfully sent by status flag... */
	while(!(I2C1->SR1 & SR1_ADDR)){}

	/*Clear the Addr Flag by reading the SR2... */
	temp = I2C1->SR2;

	/*Ensure that the mem_addr has been successfully sent by status Txe flag... */
	while(!(I2C1->SR1 & SR1_TXE)){}

	/*After sending the slave addr start send the memory addr of the slave where we are going to read the data from... */
	I2C1->DR = mem_addr;


	for(int i=0; i<n; i++)
	{
		/*Ensure that the mem_addr has been successfully sent by status Txe flag... */
		while(!(I2C1->SR1 & SR1_TXE)){}

		/*Send the actual data to the slave by filling it in the DR... */
		I2C1->DR = *data++;


	}

	/*Ensure that the data has been successfully sent by status Txe flag... */
	while(!(I2C1->SR1 & SR1_BTF)){}

	/*Send STOP CONDITION to notify the slave that this is last byte accessing by the master... */
	I2C1->CR1 |= CR1_STOP;



}

void Delay_ms(volatile uint32_t ms) {
    ms *= (16000000 / 1000 / 4);
    while (ms--) {
        __NOP();
    }
}















