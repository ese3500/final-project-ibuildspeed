#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
void
Initialize_throttle() {
    cli();
    // input pins
    DDRC &= ~(1 << DDRC1);
    DDRC &= ~(1 << DDRC2);

	//sets output pin for brake lights and initializes as off
	DDRB |= (1<<DDB5);
	PORTB &= ~(1<<PORTB5);
	
	//output for buzzer
	DDRD |= (1 << DDRD7); 
	PORTD &= ~(1 << PORTD7); 
    // 0V (min) to 5V (max)
    // 0 --> 1023
    sei();
}

void brake_lights() {
	if(OCR0B < (OCR0A * 8.5 / 100)) {
		PORTB |= (1<<PORTB5);
	} else {
		PORTB &= ~(1<<PORTB5);
	}
}


double
set_throttle(uint16_t acc_value) {
    // Define start and end points of input and output ranges
    const double start_x = 1800;
    const double end_x = 16000;
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
    const double U = 9.2;     // Upper asymptote
    const double k = 0.00029;   // Decay rate
    const double x0 = 7100;    // Midpoint

    // Logistic decay formula
    double result = L + (U - L) / (1 + exp(k * (brake_value - x0)));

    return (OCR0A * result / 100.0);
}

void
e_brake() {
 	if((PIND >> 0x4) == 1) {
		OCR0B = OCR0A * 6.1 / 100.0;
			PORTD |= (1 << PORTD7);
			_delay_ms(5000);
			PORTD &= ~(1 << PORTD7);
			brake_lights();
 	}

}

void
neutral() {
    OCR0B = OCR0A * 9.1 / 100.0;
}
