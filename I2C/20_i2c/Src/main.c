#include "i2c.h"
#include "stm32f446xx.h"
#include <stdint.h>
#include "ssd1306_driver.h"


uint8_t slave_addr_ssd1306 = 0x3C;
uint8_t cmd_mem_addr_ssd1306 = 0x00;
uint8_t data_mem_addr_ssd1306 = 0x40;

uint8_t s[] = {0xAE,       // 1. Display OFF (Sleep mode)
	    0xD5, 0x80, // 2. Set Display Clock Divide Ratio/Oscillator Frequency
	    0xA8, 0x3F, // 3. Set Multiplex Ratio (0x3F for 128x64, 0x1F for 128x32)
	    0xD3, 0x00, // 4. Set Display Offset (0)
	    0x40,       // 5. Set Display Start Line (0)
	    0x8D, 0x14, // 6. ENABLE CHARGE PUMP (Critical!)
	    0x20, 0x02, // 7. Set Memory Addressing Mode (page)
	    0xA1,       // 8. Set Segment Re-map (Flip horizontally)
	    0xC8,       // 9. Set COM Output Scan Direction (Flip vertically)
	    0xDA, 0x12, // 10. Set COM Pins Hardware Configuration
	    0x81, 0xCF, // 11. Set Contrast Control (0x00 to 0xFF)
	    0xD9, 0xF1, // 12. Set Pre-charge Period
	    0xDB, 0x40, // 13. Set VCOMH Deselect Level
	    0xA4,       // 14. Output RAM to Display
	    0xA6,       // 15. Normal Display (0xA7 for inverse)
	    0xAF     // 16. Display ON;
};
uint8_t s1[] = {0xFF};

uint32_t size = 7;
int main()
{
	i2c_Init();
	//Delay_ms(100);

		i2c_Burst_Write(slave_addr_ssd1306,cmd_mem_addr_ssd1306,(char*)s,sizeof(s));
		//i2c_Burst_Write(slave_addr_ssd1306,data_mem_addr_ssd1306,(char*)s1,1);

		/*1.Call Set Cursor function to set the cursor... */
		uint8_t page_addr = 0x01;

		uint8_t col_start_addr = 0x00;

		Set_Cursor(slave_addr_ssd1306,cmd_mem_addr_ssd1306,page_addr,col_start_addr);
	 	i2c_Burst_Write(slave_addr_ssd1306,data_mem_addr_ssd1306,(char*)s1,1);
	 	char *x = "Sabari APTIV Engineer";
	 	OLED_WriteString(slave_addr_ssd1306,data_mem_addr_ssd1306,x);

		while(1)
		{

	}
}
