# num2disp

Arduino library for interfacing GPIO to generic nixie tubes or other numerical displays with discrete 0-9 control pins. 

## Prerequisites
* Arduino compatible microcontroller
* Sufficient microcontroller GPIO, or GPIO expander
\
## How to use
\
Declare an instance of NumericalDisplay_t and pinout array for each tube. The pinout must be ordered from 0 to 9.
```C++
NumericalDisplay_t num1;
uint8_t pinout1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
```
\
Link the pinout to the NumericalDisplay_t.
```C++
num2disp_createInstanceNumericalDisplay(&num1, pinout1);
```
\
Link all the instances of NumericalDisplay_t to be controlled as a single set. The last two arguments are the number of active tubes (of 6) and offset from left respectively.
```C++
num2disp_createInstanceFullDisplay(&tube1, &tube2, &tube3, &tube4, &tube5, &tube6, 6, 0);
```
\
Write a number to the tubes. The first two arguments are the number to be written and the previous number (i.e the one currently on the tubes). The final argument is an option to enable crossfade transistion.
```C++
num2disp_err_t num2disp_writeNumberToFullDisplay(x,
		x - 1, true);
```
