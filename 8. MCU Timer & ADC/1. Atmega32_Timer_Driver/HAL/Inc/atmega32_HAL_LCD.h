/*
 * atmega32_HAL_LCD.h
 *
 * Created: 05/12/2024 8:02:31 PM
 *  Author: Dubai Store
 */ 


#ifndef ATMEGA32_HAL_LCD_H_
#define ATMEGA32_HAL_LCD_H_

#include "atmega32_GPIO_driver.h"

#define LCD_8BIT_MODE                   1
#define LCD_4BIT_MODE                   0
#define LCD_MODE                        LCD_4BIT_MODE

#define LCD_DATA_PORT                   PORTA
#define LCD_DIRECTION_PORT              DDRA

#define LCD_CRTL_PORT                   PORTB
#define LCD_CRTL_DIRECTION              DDRB

#define LCD_BIT_D0                      PA0
#define LCD_BIT_D1                      PA1
#define LCD_BIT_D2                      PA2
#define LCD_BIT_D3                      PA3

#define RS                              PB0
#define EN                              PB1

#define _LCD_CLEAR                      0X01
#define _LCD_RETURN_HOME                0X02
#define _LCD_INC_SHIFT_OFF              0X06
#define _LCD_DEC_SHIFT_OFF              0X04
#define _LCD_INC_SHIFT_ON               0X07
#define _LCD_DEC_SHIFT_ON               0X05
#define _LCD_CURSOR_SHIFT_LEFT          0X10
#define _LCD_CURSOR_SHIFT_RIGHT         0X14
#define _LCD_DISPLAY_SHIFT_LEFT         0X18
#define _LCD_DISPLAY_SHIFT_RIGHT        0X1C
#define _LCD_CURSOR_OFF_DISPLAY_ON      0X0C
#define _LCD_CURSOR_ON_DISPLAY_ON       0X0F
#define _LCD_CURSOR_OFF_DISPLAY_OFF     0X08
#define _LCD_CURSOR_ON_BLINK_ON         0X0F
#define _LCD_CURSOR_ON_BLINK_OFF        0X0E
#define _LCD_8BIT_MODE_2LINE            0X38
#define _LCD_4BIT_MODE_2LINE            0X28
#define _LCD_DDRAM_START                0X80
#define _LCD_CGRAM_START                0X40
#define _LCD_4BIT_PINS                   4
#define _LCD_8BIT_PINS                   8

#define ROW1  1
#define ROW2  2
#define ROW3  3
#define ROW4  4

/*FUNCTIONS DECLARATIONS*/
void lcd_initialize();
void lcd_send_command(uint8_t command);
void lcd_send_char_data(uint8_t data);
void lcd_set_cursor_pos(uint8_t row, uint8_t col);
void lcd_send_char_data_pos(uint8_t data, uint8_t row, uint8_t column);
void lcd_send_string(uint8_t str[]);
void lcd_send_string_pos(uint8_t str[], uint8_t row, uint8_t column);
void lcd_send_custom_char(uint8_t custom_chr[], uint8_t row, uint8_t column, uint8_t memory_pos);

void covert_num_to_str(uint32_t num, char *s);

#endif /* ATMEGA32_HAL_LCD_H_ */