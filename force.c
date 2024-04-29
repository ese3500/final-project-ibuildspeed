/*
 * force.c
 *
 * Created: 3/29/2024 4:10:23 PM
 *  Author: Ahmed
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#define ACC_PAD PORTC5
#define DEC_PAD PORTC4

void Initialize()
{
	cli();
	sei();
}

int main(void) {
	
	
}
