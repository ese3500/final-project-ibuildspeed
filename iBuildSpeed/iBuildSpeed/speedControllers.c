#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>

void
Initialize_throttle() {
    cli();
    // input pins
    DDRC &= ~(1 << DDRC1);
    DDRC &= ~(1 << DDRC2);
    // 0V (min) to 5V (max)
    // 0 --> 1023
    sei();
}

double
set_throttle(uint16_t acc_value) {
    // Define start and end points of input and output ranges
    const double start_x = 0;
    const double end_x = 1023;
    const double start_y = 9.1;
    const double end_y = 12.1;

    // Calculate slope (change in y / change in x)
    const double slope = (end_y - start_y) / (end_x - start_x);

    // Calculate and return the output value using the linear equation
    double result = start_y + slope * (acc_value - start_x);

    return (OCR0A * result / 100.0);
}

double
set_brake(uint16_t brake_value) {
    // Constants for the formula
    const double L = 6.1;     // Lower asymptote
    const double U = 8.9;     // Upper asymptote
    const double k = 0.008;   // Decay rate
    const double x0 = 512;    // Midpoint

    // Logistic decay formula
    double result = L + (U - L) / (1 + exp(k * (brake_value - x0)));

    return (OCR0A * result / 100.0);
}

void
e_brake() {
    OCR0B = OCR0A * 6.1 / 100.0;
}

void
neutral() {
    OCR0B = OCR0A * 9.1 / 100.0;
}
