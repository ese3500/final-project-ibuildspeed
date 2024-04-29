/*
 * main2.c
 *
 * Created: 4/29/2024 1:06:39 PM
 *  Author: abdellah
 */ 
#define F_CPU          16000000UL
#define BAUD_RATE      9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>   // Include the math library for the exp() function
#include <stdio.h>
#include <stdlib.h>

#include <util/delay.h>

#include "adc.h"
#include "i2c.h"
#include "lights.h"
#include "speedControllers.h"
#include "uart.h"
#include "ultrasonic.h"
char String[25];

int speed = 0;


void
drive() {	
		// read the throttle value
		uint16_t acc_value = readGas();
		_delay_ms(50);
		uint16_t brake_value = readBrake();

		if (brake_value < 1800  || acc_value < 1800) {
			neutral();
		}

		if (brake_value > 1800) {
			// both are being pressed --> we want to brake
			OCR0B = set_brake(brake_value);
			// 		brake_lights();
			} else if (acc_value > 1800) {
			OCR0B = set_throttle(acc_value);
		}
}

// 1800 (0) --> 16000
// every 473 --> +/- .1 duty cycle 

// 9.1 -> neutral
// 6.1 -> min
// 12.1 -> max
int
main(void) {
	Initialize_light_PWM();
	UART_init(BAUD_PRESCALER);
	sprintf(String, "test\n");
	UART_putstring(String);
	uint16_t brake = 0;
	uint16_t gas = 0;
	while (1) {
		drive();
// 		brake = readBrake();
// 		sprintf(String, "Brake: %d \n", brake);
// 		UART_putstring(String);
// 		_delay_ms(50);
// 		gas = readGas();
// 		sprintf(String, "Gas: %d \n", gas);
// 		UART_putstring(String);
// 		_delay_ms(50);

	}
}
