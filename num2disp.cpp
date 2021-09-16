/**
 @file num2disp.cpp
 @brief Library for interfacing numerical displays
 @author Edward62740
 */

#include "num2disp.h"
#include <Arduino.h>

struct FullDisplayStruct FullDisplay;
uint8_t internal_num_current[6];
uint8_t internal_num_prev[6];
uint32_t record_time = 0;

/**
 @brief map digits to pinout for a single display
 @param [in] *num pointer to NumericalDisplay_t
 @param [in] pinout[] 
 */
num2disp_err_t num2disp_createInstanceNumericalDisplay(NumericalDisplay_t *num,
		uint8_t pinout[]) {
	for (int i = 0; i <= 10; i++) {
		num->pinout[i] = pinout[i];
	}
	return NO_ERR;
}

/**
 @brief combine single displays into a group
 @param [in] *num1:6 pointer to NumericalDisplay_t
 @param [in] num_active number of active digits (max 6)
 @param [in] num_offset offset of digits from left 
 */
num2disp_err_t num2disp_createInstanceFullDisplay(NumericalDisplay_t *num1,
		NumericalDisplay_t *num2, NumericalDisplay_t *num3,
		NumericalDisplay_t *num4, NumericalDisplay_t *num5,
		NumericalDisplay_t *num6, uint8_t num_active, uint8_t num_offset) {
	FullDisplay.display[0] = *num1;
	FullDisplay.display[1] = *num2;
	FullDisplay.display[2] = *num3;
	FullDisplay.display[3] = *num4;
	FullDisplay.display[4] = *num5;
	FullDisplay.display[5] = *num6;
	FullDisplay.num_active = num_active;
	FullDisplay.num_offset = num_offset;
	return NO_ERR;
}

/**
 @brief write a maximum of 6 digits to the displays
 @param [in] num number to be written
 @param [in] prev_num previous number on the display
 @param [in] crossfade option to crossfade write
 */
num2disp_err_t num2disp_writeNumberToFullDisplay(uint32_t num,
		uint32_t prev_num, bool crossfade) {

	num2disp_err_t ret = 0;

	if (num > 999999 | prev_num > 999999) {
		return PARAM_FAIL;
	}
	for (int i = 0; i < 6; i++) {

		internal_num_current[5 - i] = num % 10;
		num = (num - num % 10) / 10;
	}
	for (int i = 0; i < 6; i++) {

		internal_num_prev[5 - i] = prev_num % 10;
		prev_num = (prev_num - prev_num % 10) / 10;
	}
	for (uint8_t n = 0; n < 6; n++) {

		uint8_t current = internal_num_current[n];
		uint8_t prev = internal_num_prev[n];
		num2disp_writeNumberToNumericalDisplay(n, current, prev, crossfade);
	}

	return NO_ERR;

}

/**
 @brief write a digit to a single display
 @param [in] index order of display from left
 @param [in] digit digit to be written
 @param [in] prev_digit previous digit
 @param [in] crossfade option to crossfade write
 */
num2disp_err_t num2disp_writeNumberToNumericalDisplay(uint8_t index,
		uint8_t digit, uint8_t prev_digit, bool crossfade) {
	uint8_t gpio_digit_current =
			(uint8_t) FullDisplay.display[index].pinout[digit]; //get pin number from NumericalDisplayStruct
	uint8_t gpio_digit_prev =
			(uint8_t) FullDisplay.display[index].pinout[prev_digit];

	if (crossfade && (gpio_digit_current != gpio_digit_prev)) {
		num2disp_gpio_write(gpio_digit_current, 0);
		num2disp_gpio_write(gpio_digit_prev, 1);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.8);
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.2);
		num2disp_gpio_write(gpio_digit_current, 0);
		num2disp_gpio_write(gpio_digit_prev, 1);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.7);
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.3);

		num2disp_gpio_write(gpio_digit_current, 0);
		num2disp_gpio_write(gpio_digit_prev, 1);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.6);
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.4);
		num2disp_gpio_write(gpio_digit_current, 0);
		num2disp_gpio_write(gpio_digit_prev, 1);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.5);
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.5);

		num2disp_gpio_write(gpio_digit_current, 0);
		num2disp_gpio_write(gpio_digit_prev, 1);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.4);
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.6);
		num2disp_gpio_write(gpio_digit_current, 0);
		num2disp_gpio_write(gpio_digit_prev, 1);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.3);
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.7);

		num2disp_gpio_write(gpio_digit_current, 0);
		num2disp_gpio_write(gpio_digit_prev, 1);
		delay(CROSSFADE_PULSE_CYCLE_MS * 0.2);
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);

	} else if (!crossfade && (gpio_digit_current != gpio_digit_prev)) {
		num2disp_gpio_write(gpio_digit_current, 1);
		num2disp_gpio_write(gpio_digit_prev, 0);

	} else {
		num2disp_gpio_write(gpio_digit_current, 1);
	}

	return NO_ERR;
}

/**
 @brief write time to the display
 @param [in] sec seconds
 @param [in] min minutes
 @param [in] hr hours
 @param [in] crossfade option to crossfade write
 @param [in] nosec option to exclude seconds from 4-digit displays
 */
num2disp_err_t num2disp_writeTimeToFullDisplay(uint32_t sec, uint32_t min,
		uint32_t hr, bool crossfade, bool nosec) {

	uint32_t time = 0;
	uint32_t prev_time = 0;

	if (!nosec) {
		time = (uint32_t)(sec + min * 100 + hr * 10000);
		if (time == record_time) {
			return 0;
		}
		record_time = time;
		prev_time = (sec + min * 60 + hr * 3600) - 1;
		uint32_t temp_hr = (prev_time - (prev_time % 3600)) / 3600;
		uint32_t temp_min = ((prev_time - (temp_hr * 3600)) % 60) / 60;
		uint32_t temp_sec = (prev_time - (temp_hr * 3600 + temp_min * 60)) / 60;
		prev_time = (uint32_t)(temp_sec + temp_min * 100 + temp_hr * 10000);

	}
	num2disp_writeNumberToFullDisplay(time, prev_time, crossfade);
	return NO_ERR;

}
