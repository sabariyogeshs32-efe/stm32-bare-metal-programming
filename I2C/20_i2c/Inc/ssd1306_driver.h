/*
 * ssd1306_driver.h
 *
 *  Created on: Jun 14, 2026
 *      Author: sabariyogesh
 */

#ifndef SSD1306_DRIVER_H_
#define SSD1306_DRIVER_H_

void Set_Cursor(uint8_t slave_addr,uint8_t cmd_mem_addr_ssd1306,uint8_t page_addr,uint8_t col_start_addr);
void OLED_WriteChar(uint8_t slave_addr,uint8_t data_mem_addr_ssd1306,char x);
void OLED_WriteString(uint8_t slave_addr,uint8_t data_mem_addr_ssd1306,char *str);



#endif /* SSD1306_DRIVER_H_ */
