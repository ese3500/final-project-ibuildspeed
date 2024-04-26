/*
 * GccApplication1.c
 *
 * Created: 2/23/2024 2:21:11 PM
 * Author : atewfik1
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

#include "i2c.h"
#include "lights.h"
#include "speedControllers.h"
#include "uart.h"
#include "ultrasonic.h"
char String[25];

// keeps track of distance
int distance = 0;

int speed = 0;   // neutral

int currADC = 0;
double duty = 0;

void
drive() {
    distance = get_distance();

    if (distance < 20) {
        e_brake();
    } else {
        //     sprintf(String, "distance: %d \n", distance);
        //     UART_putstring(String);

        // read the throttle value
        uint16_t acc_value = readGas();
        // uint16_t acc_value = readADC(1);
        sprintf(String, "GAS: %d \n", acc_value);
        UART_putstring(String);
        _delay_ms(1000);
        uint16_t brake_value = readBrake();
        // uint16_t brake_value = readADC(2);
        sprintf(String, "BRAKE: %d \n", brake_value);
        UART_putstring(String);

        if (brake_value < 1800 || acc_value < 1800) {
            neutral();
        }

        if (brake_value > 1800) {
            // both are being pressed --> we want to brake
            // OCR0B = set_brake(brake_value);
        } else if (acc_value > 1800) {
            // OCR0B = set_throttle(acc_value);
        }
    }
}

// 9.1 -> neutral
// 6.1 -> min
// 12.1 -> max
void
Initialize() {
    cli();
    Initialize_ultrasonic();
    Initialize_throttle();
    Initialize_light_PWM();
    Initialize_ADC();
    sei();
}

int
main(void) {

    UART_init(BAUD_PRESCALER);
    Initialize();
    neutral();
    _delay_ms(10000);
    while (1) {
        lights();
        drive();
        send_trigger();
        sprintf(String, "distance: %d \n", distance);
        UART_putstring(String);
        _delay_ms(100);
    }
}
