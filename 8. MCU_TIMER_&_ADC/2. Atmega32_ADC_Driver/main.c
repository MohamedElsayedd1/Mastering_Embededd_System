/*
 * main.c
 *
 * Created: 05/12/2024 7:51:50 PM
 *  Author: Mohamed Elsayed
 */ 

#include <util/delay.h>
#include <xc.h>

#include "atmega32_GPIO_driver.h"
#include "atmega32_HAL_LCD.h"
#include "atmega32_UART_driver.h"
#include "atmega32_I2C_driver.h"
#include "atmega32_TIMER_driver.h"
#include "atmega32_ADC_driver.h"


#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

void my_itoa(int num, char* str, int base) {
	int i = 0, isNegative = 0;

	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return;
	}

	if (num < 0 && base == 10) {
		isNegative = 1;
		num = -num;
	}

	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num = num / base;
	}

	if (isNegative)
	str[i++] = '-';

	str[i] = '\0';

	// Reverse the string
	int start = 0, end = i - 1;
	while (start < end) {
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}

int main(void) {
	lcd_initialize();
	ADC_Init();

	while (1) {
		uint8_t digitalInput[] = "Digital : ";
		lcd_send_string_pos(digitalInput, ROW2, 1);
		uint8_t Voltage[] = "Voltage : ";
		lcd_send_string_pos(Voltage, ROW3, 1);
		uint8_t per[] = " Percentage : ";
		lcd_send_string_pos(per, ROW4, 1);

		// Read ADC value
		uint16_t digitalADC = ADC_Read(ADC_CHANNEL_0);

		// Convert ADC value to string
		char str[5];
		my_itoa(digitalADC, str, 10);  // Convert integer to string
		lcd_send_string_pos(str, ROW2, 10);  // Display ADC value

		// Convert ADC value to voltage
		float voltage = (digitalADC / 1023.0) * 5.0;
		char voltStr[6];
		sprintf(voltStr, "%.2f", voltage);
		lcd_send_string_pos(voltStr, ROW3, 10);  // Display voltage

		// Convert ADC value to percentage
		float percentage = (digitalADC * 100.00) / 1023.00;
		char perStr[7];
		sprintf(perStr, "%.2f", percentage);
		lcd_send_string_pos(perStr, ROW4, 14);  // Display percentage
		lcd_send_char_data_pos('%', ROW4, 19);
		_delay_ms(100);  // Small delay
	}

	return 0;
}

