#ifndef ADC_H
#define ADC_H
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
uint16_t readADC(uint8_t ADCchannel);
void Initialize_ADC();
#endif