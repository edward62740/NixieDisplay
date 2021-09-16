/**
 @file num2disp.cpp
 @brief Library for interfacing numerical displays
 @author Edward62740
 */


#ifndef NUM2DISP_H
#define NUM2DISP_H

#include <Arduino.h>

#define CROSSFADE_PULSE_CYCLE_MS 16

typedef struct NumericalDisplayStruct {
	uint8_t digit[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	uint8_t pinout[10];
} NumericalDisplay_t;

struct FullDisplayStruct {
	NumericalDisplay_t display[6]; // display index from right
	uint8_t num_active;
	uint8_t num_offset;
};

enum {
	NO_ERR, NODESC_FAIL, COMMS_FAIL, PARAM_FAIL
};

typedef int8_t num2disp_err_t;

extern void num2disp_gpio_write(uint8_t pin, bool data);

num2disp_err_t num2disp_createInstanceNumericalDisplay(NumericalDisplay_t *num,
		uint8_t pinout[]);

num2disp_err_t num2disp_createInstanceFullDisplay(NumericalDisplay_t *num1,
		NumericalDisplay_t *num2, NumericalDisplay_t *num3,
		NumericalDisplay_t *num4, NumericalDisplay_t *num5,
		NumericalDisplay_t *num6, uint8_t num_active, uint8_t num_offset);

num2disp_err_t num2disp_writeNumberToFullDisplay(uint32_t num,
		uint32_t prev_num, bool crossfade);

num2disp_err_t num2disp_writeTimeToFullDisplay(uint32_t sec, uint32_t min,
		uint32_t hr, bool crossfade, bool nosec);

num2disp_err_t num2disp_writeNumberToNumericalDisplay(uint8_t index,
		uint8_t digit, uint8_t prev_digit, bool crossfade);

#endif // NTC_PCA9698_H
