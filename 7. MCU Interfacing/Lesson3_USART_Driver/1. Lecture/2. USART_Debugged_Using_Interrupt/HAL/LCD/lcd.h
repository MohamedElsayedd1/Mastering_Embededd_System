
#ifndef _LCD_H_
#define _LCD_H_

/* ================================================================ */
/* =========================== Includes =========================== */
/* ================================================================ */

#include "stm32f103x6_GPIO_driver.h"
#include "stm32f103x6.h"
#include <stdint.h>

/* ================================================================ */
/* ============= User Type Definitions (Structures) =============== */
/* ================================================================ */

typedef struct{
	GPIO_t *DataRegister;
	GPIO_t *ControlRegister;
	GPIO_PinConfig_t DataPins[8];
	GPIO_PinConfig_t EN;
	GPIO_PinConfig_t RS;
}lcd_t;

/* ================================================================ */
/* ============= Macros Configuration References ================== */
/* ================================================================ */

#define LCD_8BIT_MODE                   1
#define LCD_4BIT_MODE                   0
#define LCD_MODE                        LCD_8BIT_MODE

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

/* ================================================================ */
/* ============= APIs Supported by "HAL LCD DRIVER"============== */
/* ================================================================ */

void lcd_initialize(lcd_t *lcd);
void lcd_send_command(lcd_t *lcd, uint8_t command);
void lcd_send_char_data(lcd_t *lcd, uint8_t data);
void lcd_set_cursor_pos(lcd_t *lcd, uint8_t row, uint8_t col);
void lcd_send_char_data_pos(lcd_t *lcd, uint8_t data, uint8_t row, uint8_t column);
void lcd_send_string(lcd_t *lcd, uint8_t str[]);
void lcd_send_string_pos(lcd_t *lcd, uint8_t str[], uint8_t row, uint8_t column);
void lcd_send_custom_char(lcd_t *lcd, uint8_t custom_chr[], uint8_t row, uint8_t column, uint8_t memory_pos);

void covert_num_to_str(uint32_t num, char *s);

void _delay_ms(uint32 ms);

#endif



