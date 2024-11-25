#include "lcd.h"

static void lcd_send_4bit(uint8_t command);
static void lcd_send_EN();

static void lcd_send_4bit(uint8_t command) {
    // Clear Lower Nipple First
    LCD_DATA_PORT &= ~(0x0F << 0);
    LCD_DATA_PORT |= (command & 0x0F);
}

static void lcd_send_EN() {
    LCD_CRTL_PORT |= (1 << EN);    // EN = High
    _delay_ms(5);                  // Small delay
    LCD_CRTL_PORT &= ~(1 << EN);   // EN = Low
    _delay_ms(5); 
}

void lcd_initialize() {
    // Set LCD control pins as output
    LCD_CRTL_DIRECTION |= (1 << RS);
    LCD_CRTL_DIRECTION |= (1 << EN);
    LCD_CRTL_PORT &= ~(1 << RS); // RS = Low
    LCD_CRTL_PORT &= ~(1 << EN); // EN = Low

    #if LCD_MODE == LCD_4BIT_MODE
    // Set LCD pins for 4-bit mode
    LCD_DIRECTION_PORT = 0x0F;  // Set lower 4 bits for data pins as output
    LCD_DATA_PORT &= 0xF0;       // Clear lower 4 bits

    // Initial delay for LCD power-up
    _delay_ms(20);

    // Function Set: 4-bit mode, 2 lines, 5x8 dots
    lcd_send_command(_LCD_RETURN_HOME);  // Initialize LCD to 4-bit mode
    _delay_ms(5);
    lcd_send_command(_LCD_4BIT_MODE_2LINE);  // Function Set: 4-bit, 2 lines, 5x8 font

    #endif
    #if LCD_MODE == LCD_8BIT_MODE
    // Set LCD pins for 8-bit mode
    LCD_DIRECTION_PORT = 0xFF;  // Set all pins for data as output
    LCD_DATA_PORT = 0x00;       // Clear all data pins

    _delay_ms(20); // Wait for the LCD to power up
    // 8-bit, 2-line, 5x8 dots
    lcd_send_command(_LCD_8BIT_MODE_2LINE);
    #endif

    _delay_ms(5);  // Wait for initialization
    // Display on, cursor off
    lcd_send_command(_LCD_CURSOR_OFF_DISPLAY_ON);
    _delay_ms(1);
    // Clear the LCD and return home
    lcd_send_command(_LCD_CLEAR);
    _delay_ms(2);
    // Increment cursor without shifting
    lcd_send_command(_LCD_INC_SHIFT_OFF); 
    _delay_ms(1);
    lcd_send_command(_LCD_DDRAM_START);
    _delay_ms(1);
}

void lcd_send_command(uint8_t command) {
    // Set RS = 0 for command mode
    LCD_CRTL_PORT &= ~(1 << RS);

    #if LCD_MODE == LCD_4BIT_MODE
    // Send Higher Nibble first
    lcd_send_4bit((command >> 4) & 0x0F);
    lcd_send_EN();  // Enable pulse
    // Send Lower Nibble
    lcd_send_4bit(command & 0x0F);
    lcd_send_EN();  // Enable pulse
    #endif

    #if LCD_MODE == LCD_8BIT_MODE
    // Send full 8-bit command
    LCD_DATA_PORT = command;
    lcd_send_EN();  // Enable pulse
    #endif
}

void lcd_send_char_data(uint8_t data) {
    // Set RS = 1 for data mode
    LCD_CRTL_PORT |= (1 << RS);

    #if LCD_MODE == LCD_4BIT_MODE
    // Send Higher Nibble first
    lcd_send_4bit((data >> 4) & 0x0F);
    lcd_send_EN();  // Enable pulse
    // Send Lower Nibble
    lcd_send_4bit(data & 0x0F);
    lcd_send_EN();  // Enable pulse
    #endif

    #if LCD_MODE == LCD_8BIT_MODE
    // Send full 8-bit data
    LCD_DATA_PORT = data;
    lcd_send_EN();  // Enable pulse
    #endif
}

void lcd_set_cursor_pos(uint8_t row, uint8_t col){
    switch(row){
        case ROW1 :
            lcd_send_command(0x80 + col - 1);
            break;
        case ROW2 :
            lcd_send_command(0xC0 + col - 1);
            break;
        case ROW3 :
            lcd_send_command(0x94 + col - 1);
            break;
        case ROW4 :
            lcd_send_command(0xd4 + col - 1);
            break;
    }
}

void lcd_send_char_data_pos(uint8_t data, uint8_t row, uint8_t column){
    lcd_set_cursor_pos(row, column);
    lcd_send_char_data(data);
}

void lcd_send_string(uint8_t str[]){
    while(*str != '\0'){
        lcd_send_char_data(*str++);
    }
}

void lcd_send_string_pos(uint8_t str[], uint8_t row, uint8_t column){
    lcd_set_cursor_pos(row, column);
    lcd_send_string(str);
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

void lcd_send_custom_char(uint8_t custom_chr[], uint8_t row, uint8_t column, uint8_t memory_pos) {
    // Validate memory position
    if (memory_pos > 7) return; // CGRAM only supports 8 custom characters

    // Set CGRAM address to write the custom character
    lcd_send_command(_LCD_CGRAM_START + (memory_pos * 8));

    // Write the custom character data to CGRAM
    for (int i = 0; i < 8; i++) { // Ensure 8 rows
        lcd_send_char_data(custom_chr[i]);
    }

    // Display the custom character at the specified position
    lcd_send_char_data_pos(memory_pos, row, column);
}