/*
 * lcd.c
 *
 *  Created on: Nov 29, 2024
 *      Author: Mohamed Elsayed
 */

#include "lcd.h"

static void lcd_send_4bit(lcd_t *lcd, uint8_t command);
static void lcd_send_EN(lcd_t *lcd);

static void lcd_send_4bit(lcd_t *lcd, uint8_t command) {
	MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[0].PinNum, ((command >> 0) & 0x01));
	MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[1].PinNum, ((command >> 1) & 0x01));
	MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[2].PinNum, ((command >> 2) & 0x01));
	MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[3].PinNum, ((command >> 3) & 0x01));
}

static void lcd_send_EN(lcd_t *lcd) {
	MCAL_GPIO_WritePin(lcd->ControlRegister, lcd->EN.PinNum , GPIO_HIGH); // EN = High
    _delay_ms(5);                  // Small delay
    MCAL_GPIO_WritePin(lcd->ControlRegister, lcd->EN.PinNum , GPIO_LOW); // EN = Low
    _delay_ms(5); 
}

void lcd_initialize(lcd_t *lcd) {
    // Set LCD control pins as output
	MCAL_GPIO_Init(lcd->ControlRegister, &(lcd->EN));
	MCAL_GPIO_Init(lcd->ControlRegister, &(lcd->RS));
	MCAL_GPIO_WritePin(lcd->ControlRegister, lcd->RS.PinNum, lcd->RS.PinState);
	MCAL_GPIO_WritePin(lcd->ControlRegister, lcd->EN.PinNum, lcd->EN.PinState);

    #if LCD_MODE == LCD_4BIT_MODE
    // Set LCD pins for 4-bit mode
	for(int i = 0; i < 4; i++){
		MCAL_GPIO_Init(lcd->DataRegister, &(lcd->DataPins[i]));
		MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[i].PinNum, lcd->DataPins[i].PinState);
	}

    // Initial delay for LCD power-up
    _delay_ms(20);

    // Function Set: 4-bit mode, 2 lines, 5x8 dots
    lcd_send_command(lcd, _LCD_RETURN_HOME);  // Initialize LCD to 4-bit mode
    _delay_ms(5);
    lcd_send_command(lcd, _LCD_4BIT_MODE_2LINE);  // Function Set: 4-bit, 2 lines, 5x8 font

    #endif

    #if LCD_MODE == LCD_8BIT_MODE
    // Set LCD pins for 8-bit mode
    // Set all pins for data as output
    for(int i = 0; i < 8; i++){
    	MCAL_GPIO_Init(lcd->DataRegister, &(lcd->DataPins[i]));
    	MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[i].PinNum, lcd->DataPins[i].PinState);
    }

    _delay_ms(20); // Wait for the LCD to power up

    // 8-bit, 2-line, 5x8 dots
    lcd_send_command(lcd, _LCD_8BIT_MODE_2LINE);

    #endif

    _delay_ms(5);  // Wait for initialization
    // Display on, cursor off
    lcd_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
    _delay_ms(1);
    // Clear the LCD and return home
    lcd_send_command(lcd, _LCD_CLEAR);
    _delay_ms(2);
    // Increment cursor without shifting
    lcd_send_command(lcd, _LCD_INC_SHIFT_OFF);
    _delay_ms(1);
    lcd_send_command(lcd, _LCD_DDRAM_START);
    _delay_ms(1);
}

void lcd_send_command(lcd_t *lcd, uint8_t command) {
    // Set RS = 0 for command mode
    MCAL_GPIO_WritePin(lcd->ControlRegister, lcd->RS.PinNum , GPIO_LOW);

    #if LCD_MODE == LCD_4BIT_MODE
    // Send Higher Nibble first
    lcd_send_4bit(lcd, (command >> 4) & 0x0F);
    lcd_send_EN(lcd);  // Enable pulse
    // Send Lower Nibble
    lcd_send_4bit(lcd, command & 0x0F);
    lcd_send_EN(lcd);  // Enable pulse
    #endif

    #if LCD_MODE == LCD_8BIT_MODE
    // Send full 8-bit command
    for(int i = 0; i < 8; i++){
    	MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[i].PinNum, ((command >> i) & 0x01));
    }
    lcd_send_EN(lcd);  // Enable pulse
    #endif
}

void lcd_send_char_data(lcd_t *lcd, uint8_t data) {
    // Set RS = 1 for data mode
	MCAL_GPIO_WritePin(lcd->ControlRegister, lcd->RS.PinNum , GPIO_HIGH);

    #if LCD_MODE == LCD_4BIT_MODE
    // Send Higher Nibble first
    lcd_send_4bit(lcd, (data >> 4) & 0x0F);
    lcd_send_EN(lcd);  // Enable pulse
    // Send Lower Nibble
    lcd_send_4bit(lcd, data & 0x0F);
    lcd_send_EN(lcd);  // Enable pulse
    #endif

    #if LCD_MODE == LCD_8BIT_MODE
    // Send full 8-bit data
    for(int i = 0; i < 8; i++){
		MCAL_GPIO_WritePin(lcd->DataRegister, lcd->DataPins[i].PinNum, ((data >> i) & 0x01));
	}
    lcd_send_EN(lcd);  // Enable pulse
    #endif
}

void lcd_set_cursor_pos(lcd_t *lcd, uint8_t row, uint8_t col){
    switch(row){
        case ROW1 :
            lcd_send_command(lcd, 0x80 + col - 1);
            break;
        case ROW2 :
            lcd_send_command(lcd, 0xC0 + col - 1);
            break;
        case ROW3 :
            lcd_send_command(lcd, 0x94 + col - 1);
            break;
        case ROW4 :
            lcd_send_command(lcd, 0xd4 + col - 1);
            break;
    }
}

void lcd_send_char_data_pos(lcd_t *lcd, uint8_t data, uint8_t row, uint8_t column){
    lcd_set_cursor_pos(lcd, row, column);
    lcd_send_char_data(lcd, data);
}

void lcd_send_string(lcd_t *lcd, uint8_t str[]){
    while(*str != '\0'){
        lcd_send_char_data(lcd, *str++);
    }
}

void lcd_send_string_pos(lcd_t *lcd, uint8_t str[], uint8_t row, uint8_t column){
    lcd_set_cursor_pos(lcd, row, column);
    lcd_send_string(lcd, str);
}

void covert_num_to_str(uint32_t num, char *s) {
    int count = 0;
    
    // Handle 0 case separately
    if (num == 0) {
        s[count++] = '0';
        s[count] = '\0';
        return;
    }

    while(num != 0) {
        int reminder = num % 10;
        num = num / 10;
        s[count] = reminder + '0';
        count++;
    }
    s[count] = '\0';
    
    int start = 0, end = count - 1;
    while(start < end) {
        char temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

void lcd_send_custom_char(lcd_t *lcd, uint8_t custom_chr[], uint8_t row, uint8_t column, uint8_t memory_pos) {
    // Validate memory position
    if (memory_pos > 7) return; // CGRAM only supports 8 custom characters

    // Set CGRAM address to write the custom character
    lcd_send_command(lcd, _LCD_CGRAM_START + (memory_pos * 8));

    // Write the custom character data to CGRAM
    for (int i = 0; i < 8; i++) { // Ensure 8 rows
        lcd_send_char_data(lcd, custom_chr[i]);
    }

    // Display the custom character at the specified position
    lcd_send_char_data_pos(lcd, memory_pos, row, column);
}

void _delay_ms(uint32 ms) {
    volatile uint32 i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 255; j++) {

        }
    }
}

