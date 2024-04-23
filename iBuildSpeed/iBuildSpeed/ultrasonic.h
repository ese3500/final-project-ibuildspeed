#ifndef ULTRASONIC_H
#define ULTRASONIC_H
// #define F_CPU          16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
// Declare the function to initialize the ultrasonic sensor
void Initialize_ultrasonic(void);
void send_trigger();
// External variable for duration
extern volatile int duration;
extern volatile int start;
extern volatile int end;

uint16_t get_distance();
#endif
